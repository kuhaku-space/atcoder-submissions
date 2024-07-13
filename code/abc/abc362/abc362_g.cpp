// competitive-verifier: PROBLEM
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
#include <ext/pb_ds/tree_policy.hpp>
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
#include <cstdint>
#include <random>
#include <string>
/**
 * @brief ローリングハッシュ
 * @see https://qiita.com/keymoon/items/11fac5627672a6d6a9f6
 * @see https://yosupo.hatenablog.com/entry/2023/08/06/181942
 */
struct rolling_hash {
    rolling_hash(const std::string &_s, uint64_t base = (std::uint64_t)std::random_device()() + 2)
        : len(_s.size() + 1), base(base), data(1), p(1, 1) {
        std::uint64_t x = 0, t = 1, y;
        for (const auto c : _s) {
            x = _mul(x, base) + c;
            x = (__builtin_usubl_overflow(x, mod, &y) ? x : y);
            data.emplace_back(x);
            t = _mul(t, base);
            p.emplace_back(t);
        }
    }
    std::uint64_t get_base() const { return base; }
    /// get hash of s[l...r]
    std::uint64_t get(int l, int r) const {
        std::uint64_t x = data[r] + mod - _mul(data[l], p[r - l]), y;
        return __builtin_usubl_overflow(x, mod, &y) ? x : y;
    }
    /// search string
    std::vector<int> search(const std::string &s) {
        std::vector<int> res;
        int n = s.size();
        if (n >= len) return res;
        std::uint64_t x = 0, y;
        for (char c : s) {
            x = _mul(x, base) + c;
            x = (__builtin_usubl_overflow(x, mod, &y) ? x : y);
        }
        for (int i = 0; i < len - n; ++i) {
            if (get(i, i + n) == x) res.emplace_back(i);
        }
        return res;
    }
    std::uint64_t hash(const std::string &s) const {
        std::uint64_t x = 0, y;
        for (const auto c : s) {
            x = _mul(x, base) + c;
            x = (__builtin_usubl_overflow(x, mod, &y) ? x : y);
        }
        return x;
    }
  private:
    static constexpr std::uint64_t mod = (1ul << 61) - 1;
    static constexpr std::uint64_t mask30 = (1ul << 30) - 1;
    static constexpr std::uint64_t mask31 = (1ul << 31) - 1;
    int len;
    std::uint64_t base;
    std::vector<std::uint64_t> data, p;
    constexpr std::uint64_t _mul(std::uint64_t a, std::uint64_t b) const {
        __uint128_t t = (__uint128_t)a * b;
        a = (t >> 61) + (t & mod);
        return __builtin_usubl_overflow(a, mod, &b) ? a : b;
    }
    constexpr std::uint64_t _pow(std::uint64_t x, std::uint64_t k) const {
        std::uint64_t res = 1;
        for (; k; k >>= 1) {
            if (k & 1) res = _mul(res, x);
            x = _mul(x, x);
        }
        return res;
    }
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
using namespace __gnu_pbds;
template <typename T, typename S>
using hash_table = gp_hash_table<T, S>;
int main(void) {
    string s;
    cin >> s;
    int n = s.size();
    int q;
    cin >> q;
    vector<string> v(q);
    cin >> v;
    rolling_hash rh(s);
    vector<int> a(q);
    rep (i, q) a[i] = v[i].size();
    coordinate_compression cps(a);
    vector queries(cps.size(), vector<int>());
    rep (i, q) queries[cps.get(a[i])].emplace_back(i);
    vector<int> ans(q);
    rep (i, cps.size()) {
        int l = cps[i];
        hash_table<uint64_t, int> ht;
        hash_table<uint64_t, vector<int>> li;
        for (int idx : queries[i]) {
            auto h = rh.hash(v[idx]);
            li[h].emplace_back(idx);
            ht[h] = 0;
        }
        rep (j, n - l + 1) {
            auto h = rh.get(j, j + l);
            if (ht.find(h) != ht.end())
                ht[h]++;
        }
        for (auto [x, y] : ht) {
            for (int idx : li[x]) {
                ans[idx] = y;
            }
        }
    }
    rep (i, q) co(ans[i]);
    return 0;
}
