你可以按照如下方式在本地部署并预览这个项目。

## 克隆仓库

```bash
git clone https://github.com/xjtu-ai/xjtu-ai.github.io.git --depth=1 
cd xjtu-ai.github.io 
```

## 安装依赖

```bash
pip install mkdocs-material mkdocs-material-extensions mkdocs-material-pymdownx-extras
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
