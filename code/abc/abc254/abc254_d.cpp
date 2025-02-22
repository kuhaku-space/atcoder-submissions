// competitive-verifier: PROBLEM
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
template <int N>
struct linear_sieve {
    linear_sieve() {
        build();
    }
    bool is_prime_number(int x) {
        assert(x <= N);
        return lpf[x] == x;
    }
    std::vector<int> prime_factorization(int x) {
        assert(1 <= x && x <= N);
        std::vector<int> res;
        while (x > 1) {
            res.emplace_back(lpf[x]);
            x /= lpf[x];
        }
        return res;
    }
  private:
    std::array<int, N + 1> lpf;
    std::vector<int> prime_numbers;
    void build() {
        lpf.fill(-1);
        for (int i = 2; i <= N; ++i) {
            if (lpf[i] == -1) {
                lpf[i] = i;
                prime_numbers.emplace_back(i);
            }
            for (int j = 0; i * prime_numbers[j] <= N; ++j) {
                lpf[i * prime_numbers[j]] = prime_numbers[j];
                if (prime_numbers[j] == lpf[i])
                    break;
            }
        }
    }
};
int main(void) {
    int n;
    cin >> n;
    linear_sieve<20000000> ls;
    ll ans = 0;
    repn (i, n) {
        auto v = ls.prime_factorization(i);
        ll p = 1;
        ll q = -1;
        for (auto x : v) {
            if (q == -1) {
                q = x;
            } else if (q == x) {
                q = -1;
            } else {
                p *= q;
                q = x;
            }
        }
        if (q != -1)
            p *= q;
        ans += sqrt(n / p);
    }
    co(ans);
    return 0;
}
