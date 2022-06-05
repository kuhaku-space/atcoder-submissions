#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/template/template.hpp"
#include <bits/stdc++.h>
using namespace std;
template <class T, class U>
bool chmax(T &a, const U &b) {
    return a < b ? a = b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U &b) {
    return b < a ? a = b, true : false;
}
constexpr int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
const double PI = acos(-1.0);
#line 3 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/template/atcoder.hpp"
using ll = int64_t;
using ld = long double;
#define FOR(i, m, n) for(int i = (m); i < (n); ++i)
#define FORR(i, m, n) for(int i = (m)-1; i >= (n); --i)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FOR(i, 1, n+1)
#define repr(i, n) FORR(i, n, 0)
#define repnr(i, n) FORR(i, n+1, 1)
#define all(s) (s).begin(), (s).end()
template <class T>
istream &operator>>(istream &is, vector<T> &v) { for (T &i : v) is>>i; return is; }
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    for (auto it=v.begin(); it!=v.end(); ++it) { os<<(it==v.begin()?"":" ")<<*it; } return os;
}
template <class Head, class... Tail>
void co(Head&& head, Tail&&... tail) {
    if constexpr(sizeof...(tail)==0) cout<<head<<'\n'; else cout<<head<<' ',co(forward<Tail>(tail)...);
}
template <class Head, class... Tail>
void ce(Head&& head, Tail&&... tail) {
    if constexpr(sizeof...(tail)==0) cerr<<head<<'\n'; else cerr<<head<<' ',ce(forward<Tail>(tail)...);
}
template<typename T, typename... Args>
auto make_vector(T x, int arg, Args ...args) {
    if constexpr(sizeof...(args)==0) return vector<T>(arg, x); else return vector(arg,make_vector<T>(x, args...));
}
void sonic() { ios::sync_with_stdio(false); cin.tie(nullptr); }
void setp(const int n) { cout << fixed << setprecision(n); }
#line 3 "a.cpp"

// Dynamic Segment Tree
template <class T, class F>
struct dynamic_segment_tree {
    struct Node {
        Node *parent, *left, *right;
        T value;

        Node(Node *ptr) : parent(ptr), left(nullptr), right(nullptr), value() {}
    };

    Node *root;
    int64_t N;
    const T e;
    const F op;

    dynamic_segment_tree(int64_t n, T _e, F &&_op) : e(_e), op(_op) {
        init(n);
    }
    dynamic_segment_tree(int64_t n, T _e, const F &_op) : e(_e), op(_op) {
        init(n);
    }

    void init(int64_t n) {
        for (this->N = 1; N < n; this->N <<= 1) {}
        this->root = new Node(nullptr);
    }

    void update(int64_t k, T x) {
        Node *node = this->root;
        int64_t l = 0, r = this->N;
        while (r - l > 1) {
            int64_t m = (l + r) >> 1;
            if (k < m) {
                if (!node->left)
                    node->left = new Node(node);
                node = node->left;
                r = m;
            } else {
                if (!node->right)
                    node->right = new Node(node);
                node = node->right;
                l = m;
            }
        }

        node->value = x;
        while (node->parent) {
            node = node->parent;
            T lvalue = node->left ? node->left->value : e;
            T rvalue = node->right ? node->right->value : e;
            node->value = op(lvalue, rvalue);
        }
    }

    T query() {
        return root->value;
    }
    T query(int64_t a, int64_t b) {
        return this->query(a, b, root, 0, N);
    }
    T query(int64_t a, int64_t b, Node *node, int64_t l, int64_t r) {
        if (a <= l && r <= b)
            return node->value;

        if (r <= a || b <= l)
            return e;

        return op(node->left ? this->query(a, b, node->left, l, (l + r) >> 1) : e,
                  node->right ? this->query(a, b, node->right, (l + r) >> 1, r) : e);
    }
};

struct S {
    double a, b;

    S() : a(1), b(0) {}
    S(double _a, double _b) : a(_a), b(_b) {}
};

S op(S a, S b) {
    return S{b.a * a.a, b.a * a.b + b.b};
}

int main(void) {
    sonic();
    setp(10);
    ll n, m;
    cin >> n >> m;
    auto op = [](auto a, auto b) {
        return S{b.a * a.a, b.a * a.b + b.b};
    };
    dynamic_segment_tree st(n, S(), op);

    double x = 1, y = 1;
    vector<ll> p(m);
    vector<double> a(m), b(m);
    rep(i, m) cin >> p[i] >> a[i] >> b[i];
    rep(i, m) {
        st.update(p[i] - 1, S{a[i], b[i]});
        auto s = st.query();
        chmin(x, s.a + s.b);
        chmax(y, s.a + s.b);
    }
    co(x);
    co(y);

    return 0;
}
