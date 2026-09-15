# 电子技术与系统 复习资料

本页面收集《电子技术与系统》的复习资料。该课程俗称「三合一」，由模拟电子技术、数字电路逻辑系统设计与计算机体系结构 I 三部分组成。

《电子技术与系统》的复习资料有对应的 Markdown 版本，见「数电复习资料」「数字逻辑与 Verilog HDL」「SystemVerilog 复习报告」页面。

## 模拟电子技术-速通资料

针对模拟电子技术部分的速通复习资料。前言说明了资料定位与食用指南：时间充足时配合全套 PPT，时间紧张时优先使用本资料与老师的知识总结 PPT。正文以问答形式覆盖半导体器件（二极管、晶体管、场效应管、集成运放）与半导体应用（信号运算、信号调理、信号生成、电源）中的定量计算与电路分析要点，并整理了大量选择填空考点。

??? note "模拟电子技术-速通资料"
    <iframe loading="lazy" src="/static/course/electronics/docs/模拟电子电路-速通资料.pdf" type="application/pdf" width=100% height=1000px></iframe>

## 模电知识点总结（赵文哲老师）

课程老师提供的模拟电子技术知识点总结，以知识框架图串联「半导体器件」（二极管、晶体管、场效应管、集成运放）与「半导体应用」（信号运算、信号调理、信号生成、电源）两大板块，是考前梳理模电知识体系的首选材料。

??? note "模电知识点总结（赵文哲老师）"
    <iframe loading="lazy" src="/static/course/electronics/docs/电子技术与系统-模拟电子技术-模电知识点总结.pdf" type="application/pdf" width=100% height=1000px></iframe>

## 体系结构

计算机体系结构 I 部分的考点整理，涵盖体系结构设计的四条准则、ARM 常见指令（数据处理、存储器访问、分支等）、寄存器特殊用途、条件执行、函数调用与寻址模式等内容，适合对照 Harris 教材复习 ARM 指令集。

??? note "体系结构"
    <iframe loading="lazy" src="/static/course/electronics/docs/体系结构.pdf" type="application/pdf" width=100% height=1000px></iframe>

## 微架构

计算机体系结构 I 部分微架构章节的复习笔记，梳理单周期数据通路、CPI 与时钟周期的计算、多周期与流水线（IF/ID/EX/MEM/WB 五级）数据通路、数据冒险与前递（Forwarding）、Load-Use 冒险与插入气泡、控制冒险与流水线冲刷，以及 ARM 条件执行等考点。

??? note "微架构"
    <iframe loading="lazy" src="/static/course/electronics/docs/微架构.pdf" type="application/pdf" width=100% height=1000px></iframe>

## 存储器系统

计算机体系结构 I 部分存储器系统的复习笔记，围绕局部性原理、AMAT 计算、Cache 的三种映射方式（直接映射、组相联、全相联）、地址划分（Tag/Set Index/Block Offset）、3C 缺失模型（强制、容量、冲突）、替换与写策略（LRU/随机、写直达/写回）、虚拟内存地址翻译与 TLB 等考点整理。

??? note "存储器系统"
    <iframe loading="lazy" src="/static/course/electronics/docs/存储器系统.pdf" type="application/pdf" width=100% height=1000px></iframe>
