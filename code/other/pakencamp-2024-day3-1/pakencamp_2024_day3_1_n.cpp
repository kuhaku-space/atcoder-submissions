// competitive-verifier: PROBLEM
#include <cstdint>
#include <vector>
#include <iostream>
/**
 * @brief 隣接行列
 *
 * @tparam T
 */
template <class T>
struct matrix_graph {
    matrix_graph(int v, T e = T()) : _size(v), m(v, std::vector<T>(v, e)) {}
    const auto &operator[](int i) const { return m[i]; }
    auto &operator[](int i) { return m[i]; }
    const auto begin() const { return m.begin(); }
    auto begin() { return m.begin(); }
    const auto end() const { return m.end(); }
    auto end() { return m.end(); }
    constexpr int size() const { return _size; }
    void add_edge(int a, int b, T d = T(1)) { m[a][b] = d; }
    void add_edges(int a, int b, T d = T(1)) { m[a][b] = m[b][a] = d; }
    void input_edge(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            T weight;
            std::cin >> from >> to >> weight;
            add_edge(from - base, to - base, weight);
        }
    }
    void input_edges(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            T weight;
            std::cin >> from >> to >> weight;
            add_edges(from - base, to - base, weight);
        }
    }
  private:
    int _size;
    std::vector<std::vector<T>> m;
};
template <>
struct matrix_graph<void> {
    matrix_graph(int v) : _size(v), m(v, std::vector<bool>(v)) {}
    const auto &operator[](int i) const { return m[i]; }
    auto &operator[](int i) { return m[i]; }
    const auto begin() const { return m.begin(); }
    auto begin() { return m.begin(); }
    const auto end() const { return m.end(); }
    auto end() { return m.end(); }
    constexpr int size() const { return _size; }
    void add_edge(int a, int b) { m[a][b] = true; }
    void add_edges(int a, int b) { m[a][b] = m[b][a] = true; }
    void input_edge(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            std::cin >> from >> to;
            add_edge(from - base, to - base);
        }
    }
    void input_edges(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            std::cin >> from >> to;
            add_edges(from - base, to - base);
        }
    }
    void complement() {
        for (int i = 0; i < _size; ++i) {
            for (int j = 0; j < _size; ++j) m[i][j] = !m[i][j];
        }
    }
  private:
    int _size;
    std::vector<std::vector<bool>> m;
};
/**
 * @brief 彩色数を求める
 * @details $O(2^N)$
 *
 * @param G グラフ
 * @return int 彩色数
 */
int chromatic_number(const matrix_graph<void> &G) {
    constexpr std::int64_t _MOD = (1LL << 31) - 1;
    int n = G.size();
    std::vector<int> neighbor(n, 0);
    for (int i = 0; i < n; ++i) {
        int s = 1 << i;
        for (int j = 0; j < n; ++j) {
            if (G[i][j]) s |= 1 << j;
        }
        neighbor[i] = s;
    }
    std::vector<int> v(1 << n);
    v[0] = 1;
    for (int s = 1; s < 1 << n; ++s) {
        int c = __builtin_ctz(s);
        v[s] = v[s & ~(1 << c)] + v[s & ~neighbor[c]];
    }
    auto _mod = [](std::int64_t a) -> std::int64_t {
        a = (a & _MOD) + (a >> 31);
        return a >= _MOD ? a - _MOD : a;
    };
    auto _pow = [](auto f, std::int64_t a, int n) {
        std::int64_t res = 1;
        for (; n > 0; n >>= 1) {
            if (n & 1) res = f(res * a);
            a = f(a * a);
        }
        return res;
    };
    int low = 0, high = n;
    while (high - low > 1) {
        int mid = (low + high) >> 1;
        std::int64_t g = 0;
        for (int s = 0; s < 1 << n; ++s) {
            if ((n - __builtin_popcount(s)) & 1) g = _mod(g + _MOD - _pow(_mod, v[s], mid));
            else g = _mod(g + _pow(_mod, v[s], mid));
        }
        if (g != 0) high = mid;
        else low = mid;
    }
    return high;
}
#ifdef ATCODER
#pragma GCC target("sse4.2,avx512f,avx512dq,avx512ifma,avx512cd,avx512bw,avx512vl,bmi2")
#endif
#pragma GCC optimize("Ofast,fast-math,unroll-all-loops")
#include <bits/stdc++.h>
#ifndef ATCODER
#pragma GCC target("sse4.2,avx2,bmi2")
#endif
template <class T, class U>
constexpr bool chmax(T &a, const U &b) {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
constexpr bool chmin(T &a, const U &b) {
    return (T)b < a ? a = (T)b, true : false;
}
constexpr std::int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr double EPS = 1e-7;
constexpr double PI = 3.14159265358979323846;
#define FOR(i, m, n) for (int i = (m); i < int(n); ++i)
#define FORR(i, m, n) for (int i = (m)-1; i >= int(n); --i)
#define FORL(i, m, n) for (int64_t i = (m); i < int64_t(n); ++i)
#define rep(i, n) FOR (i, 0, n)
#define repn(i, n) FOR (i, 1, n + 1)
#define repr(i, n) FORR (i, n, 0)
#define repnr(i, n) FORR (i, n + 1, 1)
#define all(s) (s).begin(), (s).end()
struct Sonic {
    Sonic() {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
        std::cout << std::fixed << std::setprecision(20);
    }
    constexpr void operator()() const {}
} sonic;
using namespace std;
using ll = std::int64_t;
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
    for (auto it = v.begin(); it != v.end(); ++it) os << (it == v.begin() ? "" : " ") << *it;
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
void Yes(bool is_correct = true) { std::cout << (is_correct ? "Yes\n" : "No\n"); }
void No(bool is_not_correct = true) { Yes(!is_not_correct); }
void YES(bool is_correct = true) { std::cout << (is_correct ? "YES\n" : "NO\n"); }
void NO(bool is_not_correct = true) { YES(!is_not_correct); }
void Takahashi(bool is_correct = true) { std::cout << (is_correct ? "Takahashi" : "Aoki") << '\n'; }
void Aoki(bool is_not_correct = true) { Takahashi(!is_not_correct); }
void solve() {
    int n, m;
    cin >> n >> m;
    matrix_graph<void> g(n);
    g.input_edges(m);
    co(chromatic_number(g));
}
int main(void) {
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
