// competitive-verifier: PROBLEM
#include <algorithm>
#include <concepts>
#include <optional>
#include <utility>
/// @brief 半開区間
namespace open_interval {
template <std::integral T>
bool is_include(T l1, T r1, T l2, T r2) {
    return (l1 <= l2 && r2 <= r1) || (l2 <= l1 && r1 <= r2);
}
template <std::integral T>
bool is_include(std::pair<T, T> p, std::pair<T, T> q) {
    return is_include(p.first, p.second, q.first, q.second);
}
template <std::integral T>
bool is_intersect(T l1, T r1, T l2, T r2) {
    return std::max(l1, l2) < std::min(r1, r2);
}
template <std::integral T>
bool is_intersect(std::pair<T, T> p, std::pair<T, T> q) {
    return is_intersect(p.first, p.second, q.first, q.second);
}
template <std::integral T>
std::optional<std::pair<T, T>> intersection(T l1, T r1, T l2, T r2) {
    if (is_intersect(l1, r1, l2, r2)) return std::pair{std::max(l1, l2), std::min(r1, r2)};
    else return std::nullopt;
}
template <std::integral T>
std::optional<std::pair<T, T>> intersection(std::pair<T, T> p, std::pair<T, T> q) {
    return intersection(p.first, p.second, q.first, q.second);
}
template <std::integral T>
bool is_disjoint(T l1, T r1, T l2, T r2) {
    return std::min(r1, r2) <= std::max(l1, l2);
}
template <std::integral T>
bool is_disjoint(std::pair<T, T> p, std::pair<T, T> q) {
    return is_disjoint(p.first, p.second, q.first, q.second);
}
}  // namespace open_interval
/// @brief 閉区間
namespace closed_interval {
template <std::integral T>
bool is_include(T l1, T r1, T l2, T r2) {
    return (l1 <= l2 && r2 <= r1) || (l2 <= l1 && r1 <= r2);
}
template <std::integral T>
bool is_include(std::pair<T, T> p, std::pair<T, T> q) {
    return is_include(p.first, p.second, q.first, q.second);
}
template <std::integral T>
bool is_intersect(T l1, T r1, T l2, T r2) {
    return std::max(l1, l2) <= std::min(r1, r2);
}
template <std::integral T>
bool is_intersect(std::pair<T, T> p, std::pair<T, T> q) {
    return is_intersect(p.first, p.second, q.first, q.second);
}
template <std::integral T>
std::optional<std::pair<T, T>> intersection(T l1, T r1, T l2, T r2) {
    if (is_intersect(l1, r1, l2, r2)) return std::pair{std::max(l1, l2), std::min(r1, r2)};
    else return std::nullopt;
}
template <std::integral T>
std::optional<std::pair<T, T>> intersection(std::pair<T, T> p, std::pair<T, T> q) {
    return intersection(p.first, p.second, q.first, q.second);
}
template <std::integral T>
bool is_disjoint(T l1, T r1, T l2, T r2) {
    return std::min(r1, r2) < std::max(l1, l2);
}
template <std::integral T>
bool is_disjoint(std::pair<T, T> p, std::pair<T, T> q) {
    return is_disjoint(p.first, p.second, q.first, q.second);
}
}  // namespace closed_interval
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
    int n, m;
    cin >> n >> m;
    pair<int, int> ans(1, n);
    rep (i, m) {
        int l, r;
        cin >> l >> r;
        auto p = closed_interval::intersection(ans, {l, r});
        if (!p) {
            co(0);
            return 0;
        }
        ans = p.value();
    }
    co(ans.second - ans.first + 1);
    return 0;
}
