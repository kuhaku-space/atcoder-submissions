// competitive-verifier: PROBLEM
#include <cstdint>
#include <utility>
#include <vector>
#include <iostream>
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
#include <stack>
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
/**
 * @brief HL分解
 * @see https://beet-aizu.github.io/library/tree/heavylightdecomposition.cpp
 */
struct heavy_light_decomposition {
    heavy_light_decomposition() = default;
    template <class T>
    heavy_light_decomposition(const Graph<T> &g, int r = 0) : heavy_light_decomposition(g.size()) {
        std::vector<int> heavy_path(_size, -1), sub_size(_size, 1);
        std::stack<int> st;
        st.emplace(r);
        int pos = 0;
        while (!st.empty()) {
            int v = st.top();
            st.pop();
            vid[pos++] = v;
            for (auto &e : g[v]) {
                int u = e.to();
                if (u == par[v]) continue;
                par[u] = v, dep[u] = dep[v] + 1, st.emplace(u);
            }
        }
        for (int i = _size - 1; i >= 0; --i) {
            int v = vid[i];
            int max_sub = 0;
            for (auto &e : g[v]) {
                int u = e.to();
                if (u == par[v]) continue;
                sub_size[v] += sub_size[u];
                if (max_sub < sub_size[u]) max_sub = sub_size[u], heavy_path[v] = u;
            }
        }
        nxt[r] = r;
        pos = 0;
        st.emplace(r);
        while (!st.empty()) {
            int v = st.top();
            st.pop();
            vid[v] = pos++;
            inv[vid[v]] = v;
            int hp = heavy_path[v];
            for (auto &e : g[v]) {
                int u = e.to();
                if (u == par[v] || u == hp) continue;
                nxt[u] = u, st.emplace(u);
            }
            if (hp != -1) nxt[hp] = nxt[v], st.emplace(hp);
        }
    }
    heavy_light_decomposition(const internal::graph_csr &g, int r = 0)
        : heavy_light_decomposition(g.size()) {
        std::vector<int> heavy_path(_size, -1), sub_size(_size, 1);
        std::stack<int> st;
        st.emplace(r);
        int pos = 0;
        while (!st.empty()) {
            int v = st.top();
            st.pop();
            vid[pos++] = v;
            for (int u : g[v]) {
                if (u == par[v]) continue;
                par[u] = v, dep[u] = dep[v] + 1, st.emplace(u);
            }
        }
        for (int i = _size - 1; i >= 0; --i) {
            int v = vid[i];
            int max_sub = 0;
            for (int u : g[v]) {
                if (u == par[v]) continue;
                sub_size[v] += sub_size[u];
                if (max_sub < sub_size[u]) max_sub = sub_size[u], heavy_path[v] = u;
            }
        }
        nxt[r] = r;
        pos = 0;
        st.emplace(r);
        while (!st.empty()) {
            int v = st.top();
            st.pop();
            vid[v] = pos++;
            inv[vid[v]] = v;
            int hp = heavy_path[v];
            for (int u : g[v]) {
                if (u == par[v] || u == hp) continue;
                nxt[u] = u, st.emplace(u);
            }
            if (hp != -1) nxt[hp] = nxt[v], st.emplace(hp);
        }
    }
    constexpr int size() const { return _size; }
    int get(int v) const { return vid[v]; }
    int get_parent(int v) const { return par[v]; }
    int get_depth(int v) const { return dep[v]; }
    int dist(int u, int v) const {
        int d = 0;
        while (true) {
            if (vid[u] > vid[v]) std::swap(u, v);
            if (nxt[u] == nxt[v]) return d + vid[v] - vid[u];
            d += vid[v] - vid[nxt[v]] + 1;
            v = par[nxt[v]];
        }
    }
    int jump(int u, int v, int k) const {
        int d = dist(u, v);
        if (d < k) return -1;
        int l = lca(u, v);
        if (dist(u, l) >= k) return la(u, k);
        else return la(v, d - k);
    }
    int la(int v, int k) const {
        while (true) {
            int u = nxt[v];
            if (vid[v] - k >= vid[u]) return inv[vid[v] - k];
            k -= vid[v] - vid[u] + 1;
            v = par[u];
        }
    }
    int lca(int u, int v) const {
        while (true) {
            if (vid[u] > vid[v]) std::swap(u, v);
            if (nxt[u] == nxt[v]) return u;
            v = par[nxt[v]];
        }
    }
    template <class F>
    void for_each(int u, int v, const F &f) const {
        while (true) {
            if (vid[u] > vid[v]) std::swap(u, v);
            f(std::max(vid[nxt[v]], vid[u]), vid[v] + 1);
            if (nxt[u] != nxt[v]) v = par[nxt[v]];
            else break;
        }
    }
    template <class F>
    void for_each_edge(int u, int v, const F &f) const {
        while (true) {
            if (vid[u] > vid[v]) std::swap(u, v);
            if (nxt[u] != nxt[v]) {
                f(vid[nxt[v]], vid[v] + 1);
                v = par[nxt[v]];
            } else {
                if (u != v) f(vid[u] + 1, vid[v] + 1);
                break;
            }
        }
    }
  private:
    int _size;
    std::vector<int> vid, nxt, par, dep, inv;
    heavy_light_decomposition(int n) : _size(n), vid(n, -1), nxt(n), par(n, -1), dep(n), inv(n) {}
};
/// @brief functional graph
struct functional_graph {
    functional_graph() = default;
    functional_graph(const std::vector<int> &_to) : functional_graph(_to.size(), _to) {
        for (int i = 0; i < _size; ++i) {
            int x = i;
            while (root[x] == -1) {
                root[x] = i;
                x = to[x];
            }
            int r = (root[x] == i ? x : root[x]);
            x = i;
            while (r != i && root[x] == i) {
                root[x] = r;
                x = to[x];
            }
        }
        for (int i = 0; i < _size; ++i) {
            if (root[i] == i) g.add_edge(_size, i);
            else g.add_edge(to[i], i);
        }
        g.build();
        hld = heavy_light_decomposition(g, _size);
    }
    constexpr int size() const { return _size; }
    int jump(int v, std::uint64_t step) const {
        int d = hld.get_depth(v);
        if (step <= (std::uint64_t)d - 1) return hld.jump(v, _size, step);
        v = root[v];
        step -= d - 1;
        int bottom = to[v];
        int c = hld.get_depth(bottom);
        step %= c;
        if (step == 0) return v;
        return hld.jump(bottom, _size, step - 1);
    }
    std::vector<int> jump_all(std::uint64_t step) const {
        std::vector<int> res(_size, -1);
        std::vector<std::pair<int, int>> query;
        internal::graph_csr csr(_size);
        for (int v = 0; v < _size; ++v) {
            int d = hld.get_depth(v);
            int r = root[v];
            if ((std::uint64_t)d - 1 > step) {
                csr.add_edge(v, query.size());
                query.emplace_back(v, step);
            } else {
                std::int64_t k = step - (d - 1);
                int bottom = to[r];
                int c = hld.get_depth(bottom);
                k %= c;
                if (k == 0) {
                    res[v] = r;
                    continue;
                }
                csr.add_edge(bottom, query.size());
                query.emplace_back(v, k - 1);
            }
        }
        csr.build();
        std::vector<int> path;
        auto dfs = [&](auto self, int v) -> void {
            path.emplace_back(v);
            for (int id : csr[v]) res[query[id].first] = path[path.size() - 1 - query[id].second];
            for (int u : g[v]) self(self, u);
            path.pop_back();
        };
        for (int u : g[_size]) dfs(dfs, u);
        return res;
    }
    int dist(int u, int v) {
        if (root[u] != root[v]) return -1;
        if (u == v) return 0;
        int du = hld.get_depth(u);
        int dv = hld.get_depth(v);
        if (du > dv) return du - dv;
        int c = hld.get_depth(to[root[u]]);
        return dv > c ? -1 : c - dv + du;
    }
    int cycle(int v) const {
        v = root[v];
        return hld.get_depth(to[v]);
    }
    std::vector<std::vector<int>> get_cycles() const {
        std::vector<std::vector<int>> res;
        for (int v = 0; v < _size; ++v) {
            if (v == root[v]) res.emplace_back(get_cycle(v));
        }
        return res;
    }
  private:
    int _size;
    const std::vector<int> &to;
    std::vector<int> root;
    internal::graph_csr g;
    heavy_light_decomposition hld;
    functional_graph(int n, const std::vector<int> &_to)
        : _size(n), to(_to), root(n, -1), g(n + 1), hld() {}
    std::vector<int> get_cycle(int v) const {
        std::vector<int> res(1, v);
        int u = to[v];
        while (u != v) {
            res.emplace_back(u);
            u = to[u];
        }
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
template <class F>
std::int64_t meguru_binary_search(std::int64_t ok, std::int64_t ng, F check) {
    while (abs(ok - ng) > 1) {
        std::int64_t mid = (ok + ng) / 2;
        (check(mid) ? ok : ng) = mid;
    }
    return ok;
}
int main(void) {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    cin >> a;
    ll s = accumulate(all(a), 0l);
    rep (i, n) a.emplace_back(a[i]);
    a.emplace_back(0);
    repr (i, 2 * n) a[i] += a[i + 1];
    ll l = 0, r = s;
    ll ans = 0;
    while (r - l > 1) {
        ll w = (l + r) / 2;
        vector<int> v(2 * n + 2);
        v[2 * n + 1] = 2 * n + 1;
        rep (i, 2 * n + 1) {
            int f = i, g = 2 * n + 1;
            auto check = [&](int x) {
                return a[i] - a[x] >= w;
            };
            v[i] = meguru_binary_search(g, f, check);
        }
        functional_graph fg(v);
        auto jp = fg.jump_all(k);
        int c = 0;
        rep (i, n) {
            if (jp[i] - i <= n)
                ++c;
        }
        if (c) {
            l = w;
            ans = n - c;
        } else {
            r = w;
        }
    }
    co(l, ans);
    return 0;
}
