#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next;
    Node(int val = 0, Node *ptr = NULL) : data(val), next(ptr) {}
};

class List {
  public:
    Node *head; // 头节点
    int len;    // 表长（可选)

    void deepcopy(const List &other) { // 深拷贝
        Node *curOther = other.head->next;
        Node *curThis = head;
        while (curOther != NULL) {
            curThis->next = new Node(curOther->data);
            curThis = curThis->next;
            curOther = curOther->next;
        }
        len = other.len;
    }
    void clear() { // 清空链表
        Node *current = head->next;
        while (current != NULL) {
            Node *n = current->next;
            delete current;
            current = n;
        }
        head->next = NULL; // 防止悬空指针
        len = 0;
    }

    List() : len(0) { head = new Node(); } // 构造函数
    ~List() {
        clear();
        delete head;
    } // 析构函数
    // 拷贝构造函数
    List(const List &other) : len(0) {
        head = new Node();
        deepcopy(other);
    }
    // 赋值运算符重载
    List &operator=(const List &other) {
        if (this != &other) { // 防止自我赋值
            clear();          // 先清空自身
            deepcopy(other);
        }
        return *this;
    }

    int size() { return len; }
    bool isEmpty() { return head->next == NULL; }
    // 在指定位置插入元素（index需在[0, len]内）
    void insert(int data, int index) {
        Node *current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        // 在current后插入新节点
        Node *n = new Node(data, current->next);
        current->next = n;
        len++;
    }
    void insertAtHead(int data) { insert(data, 0); }
    void insertAtTail(int data) { insert(data, len); }
    // 删除指定位置的元素（index需在[0, len-1]内）
    void remove(int index) {
        Node *current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        // 删除current的后继节点
        Node *n = current->next;
        current->next = n->next;
        delete n;
        len--;
    }
    // 返回指定位置的元素（index需在[0, len-1]内）
    int get(int index) const {
        Node *current = head->next;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }
    // 查找指定元素
    // 返回首个匹配元素的索引，如果未找到则返回-1
    int find(int val) {
        Node *current = head->next;
        int index = 0;
        while (current != NULL) {
            if (current->data == val) {
                return index;
            }
            current = current->next;
            index++;
        }
        return -1;
    }
    // 打印链表中的所有元素，依实际需要修改
    void print() {
        if (len == 0) {
            cout << "empty" << endl;
            return;
        }
        Node *current = head->next;
        while (current != NULL) {
            cout << current->data << endl;
            current = current->next;
        }
    }
};