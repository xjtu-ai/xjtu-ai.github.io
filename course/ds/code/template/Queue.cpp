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