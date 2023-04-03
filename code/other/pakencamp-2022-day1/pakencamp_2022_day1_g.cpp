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
#line 3 "/home/kuhaku/home/github/algo/lib/tree/hld.hpp"

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
            cin >> from >> to >> weight;
            this->add_edge(from - base, to - base, weight);
        }
    }
    void input_edges(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            T weight;
            cin >> from >> to >> weight;
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
            cin >> from >> to;
            this->add_edge(from - base, to - base);
        }
    }
    void input_edges(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            cin >> from >> to;
            this->add_edges(from - base, to - base);
        }
    }

  private:
    int _size;
    std::vector<std::vector<edge_type>> edges;
};
#line 3 "/home/kuhaku/home/github/algo/lib/tree/tree_function.hpp"

template <class T>
std::vector<int> tree_bfs(const Graph<T> &g, int r = 0) {
    int pos = 0;
    std::vector<int> res;
    std::vector<bool> visited(g.size());
    res.emplace_back(r);
    visited[r] = true;
    while (pos < (int)res.size()) {
        auto index = res[pos++];
        for (auto &e : g[index]) {
            if (visited[e.to()]) continue;
            res.emplace_back(e.to());
            visited[e.to()] = true;
        }
    }
    return res;
}

std::vector<int> tree_bfs(const std::vector<int> &parents) {
    int n = parents.size();
    Graph<void> g(n);
    int r = 0;
    for (int i = 0; i < n; ++i) {
        if (parents[i] == -1 || parents[i] == i) {
            r = i;
            continue;
        }
        g.add_edges(i, parents[i]);
    }
    return tree_bfs(g, r);
}

template <class T>
std::vector<int> tree_dfs(const Graph<T> &g, int r = 0) {
    std::vector<int> res;
    auto dfs = [&g, &res](auto self, int index, int parent) {
        res.emplace_back(index);
        for (auto &e : g[index]) {
            if (e.to() == parent) continue;
            self(self, e.to(), index);
        }
    };
    dfs(dfs, r, -1);
    return res;
}

/**
 * @brief 木の距離を求める
 *
 * @tparam T 辺の重みの型
 * @tparam U 距離の型
 * @param g 木
 * @param r 根
 * @return std::vector<U> 各頂点の根からの距離
 */
template <class T, class U = T>
std::vector<U> tree_dist(const Graph<T> &g, int r = 0) {
    std::vector<U> res(g.size(), -1);
    std::stack<int> st;
    res[r] = 0;
    st.emplace(r);
    while (!st.empty()) {
        auto index = st.top();
        st.pop();
        for (auto &e : g[index]) {
            if (res[e.to()] != -1) continue;
            res[e.to()] = res[index] + e.weight();
            st.emplace(e.to());
        }
    }
    return res;
}

/**
 * @brief 木の頂点の親を求める
 *
 * @tparam T 辺の重みの型
 * @param g 木
 * @param r 根
 * @return std::vector<int>
 */
template <class T>
std::vector<int> tree_parent(const Graph<T> &g, int r = 0) {
    std::vector<int> res(g.size(), -1);
    std::stack<int> st;
    res[r] = r;
    st.emplace(r);
    while (!st.empty()) {
        auto index = st.top();
        st.pop();
        for (auto &e : g[index]) {
            if (res[e.to()] != -1) continue;
            res[e.to()] = index;
            st.emplace(e.to());
        }
    }
    res[r] = -1;
    return res;
}

/**
 * @brief 部分木の大きさを求める
 *
 * @tparam T 辺の重みの型
 * @param g グラフ
 * @param r 根
 * @return std::vector<int>
 */
template <class T>
std::vector<int> tree_subtree(const Graph<T> &g, int r = 0) {
    std::vector<int> res(g.size());
    auto dfs = [&g, &res](auto self, int index) -> int {
        res[index] = 1;
        for (auto &e : g[index]) {
            if (res[e.to()] != 0) continue;
            res[index] += self(self, e.to());
        }
        return res[index];
    };
    dfs(dfs, r);
    return res;
}
#line 5 "a.cpp"

int main(void) {
    int n;
    cin >> n;
    vector<int> p(n - 1);
    cin >> p;
    for_each(all(p), [](auto &x) {
        --x;
    });

    HLD hld(n);
    Graph<int> g(n);
    rep (i, n - 1) {
        g.add_edges(i + 1, p[i]);
        hld.add_edge(i + 1, p[i]);
    }
    hld.build();

    auto d = tree_dist(g);
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        co(hld.la(v, d[v] - d[u] - 1) + 1);
    }

    return 0;
}
