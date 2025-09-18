#include <iostream>
using namespace std;

class MyClass {
    int a; // 默认权限是 private

public: // 指定接下来的内容是 public
    int b;

private: // 指定接下来的内容是 private
    void foo() {
        cout << "foo" << endl;
    }

public: // 可以多次指定 public 或 private
    void goo() {
        cout << "goo" << endl;
    }
    void fooo() {
        a = 10; // 不会报错，在类内可以访问 private
        foo(); // 不会报错
    }
};

int main() {
    MyClass c;
    c.b = 100; // 不会报错，在类外可以访问 public
    c.goo(); // 不会报错，输出 goo

    // c.a = 100; // 报错，类外不可访问 private
    // c.foo(); // 报错

    c.fooo(); // 不会报错，通过 public 间接访问 private。a 被设为 10, 输出 foo
        
    return 0;
}