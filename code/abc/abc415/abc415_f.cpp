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
struct S {
    int ans, len, l, r;
    char cl, cr;
};
template <class T>
struct M {
    using value_type = T;
    static constexpr T id() {
        return T{0, -1, 0, 0, 0, 0};
    }
    static constexpr T op(const T &lhs, const T &rhs) {
        if (lhs.len == -1)
            return rhs;
        if (rhs.len == -1)
            return lhs;
        T res;
        res.ans = max(lhs.ans, rhs.ans);
        res.len = lhs.len + rhs.len;
        res.cl = lhs.cl;
        res.cr = rhs.cr;
        res.l = lhs.l;
        res.r = rhs.r;
        if (lhs.len == lhs.l && lhs.cr == rhs.cl)
            res.l += rhs.l, chmax(res.ans, res.l);
        if (rhs.len == rhs.r && rhs.cl == lhs.cr)
            res.r += lhs.r, chmax(res.ans, res.r);
        if (lhs.cr == rhs.cl)
            chmax(res.ans, lhs.r + rhs.l);
        return res;
    }
};
void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<S> v(n);
    rep (i, n) {
        v[i] = S{1, 1, 1, 1, s[i], s[i]};
    }
    segment_tree<M<S>> seg(v);
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int x;
            char c;
            cin >> x >> c;
            seg.set(x - 1, S{1, 1, 1, 1, c, c});
        } else {
            int l, r;
            cin >> l >> r;
            co(seg.prod(l - 1, r).ans);
        }
    }
}
int main(void) {
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}
