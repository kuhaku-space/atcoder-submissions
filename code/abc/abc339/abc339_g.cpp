#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/home/github/algo/lib/segment_tree/segment_tree.hpp"
#include <cassert>
#include <vector>
#line 2 "/home/kuhaku/home/github/algo/lib/internal/internal_bit.hpp"

namespace internal {

// @return same with std::bit::bit_ceil
unsigned int bit_ceil(unsigned int n) {
    unsigned int x = 1;
    while (x < (unsigned int)(n)) x *= 2;
    return x;
}

// @param n `1 <= n`
// @return same with std::bit::countr_zero
int countr_zero(unsigned int n) { return __builtin_ctz(n); }

// @param n `1 <= n`
// @return same with std::bit::countr_zero
constexpr int countr_zero_constexpr(unsigned int n) {
    int x = 0;
    while (!(n & (1 << x))) x++;
    return x;
}

}  // namespace internal
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
#line 6 "/home/kuhaku/home/github/algo/lib/segment_tree/segment_tree.hpp"

/**
 * @brief セグメント木
 * @see https://noshi91.hatenablog.com/entry/2020/04/22/212649
 *
 * @tparam M モノイド
 */
template <class M>
struct segment_tree {
  private:
    using T = typename M::value_type;

  public:
    segment_tree() : segment_tree(0) {}
    explicit segment_tree(int n, T e = M::id) : segment_tree(std::vector<T>(n, e)) {}
    template <class U>
    explicit segment_tree(const std::vector<U> &v) : _n(v.size()) {
        _size = internal::bit_ceil(_n);
        _log = internal::countr_zero(_size);
        data = std::vector<T>(_size << 1, M::id);
        for (int i = 0; i < _n; ++i) data[_size + i] = T(v[i]);
        for (int i = _size - 1; i >= 1; --i) update(i);
    }

    const T &operator[](int k) const { return data[k + _size]; }
    T at(int k) const { return operator[](k); }
    T get(int k) const { return operator[](k); }

    void set(int k, T val) {
        assert(0 <= k && k < _n);
        k += _size;
        data[k] = val;
        for (int i = 1; i <= _log; ++i) update(k >> i);
    }
    void reset(int k) { set(k, M::id); }

    T all_prod() const { return data[1]; }
    T prod(int a, int b) const {
        assert(0 <= a && b <= _n);
        T l = M::id, r = M::id;
        for (a += _size, b += _size; a < b; a >>= 1, b >>= 1) {
            if (a & 1) l = M::op(l, data[a++]);
            if (b & 1) r = M::op(data[--b], r);
        }
        return M::op(l, r);
    }

    template <class F>
    int max_right(F f) const {
        return max_right(0, f);
    }

    template <class F>
    int max_right(int l, F f) const {
        assert(0 <= l && l <= _n);
        assert(f(M::id));
        if (l == _n) return _n;
        l += _size;
        T sm = M::id;
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(M::op(sm, data[l]))) {
                while (l < _size) {
                    l = (2 * l);
                    if (f(M::op(sm, data[l]))) {
                        sm = M::op(sm, data[l]);
                        l++;
                    }
                }
                return l - _size;
            }
            sm = M::op(sm, data[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <class F>
    int min_left(F f) const {
        return min_left(_n, f);
    }

    template <class F>
    int min_left(int r, F f) const {
        assert(0 <= r && r <= _n);
        assert(f(M::id));
        if (r == 0) return 0;
        r += _size;
        T sm = M::id;
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(M::op(data[r], sm))) {
                while (r < _size) {
                    r = (2 * r + 1);
                    if (f(M::op(data[r], sm))) {
                        sm = M::op(data[r], sm);
                        r--;
                    }
                }
                return r + 1 - _size;
            }
            sm = M::op(data[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, _size, _log;
    std::vector<T> data;

    void update(int k) { data[k] = M::op(data[2 * k], data[2 * k + 1]); }
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
#line 3 "/home/kuhaku/home/github/algo/lib/binary_tree/range_tree.hpp"

/**
 * @brief 領域木
 *
 * @tparam M
 * @tparam T
 *
 * @see https://hitonanode.github.io/cplib-cpp/segmenttree/rangetree.hpp.html
 */
template <class M, class T = int>
struct range_tree {
  private:
    using Pt = std::pair<T, T>;
    using value_type = typename M::value_type;

  public:
    range_tree() = default;

    void add(T x, T y) noexcept { _pts.emplace_back(x, y); }

    void build() {
        std::sort(_pts.begin(), _pts.end());
        _pts.erase(std::unique(_pts.begin(), _pts.end()), _pts.end());
        _size = _pts.size();

        _range2yxs.resize(_size * 2);
        for (int i = 0; i < _size; i++) _range2yxs[_size + i] = {{_pts[i].second, _pts[i].first}};
        for (int i = _size - 1; i > 0; i--) {
            auto &lch = _range2yxs[i * 2];
            auto &rch = _range2yxs[i * 2 + 1];
            std::merge(lch.begin(), lch.end(), rch.begin(), rch.end(),
                       std::back_inserter(_range2yxs[i]));
            _range2yxs[i].erase(std::unique(_range2yxs[i].begin(), _range2yxs[i].end()),
                                _range2yxs[i].end());
        }
        for (const auto &v : _range2yxs) segtrees.emplace_back(v.size());
    }

    void set(T x, T y, value_type val) {
        int i = std::distance(_pts.begin(), std::lower_bound(_pts.begin(), _pts.end(), Pt{x, y}));
        assert(i < _size && _pts[i] == std::make_pair(x, y));
        for (i += _size; i; i >>= 1) set(i, {x, y}, val);
    }

    value_type prod(T xl, T yl, T xr, T yr) const {
        auto comp = [](const Pt &l, const Pt &r) {
            return l.first < r.first;
        };
        int l = _size + std::distance(_pts.begin(),
                                      std::lower_bound(_pts.begin(), _pts.end(), Pt{xl, yr}, comp));
        int r = _size + std::distance(_pts.begin(),
                                      std::lower_bound(_pts.begin(), _pts.end(), Pt{xr, yr}, comp));
        value_type res = M::id;
        while (l < r) {
            if (l & 1) res = M::op(res, prod(l++, yl, yr));
            if (r & 1) res = M::op(res, prod(--r, yl, yr));
            l >>= 1, r >>= 1;
        }
        return res;
    }
    value_type get(T x, T y) const {
        int i = std::distance(_pts.begin(), std::lower_bound(_pts.begin(), _pts.end(), Pt{x, y}));
        return i < _size && _pts[i] == std::make_pair(x, y) ? segtrees[_size + i].get(0) : M::id;
    }

  private:
    int _size;
    std::vector<Pt> _pts;
    std::vector<std::vector<Pt>> _range2yxs;
    std::vector<segment_tree<M>> segtrees;

    void set(int v, Pt p, value_type val) {
        auto i = std::distance(
            _range2yxs[v].begin(),
            std::lower_bound(_range2yxs[v].begin(), _range2yxs[v].end(), Pt{p.second, p.first}));
        segtrees[v].set(i, val);
    }

    value_type prod(int v, T yl, T yr) const {
        auto comp = [&](const Pt &l, const Pt &r) {
            return l.first < r.first;
        };
        auto il = std::distance(
            _range2yxs[v].begin(),
            std::lower_bound(_range2yxs[v].begin(), _range2yxs[v].end(), Pt{yl, yl}, comp));
        auto ir = std::distance(
            _range2yxs[v].begin(),
            std::lower_bound(_range2yxs[v].begin(), _range2yxs[v].end(), Pt{yr, yr}, comp));
        return segtrees[v].prod(il, ir);
    }
};
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
#line 4 "a.cpp"

int main(void) {
    int n;
    cin >> n;
    vector<ll> a(n);
    cin >> a;

    range_tree<Add<ll>> st;
    rep (i, n) st.add(i, a[i]);
    st.build();
    rep (i, n) st.set(i, a[i], a[i]);

    int q;
    cin >> q;
    ll ans = 0;
    while (q--) {
        ll l, r, x;
        cin >> l >> r >> x;
        l ^= ans;
        r ^= ans;
        x ^= ans;
        ans = st.prod(l - 1, 0, r, x + 1);
        co(ans);
    }

    return 0;
}
