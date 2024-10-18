AI 学组欢迎一切形式的一切贡献。**如果你觉得这些流程太麻烦，可以直接轰炸网站的现任维护者 [@ShwStone](https://github.com/ShwStone)**。

本页面参考了 [**OI-wiki**](https://oi-wiki.org/intro/htc/)。

## 也许会有帮助

在编写过程中，你可能会需要阅读这些文档：

- **[Github Skills](https://skills.github.com/)**
- **[MkDocs](https://www.mkdocs.org/getting-started/)**
- **[MkDocs Material](https://squidfunk.github.io/mkdocs-material/creating-your-site/)**
- [$\LaTeX$](https://oi-wiki.org/tools/latex/)

## 参与协作

???+ warning
    在开始编写一段内容之前，请查阅 [Issues](https://github.com/xjtu-ai/xjtu-ai.github.io/issues)，或者加入 QQ 群，确认没有别人在做相同的工作之后，开个 [新 issue](https://github.com/xjtu-ai/xjtu-ai.github.io/issues/new) 记录待编写的内容。

请确保阅读了 **[格式规范](./format.md)**。其实没有什么需要刻意遵守的规则，格式规范更多是教你如何使用 Markdown。

不要害怕编辑，勇于更新页面！

### 在 GitHub 上编辑

参与编写 **需要** 一个 GitHub 账号（可以前往 [GitHub 的账号注册页面](https://github.com/signup) 页面注册），但 **不需要** 高超的 GitHub 技巧，即使你是一名新手，只要按照下面所述的步骤操作，也能够 **非常出色** 地完成编辑。

???+ tip
    在你的更改被合并到主仓库之前，你所作出的修改均不会出现在主站上，所以无需担心你的修改会破坏正在显示的内容。
    
    如果还是不放心，可以查看 [GitHub 的官方教程](https://skills.github.com/)。

#### 编辑单个页面内的内容

1.  在 **AI Wiki** 上找到对应页面；
2.  点击正文右上方（目录左侧）的 **「编辑此页」**（<i class="md-icon">edit</i>）按钮，点击按钮根据提示跳转到 GitHub 进行编辑；
3.  在编辑框内编写你想修改的内容。请注意，在修改和接下来的提交过程中，请 **关闭您的自动翻译软件**，因为它可能产生不必要的麻烦（例如您修改的文件有时会被其错误改名，从而影响目录结构）；
4.  编写完成后滚动到页面下方，按照本文中 [commit 信息格式规范](#commit) 填写 commit 信息，之后点击 **Propose changes** 按钮提交修改。点击按钮后，GitHub 会自动帮你创建一份 **xjtu-ai.github.io** 仓库的分支，并将你的提交添加到这个分支仓库。
5.  GitHub 会自动跳转到你的分支仓库的页面，此时页面上方会显示一个绿色的 **Create pull request** 按钮，点击后 GitHub 会跳转到一个创建 Pull Request 页面。向下滚动检查自己所作出的修改没有错误后，按照本文中 [Pull Request 信息格式规范](#pull-request_2) 一节中的规范书写 Pull Request 信息，然后点击页面上的绿色的 **Create pull request** 按钮创建 Pull Request。
6.  不出意外的话，你的 Pull Request 就顺利提交到仓库，等待管理员审核并合并到主仓库中即可。

在等待合并的时间里，你可以给他人的 Pull Request 提意见、点赞或者点踩。如果有新消息，会在网页右上角出现提示，并附有邮件提醒（取决于个人设置中配置的通知方式）。

#### 编辑多个页面内的内容

如果你需要同时编辑互相无关联的多个页面的内容，请按照上方的 [编辑单个页面内的内容](#_2) 一节一次修改所有页面。

1.  打开 [xjtu-ai/xjtu-ai.github.io](https://github.com/xjtu-ai/xjtu-ai.github.io) 仓库，点击键盘上的<kbd>.</kbd>按钮（或者将 URL 中的 `github.com` 更改为 `github.dev`），进入 GitHub 的网页版 VS Code 编辑器；
2.  在编辑器中作出对页面源文件的更改，可以使用页面右上方的预览按钮（或按下<kbd>Ctrl+K</kbd><kbd>V</kbd>快捷键）在右侧打开预览界面；
3.  修改完成后使用左侧的 Source Control 选项卡，并按照本文中 [commit 信息格式规范](#commit) 填写 commit 信息并提交，提交时会提示是否创建此仓库的分支，点击绿色的 **Fork Repository** 按钮即可。
4.  提交后会在网页上方的中央弹出一个提示框，在第一次的提示框内填写标题，第二次的提示框内填写此提交要提交到的仓库内分支名称，之后右下角会弹出一个提示框，内容类似于 `Created Pull Request #1 for xjtu-ai/xjtu-ai.github.io.`，点击蓝字链接即可查看该 Pull Request。

#### 向 Pull Request 追加更改

1.  打开 [xjtu-ai.github.io 的 Pull Request 列表](https://github.com/xjtu-ai/xjtu-ai.github.io/pulls)，找到您提交的 Pull Request 并点击。
2.  Pull Request 页面的标题下方将会有一段例如 `<您的ID> wants to merge x commits into xjtu-ai.github.io:master from <您的ID>:patch-1` 的文字，点击 `<您的ID>:patch-1` 部分。
3.  您应该会被重定向到您的分支仓库中，而且文件列表左上角的分支名称是你提交 Pull Request 的分支名称（在本示例中应为 `patch-1`）。
4.  进行您需要的更改。
    -   如果您需要编辑单个文件或多个互相无关联的页面的内容，请直接找到你要的文件并进行更改，更改完成后滚动到页面下方，按照本文中 [commit 信息格式规范](#commit) 填写 commit 信息，之后点击 **Commit changes** 按钮提交修改。
    -   如果您需要编辑多个文件，点击键盘上的<kbd>.</kbd>按钮（或者将 URL 中的 `github.com` 更改为 `github.dev`），进入 GitHub 的网页版 VS Code 编辑器并作出更改。然后使用左侧的 Source Control 选项卡，并按照本文中 [commit 信息格式规范](#commit) 填写 commit 信息并提交修改。
5.  这时你的更改会被自动追加在您的 Pull Request 中。

### 使用 Git 在本地进行编辑

可以参考 **[本地部署](./compile.md)**

???+ warning
    为了降低主储存库大小，PDF 文件作为子模块存储在 **[xjtu-ai/static](https://github.com/xjtu-ai/static)**。这样，普通的编辑无需拉取大量 pdf 文件。
    
    若要提交新的 pdf,请移步 **[xjtu-ai/static](https://github.com/xjtu-ai/static)** 使用 upload files。请勿在本地大量更改 static 子模块！这将使得储存库大小膨胀。

虽然大多数情况下您可以直接在 GitHub 上进行编辑，但对于一些较为特殊的情况（如需要使用 GPG 签名），我们更推荐使用 Git 在本地进行编辑。

大致流程如下：

1.  将主仓库 Fork 到自己的仓库中；
2.  将 Fork 后的分支仓库克隆（clone）到本地；
3.  在本地进行修改后提交（commit）这些更改；
4.  将这些更改推送（push）到你克隆的分支仓库；
5.  提交 Pull Request 至主仓库。

#### 向 Pull Request 追加更改

在 clone 下来的本地分支仓库中继续进行修改，并提交（commit）以及推送（push）这些更改即可。你的更改会被自动追加在 Pull Request 中。

### 对于目录和引用的变更

通常情况下，如果您需要添加一个新页面，或者修改已有页面在目录中的链接，您就需要对 [`mkdocs.yml`](https://github.com/xjtu-ai/xjtu-ai.github.io/blob/master/mkdocs.yml) 文件作出改动。

添加新页面可以参考既有的格式。但除非是进行重构或修正名词，否则 **我们不建议对既有页面的引用链接进行修改**。

### Commit 信息格式规范

对于提交时需要填写的 commit 信息，请遵守以下几点基本要求：

1.  commit 摘要请简要描述这一次 commit 改动的内容。注意 commit 摘要的长度不要超过 50 字符，超出的部分会自动置于正文中。
2.  如果需要进一步描述本次 commit 内容，请在正文中详细说明。

对于 commit 摘要，推荐按照如下格式书写：

```text
<修改类型>(<文件名>): <修改的内容>
```

修改类型分为如下几类：

-   `feat`：用于添加内容的情况。
-   `fix`：用于修正现有内容错误的情况。
-   `refactor`：用于对一个页面进行重构（较大规模的更改）的情况。
-   `revert`：用于回退之前更改的情况。

### Pull Request 信息格式规范

对于 Pull Request，请遵守以下几点要求：

1.  标题请写明本次 PR 的目的（做了 **什么** 工作，修复了 **什么** 问题）。
2.  内容请简要叙述修改的内容。如果修复了一个 issue 的问题，请在内容中添加 `fix #xxxx` 字段，其中 `xxxx` 代表 issue 的编号。

对于 Pull Request 的标题，推荐使用如下格式书写：

```plain
<修改类型>(<文件名>): <修改的内容> (<对应 issue 的编号>)
```

修改类型分为如下几类：

-   `feat`：用于添加内容的情况。
-   `fix`：用于修正现有内容错误的情况。
-   `refactor`：用于对一个页面进行重构（较大规模的更改）的情况。
-   `revert`：用于回退之前更改的情况。
