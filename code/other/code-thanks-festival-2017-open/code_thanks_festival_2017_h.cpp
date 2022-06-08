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
#line 2 "/home/kuhaku/home/github/algo/lib/_new/partially_persistent_union_find.hpp"

/**
 * @brief 部分永続Union-Find
 *
 */
struct partially_persistent_union_find {
    partially_persistent_union_find(int _n)
        : _now(0), _data(_n, std::vector<std::pair<int, int>>(1, {0, -1})) {}

    int root(int x, int t) const {
        auto p = this->_data[x].back();
        if (p.first > t || p.second < 0) return x;
        return this->root(p.second, t);
    }
    int get_root(int x, int t) const { return this->root(x, t); }

    bool is_root(int x, int t) const {
        return this->_data[x].back().first > t || this->_data[x].back().second < 0;
    }

    bool same(int x, int y, int t) const { return this->root(x, t) == this->root(y, t); }
    bool is_same(int x, int y, int t) const { return this->same(x, y, t); }

    int size(int x, int t) const {
        x = this->root(x, t);
        return -std::prev(std::upper_bound(this->_data[x].begin(), this->_data[x].end(),
                                           std::pair<int, int>{t, this->_data.size()}))
                    ->second;
    }
    int get_size(int x, int t) const { return this->size(x, t); }

    int unite(int x, int y) {
        ++_now;
        x = this->root(x, _now), y = this->root(y, _now);
        if (x == y) return _now;
        auto p = this->_data[x].back(), q = this->_data[y].back();
        if (p.second > q.second) swap(x, y), swap(p, q);
        this->_data[x].emplace_back(_now, p.second + q.second);
        this->_data[y].emplace_back(_now, x);
        return _now;
    }

  private:
    int _now;
    std::vector<std::vector<std::pair<int, int>>> _data;
};
#line 2 "/home/kuhaku/home/github/algo/lib/_new/persistent_array.hpp"

template <class T, int N = 20>
struct persistent_array {
    struct Node {
        using pointer = Node *;
        T val;
        pointer ch[N] = {};
    };
    using node_pointer = typename Node::pointer;

    constexpr persistent_array() : root() {}
    constexpr persistent_array(node_pointer _root) : root(_root) {}
    constexpr persistent_array(int n, T val) : root() {
        for (int i = 0; i < n; ++i) { this->root = this->set(i, val, this->root); }
    }
    template <class U>
    constexpr persistent_array(const vector<U> &v) : root() {
        for (int i = 0; i < (int)v.size(); ++i) { this->root = this->set(i, v[i], this->root); }
    }

    constexpr T operator[](int i) const noexcept {
        node_pointer node = root;
        while (node) {
            if (i == 0) {
                return node->val;
            } else {
                --i;
                node = node->ch[i % N], i = i / N;
            }
        }
        return T();
    }
    constexpr T at(int k) const noexcept { return this->operator[](k); }
    constexpr T get(int k) const noexcept { return this->operator[](k); }

    persistent_array set(int k, T val) const noexcept {
        return persistent_array(this->set(k, val, root));
    }

  private:
    node_pointer root;

    node_pointer set(int k, T val, node_pointer node) const noexcept {
        node_pointer res = new Node();
        if (node) {
            memcpy(res->ch, node->ch, sizeof(node->ch));
            res->val = node->val;
        }
        if (k == 0) {
            res->val = val;
        } else {
            --k;
            res->ch[k % N] = set(k / N, val, res->ch[k % N]);
        }
        return res;
    }
};
#line 3 "/home/kuhaku/home/github/algo/lib/_new/persistent_union_find.hpp"

struct persistent_union_find {
    constexpr persistent_union_find() : data() {}
    persistent_union_find(const persistent_array<int> &_data) : data(_data) {}
    persistent_union_find(int n) : data(n, -1) {}

    int root(int x) const {
        int y = this->data[x];
        return y < 0 ? x : this->root(y);
    }
    int get_root(int x) const { return this->root(x); }

    bool is_root(int x) const { return this->data[x] < 0; }

    persistent_union_find unite(int x, int y) {
        x = this->root(x), y = this->root(y);
        if (x == y) return *this;
        int a = this->data[x], b = this->data[y];
        if (a > b) swap(x, y);
        return persistent_union_find(this->data.set(x, a + b).set(y, x));
    }

    int size(int x) const { return -(this->data[this->root(x)]); }
    int get_size(int x) const { return this->size(x); }

    bool same(int x, int y) const { return this->root(x) == this->root(y); }
    bool is_same(int x, int y) const { return this->same(x, y); }

  private:
    persistent_array<int> data;
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
#line 5 "a.cpp"

int main(void) {
    sonic();
    int n, m;
    cin >> n >> m;
    vector<persistent_union_find> ufs;
    ufs.emplace_back(persistent_union_find(n));
    rep (i, m) {
        int a, b;
        cin >> a >> b;
        ufs.emplace_back(ufs.back().unite(a - 1, b - 1));
    }
    int q;
    cin >> q;
    rep (i, q) {
        int a, b;
        cin >> a >> b;
        int l = 0, r = m + 1;
        while (r - l > 1) {
            int m = (l + r) >> 1;
            if (ufs[m].same(a - 1, b - 1))
                r = m;
            else
                l = m;
        }
        if (r == m + 1)
            r = -1;
        co(r);
    }

    return 0;
}
