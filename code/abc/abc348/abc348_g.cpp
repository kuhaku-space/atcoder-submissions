#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/home/github/algo/lib/template/template.hpp"
#pragma GCC target("sse4.2,avx2,bmi2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
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
constexpr double PI = M_PI;
#line 3 "/home/kuhaku/home/github/algo/lib/template/macro.hpp"
#define FOR(i, m, n) for (int i = (m); i < int(n); ++i)
#define FORR(i, m, n) for (int i = (m)-1; i >= int(n); --i)
#define FORL(i, m, n) for (int64_t i = (m); i < int64_t(n); ++i)
#define rep(i, n) FOR (i, 0, n)
#define repn(i, n) FOR (i, 1, n + 1)
#define repr(i, n) FORR (i, n, 0)
#define repnr(i, n) FORR (i, n + 1, 1)
#define all(s) (s).begin(), (s).end()
#line 3 "/home/kuhaku/home/github/algo/lib/template/sonic.hpp"
struct Sonic {
    Sonic() {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
        std::cout << std::fixed << std::setprecision(20);
    }

    constexpr void operator()() const {}
} sonic;
#line 5 "/home/kuhaku/home/github/algo/lib/template/atcoder.hpp"
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
#line 3 "a.cpp"

template <class T, class Comp = std::less<T>, class F>
std::vector<int> monotone_minima(int h, int w, F f) {
    Comp comp;
    std::vector<int> dp(h);
    auto dfs = [&](auto self, int top, int bottom, int left, int right) -> void {
        if (top > bottom)
            return;
        if (left == right) {
            for (int i = top; i <= bottom; ++i) dp[i] = left;
            return;
        }
        int line = (top + bottom) / 2;
        T min_val = f(line, left);
        int idx = left;
        for (int i = left + 1; i <= right; i++) {
            T val = f(line, i);
            if (idx == -1 || comp(val, min_val))
                min_val = val, idx = i;
        }
        dp[line] = idx;
        self(self, top, line - 1, left, idx);
        self(self, line + 1, bottom, idx, right);
    };
    dfs(dfs, 0, h - 1, 0, w - 1);
    return dp;
}

template <class T, class Comp = std::less<T>, class F>
std::vector<T> monotone_minima_value(int h, int w, F f) {
    Comp comp;
    std::vector<T> dp(h);
    auto dfs = [&](auto self, int top, int bottom, int left, int right) -> void {
        if (top > bottom)
            return;
        if (left == right) {
            for (int i = top; i <= bottom; ++i) dp[i] = f(i, left);
            return;
        }
        int line = (top + bottom) / 2;
        T min_val = f(line, left);
        int idx = left;
        for (int i = left + 1; i <= right; i++) {
            T val = f(line, i);
            if (idx == -1 || comp(val, min_val))
                min_val = val, idx = i;
        }
        dp[line] = min_val;
        self(self, top, line - 1, left, idx);
        self(self, line + 1, bottom, idx, right);
    };
    dfs(dfs, 0, h - 1, 0, w - 1);
    return dp;
}

std::vector<ll> min_plus_convolution(const vector<ll> &a, const vector<ll> &b) {
    int n = a.size(), m = b.size();
    auto f = [&](int i, int j) {
        if (i < j or i - j >= m)
            return std::numeric_limits<ll>::max();
        return a[j] + b[i - j];
    };
    return monotone_minima_value<ll>(n + m - 1, n, f);
}

std::vector<ll> max_plus_convolution(const vector<ll> &a, const vector<ll> &b) {
    int n = a.size(), m = b.size();
    auto f = [&](int i, int j) {
        if (i < j or i - j >= m)
            return std::numeric_limits<ll>::min();
        return a[j] + b[i - j];
    };
    return monotone_minima_value<ll, greater<>>(n + m - 1, n, f);
}

vector<ll> solve(const vector<pair<ll, ll>> &a, int l, int r) {
    if (r - l == 0) {
        assert(false);
    }
    if (r - l == 1) {
        return {-INF, a[l].first - a[l].second};
    }
    int m = (l + r) / 2;

    auto vl = solve(a, l, m);
    auto vr = solve(a, m, r);
    int len = m - l;
    vector<ll> cs(len + 1);
    for (int i = 0; i < len; ++i) cs[i + 1] = a[l + i].first;
    std::sort(cs.begin() + 1, cs.end(), greater<>());
    for (int i = 0; i < len; ++i) cs[i + 1] += cs[i];
    auto conv = max_plus_convolution(vr, cs);
    for (int i = 0; i < (int)vl.size(); ++i) chmax(conv[i], vl[i]);
    return conv;
}

int main(void) {
    int n;
    cin >> n;
    vector<pair<ll, ll>> a(n);
    cin >> a;
    std::sort(all(a), [](pair<ll, ll> l, pair<ll, ll> r) {
        return l.second < r.second;
    });
    auto ans = solve(a, 0, n);
    repn (i, n) co(ans[i]);

    return 0;
}
