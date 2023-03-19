#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/atcoder/github/algo/lib/template/template.hpp"
#pragma GCC target("sse4.2,avx2,bmi2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
template <class T, class U>
bool chmax(T &a, const U &b) {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U &b) {
    return (T)b < a ? a = (T)b, true : false;
}
constexpr int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
constexpr double PI = M_PI;
#line 3 "/home/kuhaku/atcoder/github/algo/lib/math/pow.hpp"

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
        swap(a -= t * b, b);
        swap(u -= t * v, v);
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
#line 3 "/home/kuhaku/atcoder/github/algo/lib/segment_tree/monoid.hpp"

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
    static constexpr T id = numeric_limits<T>::max();
    static constexpr T op(const T &lhs, const T &rhs) { return min(lhs, rhs); }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return min((U)lhs, rhs);
    }
};

template <class T>
struct Max {
    using value_type = T;
    static constexpr T id = numeric_limits<T>::min();
    static constexpr T op(const T &lhs, const T &rhs) { return max(lhs, rhs); }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return max((U)lhs, rhs);
    }
};

template <class T>
struct Update {
    using value_type = T;
    static constexpr T id = numeric_limits<T>::max();
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
#line 5 "/home/kuhaku/atcoder/github/algo/lib/segment_tree/segment_tree.hpp"

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
        this->_log = ceil_pow2(this->_n);
        this->_size = 1 << this->_log;
        this->data = std::vector<T>(this->_size << 1, M::id);
        for (int i = 0; i < this->_n; ++i) this->data[this->_size + i] = T(v[i]);
        for (int i = this->_size - 1; i >= 1; --i) this->update(i);
    }

    const T &operator[](int k) const { return this->data[k + this->_size]; }
    T at(int k) const { return this->operator[](k); }
    T get(int k) const { return this->operator[](k); }

    void set(int k, T val) {
        assert(0 <= k && k < this->_n);
        k += this->_size;
        this->data[k] = val;
        for (int i = 1; i <= this->_log; ++i) this->update(k >> i);
    }
    void reset(int k) { this->set(k, M::id); }

    T all_prod() const { return this->data[1]; }
    T prod(int a, int b) const {
        assert(0 <= a && b <= this->_n);
        T l = M::id, r = M::id;
        for (a += this->_size, b += this->_size; a < b; a >>= 1, b >>= 1) {
            if (a & 1) l = M::op(l, this->data[a++]);
            if (b & 1) r = M::op(this->data[--b], r);
        }
        return M::op(l, r);
    }

  private:
    int _n, _size, _log;
    std::vector<T> data;

    void update(int k) { this->data[k] = M::op(this->data[2 * k], this->data[2 * k + 1]); }
};
#line 3 "/home/kuhaku/atcoder/github/algo/lib/template/macro.hpp"
#define FOR(i, m, n) for (int i = (m); i < int(n); ++i)
#define FORR(i, m, n) for (int i = (m)-1; i >= int(n); --i)
#define FORL(i, m, n) for (int64_t i = (m); i < int64_t(n); ++i)
#define rep(i, n) FOR (i, 0, n)
#define repn(i, n) FOR (i, 1, n + 1)
#define repr(i, n) FORR (i, n, 0)
#define repnr(i, n) FORR (i, n + 1, 1)
#define all(s) (s).begin(), (s).end()
#line 3 "/home/kuhaku/atcoder/github/algo/lib/template/sonic.hpp"
struct Sonic {
    Sonic() {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
    }

    constexpr void operator()() const {}
} sonic;
#line 5 "/home/kuhaku/atcoder/github/algo/lib/template/atcoder.hpp"
using ll = int64_t;
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
void setp(int n) {
    std::cout << std::fixed << std::setprecision(n);
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
#line 3 "/home/kuhaku/atcoder/github/algo/lib/tree/hld.hpp"

/**
 * @brief HLD
 * @see https://beet-aizu.github.io/library/tree/heavylightdecomposition.cpp
 */
struct HLD {
    HLD(int n) : _size(n), g(n), vid(n, -1), nxt(n), sub(n, 1), par(n, -1), inv(n) {}

    void add_edge(int u, int v) { this->add_edges(u, v); }
    void add_edges(int u, int v) {
        this->g[u].emplace_back(v);
        this->g[v].emplace_back(u);
    }

    void input_edge(int base = 1) { this->input_edges(base); }
    void input_edges(int base = 1) {
        for (int i = 0; i < this->_size - 1; ++i) {
            int u, v;
            cin >> u >> v;
            this->add_edges(u - base, v - base);
        }
    }

    void build(int r = 0) {
        int pos = 0;
        this->dfs_sz(r);
        this->nxt[r] = r;
        this->dfs_hld(r, pos);
    }

    int get(int v) const { return this->vid[v]; }
    int get_parent(int v) const { return this->par[v]; }

    int la(int v, int k) const {
        while (true) {
            int u = this->nxt[v];
            if (this->vid[v] - k >= this->vid[u]) return this->inv[this->vid[v] - k];
            k -= this->vid[v] - this->vid[u] + 1;
            v = this->par[u];
        }
    }

    int lca(int u, int v) const {
        while (true) {
            if (this->vid[u] > this->vid[v]) swap(u, v);
            if (this->nxt[u] == this->nxt[v]) return u;
            v = this->par[this->nxt[v]];
        }
    }

    template <class F>
    void for_each(int u, int v, const F &f) const {
        while (true) {
            if (this->vid[u] > this->vid[v]) swap(u, v);
            f(max(this->vid[this->nxt[v]], this->vid[u]), this->vid[v] + 1);
            if (this->nxt[u] != this->nxt[v]) v = this->par[this->nxt[v]];
            else break;
        }
    }

    template <class F>
    void for_each_edge(int u, int v, const F &f) const {
        while (true) {
            if (this->vid[u] > this->vid[v]) swap(u, v);
            if (this->nxt[u] != this->nxt[v]) {
                f(this->vid[this->nxt[v]], this->vid[v] + 1);
                v = this->par[this->nxt[v]];
            } else {
                if (u != v) f(this->vid[u] + 1, this->vid[v] + 1);
                break;
            }
        }
    }

  private:
    int _size;
    std::vector<std::vector<int>> g;
    std::vector<int> vid, nxt, sub, par, inv;

    void dfs_sz(int v) {
        auto &es = this->g[v];
        if (~(this->par[v])) es.erase(find(es.begin(), es.end(), this->par[v]));

        for (auto &u : es) {
            this->par[u] = v;
            this->dfs_sz(u);
            this->sub[v] += this->sub[u];
            if (this->sub[u] > this->sub[es[0]]) swap(u, es[0]);
        }
    }

    void dfs_hld(int v, int &pos) {
        this->vid[v] = pos++;
        this->inv[this->vid[v]] = v;
        for (auto u : this->g[v]) {
            if (u == this->par[v]) continue;
            this->nxt[u] = (u == this->g[v][0] ? this->nxt[v] : u);
            this->dfs_hld(u, pos);
        }
    }
};
#line 5 "a.cpp"

int main(void) {
    int n;
    cin >> n;
    HLD hld(n);
    vector<int> u(n), v(n), w(n);
    rep (i, n - 1) cin >> u[i] >> v[i] >> w[i];
    rep (i, n - 1) {
        --u[i], --v[i];
    }
    rep (i, n - 1) {
        hld.add_edges(u[i], v[i]);
    }
    hld.build();

    segment_tree<Add<ll>> st(n);
    rep (i, n - 1) {
        if (hld.get_parent(v[i]) == u[i]) {
            st.set(hld.get(v[i]), w[i]);
        } else {
            st.set(hld.get(u[i]), w[i]);
        }
    }

    ll ans = 0;
    auto f = [&](auto x, auto y) {
        ans += st.prod(x, y);
    };

    int q;
    cin >> q;
    while (q--) {
        int c;
        cin >> c;
        if (c == 1) {
            int i, b;
            cin >> i >> b;
            --i;
            w[i] = b;
            if (hld.get_parent(v[i]) == u[i]) {
                st.set(hld.get(v[i]), w[i]);
            } else {
                st.set(hld.get(u[i]), w[i]);
            }
        } else {
            int a, b;
            cin >> a >> b;
            --a, --b;
            ans = 0;
            hld.for_each_edge(a, b, f);
            co(ans);
        }
    }

    return 0;
}
