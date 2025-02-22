// competitive-verifier: PROBLEM
#include <cassert>
#include <cstdint>
#include <vector>
/// @brief 累積和
template <class T = std::int64_t>
struct prefix_sum {
    prefix_sum(int _n) : n(_n), data(_n + 1) {}
    template <class U>
    prefix_sum(const std::vector<U> &v) : n(v.size()), data(v.size() + 1) {
        for (int i = 0; i < n; ++i) data[i] = v[i];
        build();
    }
    void build() {
        for (int i = n - 1; i >= 0; --i) data[i] += data[i + 1];
    }
    T get(int k) const {
        assert(0 <= k && k < n);
        return data[k] - data[k + 1];
    }
    void set(int k, int x) { data[k] = x; }
    void add(int k, int x) { data[k] += x; }
    T sum(int r) const {
        assert(0 <= r && r <= n);
        return data[0] - data[r];
    }
    T sum(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        return data[l] - data[r];
    }
    int min_left(T x) const { return min_left(0, x); }
    int min_left(int l, T x) const {
        assert(0 <= l && l <= n);
        int left = l, right = n + 1;
        while (right - left > 1) {
            int mid = (left + right) / 2;
            (data[l] - data[mid] >= x ? right : left) = mid;
        }
        return right;
    }
    int max_right(T x) const { return max_right(n, x); }
    int max_right(int r, T x) const {
        assert(0 <= r && r <= n);
        int left = -1, right = r;
        while (right - left > 1) {
            int mid = (left + right) / 2;
            (data[mid] - data[r] >= x ? left : right) = mid;
        }
        return left;
    }
  private:
    int n;
    std::vector<T> data;
};
#include <array>
/// @brief 線形篩
template <int N = (1 << 22)>
struct linear_sieve {
    linear_sieve() : lpf{}, pr() { build(); }
    bool is_prime(int x) {
        assert(1 <= x && x <= N);
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
    std::vector<int> pr;
    void build() {
        for (int i = 2; i <= N; ++i) {
            if (lpf[i] == 0) {
                lpf[i] = i;
                pr.emplace_back(i);
            }
            for (int j = 0; i * pr[j] <= N; ++j) {
                lpf[i * pr[j]] = pr[j];
                if (pr[j] == lpf[i]) break;
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
linear_sieve ls;
int main(void) {
    int n = 100001;
    vector<int> v(n);
    FOR (i, 3, n) {
        if (ls.is_prime(i) && ls.is_prime((i + 1) / 2)) {
            v[i] = 1;
        }
    }
    prefix_sum<int> ps(v);
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        co(ps.sum(l, r + 1));
    }
    return 0;
}
