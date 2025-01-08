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
    int h, w;
    cin >> h >> w;
    vector<string> s(h);
    cin >> s;
    vector dp(h, vector(w, vector(2, Inf)));
    queue<tuple<int, int, int>> que;
    rep (i, h) {
        rep (j, w) {
            if (s[i][j] == 'S') {
                dp[i][j][0] = 0;
                dp[i][j][1] = 0;
                que.emplace(i, j, 0);
                que.emplace(i, j, 1);
            }
        }
    }
    Grid<2> grid(h, w);
    while (!que.empty()) {
        auto [x, y, d] = que.front();
        que.pop();
        if (d == 0) {
            if (grid.in_field(x - 1, y) && s[x - 1][y] != '#' &&
                chmin(dp[x - 1][y][1], dp[x][y][0] + 1))
                que.emplace(x - 1, y, 1);
            if (grid.in_field(x + 1, y) && s[x + 1][y] != '#' &&
                chmin(dp[x + 1][y][1], dp[x][y][0] + 1))
                que.emplace(x + 1, y, 1);
        } else {
            if (grid.in_field(x, y - 1) && s[x][y - 1] != '#' &&
                chmin(dp[x][y - 1][0], dp[x][y][1] + 1))
                que.emplace(x, y - 1, 0);
            if (grid.in_field(x, y + 1) && s[x][y + 1] != '#' &&
                chmin(dp[x][y + 1][0], dp[x][y][1] + 1))
                que.emplace(x, y + 1, 0);
        }
    }
    int ans = Inf;
    rep (i, h) {
        rep (j, w) {
            if (s[i][j] == 'G') {
                chmin(ans, dp[i][j][0]);
                chmin(ans, dp[i][j][1]);
            }
        }
    }
    if (ans == Inf)
        ans = -1;
    co(ans);
    return 0;
}
