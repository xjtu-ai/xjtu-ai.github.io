#include <bits/stdc++.h>
using namespace std;


struct MyPower {
    int val;
    MyPower(int val) : val(val) {}
};
struct MyInt {
    int val;
    MyInt(int val) : val(val) {}
};

MyPower operator *(const MyInt &x) {
    return MyPower(x.val);
}

int quick_power(int x, int p) {
    if (p == 1) return x;
    int y = quick_power(x, p / 2);
    int res = y * y;
    if (p % 2 == 1) res = res * x;
    return res;
}

MyInt operator *(const MyInt &x, const MyPower &y) {
    return MyInt(quick_power(x.val, y.val));
}

ostream& operator<<(ostream &os, const MyInt &x) {
    return (os << x.val);
}

int main() {
    MyInt a(3), b(4);
    cout << a ** b << endl;
    return 0;
}
// 输出 3 的 4 次方 81