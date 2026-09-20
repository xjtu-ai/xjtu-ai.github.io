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

void foo(MyClass c) {
    // do some thing
    return;
}

MyClass goo() {
    MyClass d("d");
    return d;
}

int main() {
    cout << "Function goo begins." << endl;
    MyClass a = goo();
    cout << "Function goo ended." << endl << endl;

    cout << "Function foo begins." << endl;
    foo(a);
    cout << "Function foo ended." << endl << endl;
    return 0;
}

/*
Function goo begins.
d has been constructed.
Function goo ended.

Function foo begins.
d has been deconstructed.
Function foo ended.

d has been deconstructed.
*/