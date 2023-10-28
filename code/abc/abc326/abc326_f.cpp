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

pair<bool, ll> ok(vector<ll> v, ll s) {
    int n = v.size();
    if (n < 2) {
        rep (bit, 1 << n) {
            ll x = 0;
            rep (i, n) {
                if (bit >> i & 1)
                    x -= v[i];
                else
                    x += v[i];
            }
            if (x == s)
                return {true, bit};
        }
        return {false, 0};
    }
    int n1 = v.size() / 2;
    int n2 = v.size() - n1;
    unordered_map<ll, ll> mp;
    rep (bit, 1 << n1) {
        ll x = 0;
        rep (i, n1) {
            if (bit >> i & 1)
                x -= v[i];
            else
                x += v[i];
        }
        mp[x] = bit;
    }
    rep (bit, 1 << n2) {
        ll x = 0;
        rep (i, n2) {
            if (bit >> i & 1)
                x -= v[n1 + i];
            else
                x += v[n1 + i];
        }
        if (mp.count(s - x)) {
            return {true, (ll)bit << n1 | mp[s - x]};
        }
    }
    return {false, 0};
}

int main(void) {
    int n;
    cin >> n;
    ll x, y;
    cin >> x >> y;
    vector<ll> a(n);
    cin >> a;
    vector<ll> xs, ys;
    rep (i, n) {
        if (i & 1)
            xs.emplace_back(a[i]);
        else
            ys.emplace_back(a[i]);
    }
    auto p = ok(xs, x);
    auto q = ok(ys, y);
    // ce(p.second, q.second);
    if (!p.first || !q.first) {
        No();
        return 0;
    }
    Yes();
    vector<int> f(n + 1);
    rep (i, n) {
        if (i & 1) {
            f[i + 1] = 2 * (p.second >> (i / 2) & 1);
        } else {
            f[i + 1] = 2 * (q.second >> (i / 2) & 1) + 1;
        }
    }
    string ans;
    rep (i, n) {
        if ((f[i + 1] - f[i] + 4) % 4 == 1) {
            ans += 'L';
        } else {
            ans += 'R';
        }
    }
    co(ans);

    return 0;
}
