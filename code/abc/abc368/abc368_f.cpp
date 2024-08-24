// competitive-verifier: PROBLEM
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <iterator>
#include <utility>
#include <vector>
/**
 * @brief 素数ライブラリ
 *
 * @tparam N
 */
template <int N = 1 << 22>
struct prime_number {
    prime_number() : is_not_prime(), data() { init(); }
    /**
     * @brief 素数判定
     *
     * @param n
     * @return bool
     */
    bool is_prime(std::int64_t n) const {
        assert(n >= 0);
        if (n < N) return !is_not_prime[n];
        for (auto i : data) {
            if ((std::int64_t)i * i > n) break;
            if (n % i == 0) return false;
        }
        return true;
    }
    std::vector<int> prime_numbers(int x) const {
        std::vector<int> res;
        for (auto i : data) {
            if (i > x) break;
            res.emplace_back(i);
        }
        return res;
    }
    /**
     * @brief 素因数分解
     *
     * @tparam T
     * @param x
     * @return std::vector<std::pair<T, int>>
     */
    template <class T>
    std::vector<std::pair<T, int>> prime_factorization(T x) const {
        if (x == 1) return std::vector<std::pair<T, int>>();
        std::vector<std::pair<T, int>> res;
        for (auto p : data) {
            int cnt = 0;
            for (; x % p == 0; x /= p) ++cnt;
            if (cnt) res.emplace_back(p, cnt);
            if ((std::int64_t)p * p > x) break;
        }
        if (x != 1) res.emplace_back(x, 1);
        return res;
    }
    /**
     * @brief 約数列挙
     *
     * @tparam T
     * @param x
     * @return std::vector<T>
     */
    template <class T>
    std::vector<T> divisors(T x) const {
        if (x == 1) return std::vector<T>(1, 1);
        auto v = prime_factorization(x);
        std::vector<T> res;
        res.emplace_back(1);
        for (auto p : v) {
            int n = res.size();
            res.resize(n * (p.second + 1));
            for (int i = 0; i < n * p.second; ++i) res[n + i] = res[i] * p.first;
            for (int i = 1; i <= p.second; ++i) {
                std::inplace_merge(res.begin(), res.begin() + n * i, res.begin() + n * (i + 1));
            }
        }
        return res;
    }
    /**
     * @brief 因数分解列挙
     *
     * @tparam T
     * @param x
     * @return std::vector<std::vector<T>>
     */
    template <class T>
    std::vector<std::vector<T>> factorization(T x) const {
        std::vector<std::vector<T>> res;
        auto f = [&](auto self, std::vector<T> v, T a) -> void {
            if (a == 1) res.emplace_back(v);
            for (auto i : this->divisors(a)) {
                if (i == 1 || (!v.empty() && v.back() > i)) continue;
                v.emplace_back(i);
                self(self, v, a / i);
                v.pop_back();
            }
        };
        f(f, std::vector<T>(), x);
        return res;
    }
  private:
    std::bitset<N> is_not_prime;
    std::vector<int> data;
    void init() {
        is_not_prime[0] = is_not_prime[1] = true;
        for (int i = 2; i < N; ++i) {
            if (!is_not_prime[i]) {
                data.emplace_back(i);
                if ((std::int64_t)i * i >= N) continue;
                if (i == 2) {
                    for (int j = i * i; j < N; j += i) is_not_prime[j] = true;
                } else {
                    for (int j = i * i; j < N; j += i << 1) is_not_prime[j] = true;
                }
            }
        }
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
prime_number pn;
int main(void) {
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    int ans = 0;
    for (int x : a) {
        auto v = pn.prime_factorization(x);
        int s = 0;
        for (auto [p, q] : v) s += q;
        ans ^= s;
    }
    if (!ans)
        co("Bruno");
    else
        co("Anna");
    return 0;
}
