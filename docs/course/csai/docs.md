## [AI学组]CSAI矩阵论与回归分析复习资料2025

文件系统梳理了矩阵论与回归分析的核心内容：  
1. 主成分分析（PCA）给出协方差矩阵、相关矩阵、R/S 型分析步骤及 4×3 数据实例。  
2. 奇异值分解（SVD）介绍两种计算流程，并配 2 道手写例题。  
3. 函数矩阵求导、梯度与 Jacobian 定义常用公式及证明。  
4. 伪逆、广义逆、Moore-Penrose 逆的判定、计算与例题。  
5. 多元线性回归建模、最小二乘解、帽子矩阵与二次拟合示例。

??? note "[AI学组]CSAI矩阵论与回归分析复习资料2025"
    <iframe loading="lazy" src="/static/course/csai/[AI学组]CSAI矩阵论与回归分析复习资料2025.pdf" type="application/pdf" width=100% height=1000px></iframe>

## CSAI 复习 (1)

**CSAI 复习摘要**

- **数理逻辑**：命题判定、真值表、范式、推理证明、谓词符号化。  
- **集合论**：对称差、幂集、势的证明（双射/伯恩斯坦）、可数性技巧。  
- **组合分析**：整系数二次方程根的可数性、$\aleph_0$ 幂集、$\{0,1\}^*$ 与 $\{0,1\}^\omega$ 可数性。  
- **图论**：  
  – 欧拉图：无奇度顶点 $\Leftrightarrow$ 欧拉回路。  
  – 哈密顿图：$p(G-V)\le|V|$；度和大条件。  
  – 平面图：欧拉公式 $n-m+r=2$，极大平面 $\Leftrightarrow$ 每面 3 次。  
  – 着色：$\delta\ge4$ 则必有 $\le4$ 次面；$n\ge11$ 补图非平面。  
- **代数系统**：群/环/域定义与证明模板；幂等元即单位元。  
- **三维刚体**：$SO(3)$ 表征（欧拉角、四元数、旋转向量）、罗德里格斯公式  
  $R=\cos\theta I+(1-\cos\theta)aa^\top+\sin\theta[a]_\times$
  及指数映射 $\exp(\theta a^\wedge)$。

??? note "CSAI 复习 (1)"
    <iframe loading="lazy" src="/static/course/csai/CSAI 复习 (1).pdf" type="application/pdf" width=100% height=1000px></iframe>

## CSAI讲座讲义

以下按讲义中出现的顺序，逐条给出最简答案（仅结论或一句话提示）

（**这里的解析是 AI 识别并生成的，未经人工审核**）。
### 集合论
1. $A\cap(B\setminus C)=(C\setminus B)\cap A$  
   **不成立**；反例：$A=\{1\},B=\{1,2\},C=\{2\}$ 左侧$\{1\}$，右侧$\varnothing$。

2. $A\cap(B\cap C)=B\cap(A\cap C)$  
   **成立**；两边均等于$A\cap B\cap C$（交换律）。

3. 可数/不可数  
   $\{0,1\}^*$可枚举（按长度字典序），$\{0,1\}^\omega$与$\mathbb R$等势，对角化证不可数。

---

### 图论
1. $K_{m,n}$哈密顿$\iff m=n\ge 2$。  
   证：二部图回路必偶长，需两边顶点数相等；构造显式圈。

2. $K_{m,n}$半哈密顿$\iff m\ge n-1\ge 0$且$m+n\ge2$。  
   证：删一顶点后可哈密顿。

3. 6边极大平面$\iff$三角剖分$\Rightarrow$必$K_4$（4点6边）。  
   结论：**是**。

4. 8点极大平面$\Rightarrow e=3n-6=18\Rightarrow f=e+2-n=12$。

5. 4-色：平面图的色数$\le4$（四色定理）。

6. $r<12,\delta(G)\ge3\Rightarrow$平均面度$<4\Rightarrow$存在$\le4$次面。

7. $n=10,m=37$  
   - 哈密顿？**不一定**；$K_{5,5}+7$边可非哈密顿。  
   - 二分？**不一定**；$K_{10}-8$边含奇圈。  
   - 平面？**否**；$m>3n-6=24$。

8. 所有度偶且连通$\Rightarrow$欧拉图；**是**。

9. $n\ge11$平面$\Rightarrow\overline G$含$K_5$或$K_{3,3}$子式$\Rightarrow$非平面。

---

### 代数系统
1. $\langle S,*\rangle$群：封闭、结合、单位$1$、逆元显见。

2. 交换$\iff(ab)^2=a^2b^2$  
   $\Rightarrow$显然；$\Leftarrow$展开得$ab=ba$。

3. 域$\mathbb F$：验证加法、乘法群及分配律（题目片段，略）。

??? note "CSAI讲座讲义"
    <iframe loading="lazy" src="/static/course/csai/CSAI讲座讲义.pdf" type="application/pdf" width=100% height=1000px></iframe>

## 计算机科学与人工智能的数学基础上复习大纲

涵盖 **命题逻辑、谓词逻辑、集合论、图论、代数系统、线性代数与三维几何、组合计数、回归与降维** 八大模块。

- **逻辑**：命题公式、真值表、范式、推理定律；谓词、量词、前束范式。  
- **集合**：运算律、幂集、包含排斥、映射与势、可数/连续统。  
- **图论**：度与握手定理、连通性、欧拉图、哈密顿图、平面图、树、匹配、割集。  
- **代数系统**：群、子群、陪集、同构；变换群与置换群。  
- **线性代数**：SVD、Moore-Penrose 逆、PCA 四步：  
  1. 均值 $\bar x$ 与协方差 $S$；  
  2. 解 $|λI-S|=0$ 得特征值；  
  3. 单位特征向量 $α_k$；  
  4. 主成分 $f_i=α_{1i}(x_1-\bar x_1)+\dots+α_{pi}(x_p-\bar x_p)$。  
- **三维几何**：旋转向量 $\phi=θn$、Rodrigues 公式  
  $R=\cosθI+(1-\cosθ)nn^T+\sinθ[n]_×$；  
  单位四元数 $q=(\cos\fracθ2,\sin\fracθ2 n)$ 表示旋转。  
- **组合计数**：排列 $P(n,r)=\frac{n!}{(n-r)!}$、组合 $C(n,r)=\frac{n!}{r!(n-r)!}$、多重集重复选取 $C_{k+r-1}^{r}$。  
- **回归**：最小二乘 $\hatβ=(X^TX)^{-1}X^Ty$，帽子矩阵 $H=X(X^TX)^{-1}X^T$。

??? note "计算机科学与人工智能的数学基础上复习大纲"
    <iframe loading="lazy" src="/static/course/csai/计算机科学与人工智能的数学基础上复习大纲.pdf" type="application/pdf" width=100% height=1000px></iframe>

## PPT

??? note "计算机科学与人工智能的数学基础I(2023-2024学年第二学期)"
    <iframe loading="lazy" src="/static/course/csai/计算机科学与人工智能的数学基础I(2023-2024学年第二学期).pdf" type="application/pdf" width=100% height=1000px></iframe>