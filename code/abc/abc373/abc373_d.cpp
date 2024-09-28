// competitive-verifier: PROBLEM
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
/**
 * @brief 重み付き素集合データ構造
 *
 * @tparam T
 */
template <class T>
struct weighted_union_find {
    weighted_union_find() {}
    weighted_union_find(int size) : _data(size, -1), _weights(size) {}
    int find(int k) {
        if (_data[k] < 0) return k;
        int par = find(_data[k]);
        _weights[k] += _weights[_data[k]];
        return _data[k] = par;
    }
    T get_weight(int t) {
        find(t);
        return _weights[t];
    }
    bool same(int x, int y) { return find(x) == find(y); }
    bool is_same(int x, int y) { return same(x, y); }
    int size(int x) { return -_data[find(x)]; }
    /**
     * @brief get diff between x and y
     *
     * @param x
     * @param y
     * @return T v[y] - v[x]
     */
    T diff(int x, int y) { return get_weight(y) - get_weight(x); }
    T get_diff(int x, int y) { return diff(x, y); }
    /**
     * @brief v[y] = v[x] + w
     *
     * @param x
     * @param y
     * @param w
     * @return true unite correctly
     * @return false already united
     */
    bool unite(int x, int y, T w) {
        w += get_weight(x) - get_weight(y);
        x = find(x), y = find(y);
        if (x == y) return false;
        if (_data[x] > _data[y]) {
            std::swap(x, y);
            w = -w;
        }
        _data[x] += _data[y];
        _data[y] = x;
        _weights[y] = w;
        return true;
    }
  private:
    std::vector<int> _data;
    std::vector<T> _weights;
};
int main(void) {
    int n, m;
    cin >> n >> m;
    weighted_union_find<ll> uf(n);
    rep (i, m) {
        int u, v, w;
        cin >> u >> v >> w;
        uf.unite(u - 1, v - 1, w);
    }
    vector<ll> ans(n);
    rep (i, n) {
        ans[i] = uf.diff(uf.find(i), i);
    }
    co(ans);
    return 0;
}
