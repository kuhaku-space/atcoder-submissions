#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/home/github/algo/lib/template/template.hpp"
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
#line 5 "/home/kuhaku/home/github/algo/lib/segment_tree/dynamic_segment_tree.hpp"

/**
 * @brief 動的セグメント木
 *
 * @tparam M モノイド
 */
template <class M>
struct dynamic_segment_tree {
  private:
    using T = typename M::value_type;

    struct _node {
        using pointer = _node *;
        pointer parent, left, right;
        T value;

        _node(pointer ptr) : parent(ptr), left(nullptr), right(nullptr), value(M::id) {}
    };

  public:
    using node_ptr = typename _node::pointer;

    dynamic_segment_tree(std::int64_t n) : root(), _size(), _log() { this->init(n); }

    T operator[](int k) const {
        node_ptr node = this->root;
        for (int i = this->_log - 1; i >= 0; --i) {
            if (k >> i & 1) {
                if (!node->right) return M::id;
                node = node->right;
            } else {
                if (!node->left) return M::id;
                node = node->left;
            }
        }
        return node->value;
    }
    T at(int k) const { return this->operator[](k); }
    T get(int k) const { return this->operator[](k); }

    void init(std::int64_t n) {
        this->_log = ceil_pow2(n);
        this->_size = 1LL << this->_log;
        this->root = new _node(nullptr);
    }

    void set(std::int64_t k, T x) {
        assert(0 <= k && k < this->_size);
        node_ptr node = this->root;
        for (int i = this->_log - 1; i >= 0; --i) {
            if (k >> i & 1) {
                if (!node->right) node->right = new _node(node);
                node = node->right;
            } else {
                if (!node->left) node->left = new _node(node);
                node = node->left;
            }
        }

        node->value = x;
        while (node->parent) {
            node = node->parent;
            node->value = M::op(node->left ? node->left->value : M::id,
                                node->right ? node->right->value : M::id);
        }
    }
    void reset(std::int64_t k) { this->set(k, M::id); }

    T all_prod() const { return this->root ? this->root->value : M::id; }
    T prod(std::int64_t a, std::int64_t b) const {
        assert(0 <= a && a <= this->_size);
        assert(0 <= b && b <= this->_size);
        return this->prod(a, b, this->root, 0, this->_size);
    }

    template <class F>
    std::int64_t max_right(F f) const {
        assert(f(M::id));
        if (this->root == nullptr || f(this->root->value)) return this->_size;
        node_ptr node = this->root;
        T sm = M::id;
        std::int64_t l = 0, r = this->_size;
        while (r - l > 1) {
            std::int64_t m = (l + r) >> 1;
            if (node->left == nullptr || f(M::op(sm, node->left->value))) {
                if (node->left != nullptr) sm = M::op(sm, node->left->value);
                l = m;
                node = node->right;
            } else {
                r = m;
                node = node->left;
            }
        }
        return f(M::op(sm, node->value)) ? r : l;
    }

    template <class F>
    std::int64_t min_left(F f) const {
        assert(f(M::id));
        if (this->root == nullptr || f(this->root->value)) return 0;
        node_ptr node = this->root;
        T sm = M::id;
        std::int64_t l = 0, r = this->_size;
        while (r - l > 1) {
            std::int64_t m = (l + r) >> 1;
            if (node->right == nullptr || f(M::op(node->right->value, sm))) {
                if (node->right != nullptr) sm = M::op(node->right->value, sm);
                r = m;
                node = node->left;
            } else {
                l = m;
                node = node->right;
            }
        }
        return f(M::op(node->value, sm)) ? l : r;
    }

  private:
    node_ptr root;
    std::int64_t _size, _log;

    T prod(std::int64_t a, std::int64_t b, node_ptr node, std::int64_t l, std::int64_t r) const {
        if (a <= l && r <= b) return node->value;
        if (r <= a || b <= l) return M::id;

        return M::op(node->left ? this->prod(a, b, node->left, l, (l + r) >> 1) : M::id,
                     node->right ? this->prod(a, b, node->right, (l + r) >> 1, r) : M::id);
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
    }

    constexpr void operator()() const {}
} sonic;
#line 5 "/home/kuhaku/home/github/algo/lib/template/atcoder.hpp"
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
#line 4 "a.cpp"

struct Monoid {
    using T = pair<ll, ll>;
    using value_type = T;
    static constexpr T id = T(0, 0);
    static constexpr T op(const T &lhs, const T &rhs) {
        return {lhs.first + rhs.first, lhs.second + rhs.second};
    }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs + rhs;
    }
};

int main(void) {
    int n;
    cin >> n;
    vector<pair<ll, ll>> p(n);
    cin >> p;
    dynamic_segment_tree<Monoid> st(Inf);
    rep (i, n) {
        auto a = st.get(p[i].first);
        st.set(p[i].first, {a.first + p[i].second, a.second + p[i].first * p[i].second});
    }

    int q;
    cin >> q;
    rep (i, q) {
        int c;
        cin >> c;
        if (c == 1) {
            int x, y;
            cin >> x >> y;
            --x;
            auto f = st.get(p[x].first);
            st.set(p[x].first, {f.first - p[x].second, f.second - p[x].first * p[x].second});
            p[x].first = y;
            auto g = st.get(p[x].first);
            st.set(p[x].first, {g.first + p[x].second, g.second + p[x].first * p[x].second});
        } else if (c == 2) {
            int x, y;
            cin >> x >> y;
            --x;
            auto f = st.get(p[x].first);
            st.set(p[x].first, {f.first - p[x].second, f.second - p[x].first * p[x].second});
            p[x].second = y;
            auto g = st.get(p[x].first);
            st.set(p[x].first, {g.first + p[x].second, g.second + p[x].first * p[x].second});
        } else {
            int x;
            cin >> x;
            auto z = st.all_prod();
            if (z.first < x) {
                co(-1);
                continue;
            } else if (z.first == x) {
                co(z.second);
                continue;
            }

            int l = st.min_left([&](auto p) {
                return p.first <= x;
            });

            auto m = st.prod(l, Inf);
            if (m.first == x) {
                co(m.second);
            } else {
                co(m.second + (x - m.first) * (l - 1));
            }
        }
    }

    return 0;
}
