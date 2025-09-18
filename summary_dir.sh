#!/bin/bash

# 指定要遍历的目录
DIRECTORY=$1

# 检查目录是否存在
if [ ! -d "$DIRECTORY" ]; then
  echo "错误: 目录 '$DIRECTORY' 不存在。"
  exit 1
fi

cd . > a.out

# 遍历目录下的所有 .pdf 文件
for pdf_file in "$DIRECTORY"/*.pdf; do
  # 检查是否找到了文件，以防目录为空
  [ -e "$pdf_file" ] || continue

  # 在这里执行你的特定脚本，"$pdf_file" 是当前 PDF 文件的完整路径
  echo "正在处理文件: $pdf_file"
  /home/shwstone/.conda/envs/xjtu-ai/bin/python summary.py "$pdf_file" >> a.out

  # --- 或者直接在这里写命令 ---
  # 例如，使用 pdftotext 将 pdf 转为文本
  # pdftotext "$pdf_file" "${pdf_file%.pdf}.txt"
done

echo "所有 PDF 文件处理完毕。"