#include <iostream>
using namespace std;

class A {
public:
    void foo() {
        cout << "A foo()" << endl;
    }
    void goo() {
        cout << "A goo()" << endl;
    }
};

class B : public A {
public:
    void goo() {
        cout << "B goo()" << endl;
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
    cout << endl << "x_point_A:" << endl;
    x_point_A -> foo();
    x_point_A -> goo();
    cout << endl << "x_as_A:" << endl;
    x_as_A.foo();
    x_as_A.goo();
    cout << endl << "x_cut_A:" << endl;
    x_cut_A.foo();
    x_cut_A.goo();
    return 0;
}

/*
x:
A foo()
B goo()

x_point_A:
A foo()
A goo()

x_as_A:
A foo()
A goo()

x_cut_A:
A foo()
A goo()
*/