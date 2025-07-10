// competitive-verifier: PROBLEM
#pragma GCC optimize("Ofast,fast-math,unroll-all-loops")
#include <bits/stdc++.h>
#if !defined(ATCODER) && !defined(EVAL)
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
#define FORR(i, m, n) for (int i = (m) - 1; i >= int(n); --i)
#define FORL(i, m, n) for (std::int64_t i = (m); i < std::int64_t(n); ++i)
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
struct increment_impl {
    template <class T>
    const increment_impl &operator>>(std::vector<T> &v) const {
        for (auto &x : v) ++x;
        return *this;
    }
} Inc;
struct decrement_impl {
    template <class T>
    const decrement_impl &operator>>(std::vector<T> &v) const {
        for (auto &x : v) --x;
        return *this;
    }
} Dec;
struct sort_impl {
    template <class T>
    const sort_impl &operator>>(std::vector<T> &v) const {
        std::sort(v.begin(), v.end());
        return *this;
    }
} Sort;
struct unique_impl {
    template <class T>
    const unique_impl &operator>>(std::vector<T> &v) const {
        std::sort(v.begin(), v.end());
        v.erase(std::unique(v.begin(), v.end()), v.end());
        return *this;
    }
} Uniq;
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
#include <concepts>
#include <type_traits>
namespace internal {
/// @param m `1 <= m`
/// @return x mod m
constexpr std::int64_t safe_mod(std::int64_t x, std::int64_t m) {
    x %= m;
    if (x < 0) x += m;
    return x;
}
/// Fast modular multiplication by barrett reduction
/// Reference: https://en.wikipedia.org/wiki/Barrett_reduction
/// NOTE: reconsider after Ice Lake
struct barrett {
    unsigned int _m;
    std::uint64_t im;
    // @param m `1 <= m`
    explicit barrett(unsigned int m) : _m(m), im((std::uint64_t)(-1) / m + 1) {}
    // @return m
    unsigned int umod() const { return _m; }
    // @param a `0 <= a < m`
    // @param b `0 <= b < m`
    // @return `a * b % m`
    unsigned int mul(unsigned int a, unsigned int b) const {
        std::uint64_t z = a;
        z *= b;
        std::uint64_t x = (std::uint64_t)(((__uint128_t)(z)*im) >> 64);
        std::uint64_t y = x * _m;
        return (unsigned int)(z - y + (z < y ? _m : 0));
    }
};
/// @brief Montgomery modular multiplication
/// @see https://rsk0315.hatenablog.com/entry/2022/11/27/060616
struct montgomery {
    /// @param m `1 <= m`
    explicit constexpr montgomery(std::uint64_t m)
        : _m(m), im(m), r((__uint128_t(1) << 64) % m), r2(-__uint128_t(m) % m) {
        for (int i = 0; i < 5; ++i) im = im * (2 - _m * im);
        im = -im;
    }
    /// @return m
    constexpr std::uint64_t umod() const { return _m; }
    /// @param a `0 <= a < m`
    /// @param b `0 <= b < m`
    /// @return `a * b % m`
    constexpr std::uint64_t mul(std::uint64_t a, std::uint64_t b) const {
        return mr((__uint128_t)a * mr((__uint128_t)b * r2));
    }
    constexpr std::uint64_t exp(std::uint64_t a, std::uint64_t b) const {
        std::uint64_t res = 1, p = mr((__uint128_t)a * r2);
        while (b) {
            if (b & 1) res = mr((__uint128_t)res * p);
            p = mr((__uint128_t)p * p);
            b >>= 1;
        }
        return res;
    }
    constexpr bool same_pow(std::uint64_t x, int s, std::uint64_t n) const {
        x = mr((__uint128_t)x * r2), n = mr((__uint128_t)n * r2);
        for (int r = 0; r < s; r++) {
            if (x == n) return true;
            x = mr((__uint128_t)x * x);
        }
        return false;
    }
  private:
    std::uint64_t _m, im, r, r2;
    constexpr std::uint64_t mr(std::uint64_t x) const {
        std::uint64_t res = (__uint128_t(x * im) * _m + x) >> 64;
        return res >= _m ? res - _m : res;
    }
    constexpr std::uint64_t mr(__uint128_t x) const {
        std::uint64_t res = (__uint128_t(std::uint64_t(x) * im) * _m + x) >> 64;
        return res >= _m ? res - _m : res;
    }
    constexpr std::uint64_t mr(std::uint64_t a, std::uint64_t b) const {
        __uint128_t t = (__uint128_t)a * b;
        std::uint64_t x = t >> 64, y = t;
        x = mr((__uint128_t)x * r), y = mr(y);
        return x + y >= _m ? x + y - _m : x + y;
    }
};
constexpr bool is_SPRP32(std::uint32_t n, std::uint32_t a) {
    std::uint32_t d = n - 1, s = 0;
    while ((d & 1) == 0) ++s, d >>= 1;
    std::uint64_t cur = 1, pw = d;
    while (pw) {
        if (pw & 1) cur = (cur * a) % n;
        a = (std::uint64_t)a * a % n;
        pw >>= 1;
    }
    if (cur == 1) return true;
    for (std::uint32_t r = 0; r < s; r++) {
        if (cur == n - 1) return true;
        cur = cur * cur % n;
    }
    return false;
}
/// given 2 <= n,a < 2^64, a prime, check whether n is a-SPRP
/// without 2,3,5,13,19,73,193,407521,299210837
constexpr bool is_SPRP64(const montgomery &m, std::uint64_t a) {
    auto n = m.umod();
    std::uint64_t d = n - 1;
    int s = 0;
    while ((d & 1) == 0) ++s, d >>= 1;
    std::uint64_t cur = m.exp(a, d);
    if (cur == 1) return true;
    return m.same_pow(cur, s, n - 1);
}
constexpr bool is_prime_constexpr(std::uint32_t x) {
    if (x == 2 || x == 3 || x == 5 || x == 7) return true;
    if (x % 2 == 0 || x % 3 == 0 || x % 5 == 0 || x % 7 == 0) return false;
    if (x < 121) return (x > 1);
    std::uint64_t h = x;
    h = ((h >> 16) ^ h) * 0x45d9f3b;
    h = ((h >> 16) ^ h) * 0x45d9f3b;
    h = ((h >> 16) ^ h) & 255;
    constexpr uint16_t bases[] = {
        15591, 2018,  166,  7429, 8064,  16045, 10503, 4399,  1949,  1295,  2776, 3620,  560,   3128,  5212,  2657,
        2300,  2021,  4652, 1471, 9336,  4018,  2398,  20462, 10277, 8028,  2213, 6219,  620,   3763,  4852,  5012,
        3185,  1333,  6227, 5298, 1074,  2391,  5113,  7061,  803,   1269,  3875, 422,   751,   580,   4729,  10239,
        746,   2951,  556,  2206, 3778,  481,   1522,  3476,  481,   2487,  3266, 5633,  488,   3373,  6441,  3344,
        17,    15105, 1490, 4154, 2036,  1882,  1813,  467,   3307,  14042, 6371, 658,   1005,  903,   737,   1887,
        7447,  1888,  2848, 1784, 7559,  3400,  951,   13969, 4304,  177,   41,   19875, 3110,  13221, 8726,  571,
        7043,  6943,  1199, 352,  6435,  165,   1169,  3315,  978,   233,   3003, 2562,  2994,  10587, 10030, 2377,
        1902,  5354,  4447, 1555, 263,   27027, 2283,  305,   669,   1912,  601,  6186,  429,   1930,  14873, 1784,
        1661,  524,   3577, 236,  2360,  6146,  2850,  55637, 1753,  4178,  8466, 222,   2579,  2743,  2031,  2226,
        2276,  374,   2132, 813,  23788, 1610,  4422,  5159,  1725,  3597,  3366, 14336, 579,   165,   1375,  10018,
        12616, 9816,  1371, 536,  1867,  10864, 857,   2206,  5788,  434,   8085, 17618, 727,   3639,  1595,  4944,
        2129,  2029,  8195, 8344, 6232,  9183,  8126,  1870,  3296,  7455,  8947, 25017, 541,   19115, 368,   566,
        5674,  411,   522,  1027, 8215,  2050,  6544,  10049, 614,   774,   2333, 3007,  35201, 4706,  1152,  1785,
        1028,  1540,  3743, 493,  4474,  2521,  26845, 8354,  864,   18915, 5465, 2447,  42,    4511,  1660,  166,
        1249,  6259,  2553, 304,  272,   7286,  73,    6554,  899,   2816,  5197, 13330, 7054,  2818,  3199,  811,
        922,   350,   7514, 4452, 3449,  2663,  4708,  418,   1621,  1171,  3471, 88,    11345, 412,   1559,  194};
    return is_SPRP32(x, bases[h]);
}
constexpr bool is_prime_constexpr(std::uint64_t x) {
    if (x <= std::numeric_limits<std::uint32_t>::max()) return is_prime_constexpr((std::uint32_t)x);
    if (x % 2 == 0 || x % 3 == 0 || x % 5 == 0 || x % 7 == 0) return false;
    montgomery m(x);
    constexpr std::uint64_t bases[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    for (auto a : bases) {
        if (!is_SPRP64(m, a)) return false;
    }
    return true;
}
constexpr bool is_prime_constexpr(std::int64_t x) {
    if (x < 0) return false;
    return is_prime_constexpr(std::uint64_t(x));
}
/// @param n `0 <= n`
/// @param m `1 <= m`
/// @return `(x ** n) % m`
constexpr std::int64_t pow_mod_constexpr(std::int64_t x, std::int64_t n, int m) {
    if (m == 1) return 0;
    unsigned int _m = (unsigned int)(m);
    std::uint64_t r = 1;
    std::uint64_t y = safe_mod(x, m);
    while (n) {
        if (n & 1) r = (r * y) % _m;
        y = (y * y) % _m;
        n >>= 1;
    }
    return r;
}
/// Reference:
/// M. Forisek and J. Jancina,
/// Fast Primality Testing for Integers That Fit into a Machine Word
/// @param n `0 <= n`
constexpr bool is_prime_constexpr(int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 7 || n == 61) return true;
    if (n % 2 == 0) return false;
    std::int64_t d = n - 1;
    while (d % 2 == 0) d /= 2;
    constexpr std::int64_t bases[3] = {2, 7, 61};
    for (std::int64_t a : bases) {
        std::int64_t t = d;
        std::int64_t y = pow_mod_constexpr(a, t, n);
        while (t != n - 1 && y != 1 && y != n - 1) {
            y = y * y % n;
            t <<= 1;
        }
        if (y != n - 1 && t % 2 == 0) { return false; }
    }
    return true;
}
template <int n>
constexpr bool is_prime = is_prime_constexpr(n);
/// @param b `1 <= b`
/// @return pair(g, x) s.t. g = gcd(a, b), xa = g (mod b), 0 <= x < b/g
constexpr std::pair<std::int64_t, std::int64_t> inv_gcd(std::int64_t a, std::int64_t b) {
    a = safe_mod(a, b);
    if (a == 0) return {b, 0};
    std::int64_t s = b, t = a;
    std::int64_t m0 = 0, m1 = 1;
    while (t) {
        std::int64_t u = s / t;
        s -= t * u;
        m0 -= m1 * u;
        auto tmp = s;
        s = t;
        t = tmp;
        tmp = m0;
        m0 = m1;
        m1 = tmp;
    }
    if (m0 < 0) m0 += b / s;
    return {s, m0};
}
/// Compile time primitive root
/// @param m must be prime
/// @return primitive root (and minimum in now)
constexpr int primitive_root_constexpr(int m) {
    if (m == 2) return 1;
    if (m == 167772161) return 3;
    if (m == 469762049) return 3;
    if (m == 754974721) return 11;
    if (m == 998244353) return 3;
    int divs[20] = {};
    divs[0] = 2;
    int cnt = 1;
    int x = (m - 1) / 2;
    while (x % 2 == 0) x /= 2;
    for (int i = 3; (std::int64_t)(i)*i <= x; i += 2) {
        if (x % i == 0) {
            divs[cnt++] = i;
            while (x % i == 0) { x /= i; }
        }
    }
    if (x > 1) { divs[cnt++] = x; }
    for (int g = 2;; g++) {
        bool ok = true;
        for (int i = 0; i < cnt; i++) {
            if (pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
}
template <int m>
constexpr int primitive_root = primitive_root_constexpr(m);
}  // namespace internal
namespace internal {
struct modint_base {};
struct static_modint_base : modint_base {};
template <class T>
using is_modint = std::is_base_of<modint_base, T>;
template <class T>
using is_modint_t = std::enable_if_t<is_modint<T>::value>;
}  // namespace internal
template <int m>
requires(m >= 1)
struct static_modint : internal::static_modint_base {
    using mint = static_modint;
  public:
    static constexpr int mod() { return m; }
    static constexpr mint raw(int v) {
        mint x;
        x._v = v;
        return x;
    }
    constexpr static_modint() : _v(0) {}
    template <std::integral T>
    constexpr static_modint(T v) : _v(0) {
        std::int64_t x = (std::int64_t)(v % (std::int64_t)(umod()));
        if (x < 0) x += umod();
        _v = (unsigned int)(x);
    }
    template <std::unsigned_integral T>
    constexpr static_modint(T v) : _v(0) {
        _v = (unsigned int)(v % umod());
    }
    constexpr unsigned int val() const { return _v; }
    constexpr mint &operator++() {
        _v++;
        if (_v == umod()) _v = 0;
        return *this;
    }
    constexpr mint &operator--() {
        if (_v == 0) _v = umod();
        _v--;
        return *this;
    }
    constexpr mint operator++(int) {
        mint result = *this;
        ++*this;
        return result;
    }
    constexpr mint operator--(int) {
        mint result = *this;
        --*this;
        return result;
    }
    constexpr mint &operator+=(const mint &rhs) {
        _v += rhs._v;
        if (_v >= umod()) _v -= umod();
        return *this;
    }
    constexpr mint &operator-=(const mint &rhs) {
        _v -= rhs._v;
        if (_v >= umod()) _v += umod();
        return *this;
    }
    constexpr mint &operator*=(const mint &rhs) {
        std::uint64_t z = _v;
        z *= rhs._v;
        _v = (unsigned int)(z % umod());
        return *this;
    }
    constexpr mint &operator/=(const mint &rhs) { return *this *= rhs.inv(); }
    constexpr mint operator+() const { return *this; }
    constexpr mint operator-() const { return mint() - *this; }
    constexpr mint pow(std::int64_t n) const {
        assert(0 <= n);
        mint x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    constexpr mint inv() const {
        if (prime) {
            assert(_v);
            return pow(umod() - 2);
        } else {
            auto eg = internal::inv_gcd(_v, m);
            assert(eg.first == 1);
            return eg.second;
        }
    }
    friend constexpr mint operator+(const mint &lhs, const mint &rhs) { return mint(lhs) += rhs; }
    friend constexpr mint operator-(const mint &lhs, const mint &rhs) { return mint(lhs) -= rhs; }
    friend constexpr mint operator*(const mint &lhs, const mint &rhs) { return mint(lhs) *= rhs; }
    friend constexpr mint operator/(const mint &lhs, const mint &rhs) { return mint(lhs) /= rhs; }
    friend constexpr bool operator==(const mint &lhs, const mint &rhs) { return lhs._v == rhs._v; }
    friend constexpr bool operator!=(const mint &lhs, const mint &rhs) { return lhs._v != rhs._v; }
    friend std::istream &operator>>(std::istream &is, mint &rhs) {
        std::int64_t t;
        is >> t;
        rhs = mint(t);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const mint &rhs) { return os << rhs._v; }
  private:
    unsigned int _v;
    static constexpr unsigned int umod() { return m; }
    static constexpr bool prime = internal::is_prime<m>;
};
template <int id>
struct dynamic_modint : internal::modint_base {
    using mint = dynamic_modint;
  public:
    static int mod() { return (int)(bt.umod()); }
    static void set_mod(int m) {
        assert(1 <= m);
        bt = internal::barrett(m);
    }
    static mint raw(int v) {
        mint x;
        x._v = v;
        return x;
    }
    dynamic_modint() : _v(0) {}
    template <std::integral T>
    dynamic_modint(T v) {
        std::int64_t x = (std::int64_t)(v % (std::int64_t)(mod()));
        if (x < 0) x += mod();
        _v = (unsigned int)(x);
    }
    template <std::unsigned_integral T>
    dynamic_modint(T v) {
        _v = (unsigned int)(v % mod());
    }
    unsigned int val() const { return _v; }
    mint &operator++() {
        _v++;
        if (_v == umod()) _v = 0;
        return *this;
    }
    mint &operator--() {
        if (_v == 0) _v = umod();
        _v--;
        return *this;
    }
    mint operator++(int) {
        mint result = *this;
        ++*this;
        return result;
    }
    mint operator--(int) {
        mint result = *this;
        --*this;
        return result;
    }
    mint &operator+=(const mint &rhs) {
        _v += rhs._v;
        if (_v >= umod()) _v -= umod();
        return *this;
    }
    mint &operator-=(const mint &rhs) {
        _v += mod() - rhs._v;
        if (_v >= umod()) _v -= umod();
        return *this;
    }
    mint &operator*=(const mint &rhs) {
        _v = bt.mul(_v, rhs._v);
        return *this;
    }
    mint &operator/=(const mint &rhs) { return *this *= rhs.inv(); }
    mint operator+() const { return *this; }
    mint operator-() const { return mint() - *this; }
    mint pow(std::int64_t n) const {
        assert(0 <= n);
        mint x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    mint inv() const {
        auto eg = internal::inv_gcd(_v, mod());
        assert(eg.first == 1);
        return eg.second;
    }
    friend mint operator+(const mint &lhs, const mint &rhs) { return mint(lhs) += rhs; }
    friend mint operator-(const mint &lhs, const mint &rhs) { return mint(lhs) -= rhs; }
    friend mint operator*(const mint &lhs, const mint &rhs) { return mint(lhs) *= rhs; }
    friend mint operator/(const mint &lhs, const mint &rhs) { return mint(lhs) /= rhs; }
    friend bool operator==(const mint &lhs, const mint &rhs) { return lhs._v == rhs._v; }
    friend bool operator!=(const mint &lhs, const mint &rhs) { return lhs._v != rhs._v; }
    friend std::istream &operator>>(std::istream &is, mint &rhs) {
        std::int64_t t;
        is >> t;
        rhs = mint(t);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const mint &rhs) { return os << rhs._v; }
  private:
    unsigned int _v;
    static internal::barrett bt;
    static unsigned int umod() { return bt.umod(); }
};
template <int id>
internal::barrett dynamic_modint<id>::bt(998244353);
using modint998 = static_modint<998244353>;
using modint107 = static_modint<1000000007>;
using modint = dynamic_modint<-1>;
namespace internal {
template <class T>
using is_static_modint = std::is_base_of<internal::static_modint_base, T>;
template <class T>
using is_static_modint_t = std::enable_if_t<is_static_modint<T>::value>;
template <class>
struct is_dynamic_modint : public std::false_type {};
template <int id>
struct is_dynamic_modint<dynamic_modint<id>> : public std::true_type {};
template <class T>
using is_dynamic_modint_t = std::enable_if_t<is_dynamic_modint<T>::value>;
}  // namespace internal
#include <bit>
template <class T>
struct Add {
    using value_type = T;
    static constexpr T id() { return T(); }
    static constexpr T op(const T &lhs, const T &rhs) { return lhs + rhs; }
    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs + rhs;
    }
};
template <class T>
struct Mul {
    using value_type = T;
    static constexpr T id() { return T(1); }
    static constexpr T op(const T &lhs, const T &rhs) { return lhs * rhs; }
    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs * rhs;
    }
};
template <class T>
struct And {
    using value_type = T;
    static constexpr T id() { return std::numeric_limits<T>::max(); }
    static constexpr T op(const T &lhs, const T &rhs) { return lhs & rhs; }
    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs & rhs;
    }
};
template <class T>
struct Or {
    using value_type = T;
    static constexpr T id() { return T(); }
    static constexpr T op(const T &lhs, const T &rhs) { return lhs | rhs; }
    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs | rhs;
    }
};
template <class T>
struct Xor {
    using value_type = T;
    static constexpr T id() { return T(); }
    static constexpr T op(const T &lhs, const T &rhs) { return lhs ^ rhs; }
    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs ^ rhs;
    }
};
template <class T>
struct Min {
    using value_type = T;
    static constexpr T id() { return std::numeric_limits<T>::max(); }
    static constexpr T op(const T &lhs, const T &rhs) { return std::min(lhs, rhs); }
    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return std::min((U)lhs, rhs);
    }
};
template <class T>
struct Max {
    using value_type = T;
    static constexpr T id() { return std::numeric_limits<T>::lowest(); }
    static constexpr T op(const T &lhs, const T &rhs) { return std::max(lhs, rhs); }
    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return std::max((U)lhs, rhs);
    }
};
template <class T>
struct Gcd {
    using value_type = T;
    static constexpr T id() { return std::numeric_limits<T>::max(); }
    static constexpr T op(const T &lhs, const T &rhs) {
        return lhs == Gcd::id() ? rhs : (rhs == Gcd::id() ? lhs : std::gcd(lhs, rhs));
    }
};
template <class T>
struct Lcm {
    using value_type = T;
    static constexpr T id() { return std::numeric_limits<T>::max(); }
    static constexpr T op(const T &lhs, const T &rhs) {
        return lhs == Lcm::id() ? rhs : (rhs == Lcm::id() ? lhs : std::lcm(lhs, rhs));
    }
};
template <class T>
struct Update {
    using value_type = T;
    static constexpr T id() { return std::numeric_limits<T>::max(); }
    static constexpr T op(const T &lhs, const T &rhs) { return lhs == Update::id() ? rhs : lhs; }
    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs == Update::id() ? rhs : lhs;
    }
};
template <class T>
struct Affine {
    using P = std::pair<T, T>;
    using value_type = P;
    static constexpr P id() { return P(1, 0); }
    static constexpr P op(P lhs, P rhs) {
        return {lhs.first * rhs.first, lhs.first * rhs.second + lhs.second};
    }
};
template <class M>
struct Rev {
    using T = typename M::value_type;
    using value_type = T;
    static constexpr T id() { return M::id(); }
    static constexpr T op(T lhs, T rhs) { return M::op(rhs, lhs); }
};
/// @brief セグメント木
/// @see https://noshi91.hatenablog.com/entry/2020/04/22/212649
template <class M>
struct segment_tree {
  private:
    using T = typename M::value_type;
    struct _segment_tree_reference {
      private:
        segment_tree<M> &self;
        int k;
      public:
        _segment_tree_reference(segment_tree<M> &self, int k) : self(self), k(k) {}
        _segment_tree_reference &operator=(const T &x) {
            self.set(k, x);
            return *this;
        }
        _segment_tree_reference &operator=(T &&x) {
            self.set(k, std::move(x));
            return *this;
        }
        operator T() const { return self.get(k); }
    };
  public:
    segment_tree() : segment_tree(0) {}
    explicit segment_tree(int n, T e = M::id()) : segment_tree(std::vector<T>(n, e)) {}
    template <class U>
    explicit segment_tree(const std::vector<U> &v) : _n(v.size()) {
        _size = std::bit_ceil<unsigned>(_n);
        _log = std::countr_zero<unsigned>(_size);
        data = std::vector<T>(_size << 1, M::id());
        for (int i = 0; i < _n; ++i) data[_size + i] = T(v[i]);
        for (int i = _size - 1; i >= 1; --i) update(i);
    }
    const T &operator[](int k) const { return data[k + _size]; }
    _segment_tree_reference operator[](int k) { return _segment_tree_reference(*this, k); }
    T at(int k) const { return data[k + _size]; }
    T get(int k) const { return data[k + _size]; }
    void set(int k, T val) {
        assert(0 <= k && k < _n);
        k += _size;
        data[k] = val;
        for (int i = 1; i <= _log; ++i) update(k >> i);
    }
    void reset(int k) { set(k, M::id()); }
    T all_prod() const { return data[1]; }
    T prod(int a, int b) const {
        assert(0 <= a && b <= _n);
        T l = M::id(), r = M::id();
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
        assert(f(M::id()));
        if (l == _n) return _n;
        l += _size;
        T sm = M::id();
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
        assert(f(M::id()));
        if (r == 0) return 0;
        r += _size;
        T sm = M::id();
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
struct string_converter {
    char type(const char &c) const {
        return (std::islower(c) ? 'a' : std::isupper(c) ? 'A' : std::isdigit(c) ? '0' : 0);
    }
    int convert(const char &c) {
        if (!start) start = type(c);
        return c - start;
    }
    int convert(const char &c, const std::string &chars) { return chars.find(c); }
    template <class T>
    auto convert(const T &v) {
        std::vector<decltype(convert(v[0]))> res;
        res.reserve(v.size());
        for (auto &&e : v) res.emplace_back(convert(e));
        return res;
    }
    template <class T>
    auto convert(const T &v, const std::string &chars) {
        std::vector<decltype(convert(v[0], chars))> res;
        res.reserve(v.size());
        for (auto &&e : v) res.emplace_back(convert(e, chars));
        return res;
    }
    int operator()(const char &v, char s = 0) {
        start = s;
        return convert(v);
    }
    int operator()(const char &v, const std::string &chars) { return convert(v, chars); }
    template <class T>
    auto operator()(const T &v, char s = 0) {
        start = s;
        return convert(v);
    }
    template <class T>
    auto operator()(const T &v, const std::string &chars) {
        return convert(v, chars);
    }
  private:
    char start = 0;
} to_int;
using Mint = modint107;
void solve() {
    string s;
    cin >> s;
    auto v = to_int(s);
    int n = v.size();
    vector seg(26, segment_tree<Add<Mint>>(n + 3));
    vector dp(n + 3, vector(26, Mint()));
    vector<Mint> ans(n + 3);
    ans[0] = 1;
    ans[1] = 1;
    ans[2] = 1;
    rep (i, n) {
        dp[i + 3] = dp[i + 2];
        ans[i + 3] += ans[i + 2];
        ans[i + 3] += ans[i + 1] - seg[v[i]].prod(0, i + 3);
        dp[i + 3][v[i]] = ans[i + 3] - ans[i + 2];
        seg[v[i]].set(i + 3, ans[i + 3] - ans[i + 2]);
    }
    co(ans.back() - 1);
}
int main(void) {
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}
