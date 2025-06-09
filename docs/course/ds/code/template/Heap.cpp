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
    // 插入元素（len需小于MAX_SIZE）
    void insert(int val) {
        data[len] = val;    // 将新元素放在堆的末尾
        len++;              // 增加堆大小
        heapifyUp(len - 1); // 上浮
    }
    // 弹出堆顶元素（len需大于0）
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