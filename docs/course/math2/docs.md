## 【AI学组&钱学组】高数下期中专题复习

**《工科数学分析（二）》期中专题复习摘要**

- **多元函数微分学**  
  连续与可微判定、方向导数、泰勒展开

$$
f(x)=f(x_0)+\langle\nabla f(x_0),\Delta x\rangle+\tfrac12\Delta x^{\mathsf T}H_f(x_0+\theta\Delta x)\Delta x
$$

  极值：无约束用 Hesse 矩阵正定/负定；有约束用 Lagrange 乘子  
  
$$
\nabla f(x_0)=\lambda\nabla\varphi(x_0),\quad \varphi(x_0)=0
$$


- **几何应用**  
  曲线切向量 $\dot r(t)$，曲面法向量 $r_u\times r_v$；弧长、曲率公式  
  
$$
\kappa(t)=\dfrac{|\dot r\times\ddot r|}{|\dot r|^3}
$$


- **重积分**  
  二重：X/Y 型、极坐标、对称奇偶、换序、变量替换  
  
$$
\iint_D f(x,y)\,\mathrm d\sigma=\iint_{D'}f(x(u,v),y(u,v))|J|\,\mathrm du\mathrm dv
$$

  三重：柱/球坐标、椭球变换、轮换对称  
  
$$
\iiint_\Omega\mathrm dV=\int_0^{2\pi}\!\!\int_0^\pi\!\!\int_0^R \rho^2\sin\varphi\,\mathrm d\rho\mathrm d\varphi\mathrm d\theta
$$

- **典型技巧**  
  极坐标求极限、Jacobi 链式法则、隐函数组求导、Lagrange 证不等式、对称性化简积分。

??? note "【AI学组&钱学组】高数下期中专题复习"
    <iframe loading="lazy" src="/static/course/math2/docs/【AI学组&钱学组】高数下期中专题复习.pdf" type="application/pdf" width=100% height=1000px></iframe>

## 工科数学分析-期中

### 摘要

文件为《工科数学分析-2期中复习》讲义，涵盖多元微积分核心内容：

1. **极限与连续性**  
   - $\mathbb{R}^n\to\mathbb{R}$ 与 $\mathbb{R}^n\to\mathbb{R}^m$ 连续定义：任意路径极限相同，分量函数皆连续。  
   - 反例警示：直线路径不足以判定极限存在。

2. **可微性**  
   - 全微分：$\Delta f=\nabla f\cdot\delta x+o(\|\delta x\|)$。  
   - 充分条件：偏导数连续；必要条件：函数连续、偏导存在。  
   - 方向导数与梯度：$\partial_{\mathbf{e}}f=\nabla f\cdot\mathbf{e}$。

3. **高阶导数与 Taylor 展开**  
   - Hessian 矩阵 $H_f$；二阶 Taylor：  
     
$$
f(\mathbf{x})=f(0)+\nabla f(0)\cdot\mathbf{x}+\tfrac12\mathbf{x}^TH_f(0)\mathbf{x}+o(\|\mathbf{x}\|^2).
$$

4. **极值与 Lagrange 乘子**  
   - 必要条件：$\nabla f=0$；Hessian 正定⇒极小，负定⇒极大，不定⇒鞍点。  
   - 约束极值：$\mathcal{L}=f+\sum\lambda_i g_i$，$\nabla\mathcal{L}=0$。

5. **链式法则与变量替换**  
   - Jacobi 矩阵 $Df=J_{m\times n}$；链式：$D(f\circ g)=Df|_g\cdot Dg$。  
   - 全微分形式不变性：$\mathrm{d}f=\partial_u f\,\mathrm{d}u+\partial_v f\,\mathrm{d}v$。

6. **重积分**  
   - 换元公式：$\mathrm{d}x\mathrm{d}y=|\det J|\mathrm{d}u\mathrm{d}v$；柱坐标 $\rho\,\mathrm{d}\rho\mathrm{d}\theta\mathrm{d}z$，球坐标 $r^2\sin\varphi\,\mathrm{d}r\mathrm{d}\varphi\mathrm{d}\theta$。  
   - 对称性：利用 $f(x,y)\pm f(\pm x,\pm y)=0$ 或轮换对称化简。

7. **空间几何**  
   - 曲线切向量 $\dot{\mathbf{r}}$，弧微分 $\mathrm{d}s=\|\dot{\mathbf{r}}\|\mathrm{d}t$。  
   - 曲面法向量：$\mathbf{n}=\partial_u\mathbf{r}\times\partial_v\mathbf{r}$ 或 $\nabla F$；交线切向量 $\mathbf{t}=\mathbf{n}_1\times\mathbf{n}_2$。

8. **技巧与例题**  
   - 构造一元函数 $\varphi(t)=f\bigl(A(1-t)+Bt\bigr)$ 证明 $|f(A)-f(B)|\le M|AB|$。  
   - 分离变量解 Laplace 算子极坐标形式：$\nabla^2 f=\frac{\mathrm{d}^2f}{\mathrm{d}\rho^2}+\frac1\rho\frac{\mathrm{d}f}{\mathrm{d}\rho}$。

祝考试顺利。

??? note "工科数学分析-期中"
    <iframe loading="lazy" src="/static/course/math2/docs/工科数学分析-期中.pdf" type="application/pdf" width=100% height=1000px></iframe>

## 高数下知识点&&习题归纳

### 高数下知识点与习题归纳摘要

- **多元函数微分学**：  
  - 极限、连续、偏导、全微分、方向导数与梯度  
  - Taylor 展开、极值（无约束 & Lagrange 乘数法）  
  - 向量值函数、隐函数、几何应用（切线、法平面、弧长、切平面）

- **多元函数积分学**：  
  - 二重、三重积分（直角、极、柱、球坐标）  
  - 一型线/面积分（质量）、二型线/面积分（功、流量）  
  - Green、Stokes、Gauss 公式；散度、旋度、有势/无源/调和场

- **无穷级数**：  
  - 常数项级数审敛（比较、比值、根值、Leibniz）  
  - 幂级数：收敛半径 $R=\lim|\frac{a_n}{a_{n+1}}|$，和函数与展开  
  - Fourier 级数：系数  
  
$$
a_n=\frac1l\int_{-l}^{l}f(x)\cos\frac{n\pi x}{l}\,\mathrm{d}x,\quad
b_n=\frac1l\int_{-l}^{l}f(x)\sin\frac{n\pi x}{l}\,\mathrm{d}x
$$

- **习题精选**：  
  每章配典型题与完整解答，强化计算技巧与定理应用。

??? note "高数下知识点&&习题归纳"
    <iframe loading="lazy" src="/static/course/math2/docs/高数下知识点&&习题归纳.pdf" type="application/pdf" width=100% height=1000px></iframe>

