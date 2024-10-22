// competitive-verifier: PROBLEM
#include <algorithm>
#include <cassert>
#include <limits>
#include <queue>
#include <vector>
/**
 * @brief 最小費用流
 *
 * @tparam Cap
 * @tparam Cost
 */
template <class Cap, class Cost>
struct mcf_graph {
    mcf_graph() {}
    explicit mcf_graph(int n) : _n(n) {}
    int add_edge(int from, int to, Cap cap, Cost cost) {
        assert(0 <= from && from < _n);
        assert(0 <= to && to < _n);
        assert(0 <= cap);
        assert(0 <= cost);
        int m = int(_edges.size());
        _edges.emplace_back(from, to, cap, 0, cost);
        return m;
    }
    struct edge {
        int from, to;
        Cap cap, flow;
        Cost cost;
        constexpr edge(int _from, int _to, Cap _cap, Cap _flow, Cost _cost)
            : from(_from), to(_to), cap(_cap), flow(_flow), cost(_cost) {}
    };
    edge get_edge(int i) {
        int m = int(_edges.size());
        assert(0 <= i && i < m);
        return _edges[i];
    }
    std::vector<edge> edges() { return _edges; }
    std::pair<Cap, Cost> flow(int s, int t) { return flow(s, t, std::numeric_limits<Cap>::max()); }
    std::pair<Cap, Cost> flow(int s, int t, Cap flow_limit) {
        return slope(s, t, flow_limit).back();
    }
    std::vector<std::pair<Cap, Cost>> slope(int s, int t) {
        return slope(s, t, std::numeric_limits<Cap>::max());
    }
    std::vector<std::pair<Cap, Cost>> slope(int s, int t, Cap flow_limit) {
        assert(0 <= s && s < _n);
        assert(0 <= t && t < _n);
        assert(s != t);
        int m = int(_edges.size());
        std::vector<int> edge_idx(m);
        auto g = [&]() {
            std::vector<int> degree(_n), redge_idx(m);
            std::vector<std::pair<int, _edge>> elist;
            elist.reserve(2 * m);
            for (int i = 0; i < m; ++i) {
                auto e = _edges[i];
                edge_idx[i] = degree[e.from]++;
                redge_idx[i] = degree[e.to]++;
                elist.emplace_back(e.from, _edge(e.to, -1, e.cap - e.flow, e.cost));
                elist.emplace_back(e.to, _edge(e.from, -1, e.flow, -e.cost));
            }
            auto _g = csr<_edge>(_n, elist);
            for (int i = 0; i < m; ++i) {
                auto e = _edges[i];
                edge_idx[i] += _g.start[e.from];
                redge_idx[i] += _g.start[e.to];
                _g.elist[edge_idx[i]].rev = redge_idx[i];
                _g.elist[redge_idx[i]].rev = edge_idx[i];
            }
            return _g;
        }();
        auto result = slope(g, s, t, flow_limit);
        for (int i = 0; i < m; ++i) {
            auto e = g.elist[edge_idx[i]];
            _edges[i].flow = _edges[i].cap - e.cap;
        }
        return result;
    }
  private:
    int _n;
    std::vector<edge> _edges;
    struct _edge {
        int to, rev;
        Cap cap;
        Cost cost;
        constexpr _edge() : to(), rev(), cap(), cost() {}
        constexpr _edge(int _to, int _rev, Cap _cap, Cost _cost)
            : to(_to), rev(_rev), cap(_cap), cost(_cost) {}
    };
    template <class E>
    struct csr {
        std::vector<int> start;
        std::vector<E> elist;
        explicit csr(int n, const std::vector<std::pair<int, E>> &edges)
            : start(n + 1), elist(edges.size()) {
            for (auto e : edges) start[e.first + 1]++;
            for (int i = 1; i <= n; i++) start[i] += start[i - 1];
            auto counter = start;
            for (auto e : edges) elist[counter[e.first]++] = e.second;
        }
    };
    std::vector<std::pair<Cap, Cost>> slope(csr<_edge> &g, int s, int t, Cap flow_limit) {
        std::vector<std::pair<Cost, Cost>> dual_dist(_n);
        std::vector<int> prev_e(_n);
        std::vector<bool> vis(_n);
        struct Q {
            Cost key;
            int to;
            constexpr Q(Cost _key, int _to) : key(_key), to(_to) {}
            bool operator<(Q r) const { return key > r.key; }
        };
        std::vector<int> que_min;
        std::vector<Q> que;
        auto dual_ref = [&]() {
            for (int i = 0; i < _n; ++i) dual_dist[i].second = std::numeric_limits<Cost>::max();
            std::fill(vis.begin(), vis.end(), false);
            que_min.clear();
            que.clear();
            size_t heap_r = 0;
            dual_dist[s].second = 0;
            que_min.emplace_back(s);
            while (!que_min.empty() || !que.empty()) {
                int v;
                if (!que_min.empty()) {
                    v = que_min.back();
                    que_min.pop_back();
                } else {
                    while (heap_r < que.size()) {
                        ++heap_r;
                        std::push_heap(que.begin(), que.begin() + heap_r);
                    }
                    v = que.front().to;
                    std::pop_heap(que.begin(), que.end());
                    que.pop_back();
                    heap_r--;
                }
                if (vis[v]) continue;
                vis[v] = true;
                if (v == t) break;
                Cost dual_v = dual_dist[v].first, dist_v = dual_dist[v].second;
                for (int i = g.start[v]; i < g.start[v + 1]; ++i) {
                    auto e = g.elist[i];
                    if (!e.cap) continue;
                    Cost cost = e.cost - dual_dist[e.to].first + dual_v;
                    if (dual_dist[e.to].second - dist_v > cost) {
                        Cost dist_to = dist_v + cost;
                        dual_dist[e.to].second = dist_to;
                        prev_e[e.to] = e.rev;
                        if (dist_to == dist_v) {
                            que_min.emplace_back(e.to);
                        } else {
                            que.emplace_back(dist_to, e.to);
                        }
                    }
                }
            }
            if (!vis[t]) return false;
            for (int v = 0; v < _n; ++v) {
                if (!vis[v]) continue;
                dual_dist[v].first -= dual_dist[t].second - dual_dist[v].second;
            }
            return true;
        };
        Cap flow = 0;
        Cost cost = 0, prev_cost_per_flow = -1;
        std::vector<std::pair<Cap, Cost>> result = {{Cap(0), Cost(0)}};
        while (flow < flow_limit) {
            if (!dual_ref()) break;
            Cap c = flow_limit - flow;
            for (int v = t; v != s; v = g.elist[prev_e[v]].to) {
                c = std::min(c, g.elist[g.elist[prev_e[v]].rev].cap);
            }
            for (int v = t; v != s; v = g.elist[prev_e[v]].to) {
                auto &e = g.elist[prev_e[v]];
                e.cap += c;
                g.elist[e.rev].cap -= c;
            }
            Cost d = -dual_dist[s].first;
            flow += c;
            cost += c * d;
            if (prev_cost_per_flow == d) result.pop_back();
            result.emplace_back(flow, cost);
            prev_cost_per_flow = d;
        }
        return result;
    }
};
#include <cstdint>
#include <utility>
namespace internal {
template <int Idx>
struct grid_impl {
    template <class Head, class... Tail>
    constexpr grid_impl(Head &&head, Tail &&...tail)
        : limit(head), impl(std::forward<Tail>(tail)...) {}
    template <class Head, class... Tail>
    constexpr bool in_field(Head x, Tail &&...tail) const {
        return 0 <= x && x < limit && impl.in_field(std::forward<Tail>(tail)...);
    }
    template <class Head, class... Tail>
    constexpr std::int64_t flatten(Head x, Tail &&...tail) const {
        return x + limit * impl.flatten(std::forward<Tail>(tail)...);
    }
  private:
    std::int64_t limit;
    grid_impl<Idx - 1> impl;
};
template <>
struct grid_impl<0> {
    constexpr grid_impl() {}
    constexpr bool in_field() const { return true; }
    constexpr std::int64_t flatten() const { return 0; }
};
}  // namespace internal
template <int Idx>
struct Grid {
    template <class... Args, std::enable_if_t<(sizeof...(Args) == Idx)> * = nullptr>
    constexpr Grid(Args &&...args) : entity(std::forward<Args>(args)...) {}
    template <class... Args, std::enable_if_t<(sizeof...(Args) == Idx)> * = nullptr>
    constexpr bool in_field(Args &&...args) const {
        return entity.in_field(std::forward<Args>(args)...);
    }
    template <class... Args, std::enable_if_t<(sizeof...(Args) == Idx)> * = nullptr>
    constexpr std::int64_t flatten(Args &&...args) const {
        return entity.flatten(std::forward<Args>(args)...);
    }
  private:
    internal::grid_impl<Idx> entity;
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
    int n, m;
    cin >> n >> m;
    Grid<2> grid(n, m);
    vector<string> s(n);
    cin >> s;
    mcf_graph<int, int> mcf(n * m * 2 + 2);
    int st = n * m * 2, gl = st + 1;
    int ans = 0;
    rep (i, n) {
        rep (j, m) {
            if (s[i][j] != '#') {
                mcf.add_edge(grid.flatten(i, j), n * m + grid.flatten(i, j), Inf, 0);
                mcf.add_edge(n * m + grid.flatten(i, j), gl, 1, n + m - i - j);
                if (grid.in_field(i, j + 1) && s[i][j + 1] != '#') {
                    mcf.add_edge(n * m + grid.flatten(i, j), grid.flatten(i, j + 1), Inf, 0);
                }
                if (grid.in_field(i + 1, j) && s[i + 1][j] != '#') {
                    mcf.add_edge(n * m + grid.flatten(i, j), grid.flatten(i + 1, j), Inf, 0);
                }
            }
            if (s[i][j] == 'o') {
                ans += n + m - i - j;
                mcf.add_edge(st, grid.flatten(i, j), 1, 0);
            }
        }
    }
    co(ans - mcf.flow(st, gl).second);
    return 0;
}
