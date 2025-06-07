// competitive-verifier: PROBLEM
#include <functional>
#include <queue>
#include <utility>
/// @brief 削除可能優先度付きキュー
template <class T, class Comp = std::less<>>
struct erasable_priority_queue {
    bool empty() const { return a.empty(); }
    int size() const { return a.size() - b.size(); }
    T top() const { return a.top(); }
    void insert(const T &x) { a.push(x); }
    void insert(T &&x) { a.push(std::move(x)); }
    void push(const T &x) { a.push(x); }
    void push(T &&x) { a.push(std::move(x)); }
    template <typename... Args>
    void emplace(Args &&...args) {
        a.emplace(std::forward<Args>(args)...);
    }
    void pop() { erase(a.top()); }
    void erase(const T &x) {
        b.push(x);
        while (!b.empty() && a.top() == b.top()) { a.pop(), b.pop(); }
    }
    void erase(T &&x) {
        b.push(std::move(x));
        while (!b.empty() && a.top() == b.top()) { a.pop(), b.pop(); }
    }
  private:
    std::priority_queue<T, std::vector<T>, Comp> a, b;
};
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
struct increment_impl {
    template <class T>
    const increment_impl &operator>>(std::vector<T> &v) const {
        for (auto &x : v) ++x;
        return *this;
    }
} Inc;
struct decrement_impl {
    template <class T>
    const decrement_impl &operator>>(std::vector<T> &v) const {
        for (auto &x : v) --x;
        return *this;
    }
} Dec;
struct sort_impl {
    template <class T>
    const sort_impl &operator>>(std::vector<T> &v) const {
        std::sort(v.begin(), v.end());
        return *this;
    }
} Sort;
struct unique_impl {
    template <class T>
    const unique_impl &operator>>(std::vector<T> &v) const {
        std::sort(v.begin(), v.end());
        v.erase(std::unique(v.begin(), v.end()), v.end());
        return *this;
    }
} Uniq;
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
#include <concepts>
/// @brief 素集合データ構造
/// @details Implement (union by size) + (path compression)
/// @see https://github.com/atcoder/ac-library/blob/master/atcoder/dsu.hpp
struct union_find {
    union_find() = default;
    explicit union_find(int _n) : _rank(_n), data(_n, -1) {}
    const int &operator[](std::size_t x) const { return data[x]; }
    int &operator[](std::size_t x) { return data[x]; }
    int root(int x) { return data[x] < 0 ? x : data[x] = root(data[x]); }
    int get_root(int x) { return root(x); }
    bool is_root(int x) const { return data[x] < 0; }
    bool same(int x, int y) { return root(x) == root(y); }
    bool is_same(int x, int y) { return same(x, y); }
    int rank() { return _rank; }
    int size(int x) { return -(data[root(x)]); }
    int get_size(int x) { return size(x); }
    std::vector<int> leaders() {
        std::vector<int> res;
        for (int i = 0; i < (int)data.size(); ++i) {
            if (is_root(i)) res.emplace_back(i);
        }
        return res;
    }
    bool unite(int x, int y) {
        x = root(x), y = root(y);
        if (x == y) return false;
        --_rank;
        if (data[x] > data[y]) std::swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return true;
    }
    template <class F>
    requires std::invocable<F, int, int, bool>
    bool unite(int x, int y, F f) {
        x = root(x), y = root(y);
        bool swapped = false;
        if (x != y) {
            if (data[x] > data[y]) std::swap(x, y), swapped = true;
            data[x] += data[y];
            data[y] = x;
        }
        f(x, y, swapped);
        return x != y;
    }
    template <class F>
    requires std::invocable<F, int, int>
    bool unite(int x, int y, F f) {
        x = root(x), y = root(y);
        if (x != y) {
            if (data[x] > data[y]) std::swap(x, y);
            data[x] += data[y];
            data[y] = x;
        }
        f(x, y);
        return x != y;
    }
  private:
    int _rank;
    std::vector<int> data;
};
int main(void) {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    cin >> a >> b;
    ll sum = 0;
    rep (i, n - 1) sum += a[i];
    rep (i, m - 1) sum += b[i];
    vector<int> da(n - 1), db(m - 1);
    rep (i, n - 1) da[i] = a[i + 1] - a[i];
    rep (i, m - 1) db[i] = b[i + 1] - b[i];
    vector<int> p(n + m - 1, -1);
    p[1] = 0;
    rep (i, n - 2) {
        p[i + 2] = i + 1;
    }
    p[n] = 0;
    rep (i, m - 2) {
        p[n + i + 1] = n + i;
    }
    vector<ll> c0(n + m - 1), c1(n + m - 1);
    vector<ll> ans(n + m - 1);
    auto score = [&](int i) {
        return (double)c1[i] / c0[i];
    };
    c1[0] = a[0] + b[0];
    rep (i, n - 1) {
        c0[i + 1] = 1;
        c1[i + 1] = da[i];
    }
    rep (i, m - 1) {
        c0[n + i] = 1;
        c1[n + i] = db[i];
    }
    union_find uf(n + m - 1);
    erasable_priority_queue<pair<double, int>, greater<>> pq;
    repn (i, n + m - 2) {
        pq.emplace(score(i), i);
    }
    while (!pq.empty()) {
        auto [v, i] = pq.top();
        pq.pop();
        int r = uf.root(p[i]);
        auto f = [&](int x, int y, bool swapped) {
            if (swapped) {
                swap(c0[x], c0[y]);
                swap(c1[x], c1[y]);
                swap(p[x], p[y]);
            }
            ans[x] += ans[y] + (ll)c1[x] * c0[y];
            c0[x] += c0[y];
            c1[x] += c1[y];
        };
        if (p[r] == -1) {
            uf.unite(r, i, f);
        } else {
            pq.erase({score(r), r});
            uf.unite(r, i, f);
            pq.emplace(score(uf.root(i)), uf.root(i));
        }
    }
    co(ans[uf.root(0)] - sum);
    return 0;
}
