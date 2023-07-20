#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/home/github/algo/lib/template/template.hpp"
#pragma GCC target("sse4.2,avx2,bmi2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
template <class T, class U>
bool chmax(T &a, const U &b) {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U &b) {
    return (T)b < a ? a = (T)b, true : false;
}
constexpr std::int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
constexpr double PI = M_PI;
#line 3 "/home/kuhaku/home/github/algo/lib/algorithm/compress.hpp"

/**
 * @brief 座標圧縮
 *
 * @tparam T 要素の型
 */
template <class T>
struct coordinate_compression {
    coordinate_compression() = default;
    coordinate_compression(const std::vector<T> &_data) : data(_data) { this->build(); }

    const T &operator[](int i) const { return this->data[i]; }
    T &operator[](int i) { return this->data[i]; }

    void add(T x) { this->data.emplace_back(x); }

    void build() {
        std::sort(this->data.begin(), this->data.end());
        this->data.erase(std::unique(this->data.begin(), this->data.end()), this->data.end());
    }
    void build(const std::vector<T> &v) {
        this->data = v;
        std::sort(this->data.begin(), this->data.end());
        this->data.erase(std::unique(this->data.begin(), this->data.end()), this->data.end());
    }

    bool exist(T x) const {
        auto it = std::lower_bound(this->data.begin(), this->data.end(), x);
        return it != this->data.end() && *it == x;
    }

    int get(T x) const {
        auto it = std::lower_bound(this->data.begin(), this->data.end(), x);
        return it - this->data.begin();
    }

    int size() const { return this->data.size(); }

  private:
    std::vector<T> data;
};

/**
 * @brief 座標圧縮
 *
 * @tparam T 要素の型
 * @param v
 * @return std::vector<T>
 */
template <class T>
std::vector<T> compress(const std::vector<T> &v) {
    coordinate_compression cps(v);
    std::vector<T> res;
    for (auto x : v) res.emplace_back(cps.get(x));
    return res;
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
#line 4 "/home/kuhaku/home/github/algo/lib/segment_tree/dynamic_segment_tree.hpp"

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
        std::int64_t index;
        pointer left, right;
        T value, product;

        constexpr _node(std::int64_t _index, T _value)
            : index(_index), left(nullptr), right(nullptr), value(_value), product(_value) {}
    };

  public:
    using node_ptr = typename _node::pointer;

    dynamic_segment_tree(std::int64_t n) : root(), _size(n) {}

    T operator[](std::int64_t k) const {
        node_ptr node = root;
        std::int64_t l = 0, r = _size;
        while (node) {
            if (k == node->index) return node->value;
            std::int64_t m = (l + r) >> 1;
            if (k < m) r = m, node = node->left;
            else l = m, node = node->right;
        }
        return M::id;
    }
    T at(std::int64_t k) const { return operator[](k); }
    T get(std::int64_t k) const { return operator[](k); }

    void set(std::int64_t k, T x) {
        assert(0 <= k && k < _size);
        if (!root) {
            root = new _node(k, x);
            return;
        }
        node_ptr node = root;
        std::vector<node_ptr> nodes;
        std::int64_t l = 0, r = _size;
        while (true) {
            nodes.emplace_back(node);
            if (k == node->index) {
                node->value = x;
                break;
            }
            std::int64_t m = (l + r) >> 1;
            if (k < m) {
                if (node->index < k) std::swap(k, node->index), std::swap(x, node->value);
                if (!node->left) {
                    node->left = new _node(k, x);
                    break;
                }
                r = m, node = node->left;
            } else {
                if (k < node->index) std::swap(k, node->index), std::swap(x, node->value);
                if (!node->right) {
                    node->right = new _node(k, x);
                    break;
                }
                l = m, node = node->right;
            }
        }

        std::reverse(std::begin(nodes), std::end(nodes));
        for (auto node : nodes) {
            node->product = M::op(M::op(node->left ? node->left->product : M::id, node->value),
                                  node->right ? node->right->product : M::id);
        }
    }
    void reset(std::int64_t k) { set(k, M::id); }

    T all_prod() const { return root ? root->product : M::id; }
    T prod(std::int64_t a, std::int64_t b) const {
        assert(0 <= a && a <= _size);
        assert(0 <= b && b <= _size);
        return prod(a, b, root, 0, _size);
    }

    template <class F>
    std::int64_t max_right(F f) const {
        assert(f(M::id));
        if (root == nullptr || f(root->value)) return _size;
        node_ptr node = root;
        T sm = M::id;
        std::int64_t l = 0, r = _size;
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
        if (root == nullptr || f(root->value)) return 0;
        node_ptr node = root;
        T sm = M::id;
        std::int64_t l = 0, r = _size;
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
    std::int64_t _size;

    T prod(std::int64_t a, std::int64_t b, node_ptr node, std::int64_t l, std::int64_t r) const {
        if (!node || r <= a || b <= l) return M::id;
        if (a <= l && r <= b) return node->product;

        return M::op(M::op(prod(a, b, node->left, l, (l + r) >> 1),
                           a <= node->index && node->index < b ? node->value : M::id),
                     prod(a, b, node->right, (l + r) >> 1, r));
    }
};
#line 4 "/home/kuhaku/home/github/algo/lib/segment_tree/segment_tree_2d.hpp"

/**
 * @brief 二次元セグメント木
 *
 * @tparam M モノイド
 */
template <class M>
struct segment_tree_2d {
  private:
    using T = typename M::value_type;

    struct _node {
        using pointer = _node *;
        pointer left, right;
        dynamic_segment_tree<M> segtree;

        _node(std::int64_t w) : left(nullptr), right(nullptr), segtree(w) {}
    };

  public:
    using node_ptr = typename _node::pointer;

    segment_tree_2d(std::int64_t h, std::int64_t w) : root(new _node(w)), _h(h), _w(w) {}

    T at(std::int64_t x, std::int64_t y) const {
        node_ptr node = root;
        std::int64_t l = 0, r = _h;
        while (r - l > 1) {
            if (!node) return M::id;
            std::int64_t m = (l + r) >> 1;
            if (x < m) r = m, node = node->left;
            else l = m, node = node->right;
        }
        return node ? node->segtree.get(y) : M::id;
    }
    T get(std::int64_t x, std::int64_t y) const { return at(x, y); }

    void set(std::int64_t x, std::int64_t y, T val) {
        assert(0 <= x && x < _h);
        assert(0 <= y && y < _w);
        node_ptr node = root;
        std::vector<node_ptr> nodes;
        std::int64_t l = 0, r = _h;
        while (r - l > 1) {
            std::int64_t m = (l + r) >> 1;
            nodes.emplace_back(node);
            if (x < m) {
                if (!node->left) node->left = new _node(_w);
                r = m, node = node->left;
            } else {
                if (!node->right) node->right = new _node(_w);
                l = m, node = node->right;
            }
        }
        node->segtree.set(y, val);

        std::reverse(std::begin(nodes), std::end(nodes));
        for (auto node : nodes) {
            node->segtree.set(y, M::op(node->left ? node->left->segtree.get(y) : M::id,
                                       node->right ? node->right->segtree.get(y) : M::id));
        }
    }
    void reset(std::int64_t x, std::int64_t y) { set(x, y, M::id); }

    T all_prod() const { return root ? root->segtree.all_prod() : M::id; }
    T prod(std::int64_t l, std::int64_t r, std::int64_t d, std::int64_t u) const {
        assert(0 <= l && l <= r && r <= _h);
        assert(0 <= d && d <= u && u <= _w);
        return prod(l, r, d, u, root, 0, _h);
    }

  private:
    node_ptr root;
    std::int64_t _h, _w;

    T prod(std::int64_t l, std::int64_t r, std::int64_t d, std::int64_t u, node_ptr node,
           std::int64_t x, std::int64_t y) const {
        if (!node || y <= l || r <= x) return M::id;
        if (l <= x && y <= r) return node->segtree.prod(d, u);

        return M::op(prod(l, r, d, u, node->left, x, (x + y) >> 1),
                     prod(l, r, d, u, node->right, (x + y) >> 1, y));
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
#line 5 "a.cpp"

int main(void) {
    int n;
    cin >> n;
    vector<tuple<int, int, int>> a(n);
    coordinate_compression<int> cy;
    rep (i, n) {
        int x, y, z;
        cin >> x >> y >> z;
        vector<int> t = {x, y, z};
        sort(all(t));
        x = t[0], y = t[1], z = t[2];
        a[i] = {x, y, z};
        cy.add(y);
    }
    cy.build();

    for (auto &[x, y, z] : a) y = cy.get(y);
    sort(all(a), [&](auto x, auto y) {
        if (get<0>(x) == get<0>(y))
            return get<1>(x) > get<1>(y);
        return get<0>(x) < get<0>(y);
    });
    segment_tree_2d<Add<int>> st(2e5, 1e9);
    for (auto &&[x, y, z] : a) {
        if (st.prod(0, y, 0, z)) {
            Yes();
            return 0;
        }
        st.set(y, z, 1);
    }
    No();

    return 0;
}
