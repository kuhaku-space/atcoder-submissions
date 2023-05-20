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
#line 3 "/home/kuhaku/home/github/algo/lib/graph/graph.hpp"

/**
 * @brief 重み付きグラフ
 *
 * @tparam T 辺の重みの型
 */
template <class T>
struct Graph {
  private:
    struct _edge {
        constexpr _edge() : _from(), _to(), _weight() {}
        constexpr _edge(int from, int to, T weight) : _from(from), _to(to), _weight(weight) {}
        constexpr bool operator<(const _edge &rhs) const { return this->weight() < rhs.weight(); }
        constexpr bool operator>(const _edge &rhs) const { return rhs < *this; }

        constexpr int from() const { return this->_from; }
        constexpr int to() const { return this->_to; }
        constexpr T weight() const { return this->_weight; }

      private:
        int _from, _to;
        T _weight;
    };

  public:
    using edge_type = typename Graph<T>::_edge;

    Graph(int v) : _size(v), edges(v) {}

    const auto &operator[](int i) const { return this->edges[i]; }
    auto &operator[](int i) { return this->edges[i]; }
    const auto begin() const { return this->edges.begin(); }
    auto begin() { return this->edges.begin(); }
    const auto end() const { return this->edges.end(); }
    auto end() { return this->edges.end(); }
    constexpr int size() const { return this->_size; }

    void add_edge(const edge_type &e) { this->edges[e.from()].emplace_back(e); }
    void add_edge(int from, int to, T weight = T(1)) {
        this->edges[from].emplace_back(from, to, weight);
    }
    void add_edges(int from, int to, T weight = T(1)) {
        this->edges[from].emplace_back(from, to, weight);
        this->edges[to].emplace_back(to, from, weight);
    }

    void input_edge(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            T weight;
            std::cin >> from >> to >> weight;
            this->add_edge(from - base, to - base, weight);
        }
    }
    void input_edges(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            T weight;
            std::cin >> from >> to >> weight;
            this->add_edges(from - base, to - base, weight);
        }
    }

  private:
    int _size;
    std::vector<std::vector<edge_type>> edges;
};

template <>
struct Graph<void> {
  private:
    struct _edge {
        constexpr _edge() : _from(), _to() {}
        constexpr _edge(int from, int to) : _from(from), _to(to) {}

        constexpr int from() const { return this->_from; }
        constexpr int to() const { return this->_to; }
        constexpr int weight() const { return 1; }
        constexpr bool operator<(const _edge &rhs) const { return this->weight() < rhs.weight(); }
        constexpr bool operator>(const _edge &rhs) const { return rhs < *this; }

      private:
        int _from, _to;
    };

  public:
    using edge_type = typename Graph<void>::_edge;

    Graph(int v) : _size(v), edges(v) {}

    const auto &operator[](int i) const { return this->edges[i]; }
    auto &operator[](int i) { return this->edges[i]; }
    const auto begin() const { return this->edges.begin(); }
    auto begin() { return this->edges.begin(); }
    const auto end() const { return this->edges.end(); }
    auto end() { return this->edges.end(); }
    constexpr int size() const { return this->_size; }

    void add_edge(const edge_type &e) { this->edges[e.from()].emplace_back(e); }
    void add_edge(int from, int to) { this->edges[from].emplace_back(from, to); }
    void add_edges(int from, int to) {
        this->edges[from].emplace_back(from, to);
        this->edges[to].emplace_back(to, from);
    }

    void input_edge(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            std::cin >> from >> to;
            this->add_edge(from - base, to - base);
        }
    }
    void input_edges(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            std::cin >> from >> to;
            this->add_edges(from - base, to - base);
        }
    }

  private:
    int _size;
    std::vector<std::vector<edge_type>> edges;
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
#line 2 "/home/kuhaku/home/github/algo/lib/data_structure/persistent_array.hpp"

/**
 * @brief 永続配列
 * @see https://ei1333.github.io/luzhiled/snippets/structure/persistent-array.html
 * @see https://qiita.com/hotman78/items/9c643feae1de087e6fc5
 * @see https://37zigen.com/persistent-array/
 *
 * @tparam T 要素の型
 * @tparam B ビットサイズ
 */
template <class T, int B = 4>
struct persistent_array {
  private:
    static constexpr int MASK = (1 << B) - 1;

    struct Node {
        using pointer = Node *;
        T val;
        pointer ch[1 << B] = {};
    };
    using node_pointer = typename Node::pointer;

  public:
    constexpr persistent_array() : root() {}
    constexpr persistent_array(node_pointer _root) : root(_root) {}
    constexpr persistent_array(int n, T val) : root() {
        for (int i = 0; i < n; ++i) { this->root = this->set(i, val, this->root); }
    }
    template <class U>
    constexpr persistent_array(const std::vector<U> &v) : root() {
        for (int i = 0; i < (int)v.size(); ++i) { this->root = this->set(i, v[i], this->root); }
    }

    constexpr T operator[](int i) const noexcept {
        node_pointer node = this->root;
        while (node) {
            if (i == 0) {
                return node->val;
            } else {
                --i;
                node = node->ch[i & MASK], i = i >> B;
            }
        }
        return T();
    }
    constexpr T at(int k) const noexcept { return this->operator[](k); }
    constexpr T get(int k) const noexcept { return this->operator[](k); }

    persistent_array set(int k, T val) const noexcept {
        return persistent_array(this->set(k, val, this->root));
    }

  private:
    node_pointer root;

    node_pointer set(int k, T val, node_pointer node) const noexcept {
        node_pointer res = new Node();
        if (node) {
            memcpy(res->ch, node->ch, sizeof(node->ch));
            res->val = node->val;
        }
        if (k == 0) {
            res->val = val;
        } else {
            --k;
            res->ch[k & MASK] = set(k >> B, val, res->ch[k & MASK]);
        }
        return res;
    }
};
#line 3 "/home/kuhaku/home/github/algo/lib/tree/persistent_union_find.hpp"

/**
 * @brief 永続Union-Find
 *
 */
struct persistent_union_find {
    constexpr persistent_union_find() : data() {}
    persistent_union_find(const persistent_array<int> &_data) : data(_data) {}
    persistent_union_find(int n) : data(n, -1) {}

    int root(int x) const {
        int y = this->data[x];
        return y < 0 ? x : this->root(y);
    }
    int get_root(int x) const { return this->root(x); }

    bool is_root(int x) const { return this->data[x] < 0; }

    persistent_union_find unite(int x, int y) {
        x = this->root(x), y = this->root(y);
        if (x == y) return *this;
        int a = this->data[x], b = this->data[y];
        if (a > b) swap(x, y);
        return persistent_union_find(this->data.set(x, a + b).set(y, x));
    }

    int size(int x) const { return -(this->data[this->root(x)]); }
    int get_size(int x) const { return this->size(x); }

    bool same(int x, int y) const { return this->root(x) == this->root(y); }
    bool is_same(int x, int y) const { return this->same(x, y); }

  private:
    persistent_array<int> data;
};
#line 5 "a.cpp"

int main(void) {
    int n;
    cin >> n;
    vector<pair<int, int>> p(n);
    cin >> p;
    for_each(all(p), [](auto &x) {
        --x.first, --x.second;
    });
    Graph<void> g(n);
    g.input_edges(n - 1);

    vector<persistent_array<int>> vs(n);
    vector<persistent_union_find> ufs(n);
    vector<int> ans(n);
    auto dfs = [&](auto self, int idx, int par) -> void {
        persistent_array<int> v;
        persistent_union_find uf;
        int sum = 0;
        if (par == -1) {
            v = persistent_array<int>(n, 0);
            uf = persistent_union_find(n);
        } else {
            v = vs[par];
            uf = ufs[par];
            sum = ans[par];
        }
        auto [x, y] = p[idx];
        x = uf.root(x), y = uf.root(y);
        if (x == y) {
            if (v[x] == 0) {
                ++sum;
                v = v.set(x, 1);
            }
        } else {
            int s = v[x] + v[y];
            uf = uf.unite(x, y);
            if (s == 0) {
                ++sum;
            } else if (s == 1) {
                ++sum;
                v = v.set(x, 1).set(y, 1);
            }
        }
        vs[idx] = v;
        ufs[idx] = uf;
        ans[idx] = sum;

        for (auto e : g[idx]) {
            if (e.to() != par)
                self(self, e.to(), idx);
        }
    };

    dfs(dfs, 0, -1);
    ans.erase(ans.begin());
    co(ans);

    return 0;
}
