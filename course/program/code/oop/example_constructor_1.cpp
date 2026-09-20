#include <iostream>
using namespace std;

class MyClass {
private:
    int a, b, c;
public:
    MyClass() {
        a = b = c = 0;
    }
    
    MyClass(int a) { // 重名
        this -> a = a;
        b = c = 0;
    }

    MyClass(int a, int b, int c = 0) : a(a), b(b), c(c) {} // 默认值 & 语法糖

    void print() {
        cout << "a is " << a << ", b is " << b << ", c is " << c << endl;
    }
};

int main() {
    MyClass a;
    a.print(); // 0, 0, 0

    MyClass b(1);
    b.print(); // 1, 0, 0

    MyClass c(1, 2);
    c.print(); // 1, 2, 0

    MyClass d = MyClass(1, 2, 3);
    d.print(); // 1, 2, 3

    return 0;
}