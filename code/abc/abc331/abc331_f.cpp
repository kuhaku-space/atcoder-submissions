#line 1 "a.cpp"
#define PROBLEM ""
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
#line 3 "/home/kuhaku/home/github/algo/lib/math/hashint.hpp"

struct HashInt {
    static constexpr std::uint64_t get_mod() noexcept { return mod; }

    constexpr HashInt() noexcept : x(0) {}
    constexpr HashInt(int y) noexcept : x(y >= 0 ? y % mod : (mod - 1 - ~y % mod)) {}
    constexpr HashInt(unsigned int y) noexcept : x(y % mod) {}
    constexpr HashInt(long y) noexcept : x(y >= 0 ? y % mod : (mod - 1 - ~y % mod)) {}
    constexpr HashInt(unsigned long y) noexcept : x(y % mod) {}
    constexpr HashInt(long long y) noexcept : x(y >= 0 ? y % mod : (mod - 1 - ~y % mod)) {}
    constexpr HashInt(unsigned long long y) noexcept : x(y % mod) {}

    constexpr HashInt &operator+=(const HashInt &rhs) noexcept {
        if ((this->x += rhs.x) >= mod) this->x -= mod;
        return *this;
    }
    constexpr HashInt &operator-=(const HashInt &rhs) noexcept {
        if ((this->x += mod - rhs.x) >= mod) this->x -= mod;
        return *this;
    }
    constexpr HashInt &operator*=(const HashInt &rhs) noexcept {
        std::uint64_t au = this->x >> 31, ad = this->x & this->mask31;
        std::uint64_t bu = rhs.x >> 31, bd = rhs.x & this->mask31;
        std::uint64_t mid = ad * bu + au * bd;
        std::uint64_t midu = mid >> 30, midd = mid & this->mask30;
        this->x = this->_mod(au * bu * 2 + midu + (midd << 31) + ad * bd);
        return *this;
    }
    constexpr HashInt &operator/=(const HashInt &rhs) noexcept {
        *this *= rhs.inverse();
        return *this;
    }

    constexpr HashInt &operator++() noexcept {
        if ((++(this->x)) >= mod) this->x -= mod;
        return *this;
    }
    constexpr HashInt operator++(int) noexcept {
        HashInt tmp(*this);
        this->operator++();
        return tmp;
    }
    constexpr HashInt &operator--() noexcept {
        if ((this->x += mod - 1) >= mod) this->x -= mod;
        return *this;
    }
    constexpr HashInt operator--(int) noexcept {
        HashInt tmp(*this);
        this->operator--();
        return tmp;
    }

    constexpr HashInt operator-() const noexcept { return HashInt(-this->x); }
    constexpr HashInt operator+(const HashInt &rhs) const noexcept { return HashInt(*this) += rhs; }
    constexpr HashInt operator-(const HashInt &rhs) const noexcept { return HashInt(*this) -= rhs; }
    constexpr HashInt operator*(const HashInt &rhs) const noexcept { return HashInt(*this) *= rhs; }
    constexpr HashInt operator/(const HashInt &rhs) const noexcept { return HashInt(*this) /= rhs; }

    constexpr bool operator==(const HashInt &rhs) const noexcept { return this->x == rhs.x; }
    constexpr bool operator!=(const HashInt &rhs) const noexcept { return this->x != rhs.x; }

    constexpr explicit operator long() const noexcept { return x; }
    constexpr explicit operator unsigned long() const noexcept { return x; }
    constexpr explicit operator long long() const noexcept { return x; }
    constexpr explicit operator unsigned long long() const noexcept { return x; }

    constexpr HashInt inverse() const noexcept {
        std::int64_t a = x, b = mod, u = 1, v = 0, t = 0;
        while (b > 0) {
            t = a / b;
            std::swap(a -= t * b, b);
            std::swap(u -= t * v, v);
        }
        return HashInt(u);
    }

    constexpr HashInt pow(std::uint64_t n) const noexcept { return HashInt(*this).pow_self(n); }
    constexpr HashInt &pow_self(std::uint64_t n) noexcept {
        HashInt res(1);
        for (; n > 0; n >>= 1) {
            if (n & 1) res *= *this;
            *this *= *this;
        }
        *this = res;
        return *this;
    }

  private:
    std::uint64_t x;

    static constexpr std::uint64_t mod = (1ul << 61) - 1;
    static constexpr std::uint64_t mask30 = (1ul << 30) - 1;
    static constexpr std::uint64_t mask31 = (1ul << 31) - 1;

    constexpr std::uint64_t _mod(std::uint64_t x) const {
        std::uint64_t xu = x >> 61, xd = x & this->mod;
        std::uint64_t res = xu + xd;
        if (res >= this->mod) res -= this->mod;
        return res;
    }
};
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
#line 5 "/home/kuhaku/home/github/algo/lib/segment_tree/monoid.hpp"

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
#line 5 "/home/kuhaku/home/github/algo/lib/segment_tree/segment_tree.hpp"

/**
 * @brief セグメント木
 *
 * @tparam M モノイド
 *
 * @see https://noshi91.hatenablog.com/entry/2020/04/22/212649
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

vector<HashInt> p(1000006);

struct S {
    HashInt value;
    int len;
};

struct M {
    using T = S;
    using value_type = T;
    static constexpr T id = T(0, 0);
    static constexpr T op(const T &lhs, const T &rhs) {
        return S{lhs.value + rhs.value * p[lhs.len], lhs.len + rhs.len};
    }
};

int main(void) {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    {
        p[0] = 1;
        random_device seed;
        mt19937_64 mt(seed());
        HashInt x = mt();
        rep (i, 1000005) p[i + 1] = p[i] * x;
    }

    segment_tree<M> sta(n), stb(n);
    rep (i, n) {
        sta.set(i, S{HashInt(s[i]), 1});
        stb.set(n - 1 - i, S{HashInt(s[i]), 1});
    }

    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int x;
            char c;
            cin >> x >> c;
            --x;
            sta.set(x, S{HashInt(c), 1});
            stb.set(n - 1 - x, S{HashInt(c), 1});
        } else {
            int l, r;
            cin >> l >> r;
            --l;
            Yes(sta.prod(l, r).value == stb.prod(n - r, n - l).value);
        }
    }

    return 0;
}
