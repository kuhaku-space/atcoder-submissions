#define PROBLEM ""
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
    T &operator[](int i) { return data[i]; }
    void add(T x) { data.emplace_back(x); }
    void build() {
        std::sort(std::begin(data), std::end(data));
        data.erase(std::unique(std::begin(data), std::end(data)), std::end(data));
    }
    bool exists(T x) const {
        auto it = std::lower_bound(std::begin(data), std::end(data), x);
        return it != std::end(data) && *it == x;
    }
    int get(T x) const {
        auto it = std::lower_bound(std::begin(data), std::end(data), x);
        return std::distance(std::begin(data), it);
    }
    int size() const { return std::size(data); }
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
std::vector<T> compress(const std::vector<T> &v) {
    coordinate_compression cps(v);
    std::vector<T> res;
    res.reserve(std::size(v));
    for (auto &&x : v) res.emplace_back(cps.get(x));
    return res;
}
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
int main(void) {
    int n;
    cin >> n;
    vector p(n, vector(n, 0l));
    vector r(n, vector(n - 1, 0l));
    vector d(n - 1, vector(n, 0l));
    cin >> p >> r >> d;
    coordinate_compression<ll> cps;
    rep (i, n) {
        rep (j, n) cps.add(p[i][j]);
    }
    cps.build();
    vector dp(n, vector(n, vector(n * n, pair<ll, ll>(INF, 0))));
    dp[0][0][cps.get(p[0][0])] = {0, 0};
    rep (i, n) {
        rep (j, n) {
            rep (k, n * n) {
                if (dp[i][j][k].first == INF)
                    continue;
                auto [a, b] = dp[i][j][k];
                if (j + 1 < n) {
                    ll v = cps[k];
                    ll x = a, y = b;
                    if (b >= r[i][j]) {
                        y -= r[i][j];
                    } else {
                        ll e = (r[i][j] - b - 1) / v + 1;
                        x += e;
                        y += v * e - r[i][j];
                    }
                    ++x;
                    int z = max(k, cps.get(p[i][j + 1]));
                    if (chmin(dp[i][j + 1][z].first, x)) {
                        dp[i][j + 1][z].second = y;
                    } else if (dp[i][j + 1][z].first == x) {
                        chmax(dp[i][j + 1][z].second, y);
                    }
                }
                if (i + 1 < n) {
                    ll v = cps[k];
                    ll x = a, y = b;
                    if (b >= d[i][j]) {
                        y -= d[i][j];
                    } else {
                        ll e = (d[i][j] - b - 1) / v + 1;
                        x += e;
                        y += v * e - d[i][j];
                    }
                    ++x;
                    int z = max(k, cps.get(p[i + 1][j]));
                    if (chmin(dp[i + 1][j][z].first, x)) {
                        dp[i + 1][j][z].second = y;
                    } else if (dp[i + 1][j][z].first == x) {
                        chmax(dp[i + 1][j][z].second, y);
                    }
                }
            }
        }
    }
    ll ans = INF;
    rep (i, n * n) {
        chmin(ans, dp[n - 1][n - 1][i].first);
    }
    co(ans);
    return 0;
}
