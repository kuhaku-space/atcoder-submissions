#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/home/github/algo/lib/template/template.hpp"
#pragma GCC target("sse4.2,avx2,bmi2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
template <class T, class U>
bool chmax(T &a, const U &b) {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U &b) {
    return (T)b < a ? a = (T)b, true : false;
}
constexpr std::int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
constexpr double PI = M_PI;
#line 2 "/home/kuhaku/home/github/algo/lib/string/z_algorithm.hpp"

/**
 * @brief Z algorithm
 *
 * @tparam Container
 *
 * @see https://snuke.hatenablog.com/entry/2014/12/03/214243
 *
 * Z[i] := S[i:Z[i]] == S[0:Z[i]-i]
 */
template <class Container>
std::vector<int> z_algorithm(const Container &s) {
    int n = s.size();
    std::vector<int> res(n);
    res[0] = n;
    int i = 1, j = 0;
    while (i < n) {
        while (i + j < n && s[j] == s[i + j]) ++j;
        res[i] = j;
        if (!j) {
            ++i;
            continue;
        }
        int k = 1;
        while (i + k < n && k + res[k] < j) res[i + k] = res[k], ++k;
        i += k, j -= k;
    }
    return res;
}
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
void setp(int n) {
    std::cout << std::fixed << std::setprecision(n);
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
#line 4 "a.cpp"

int repetition(const string &s) {
    auto z = z_algorithm(s);
    int n = s.size();
    for (int i = 1; i <= n / 2; ++i) {
        if (n % i == 0 && z[i] == n - i)
            return i;
    }
    return n;
}

vector<int> solve(const vector<int> &v) {
    int n = v.size();
    unordered_map<int, int> mp;
    unordered_set<int> st;
    vector<int> res;
    for (auto x : v) {
        int y = x;
        if (mp.count(x))
            y = mp[x];
        while (st.count(y)) y += x;
        mp[x] = y;
        res.emplace_back(y);
        st.emplace(y);
    }
    return res;
}

int main(void) {
    int n;
    cin >> n;
    vector<string> x(n);
    vector<int> y(n);
    rep (i, n) {
        string s;
        cin >> s;
        int len = repetition(s);
        x[i] = s.substr(0, len);
        y[i] = s.size() / len;
    }

    unordered_map<string, vector<pair<int, int>>> mp;
    rep (i, n) {
        mp[x[i]].emplace_back(i, y[i]);
    }

    vector<int> ans(n);
    for (auto &&[s, t] : mp) {
        vector<int> v;
        for (auto [a, b] : t) v.emplace_back(b);
        auto u = solve(v);
        rep (i, v.size()) {
            ans[t[i].first] = u[i] / t[i].second;
        }
    }
    co(ans);

    return 0;
}
