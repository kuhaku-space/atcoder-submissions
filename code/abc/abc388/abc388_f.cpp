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
int main(void) {
    ll n;
    int m, a, b;
    cin >> n >> m >> a >> b;
    vector<ll> l(m), r(m);
    rep (i, m) cin >> l[i] >> r[i];
    if (m) {
        int t1 = 0, t2 = 1;
        while (t2 < m) {
            if (r[t1] + 1 == l[t2]) {
                r[t1] = r[t2];
            } else {
                ++t1;
                l[t1] = l[t2];
                r[t1] = r[t2];
            }
            ++t2;
        }
        l.erase(l.begin() + t1 + 1, l.end());
        r.erase(r.begin() + t1 + 1, r.end());
        m = l.size();
    }
    rep (i, m) {
        if (r[i] - l[i] + 1 >= b) {
            No();
            return 0;
        }
    }
    if (a == b) {
        if ((n - 1) % a != 0) {
            No();
            return 0;
        }
        rep (i, m) {
            ll x = l[i];
            while (x <= r[i]) {
                if ((x - 1) % a == 0) {
                    No();
                    return 0;
                }
                ++x;
            }
        }
        Yes();
        return 0;
    }
    vector<bool> dp(10000);
    dp[0] = true;
    rep (i, 10000) {
        if (!dp[i])
            continue;
        FOR (j, a, b + 1) {
            if (i + j < 10000)
                dp[i + j] = true;
        }
    }
    ll x = 1;
    vector<bool> v(50);
    v[0] = true;
    rep (i, m) {
        vector<bool> u(50);
        rep (j, 50) {
            rep (k, 50) {
                ll p = x + j;
                ll q = l[i] - 1 - k;
                if (p > q)
                    continue;
                if (v[j] && q - p >= 10000) {
                    u[k] = true;
                } else if (v[j]) {
                    u[k] = dp[q - p];
                }
            }
        }
        vector<bool> w(50);
        rep (j, 50) {
            rep (k, 50) {
                ll d = r[i] + 1 + k - (l[i] - 1 - j);
                if (u[j] && a <= d && d <= b)
                    w[k] = true;
            }
        }
        rep (j, 50) {
            rep (k, 50) {
                if (v[j] && x + j == r[i] + 1 + k)
                    w[k] = true;
            }
        }
        x = r[i] + 1;
        v = w;
    }
    rep (i, 50) {
        ll d = n - (x + i);
        if (d < 0)
            continue;
        if (v[i] && d >= 10000) {
            Yes();
            return 0;
        } else if (v[i] && dp[d]) {
            Yes();
            return 0;
        }
    }
    No();
    return 0;
}
