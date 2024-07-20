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
bool is_palindrome_number(ll x) {
    string s = to_string(x);
    if (s.find('0') != string::npos) {
        return false;
    }
    int n = s.size();
    rep (i, n / 2) {
        if (s[i] != s[n - 1 - i])
            return false;
    }
    return true;
}
int main(void) {
    ll n;
    cin >> n;
    vector<ll> v;
    unordered_map<ll, ll> a;
    FOR (x, 2, 1000001) {
        string s = to_string(x);
        if (s.find('0') != string::npos) {
            continue;
        }
        auto t = s;
        reverse(all(t));
        ll y = x * stol(t);
        v.emplace_back(y);
        a[y] = x;
    }
    sort(all(v));
    v.erase(unique(all(v)), v.end());
    unordered_map<ll, bool> mp;
    unordered_map<ll, ll> memo;
    auto dfs = [&](auto self, ll x) -> bool {
        if (is_palindrome_number(x)) {
            memo[x] = x;
            return true;
        }
        if (mp.count(x))
            return mp[x];
        for (auto e : v) {
            if (x < e)
                return false;
            if (x % e == 0) {
                if (self(self, x / e)) {
                    memo[x] = e;
                    return true;
                }
            }
        }
        return false;
    };
    if (!dfs(dfs, n)) {
        co(-1);
        return 0;
    }
    string ans;
    vector<ll> u;
    while (n) {
        if (is_palindrome_number(n)) {
            ans += to_string(n);
            break;
        }
        string s = to_string(a[memo[n]]);
        ans += s;
        ans += '*';
        reverse(all(s));
        u.emplace_back(stol(s));
        n /= memo[n];
    }
    reverse(all(u));
    for (ll e : u) {
        ans += '*';
        ans += to_string(e);
    }
    co(ans);
    return 0;
}
