#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/home/github/algo/lib/graph/graph.hpp"
#include <iostream>
#include <vector>

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
        constexpr bool operator<(const _edge &rhs) const { return weight() < rhs.weight(); }
        constexpr bool operator>(const _edge &rhs) const { return rhs < *this; }

        constexpr int from() const { return _from; }
        constexpr int to() const { return _to; }
        constexpr T weight() const { return _weight; }

      private:
        int _from, _to;
        T _weight;
    };

  public:
    using edge_type = typename Graph<T>::_edge;

    Graph() : _size(), edges() {}
    Graph(int v) : _size(v), edges(v) {}

    const auto &operator[](int i) const { return edges[i]; }
    auto &operator[](int i) { return edges[i]; }
    const auto begin() const { return edges.begin(); }
    auto begin() { return edges.begin(); }
    const auto end() const { return edges.end(); }
    auto end() { return edges.end(); }
    constexpr int size() const { return _size; }

    void add_edge(const edge_type &e) { edges[e.from()].emplace_back(e); }
    void add_edge(int from, int to, T weight = T(1)) { edges[from].emplace_back(from, to, weight); }
    void add_edges(int from, int to, T weight = T(1)) {
        edges[from].emplace_back(from, to, weight);
        edges[to].emplace_back(to, from, weight);
    }

    void input_edge(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            T weight;
            std::cin >> from >> to >> weight;
            add_edge(from - base, to - base, weight);
        }
    }
    void input_edges(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            T weight;
            std::cin >> from >> to >> weight;
            add_edges(from - base, to - base, weight);
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

        constexpr int from() const { return _from; }
        constexpr int to() const { return _to; }
        constexpr int weight() const { return 1; }
        constexpr bool operator<(const _edge &rhs) const { return weight() < rhs.weight(); }
        constexpr bool operator>(const _edge &rhs) const { return rhs < *this; }

      private:
        int _from, _to;
    };

  public:
    using edge_type = typename Graph<void>::_edge;

    Graph() : _size(), edges() {}
    Graph(int v) : _size(v), edges(v) {}

    const auto &operator[](int i) const { return edges[i]; }
    auto &operator[](int i) { return edges[i]; }
    const auto begin() const { return edges.begin(); }
    auto begin() { return edges.begin(); }
    const auto end() const { return edges.end(); }
    auto end() { return edges.end(); }
    constexpr int size() const { return _size; }

    void add_edge(const edge_type &e) { edges[e.from()].emplace_back(e); }
    void add_edge(int from, int to) { edges[from].emplace_back(from, to); }
    void add_edges(int from, int to) {
        edges[from].emplace_back(from, to);
        edges[to].emplace_back(to, from);
    }

    void input_edge(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            std::cin >> from >> to;
            add_edge(from - base, to - base);
        }
    }
    void input_edges(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            std::cin >> from >> to;
            add_edges(from - base, to - base);
        }
    }

  private:
    int _size;
    std::vector<std::vector<edge_type>> edges;
};
#line 2 "/home/kuhaku/home/github/algo/lib/template/template.hpp"
#pragma GCC target("sse4.2,avx2,bmi2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
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
constexpr double PI = M_PI;
#line 3 "/home/kuhaku/home/github/algo/lib/graph/scc.hpp"

/**
 * @brief 強連結成分分解
 *
 * @tparam T 辺の重みの型
 * @param g グラフ
 * @return std::vector<int> 各頂点が属する強連結成分の番号
 */
template <class T>
std::vector<int> scc(const Graph<T> &g) {
    int n = g.size();
    Graph<void> rg(n);
    std::vector<int> comp(n, -1), order;
    std::vector<bool> used(n);

    for (auto &es : g) {
        for (auto &e : es) rg.add_edge(e.to(), e.from());
    }

    auto dfs = [&](auto self, int index) {
        if (used[index]) return;
        used[index] = true;
        for (auto &e : g[index]) self(self, e.to());
        order.emplace_back(index);
    };
    auto rdfs = [&](auto self, int index, int count) {
        if (~comp[index]) return;
        comp[index] = count;
        for (auto &e : rg[index]) self(self, e.to(), count);
    };

    for (int i = 0; i < n; ++i) dfs(dfs, i);
    std::reverse(order.begin(), order.end());
    int ptr = 0;
    for (auto i : order) {
        if (comp[i] == -1) rdfs(rdfs, i, ptr++);
    }

    return comp;
};

/**
 * @brief 有向非巡回グラフの構築
 *
 * @tparam T 辺の重みの型
 * @param g グラフ
 * @param v 各頂点が属する強連結成分の番号
 * @return Graph<T> 有向非巡回グラフ
 */
template <class T>
Graph<T> make_DAG(const Graph<T> &g, const std::vector<int> &v) {
    Graph<T> res(*std::max_element(v.begin(), v.end()) + 1);
    for (auto &es : g) {
        for (auto &e : es) {
            int x = v[e.from()], y = v[e.to()];
            if (x != y) res.add_edge(x, y, e.weight());
        }
    }
    return res;
}

template <>
Graph<void> make_DAG(const Graph<void> &g, const std::vector<int> &v) {
    Graph<void> res(*std::max_element(v.begin(), v.end()) + 1);
    for (auto &es : g) {
        for (auto &e : es) {
            int x = v[e.from()], y = v[e.to()];
            if (x != y) res.add_edge(x, y);
        }
    }
    return res;
}
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
        std::cout << std::fixed << std::setprecision(20);
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
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    cin >> a;
    Graph<void> g(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        if (a[u] < a[v])
            g.add_edge(u, v);
        else if (a[u] > a[v])
            g.add_edge(v, u);
        else
            g.add_edges(u, v);
    }

    auto v = scc(g);
    auto dag = make_DAG(g, v);
    vector<int> dp(n, -1);
    dp[v[0]] = 0;
    rep (i, dag.size()) {
        if (dp[i] == -1)
            continue;
        for (auto e : dag[i]) {
            chmax(dp[e.to()], dp[e.from()] + 1);
        }
    }
    co(dp[v[n - 1]] + 1);

    return 0;
}
