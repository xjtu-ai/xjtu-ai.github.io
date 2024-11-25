#include <queue>
#include <iostream>
using namespace std;

class MyQueue : public queue<int> {
public:
    int pop() {
        int res = front();
        queue<int>::pop();
        return res;
    }
};

int main() {
    int n;
    cin >> n;
    MyQueue q;
    while (n--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x;
            cin >> x;
            q.push(x);
        } else if (op == 2) {
            if (!q.empty()) {
                cout << q.pop() << endl;
            } else {
                cout << "Invalid" << endl;
            }
        } else {
            cout << q.size() << endl;
        }
    }
    return 0;
}
