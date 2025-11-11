## 概率论复习课速览
- **高频痛点**：参数估计(80%)、假设检验(93%)  
- **核心分布**：$\chi^2(n),\ t(n),\ F(n,m)$ 及其构造关系  
- **正态总体三宝**：  
  - $\bar X$ 与 $S^2$ 独立  
  - $\displaystyle \frac{(n-1)S^2}{\sigma^2}\sim\chi^2(n-1)$  
  - $\displaystyle \frac{\bar X-\mu}{S/\sqrt n}\sim t(n-1)$  
- **区间估计速查**（置信度 $1-\alpha$）：  
  - 均值：$\bar x\pm t_{\alpha/2}(n-1)\dfrac{s}{\sqrt n}$  
  - 方差：$\displaystyle \Bigl(\frac{(n-1)s^2}{\chi^2_{\alpha/2}},\ \frac{(n-1)s^2}{\chi^2_{1-\alpha/2}}\Bigr)$  
- **假设检验口诀**：  
  “均值用 $t$，方差用 $\chi^2$，双总体方差比 $F$ 走起”  
- **随机过程两问**：  
  1. 泊松过程间隔 $\sim\mathrm{Exp}(\lambda)$  
  2. 宽平稳 $\Leftrightarrow$ 均值为常数且 $R_X(\tau)$ 仅依赖时差

??? note "概率论PPT"
    <iframe loading="lazy" src="/static/course/prob/概率论PPT.pdf" type="application/pdf" width=100% height=1000px></iframe>  

~~下面是ShwStone厚颜无耻的宣传自己编写的内容的地方~~

## [假设检验](https://shwstone.cn/2025/05/14/%E5%81%87%E8%AE%BE%E6%A3%80%E9%AA%8C%E6%98%AF%E6%8B%92%E7%BB%9D%E7%9A%84%E8%89%BA%E6%9C%AF/)

本文梳理经典假设检验的核心逻辑：  
1. 以**拒绝域** $R$ 控制第一类错误概率 $P(X\in R\mid H_0)\le\alpha$，对第二类错误不设限。  
2. 检验结论只有“拒绝 $H_0$”或“未能拒绝 $H_0$”，不存在“接受”；拒绝即支持备择假设 $H_1$。  
3. 点值假设 $H_0:\theta=\theta_0$ 只能作原假设，因备择无界难以控制尺寸。  
4. 单侧假设 $H_0:\theta\le\theta_0$ vs $H_1:\theta\ge\theta_0$ 不会同时拒绝；若两单侧均未能拒绝，仅说明样本不足。  
5. 贝叶斯视角视 $P(H_0)$ 为先验，可算后验 $P(H_0\mid X)$，但先验需人为设定。

??? note "假设检验 (Markor)"
    <iframe loading="lazy" src="/static/course/prob/假设检验 (Markor).pdf" type="application/pdf" width=100% height=1000px></iframe>

## [正态分布统计量的一些问题](https://shwstone.cn/2025/04/27/%E6%AD%A3%E6%80%81%E5%88%86%E5%B8%83%E7%9A%84%E4%B8%A4%E4%B8%AA%E7%BB%9F%E8%AE%A1%E9%87%8F)

本文用**线性代数视角**重新梳理正态样本的两大核心统计量  

$$
\bar{X}=\frac{1}{n}\sum_{i=1}^n X_i,\quad S^2=\frac{1}{n-1}\sum_{i=1}^n(X_i-\bar{X})^2
$$

的分布与独立性。  

1. 把样本写成**中心化多元正态**

$$
\mathbf{Z}=(Z_1,\dots,Z_n)^{\mathsf T},\quad Z_i=\frac{X_i-\mu}{\sigma}\sim N(0,1),
$$

其协方差阵为**单位阵**\(I_n\)。  

1. 证明\(\bar{X}\)与\(S^2\)独立：  
   - \(\bar{X}\)仅依赖**全1方向**\(u=(1,\dots,1)^{\mathsf T}\)；  
   - \(S^2\)可写成**正交补空间**上的二次型  
  
    $$
    \frac{(n-1)S^2}{\sigma^2}=\mathbf{Z}^{\mathsf T}(I_n-\tfrac{1}{n}uu^{\mathsf T})\mathbf{Z}.
    $$

   因投影矩阵\(I_n-\tfrac{1}{n}uu^{\mathsf T}\)的零空间恰为\(u\)，故两统计量**正交投影互补**，在多元正态下即**独立**。  

2. 分布结果：  

$$
\frac{(n-1)S^2}{\sigma^2}\sim\chi^2(n-1),\quad
\frac{\bar{X}-\mu}{S/\sqrt{n}}\sim t(n-1).
$$


全文以**特征值分解**与**二次型几何**为核心，澄清了“为何分子分母独立”这一常见疑惑，并顺带揭示**主成分分析**与正态等高椭圆的内在联系。

??? note "正态分布统计量的一些问题 (Markor)"
    <iframe loading="lazy" src="/static/course/prob/正态分布统计量的一些问题 (Markor).pdf" type="application/pdf" width=100% height=1000px></iframe>

## 样本方差vs样本中心矩

对正态样本 $X_1,\dots,X_n$，最大似然估计（MLE）把均值与方差同时视为待估参数。  
- 均值 MLE：$\hat\mu_{\text{MLE}}=\bar X$，即样本一阶原点矩。  
- 方差 MLE：$\hat\sigma^2_{\text{MLE}}=\frac1n\sum_{i=1}^n(X_i-\bar X)^2$，即样本二阶中心矩。  

MLE 通过最大化似然函数 $L(\mu,\sigma^2)$ 得到，不保证无偏，但具有一致性与渐近有效性。  
无偏方差估计 $\hat\sigma^2_{\text{unbiased}}=\frac1{n-1}\sum_{i=1}^n(X_i-\bar X)^2$ 虽消除偏差，却非 MLE。  

选择依据：  
- 小样本或强调无偏 → 用 $n-1$ 修正；  
- 大样本、关注效率与计算简便 → 保留 MLE（样本中心矩）。

??? note "样本方差vs样本中心矩 (Markor)"
    <iframe loading="lazy" src="/static/course/prob/样本方差vs样本中心矩 (Markor).pdf" type="application/pdf" width=100% height=1000px></iframe>
