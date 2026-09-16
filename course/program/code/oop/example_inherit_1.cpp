#include <iostream>
using namespace std;

class BaseClass {
public:
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
    c.a = 114;
    c.print();
    return 0;
}