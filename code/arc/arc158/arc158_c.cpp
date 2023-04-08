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

int main(void) {
    int n;
    cin >> n;
    vector<ll> a(n);
    cin >> a;

    ll ans = 0;
    for (auto x : a) {
        while (x) {
            ans += x % 10 * n * 2;
            x /= 10;
        }
    }

    ll p = 1;
    rep (i, 16) {
        p *= 10;
        vector<ll> v;
        rep (j, n) {
            v.emplace_back(a[j] % p);
        }
        sort(all(v));
        rep (j, n) {
            ans -= 9 * (v.end() - lower_bound(all(v), p - a[j] % p));
        }
    }
    co(ans);

    return 0;
}
