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