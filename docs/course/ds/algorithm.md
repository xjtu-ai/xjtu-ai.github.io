算法模板以题目为背景，选取 Luogu 和作业平台上的例题。讲解为什么选择这个算法，这个算法实现时要注意什么。

## 链表运用——多项式加法（第四周第四题）

使用链表来实现多项式的加法，尤其是在指数范围较大或指数不连续的情况下，是一个更为合理的选择。链表的优势在于它能高效地处理稀疏多项式（非连续指数），节省空间，并且操作起来相对灵活。

为什么选择链表？

- 多项式可能很稀疏（非连续指数），用数组存储可能会浪费大量空间。
- 链表动态存储，适合处理虚拟空间中的非零项。
- 插入、合并、删除操作都可以用链表高效实现。

如何实现加法？

在存储多项式时，如果我们将每一项在链表内的顺序按照指数从小到大排序，那么加法就会比较简单。流程如下：

1. 比较待加两个多项式的当前最低次项
2. 如果次数不同，把次数更小的取出，插入新多项式
3. 如果次数相同，把两个都取出，加起来插入新多项式
4. 重复 1. 直到某个多项式为空
5. 把剩下的另一个多项式全部插入答案的尾部

读者不难注意到，这个算法和归并排序中的合并如出一辙，因为这其实是对指数有序数组的合并。

??? note "参考代码"
    ```cpp
    struct Monomial {
        Monomial *nxt;
        int exp, coeff;
        Monomial() : nxt(nullptr) {}
        Monomial(Monomial *nxt, int exponent, int coefficient)
            : nxt(nxt), exp(exponent), coeff(coefficient) {}
    };
    
    class Polynomial {
      private:
        Monomial *content;
        int length;
    
      public:
        Polynomial() : content(nullptr), length(0) {}
        Polynomial(const Polynomial &x);
        ~Polynomial();
        Polynomial &operator=(const Polynomial &rhs);
    
        friend Polynomial operator+(const Polynomial &lhs, const Polynomial &rhs);
    };
    
    inline Polynomial::Polynomial(const Polynomial &x)
        : content(nullptr), length(x.length) {
        Monomial **tail = &content;
        for (Monomial *p = x.content; p != nullptr; p = p->nxt) {
            *tail = new Monomial(*tail, p->exp, p->coeff);
            tail = &((*tail)->nxt);
        }
    }
    
    inline Polynomial::~Polynomial() {
        for (Monomial *p = content; p != nullptr;) {
            Monomial *q = p;
            p = p->nxt;
            delete q;
        }
    }
    
    inline Polynomial &Polynomial::operator=(const Polynomial &rhs) {
        for (Monomial *p = content; p != nullptr;) {
            Monomial *q = p;
            p = p->nxt;
            delete q;
        }
        content = nullptr;
        length = rhs.length;
        Monomial **tail = &content;
        for (Monomial *p = rhs.content; p != nullptr; p = p->nxt) {
            *tail = new Monomial(*tail, p->exp, p->coeff);
            tail = &((*tail)->nxt);
        }
        return *this;
    }
    
    inline Polynomial operator+(const Polynomial &lhs, const Polynomial &rhs) {
        Polynomial result;
        Monomial *tail = nullptr;    // 指向结果链表的最后一个节点
        Monomial *current = nullptr; // 新节点临时变量
        Monomial *lp = lhs.content, *rp = rhs.content;
    
        while (lp != nullptr || rp != nullptr) {
            if (lp != nullptr && (rp == nullptr || lp->exp < rp->exp)) {
                // 1. 或 3.：插入lp
                current = new Monomial(nullptr, lp->exp, lp->coeff);
            } else if (rp != nullptr && (lp == nullptr || lp->exp > rp->exp)) {
                // 2. 或 4.：插入rp
                current = new Monomial(nullptr, rp->exp, rp->coeff);
            } else {
                // 5.：指数相等，系数相加
                double new_coeff = lp->coeff + rp->coeff;
                if (new_coeff != 0) {
                    current = new Monomial(nullptr, lp->exp, new_coeff);
                } else {
                    // 系数相加为0，不插入，继续下一组
                    lp = lp->nxt;
                    rp = rp->nxt;
                    continue;
                }
                lp = lp->nxt;
                rp = rp->nxt;
            }
    
            // 将新节点加入链表
            if (result.content == nullptr) {
                // 第一个节点
                result.content = current;
                tail = current;
            } else {
                // 非第一个节点，追加到尾部
                tail->nxt = current;
                tail = current;
            }
            result.length++;
        }
        return result;
    }
    ```

## 栈的运用——括号匹配（十三周第一题）

括号匹配是栈的一大应用。

一般的括号匹配可能有多种括号，比如 `()`、`[]`、`{}`、`<>` 什么的。括号匹配的核心只有一句话：

- 从左往右扫描括号，每一个右括号都必须和**在它之前的最后一个未匹配的左括号匹配**。

如果它之前没有未匹配的左括号，或者最后一个未匹配的左括号和它不是同一种括号（比如 `[)`）那么括号匹配失败。

那么，如何维护这个**最后一个未匹配的左括号**呢？

分析一下，我们是从前往后扫描左括号的，但是却要从后往前取出来，所以需要一个**后进先出**的数据结构，也就是栈。流程如下：

1. 遍历表达式的每个字符。
2. 遇到左括号时，入栈。
3. 遇到右括号时，弹出栈顶元素：
   - 如果栈为空，或者栈顶的括号类型不同，说明没有对应的左括号，匹配失败。
   - 否则，弹出栈顶元素，匹配成功。
4. 表达式扫描完后：
   - 如果栈为空，表示所有括号都匹配。
   - 如果栈不为空，说明有左括号没有配对，匹配失败。

下面用数组模拟一个栈：

??? note "参考代码"
    ```cpp
    #include <iostream>
    #include <string>
    using namespace std;
    
    int main() {
        string s;
        cin >> s;
    
        // 定义栈（用数组模拟）
        char stack[1000]; // 假设表达式长度不超过1000
        int top = -1;     // 栈顶指针，-1 表示空栈
    
        bool isMatch = true; // 标志括号是否匹配
    
        for (char ch : s) {
            if (ch == '(' || ch == '[') {
                // 入栈
                top++;
                stack[top] = ch;
            } else if (ch == ')') {
                // 出栈，匹配
                if (top == -1 || stack[top] != '(') {
                    isMatch = false;
                    break;
                } else {
                    top--;
                }
            } else if (ch == ']') {
                // 出栈，匹配
                if (top == -1 || stack[top] == '[') {
                    isMatch = false;
                    break;
                } else {
                    top--;
                }
            }
        }
    
        // 扫描结束后，判断栈是否为空
        if (isMatch && top == -1) {
            cout << "括号匹配！" << endl;
        } else {
            cout << "括号不匹配！" << endl;
        }
    
        return 0;
    }
    ```

不过这个题只要求匹配小括号。我们发现，第三步中的判断“类型是否相同”就不重要了，因为栈里只有可能有小括号。进一步地，栈里的元素就不重要了，我们只关心栈的大小，即“是否有足够多左括号给右括号匹配”：

```cpp
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
int main() {
    string s;
    cin >> s;
    int cnt = 0;
    for (char ch : s) {
        if (ch == '(') cnt++;
        if (ch == ')') cnt--;
        if (cnt < 0) {
            break;
        }
    }
    if (cnt == 0) {
        puts("括号匹配！");
    } else {
        puts("括号不匹配！");
    }
    return 0;
}
```

**注意第12行和第18行的两个失败判断缺一不可！** 虽然在作业平台上不写 12 行也能通过。


## 堆的运用——第K小值 [P1338](https://www.luogu.com.cn/problem/P1138)

求第 $k$ 小值，一种暴力的思路是对输入进行排序，然后直接返回第 $k$ 个元素。排序的复杂度是 $\mathcal O(n \log n)$。如果 $n$ 很大，但是 $k$ 很小，有没有更好的办法呢？

我们先思考怎么求最小值。我们有所谓“擂台法”。每次拿一个新的数，和当前最小值进行比较，留下新的最小值。在这种算法中，如果考察了 $m$ 个数，我们就得到前 $m$ 个数的最小值。

那如果要求次小值呢？我们还是可以打擂台：我们维护前 $m$ 个数中最小的那两个数。每当加入一个新数，就把前 $m$ 个数中最小的那两个数和这个新数一共三个数进行比较，留下两个最小的作为新的答案。

这个算法的正确性在于如下观察：**如果已经有两个数小于 $a$，则无论后面还有多少个数，$a$ 永远不可能成为最小的两个**。

这种算法可以方便地扩展到前 $k$ 小：我们维护前 $m$ 个数中最小的 $k$ 个数。每当加入一个新数，就把这 $k$ 个数和这个新数一共 $k + 1$ 个数进行比较，留下 $k$ 个最小的作为新的答案。

乍一看，我们好像要操作 $k$ 次数据结构，毕竟要保留 $k$ 个数嘛。但是你想，在 $k+1$ 个数中**保留最小的 $k$ 个数，其实就是删除最大的一个数**嘛！

所以，我们需要一个数据结构，能够：

- 在 $k$ 个数中加入一个新数
- 把 $k+1$ 个数中最大的删掉

这正好是一个**大根堆**。好好思考一下为什么求最小值需要大根堆。

??? note "参考代码"
    ```cpp
    #include <cstring> // for memset
    #include <iostream>
    using namespace std;
    
    class MaxHeap {
      private:
        int data[10005]; // 索引从1开始
        int size;
    
        void siftUp(int idx) {
            while (idx > 1 && data[idx / 2] < data[idx]) {
                swap(data[idx / 2], data[idx]);
                idx = idx / 2;
            }
        }
    
        void siftDown(int idx) {
            while (true) {
                int largest = idx;
                int left = 2 * idx;
                int right = 2 * idx + 1;
                if (left <= size && data[left] > data[largest]) {
                    largest = left;
                }
                if (right <= size && data[right] > data[largest]) {
                    largest = right;
                }
                if (largest == idx) break;
                swap(data[idx], data[largest]);
                idx = largest;
            }
        }
    
      public:
        MaxHeap() : size(0) {} // 初始化为空
    
        void push(int val) {
            data[++size] = val;
            siftUp(size);
        }
    
        void pop() {
            if (size == 0) return;
            swap(data[1], data[size]);
            size--;
            siftDown(1);
        }
    
        int top() {
            if (size == 0) return -1;
            return data[1];
        }
    
        int getSize() { return size; }
    };
    
    int main() {
        int n, k;
        cin >> n >> k;
    
        // 存储元素是否已出现
        bool exists[30005];
        memset(exists, false, sizeof(exists));
    
        MaxHeap heap;
    
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            if (exists[x]) continue; // 已存在
            exists[x] = true;
            heap.push(x);
            if (heap.getSize() > k) {
                heap.pop(); // 保持堆中元素不超过k
            }
        }
    
        if (heap.getSize() < k) {
            cout << "NO RESULT" << endl;
        } else {
            cout << heap.top() << endl; // 第k小
        }
    
        return 0;
    }
    ```


## 图的遍历——拓扑排序 [P1113](https://www.luogu.com.cn/problem/P1113)

拓扑排序的原理，是在搜索的过程中进行一个“忍耐”。当你发现一个新节点的时候，不着急访问它，而是“删掉这条边”，维护新节点的入度，直到入度为 0 了再去访问它。这样一来，既满足了拓扑序的要求（入度为 0 说明所有前置节点已经被访问），又能保证搜索的完整性（**每个点必然会被最后一条入边访问**）。

另一个要提及的是建图方法。在离散课中，提出了所谓“流程图”，把事件建成边。这是非常别扭的。因为限制条件明明是事件间的二元关系，把事件建成点，依赖关系建成边更合理。当你求出拓扑序之后，按照拓扑序进行如下递推：

- **我的最早完成时间** = **我自己的消耗时长** + **我所有依赖关系的最早完成时间的最大值**

这个递推成立的理由是：**按照拓扑序，在计算自己的最早完成时间时，依赖关系的最早完成事件已经计算完成。**

??? note "参考代码"
    ```cpp
    #include <algorithm>
    #include <iostream>
    using namespace std;
    
    const int MAXN(1e4 + 5), MAXM(1e6 + 5);
    
    struct edge {
        int nxt, v;
    };
    edge e[MAXM];
    int head[MAXN], cnt, in_degree[MAXN];
    
    void add(int u, int v) {
        e[++cnt].v = v;
        e[cnt].nxt = head[u];
        head[u] = cnt;
        in_degree[v]++;
    }
    
    int len[MAXN], ans[MAXN];
    int que[MAXN], h, t;
    
    int main() {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            int id;
            cin >> id;
            cin >> len[id];
            int x;
            while (true) {
                cin >> x;
                if (x == 0) break;
                add(x, id);
            }
        }
        // 强烈推荐在 BFS 的基础上实现拓扑排序
        h = t = 1;
        que[t++] = 1;
        while (h < t) {
            int u = que[h++];
            for (int i = head[u]; i; i = e[i].nxt) {
                in_degree[e[i].v]--;
                // 正常的 BFS 在这里直接把 e[i].v 入队，但是拓扑排序要等到 e[i].v
                // 所有前置都完成才行
                if (in_degree[e[i].v] == 0) {
                    que[t++] = e[i].v;
                }
            }
        }
        // que 恰好是拓扑序
        int max_ans = 0;
        for (int i = 1; i <= n; i++) {
            int u = que[i];
            ans[u] += len[u];
            for (int j = head[u]; j; j = e[j].nxt) {
                ans[e[j].v] = max(ans[e[j].v], ans[u]);
            }
            max_ans = max(max_ans, ans[u]);
        }
        cout << max_ans << endl;
    }
    ```


## 排序——简单排序（十四周第一题）


插入排序：类似于整理扑克牌，从第二个元素开始，将每个元素插入到前面已排序部分的合适位置。

```cpp
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        
        // 将大于key的元素向后移动一位
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
```

选择排序：每次从未排序部分选择最小的元素，放到已排序部分的末尾。

```cpp
void selectionSort(int arr[], int n) {
    int i, j, min_idx, temp;
    
    for (i = 0; i < n - 1; i++) {
        // 找到未排序部分的最小元素
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        
        // 交换最小元素与当前位置元素
        if (min_idx != i) {
            temp = arr[min_idx];
            arr[min_idx] = arr[i];
            arr[i] = temp;
        }
    }
}
```

冒泡排序：重复遍历数组，比较相邻元素并交换，使较大元素"冒泡"到末尾。

```cpp
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    int swapped;
    
    for (i = 0; i < n - 1; i++) {
        swapped = 0;  // 优化：检测是否发生交换
        
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // 交换相邻元素
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        
        // 如果没有发生交换，说明数组已经有序
        if (swapped == 0) {
            break;
        }
    }
}
```


## 排序——复杂排序（十四周第二题）

### 快速排序

快速排序的核心操作是“哨兵划分”，其目标是：选择数组中的某个元素作为“基准数”，将所有小于基准数的元素移到其左侧，而大于基准数的元素移到其右侧。

1. 选取数组最左端元素作为基准数，初始化两个指针 i 和 j 分别指向数组的两端。
2. 设置一个循环，在每轮中使用 i（j）分别寻找第一个比基准数大（小）的元素，然后交换这两个元素。
3. 循环执行步骤 2. ，直到 i 和 j 相遇时停止，最后将基准数交换至两个子数组的分界线。

哨兵划分完成后，原数组被划分成三部分：左子数组、基准数、右子数组，且满足“左子数组任意元素 $\leq$ 基准数 $\leq$ 右子数组任意元素”。因此，我们接下来只需对这两个子数组进行排序。

```cpp
/* 哨兵划分 */
int partition(int *nums, int left, int right) {
    // 以 nums[left] 为基准数
    int i = left, j = right;
    while (i < j) {
        while (i < j && nums[j] >= nums[left])
            j--;                // 从右向左找首个小于基准数的元素
        while (i < j && nums[i] <= nums[left])
            i++;                // 从左向右找首个大于基准数的元素
        swap(nums[i], nums[j]); // 交换这两个元素
    }
    swap(nums[i], nums[left]);  // 将基准数交换至两子数组的分界线
    return i;                   // 返回基准数的索引
}

/* 快速排序 */
void quickSort(int *nums, int left, int right) {
    // 子数组长度为 1 时终止递归
    if (left >= right)
        return;
    // 哨兵划分
    int pivot = partition(nums, left, right);
    // 递归左子数组、右子数组
    quickSort(nums, left, pivot - 1);
    quickSort(nums, pivot + 1, right);
}
```


### 归并排序

归并排序（merge sort）是一种基于分治策略的排序算法，包含“划分”和“合并”阶段。

1. **划分阶段**：通过递归不断地将数组从中点处分开，将长数组的排序问题转换为短数组的排序问题。
2. **合并阶段**：当子数组长度为 1 时终止划分，开始合并，持续地将左右两个较短的有序数组合并为一个较长的有序数组，直至结束。

```cpp
/* 合并左子数组和右子数组 */
void merge(int *nums, int left, int mid, int right) {
    // 左子数组区间为 [left, mid], 右子数组区间为 [mid+1, right]
    // 创建一个临时数组 tmp ，用于存放合并后的结果
    int *tmp = new int[right - left + 1];
    // 初始化左子数组和右子数组的起始索引
    int i = left, j = mid + 1, k = 0;
    // 当左右子数组都还有元素时，进行比较并将较小的元素复制到临时数组中
    while (i <= mid && j <= right) {
        if (nums[i] <= nums[j])
            tmp[k++] = nums[i++];
        else
            tmp[k++] = nums[j++];
    }
    // 将左子数组和右子数组的剩余元素复制到临时数组中
    while (i <= mid) {
        tmp[k++] = nums[i++];
    }
    while (j <= right) {
        tmp[k++] = nums[j++];
    }
    // 将临时数组 tmp 中的元素复制回原数组 nums 的对应区间
    for (k = 0; k < tmp.size(); k++) {
        nums[left + k] = tmp[k];
    }
    delete[] tmp;
}

/* 归并排序 */
void mergeSort(int *nums, int left, int right) {
    // 终止条件
    if (left >= right)
        return; // 当子数组长度为 1 时终止递归
    // 划分阶段
    int mid = left + (right - left) / 2;    // 计算中点
    mergeSort(nums, left, mid);      // 递归左子数组
    mergeSort(nums, mid + 1, right); // 递归右子数组
    // 合并阶段
    merge(nums, left, mid, right);
}
```


### 堆排序

堆排序（heap sort）是一种基于堆数据结构实现的高效排序算法。我们可以利用已经学过的“建堆操作”和“元素出堆操作”实现堆排序。

1. 输入数组并建立小顶堆，此时最小元素位于堆顶。
2. 不断执行出堆操作，依次记录出堆元素，即可得到从小到大排序的序列。

以上方法虽然可行，但需要借助一个额外数组来保存弹出的元素，比较浪费空间。在实际中，我们通常让堆和已排序数组公用一块空间：数组前半部分维护一个大根堆，后半部分维护已排序的较大数。

```cpp
/* 堆的长度为 n ，从节点 i 开始，从顶至底堆化 */
void siftDown(int *nums, int n, int i) {
    while (true) {
        // 判断节点 i, l, r 中值最大的节点，记为 ma
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int ma = i;
        if (l < n && nums[l] > nums[ma])
            ma = l;
        if (r < n && nums[r] > nums[ma])
            ma = r;
        // 若节点 i 最大或索引 l, r 越界，则无须继续堆化，跳出
        if (ma == i) {
            break;
        }
        // 交换两节点
        swap(nums[i], nums[ma]);
        // 循环向下堆化
        i = ma;
    }
}

/* 堆排序 */
void heapSort(int *nums) {
    // 建堆操作：堆化除叶节点以外的其他所有节点
    for (int i = nums.size() / 2 - 1; i >= 0; --i) {
        siftDown(nums, nums.size(), i);
    }
    // 从堆中提取最大元素，循环 n-1 轮
    for (int i = nums.size() - 1; i > 0; --i) {
        // 交换根节点与最右叶节点（交换首元素与尾元素）
        swap(nums[0], nums[i]);
        // 以根节点为起点，从顶至底进行堆化
        siftDown(nums, i, 0);
    }
}
```

值得注意的是，堆排序只需要 `shiftDown` 就能运行，无需实现 `shiftUp`。

## 二分查找 [P2249](https://www.luogu.com.cn/problem/P2249)

很多人都玩过猜数游戏。如果每次能知道大了还是小了，我们就可以每次询问中位数。因为这么做可以把可能的答案集合缩小一半。

对于一列排好序的数，思路是相似的：如果我想找到某个数的位置，其实就是在 1 到 $n$ 中“猜位置”。我先猜他在正中间，然后看看是猜大了还是猜小了。

这里有一个关键点：必须要是排好序的。这样，通过比较**猜测位置的值**和**待查找的值**，就可以实现**猜测位置**和**待查找的值的位置**的转化。否则折半查找是不成立的。

我们每次折的半，不是值域的一半，而是下标的一半。

那么，代码应该不难写：

??? note "参考代码"
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    
    const int MAXN(1e6 + 5);
    
    /*
    假设 a 是长度为 n 的从小到大排序的数组，查找 v 的首次出现位置
    
    如果不存在，返回 -1
    */
    int binary_search(int *a, int n, int v) {
        int l = 1, r = n, mid; // [l, r] 是当前可能的下标区间
        int ans = n + 1;
        while (l <= r) {
            mid = (l + r) / 2;                    // 这次猜测中位数
            if (v == a[mid]) ans = min(ans, mid); // 最小的那个出现位置
            if (v > a[mid]) l = mid + 1;
            else r = mid - 1;
        }
        if (ans == n + 1) ans = -1;
        return ans;
    }
    
    int n, m;
    int a[MAXN];
    
    int main() {
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
        }
        while (m--) {
            int x;
            scanf("%d", &x);
            printf("%d ", binary_search(a, n, x));
        }
        return 0;
    }
    ```


## 最大子段和（第四周十一题） 

基础的动态规划思想。

如果我们已经知道了**以 $a_{i-1}$ 为结尾的最大子段和 $pre$**，那么以 $a_i$ 为结尾的最大子段和如下：

- $sum = a_i + \max(pre, 0)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
int now, pre, ans = -999999999;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> now;
        if (pre > 0) now += pre;
        pre = now;
        ans = max(ans, now);
    }
    cout << ans << endl;
    return 0;
}
```


## 如何取出十进制数的每一位（第三周第九题）

这是一个小技巧：如果你需要对“每位数字”进行操作，可以使用下面的模板：

```cpp
int x = 12345;
while (x) {
    int tmp = x % 10;
    x /= 10;
    //... tmp 轮流取 5,4,3,2,1
}
```

使用反方法可以从字符串拼出一个整数：

```cpp
string s = "12345";
int x = 0;
for (int i = 0; i < s.size(); i++) {
    int tmp = s[i] - '0';
    x *= 10;
    x += tmp;
} // x = 54321
```

要注意这样做都是逆序的。


## 字符串查找（第三周第二题）

借助这一题，说一些 `std::string` 的使用技巧。

首先是读入一整行：

```cpp
#include <string> // 非常关键！
#include <iostream>

string s;
getline(cin, s); // 读入一整行，末尾不含 '\n'
```

这里 `#include <string>` 非常关键。在 GCC/MinGW 环境下，不加这一行也能运行，但是在评测用的 MSVC 中，会出现报错。不要因为这个失分！

其次是如何比较。两个 `string` 类型可以用 `<,>,==` 等进行比较，这种比较是**字典序比较**。举几个例子就明白了：

```cpp
"abc" < "de"
"ab" < "abc"
"ac" > "abc"
"" < 任意非空字符串
"" == ""
"a" == "a"
```

**取出子串的方法：**

```cpp
string s = "abcdefg";
int l = 1, r = 3;
string sub = s.substr(l, r - l + 1);  // 从位置l开始，长度为r-l+1
// 或者更直观的写法
string sub = s.substr(1, 3);  // "bcd"
```

**字符串查找相关方法**：
```cpp
string s = "hello world";

// 查找子串位置
size_t pos = s.find("world");  // 返回6，找不到返回string::npos

// 从指定位置开始查找
pos = s.find("l", 3);  // 从位置3开始找'l'

// 反向查找
pos = s.rfind("l");  // 从后往前找最后一个'l'
```

**字符串长度和空判断**：
```cpp
string s = "hello";
cout << s.length() << endl;  // 或者 s.size()
if (s.empty()) { /* 字符串为空 */ }
```

**字符串拼接**：
```cpp
string a = "hello";
string b = "world";
string c = a + " " + b;  // "hello world"
a += b;  // a变成"helloworld"
```
