// competitive-verifier: PROBLEM
#include <array>
#include <cmath>
#include <cstdint>
#include <vector>
/// @brief エラトステネスの篩
/// @see https://qiita.com/peria/items/a4ff4ddb3336f7b81d50
template <int N = (1 << 22)>
struct eratosthenes {
  private:
    static constexpr int SIZE = N / 30 + (N % 30 != 0);
    static constexpr std::array<int, 8> kMod30 = {1, 7, 11, 13, 17, 19, 23, 29};
    static constexpr std::array<int, 8> C1 = {6, 4, 2, 4, 2, 4, 6, 2};
    static constexpr std::array<std::array<int, 8>, 8> C0 = {
        0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 2, 2, 0, 2, 0, 2,
        2, 1, 3, 1, 1, 2, 1, 1, 3, 1, 3, 3, 1, 2, 1, 3, 3, 1, 4, 2, 2, 2,
        2, 2, 4, 1, 5, 3, 1, 4, 1, 3, 5, 1, 6, 4, 2, 4, 2, 4, 6, 1,
    };
    static constexpr std::array<std::array<std::uint8_t, 8>, 8> kMask = {
        0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f, 0xfd, 0xdf, 0xef, 0xfe, 0x7f,
        0xf7, 0xfb, 0xbf, 0xfb, 0xef, 0xfe, 0xbf, 0xfd, 0x7f, 0xf7, 0xdf, 0xf7, 0xfe,
        0xbf, 0xdf, 0xfb, 0xfd, 0x7f, 0xef, 0xef, 0x7f, 0xfd, 0xfb, 0xdf, 0xbf, 0xfe,
        0xf7, 0xdf, 0xf7, 0x7f, 0xfd, 0xbf, 0xfe, 0xef, 0xfb, 0xbf, 0xfb, 0xf7, 0x7f,
        0xfe, 0xef, 0xdf, 0xfd, 0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe,
    };
  public:
    constexpr eratosthenes() {
        prime_number.fill(0xff);
        prime_number[0] = 0xfe;
        if (int r = N % 30) {
            if (r < 7) prime_number[SIZE - 1] = 0x1;
            else if (r < 11) prime_number[SIZE - 1] = 0x3;
            else if (r < 13) prime_number[SIZE - 1] = 0x7;
            else if (r < 17) prime_number[SIZE - 1] = 0xf;
            else if (r < 19) prime_number[SIZE - 1] = 0x1f;
            else if (r < 23) prime_number[SIZE - 1] = 0x3f;
            else if (r < 29) prime_number[SIZE - 1] = 0x7f;
        }
        const std::uint64_t sqrt_x = std::ceil(std::sqrt(N) + 0.1);
        const std::uint64_t sqrt_xi = sqrt_x / 30 + 1;
        for (std::uint64_t i = 0; i < sqrt_xi; ++i) {
            for (std::uint8_t flags = prime_number[i]; flags; flags &= flags - 1) {
                std::uint8_t lsb = flags & (-flags);
                const int ibit = __builtin_ctz(lsb);
                const int m = kMod30[ibit];
                const int pm = 30 * i + 2 * m;
                for (std::uint64_t j = i * pm + (m * m) / 30, k = ibit; j < SIZE;
                     j += i * C1[k] + C0[ibit][k], k = (k + 1) & 7) {
                    prime_number[j] &= kMask[ibit][k];
                }
            }
        }
    }
    /// @brief 素数判定
    bool is_prime(int x) const {
        switch (x % 30) {
            case 1: return prime_number[x / 30] >> 0 & 1;
            case 7: return prime_number[x / 30] >> 1 & 1;
            case 11: return prime_number[x / 30] >> 2 & 1;
            case 13: return prime_number[x / 30] >> 3 & 1;
            case 17: return prime_number[x / 30] >> 4 & 1;
            case 19: return prime_number[x / 30] >> 5 & 1;
            case 23: return prime_number[x / 30] >> 6 & 1;
            case 29: return prime_number[x / 30] >> 7 & 1;
        }
        if (x < 6) {
            if (x == 2) return true;
            if (x == 3) return true;
            if (x == 5) return true;
        }
        return false;
    }
    std::vector<int> prime_numbers(int x) const {
        if (x < 2) return std::vector<int>();
        std::vector<int> res = {2};
        for (int i = 3; i <= x; i += 2) {
            if (is_prime(i)) res.emplace_back(i);
        }
        return res;
    }
  private:
    std::array<std::uint8_t, SIZE> prime_number;
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
eratosthenes pn;
int main(void) {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    cin >> a;
    int l = 1000000;
    vector<int> b(l + 1);
    for (auto x : a) ++b[x];
    for (int p = 2; p <= l; ++p) {
        if (!pn.is_prime(p))
            continue;
        for (int i = l / p; i >= 1; --i) {
            b[i] += b[i * p];
        }
    }
    vector<int> ans(l + 1);
    repn (i, l) {
        if (b[i] >= k) {
            for (int j = i; j <= l; j += i) {
                ans[j] = i;
            }
        }
    }
    rep (i, n) co(ans[a[i]]);
    return 0;
}
