// competitive-verifier: PROBLEM
#include <cassert>
#include <utility>
#include <vector>
/**
 * @brief Hopcroft-Karp algorithm
 * @see https://judge.yosupo.jp/submission/99577
 */
struct hopcroft_karp {
    hopcroft_karp(int _n, int _m) : n(_n), m(_m), g(_n), match_left(_n, -1), match_right(_m, -1) {}
    void add_edge(int u, int v) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < m);
        g[u].emplace_back(v);
    }
    int matching() {
        int flow = 0;
        std::vector<int> root(n), prev(n), qq(n);
        for (bool updated = true; updated;) {
            updated = false;
            int qi = 0, qj = 0;
            std::fill(root.begin(), root.end(), -1);
            std::fill(prev.begin(), prev.end(), -1);
            for (int i = 0; i < n; i++) {
                if (match_left[i] == -1) qq[qj++] = i, root[i] = i, prev[i] = i;
            }
            while (qi < qj) {
                int u = qq[qi++];
                if (match_left[root[u]] != -1) continue;
                for (int v : g[u]) {
                    if (match_right[v] == -1) {
                        while (v != -1)
                            match_right[v] = u, std::swap(match_left[u], v), u = prev[u];
                        updated = true, flow++;
                        break;
                    }
                    if (prev[match_right[v]] == -1)
                        v = match_right[v], prev[v] = u, root[v] = root[u], qq[qj++] = v;
                }
            }
        }
        return flow;
    }
    std::vector<std::pair<int, int>> get_pairs() const {
        std::vector<std::pair<int, int>> res;
        for (int i = 0; i < n; i++) {
            if (~match_left[i]) res.emplace_back(i, match_left[i]);
        }
        return res;
    }
  private:
    const int n, m;
    std::vector<std::vector<int>> g;
    std::vector<int> match_left, match_right;
};
#include <iostream>
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
#include <algorithm>
namespace internal {
struct graph_csr {
  private:
    struct edge_list {
        using const_iterator = std::vector<int>::const_iterator;
        edge_list(const graph_csr &g, int v) : g(g), v(v) {}
        const_iterator begin() const { return std::next(g.elist.begin(), g.start[v]); }
        const_iterator end() const { return std::next(g.elist.begin(), g.start[v + 1]); }
      private:
        const graph_csr &g;
        int v;
    };
  public:
    graph_csr(int n) : _size(n), edges(), start(n + 1) {}
    edge_list operator[](int i) const { return edge_list(*this, i); }
    constexpr int size() const { return _size; }
    void build() {
        for (auto [u, v] : edges) ++start[u + 1];
        for (int i = 0; i < _size; ++i) start[i + 1] += start[i];
        auto counter = start;
        elist = std::vector<int>(edges.size());
        for (auto [u, v] : edges) elist[counter[u]++] = v;
    }
    void add_edge(int u, int v) { edges.emplace_back(u, v); }
    void add_edges(int u, int v) {
        edges.emplace_back(u, v);
        edges.emplace_back(v, u);
    }
    void input_edge(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            std::cin >> from >> to;
            add_edge(from - base, to - base);
        }
        build();
    }
    void input_edges(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            std::cin >> from >> to;
            add_edges(from - base, to - base);
        }
        build();
    }
    int _size;
    std::vector<std::pair<int, int>> edges;
    std::vector<int> elist;
    std::vector<int> start;
};
}  // namespace internal
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
    std::vector<int> comp(n, -1), order;
    std::vector<bool> used(n);
    internal::graph_csr rg(n);
    for (auto &es : g) {
        for (auto &e : es) rg.add_edge(e.to(), e.from());
    }
    rg.build();
    auto dfs = [&](auto self, int index) {
        if (used[index]) return;
        used[index] = true;
        for (auto &e : g[index]) self(self, e.to());
        order.emplace_back(index);
    };
    auto rdfs = [&](auto self, int index, int count) {
        if (~comp[index]) return;
        comp[index] = count;
        for (int u : rg[index]) self(self, u, count);
    };
    for (int i = 0; i < n; ++i) dfs(dfs, i);
    std::reverse(order.begin(), order.end());
    int ptr = 0;
    for (auto i : order) {
        if (comp[i] == -1) rdfs(rdfs, i, ptr++);
    }
    return comp;
};
std::vector<int> scc(const internal::graph_csr &g) {
    int n = g.size();
    std::vector<int> comp(n, -1), order;
    std::vector<bool> used(n);
    internal::graph_csr rg(n);
    for (int i = 0; i < n; ++i) {
        for (int u : g[i]) rg.add_edge(u, i);
    }
    rg.build();
    auto dfs = [&](auto self, int index) {
        if (used[index]) return;
        used[index] = true;
        for (int u : g[index]) self(self, u);
        order.emplace_back(index);
    };
    auto rdfs = [&](auto self, int index, int count) {
        if (~comp[index]) return;
        comp[index] = count;
        for (int u : rg[index]) self(self, u, count);
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
Graph<T> make_directed_acyclic_graph(const Graph<T> &g, const std::vector<int> &v) {
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
Graph<void> make_directed_acyclic_graph(const Graph<void> &g, const std::vector<int> &v) {
    Graph<void> res(*std::max_element(v.begin(), v.end()) + 1);
    for (auto &es : g) {
        for (auto &e : es) {
            int x = v[e.from()], y = v[e.to()];
            if (x != y) res.add_edge(x, y);
        }
    }
    return res;
}
internal::graph_csr make_directed_acyclic_graph(internal::graph_csr &g, const std::vector<int> &v) {
    int n = *std::max_element(v.begin(), v.end()) + 1;
    internal::graph_csr res(n);
    for (int i = 0; i < n; ++i) {
        for (int u : g[i]) {
            int x = v[i], y = v[u];
            if (x != y) res.add_edge(x, y);
        }
    }
    return res;
}
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
    int n;
    cin >> n;
    vector<string> s(n);
    cin >> s;
    Graph<void> g(n);
    rep (i, n) {
        rep (j, n) {
            if (i == j)
                continue;
            if (s[i][1] == s[j][0])
                g.add_edge(i, j);
        }
    }
    auto v = scc(g);
    auto h = make_directed_acyclic_graph(g, v);
    int m = h.size();
    vector<bitset<1000>> visited(m);
    repr (i, m) {
        for (auto e : h[i]) {
            visited[i][e.to()] = true;
            visited[i] |= visited[e.to()];
        }
    }
    hopcroft_karp hk(h.size(), h.size());
    rep (i, m) {
        rep (j, m) {
            if (visited[i][j])
                hk.add_edge(i, j);
        }
    }
    co(h.size() - hk.matching());
    return 0;
}
