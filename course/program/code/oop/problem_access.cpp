#include <bits/stdc++.h>
using namespace std;

class CodeMonkey;

class ProdoctDog {
    vector<CodeMonkey> coders;
public:
    void add_todolist(CodeMonkey &coder, int x);
    void reduce_todolist(CodeMonkey &coder, int x);
    void add_coder(const CodeMonkey &coder);
    CodeMonkey& find_coder(string name);
    void print_todolists();
};

class CodeMonkey {
private: 
    string name;
    int todolist;
public:
    friend ProdoctDog;
    int sizeof_todolist();
    CodeMonkey(string name, int todolist);
};

void ProdoctDog::add_coder(const CodeMonkey &coder) {
    coders.push_back(coder);
}
CodeMonkey& ProdoctDog::find_coder(string name) {
    for (CodeMonkey &coder : coders) {
        if (coder.name == name) {
            return coder;
        }
    }
}
void ProdoctDog::print_todolists() {
    for (CodeMonkey &coder : coders) {
        cout << coder.name << " " << coder.sizeof_todolist() << endl;
    }
}
void ProdoctDog::add_todolist(CodeMonkey &coder, int x) {
    coder.todolist += x;
}
void ProdoctDog::reduce_todolist(CodeMonkey &coder, int x) {
    coder.todolist -= x;
}

int CodeMonkey::sizeof_todolist() {
    return todolist;
}
CodeMonkey::CodeMonkey(string name, int todolist) : name(name), todolist(todolist) {}

int main() {
    int n, m;
    cin >> n;
    ProdoctDog dog;
    for (int i = 1; i <= n; i++) {
        string s; int x;
        cin >> s >> x;
        dog.add_coder(CodeMonkey(s, x));
    }
    cin >> m;
    while (m--) {
        string s;
        int op, x;
        cin >> s >> op >> x;
        if (op == 0) {
            dog.add_todolist(dog.find_coder(s), x);
        } else {
            dog.reduce_todolist(dog.find_coder(s), x);
        }
    }
    dog.print_todolists();
    return 0;
}
