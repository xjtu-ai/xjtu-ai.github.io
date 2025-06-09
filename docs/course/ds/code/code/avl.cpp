#include <bits/stdc++.h>
using namespace std;

struct AVL_tree {
    struct point {
        int val;
        int height;
        point *ls;
        point *rs;
        point *fa;
        point() {
            val = 0;
            height = 1;
            ls = rs = fa = NULL;
        }
    };
    point *root;
    AVL_tree() { root = NULL; }
    inline void push_up(point *p) {
        if (p != NULL) p->height = max(h(p->ls), h(p->rs)) + 1;
    }
    inline int h(point *p) {
        if (p == NULL) return 0;
        return p->height;
    }
    inline void take_place(point *q, point *p) {
        if (root == p) root = q;
        else if (p->fa->ls == p) p->fa->ls = q;
        else p->fa->rs = q;
        if (q != NULL) q->fa = p->fa;
    }
    point *search(point *p, int val) {
        if (p == NULL || val == p->val) return p;
        if (val < p->val) return search(p->ls, val);
        return search(p->rs, val);
    }
    point *maximum(point *p) {
        while (p->rs != NULL) p = p->rs;
        return p;
    }
    point *minimum(point *p) {
        while (p->ls != NULL) p = p->ls;
        return p;
    }
    void turn_right(point *p) {
        take_place(p->ls, p);
        p->fa = p->ls;
        p->ls = p->fa->rs;
        if (p->fa->rs != NULL) p->fa->rs->fa = p;
        p->fa->rs = p;
    }
    void turn_left(point *p) {
        take_place(p->rs, p);
        p->fa = p->rs;
        p->rs = p->fa->ls;
        if (p->fa->ls != NULL) p->fa->ls->fa = p;
        p->fa->ls = p;
    }
    void balance(point *p) {
        if (h(p->ls) - h(p->rs) == 2) {
            if (h(p->ls->rs) > h(p->ls->ls)) turn_left(p->ls);
            turn_right(p);
        } else if (h(p->ls) - h(p->rs) == -2) {
            if (h(p->rs->ls) > h(p->rs->rs)) turn_right(p->rs);
            turn_left(p);
        }
    }
    void insert(point *r, point *p) {
        if (p->val < r->val) {
            if (r->ls == NULL) {
                r->ls = p;
                p->fa = r;
            } else insert(r->ls, p);
        } else {
            if (r->rs == NULL) {
                r->rs = p;
                p->fa = r;
            } else insert(r->rs, p);
        }
        push_up(r);
        balance(r);
    }
    void ins(int val) {
        point *p = new point();
        p->val = val;
        if (root == NULL) {
            root = p;
            p->fa = NULL;
            return;
        }
        insert(root, p);
    }
    void print(point *p) {
        if (p != NULL) {
            print(p->ls);
            printf("%d ", p->val);
            print(p->rs);
        }
    }
    void del_one(point *p) {
        point *q = p->ls;
        if (q == NULL) q = p->rs;
        take_place(q, p);
        delete p;
    }
    void del(point *p) {
        point *q;
        if (p->ls == NULL || p->rs == NULL) q = p;
        else {
            q = minimum(p->rs);
            p->val = q->val;
        }
        point *r = q->fa;
        del_one(q);
        while (r != NULL) {
            push_up(r);
            balance(r);
            r = r->fa;
        }
    }
    void del(int val) {
        point *p = search(root, val);
        if (p == NULL) return;
        del(p);
    }
};