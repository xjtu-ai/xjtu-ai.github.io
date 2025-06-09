struct Monomial {
    Monomial *nxt;
    int exp, coeff;
    Monomial() : nxt(nullptr) {}
    Monomial(Monomial *nxt, int exponent, int coefficient)
        : nxt(nxt), exp(exponent), coeff(coefficient) {}
};

class Polynomial {
  private:
    Monomial *content;
    int length;

  public:
    Polynomial() : content(nullptr), length(0) {}
    Polynomial(const Polynomial &x);
    ~Polynomial();
    Polynomial &operator=(const Polynomial &rhs);

    friend Polynomial operator+(const Polynomial &lhs, const Polynomial &rhs);
};

inline Polynomial::Polynomial(const Polynomial &x)
    : content(nullptr), length(x.length) {
    Monomial **tail = &content;
    for (Monomial *p = x.content; p != nullptr; p = p->nxt) {
        *tail = new Monomial(*tail, p->exp, p->coeff);
        tail = &((*tail)->nxt);
    }
}

inline Polynomial::~Polynomial() {
    for (Monomial *p = content; p != nullptr;) {
        Monomial *q = p;
        p = p->nxt;
        delete q;
    }
}

inline Polynomial &Polynomial::operator=(const Polynomial &rhs) {
    for (Monomial *p = content; p != nullptr;) {
        Monomial *q = p;
        p = p->nxt;
        delete q;
    }
    content = nullptr;
    length = rhs.length;
    Monomial **tail = &content;
    for (Monomial *p = rhs.content; p != nullptr; p = p->nxt) {
        *tail = new Monomial(*tail, p->exp, p->coeff);
        tail = &((*tail)->nxt);
    }
    return *this;
}

inline Polynomial operator+(const Polynomial &lhs, const Polynomial &rhs) {
    Polynomial result;
    Monomial *tail = nullptr;    // 指向结果链表的最后一个节点
    Monomial *current = nullptr; // 新节点临时变量
    Monomial *lp = lhs.content, *rp = rhs.content;

    while (lp != nullptr || rp != nullptr) {
        if (lp != nullptr && (rp == nullptr || lp->exp < rp->exp)) {
            // 1. 或 3.：插入lp
            current = new Monomial(nullptr, lp->exp, lp->coeff);
        } else if (rp != nullptr && (lp == nullptr || lp->exp > rp->exp)) {
            // 2. 或 4.：插入rp
            current = new Monomial(nullptr, rp->exp, rp->coeff);
        } else {
            // 5.：指数相等，系数相加
            double new_coeff = lp->coeff + rp->coeff;
            if (new_coeff != 0) {
                current = new Monomial(nullptr, lp->exp, new_coeff);
            } else {
                // 系数相加为0，不插入，继续下一组
                lp = lp->nxt;
                rp = rp->nxt;
                continue;
            }
            lp = lp->nxt;
            rp = rp->nxt;
        }

        // 将新节点加入链表
        if (result.content == nullptr) {
            // 第一个节点
            result.content = current;
            tail = current;
        } else {
            // 非第一个节点，追加到尾部
            tail->nxt = current;
            tail = current;
        }
        result.length++;
    }
    return result;
}