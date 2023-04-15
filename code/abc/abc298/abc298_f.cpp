#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/home/github/algo/lib/template/template.hpp"
#pragma GCC target("sse4.2,avx2,bmi2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
template <class T, class U>
bool chmax(T &a, const U &b) {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U &b) {
    return (T)b < a ? a = (T)b, true : false;
}
constexpr int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
constexpr double PI = M_PI;
#line 3 "/home/kuhaku/home/github/algo/lib/algorithm/compress.hpp"

/**
 * @brief 座標圧縮
 *
 * @tparam T 要素の型
 */
template <class T>
struct coordinate_compression {
    coordinate_compression() = default;
    coordinate_compression(const vector<T> &_data) : data(_data) { this->build(); }

    const T &operator[](int i) const { return this->data[i]; }
    T &operator[](int i) { return this->data[i]; }

    void add(T x) { this->data.emplace_back(x); }

    void build() {
        std::sort(this->data.begin(), this->data.end());
        this->data.erase(std::unique(this->data.begin(), this->data.end()), this->data.end());
    }
    void build(const vector<T> &v) {
        this->data = v;
        std::sort(this->data.begin(), this->data.end());
        this->data.erase(std::unique(this->data.begin(), this->data.end()), this->data.end());
    }

    bool exist(T x) const {
        auto it = std::lower_bound(this->data.begin(), this->data.end(), x);
        return it != this->data.end() && *it == x;
    }

    int get(T x) const {
        auto it = std::lower_bound(this->data.begin(), this->data.end(), x);
        return it - this->data.begin();
    }

    int size() const { return this->data.size(); }

  private:
    std::vector<T> data;
};

/**
 * @brief 座標圧縮
 *
 * @tparam T 要素の型
 * @param v
 * @return std::vector<T>
 */
template <class T>
std::vector<T> compress(const std::vector<T> &v) {
    coordinate_compression cps(v);
    std::vector<T> res;
    for (auto x : v) res.emplace_back(cps.get(x));
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
using ll = int64_t;
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

int main(void) {
    int n;
    cin >> n;
    vector<ll> r(n), c(n), v(n);
    rep (i, n) cin >> r[i] >> c[i] >> v[i];
    r = compress(r);
    c = compress(c);

    vector<ll> xs(n), ys(n);
    rep (i, n) {
        xs[r[i]] += v[i];
        ys[c[i]] += v[i];
    }

    auto a = r, b = c;
    sort(all(a));
    a.erase(unique(all(a)), a.end());
    sort(all(b));
    b.erase(unique(all(b)), b.end());
    sort(all(a), [&](auto x, auto y) {
        return xs[x] > xs[y];
    });
    sort(all(b), [&](auto x, auto y) {
        return ys[x] > ys[y];
    });

    ll ans = 0;
    unordered_set<ll> ps, qs;
    rep (i, n) ps.emplace(r[i] * n + c[i]);
    priority_queue<pair<ll, ll>> pq;
    pq.emplace(xs[a[0]] + ys[b[0]], 0);
    qs.emplace(0);
    while (!pq.empty()) {
        auto [s, p] = pq.top();
        pq.pop();
        int x = p / n, y = p % n;
        if (!ps.count(a[x] * n + b[y])) {
            ans = s;
            break;
        }
        if (x + 1 < a.size() && !qs.count(p + n)) {
            pq.emplace(xs[a[x + 1]] + ys[b[y]], p + n);
            qs.emplace(p + n);
        }
        if (y + 1 < b.size() && !qs.count(p + 1)) {
            pq.emplace(xs[a[x]] + ys[b[y + 1]], p + 1);
            qs.emplace(p + 1);
        }
    }

    rep (i, n) chmax(ans, xs[r[i]] + ys[c[i]] - v[i]);
    co(ans);

    return 0;
}
