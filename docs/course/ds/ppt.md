此页面收集了数据结构与算法课程的课件。请读者自行取用。

## 作业 X

??? note "作业 X"
    <iframe loading="lazy" src="/static/course/ds/ppt/Homework_X.pdf" type="application/pdf" width=100% height=1000px></iframe>

## 作业 Y

??? note "作业 Y"
    <iframe loading="lazy" src="/static/course/ds/ppt/Homework_Y.pdf" type="application/pdf" width=100% height=1000px></iframe>

## L01-环路检测（Find and Union）

本讲介绍并查集（Disjoint Set Union / Find and Union）数据结构及其在图论中的应用。内容包括并查集的基本操作（查找与合并）、路径压缩与按秩合并的优化策略，以及使用并查集检测图中环路（Cycle Detection）的算法设计与复杂度分析。

??? note "L01-环路检测（Find and Union）"
    <iframe loading="lazy" src="/static/course/ds/ppt/L01-环路检测（Find and Union）-20260205.pdf" type="application/pdf" width=100% height=1000px></iframe>

## L02-约瑟夫环（链表数组-递归调用）

本讲以约瑟夫环（Josephus Problem）为切入点，讲解链表与数组的灵活运用及递归思想。内容包括约瑟夫环问题的数学建模、基于循环链表的模拟解法、基于数组的递推解法，以及递归公式的推导与分析。

??? note "L02-约瑟夫环（链表数组-递归调用）"
    <iframe loading="lazy" src="/static/course/ds/ppt/L02-约瑟夫环（链表数组-递归调用）-20260205.pdf" type="application/pdf" width=100% height=1000px></iframe>

## L03-两数之和（哈希-时空复杂度分析-排序）

本讲以经典的 Two Sum 问题为例，系统讲解哈希表（Hash Table）的应用及其时空复杂度分析方法。内容包括暴力枚举、排序 + 双指针、哈希表一次遍历三种解法的对比，引出时空复杂度权衡（Time-Space Trade-off）的核心思想。

??? note "L03-两数之和（哈希-时空复杂度分析-排序）A"
    <iframe loading="lazy" src="/static/course/ds/ppt/L03-两数之和（哈希-时空复杂度分析-排序）-20260205.pdf" type="application/pdf" width=100% height=1000px></iframe>

??? note "L03-两数之和（哈希-时空复杂度分析-排序）B"
    <iframe loading="lazy" src="/static/course/ds/ppt/L03-两数之和（哈希-时空复杂度分析-排序）-20260205(1).pdf" type="application/pdf" width=100% height=1000px></iframe>

## L04-表达式求值（栈的综合应用，数学归纳）

本讲讲解表达式求值（Expression Evaluation）算法及其背后的数据结构——栈（Stack）。内容包括中缀表达式与后缀表达式（逆波兰表示法）的相互转换、基于栈的表达式求值算法、数学归纳法在算法正确性证明中的应用，以及括号匹配等栈的经典应用场景。

??? note "L04-表达式求值"
    <iframe loading="lazy" src="/static/course/ds/ppt/L04-表达式求值（栈的综合应用，数学归纳）-20260205.pdf" type="application/pdf" width=100% height=1000px></iframe>

## L05-最大子数组和（动态规划入门-分治入门）

本讲以最大子数组和（Maximum Subarray Sum）问题为主线，引入动态规划（Dynamic Programming）与分治算法（Divide and Conquer）两种核心算法范式。内容包括 Kadane 算法的设计思想与正确性证明、分治策略的递归分解与合并过程，以及两种方法在时间复杂度上的对比分析。

??? note "L05-最大子数组和（正课）"
    <iframe loading="lazy" src="/static/course/ds/ppt/L05-最大子数组和（动态规划入门-分治入门）-20260301.pdf" type="application/pdf" width=100% height=1000px></iframe>

??? note "L05-最大子数组和（Part 1）"
    <iframe loading="lazy" src="/static/course/ds/ppt/L05-part1-最大子数组和（动态规划入门-分治入门）-20260301.pdf" type="application/pdf" width=100% height=1000px></iframe>

## L06-公共祖先（树的基础知识-BST-AVL）

本讲围绕树（Tree）数据结构展开，以最近公共祖先（Lowest Common Ancestor, LCA）问题为引子。内容包括树的基本概念与术语、二叉树与二叉查找树（BST）的定义与操作、平衡二叉树（AVL 树）的旋转调整策略，以及 LCA 问题的多种求解算法。

??? note "L06-公共祖先（树的基础知识-BST-AVL）"
    <iframe loading="lazy" src="/static/course/ds/ppt/L06-公共祖先（树的基础知识-BST-AVL）-20260312.pdf" type="application/pdf" width=100% height=1000px></iframe>

## L07-树的扩展（B树-B+树-23树-红黑树）

本讲深入介绍树结构的扩展与变体，服务于大规模数据存储与索引场景。内容包括 2-3 树的定义与操作、B 树与 B+ 树的结构特性与磁盘 I/O 优化、红黑树（Red-Black Tree）的平衡性质与插入/删除修正，以及各种平衡树在实际系统（数据库索引、文件系统）中的应用对比。

??? note "L07-树的扩展（B树-B+树-23树-红黑树）"
    <iframe loading="lazy" src="/static/course/ds/ppt/L07-树的扩展（B树-B+树-23树-红黑树）-20260312.pdf" type="application/pdf" width=100% height=1000px></iframe>

## L08-农羊狼菜（搜索与回溯）

本讲以经典过河问题「农夫、狼、羊、白菜」为线索，讲解搜索算法（Search）与回溯法（Backtracking）的核心思想。内容包括状态空间建模、DFS/BFS 搜索策略、约束满足与剪枝优化，以及回溯法在组合搜索与 NP 问题中的应用。

??? note "L08-农羊狼菜（搜索与回溯）"
    <iframe loading="lazy" src="/static/course/ds/ppt/L08-农羊狼菜 (Search and Backtracking）-20260312.pdf" type="application/pdf" width=100% height=1000px></iframe>

## L09-优化问题（贪心与分支限界）

本讲聚焦于优化问题的两种经典求解策略——贪心算法（Greedy）与分支限界法（Branch and Bound）。内容包括贪心选择性质与最优子结构的判定、活动选择/背包等经典贪心问题、分支限界法的搜索树剪枝策略与界限函数设计，以及两种方法的适用场景对比。

??? note "L09-优化问题（贪心与分支限界）"
    <iframe loading="lazy" src="/static/course/ds/ppt/L09-优化问题（Greedy Branch and Bound) -20260421.pdf" type="application/pdf" width=100% height=1000px></iframe>

## L10-六度空间（图论基础）

本讲以「六度空间」理论为切入点，介绍图论（Graph）的基础知识。内容包括图的基本定义与术语、图的存储结构（邻接矩阵与邻接表）、图的遍历算法（BFS 与 DFS）及其复杂度分析，以及利用 BFS 计算最短路径与社交网络中的小世界现象。

??? note "L10-六度空间（图论基础）"
    <iframe loading="lazy" src="/static/course/ds/ppt/L10-六度空间 (Basics of Graph)-20260429.pdf" type="application/pdf" width=100% height=1000px></iframe>

## L11-图的高级应用

本讲进一步探讨图论的高级应用。内容包括最短路径算法（Dijkstra、Floyd-Warshall）、最小生成树（Prim、Kruskal）、拓扑排序与关键路径，以及网络流初步（最大流与最小割）。各部分均结合实际工程场景讲解算法的设计动机与实现要点。

??? note "L11-图的高级应用"
    <iframe loading="lazy" src="/static/course/ds/ppt/L11-高级应用（Advances of Graph)-20260506.pdf" type="application/pdf" width=100% height=1000px></iframe>

## L12-NP问题（NP-NP-hard-NP-Complete）

本讲介绍计算复杂性理论的基础概念。内容包括 P、NP、NP-Complete 与 NP-hard 的定义与关系、多项式时间归约（Polynomial-time Reduction）、经典 NP 完全问题（SAT、旅行商问题、子集和问题等）的判定与证明，以及面对 NP 难问题的实用应对策略（近似算法、启发式搜索、参数化算法）。

??? note "L12-NP问题（NP-NP-hard-NP-Complete）"
    <iframe loading="lazy" src="/static/course/ds/ppt/L12-NP问题（NP-NP-hard-NP-Complete)-20260506.pdf" type="application/pdf" width=100% height=1000px></iframe>
