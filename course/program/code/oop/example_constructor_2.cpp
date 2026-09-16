#include <iostream>
#include <string>
using namespace std;

class MyClass {
private:
    string name;
public:
    MyClass(string name) : name(name) {
        cout << name << " has been constructed." << endl;
    }

    ~MyClass() {
        cout << name << " has been deconstructed." << endl;
    }
};

void foo() {
    MyClass c("c");
}

int main() {
    MyClass a("a");

    cout << "Code block begins." << endl;
    {
        MyClass b("b");
    }
    cout << "Code block ended." << endl << endl;

    cout << "Function foo begins." << endl;
    foo();
    cout << "Function foo ended." << endl << endl;
    return 0;
}

/*
a has been constructed.
Code block begins.
b has been constructed.
b has been deconstructed.
Code block ended.

Function foo begins.
c has been constructed.
c has been deconstructed.
Function foo ended.

a has been deconstructed.
*/