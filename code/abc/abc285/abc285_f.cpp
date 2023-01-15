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
#line 2 "/home/kuhaku/home/github/algo/lib/binary_tree/scapegoat_tree.hpp"

/**
 * @brief スケープゴート木
 * @see https://kopricky.github.io/code/BinarySearchTree/scapegoat_tree.html
 *
 * @tparam T 要素の型
 */
template <class T>
struct scapegoat_tree {
  private:
    struct Node {
        using pointer = Node *;

        T val;
        unsigned int size;
        pointer left, right;

        Node(T _val) : val(_val), size(1), left(nullptr), right(nullptr) {}

        static constexpr int get_size(pointer node) { return node ? node->size : 0; }

        void eval() { this->size = 1 + Node::get_size(left) + Node::get_size(right); }
    };

  public:
    using node_ptr = typename Node::pointer;

    scapegoat_tree(const double _alpha = 2.0 / 3.0)
        : root(nullptr), alpha(_alpha), log_val(-1.0 / std::log2(_alpha)), max_element_size(0) {}

    constexpr bool empty() const { return !(this->root); }

    constexpr int size() const { return this->empty() ? 0 : this->root->size; }

    constexpr bool contains(T val) const {
        node_ptr node = this->root;
        while (node) {
            if (node->val == val) return true;
            node = (val < node->val ? node->left : node->right);
        }
        return false;
    }

    constexpr T index(int k) const {
        assert(k < this->size());
        node_ptr node = this->root;
        while (node) {
            if (Node::get_size(node->left) == k) {
                break;
            } else if (k < Node::get_size(node->left)) {
                node = node->left;
            } else {
                k -= Node::get_size(node->left) + 1;
                node = node->right;
            }
        }
        return node->val;
    }
    constexpr T kth_element(int k) const { return this->index(k); }

    void insert(T val) {
        this->max_element_size = std::max(this->max_element_size, this->size() + 1);
        bool balanced = true;
        this->root = this->insert(this->root, val, 0, balanced);
        assert(balanced);
    }

    void erase(T val) {
        this->root = this->erase(this->root, val);
        this->check();
    }

    int count(T val) {
        int res = 0;
        node_ptr node = this->root;
        while (node) {
            if (node->val < val) res += Node::get_size(node->left) + 1;
            node = (val <= node->val ? node->left : node->right);
        }
        return res;
    }

  private:
    node_ptr root;
    double alpha, log_val;
    int max_element_size;

    void subtree_dfs(node_ptr node, std::vector<node_ptr> &nodes) const {
        if (node->left) this->subtree_dfs(node->left, nodes);
        nodes.emplace_back(node);
        if (node->right) this->subtree_dfs(node->right, nodes);
    }
    node_ptr build_pbbt_rec(int l, int r, const std::vector<node_ptr> &nodes) {
        if (r - l == 0) {
            return nullptr;
        } else if (r - l == 1) {
            node_ptr node = nodes[l];
            node->left = node->right = nullptr;
            node->eval();
            return node;
        }
        int mid = (l + r) >> 1;
        node_ptr node = nodes[mid];
        node->left = this->build_pbbt_rec(l, mid, nodes);
        node->right = this->build_pbbt_rec(mid + 1, r, nodes);
        node->eval();
        return node;
    }
    node_ptr build_pbbt(node_ptr node) {
        if (!node) return nullptr;
        std::vector<node_ptr> nodes;
        this->subtree_dfs(node, nodes);
        return this->build_pbbt_rec(0, nodes.size(), nodes);
    }

    node_ptr insert(node_ptr node, T val, int depth, bool &balanced) {
        if (!node) {
            balanced = (depth <= std::floor(log_val * std::log2(max_element_size)));
            return new Node(val);
        } else if (val < node->val) {
            node->left = this->insert(node->left, val, depth + 1, balanced);
            node->eval();
            if (balanced || node->left->size <= alpha * node->size) return node;
        } else {
            node->right = this->insert(node->right, val, depth + 1, balanced);
            node->eval();
            if (balanced || node->right->size <= alpha * node->size) return node;
        }
        balanced = true;
        return this->build_pbbt(node);
    }

    node_ptr join(node_ptr left, node_ptr right) {
        if (!left || !right) {
            return left ? left : right;
        } else if (left->size < right->size) {
            right->left = this->join(left, right->left);
            right->eval();
            return right;
        } else {
            left->right = this->join(left->right, right);
            left->eval();
            return left;
        }
    }

    node_ptr erase(node_ptr node, T val) {
        if (!node) {
            return nullptr;
        } else if (node->val == val) {
            return this->join(node->left, node->right);
        } else if (val < node->val) {
            node->left = this->erase(node->left, val);
            node->eval();
            return node;
        } else {
            node->right = this->erase(node->right, val);
            node->eval();
            return node;
        }
    }

    void check() {
        if (this->size() >= alpha * max_element_size) return;
        this->root = this->build_pbbt(this->root);
        this->max_element_size = this->size();
    }
};
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
#line 5 "/home/kuhaku/home/github/algo/lib/segment_tree/segment_tree.hpp"

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
#line 5 "a.cpp"

int main(void) {
    int n;
    cin >> n;
    string s;
    cin >> s;
    segment_tree<And<bool>> st(n - 1);
    rep (i, n - 1) {
        if (s[i] > s[i + 1])
            st.set(i, 0);
    }
    scapegoat_tree<char> sct;
    rep (i, n) sct.insert(s[i]);
    int q;
    cin >> q;
    while (q--) {
        int com;
        cin >> com;
        if (com == 1) {
            int x;
            char c;
            cin >> x >> c;
            --x;
            sct.erase(s[x]);
            s[x] = c;
            sct.insert(s[x]);
            if (x < n - 1) {
                st.set(x, s[x] <= s[x + 1]);
            }
            if (x > 0) {
                st.set(x - 1, s[x - 1] <= s[x]);
            }
        } else {
            int l, r;
            cin >> l >> r;
            --l, --r;
            if (st.prod(l, r)) {
                if (s[l] == s[r]) {
                    Yes();
                    continue;
                }
                int fl = l, fr = r;
                while (fl + 1 < fr) {
                    int m = (fl + fr) / 2;
                    if (s[m] == s[l])
                        fl = m;
                    else
                        fr = m;
                }
                int gl = l, gr = r;
                while (gl + 1 < gr) {
                    int m = (gl + gr) / 2;
                    if (s[m] == s[r])
                        gr = m;
                    else
                        gl = m;
                }
                int x = sct.count(s[l] + 1);
                int y = sct.count(s[r]);
                ce(x, y, fr, gl);
                Yes(y - x == gl - fr + 1);
            } else {
                No();
            }
        }
    }

    return 0;
}
