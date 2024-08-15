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
std::uint64_t kth_root(std::uint64_t a, std::uint64_t k) {
    if (a == 0 || a == 1 || k == 1)
        return a;
    if (k >= 64)
        return 1;
    if (k >= 41) {
        if (a >= (1ull << k))
            return 2;
        else
            return 1;
    }
    if (k == 2)
        return (std::uint64_t)sqrtl(a);
    std::uint64_t l = 0, r = (std::uint64_t)std::numeric_limits<std::uint32_t>::max() + 1;
    while (r - l > 1) {
        std::uint64_t m = (l + r) / 2;
        __uint128_t q = 1;
        for (int i = 0; i < k; ++i) {
            q *= m;
            if (q > a)
                break;
        }
        if (q <= a)
            l = m;
        else
            r = m;
    }
    return l;
}
__uint128_t pow_int(std::uint64_t x, std::uint64_t p) {
    __uint128_t res = 1;
    for (int i = 0; i < p; ++i) {
        res *= x;
    }
    return res;
}
int main(void) {
    ll n, a;
    cin >> n >> a;
    ll ans = n;
    FOR (k, 2, 64) {
        ll x = kth_root(n, k);
        rep (i, k + 1) {
            if (pow_int(x, i) * pow_int(x + 1, k - i) >= n) {
                chmin(ans, a * (k - 1) + x * i + (x + 1) * (k - i));
            }
        }
    }
    co(ans);
    return 0;
}
