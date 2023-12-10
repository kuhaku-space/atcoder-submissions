#line 1 "a.cpp"
#define PROBLEM ""
#line 1 "/home/kuhaku/home/github/algo/lib/algorithm/lis.hpp"
#include <algorithm>
#include <iterator>
#include <vector>

/**
 * @brief 最長増加部分列
 *
 * @tparam T 配列の型
 * @param v 配列
 * @retval int 最長増加部分列の長さ
 */
template <class T>
int longest_increasing_subsequence(const std::vector<T> &v) {
    int n = v.size();
    std::vector<T> dp;
    for (auto x : v) {
        auto it = std::lower_bound(std::begin(dp), std::end(dp), x);
        if (it == std::end(dp)) dp.emplace_back(x);
        else *it = x;
    }
    return dp.size();
}

/**
 * @brief 最長増加部分列
 *
 * @tparam T 配列の型
 * @param v 配列
 * @retval std::vector<int> 最長増加部分列のインデックス
 */
template <class T>
std::vector<int> make_lis(const std::vector<T> &v) {
    int n = v.size();
    std::vector<T> dp;
    std::vector<int> pos;
    pos.reserve(n);
    for (auto x : v) {
        auto it = std::lower_bound(std::begin(dp), std::end(dp), x);
        pos.emplace_back(std::distance(std::begin(dp), it));
        if (it == std::end(dp)) dp.emplace_back(x);
        else *it = x;
    }

    int x = dp.size();
    std::vector<int> res(x--);
    for (int i = n - 1; i >= 0; --i) {
        if (pos[i] == x) res[x] = i, --x;
    }
    return res;
}
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
#line 4 "a.cpp"

int main(void) {
    int n;
    cin >> n;
    vector<pair<int, int>> p(n);
    rep (i, n) cin >> p[i].first;
    rep (i, n) cin >> p[i].second;

    int ans = 0;
    sort(all(p));
    vector<int> a(n);
    rep (i, n) a[i] = p[i].second;
    chmax(ans, n + longest_increasing_subsequence(a));
    sort(all(p), [](auto l, auto r) {
        return l.second < r.second;
    });
    rep (i, n) a[i] = p[i].first;
    chmax(ans, n + longest_increasing_subsequence(a));
    co(ans);

    return 0;
}
