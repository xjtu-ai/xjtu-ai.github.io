from pathlib import Path
from openai import OpenAI
import sys
import os

key = os.getenv('MOONSHOT_AI_KEY') # 或者填入 API key
outdir = '/static/course/prob/'
if outdir == "" :
    outdir = '/'
path = Path(sys.argv[1])
basename = path.stem
filename = path.name

print("## %s\n" % basename)

if key:
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
        {"role": "user", "content": "请生成上传文件的摘要。字数不要超过 300 字。使用 Markdown 语法标记输出。使用 Latex 语法输出数学公式"},
    ]

    try :
        completion = client.chat.completions.create(
            model="kimi-k2-0905-preview",
            messages=messages,
            temperature=0.3,
        )
        print(completion.choices[0].message.content)
        print("")

    except :
        print("调用 API 失败")

    client.files.delete(file_id=file_object.id)

print("??? note \"%s\"\n    <iframe loading=\"lazy\" src=\"%s%s\" type=\"application/pdf\" width=100%% height=1000px></iframe>\n" % (basename, outdir, filename))