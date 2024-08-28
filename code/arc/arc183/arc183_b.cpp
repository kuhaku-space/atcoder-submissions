// competitive-verifier: PROBLEM
#include <algorithm>
#include <iterator>
#include <vector>
/**
 * @brief 座標圧縮
 *
 * @tparam T 要素の型
 */
template <class T>
struct coordinate_compression {
    coordinate_compression() = default;
    coordinate_compression(const std::vector<T> &_data) : data(_data) { build(); }
    const T &operator[](int i) const { return data[i]; }
    void add(T x) { data.emplace_back(x); }
    void build() {
        std::sort(data.begin(), data.end());
        data.erase(std::unique(data.begin(), data.end()), data.end());
    }
    bool exists(T x) const {
        auto it = std::lower_bound(data.begin(), data.end(), x);
        return it != data.end() && *it == x;
    }
    int get(T x) const {
        auto it = std::lower_bound(data.begin(), data.end(), x);
        return std::distance(data.begin(), it);
    }
    int size() const { return data.size(); }
  private:
    std::vector<T> data;
};
/**
 * @brief 座標圧縮
 *
 * @tparam T 要素の型
 * @param v 配列
 * @return std::vector<T>
 */
template <class T>
std::vector<int> compress(const std::vector<T> &v) {
    coordinate_compression cps(v);
    std::vector<int> res;
    res.reserve(std::size(v));
    for (auto &&x : v) res.emplace_back(cps.get(x));
    return res;
}
#include <utility>
/**
 * @brief ランレングス圧縮
 *
 * @tparam Container
 * @param v 配列
 * @return auto
 */
template <class Container>
auto run_length_encoding(const Container &v) {
    std::vector<std::pair<std::decay_t<decltype(v[0])>, int>> res;
    for (auto &&e : v) {
        if (res.empty() || res.back().first != e) res.emplace_back(e, 1);
        else ++res.back().second;
    }
    return res;
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
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n);
    cin >> a >> b;
    if (a == b) {
        Yes();
        return;
    }
    if (k == 1) {
        auto v = run_length_encoding(b);
        int c = 0;
        for (int x : a) {
            if (c < v.size() && v[c].first == x)
                ++c;
        }
        Yes(c == v.size());
        return;
    }
    coordinate_compression<int> cps;
    rep (i, n) {
        cps.add(a[i]);
        cps.add(b[i]);
    }
    cps.build();
    rep (i, n) {
        a[i] = cps.get(a[i]);
        b[i] = cps.get(b[i]);
    }
    bool f = false;
    vector<vector<int>> dp(cps.size());
    rep (i, n) dp[b[i]].emplace_back(i);
    rep (i, cps.size()) {
        rep (j, dp[i].size() - 1) {
            f |= dp[i][j + 1] - dp[i][j] <= k;
        }
    }
    if (!f) {
        No();
        return;
    }
    set<int> st(all(a));
    rep (i, n) {
        if (!st.count(b[i])) {
            No();
            return;
        }
    }
    Yes();
    return;
}
int main(void) {
    int q;
    cin >> q;
    while (q--) solve();
    return 0;
}
