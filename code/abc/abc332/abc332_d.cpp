// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/1209
#include <algorithm>
#include <cstdint>
#include <numeric>
#include <vector>
#include <iterator>
/// @brief 座標圧縮
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
        return std::distance(data.begin(), std::lower_bound(data.begin(), data.end(), x));
    }
    int lower_bound(T x) const {
        return std::distance(data.begin(), std::lower_bound(data.begin(), data.end(), x));
    }
    int upper_bound(T x) const {
        return std::distance(data.begin(), std::upper_bound(data.begin(), data.end(), x));
    }
    std::vector<int> compress(const std::vector<T> &v) const {
        int n = v.size();
        std::vector<int> res(n);
        for (int i = 0; i < n; ++i) res[i] = get(v[i]);
        return res;
    }
    int size() const { return data.size(); }
  private:
    std::vector<T> data;
};
/// @brief 座標圧縮
template <class T>
std::vector<int> compress(const std::vector<T> &v) {
    coordinate_compression cps(v);
    std::vector<int> res;
    res.reserve(std::size(v));
    for (auto &&x : v) res.emplace_back(cps.get(x));
    return res;
}
#include <cassert>
/**
 * @brief フェニック木
 * @see http://hos.ac/slides/20140319_bit.pdf
 *
 * @tparam T
 */
template <class T>
struct fenwick_tree {
    fenwick_tree() : _size(), data() {}
    fenwick_tree(int n) : _size(n + 1), data(n + 1) {}
    template <class U>
    fenwick_tree(const std::vector<U> &v) : _size((int)v.size() + 1), data((int)v.size() + 1) {
        build(v);
    }
    T operator[](int i) const { return sum(i, i + 1); }
    T at(int k) const { return operator[](k); }
    T get(int k) const { return operator[](k); }
    template <class U>
    void build(const std::vector<U> &v) {
        for (int i = 0, n = v.size(); i < n; ++i) data[i + 1] = v[i];
        for (int i = 1; i < _size; ++i) {
            if (i + (i & -i) < _size) data[i + (i & -i)] += data[i];
        }
    }
    void set(int k, T val) { add(k, val - at(k)); }
    void update(int k, T val) { set(k); }
    void add(int k, T val) {
        assert(0 <= k && k < _size - 1);
        for (++k; k < _size; k += k & -k) data[k] += val;
    }
    bool chmax(int k, T val) {
        if (at(k) >= val) return false;
        set(k, val);
        return true;
    }
    bool chmin(int k, T val) {
        if (at(k) <= val) return false;
        set(k, val);
        return true;
    }
    T all_prod() const { return prod(_size - 1); }
    T prod(int k) const { return sum(k); }
    T prod(int a, int b) const { return sum(a, b); }
    T all_sum() const { return sum(_size - 1); }
    T sum(int k) const {
        assert(0 <= k && k < _size);
        T res = 0;
        for (; k > 0; k -= k & -k) res += data[k];
        return res;
    }
    T sum(int a, int b) const {
        assert(0 <= a && a <= b && b < _size);
        T res = T();
        while (a != b) {
            if (a < b) {
                res += data[b];
                b -= b & -b;
            } else {
                res -= data[a];
                a -= a & -a;
            }
        }
        return res;
    }
    int lower_bound(T val) const {
        if (val <= 0) return 0;
        int k = 1;
        while (k < _size) k <<= 1;
        int res = 0;
        for (; k > 0; k >>= 1) {
            if (res + k < _size && data[res + k] < val) val -= data[res += k];
        }
        return res;
    }
  private:
    int _size;
    std::vector<T> data;
};
/// @brief 転倒数
template <class T>
std::int64_t inversion_number(const std::vector<T> &v) {
    if (v.empty()) return 0;
    auto u = compress(v);
    std::reverse(u.begin(), u.end());
    fenwick_tree<T> bit(*std::max_element(u.begin(), u.end()) + 1);
    std::int64_t res = 0;
    for (auto x : u) {
        res += bit.sum(x);
        bit.add(x, 1);
    }
    return res;
}
/// @brief 転倒数
template <class T>
std::int64_t inversion_number_of_permutation(const std::vector<T> &v) {
    if (v.empty()) return 0;
    int n = v.size();
    fenwick_tree<T> bit(n);
    std::int64_t res = 0;
    for (int i = n - 1; i >= 0; --i) {
        res += bit.sum(v[i]);
        bit.add(v[i], 1);
    }
    return res;
}
/// @brief 最小隣接スワップ回数
template <class T>
std::int64_t swap_distance(const std::vector<T> &a, const std::vector<T> &b) {
    if (a.size() != b.size()) return -1;
    int n = a.size();
    std::vector<int> c(n), d(n);
    std::iota(c.begin(), c.end(), 0);
    std::iota(d.begin(), d.end(), 0);
    std::stable_sort(c.begin(), c.end(), [&a](int x, int y) { return a[x] < a[y]; });
    std::stable_sort(d.begin(), d.end(), [&b](int x, int y) { return b[x] < b[y]; });
    std::vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        int x = c[i], y = d[i];
        if (a[x] != b[y]) return -1;
        p[x] = y;
    }
    return inversion_number_of_permutation(p);
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
int main(void) {
    int h, w;
    cin >> h >> w;
    vector a(h, vector(w, 0));
    auto b = a;
    cin >> a >> b;
    int ans = Inf;
    vector<int> ordx(h);
    iota(all(ordx), 0);
    do {
        int x = inversion_number_of_permutation(ordx);
        vector<int> ordy(w);
        iota(all(ordy), 0);
        do {
            bool f = true;
            rep (i, h) {
                rep (j, w) {
                    f &= a[i][j] == b[ordx[i]][ordy[j]];
                }
            }
            if (f)
                chmin(ans, x + inversion_number_of_permutation(ordy));
        } while (next_permutation(all(ordy)));
    } while (next_permutation(all(ordx)));
    co(ans == Inf ? -1 : ans);
    return 0;
}
