#include <bits/stdc++.h>
using namespace std;

class BigInt {
private:
    static const int BASE;
    vector<int> val;
    void maintain();
public:
    BigInt();
    BigInt(int v);
    BigInt(const BigInt &x);

    friend BigInt operator+ (const BigInt &x, const BigInt &y);
    
    friend BigInt operator+ (const BigInt &x);

    friend BigInt& operator++ (BigInt &x); // ++x
    friend BigInt operator++ (BigInt &x, int); // x++

    friend bool operator< (const BigInt &x, const BigInt &y);

    friend BigInt& operator+= (BigInt &x, const BigInt &y);

    friend istream& operator>> (istream &is, BigInt &x);
    friend ostream& operator<< (ostream &os, const BigInt &x);
};

const int BigInt::BASE = 10;

void BigInt::maintain() {
    int c = 0;
    for (int &x : val) {
        x += c;
        c = x / BASE;
        x %= BASE;
    }
    if (c) val.push_back(c);
    while (val.size() > 1 && val.back() == 0) val.pop_back();
}

BigInt::BigInt() {
    val.push_back(0);
}

BigInt::BigInt(int x) {
    val.push_back(x);
    maintain();
}

BigInt::BigInt(const BigInt &x) {
    val = x.val;
}

BigInt operator+(const BigInt &x, const BigInt &y) {
    BigInt res = x;
    for (int i = 0; i < y.val.size(); i++) {
        if (i == res.val.size()) res.val.push_back(y.val[i]);
        else res.val[i] += y.val[i];
    }
    res.maintain();
    return res;
}

BigInt operator+(const BigInt &x) {
    return x;
}

// ++x 单目运算符
BigInt& operator++(BigInt &x) { 
    x.val[0]++;
    x.maintain();
    return x;
}

// x++ 通过后面加上一个无用的隐藏的 int 实现，实际是告诉编译器这是一个后缀++
BigInt operator++(BigInt &x, int) {
    BigInt res = x;
    x.val[0]++;
    x.maintain();
    return res;
}

bool operator<(const BigInt &x, const BigInt &y) {
    if (x.val.size() != y.val.size()) {
        return x.val.size() < y.val.size();
    }
    for (int i = x.val.size() - 1; i >= 0; i--) {
        if (x.val[i] != y.val[i]) {
            return x.val[i] < y.val[i];
        }
    }
    return false;
}

BigInt& operator+=(BigInt &x, const BigInt &y) {
    for (int i = 0; i < y.val.size(); i++) {
        if (i == x.val.size()) x.val.push_back(y.val[i]);
        else x.val[i] += y.val[i];
    }
    x.maintain();
    return x;
}

/*
cin cout 的原理：

cin 是 istream 类的对象。istream 类重载了与许多常见类型的 >> 运算符。
比如重载了 istream::operator>>(istream, int&) 就可以用 cin >> (一个 int 变量)  来输入一个 int

cin 的巧思在于，将 >> 运算符的返回值设为 cin 本身实现连续输入
比如 cin >> a >> b

先执行 cin >> a，输入 a 之后返回 cin 自己，这个 cin 返回值再 >> b，完成对 b 的输入

cout 同理
*/

istream& operator>>(istream &is, BigInt &x) { 
    x.val.clear();
    int ch = is.get();
    while (ch < '0' || ch > '9') ch = is.get();
    while (ch >= '0' && ch <= '9') {
        x.val.push_back(ch - '0');
        ch = is.get();
    }
    reverse(x.val.begin(), x.val.end());
    x.maintain();
    return is;
}

ostream& operator<<(ostream &os, const BigInt &x) {
    for (int i = x.val.size() - 1; i >= 0; i--) {
        os << x.val[i];
    }
    return os;
}

int main() {
    BigInt a, b;
    cin >> a >> b;
    cout << "a < b: " << (a < b) << endl << endl; 
    cout << "a + b: " << a + b << endl;
    cout << "a += b: " << (a += b) << endl;
    cout << "after a += b: " << a << endl << endl;
    cout << "a++: " << (a++) << endl;
    cout << "after a++: " << a << endl << endl;
    cout << "++a: " << (++a) << endl;
    cout << "after ++a: " << a << endl << endl;
    return 0;
}