#include <functional>
#include <limits>
#include <vector>
template <class T, class Comp = std::less<>, class F>
std::vector<int> monotone_minima(int h, int w, F f) {
    Comp comp;
    std::vector<int> dp(h);
    auto dfs = [&](auto self, int top, int bottom, int left, int right) -> void {
        if (top > bottom) return;
        if (left == right) {
            for (int i = top; i <= bottom; ++i) dp[i] = left;
            return;
        }
        int line = (top + bottom) / 2;
        T min_val = f(line, left);
        int idx = left;
        for (int i = left + 1; i <= right; i++) {
            T val = f(line, i);
            if (comp(val, min_val)) min_val = val, idx = i;
        }
        dp[line] = idx;
        self(self, top, line - 1, left, idx);
        self(self, line + 1, bottom, idx, right);
    };
    dfs(dfs, 0, h - 1, 0, w - 1);
    return dp;
}
template <class T, class Comp = std::less<>, class F>
std::vector<T> monotone_minima_value(int h, int w, F f) {
    Comp comp;
    std::vector<T> dp(h);
    auto dfs = [&](auto self, int top, int bottom, int left, int right) -> void {
        if (top > bottom) return;
        if (left == right) {
            for (int i = top; i <= bottom; ++i) dp[i] = f(i, left);
            return;
        }
        int line = (top + bottom) / 2;
        T min_val = f(line, left);
        int idx = left;
        for (int i = left + 1; i <= right; i++) {
            T val = f(line, i);
            if (comp(val, min_val)) min_val = val, idx = i;
        }
        dp[line] = min_val;
        self(self, top, line - 1, left, idx);
        self(self, line + 1, bottom, idx, right);
    };
    dfs(dfs, 0, h - 1, 0, w - 1);
    return dp;
}
/// @brief min-plus convolution
/// @param b 下に凸
template <class T>
std::vector<T> min_plus_convolution(const std::vector<T> &a, const std::vector<T> &b) {
    int n = a.size(), m = b.size();
    auto f = [&](int i, int j) {
        if (i < j or i - j >= m) return std::numeric_limits<T>::max();
        return a[j] + b[i - j];
    };
    return monotone_minima_value<T>(n + m - 1, n, f);
}
template <class T>
std::vector<T> max_plus_convolution(const std::vector<T> &a, const std::vector<T> &b) {
    int n = a.size(), m = b.size();
    auto f = [&](int i, int j) {
        if (i < j or i - j >= m) return std::numeric_limits<T>::lowest();
        return a[j] + b[i - j];
    };
    return monotone_minima_value<T, std::greater<>>(n + m - 1, n, f);
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
int main(void) {
    int n;
    cin >> n;
    vector<pair<ll, ll>> a(n);
    cin >> a;
    sort(all(a), [](auto p, auto q) {
        return p.second < q.second;
    });
    auto f = [&](auto self, int l, int r) -> vector<ll> {
        if (l + 1 == r) {
            return {-INF, a[l].first - a[l].second};
        }
        int m = (l + r) / 2;
        auto p = self(self, l, m);
        auto q = self(self, m, r);
        priority_queue<ll> pq;
        vector<ll> v(m - l + 1);
        FOR (i, l, m) pq.emplace(a[i].first);
        rep (i, m - l) {
            v[i + 1] = v[i] + pq.top();
            pq.pop();
        }
        auto res = max_plus_convolution(q, v);
        rep (i, m - l + 1) chmax(res[i], p[i]);
        rep (i, r - m + 1) chmax(res[i], q[i]);
        return res;
    };
    auto ans = f(f, 0, n);
    ans.erase(ans.begin());
    co(ans);
    return 0;
}
