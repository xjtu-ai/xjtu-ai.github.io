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