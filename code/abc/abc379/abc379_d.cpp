// competitive-verifier: PROBLEM
#include <utility>
#include <vector>
/**
 * @brief ランレングス圧縮
 *
 * @tparam Container
 * @param v 配列
 * @return auto
 */
template <class Container>
auto run_length_encoding(const Container &v) {
    std::vector<std::pair<std::decay_t<decltype(v[0])>, int>> res;
    for (auto &&e : v) {
        if (res.empty() || res.back().first != e) res.emplace_back(e, 1);
        else ++res.back().second;
    }
    return res;
}
#include <cassert>
#include <iostream>
#include <random>
/**
 * @brief Treap
 *
 * @tparam T 要素の型
 * @tparam UniformRandomBitGenerator 疑似乱数生成器
 */
template <class T, class UniformRandomBitGenerator = std::mt19937>
struct treap {
  private:
    struct node_t {
        using pointer = node_t *;
        static int count(pointer t) { return t ? t->cnt : 0; }
        node_t(T _val, typename UniformRandomBitGenerator::result_type _priority)
            : val(_val), priority(_priority), cnt(1), left(nullptr), right(nullptr) {}
        T val;
        typename UniformRandomBitGenerator::result_type priority;
        int cnt;
        pointer left, right;
    };
  public:
    using node_ptr = typename node_t::pointer;
    constexpr treap() : root(nullptr) {}
    constexpr treap(node_ptr p) : root(p) {}
    bool empty() const { return root == nullptr; }
    int size() const { return node_t::count(root); }
    T top() { return root->val; }
    T get(int k) const {
        assert(0 <= k && k < size());
        node_ptr node = root;
        while (true) {
            int c = node_t::count(node->left);
            if (c == k) break;
            if (k < c) node = node->left;
            else node = node->right, k -= c + 1;
        }
        return node->val;
    }
    int lower_bound(T val) const {
        int res = 0;
        node_ptr node = root;
        while (node) {
            int c = node_t::count(node->left);
            if (node->val < val) node = node->right, res += c + 1;
            else node = node->left;
        }
        return res;
    }
    void insert(T val) {
        node_ptr t = new node_t(val, gen());
        root = merge(root, t);
    }
    void erase(T val) { root = erase(root, val); }
    bool contains(T val) const {
        node_ptr node = root;
        while (node && node->val != val) {
            if (val < node->val) node = node->left;
            else node = node->right;
        }
        return node != nullptr;
    }
    int count(T val) const { return count(root, val); }
    std::pair<treap, treap> split(T val) {
        auto [l, r] = split(root, val);
        return std::make_pair(treap(l), treap(r));
    }
    void merge(treap treap) { root = merge(root, treap.root); }
  private:
    static inline UniformRandomBitGenerator gen = UniformRandomBitGenerator();
    node_ptr root;
    node_ptr update(node_ptr t) {
        if (t == nullptr) return t;
        t->cnt = node_t::count(t->left) + node_t::count(t->right) + 1;
        return t;
    }
    node_ptr merge(node_ptr l, node_ptr r) {
        if (!l || !r) return !l ? r : l;
        if (l->priority < r->priority) std::swap(l, r);
        auto [p, q] = split(r, l->val);
        l->left = merge(l->left, p);
        l->right = merge(l->right, q);
        return update(l);
    }
    node_ptr simple_merge(node_ptr l, node_ptr r) {
        if (!l || !r) return !l ? r : l;
        if (l->priority > r->priority) {
            if (l->val < r->val) l->right = simple_merge(l->right, r);
            else l->left = simple_merge(l->left, r);
            return update(l);
        } else {
            if (l->val < r->val) r->left = simple_merge(l, r->left);
            else r->right = simple_merge(l, r->right);
            return update(r);
        }
    }
    std::pair<node_ptr, node_ptr> split(node_ptr node, T val) {
        if (node == nullptr) return {nullptr, nullptr};
        if (node->val < val) {
            auto [l, r] = split(node->right, val);
            node->right = nullptr;
            update(node);
            return {merge(node, l), r};
        } else {
            auto [l, r] = split(node->left, val);
            node->left = nullptr;
            update(node);
            return {l, merge(r, node)};
        }
    }
    node_ptr erase(node_ptr node, T val) {
        if (node == nullptr) return nullptr;
        if (val == node->val) return simple_merge(node->left, node->right);
        if (val < node->val) node->left = erase(node->left, val);
        else node->right = erase(node->right, val);
        return update(node);
    }
    int count(node_ptr node, T val) const {
        if (node == nullptr) return 0;
        int res = node->val == val;
        if (!(node->val < val)) res += count(node->left, val);
        if (!(val < node->val)) res += count(node->right, val);
        return res;
    }
};
#ifdef ATCODER
#pragma GCC target("sse4.2,avx512f,avx512dq,avx512ifma,avx512cd,avx512bw,avx512vl,bmi2")
#endif
#pragma GCC optimize("Ofast,fast-math,unroll-all-loops")
#include <bits/stdc++.h>
#ifndef ATCODER
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
#define FORR(i, m, n) for (int i = (m)-1; i >= int(n); --i)
#define FORL(i, m, n) for (int64_t i = (m); i < int64_t(n); ++i)
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
int main(void) {
    int q;
    cin >> q;
    ll s = 0;
    treap<ll> tp;
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            tp.insert(s);
        } else if (t == 2) {
            int x;
            cin >> x;
            s -= x;
        } else {
            int x;
            cin >> x;
            auto [l, r] = tp.split(s + x);
            co(r.size());
            tp = l;
        }
    }
    return 0;
}
