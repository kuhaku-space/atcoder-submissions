// competitive-verifier: PROBLEM
#include <cassert>
#include <tuple>
#include <vector>
namespace internal {
/**
 * @brief 完備辞書
 *
 * @see https://ei1333.github.io/library/structure/wavelet/succinct-indexable-dictionary.hpp
 */
struct bit_vector {
    bit_vector() = default;
    bit_vector(unsigned int _length)
        : length(_length), blocks((_length + 31) >> 5), bit((_length + 31) >> 5),
          sum((_length + 31) >> 5) {}
    void set(unsigned int k) { bit[k >> 5] |= 1U << (k & 31); }
    void build() {
        sum[0] = 0U;
        for (unsigned int i = 1; i < blocks; ++i) {
            sum[i] = sum[i - 1] + __builtin_popcount(bit[i - 1]);
        }
    }
    bool operator[](unsigned int k) const { return bit[k >> 5] >> (k & 31) & 1; }
    unsigned int rank(unsigned int k) const {
        return sum[k >> 5] + __builtin_popcount(bit[k >> 5] & ((1U << (k & 31)) - 1));
    }
    unsigned int rank(bool val, unsigned int k) const { return val ? rank(k) : k - rank(k); }
    unsigned int select(unsigned int k) const {
        unsigned int sl = 0, sr = blocks + 1;
        while (sr - sl > 1) {
            unsigned int m = (sl + sr) >> 1;
            if (sum[m] < k) sl = m;
            else sr = m;
        }
        k -= sum[sl];
        unsigned int bl = 0, br = 32;
        while (br - bl > 1) {
            unsigned int m = (bl + br) >> 1;
            if (__builtin_popcount(bit[sl] & ((1U << m) - 1)) < k) bl = m;
            else br = m;
        }
        return (sl << 5) + bl;
    }
  private:
    unsigned int length, blocks;
    std::vector<unsigned int> bit, sum;
};
}  // namespace internal
/**
 * @brief ウェーブレット行列
 * @see https://ei1333.github.io/library/structure/wavelet/wavelet-matrix.hpp
 *
 * @tparam T
 * @tparam L
 */
template <class T, int L = 20>
struct wavelet_matrix {
    wavelet_matrix() = default;
    wavelet_matrix(std::vector<T> v) : length(v.size()) {
        std::vector<T> l(length), r(length);
        for (int level = L - 1; level >= 0; --level) {
            matrix[level] = internal::bit_vector(length + 1);
            int left = 0, right = 0;
            for (int i = 0; i < length; ++i) {
                if (v[i] >> level & 1) {
                    matrix[level].set(i);
                    r[right++] = v[i];
                } else {
                    l[left++] = v[i];
                }
            }
            mid[level] = left;
            matrix[level].build();
            v.swap(l);
            for (int i = 0; i < right; ++i) v[left + i] = r[i];
        }
    }
    T access(int k) const {
        T res = 0;
        for (int level = L - 1; level >= 0; --level) {
            bool f = matrix[level][k];
            if (f) res |= T(1) << level;
            k = matrix[level].rank(f, k) + mid[level] * f;
        }
        return res;
    }
    T operator[](int k) const { return access(k); }
    /// count i s.t. (0 <= i < r) && v[i] == x
    int rank(int r, T x) const {
        int l = 0;
        for (int level = L - 1; level >= 0; --level) {
            std::tie(l, r) = succ((x >> level) & 1, l, r, level);
        }
        return r - l;
    }
    /// count i s.t. (l <= i < r) && v[i] == x
    int rank(int l, int r, T x) const { return rank(r, x) - rank(l, x); }
    /// k-th smallest number in v[l ... r-1]
    T kth_smallest(int l, int r, int k) const {
        assert(0 <= k && k < r - l);
        T res = 0;
        for (int level = L - 1; level >= 0; --level) {
            int cnt = matrix[level].rank(false, r) - matrix[level].rank(false, l);
            bool f = cnt <= k;
            if (f) {
                res |= T(1) << level;
                k -= cnt;
            }
            std::tie(l, r) = succ(f, l, r, level);
        }
        return res;
    }
    /// k-th largest number in v[l ... r-1]
    T kth_largest(int l, int r, int k) const { return kth_smallest(l, r, r - l - k - 1); }
    /// count i s.t. (l <= i < r) && (v[i] < upper)
    int range_freq(int l, int r, T upper) const {
        int res = 0;
        for (int level = L - 1; level >= 0; --level) {
            bool f = ((upper >> level) & 1);
            if (f) res += matrix[level].rank(false, r) - matrix[level].rank(false, l);
            std::tie(l, r) = succ(f, l, r, level);
        }
        return res;
    }
    /// count i s.t. (l <= i < r) && (lower <= v[i] < upper)
    int range_freq(int l, int r, T lower, T upper) const {
        return range_freq(l, r, upper) - range_freq(l, r, lower);
    }
    /// max v[i] s.t. (l <= i < r) && (v[i] < upper)
    T prev_value(int l, int r, T upper) const {
        int cnt = range_freq(l, r, upper);
        return cnt == 0 ? T(-1) : kth_smallest(l, r, cnt - 1);
    }
    /// min v[i] s.t. (l <= i < r) && (lower <= v[i])
    T next_value(int l, int r, T lower) const {
        int cnt = range_freq(l, r, lower);
        return cnt == r - l ? T(-1) : kth_smallest(l, r, cnt);
    }
  private:
    int length;
    internal::bit_vector matrix[L];
    int mid[L];
    std::pair<int, int> succ(bool f, int l, int r, int level) const {
        return {matrix[level].rank(f, l) + mid[level] * f,
                matrix[level].rank(f, r) + mid[level] * f};
    }
};
#include <functional>
#include <limits>
template <class T, class Comp = std::less<>, class F>
std::vector<int> monotone_minima(int h, int w, F f) {
    Comp comp;
    std::vector<int> dp(h);
    auto dfs = [&](auto self, int top, int bottom, int left, int right) -> void {
        if (top > bottom) return;
        if (left == right) {
            for (int i = top; i <= bottom; ++i) dp[i] = left;
            return;
        }
        int line = (top + bottom) / 2;
        T min_val = f(line, left);
        int idx = left;
        for (int i = left + 1; i <= right; i++) {
            T val = f(line, i);
            if (comp(val, min_val)) min_val = val, idx = i;
        }
        dp[line] = idx;
        self(self, top, line - 1, left, idx);
        self(self, line + 1, bottom, idx, right);
    };
    dfs(dfs, 0, h - 1, 0, w - 1);
    return dp;
}
template <class T, class Comp = std::less<>, class F>
std::vector<T> monotone_minima_value(int h, int w, F f) {
    Comp comp;
    std::vector<T> dp(h);
    auto dfs = [&](auto self, int top, int bottom, int left, int right) -> void {
        if (top > bottom) return;
        if (left == right) {
            for (int i = top; i <= bottom; ++i) dp[i] = f(i, left);
            return;
        }
        int line = (top + bottom) / 2;
        T min_val = f(line, left);
        int idx = left;
        for (int i = left + 1; i <= right; i++) {
            T val = f(line, i);
            if (comp(val, min_val)) min_val = val, idx = i;
        }
        dp[line] = min_val;
        self(self, top, line - 1, left, idx);
        self(self, line + 1, bottom, idx, right);
    };
    dfs(dfs, 0, h - 1, 0, w - 1);
    return dp;
}
/// @brief min-plus convolution
/// @param b 下に凸
template <class T>
std::vector<T> min_plus_convolution(const std::vector<T> &a, const std::vector<T> &b) {
    int n = a.size(), m = b.size();
    auto f = [&](int i, int j) {
        if (i < j or i - j >= m) return std::numeric_limits<T>::max();
        return a[j] + b[i - j];
    };
    return monotone_minima_value<T>(n + m - 1, n, f);
}
template <class T>
std::vector<T> max_plus_convolution(const std::vector<T> &a, const std::vector<T> &b) {
    int n = a.size(), m = b.size();
    auto f = [&](int i, int j) {
        if (i < j or i - j >= m) return std::numeric_limits<T>::lowest();
        return a[j] + b[i - j];
    };
    return monotone_minima_value<T, std::greater<>>(n + m - 1, n, f);
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
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    unordered_map<int, int> mp;
    vector<int> v(n);
    rep (i, n) {
        v[i] = (mp.count(a[i]) ? mp[a[i]] : 0);
        mp[a[i]] = i + 1;
    }
    wavelet_matrix<int, 19> wm(v);
    vector<int> ls(n + 1), rs(n + 1);
    rep (i, n + 1) ls[i] = wm.range_freq(0, i, 1, i + 1), rs[i] = wm.range_freq(i, n, i + 1, n + 1);
    auto f = [&](int l, int r) {
        return ls[l] + rs[r] + wm.range_freq(l, r, l + 1, r + 1);
    };
    auto ans = monotone_minima_value<int>(n, n, f);
    co(n - *min_element(all(ans)));
    return 0;
}
