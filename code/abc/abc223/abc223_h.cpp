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

using T = tuple<ll, ll, ll, ll>;

vector<ll> op(vector<ll> l, ll r) {
    for (ll x : l) {
        chmin(r, r ^ x);
    }
    if (r)
        l.emplace_back(r);
    return l;
}

vector<ll> op(ll l, vector<ll> r) {
    for (ll x : r) {
        chmin(l, l ^ x);
    }
    if (l)
        r.emplace_back(l);
    return r;
}

vector<ll> op(vector<ll> l, vector<ll> r) {
    if (l.size() > r.size())
        swap(l, r);
    for (ll x : l) {
        for (ll y : r) {
            chmin(x, x ^ y);
        }
        if (x)
            r.emplace_back(x);
    }
    return r;
}

int main(void) {
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    cin >> a;
    vector<T> queries(q);
    rep (i, q) get<0>(queries[i]) = i;
    for (auto &[id, l, r, x] : queries) cin >> l >> r >> x, --l;

    vector<vector<ll>> ans(q);
    auto calc = [&](int L, int M, int R, vector<T> &query) -> void {
        static vector<vector<ll>> dp(n + 1);
        ll min_l = M, max_r = M;
        for (auto &&[id, l, r, x] : query) min_l = std::min(min_l, l), max_r = std::max(max_r, r);
        dp[M] = vector<ll>();
        for (int i = M; i > min_l; --i) dp[i - 1] = op(a[i - 1], dp[i]);
        for (int i = M; i < max_r; ++i) dp[i + 1] = op(dp[i], a[i]);
        for (auto &&[q, l, r, x] : query) ans[q] = op(dp[l], dp[r]);
    };

    auto dfs = [&](auto &dfs, int L, int R, vector<T> &query) -> void {
        if (R - L <= 1) {
            for (auto &&[id, l, r, x] : query) ans[id] = vector<ll>{a[l]};
            return;
        }
        int M = (L + R) / 2;
        vector<T> query_L, query_R, other;
        for (auto &&[id, l, r, x] : query) {
            if (r <= M)
                query_L.emplace_back(id, l, r, x);
            if (M <= l)
                query_R.emplace_back(id, l, r, x);
            if (l < M && M < r)
                other.emplace_back(id, l, r, x);
        }
        calc(L, M, R, other), dfs(dfs, L, M, query_L), dfs(dfs, M, R, query_R);
    };
    dfs(dfs, 0, n, queries);

    for (auto [id, l, r, x] : queries) {
        for (ll y : ans[id]) chmin(x, x ^ y);
        Yes(x == 0);
    }

    return 0;
}
