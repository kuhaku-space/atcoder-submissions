// competitive-verifier: PROBLEM
#include <cstdint>
#include <string>
#include <vector>
/// 回文判定
template <class T>
bool is_palindrome(const std::vector<T> &v) {
    int n = v.size();
    for (int i = 0; i < n / 2; ++i) {
        if (v[i] != v[n - 1 - i])
            return false;
    }
    return true;
}
/// 回文判定
bool is_palindrome(const std::string &s) {
    int n = s.size();
    for (int i = 0; i < n / 2; ++i) {
        if (s[i] != s[n - 1 - i])
            return false;
    }
    return true;
}
/// 回文数判定
bool is_palindromic_number(std::int64_t x) {
    return is_palindrome(std::to_string(x));
}
#include <cassert>
#include <limits>
#include <random>
/**
 * @brief ローリングハッシュ
 * @see https://qiita.com/keymoon/items/11fac5627672a6d6a9f6
 * @see https://yosupo.hatenablog.com/entry/2023/08/06/181942
 */
struct rolling_hash {
    rolling_hash(uint64_t base = (std::uint64_t)std::random_device()() + 2)
        : _size(), base(base), data(1), p(1, 1) {}
    rolling_hash(const std::string &_s, uint64_t base = (std::uint64_t)std::random_device()() + 2)
        : _size(_s.size()), base(base), data(1), p(1, 1) {
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
    /// get hash of s[0...r]
    std::uint64_t get(int r) const { return data[r]; }
    /// get hash of s[l...r]
    std::uint64_t get(int l, int r) const {
        assert(0 <= l && l <= r && r <= _size);
        std::uint64_t x = data[r] + mod - _mul(data[l], p[r - l]), y;
        return __builtin_usubl_overflow(x, mod, &y) ? x : y;
    }
    /// get hash of s.substr(pos, len)
    std::uint64_t substr(int pos, int len = std::numeric_limits<int>::max()) const {
        assert(0 <= pos && pos <= _size);
        len = std::min(len, _size - pos);
        std::uint64_t x = data[pos + len] + mod - _mul(data[pos], p[len]), y;
        return __builtin_usubl_overflow(x, mod, &y) ? x : y;
    }
    /// search string
    std::vector<int> search(const std::string &s) {
        std::vector<int> res;
        int n = s.size();
        if (n > _size) return res;
        std::uint64_t x = 0, y;
        for (char c : s) {
            x = _mul(x, base) + c;
            x = (__builtin_usubl_overflow(x, mod, &y) ? x : y);
        }
        for (int i = 0; i <= _size - n; ++i) {
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
    int _size;
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
int main(void) {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    sort(all(s));
    rolling_hash rh;
    unordered_set<uint64_t> st;
    do {
        bool f = false;
        rep (i, n - k + 1) {
            f |= is_palindrome(s.substr(i, k));
        }
        if (!f)
            st.emplace(rh.hash(s));
    } while (next_permutation(all(s)));
    co(st.size());
    return 0;
}
