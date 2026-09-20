#include <iostream>
using namespace std;

class A {
public:
    virtual void foo() {
        cout << "A foo()" << endl;
    }
    virtual void goo() {
        cout << "A goo()" << endl;
    }
};

class B : public A {
public:
    virtual void goo() {
        cout << "B goo()" << endl;
    };
    virtual void hoo() {
        cout << "B hoo()" << endl;
    };
};

int main() {
    B x;
    A *x_point_A = &x;
    A &x_as_A = x;
    A x_cut_A = x;
    cout << "x:" << endl;
    x.foo();
    x.goo();
    x.hoo();
    cout << endl << "x_point_A:" << endl;
    x_point_A -> foo();
    x_point_A -> goo();
    // x_point_A -> hoo(); // 编译错误
    cout << endl << "x_as_A:" << endl;
    x_as_A.foo();
    x_as_A.goo();
    // x_as_A.hoo(); // 编译错误
    cout << endl << "x_cut_A:" << endl;
    x_cut_A.foo();
    x_cut_A.goo();
    // x_cut_A.hoo(); // 编译错误
    return 0;
}

/*
x:
A foo()
B goo()
B hoo()

x_point_A:
A foo()
B goo()

x_as_A:
A foo()
B goo()

x_cut_A:
A foo()
A goo()
*/