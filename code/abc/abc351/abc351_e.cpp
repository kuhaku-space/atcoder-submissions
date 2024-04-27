#line 1 "a.cpp"
#define PROBLEM ""
#line 1 "/home/kuhaku/home/github/algo/lib/data_structure/compressed_wavelet_matrix.hpp"
#include <vector>
#line 2 "/home/kuhaku/home/github/algo/lib/algorithm/compress.hpp"
#include <algorithm>
#include <iterator>
#line 5 "/home/kuhaku/home/github/algo/lib/algorithm/compress.hpp"

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
#line 1 "/home/kuhaku/home/github/algo/lib/data_structure/wavelet_matrix.hpp"
#include <cassert>
#include <tuple>
#line 3 "/home/kuhaku/home/github/algo/lib/data_structure/bit_vector.hpp"

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
#line 5 "/home/kuhaku/home/github/algo/lib/data_structure/wavelet_matrix.hpp"

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
            matrix[level] = bit_vector(length + 1);
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

    /**
     * @brief count i s.t. (0 <= i < r) && v[i] == x
     *
     * @param x
     * @param r
     * @return int
     */
    int rank(int r, T x) const {
        int l = 0;
        for (int level = L - 1; level >= 0; --level) {
            std::tie(l, r) = succ((x >> level) & 1, l, r, level);
        }
        return r - l;
    }

    /**
     * @brief count i s.t. (l <= i < r) && v[i] == x
     *
     * @param l
     * @param r
     * @param x
     * @return int
     */
    int rank(int l, int r, T x) const { return rank(r, x) - rank(l, x); }

    /**
     * @brief k-th smallest number in v[l ... r-1]
     *
     * @param l
     * @param r
     * @param k
     * @return T
     */
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

    /**
     * @brief k-th largest number in v[l ... r-1]
     *
     * @param l
     * @param r
     * @param k
     * @return T
     */
    T kth_largest(int l, int r, int k) const { return kth_smallest(l, r, r - l - k - 1); }

    /**
     * @brief count i s.t. (l <= i < r) && (v[i] < upper)
     *
     * @param l
     * @param r
     * @param upper
     * @return int
     */
    int range_freq(int l, int r, T upper) const {
        int res = 0;
        for (int level = L - 1; level >= 0; --level) {
            bool f = ((upper >> level) & 1);
            if (f) res += matrix[level].rank(false, r) - matrix[level].rank(false, l);
            std::tie(l, r) = succ(f, l, r, level);
        }
        return res;
    }

    /**
     * @brief count i s.t. (l <= i < r) && (lower <= v[i] < upper)
     *
     * @param l
     * @param r
     * @param lower
     * @param upper
     * @return int
     */
    int range_freq(int l, int r, T lower, T upper) const {
        return range_freq(l, r, upper) - range_freq(l, r, lower);
    }

    /**
     * @brief max v[i] s.t. (l <= i < r) && (v[i] < upper)
     *
     * @param l
     * @param r
     * @param upper
     * @return T
     */
    T prev_value(int l, int r, T upper) const {
        int cnt = range_freq(l, r, upper);
        return cnt == 0 ? T(-1) : kth_smallest(l, r, cnt - 1);
    }

    /**
     * @brief min v[i] s.t. (l <= i < r) && (lower <= v[i])
     *
     * @param l
     * @param r
     * @param lower
     * @return T
     */
    T next_value(int l, int r, T lower) const {
        int cnt = range_freq(l, r, lower);
        return cnt == r - l ? T(-1) : kth_smallest(l, r, cnt);
    }

  private:
    int length;
    bit_vector matrix[L];
    int mid[L];

    std::pair<int, int> succ(bool f, int l, int r, int level) const {
        return {matrix[level].rank(f, l) + mid[level] * f,
                matrix[level].rank(f, r) + mid[level] * f};
    }
};
#line 4 "/home/kuhaku/home/github/algo/lib/data_structure/compressed_wavelet_matrix.hpp"

/**
 * @brief ウェーブレット行列
 * @see https://ei1333.github.io/library/structure/wavelet/wavelet-matrix.hpp
 *
 * @tparam T
 * @tparam L
 */
template <class T, int L = 20>
struct compressed_wavelet_matrix {
    compressed_wavelet_matrix() = default;
    compressed_wavelet_matrix(const std::vector<T> &v) : cps(v) {
        int n = v.size();
        std::vector<int> t(n);
        for (int i = 0; i < n; ++i) t[i] = cps.get(v[i]);
        mat = wavelet_matrix<int, L>(t);
    }

    T access(int k) const { return cps[mat.access(k)]; }
    T operator[](int k) const { return access(k); }

    /**
     * @brief count i s.t. (0 <= i < r) && v[i] == x
     *
     * @param x
     * @param r
     * @return int
     */
    int rank(int r, T x) const {
        auto pos = cps.get(x);
        if (pos == cps.size() || cps[pos] != x) return 0;
        return mat.rank(r, pos);
    }

    /**
     * @brief count i s.t. (l <= i < r) && v[i] == x
     *
     * @param l
     * @param r
     * @param x
     * @return int
     */
    int rank(int l, int r, T x) const { return rank(r, x) - rank(l, x); }

    /**
     * @brief k-th smallest number in v[l ... r-1]
     *
     * @param l
     * @param r
     * @param k
     * @return T
     */
    T kth_smallest(int l, int r, int k) const { return cps[mat.kth_smallest(l, r, k)]; }

    /**
     * @brief k-th largest number in v[l ... r-1]
     *
     * @param l
     * @param r
     * @param k
     * @return T
     */
    T kth_largest(int l, int r, int k) const { return cps[mat.kth_largest(l, r, k)]; }

    /**
     * @brief count i s.t. (l <= i < r) && (v[i] < upper)
     *
     * @param l
     * @param r
     * @param upper
     * @return int
     */
    int range_freq(int l, int r, T upper) const { return mat.range_freq(l, r, cps.get(upper)); }

    /**
     * @brief count i s.t. (l <= i < r) && (lower <= v[i] < upper)
     *
     * @param l
     * @param r
     * @param lower
     * @param upper
     * @return int
     */
    int range_freq(int l, int r, T lower, T upper) const {
        return mat.range_freq(l, r, cps.get(lower), cps.get(upper));
    }

    /**
     * @brief max v[i] s.t. (l <= i < r) && (v[i] < upper)
     *
     * @param l
     * @param r
     * @param upper
     * @return T
     */
    T prev_value(int l, int r, T upper) const {
        auto res = mat.prev_value(l, r, cps.get(upper));
        return res == -1 ? T(-1) : cps[res];
    }

    /**
     * @brief min v[i] s.t. (l <= i < r) && (lower <= v[i])
     *
     * @param l
     * @param r
     * @param lower
     * @return T
     */
    T next_value(int l, int r, T lower) const {
        auto res = mat.next_value(l, r, cps.get(lower));
        return res == -1 ? T(-1) : cps[res];
    }

  private:
    wavelet_matrix<int, L> mat;
    coordinate_compression<T> cps;
};
#line 2 "/home/kuhaku/home/github/algo/lib/data_structure/wavelet_matrix_rectangle_sum.hpp"
#include <numeric>
#line 6 "/home/kuhaku/home/github/algo/lib/data_structure/wavelet_matrix_rectangle_sum.hpp"

template <class T, class U = T, int L = 30>
struct wavelet_matrix_rectangle_sum {
    wavelet_matrix_rectangle_sum() = default;
    template <class Value>
    wavelet_matrix_rectangle_sum(const std::vector<T> &v, const std::vector<Value> &u)
        : length(v.size()) {
        assert(v.size() == u.size());
        std::vector<int> l(length), r(length), ord(length);
        std::iota(ord.begin(), ord.end(), 0);
        for (int level = L - 1; level >= 0; level--) {
            matrix[level] = bit_vector(length + 1);
            int left = 0, right = 0;
            for (int i = 0; i < length; i++) {
                if ((v[ord[i]] >> level) & 1) {
                    matrix[level].set(i);
                    r[right++] = ord[i];
                } else {
                    l[left++] = ord[i];
                }
            }
            mid[level] = left;
            matrix[level].build();
            ord.swap(l);
            for (int i = 0; i < right; i++) ord[left + i] = r[i];
            cs[level].resize(length + 1);
            cs[level][0] = U(0);
            for (int i = 0; i < length; i++) cs[level][i + 1] = cs[level][i] + u[ord[i]];
        }
    }

    U range_sum(int r, T x) const { return range_sum(0, r, x); }

    U range_sum(int l, int r, T x) const {
        for (int level = L - 1; level >= 0; level--)
            std::tie(l, r) = succ((x >> level) & 1, l, r, level);
        return cs[0][matrix[0].rank(false, r)] - cs[0][matrix[0].rank(false, l)];
    }

    U rect_sum(int l, int r, T upper) const {
        U res = 0;
        for (int level = L - 1; level >= 0; level--) {
            bool f = (upper >> level) & 1;
            if (f)
                res += cs[level][matrix[level].rank(false, r)] -
                       cs[level][matrix[level].rank(false, l)];
            std::tie(l, r) = succ(f, l, r, level);
        }
        return res;
    }

    U rect_sum(int l, int r, T lower, T upper) const {
        return rect_sum(l, r, upper) - rect_sum(l, r, lower);
    }

  private:
    int length;
    bit_vector matrix[L];
    int mid[L];
    std::vector<U> cs[L];

    std::pair<int, int> succ(bool f, int l, int r, int level) const {
        return {matrix[level].rank(f, l) + mid[level] * f,
                matrix[level].rank(f, r) + mid[level] * f};
    }
};
#line 2 "/home/kuhaku/home/github/algo/lib/template/template.hpp"
#pragma GCC target("sse4.2,avx2,bmi2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
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
constexpr double PI = M_PI;
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
        std::cout << std::fixed << std::setprecision(20);
    }

    constexpr void operator()() const {}
} sonic;
#line 5 "/home/kuhaku/home/github/algo/lib/template/atcoder.hpp"
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
#line 5 "a.cpp"

int main(void) {
    int n;
    cin >> n;
    vector<pair<ll, ll>> a(n);
    rep (i, n) cin >> a[i];

    vector<ll> bx, by, cx, cy;
    rep (i, n) {
        auto [x, y] = a[i];
        if ((x + y) & 1) {
            bx.emplace_back(x + y);
            by.emplace_back(x - y);
        } else {
            cx.emplace_back(x + y);
            cy.emplace_back(x - y);
        }
    }

    ll ans = 0;
    rep (_, 2) {
        int s = bx.size();
        sort(all(bx));
        sort(all(by));
        rep (i, s) {
            ans += (bx[i] + by[i]) * i;
            ans -= (bx[i] + by[i]) * (s - 1 - i);
        }
        swap(bx, cx);
        swap(by, cy);
    }
    co(ans / 2);

    return 0;
}
