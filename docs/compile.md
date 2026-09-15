你可以按照如下方式在本地部署并预览这个项目。

## 克隆仓库

```bash
git clone https://github.com/xjtu-ai/xjtu-ai.github.io.git --depth=1 
cd xjtu-ai.github.io 
```

## 安装依赖

```bash
pip install mkdocs-material mkdocs-material-extensions mkdocs_pymdownx_material_extras
```

## 本地预览

为了降低主储存库大小，PDF 文件作为子模块存储在 **[xjtu-ai/static](https://github.com/xjtu-ai/static)**，如果需要构建网站，要先拉取子模块。

```bash
git submodule sync
git submodule update --init --recursive
mkdocs serve # server on localhost:8000
```

请勿在本地大量更改 static 子模块！如果要上传 pdf 文档推荐在 github 上上传。

## 构建

```bash
git submodule sync
git submodule update --init --recursive
mkdocs build
```

## 检查坏引用

构建之后建议检查站内引用（图片、链接、`/static/...` 的 PDF）是否都能解析到实际文件：

```bash
mkdocs build --strict
python3 tools/check_refs.py site --check-static
```

MkDocs 只会重写 Markdown 语法（`![alt](a.png)`）里的相对路径，直接写在 Markdown 里的 raw HTML（如 `<img src="images/x.png">`）会原样输出。而页面使用的是目录式 URL（`a.md` 对应 `/a/`），所以这类引用很容易指错目录，导致线上 404，而且 `mkdocs build --strict` 检查不出来。CI 的 compile-check 已经包含这一步。
