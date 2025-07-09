// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/convolution_mod
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
#include <optional>
template <class T>
struct ordered_set {
  private:
    struct node_t {
        using pointer = node_t *;
        T val, total;
        int height, count;
        pointer left, right;
        constexpr node_t(T _val) : val(_val), total(_val), height(1), count(1), left(nullptr), right(nullptr) {}
        static constexpr T get_total(pointer node) { return node == nullptr ? T() : node->total; }
        static constexpr int get_height(pointer node) { return node == nullptr ? 0 : node->height; }
        static constexpr int get_count(pointer node) { return node == nullptr ? 0 : node->count; }
        static constexpr int get_balance_factor(pointer node) {
            return node == nullptr ? 0 : node_t::get_height(node->left) - node_t::get_height(node->right);
        }
        constexpr void update() {
            total = node_t::get_total(left) + val + node_t::get_total(right);
            height = std::max(node_t::get_height(left), node_t::get_height(right)) + 1;
            count = node_t::get_count(left) + node_t::get_count(right) + 1;
        }
        constexpr bool is_leaf() const { return left == nullptr && right == nullptr; }
    };
  public:
    using node_type = node_t;
    using node_ptr = typename node_t::pointer;
    constexpr ordered_set() : root(nullptr) {}
    constexpr ordered_set(const std::vector<T> &v) : root(nullptr) {
        auto build = [&v](auto self, int l, int r) -> node_ptr {
            if (l == r) return nullptr;
            int m = (l + r) >> 1;
            auto node = new node_t(v[m]);
            node->left = self(self, l, m);
            node->right = self(self, m + 1, r);
            node->update();
            return node;
        };
        root = build(build, 0, v.size());
    }
    constexpr bool empty() const { return root == nullptr; }
    constexpr int size() const { return node_t::get_count(root); }
    void insert(T val) { root = insert(root, val); }
    void erase(T val) { root = erase(root, val); }
    void pop_front() { root = erase(root, front()); }
    void pop_back() { root = erase(root, back()); }
    T front() {
        assert(root);
        node_ptr node = root;
        while (node->left) node = node->left;
        return node->val;
    }
    T back() {
        assert(root);
        node_ptr node = root;
        while (node->right) node = node->right;
        return node->val;
    }
    T get(int k) const {
        assert(0 <= k && k < size());
        node_ptr node = root;
        while (true) {
            int c = node_t::get_count(node->left);
            if (c == k) break;
            if (k < c) node = node->left;
            else node = node->right, k -= c + 1;
        }
        return node->val;
    }
    int count(T val) const { return upper_bound(val) - lower_bound(val); }
    bool contains(T val) const {
        node_ptr node = root;
        while (node && node->val != val) node = (val < node->val ? node->left : node->right);
        return node != nullptr;
    }
    int lower_bound(T val) const {
        int res = 0;
        node_ptr node = root;
        while (node) {
            if (!(node->val < val)) node = node->left;
            else res += node_t::get_count(node->left) + 1, node = node->right;
        }
        return res;
    }
    int upper_bound(T val) const {
        int res = 0;
        node_ptr node = root;
        while (node) {
            if (val < node->val) node = node->left;
            else res += node_t::get_count(node->left) + 1, node = node->right;
        }
        return res;
    }
    std::optional<T> floor(T val) const {
        std::optional<T> res = std::nullopt;
        node_ptr node = root;
        while (node) {
            if (!(val < node->val)) res = node->val, node = node->right;
            else node = node->left;
        }
        return res;
    }
    std::optional<T> ceil(T val) const {
        std::optional<T> res = std::nullopt;
        node_ptr node = root;
        while (node) {
            if (!(node->val < val)) res = node->val, node = node->left;
            else node = node->right;
        }
        return res;
    }
    T minimum_sum(int k) const {
        assert(0 <= k && k <= size());
        if (k == size()) return node_t::get_total(root);
        T res{};
        node_ptr node = root;
        while (node && k) {
            int c = node_t::get_count(node->left);
            if (k < c) {
                node = node->left;
            } else {
                res += node_t::get_total(node->left);
                if (k == c) break;
                res += node->val;
                node = node->right, k -= c + 1;
            }
        }
        return res;
    }
    T maximum_sum(int k) const {
        assert(0 <= k && k <= size());
        if (k == size()) return node_t::get_total(root);
        T res{};
        node_ptr node = root;
        while (node && k) {
            int c = node_t::get_count(node->right);
            if (k < c) {
                node = node->right;
            } else {
                res += node_t::get_total(node->right);
                if (k == c) break;
                res += node->val;
                node = node->left, k -= c + 1;
            }
        }
        return res;
    }
  private:
    node_ptr root;
    constexpr T get_min_val(node_ptr node) const {
        assert(node);
        while (node->left) node = node->left;
        return node->val;
    }
    constexpr node_ptr rotl(node_ptr node) {
        assert(node);
        node_ptr pivot = node->right;
        assert(pivot);
        node->right = pivot->left;
        pivot->left = node;
        node->update();
        pivot->update();
        return pivot;
    }
    constexpr node_ptr rotr(node_ptr node) {
        assert(node);
        node_ptr pivot = node->left;
        assert(pivot);
        node->left = pivot->right;
        pivot->right = node;
        node->update();
        pivot->update();
        return pivot;
    }
    constexpr node_ptr rotlr(node_ptr node) {
        node->left = rotl(node->left);
        node = rotr(node);
        return node;
    }
    constexpr node_ptr rotrl(node_ptr node) {
        node->right = rotr(node->right);
        node = rotl(node);
        return node;
    }
    constexpr node_ptr rotate(node_ptr node) {
        int bf = node_type::get_balance_factor(node);
        if (bf < -1) {
            if (node_type::get_balance_factor(node->right) >= 1) node = rotrl(node);
            else node = rotl(node);
        } else if (bf > 1) {
            if (node_type::get_balance_factor(node->left) <= -1) node = rotlr(node);
            else node = rotr(node);
        } else {
            node->update();
        }
        return node;
    }
    constexpr node_ptr insert(node_ptr node, T val) {
        if (node == nullptr) return new node_t(val);
        if (val < node->val) node->left = insert(node->left, val);
        else node->right = insert(node->right, val);
        return rotate(node);
    }
    constexpr node_ptr erase(node_ptr node, T val) {
        if (node == nullptr) return nullptr;
        if (val < node->val) {
            node->left = erase(node->left, val);
        } else if (node->val < val) {
            node->right = erase(node->right, val);
        } else {
            if (node->right == nullptr) return node->left;
            else node->val = get_min_val(node->right), node->right = erase_min(node->right);
        }
        return rotate(node);
    }
    constexpr node_ptr erase_min(node_ptr node) {
        if (node->left == nullptr) return node->right;
        node->left = erase_min(node->left);
        return rotate(node);
    }
};
int main(void) {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n);
    cin >> a;
    ordered_set<ll> pq;
    vector<ll> ans;
    for (int i = 0; i < n; ++i) {
        pq.insert(a[i]);
        if (i >= m)
            pq.erase(a[i - m]);
        if (pq.size() == m) {
            ans.emplace_back(pq.minimum_sum(k));
        }
    }
    co(ans);
    return 0;
}
