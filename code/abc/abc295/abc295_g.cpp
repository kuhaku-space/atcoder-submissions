#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/atcoder/github/algo/lib/template/template.hpp"
#pragma GCC target("sse4.2,avx2,bmi2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
template <class T, class U>
bool chmax(T &a, const U &b) {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U &b) {
    return (T)b < a ? a = (T)b, true : false;
}
constexpr int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
constexpr double PI = M_PI;
#line 3 "/home/kuhaku/atcoder/github/algo/lib/template/macro.hpp"
#define FOR(i, m, n) for (int i = (m); i < int(n); ++i)
#define FORR(i, m, n) for (int i = (m)-1; i >= int(n); --i)
#define FORL(i, m, n) for (int64_t i = (m); i < int64_t(n); ++i)
#define rep(i, n) FOR (i, 0, n)
#define repn(i, n) FOR (i, 1, n + 1)
#define repr(i, n) FORR (i, n, 0)
#define repnr(i, n) FORR (i, n + 1, 1)
#define all(s) (s).begin(), (s).end()
#line 3 "/home/kuhaku/atcoder/github/algo/lib/template/sonic.hpp"
struct Sonic {
    Sonic() {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
    }

    constexpr void operator()() const {}
} sonic;
#line 5 "/home/kuhaku/atcoder/github/algo/lib/template/atcoder.hpp"
using ll = int64_t;
using ld = long double;
template <class T, class U>
std::istream &operator>>(std::istream &is, std::pair<T, U> &p) {
    return is >> p.first >> p.second;
}
template <class T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) {
    for (T &i : v) is >> i;
    return is;
}
template <class T, class U>
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &p) {
    return os << '(' << p.first << ',' << p.second << ')';
}
template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    for (auto it = v.begin(); it != v.end(); ++it) {
        os << (it == v.begin() ? "" : " ") << *it;
    }
    return os;
}
template <class Head, class... Tail>
void co(Head &&head, Tail &&...tail) {
    if constexpr (sizeof...(tail) == 0) std::cout << head << '\n';
    else std::cout << head << ' ', co(std::forward<Tail>(tail)...);
}
template <class Head, class... Tail>
void ce(Head &&head, Tail &&...tail) {
    if constexpr (sizeof...(tail) == 0) std::cerr << head << '\n';
    else std::cerr << head << ' ', ce(std::forward<Tail>(tail)...);
}
template <typename T, typename... Args>
auto make_vector(T x, int arg, Args... args) {
    if constexpr (sizeof...(args) == 0) return std::vector<T>(arg, x);
    else return std::vector(arg, make_vector<T>(x, args...));
}
void setp(int n) {
    std::cout << std::fixed << std::setprecision(n);
}
void Yes(bool is_correct = true) {
    std::cout << (is_correct ? "Yes" : "No") << '\n';
}
void No(bool is_not_correct = true) {
    Yes(!is_not_correct);
}
void YES(bool is_correct = true) {
    std::cout << (is_correct ? "YES" : "NO") << '\n';
}
void NO(bool is_not_correct = true) {
    YES(!is_not_correct);
}
void Takahashi(bool is_correct = true) {
    std::cout << (is_correct ? "Takahashi" : "Aoki") << '\n';
}
void Aoki(bool is_not_correct = true) {
    Takahashi(!is_not_correct);
}
#line 2 "/home/kuhaku/atcoder/github/algo/lib/tree/union_find.hpp"

/**
 * @brief 素集合データ構造
 * @details Implement (union by size) + (path compression)
 * @see https://github.com/atcoder/ac-library/blob/master/atcoder/dsu.hpp
 */
struct union_find {
    union_find() : data() {}
    union_find(int _n) : data(_n, -1) {}

    int root(int x) { return this->data[x] < 0 ? x : this->data[x] = this->root(this->data[x]); }
    int get_root(int x) { return this->root(x); }

    bool is_root(int x) const { return this->data[x] < 0; }

    bool same(int x, int y) { return this->root(x) == this->root(y); }
    bool is_same(int x, int y) { return this->same(x, y); }

    int size(int x) { return -(this->data[this->root(x)]); }
    int get_size(int x) { return this->size(x); }

    bool unite(int x, int y) {
        x = this->root(x), y = this->root(y);
        if (x == y) return false;
        if (this->data[x] > this->data[y]) swap(x, y);
        this->data[x] += this->data[y];
        this->data[y] = x;
        return true;
    }

    template <class F>
    bool unite(int x, int y, F f) {
        x = this->root(x), y = this->root(y);
        if (x != y) {
            if (this->data[x] > this->data[y]) swap(x, y);
            this->data[x] += this->data[y];
            this->data[y] = x;
        }
        f(x, y);
        return x != y;
    }

  private:
    std::vector<int> data;
};
#line 4 "a.cpp"

int main(void) {
    int n;
    cin >> n;
    vector<int> p(n - 1);
    cin >> p;
    p.emplace(p.begin(), 0);
    for_each(all(p), [&](int &x) {
        --x;
    });

    int q;
    cin >> q;
    vector<int> x(n);
    iota(all(x), 0);
    union_find uf(n);
    while (q--) {
        int c;
        cin >> c;
        if (c == 1) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            u = x[uf.root(u)];
            v = x[uf.root(v)];
            while (!uf.same(u, v)) {
                int a = x[uf.root(u)];
                int b = x[uf.root(p[u])];
                uf.unite(u, p[u]);
                chmin(x[uf.root(u)], min(a, b));
                u = x[uf.root(u)];
            }
        } else {
            int v;
            cin >> v;
            --v;
            co(x[uf.root(v)] + 1);
        }
    }

    return 0;
}
