#line 1 "a.cpp"
#define PROBLEM ""
#line 1 "/home/kuhaku/home/github/algo/lib/data_structure/wavelet_matrix_rectangle_sum.hpp"
#include <cassert>
#include <numeric>
#include <tuple>
#include <vector>
#line 2 "/home/kuhaku/home/github/algo/lib/data_structure/bit_vector.hpp"

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
#line 2 "/home/kuhaku/home/github/algo/lib/segment_tree/monoid.hpp"
#include <algorithm>
#include <limits>
#include <utility>

template <class T>
struct Add {
    using value_type = T;
    static constexpr T id = T(0);
    static constexpr T op(const T &lhs, const T &rhs) { return lhs + rhs; }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs + rhs;
    }
};

template <class T>
struct And {
    using value_type = T;
    static constexpr T id = std::numeric_limits<T>::max();
    static constexpr T op(const T &lhs, const T &rhs) { return lhs & rhs; }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs & rhs;
    }
};

template <class T>
struct Or {
    using value_type = T;
    static constexpr T id = T(0);
    static constexpr T op(const T &lhs, const T &rhs) { return lhs | rhs; }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs | rhs;
    }
};

template <class T>
struct Xor {
    using value_type = T;
    static constexpr T id = T(0);
    static constexpr T op(const T &lhs, const T &rhs) { return lhs ^ rhs; }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs ^ rhs;
    }
};

template <class T>
struct Min {
    using value_type = T;
    static constexpr T id = std::numeric_limits<T>::max();
    static constexpr T op(const T &lhs, const T &rhs) { return std::min(lhs, rhs); }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return std::min((U)lhs, rhs);
    }
};

template <class T>
struct Max {
    using value_type = T;
    static constexpr T id = std::numeric_limits<T>::min();
    static constexpr T op(const T &lhs, const T &rhs) { return std::max(lhs, rhs); }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return std::max((U)lhs, rhs);
    }
};

template <class T>
struct Update {
    using value_type = T;
    static constexpr T id = std::numeric_limits<T>::max();
    static constexpr T op(const T &lhs, const T &rhs) { return lhs == Update::id ? rhs : lhs; }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs == Update::id ? rhs : lhs;
    }
};

template <class T>
struct Affine {
    using value_type = std::pair<T, T>;
    static constexpr std::pair<T, T> id = std::pair<T, T>(1, 0);
    static constexpr std::pair<T, T> op(std::pair<T, T> lhs, std::pair<T, T> rhs) {
        return {lhs.first * rhs.first, lhs.first * rhs.second + lhs.second};
    }
};

template <class M>
struct Rev {
    using T = typename M::value_type;
    using value_type = T;
    static constexpr T id = M::id;
    static constexpr T op(T lhs, T rhs) { return M::op(rhs, lhs); }
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

template <class T, class U, int L = 30>
struct wavelet_matrix_monoid {
    wavelet_matrix_monoid() = default;
    wavelet_matrix_monoid(const std::vector<T> &v, const std::vector<U> &u) : length(v.size()) {
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
            for (int i = 0; i < right; i++) {
                ord[left + i] = r[i];
            }
            ds[level].resize(length + 1);
            ds[level][0] = U(0);
            for (int i = 0; i < length; i++) {
                ds[level][i + 1] = ds[level][i] + u[ord[i]];
            }
        }
    }

    U rect_sum(int l, int r, T upper) {
        U res = 0;
        for (int level = L - 1; level >= 0; level--) {
            bool f = (upper >> level) & 1;
            if (f)
                res += ds[level][matrix[level].rank(false, r)] -
                       ds[level][matrix[level].rank(false, l)];
            std::tie(l, r) = succ(f, l, r, level);
        }
        return res;
    }

    U rect_sum(int l, int r, T lower, T upper) {
        return rect_sum(l, r, upper) - rect_sum(l, r, lower);
    }

  private:
    int length;
    bit_vector matrix[L];
    int mid[L];
    std::vector<U> ds[L];

    std::pair<int, int> succ(bool f, int l, int r, int level) const {
        return {matrix[level].rank(f, l) + mid[level] * f,
                matrix[level].rank(f, r) + mid[level] * f};
    }
};

int main(void) {
    int n;
    cin >> n;
    vector<ll> a(n);
    cin >> a;

    wavelet_matrix_monoid<ll, ll> st(a, a);
    int q;
    cin >> q;
    ll ans = 0;
    while (q--) {
        ll l, r, x;
        cin >> l >> r >> x;
        l ^= ans;
        r ^= ans;
        x ^= ans;
        ans = st.rect_sum(l - 1, r, 0, x + 1);
        co(ans);
    }

    return 0;
}
