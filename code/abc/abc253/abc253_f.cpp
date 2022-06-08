#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/home/github/algo/lib/template/template.hpp"
#pragma GCC target("sse4.2,avx2,bmi2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
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
constexpr double PI = M_PI;
#line 2 "/home/kuhaku/home/github/algo/lib/segment_tree/monoid.hpp"

template <class T>
struct Add {
    using value_type = T;
    static constexpr T id = T(0);
    static constexpr T op(const T &lhs, const T &rhs) { return lhs + rhs; }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs + rhs;
    }
};

template <class T>
struct And {
    using value_type = T;
    static constexpr T id = T(0);
    static constexpr T op(const T &lhs, const T &rhs) { return lhs & rhs; }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs & rhs;
    }
};

template <class T>
struct Or {
    using value_type = T;
    static constexpr T id = T(0);
    static constexpr T op(const T &lhs, const T &rhs) { return lhs | rhs; }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs | rhs;
    }
};

template <class T>
struct Xor {
    using value_type = T;
    static constexpr T id = T(0);
    static constexpr T op(const T &lhs, const T &rhs) { return lhs ^ rhs; }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs ^ rhs;
    }
};

template <class T>
struct Min {
    using value_type = T;
    static constexpr T id = numeric_limits<T>::max();
    static constexpr T op(const T &lhs, const T &rhs) { return min(lhs, rhs); }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return min((U)lhs, rhs);
    }
};

template <class T>
struct Max {
    using value_type = T;
    static constexpr T id = numeric_limits<T>::min();
    static constexpr T op(const T &lhs, const T &rhs) { return max(lhs, rhs); }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return max((U)lhs, rhs);
    }
};

template <class T>
struct Update {
    using value_type = T;
    static constexpr T id = numeric_limits<T>::max();
    static constexpr T op(const T &lhs, const T &rhs) { return lhs == Update::id ? rhs : lhs; }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs == Update::id ? rhs : lhs;
    }
};
#line 3 "/home/kuhaku/home/github/algo/lib/segment_tree/persistent_dual_segment_tree.hpp"

template <class M>
struct persistent_dual_segment_tree {
  private:
    using T = typename M::value_type;

    struct Node {
        using pointer = Node *;
        T val;
        pointer left, right;

        constexpr Node(T _val) : val(_val), left(), right() {}
        constexpr Node(T _val, pointer _left, pointer _right)
            : val(_val), left(_left), right(_right) {}
    };

  public:
    using node_pointer = typename Node::pointer;

    constexpr persistent_dual_segment_tree() : _size(), root() {}
    constexpr persistent_dual_segment_tree(int n, node_pointer _root) : _size(n), root(_root) {}
    persistent_dual_segment_tree(int n, T e = M::id) : _size(n), root(this->build(0, n, e)) {}
    template <class U>
    persistent_dual_segment_tree(const vector<U> &v)
        : _size(v.size()), root(this->build(0, v.size(), v)) {}

    T operator[](int i) const { return this->get(0, this->_size, i, this->root); }
    T at(int k) const { return this->operator[](k); }
    T get(int k) const { return this->operator[](k); }

    persistent_dual_segment_tree apply(int a, T val) const { return this->apply(a, a + 1, val); }
    persistent_dual_segment_tree apply(int a, int b, T val) const {
        assert(0 <= a && b <= this->_size);
        return persistent_dual_segment_tree(
            this->_size, this->apply(0, this->_size, a, b, val, M::id, this->root));
    }

  private:
    int _size;
    node_pointer root;

    static node_pointer merge(node_pointer left, node_pointer right) {
        return new Node(M::op(left->val, right->val), left, right);
    }

    node_pointer build(int l, int r, T val) const {
        if (l + 1 == r) return new Node(val);
        int m = (l + r) >> 1;
        return this->merge(this->build(l, m, val), this->build(m, r, val));
    }
    template <class U>
    node_pointer build(int l, int r, const vector<U> &v) const {
        if (l + 1 == r) return new Node(v[l]);
        int m = (l + r) >> 1;
        return this->merge(this->build(l, m, v), this->build(m, r, v));
    }

    T get(int l, int r, int k, node_pointer node) const {
        if (l + 1 == r) return node->val;
        int m = (l + r) >> 1;
        if (k < m) return M::op(node->val, this->get(l, m, k, node->left));
        else return M::op(node->val, this->get(m, r, k, node->right));
    }

    node_pointer apply(int l, int r, int a, int b, T val, T prop, node_pointer node) const {
        if (a <= l && r <= b)
            return new Node(M::op(val, M::op(prop, node->val)), node->left, node->right);
        if (b <= l || r <= a) return new Node(M::op(prop, node->val), node->left, node->right);
        int m = (l + r) >> 1;
        return new Node(M::id, this->apply(l, m, a, b, val, M::op(prop, node->val), node->left),
                        this->apply(m, r, a, b, val, M::op(prop, node->val), node->right));
    }
};
#line 3 "/home/kuhaku/home/github/algo/lib/template/atcoder.hpp"
using ll = int64_t;
using ld = long double;
#define FOR(i, m, n) for(int i = (m); i < int(n); ++i)
#define FORR(i, m, n) for(int i = (m)-1; i >= int(n); --i)
#define FORL(i, m, n) for(int64_t i = (m); i < int64_t(n); ++i)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FOR(i, 1, n+1)
#define repr(i, n) FORR(i, n, 0)
#define repnr(i, n) FORR(i, n+1, 1)
#define all(s) (s).begin(), (s).end()
template<class T, class U>
std::istream &operator>>(std::istream &is, std::pair<T, U> &p) { is >> p.first >> p.second; return is; }
template <class T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) { for (T &i : v) is>>i; return is; }
template <class T, class U>
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &p) {
    return os<<'('<<p.first<< ','<<p.second<<')';
}
template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    for (auto it=v.begin(); it!=v.end(); ++it) { os<<(it==v.begin()?"":" ")<<*it; } return os;
}
template <class Head, class... Tail>
void co(Head&& head, Tail&&... tail) {
    if constexpr(sizeof...(tail)==0) std::cout<<head<<'\n'; else std::cout<<head<<' ',co(forward<Tail>(tail)...);
}
template <class Head, class... Tail>
void ce(Head&& head, Tail&&... tail) {
    if constexpr(sizeof...(tail)==0) std::cerr<<head<<'\n'; else std::cerr<<head<<' ',ce(forward<Tail>(tail)...);
}
template<typename T, typename... Args>
auto make_vector(T x, int arg, Args ...args) {
    if constexpr(sizeof...(args)==0) return std::vector<T>(arg,x); else return std::vector(arg,make_vector<T>(x,args...));
}
void sonic() { std::ios::sync_with_stdio(false); std::cin.tie(nullptr); }
void setp(const int n) { std::cout<<std::fixed<<std::setprecision(n); }
void Yes(bool is_correct=true) { std::cout<<(is_correct?"Yes":"No")<<std::endl; }
void No(bool is_not_correct=true) { Yes(!is_not_correct); }
void YES(bool is_correct=true) { std::cout<<(is_correct?"YES":"NO")<<std::endl; }
void NO(bool is_not_correct=true) { YES(!is_not_correct); }
void Takahashi(bool is_correct=true) { std::cout<<(is_correct?"Takahashi":"Aoki")<<std::endl; }
void Aoki(bool is_not_correct=true) { Takahashi(!is_not_correct); }
#line 4 "a.cpp"

int main(void) {
    sonic();
    int n, m, q;
    cin >> n >> m >> q;
    vector<persistent_dual_segment_tree<Add<ll>>> v;
    v.emplace_back(m, 0);
    vector<pair<int, int>> up(n, {0, 0});
    rep(i, q) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            v.emplace_back(v.back().apply(l - 1, r, x));
        } else if (t == 2) {
            int x, y;
            cin >> x >> y;
            up[x - 1] = {i, y};
            v.emplace_back(v.back());
        } else {
            int x, y;
            cin >> x >> y;
            co(up[x - 1].second + v.back().get(y - 1) - v[up[x - 1].first].get(y - 1));
            v.emplace_back(v.back());
        }
    }

    return 0;
}
