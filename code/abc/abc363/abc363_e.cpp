// competitive-verifier: PROBLEM
#include <cstdint>
#include <utility>
namespace internal {
template <int Idx>
struct grid_impl {
    template <class Head, class... Tail>
    constexpr grid_impl(Head &&head, Tail &&...tail)
        : limit(head), impl(std::forward<Tail>(tail)...) {}
    template <class Head, class... Tail>
    constexpr bool in_field(Head x, Tail &&...tail) const {
        return 0 <= x && x < limit && impl.in_field(std::forward<Tail>(tail)...);
    }
    template <class Head, class... Tail>
    constexpr std::int64_t flatten(Head x, Tail &&...tail) const {
        return x + limit * impl.flatten(std::forward<Tail>(tail)...);
    }
  private:
    std::int64_t limit;
    grid_impl<Idx - 1> impl;
};
template <>
struct grid_impl<0> {
    constexpr grid_impl() {}
    constexpr bool in_field() const { return true; }
    constexpr std::int64_t flatten() const { return 0; }
};
}  // namespace internal
template <int Idx>
struct Grid {
    template <class... Args, std::enable_if_t<(sizeof...(Args) == Idx)> * = nullptr>
    constexpr Grid(Args &&...args) : entity(std::forward<Args>(args)...) {}
    template <class... Args, std::enable_if_t<(sizeof...(Args) == Idx)> * = nullptr>
    constexpr bool in_field(Args &&...args) const {
        return entity.in_field(std::forward<Args>(args)...);
    }
    template <class... Args, std::enable_if_t<(sizeof...(Args) == Idx)> * = nullptr>
    constexpr std::int64_t flatten(Args &&...args) const {
        return entity.flatten(std::forward<Args>(args)...);
    }
  private:
    internal::grid_impl<Idx> entity;
};
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
int main(void) {
    int h, w, y;
    cin >> h >> w >> y;
    Grid<2> grid(h, w);
    vector a(h, vector(w, 0));
    cin >> a;
    int m = 0;
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
    vector used(h, vector(w, true));
    rep (i, h) {
        if (used[i][0]) {
            used[i][0] = false;
            pq.emplace(a[i][0], i, 0);
        }
        if (used[i][w - 1]) {
            used[i][w - 1] = false;
            pq.emplace(a[i][w - 1], i, w - 1);
        }
    }
    rep (j, w) {
        if (used[0][j]) {
            used[0][j] = false;
            pq.emplace(a[0][j], 0, j);
        }
        if (used[h - 1][j]) {
            used[h - 1][j] = false;
            pq.emplace(a[h - 1][j], h - 1, j);
        }
    }
    vector<int> dx = {1, -1, 0, 0}, dy = {0, 0, 1, -1};
    vector ans(h, vector(w, 0));
    while (!pq.empty()) {
        auto [e, x, y] = pq.top();
        pq.pop();
        chmax(m, e);
        ans[x][y] = m;
        rep (k, 4) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (grid.in_field(nx, ny) && used[nx][ny]) {
                used[nx][ny] = false;
                pq.emplace(a[nx][ny], nx, ny);
            }
        }
    }
    vector<int> v(100001);
    rep (i, h) {
        rep (j, w) {
            v[ans[i][j] - 1]++;
        }
    }
    repr (i, 100000) v[i] += v[i + 1];
    repn (i, y) co(v[i]);
    return 0;
}
