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
#line 3 "/home/kuhaku/home/github/algo/lib/math/pow.hpp"

std::int64_t safe_mod(std::int64_t a, std::int64_t mod) {
    a %= mod;
    return a >= 0 ? a : a + mod;
}

std::int64_t pow_int(std::int64_t a, std::int64_t n) {
    assert(n >= 0);
    std::int64_t res = 1, mul = a;
    for (; n > 0; n >>= 1) {
        if (n & 1) res *= mul;
        mul *= mul;
    }
    return res;
}

std::int64_t inv_mod(std::int64_t a, std::int64_t mod) {
    std::int64_t b = mod, u = 1, v = 0, t;
    while (b > 0) {
        t = a / b;
        std::swap(a -= t * b, b);
        std::swap(u -= t * v, v);
    }
    return u >= 0 ? u % mod : (mod - (-u) % mod) % mod;
}

std::int64_t pow_mod(std::int64_t a, std::int64_t n, std::int64_t mod) {
    if (n < 0) return inv_mod(pow_mod(a, -n, mod), mod);
    std::int64_t res = 1, mul = safe_mod(a, mod);
    for (; n > 0; n >>= 1) {
        if (n & 1) (res *= mul) %= mod;
        (mul *= mul) %= mod;
    }
    return res;
}

int ceil_pow2(std::int64_t n) {
    int x = 0;
    while ((std::uint64_t(1) << x) < (std::uint64_t)(n)) ++x;
    return x;
}

int floor_pow2(std::int64_t n) {
    int x = 0;
    while ((std::uint64_t(1) << (x + 1)) <= (std::uint64_t)(n)) ++x;
    return x;
}
#line 3 "/home/kuhaku/home/github/algo/lib/segment_tree/monoid.hpp"

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
#line 5 "/home/kuhaku/home/github/algo/lib/segment_tree/lazy_segment_tree.hpp"

/**
 * @brief 遅延評価セグメント木
 * @see https://github.com/atcoder/ac-library/blob/master/atcoder/lazysegtree.hpp
 *
 * @tparam S モノイド
 * @tparam F モノイド
 */
template <class S, class F>
struct lazy_segment_tree {
  private:
    using T = typename S::value_type;
    using U = typename F::value_type;

  public:
    lazy_segment_tree() : lazy_segment_tree(0) {}
    explicit lazy_segment_tree(int n, T e = S::id) : lazy_segment_tree(std::vector<T>(n, e)) {}
    explicit lazy_segment_tree(const std::vector<T> &v) : _n(int(v.size())) {
        this->_log = ceil_pow2(this->_n);
        this->_size = 1 << this->_log;
        this->data = std::vector<T>(2 * this->_size, S::id);
        this->lazy = std::vector<U>(this->_size, F::id);
        for (int i = 0; i < this->_n; i++) this->data[this->_size + i] = v[i];
        for (int i = this->_size - 1; i >= 1; --i) this->update(i);
    }

    void set(int p, T x) {
        assert(0 <= p && p < this->_n);
        p += this->_size;
        for (int i = this->_log; i >= 1; --i) this->push(p >> i);
        this->data[p] = x;
        for (int i = 1; i <= this->_log; ++i) this->update(p >> i);
    }

    T at(int p) { return this->get(p); }
    T get(int p) {
        assert(0 <= p && p < this->_n);
        p += this->_size;
        for (int i = this->_log; i >= 1; --i) this->push(p >> i);
        return this->data[p];
    }

    void apply(int p, U f) {
        assert(0 <= p && p < this->_n);
        p += this->_size;
        for (int i = this->_log; i >= 1; --i) this->push(p >> i);
        this->data[p] = F::f(f, this->data[p]);
        for (int i = 1; i <= this->_log; ++i) this->update(p >> i);
    }
    void apply(int l, int r, U f) {
        assert(0 <= l && l <= r && r <= this->_n);
        if (l == r) return;

        l += this->_size, r += this->_size;

        for (int i = this->_log; i >= 1; --i) {
            if (((l >> i) << i) != l) this->push(l >> i);
            if (((r >> i) << i) != r) this->push((r - 1) >> i);
        }

        int l2 = l, r2 = r;
        while (l < r) {
            if (l & 1) this->all_apply(l++, f);
            if (r & 1) this->all_apply(--r, f);
            l >>= 1, r >>= 1;
        }
        l = l2, r = r2;

        for (int i = 1; i <= this->_log; i++) {
            if (((l >> i) << i) != l) this->update(l >> i);
            if (((r >> i) << i) != r) this->update((r - 1) >> i);
        }
    }

    T prod(int l, int r) {
        assert(0 <= l && l <= r && r <= this->_n);
        if (l == r) return S::id;

        l += this->_size, r += this->_size;

        for (int i = this->_log; i >= 1; --i) {
            if (((l >> i) << i) != l) this->push(l >> i);
            if (((r >> i) << i) != r) this->push((r - 1) >> i);
        }

        T sml = S::id, smr = S::id;
        while (l < r) {
            if (l & 1) sml = S::op(sml, this->data[l++]);
            if (r & 1) smr = S::op(this->data[--r], smr);
            l >>= 1, r >>= 1;
        }

        return S::op(sml, smr);
    }

    T all_prod() const { return this->data[1]; }

  private:
    int _n, _size, _log;
    std::vector<T> data;
    std::vector<U> lazy;

    void update(int k) { this->data[k] = S::op(this->data[2 * k], this->data[2 * k + 1]); }
    void all_apply(int k, U f) {
        this->data[k] = F::f(f, this->data[k]);
        if (k < _size) this->lazy[k] = F::op(f, this->lazy[k]);
    }
    void push(int k) {
        this->all_apply(2 * k, this->lazy[k]);
        this->all_apply(2 * k + 1, this->lazy[k]);
        this->lazy[k] = F::id;
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

struct S {
    int sz, mx0, mx1, l0, r0, l1, r1;
};

struct M {
    using T = S;
    using value_type = S;
    static constexpr T id = S{0, 0, 0, 0, 0, 0, 0};
    static constexpr T op(const T &lhs, const T &rhs) {
        S s;
        s.sz = lhs.sz + rhs.sz;
        s.mx0 = max(lhs.mx0, rhs.mx0);
        s.mx1 = max(lhs.mx1, rhs.mx1);
        chmax(s.mx0, lhs.r0 + rhs.l0);
        chmax(s.mx1, lhs.r1 + rhs.l1);
        s.l0 = lhs.l0 != lhs.sz ? lhs.l0 : lhs.l0 + rhs.l0;
        s.l1 = lhs.l1 != lhs.sz ? lhs.l1 : lhs.l1 + rhs.l1;
        s.r0 = rhs.r0 != rhs.sz ? rhs.r0 : rhs.r0 + lhs.r0;
        s.r1 = rhs.r1 != rhs.sz ? rhs.r1 : rhs.r1 + lhs.r1;
        return s;
    }
};

struct L {
    using value_type = int;
    static constexpr value_type id = 0;
    static constexpr value_type op(const value_type &lhs, const value_type &rhs) {
        return lhs ^ rhs;
    }

    static constexpr S f(const value_type &lhs, S rhs) {
        if (lhs == 0)
            return rhs;
        swap(rhs.l0, rhs.l1);
        swap(rhs.r0, rhs.r1);
        swap(rhs.mx0, rhs.mx1);
        return rhs;
    }
};

int main(void) {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<S> v(n);
    rep (i, n) {
        if (s[i] == '0')
            v[i] = S{1, 1, 0, 1, 1, 0, 0};
        else
            v[i] = S{1, 0, 1, 0, 0, 1, 1};
    }
    lazy_segment_tree<M, L> lst(v);
    while (q--) {
        int c, l, r;
        cin >> c >> l >> r;
        l--;
        if (c == 1) {
            lst.apply(l, r, 1);
        } else {
            co(lst.prod(l, r).mx1);
        }
    }

    return 0;
}
