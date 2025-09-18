## 2025春CSAI回忆版试题（这是人智真题）

**题解由 AI 提供**

---

### 一、填空（每题 3 分，第 6 题 5 分）

1. 可满足式的否定不可能是 **重言式**。  
2. 主析取范式：  
   $m_3\vee m_6\vee m_7 = (\neg p\wedge q\wedge r)\vee(p\wedge q\wedge\neg r)\vee(p\wedge q\wedge r)$  
3. $P(\{0,\varnothing\})\oplus P(\varnothing)=\bigl\{\{0\},\{\varnothing\},\{0,\varnothing\}\bigr\}$  
4. 邻接矩阵 $A^3$ 的 $(2,1)$ 元素即为 $v_2\to v_1$ 长 3 的路径数。  
5. 极小非平面图删一边后 **不一定是** 极大平面图。  
6. 真值判断  
   (1) 无向图均可四着色 → **真**（四色定理）  
   (2) 子群单位元必为 $e$ → **真**  
   (3) 帽子矩阵对称 → **假**（对称而非反对称）

---

### 二、举例（每题 3 分）

1. 图 2 中基数 4 的边割集：任取把图分成两部分的 4 条跨集边即可。  
2. 欧拉图但非哈密顿图：$K_{2,4}$ 的“双星”加平行边使其度全偶。  
3. 弱连通但非单向连通：$1\to 2,\;3\to 2$（底层无向连通，但无 $1\to 3$ 路径）。  
4. 完备但非完美匹配：$K_{3,5}$ 中把 3 部全匹配掉，剩 2 个未盖点。

---

### 三、计算与证明

1. $((p\to q)\wedge p)\to q$ 是 **重言式**。  
2. 谓词符号化：  
   $\forall x\forall y\,\bigl(\text{Angle}(x)\wedge\text{Angle}(y)\wedge x=y\;\to\;\neg(\text{Vertical}(x)\wedge\text{Vertical}(y))\bigr)$  
3. 前束范式：  
   $\forall x\exists z\exists u\,\bigl(F(z,y)\to(H(x)\to\neg G(u))\bigr)$  
4. 会三门语言人数 = **2**。  
5. $n$ 必为 **偶数**（3-正则图握手定理）。  
6. 双射：  
   $f(x)=\dfrac{5x-2}{1-|2x-1|},\;x\in[0,1]$ 把 $[0,1]$ 映到 $(-2,3)$。  
7. 取解释 $D=\mathbb N,\;F(x):x=0,\;G(x):x=1$ 即可使两式为假。  
8. 四元数乘积：  
   $q_1*q_2=(-4,\,2,\,0,\,1)$  
9. 阶数 $n=8$；非同构树共 **2 棵**。  
10. 对偶图：把原图每个面变顶点，相邻面连边即可。  
11. 梯度：  
    $\nabla f(x)=(A+A^T)x$  
12. SVD：  
    $A=\begin{bmatrix}1\\2\\0\end{bmatrix}\begin{bmatrix}1&0\end{bmatrix}$ 已给出；  
    MP 逆：  
    $A^+=\dfrac{1}{5}\begin{bmatrix}1&2&0\end{bmatrix}$

---

### 四、应用题（真值表法）

设甲、乙、丙、丁命题变量，列 16 行真值表，保留满足 4 条约束的行，唯一解：  
**派甲、丙** 参赛。

---

### 五、分析题

1. 把协方差阵的 $1/n$ 换成 $1/(n-1)$ 只改变特征值大小，不改变 **特征向量方向** 与 **相对贡献率**，故主成分表达式不变，贡献率数值不变。  
2. Cantor 集 5 等分后每份与原集同胚，势仍为  
   $\mathfrak c=2$

??? note "2025春CSAI回忆版试题"
    <iframe loading="lazy" src="/static/course/csai/2025春CSAI回忆版试题.pdf" type="application/pdf" width=100% height=1000px></iframe>

## 2020离散期末

??? note "2020离散期末"
    <iframe loading="lazy" src="/static/course/csai/2020离散期末.pdf" type="application/pdf" width=100% height=1000px></iframe>

## 2023-2024 离散期末

??? note "2023-2024 离散期末"
    <iframe loading="lazy" src="/static/course/csai/2023-2024 离散期末.pdf" type="application/pdf" width=100% height=1000px></iframe>
