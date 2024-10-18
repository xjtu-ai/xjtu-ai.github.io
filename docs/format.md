本页面参考了 **[OI-Wiki](https://oi-wiki.org/intro/format/)**。

其实没有什么需要刻意遵守的规则，本文更多是教你如何使用 Markdown。

## 内嵌 PDF 的格式要求

### 如何上传

为了降低主储存库大小，PDF 文件作为子模块存储在 **[xjtu-ai/static](https://github.com/xjtu-ai/static)**。这样，普通的编辑无需拉取大量 pdf 文件。

若要提交新的 pdf,请移步 **[xjtu-ai/static](https://github.com/xjtu-ai/static)** 使用 upload files。

### 嵌入格式

由于前人的资料大多难以获得 Markdown 源码，我们采取 PDF 格式呈现。

展示 PDF 的时候，请遵循如下格式：

```markdown
## PDF 文档的标题（级数可以自定）

PDF 文档的摘要

??? note "PDF 文档的标题"
    <iframe loading="lazy" src="PDF 文档的绝对路径（从网站根目录开始，如/static/course/math/docs/巧用换元积分法一题九解.pdf）"></iframe>
```

这使用一个默认不展开的 note 包裹 pdf 文件。`??? note` 是 mkdocs 支持的语法，可以查看 [MkDocs Material 文档](https://squidfunk.github.io/mkdocs-material/reference/admonitions/)。

注意 `loading="lazy"` 至关重要。这将懒加载文件，等到读者展开 note 时才会加载。否则较大的 pdf 会严重拖慢网站加载速度。

上面例子的效果如下：

???+ note "效果"
    ### 巧用换元积分法一题九解
    
    本文探讨了换元积分法在解决不定积分问题中的应用和技巧。作者通过一道具体的积分习题，展示了九种不同的换元积分解法，包括三角代换、双曲代换、倒代换等常用技巧。这些方法涉及将被积函数变形以适应基本积分公式，以及通过分解被积函数并逐步凑微元变形来解决积分问题。文章强调，不定积分的结果是一个原函数的集合，通常表示为一个原函数加上任意常数。重要的是，只要积分结果的导数等于被积函数，该结果就是正确的，即使形式上可能与参考答案不同。通过这些解法，作者旨在提高学生在积分方面的水平，鼓励他们在实践中探索和总结换元积分的技巧。
    
    ??? note "巧用换元积分法一题九解"
        <iframe loading="lazy" src="/static/course/math/docs/巧用换元积分法一题九解.pdf" type="application/pdf" width=100% height=1000px></iframe>

### 自动生成脚本

如果你觉得上面的 html 代码难以记忆，可以使用如下的脚本：

??? note "summary.py"
    ```python
    from pathlib import Path
    from openai import OpenAI
    import sys
    import os
    
    key = None # 或者填入 API key
    outdir = # pdf 的绝对路径（不包含文件名），如'/static/course/math/docs'
    if outdir == None :
        outdir = '/'
    path = Path(sys.argv[1])
    basename = path.name[:-4]
    
    print("## %s\n" % basename)
    
    if key != None:
        client = OpenAI(
            api_key = key,
            base_url = "https://api.moonshot.cn/v1",
        )
        file_object = client.files.create(file=path, purpose="file-extract")
        file_content = client.files.content(file_id=file_object.id).text
        
        messages = [
            {
                "role": "system",
                "content": "你是 Kimi，由 Moonshot AI 提供的人工智能助手，你更擅长中文和英文的对话。你会为用户提供安全，有帮助，准确的回答。同时，你会拒绝一切涉及恐怖主义，种族歧视，黄色暴力等问题的回答。Moonshot AI 为专有名词，不可翻译成其他语言。",
            },
            {
                "role": "system",
                "content": file_content,
            },
            {"role": "user", "content": "请生成上传文件的摘要。字数不要超过 300 字。"},
        ]
    
        try :
            completion = client.chat.completions.create(
                model="moonshot-v1-auto",
                messages=messages,
                temperature=0.3,
            )
            print(completion.choices[0].message.content)
            print("")
            
        except :
            print("调用 API 失败")

        client.files.delete(file_id=file_object.id)
    
    print("??? note \"%s\"\n    <iframe loading="lazy" src=\"%s/%s.pdf\" type=\"application/pdf\" width=100%% height=1000px></iframe>\n" 
        % (basename, outdir, basename))%
    ```

在脚本中设定 `dir` 之后，运行 `python summary.py a.pdf` 就会生成 `a.pdf` 对应的 html 代码。如果 `key` 不是 `None`，而被指定为某个兼容 OpenAI api 的 api-key（脚本中是 Kimi），那么这个脚本还会自动用 AI 生成摘要。

## Markdown 的格式要求

-   不要使用如 `<h1>` 或者 `# 标题` 的一级标题。
-   标题要空一个英文半角空格，例如：`## 简介`。
-   列表：
    -   列表前要有空行，新开一段。
    -   使用有序列表（如 `1. 例子`）时，点号后要有空格。
-   行间公式前后各要有一行空行，否则会被当做是行内公式。
-   使用 `???` 或 `!!!` 开头的 Details 语法时，每一行要包括在 Details 语法的文本框的文本，开头必须至少有 4 个空格。
    **即使是空行，也必须保持与其他行一致的缩进。请不要使用编辑器的自动裁剪行末空格功能。**

    ???+ success "示例"
        ```text
        ???+ warning
            请记得在文本前面添加 4 个空格。其他的语法还是与 Markdown 语法一致。
            
            不添加 4 个空格的话，文本就不会出现在 Details 文本框里了。
            
            这个`???`是什么的问题会在下文解答。
        ```
        
        ???+ warning
            请记得在文本前面添加 4 个空格。其他的语法还是与 Markdown 语法一致。
            
            不添加 4 个空格的话，文本就不会出现在 Details 文本框里了。
            
            这个 `???` 是什么的问题会在下文解答。

-   代码样式的纯文本块请使用 ` ```text`。直接使用 ` ``` ` 而不指定纯文本块里的语言，可能会导致内容被错误地缩进。
-   表示强调时请使用 `**SOMETHING**` 和 `「」`，而非某级标题，因为使用标题会导致文章结构层次混乱和（或）目录出现问题。

-   当需要引用题目链接时，应尽可能使用原 OJ 题库中的链接而不是镜像链接。

-   请正确使用 Markdown 的区块功能。插入行内代码请使用一对反引号包围代码区块；行间代码请使用一对 ` ``` ` 包围代码区块，其中反引号就是键盘左上角波浪线下面那个符号，行间代码请在第一个 ` ``` ` 的后面加上语言名称（如：` ```cpp`）。

    ???+ success "示例"
        ````text
        ```cpp
        // #include<stdio.h>    //不好的写法
        #include <cstdio>  //好的写法
        ```
        ````
        
        ```cpp
        // #include<stdio.h>    //不好的写法
        #include <cstdio>  //好的写法
        ```

-   「参考资料与注释」使用 Markdown 的脚注功能进行编写。格式为：

    ```markdown
    文本内容。[^脚注名]
    [^脚注名]: 参考资料内容。注意：冒号是英文冒号，冒号后面跟着一个空格。
    ```

    脚注名既可以使用数字也可以使用文本。脚注名摆放的位置与括号的用法一致。为美观起见，建议同一个页面内的脚注名遵循统一的命名规律，如：ref1、ref2、note1……

    脚注的内容统一放在 `## 参考资料与注释` 二级标题下。

    ???+ success "示例"
        ```markdown
        当 `#include <cxxxx>` 可以替代 `#include <xxxx.h>` 时，应使用前者。[^ref1]
        
        2020年1月21日，CCF宣布恢复NOIP。[^ref2]
        
        ## 参考资料与注释
        
        [^ref1]: [cstdio stdio.h namespace](https://stackoverflow.com/questions/10460250/cstdio-stdio-h-namespace)
        
        [^ref2]: [CCF关于恢复NOIP竞赛的公告-中国计算机学会](https://www.ccf.org.cn/c/2020-01-21/694716.shtml)
        ```
        
        当 `#include <cxxxx>` 可以替代 `#include <xxxx.h>` 时，应使用前者。[^ref1]
        
        2020 年 1 月 21 日，CCF 宣布恢复 NOIP。[^ref2]

-   主题扩展的 `???+note` 格式（即 [Collapsible Blocks](https://squidfunk.github.io/mkdocs-material/reference/admonitions/#collapsible-blocks)），带 `+` 的会默认保持展开，而不带 `+` 的会默认保持折叠。
    折叠框的标题，即 `???+note` 中 `note` 后的内容应以 `"` 包裹起来。其中的内容支持 Markdown 语法。详见 [Admonition - Changing the title](https://squidfunk.github.io/mkdocs-material/reference/admonitions/#changing-the-title)。（不具备折叠功能的为一般的 Admonitions，参考 [Admonitions - Material for MkDocs](https://squidfunk.github.io/mkdocs-material/reference/admonitions)）

如果对 mkdocs-material（我们使用的这个主题）还有什么问题，还可以查阅 [MkDocs 使用说明](https://github.com/ctf-wiki/ctf-wiki/wiki/Mkdocs-%E4%BD%BF%E7%94%A8%E8%AF%B4%E6%98%8E)，其介绍了 mkdocs-material 主题的插件使用方式。

考虑到鼓励贡献者的因素，我们不给出更多的限制，关于数学公式、代码等，你可以按照喜欢的样式编写。

## 参考资料与注释

[^ref1]: [cstdio stdio.h namespace](https://stackoverflow.com/questions/10460250/cstdio-stdio-h-namespace)

[^ref2]: [CCF 关于恢复 NOIP 竞赛的公告 - 中国计算机学会](https://www.ccf.org.cn/c/2020-01-21/694716.shtml)
