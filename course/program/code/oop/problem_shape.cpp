#include <bits/stdc++.h>
using namespace std;

const float PI(3.14159f);

class Shape {
public:
    virtual float square()=0;
    virtual void input()=0;
};

class Circle : public Shape {
private:
    float radius;
public:
    void input() {
        cin >> radius;
    }
    float square() {
        return PI * radius * radius;
    }
};

class Square : public Shape {
private:
    float length;
public:
    void input() {
        cin >> length;
    }
    float square() {
        return length * length;
    }
};

class Rectangle : public Shape {
private:
    float width, height;
public:
    void input() {
        cin >> width >> height;
    }
    float square() {
        return width * height;
    }
};

class Trapezoid : public Shape {
private:
    float lengtha, lengthb, height;
public:
    void input() {
        cin >> lengtha >> lengthb >> height;
    }
    float square() {
        return (lengtha + lengthb) * height / 2;
    }
};

class Triangle : public Shape {
private:
    float length, height;
public:
    void input() {
        cin >> length >> height;
    }
    float square() {
        return length * height / 2;
    }
};

int main() {
    vector<Shape *> vec;
    vec.push_back(new Circle());
    vec.push_back(new Square());
    vec.push_back(new Rectangle());
    vec.push_back(new Trapezoid());
    vec.push_back(new Triangle());

    for (Shape *p : vec) {
        p -> input();
    }

    float sum(0);
    for (Shape *p : vec) {
        sum += p -> square();
    }
    printf("%.3f\n", sum);

    return 0;
}
