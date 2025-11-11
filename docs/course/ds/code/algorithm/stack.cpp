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