#include <bits/stdc++.h>
using namespace std;

class Matrix {
private:
    int row;
    int column;
    int **mat;
public:
    Matrix(int r, int c) {
        row = r;
        column = c;
        mat = new int *[r];
        for (int i = 0; i < r; i++) {
            mat[i] = new int[c];
        }
    }
    void set(int i, int j, int v) {
        mat[i][j] = v;
    }
    ~Matrix() {
        for (int i = 0; i < row; i++) {
            delete mat[i];
        }
        delete mat;
    }
    void display() {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                cout<<setw(10)<<mat[i][j];
            }
            cout << endl;
        }
    }
    friend Matrix operator*(const Matrix &a, const Matrix &b);
};

Matrix operator*(const Matrix &a, const Matrix &b) {
    if (a.column == 1 && a.row == 1) {
        Matrix res(b.row, b.column);
        for (int i = 0; i < res.row; i++) {
            for (int j = 0; j < res.column; j++) {
                res.mat[i][j] = b.mat[i][j] * a.mat[0][0];
            } 
        }
        return res;
    }
    if (b.column == 1 && b.row == 1) {
        Matrix res(a.row, a.column);
        for (int i = 0; i < res.row; i++) {
            for (int j = 0; j < res.column; j++) {
                res.mat[i][j] = a.mat[i][j] * b.mat[0][0];
            } 
        }
        return res;
    }
    Matrix res(a.row, b.column);
    for (int i = 0; i < res.row; i++) {
        for (int j = 0; j < res.column; j++) {
            res.mat[i][j] = 0;
            for (int k = 0; k < a.column; k++) {
                res.mat[i][j] += a.mat[i][k] * b.mat[k][j];
            }
        }
    }
    return res;
}

int main() {
    int r1, c1, r2, c2;
    cin >> r1 >> c1; Matrix m1(r1, c1);
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++) {
            int x; cin >> x;
            m1.set(i, j, x);
        }
    }
    cin >> r2 >> c2; Matrix m2(r2, c2);
    for (int i = 0; i < r2; i++) {
        for (int j = 0; j < c2; j++) {
            int x; cin >> x;
            m2.set(i, j, x);
        }
    }
    if (c1 == r2 || (c1 == 1 && r1 == 1)) {
        Matrix m3 = m1 * m2;
        m3.display();
    } else cout << "Invalid Matrix multiplication!" << endl;
    return 0;
}