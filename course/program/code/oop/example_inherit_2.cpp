#include <iostream>
using namespace std;

class BaseClass {
protected:
    int a;
};

class MyClass : public BaseClass {
public:
    void print() {
        cout << a << endl;
    }
};

int main() {
    MyClass c;
    // c.a = 114; // 报错！不能在外部访问 protected 变量
    c.print();
    return 0;
}