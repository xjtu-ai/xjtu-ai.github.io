#!/usr/bin/env python3
"""检查 MkDocs 构建产物中的本地引用是否都能解析到实际文件。

覆盖 HTML 中所有会发起请求的属性：img/source/video/audio/embed/iframe/script/
link/a/object 的 src、srcset、href、data、poster，以及内联 style 中的 url(...)。

MkDocs 只会重写 Markdown 语法（![alt](a.png)、[文字](a.pdf)）里的相对路径，
直接写在 Markdown 中的 raw HTML（如 <img src="images/x.png">）会原样输出；
而页面使用的是目录式 URL（a.md -> /a/），这类引用很容易指错目录。本脚本用于
在 CI 中把这类 404 拦下来。

用法:
    python3 tools/check_refs.py [site_dir] [--check-static]

    site_dir        构建产物目录，默认 site
    --check-static  同时检查 /static/... 引用（需要先拉取 static 子模块）。
                    CI 中使用；本地未拉取子模块时会跳过这些引用并给出提示。
"""

from __future__ import annotations

import re
import sys
import urllib.parse
from collections import defaultdict
from html.parser import HTMLParser
from pathlib import Path

ATTRS = {
    "img": ("src", "srcset"),
    "source": ("src", "srcset"),
    "video": ("src", "poster"),
    "audio": ("src",),
    "embed": ("src",),
    "iframe": ("src",),
    "script": ("src",),
    "link": ("href",),
    "a": ("href",),
    "object": ("data",),
}

CSS_URL = re.compile(r"url\(\s*['\"]?([^'\")]+)['\"]?\s*\)")
EXTERNAL = ("http://", "https://", "//", "mailto:", "javascript:", "data:", "tel:", "#")


class RefCollector(HTMLParser):
    def __init__(self) -> None:
        super().__init__(convert_charrefs=True)
        self.refs: list[tuple[str, str, str]] = []

    def handle_starttag(self, tag: str, attrs) -> None:
        values = dict(attrs)
        for attr in ATTRS.get(tag, ()):
            if values.get(attr):
                self.refs.append((tag, attr, values[attr]))
        style = values.get("style")
        if style:
            self.refs.extend((tag, "style:url", url) for url in CSS_URL.findall(style))


def split_refs(attr: str, value: str):
    """srcset 是逗号分隔的候选列表，每项可以带 '2x' / '640w' 描述符。"""
    if attr != "srcset":
        return [value]
    return [item.strip().split(" ")[0] for item in value.split(",") if item.strip()]


def resolve(site: Path, page: Path, ref: str) -> Path:
    ref = urllib.parse.unquote(ref.strip())
    if ref.startswith("/"):
        return (site / ref.lstrip("/")).resolve()
    return (page.parent / ref).resolve()


def exists(target: Path) -> bool:
    if target.is_file():
        return True
    # 目录式 URL：/a/ 或 /a 都可能对应 a/index.html
    return (target / "index.html").is_file()


def main(argv: list[str]) -> int:
    args = [a for a in argv[1:] if not a.startswith("-")]
    site = Path(args[0] if args else "site").resolve()
    check_static = "--check-static" in argv[1:]

    if not site.is_dir():
        print(f"error: {site} 不存在，请先运行 mkdocs build", file=sys.stderr)
        return 2

    html_files = sorted(site.rglob("*.html"))
    if check_static and not (site / "static").is_dir():
        print(f"error: {site}/static 不存在，static 子模块似乎没有拉取", file=sys.stderr)
        return 2

    broken: dict[Path, list[tuple[str, str, str]]] = defaultdict(list)
    checked = skipped_static = 0
    for page in html_files:
        collector = RefCollector()
        collector.feed(page.read_text(encoding="utf-8", errors="ignore"))
        for tag, attr, value in collector.refs:
            for ref in split_refs(attr, value):
                if not ref or ref.startswith(EXTERNAL):
                    continue
                if ref.startswith("/static/") and not check_static:
                    skipped_static += 1
                    continue
                checked += 1
                if not exists(resolve(site, page, ref)):
                    broken[page].append((tag, attr, ref))

    print(f"pages: {len(html_files)}   local refs checked: {checked}   broken: {sum(map(len, broken.values()))}")
    if skipped_static:
        print(f"skipped {skipped_static} /static/... refs (本地运行未加 --check-static)")

    for page, items in sorted(broken.items()):
        print(f"\n--- {page.relative_to(site)}")
        for tag, attr, ref in items[:20]:
            print(f"    <{tag} {attr}={ref}>")
        if len(items) > 20:
            print(f"    ... 另有 {len(items) - 20} 处")

    return 1 if broken else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
