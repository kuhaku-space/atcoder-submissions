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
/// @brief めぐる式二分探索
template <class T, class F>
std::int64_t meguru_binary_search(T ok, T ng, F check) {
    while (std::abs(ok - ng) > 1) {
        T mid = std::midpoint(ok, ng);
        (check(mid) ? ok : ng) = mid;
    }
    return ok;
}
/// @brief 座標圧縮
template <class T>
struct coordinate_compression {
    coordinate_compression() = default;
    coordinate_compression(const std::vector<T> &_data) : data(_data) { build(); }
    const T &operator[](int i) const { return data[i]; }
    T front() const { return data.front(); }
    T back() const { return data.back(); }
    void add(T x) { data.emplace_back(x); }
    void build() {
        std::sort(data.begin(), data.end());
        data.erase(std::unique(data.begin(), data.end()), data.end());
    }
    bool exists(T x) const {
        auto it = std::lower_bound(data.begin(), data.end(), x);
        return it != data.end() && *it == x;
    }
    int get(T x) const { return std::distance(data.begin(), std::lower_bound(data.begin(), data.end(), x)); }
    int lower_bound(T x) const { return std::distance(data.begin(), std::lower_bound(data.begin(), data.end(), x)); }
    int upper_bound(T x) const { return std::distance(data.begin(), std::upper_bound(data.begin(), data.end(), x)); }
    std::vector<int> compress(const std::vector<T> &v) const {
        int n = v.size();
        std::vector<int> res(n);
        for (int i = 0; i < n; ++i) res[i] = get(v[i]);
        return res;
    }
    int size() const { return data.size(); }
  private:
    std::vector<T> data;
};
/// @brief 座標圧縮
template <class T>
std::vector<int> compress(const std::vector<T> &v) {
    coordinate_compression cps(v);
    std::vector<int> res;
    res.reserve(std::size(v));
    for (auto &&x : v) res.emplace_back(cps.get(x));
    return res;
}
/// @brief 二次元累積和
template <class T>
struct cumulative_sum_2d {
    cumulative_sum_2d(int _n, int _m) : v(_n, std::vector<T>(_m)), n(_n), m(_m) {}
    cumulative_sum_2d(const std::vector<std::vector<T>> &_v) : v(_v) { build(); }
    void set(int x, int y, T val) { v[x][y] = val; }
    void add(int x, int y, T val) { v[x][y] += val; }
    void build() {
        n = v.size();
        assert(n > 0);
        m = v[0].size();
        assert(m > 0);
        v.resize(n + 1);
        for (int i = 0; i <= n; ++i) v[i].resize(m + 1);
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) v[i][j] += v[i][j + 1];
        }
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) v[i][j] += v[i + 1][j];
        }
    }
    T get(int x1, int y1, int x2, int y2) {
        assert(0 <= x1 && x1 <= x2 && x2 <= n && 0 <= y1 && y1 <= y2 && y2 <= m);
        return v[x1][y1] - v[x1][y2] - v[x2][y1] + v[x2][y2];
    }
  private:
    std::vector<std::vector<T>> v;
    int n, m;
};
/// @brief フェニック木
/// @see http://hos.ac/slides/20140319_bit.pdf
template <class T>
struct fenwick_tree {
    fenwick_tree() : _size(), data() {}
    fenwick_tree(int n) : _size(n + 1), data(n + 1) {}
    template <class U>
    fenwick_tree(const std::vector<U> &v) : _size((int)v.size() + 1), data((int)v.size() + 1) {
        build(v);
    }
    T operator[](int i) const { return sum(i, i + 1); }
    T at(int k) const { return operator[](k); }
    T get(int k) const { return operator[](k); }
    template <class U>
    void build(const std::vector<U> &v) {
        for (int i = 0, n = v.size(); i < n; ++i) data[i + 1] = v[i];
        for (int i = 1; i < _size; ++i) {
            if (i + (i & -i) < _size) data[i + (i & -i)] += data[i];
        }
    }
    /// @brief v[k] = val
    void set(int k, T val) { add(k, val - at(k)); }
    /// @brief v[k] += val
    void add(int k, T val) {
        assert(0 <= k && k < _size - 1);
        for (++k; k < _size; k += k & -k) data[k] += val;
    }
    /// @brief chmax(v[k], val)
    bool chmax(int k, T val) {
        if (at(k) >= val) return false;
        set(k, val);
        return true;
    }
    /// @brief chmin(v[k], val)
    bool chmin(int k, T val) {
        if (at(k) <= val) return false;
        set(k, val);
        return true;
    }
    /// @brief v[0] + ... + v[n - 1]
    T all_prod() const { return prod(_size - 1); }
    /// @brief v[0] + ... + v[k - 1]
    T prod(int k) const { return sum(k); }
    /// @brief v[a] + ... + v[b - 1]
    T prod(int a, int b) const { return sum(a, b); }
    /// @brief v[0] + ... + v[n - 1]
    T all_sum() const { return sum(_size - 1); }
    /// @brief v[0] + ... + v[k - 1]
    T sum(int k) const {
        assert(0 <= k && k < _size);
        T res = 0;
        for (; k > 0; k -= k & -k) res += data[k];
        return res;
    }
    /// @brief v[a] + ... + v[b - 1]
    T sum(int a, int b) const {
        assert(0 <= a && a <= b && b < _size);
        T res = T();
        while (a != b) {
            if (a < b) {
                res += data[b];
                b -= b & -b;
            } else {
                res -= data[a];
                a -= a & -a;
            }
        }
        return res;
    }
    int lower_bound(T val) const {
        if (val <= 0) return 0;
        int k = 1;
        while (k < _size) k <<= 1;
        int res = 0;
        for (; k > 0; k >>= 1) {
            if (res + k < _size && data[res + k] < val) val -= data[res += k];
        }
        return res;
    }
  private:
    int _size;
    std::vector<T> data;
};
/// @brief 重み付きグラフ
template <class T>
struct Graph {
  private:
    struct _edge {
        constexpr _edge() : _from(), _to(), _weight() {}
        constexpr _edge(int from, int to, T weight) : _from(from), _to(to), _weight(weight) {}
        constexpr bool operator<(const _edge &rhs) const { return weight() < rhs.weight(); }
        constexpr bool operator>(const _edge &rhs) const { return rhs < *this; }
        constexpr int from() const { return _from; }
        constexpr int to() const { return _to; }
        constexpr T weight() const { return _weight; }
      private:
        int _from, _to;
        T _weight;
    };
  public:
    using edge_type = typename Graph<T>::_edge;
    Graph() : _size(), edges() {}
    Graph(int v) : _size(v), edges(v) {}
    const auto &operator[](int i) const { return edges[i]; }
    auto &operator[](int i) { return edges[i]; }
    const auto begin() const { return edges.begin(); }
    auto begin() { return edges.begin(); }
    const auto end() const { return edges.end(); }
    auto end() { return edges.end(); }
    constexpr int size() const { return _size; }
    void add_edge(const edge_type &e) { edges[e.from()].emplace_back(e); }
    void add_edge(int from, int to, T weight = T(1)) { edges[from].emplace_back(from, to, weight); }
    void add_edges(int from, int to, T weight = T(1)) {
        edges[from].emplace_back(from, to, weight);
        edges[to].emplace_back(to, from, weight);
    }
    void input_edge(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            T weight;
            std::cin >> from >> to >> weight;
            add_edge(from - base, to - base, weight);
        }
    }
    void input_edges(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            T weight;
            std::cin >> from >> to >> weight;
            add_edges(from - base, to - base, weight);
        }
    }
  private:
    int _size;
    std::vector<std::vector<edge_type>> edges;
};
/// @brief 重みなしグラフ
template <>
struct Graph<void> {
  private:
    struct _edge {
        constexpr _edge() : _from(), _to() {}
        constexpr _edge(int from, int to) : _from(from), _to(to) {}
        constexpr int from() const { return _from; }
        constexpr int to() const { return _to; }
        constexpr int weight() const { return 1; }
        constexpr bool operator<(const _edge &rhs) const { return weight() < rhs.weight(); }
        constexpr bool operator>(const _edge &rhs) const { return rhs < *this; }
      private:
        int _from, _to;
    };
  public:
    using edge_type = typename Graph<void>::_edge;
    Graph() : _size(), edges() {}
    Graph(int v) : _size(v), edges(v) {}
    const auto &operator[](int i) const { return edges[i]; }
    auto &operator[](int i) { return edges[i]; }
    const auto begin() const { return edges.begin(); }
    auto begin() { return edges.begin(); }
    const auto end() const { return edges.end(); }
    auto end() { return edges.end(); }
    constexpr int size() const { return _size; }
    void add_edge(const edge_type &e) { edges[e.from()].emplace_back(e); }
    void add_edge(int from, int to) { edges[from].emplace_back(from, to); }
    void add_edges(int from, int to) {
        edges[from].emplace_back(from, to);
        edges[to].emplace_back(to, from);
    }
    void input_edge(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            std::cin >> from >> to;
            add_edge(from - base, to - base);
        }
    }
    void input_edges(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            std::cin >> from >> to;
            add_edges(from - base, to - base);
        }
    }
  private:
    int _size;
    std::vector<std::vector<edge_type>> edges;
};
namespace internal {
template <int Index>
struct grid_impl {
    template <class Head, class... Tail>
    constexpr grid_impl(Head &&head, Tail &&...tail) : limit(head), impl(std::forward<Tail>(tail)...) {}
    template <class Head, class... Tail>
    constexpr bool in_field(Head x, Tail &&...tail) const {
        return 0 <= x && x < limit && impl.in_field(std::forward<Tail>(tail)...);
    }
    template <class Head, class... Tail>
    constexpr std::int64_t flatten(Head x, Tail &&...tail) const {
        return x + limit * impl.flatten(std::forward<Tail>(tail)...);
    }
  private:
    std::int64_t limit;
    grid_impl<Index - 1> impl;
};
template <>
struct grid_impl<0> {
    constexpr grid_impl() {}
    constexpr bool in_field() const { return true; }
    constexpr std::int64_t flatten() const { return 0; }
};
}  // namespace internal
template <int Index>
struct Grid {
    template <class... Args>
    constexpr Grid(Args &&...args) : entity(std::forward<Args>(args)...) {
        static_assert(sizeof...(Args) == Index);
    }
    template <class... Args>
    constexpr bool in_field(Args &&...args) const {
        static_assert(sizeof...(Args) == Index);
        return entity.in_field(std::forward<Args>(args)...);
    }
    template <class... Args>
    constexpr std::int64_t flatten(Args &&...args) const {
        static_assert(sizeof...(Args) == Index);
        return entity.flatten(std::forward<Args>(args)...);
    }
  private:
    internal::grid_impl<Index> entity;
};
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
/// @brief 素集合データ構造
/// @details Implement (union by size) + (path compression)
/// @see https://github.com/atcoder/ac-library/blob/master/atcoder/dsu.hpp
struct union_find {
    union_find() = default;
    explicit union_find(int _n) : _rank(_n), data(_n, -1) {}
    const int &operator[](std::size_t x) const { return data[x]; }
    int &operator[](std::size_t x) { return data[x]; }
    int root(int x) { return data[x] < 0 ? x : data[x] = root(data[x]); }
    int get_root(int x) { return root(x); }
    bool is_root(int x) const { return data[x] < 0; }
    bool same(int x, int y) { return root(x) == root(y); }
    bool is_same(int x, int y) { return same(x, y); }
    int rank() { return _rank; }
    int size(int x) { return -(data[root(x)]); }
    int get_size(int x) { return size(x); }
    std::vector<int> leaders() {
        std::vector<int> res;
        for (int i = 0; i < (int)data.size(); ++i) {
            if (is_root(i)) res.emplace_back(i);
        }
        return res;
    }
    bool unite(int x, int y) {
        x = root(x), y = root(y);
        if (x == y) return false;
        --_rank;
        if (data[x] > data[y]) std::swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return true;
    }
    template <class F>
    requires std::invocable<F, int, int, bool>
    bool unite(int x, int y, F f) {
        x = root(x), y = root(y);
        bool swapped = false;
        if (x != y) {
            if (data[x] > data[y]) std::swap(x, y), swapped = true;
            data[x] += data[y];
            data[y] = x;
        }
        f(x, y, swapped);
        return x != y;
    }
    template <class F>
    requires std::invocable<F, int, int>
    bool unite(int x, int y, F f) {
        x = root(x), y = root(y);
        if (x != y) {
            if (data[x] > data[y]) std::swap(x, y);
            data[x] += data[y];
            data[y] = x;
        }
        f(x, y);
        return x != y;
    }
  private:
    int _rank;
    std::vector<int> data;
};
using Mint = modint998;
vector<int> dx = {1, -1, 0, 0}, dy = {0, 0, 1, -1};
void solve() {
    int h, w;
    cin >> h >> w;
    vector<string> s(h);
    cin >> s;
    int sx = 0, sy = 0;
    rep (i, h) {
        rep (j, w) {
            if (s[i][j] == 'S')
                sx = i, sy = j;
        }
    }
    s[sx][sy] = '#';
    Grid<2> g(h, w);
    vector dp(h, vector(w, 0));
    queue<pair<int, int>> que;
    rep (k, 4) {
        int nx = sx + dx[k], ny = sy + dy[k];
        if (!g.in_field(nx, ny) || s[nx][ny] != '.')
            continue;
        dp[nx][ny] = 1 << k;
        que.emplace(nx, ny);
    }
    while (!que.empty()) {
        auto [x, y] = que.front();
        que.pop();
        rep (k, 4) {
            int nx = x + dx[k], ny = y + dy[k];
            if (!g.in_field(nx, ny) || s[nx][ny] != '.')
                continue;
            if (dp[nx][ny] != (dp[nx][ny] | dp[x][y])) {
                dp[nx][ny] |= dp[x][y];
                que.emplace(nx, ny);
            }
        }
    }
    bool f = true;
    rep (k, 4) {
        int nx = sx + dx[k], ny = sy + dy[k];
        if (!g.in_field(nx, ny) || s[nx][ny] != '.')
            continue;
        if (dp[nx][ny] != 1 << k) {
            Yes();
            f = false;
            break;
        }
    }
    if (f)
        No();
}
int main(void) {
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}
