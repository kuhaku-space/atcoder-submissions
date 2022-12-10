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
#line 3 "a.cpp"

/**
 * @brief 2分トライ木
 * @see https://kazuma8128.hatenablog.com/entry/2018/05/06/022654
 *
 * @tparam T 要素の型
 * @tparam B ビットサイズ
 */
template <class T, int B = 31>
struct binary_trie {
  private:
    struct _node {
        using pointer = _node *;
        int count;
        pointer ch[2];
        _node() : count(), ch{nullptr, nullptr} {}
    };

  public:
    using node_ptr = typename _node::pointer;

    constexpr binary_trie() : root(nullptr) {}

    T operator[](int k) const {
        assert(0 <= k && k < this->size());
        return this->get(this->root, k);
    }
    T at(int k) const {
        return this->operator[](k);
    }
    T get(int k) const {
        return this->operator[](k);
    }
    T kth_element(int k) const {
        return this->operator[](k);
    }

    constexpr bool empty() const {
        return !this->root;
    }
    constexpr int size() const {
        return this->empty() ? 0 : this->root->count;
    }

    void insert(T val) {
        this->root = this->insert(this->root, val);
    }
    void erase(T val) {
        if (this->count(val))
            this->root = this->erase(this->root, val);
    }

    T max_element(T bias = 0) const {
        return this->get_min(this->root, ~bias);
    }
    T min_element(T bias = 0) const {
        return this->get_min(this->root, bias);
    }
    int lower_bound(T val) const {
        return this->count_lower(this->root, val);
    }
    int upper_bound(T val) const {
        return this->count_lower(this->root, val + 1);
    }
    int count(T val) const {
        if (!this->root)
            return 0;
        node_ptr node = this->root;
        for (int i = B - 1; i >= 0; i--) {
            node = node->ch[val >> i & 1];
            if (!node)
                return 0;
        }
        return node->count;
    }

    node_ptr root;

  private:
    node_ptr insert(node_ptr node, T val, int b = B - 1) {
        if (!node)
            node = new _node();
        ++node->count;
        if (b < 0)
            return node;
        bool f = val >> b & (T)1;
        node->ch[f] = this->insert(node->ch[f], val, b - 1);
        return node;
    }
    node_ptr erase(node_ptr node, T val, int b = B - 1) {
        assert(node);
        --node->count;
        if (!node->count)
            return nullptr;
        if (b < 0)
            return node;
        bool f = val >> b & (T)1;
        node->ch[f] = this->erase(node->ch[f], val, b - 1);
        return node;
    }
    T get_min(node_ptr node, T val, int b = B - 1) const {
        assert(node);
        if (b < 0)
            return 0;
        bool f = val >> b & (T)1;
        f ^= !node->ch[f];
        return this->get_min(node->ch[f], val, b - 1) | ((T)f << (T)b);
    }
    T get(node_ptr node, int k, int b = B - 1) const {
        if (b < 0)
            return 0;
        int m = node->ch[0] ? node->ch[0]->count : 0;
        return k < m ? this->get(node->ch[0], k, b - 1)
                     : this->get(node->ch[1], k - m, b - 1) | ((T)1 << b);
    }
    int count_lower(node_ptr node, T val, int b = B - 1) const {
        if (!node || b < 0)
            return 0;
        bool f = val >> b & 1;
        return (f && node->ch[0] ? node->ch[0]->count : 0) +
               this->count_lower(node->ch[f], val, b - 1);
    }
};

int main(void) {
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;

    binary_trie<int> bt;
    for (auto x : a) {
        bt.insert(x);
    }

    auto dfs = [&](auto self, binary_trie<int, 31>::node_ptr node, int b) -> int {
        if (node == nullptr)
            return 0;
        if (node->ch[0] == nullptr && node->ch[1] == nullptr)
            return 0;
        int res = 0;
        if (node->ch[0] && node->ch[1]) {
            res += 1 << b;
        }
        int m = numeric_limits<int>::max();
        if (node->ch[0] != nullptr)
            chmin(m, self(self, node->ch[0], b - 1));
        if (node->ch[1] != nullptr)
            chmin(m, self(self, node->ch[1], b - 1));
        return res + m;
    };

    co(dfs(dfs, bt.root, 30));

    return 0;
}
