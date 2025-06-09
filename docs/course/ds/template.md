以下将简要介绍常用的数据结构并给出代码模板。  
存储的数据类型默认为`int`。  
P.S. 为了方便，析构函数有时候可以不写（代码能过应该就不会复查）。

## 数组（Array）

数组是最基本的数据结构，存储一组相同类型的数据。特点如下：
- 大小固定，存储空间连续，内存分配效率高。
- 插入和删除操作效率低，时间复杂度为`O(n)`。
- 随机访问效率高，时间复杂度为`O(1)`。

数组适用于存储数据集大小固定，且不需要频繁插入和删除的场景。

## 链表（Linked List）

链表是一种动态数据结构，由一系列节点组成，每个节点包含数据和指向后继节点的指针。特点如下：
- 大小可变，存储空间不连续，内存分配效率低。
- 插入和删除操作效率高，时间复杂度为`O(1)`。
- 随机访问效率低，时间复杂度为`O(n)`。

链表适用于存储数据集大小可变，且需要频繁插入和删除的场景。

**易错点**：
- 空指针：注意对头结点和边界条件的处理。
- 悬空指针（删除节点后访问指向此节点的指针）

**双链表**  
双链表是链表的一种变体，每个节点额外包含了指向前驱节点的指针，可以进行双向遍历。  
在某些场景下比单链表更高效，例如删除已知节点时。在维护和单链表类似，但需要注意前驱指针的更新。

??? note "参考代码"
    ```cpp
    #include <iostream>
    using namespace std;
    
    struct Node {
        int data;
        Node *next;
        Node(int val = 0, Node *ptr = NULL) : data(val), next(ptr) {}
    };
    
    class List {
      public:
        Node *head; // 头节点
        int len;    // 表长（可选)
    
        void deepcopy(const List &other) { // 深拷贝
            Node *curOther = other.head->next;
            Node *curThis = head;
            while (curOther != NULL) {
                curThis->next = new Node(curOther->data);
                curThis = curThis->next;
                curOther = curOther->next;
            }
            len = other.len;
        }
        void clear() { // 清空链表
            Node *current = head->next;
            while (current != NULL) {
                Node *n = current->next;
                delete current;
                current = n;
            }
            head->next = NULL; // 防止悬空指针
            len = 0;
        }
    
        List() : len(0) { head = new Node(); } // 构造函数
        ~List() {
            clear();
            delete head;
        } // 析构函数
        // 拷贝构造函数
        List(const List &other) : len(0) {
            head = new Node();
            deepcopy(other);
        }
        // 赋值运算符重载
        List &operator=(const List &other) {
            if (this != &other) { // 防止自我赋值
                clear();          // 先清空自身
                deepcopy(other);
            }
            return *this;
        }
    
        int size() { return len; }
        bool isEmpty() { return head->next == NULL; }
        // 在指定位置插入元素（index需在[0, len]内）
        void insert(int data, int index) {
            Node *current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
            // 在current后插入新节点
            Node *n = new Node(data, current->next);
            current->next = n;
            len++;
        }
        void insertAtHead(int data) { insert(data, 0); }
        void insertAtTail(int data) { insert(data, len); }
        // 删除指定位置的元素（index需在[0, len-1]内）
        void remove(int index) {
            Node *current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
            // 删除current的后继节点
            Node *n = current->next;
            current->next = n->next;
            delete n;
            len--;
        }
        // 返回指定位置的元素（index需在[0, len-1]内）
        int get(int index) const {
            Node *current = head->next;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
            return current->data;
        }
        // 查找指定元素
        // 返回首个匹配元素的索引，如果未找到则返回-1
        int find(int val) {
            Node *current = head->next;
            int index = 0;
            while (current != NULL) {
                if (current->data == val) {
                    return index;
                }
                current = current->next;
                index++;
            }
            return -1;
        }
        // 打印链表中的所有元素，依实际需要修改
        void print() {
            if (len == 0) {
                cout << "empty" << endl;
                return;
            }
            Node *current = head->next;
            while (current != NULL) {
                cout << current->data << endl;
                current = current->next;
            }
        }
    };
    ```

## 栈（Stack）

栈是一种后进先出（LIFO，Last In First Out）数据结构。特点如下：
- 只能在栈顶进行插入和删除操作。
- 遵循后进先出原则。

应用广泛，如函数调用、表达式求值、深度优先搜索、括号匹配等。  

**易错点**：
- 栈溢出（栈满时入栈）
- 栈下溢（栈空时出栈）

??? note "参考代码"
    ```cpp
    #include <iostream>
    using namespace std;
    
    class Stack {
      public:
        enum { MAX_SIZE = 100 }; // 栈最大容量
        int data[MAX_SIZE];      // 存储栈元素的数组
        int top;                 // 栈顶指针，指向栈顶元素的下一位
    
        Stack() : top(0) {}
        int size() { return top; } // 返回栈中元素的数量
        bool isEmpty() { return top == 0; }
        bool isFull() { return top == MAX_SIZE; }
        // 入栈（top需小于MAXSIZE）
        void push(int val) { data[top++] = val; }
        // 出栈（top需大于0）
        int pop() {
            if (top == 0) return -1;
            return data[--top];
        }
        // 查看栈顶元素
        int peek() {
            if (top == 0) return -1;
            return data[top - 1];
        }
        // 打印栈中所有元素 (从栈底到栈顶)，依实际需要修改
        void print() {
            if (top == 0) {
                cout << "empty" << endl;
                return;
            }
            for (int i = 0; i < top; i++) {
                cout << data[i] << endl;
            }
        }
    };
    ```

## 队列（Queue）

队列是一种先进先出（FIFO，First In First Out）数据结构。特点如下：
- 只能在队头进行删除操作，在队尾插入。
- 遵循FIFO原则。

常用于任务调度、广度优先搜索等场景。  

**易错点**：
- 队列溢出（队列满时入队）
- 队列下溢（空队列出队）

??? note "参考代码"
    ```cpp
    #include <iostream>
    using namespace std;
    
    class Queue { // 使用循环数组实现队列
      public:
        enum { MAX_SIZE = 1000 }; // 队列最大容量
        int data[MAX_SIZE];       // 存储队列元素的数组
        int front;                // 队头指针，指向队头元素
        int rear;                 // 队尾指针，指向队尾元素的下一位
        int len;                  // 队列长度
        // 队列为空或满时，front和rear相同
        // 此时可以通过其长度来区分队列是否为空或满
        Queue() : front(0), rear(0), len(0) {}
        int size() { return len; }
        bool isEmpty() { return len == 0; }
        bool isFull() { return len == MAX_SIZE; }
        // 入队（len需小于MAXSIZE）
        void push(int val) {
            data[rear] = val;
            rear = (rear + 1) % MAX_SIZE; // 队尾指针循环后移
            len++;
        }
        // 出队（len需大于0）
        int pop() {
            if (len == 0) return -1;
            int val = data[front];
            front = (front + 1) % MAX_SIZE; // 队头指针循环后移
            len--;
            return val;
        }
        // 查看队头元素
        int peek() {
            if (len == 0) return -1;
            return data[front];
        }
        // 打印队列中所有元素 (从队头到队尾)，依实际需要修改
        void print() {
            if (len == 0) {
                cout << "empty" << endl;
                return;
            }
            for (int i = 0; i < len; i++) {
                cout << data[(front + i) % MAX_SIZE] << endl;
            }
        }
    };
    ```

## 图（Graph）

图由顶点和边组成。特点如下：
- 顶点可以有任意数量的边连接。
- 边可以是有向或无向。
- 边可以附带权重，表示成本或距离。

常用于网络、关系、地图等复杂结构。  
存储方式有邻接矩阵和邻接表。邻接矩阵空间复杂度为`O(V^2)`，邻接表为`O(V+E)`。这里只给出邻接表的实现。  

**易错点**：
- 图的边或顶点数超出数组限制
- 无向图需存储双向边

??? note "参考代码"
    ```cpp
    #include "Queue.cpp"
    #include <iostream>
    
    using namespace std;
    
    enum { MAX_N = 100, MAX_M = 2000 };
    
    class Graph {
      public:
        int n; // 顶点数
        struct Edge {
            float weight; // 边的权重
            int to, next; // 终点索引 / 下一条边的索引
            Edge(int t = -1, int n = -1, float w = 1.0)
                : to(t), next(n), weight(w) {}
        } edges[MAX_M];  // 存储所有边的数组
        int head[MAX_N]; // 存储每个顶点的第一条边的索引
        int count;       // 当前边的数量
    
        Graph(int n = 0) : n(n), count(0) {
            for (int i = 0; i < MAX_N; ++i) {
                head[i] = -1; // 初始化每个顶点的邻接表头为-1
            }
        }
        // 添加无向边
        void addEdge(int from, int to, float weight = 1.0) {
            addDirectedEdge(from, to, weight);
            addDirectedEdge(to, from, weight);
        }
        // 添加有向边
        void addDirectedEdge(int from, int to, float weight = 1.0) {
            edges[count] = Edge(to, head[from], weight);
            head[from] = count;
            count++;
        }
        bool hasEdge(int from, int to) {
            int index = head[from];
            while (index != -1) {
                if (edges[index].to == to) return true;
                index = edges[index].next;
            }
            return false;
        }
        // 深度优先遍历 (DFS)
        void dfs(int node, bool visited[]) {
            visited[node] = true;
            cout << node << " ";
    
            int index = head[node];
            while (index != -1) {
                int neighbor = edges[index].to;
                if (!visited[neighbor]) {
                    dfs(neighbor, visited); // 递归访问
                }
                index = edges[index].next;
            }
        }
        // 广度优先遍历 (BFS)
        void bfs(int node, bool visited[]) {
            Queue q; // 使用前文定义的队列
            q.push(node);
            visited[node] = true;
    
            while (!q.isEmpty()) {
                int current = q.pop();
                cout << current << " ";
    
                int index = head[current];
                while (index != -1) {
                    int neighbor = edges[index].to;
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        q.push(neighbor); // 将未访问的邻居入队
                    }
                    index = edges[index].next;
                }
            }
        }
    };
    ```


## 堆（Heap）

堆是一种特殊的完全二叉树，特点如下：
- 完全二叉树。
- 每个节点的值都大于等于（最大堆）或小于等于（最小堆）其子节点。
- 插入与删除时间复杂度为`O(log n)`。

常用于优先队列、Dijkstra算法、Top K、堆排序等。  
存储可以用数组（根节点下标为0）或链表，这里考虑数组的实现。

**易错点**：
- 数组下标计算错误：左子节点`2k+1`，右子节点`2k+2`，父节点`(k-1)/2`
- 堆性质未维护：插入和删除后需调整堆结构

??? note "参考代码"
    ```cpp
    #include <algorithm>
    using namespace std;
    
    // 最大堆
    class MaxHeap {
      public:
        enum { MAX_SIZE = 100 }; // 堆的最大容量
        int data[MAX_SIZE];      // 存储堆中元素的数组
        int len;                 // 当前元素的数量
        MaxHeap() : len(0) {}
        int size() { return len; }
        bool isEmpty() { return len == 0; }
        bool isFull() { return len == MAX_SIZE; }
        // 上浮操作（新元素插入到堆底时）
        void heapifyUp(int index) {
            // 当前节点大于父节点
            while (index > 0 && data[index] > data[(index - 1) / 2]) {
                // 交换当前节点和父节点
                swap(data[index], data[(index - 1) / 2]);
                // 移动到父节点
                index = (index - 1) / 2;
            }
        }
        // 下沉操作（堆顶元素被移除或改变时）
        void heapifyDown(int index) {
            // 检查是否为叶子节点
            if (index > (len / 2 - 1)) return;
            int largest = index; // 假设当前节点最大
            int left = 2 * index + 1, right = 2 * index + 2;
            // 左子节点一定存在
            if (data[left] > data[largest]) {
                largest = left;
            }
            // 右子节点可能存在
            if (right < len && data[right] > data[largest]) {
                largest = right;
            }
            // 如果最大值不是当前节点，则交换并下沉
            if (largest != index) {
                swap(data[index], data[largest]);
                heapifyDown(largest);
            }
        }
        // 插入元素（len需小于MAXSIZE）
        void insert(int val) {
            data[len] = val;    // 将新元素放在堆的末尾
            len++;              // 增加堆大小
            heapifyUp(len - 1); // 上浮
        }
        // 弹出堆顶元素（len需大于MAXSIZE）
        int pop() {
            if (len == 0) return -1;
            int val = data[0];
            data[0] = data[len - 1]; // 将最后一个元素移到堆顶
            len--;                   // 减少堆大小
            heapifyDown(0);          // 下沉
            return val;
        }
        // 查看堆顶元素
        int peek() {
            if (len == 0) return -1;
            return data[0];
        }
        // 线性建堆（n需不大于MAX_SIZE）
        void build(int arr[], int n) {
            len = n;
            for (int i = 0; i < len; i++) {
                data[i] = arr[i];
            }
            // 从最后一个非叶子节点开始向上依次进行下沉
            for (int i = len / 2 - 1; i >= 0; i--) {
                heapifyDown(i);
            }
        }
        // 堆排序（从小到大）
        void HeapSort(int arr[], int n) {
            build(arr, n); // 建立最大堆
            for (int i = n - 1; i > 0; i--) {
                // 将堆顶元素（最大值）与最后一个元素交换
                swap(data[0], data[i]);
                len--;          // 减少堆大小
                heapifyDown(0); // 下沉
            }
            // 将排序后的元素放回原数组
            for (int i = 0; i < n; i++) arr[i] = data[i];
        }
    };
    ```
