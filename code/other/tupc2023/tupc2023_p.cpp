#line 1 "a.cpp"
#define PROBLEM ""
#line 1 "/home/kuhaku/home/github/algo/lib/flow/hopcroft_karp.hpp"
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
#line 2 "/home/kuhaku/home/github/algo/lib/graph/graph.hpp"
#include <iostream>
#line 4 "/home/kuhaku/home/github/algo/lib/graph/graph.hpp"

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
    vector<pair<int, int>> a(m);
    cin >> a;

    vector<int> ls, rs;
    rep (i, m) {
        auto [x, y] = a[i];
        if (x % 2 == 1)
            ls.emplace_back(i);
        else
            rs.emplace_back(i);
    }

    vector<pair<int, int>> ps, qs;
    rep (i, m) {
        if (a[i].first % 2 != 1)
            continue;
        int x = lower_bound(all(ls), i) - ls.begin();
        rep (j, m) {
            if (a[j].first % 2 != 0)
                continue;
            int y = lower_bound(all(rs), j) - rs.begin();
            if (a[i].first <= a[j].first && a[j].first <= a[i].second &&
                a[i].second <= a[j].second) {
                ps.emplace_back(x, y);
                qs.emplace_back(i, j);
            } else if (a[j].first <= a[i].first && a[i].first <= a[j].second &&
                       a[j].second <= a[i].second) {
                ps.emplace_back(x, y);
                qs.emplace_back(i, j);
            }
        }
    }

    hopcroft_karp mf(ls.size(), rs.size());
    for (auto [x, y] : ps) mf.add_edge(x, y);
    mf.matching();

    set<pair<int, int>> st;
    for (auto [x, y] : mf.get_pairs()) {
        st.emplace(ls[x], rs[y]);
    }

    Graph<void> g(m);
    vector<int> indeg(m);
    for (auto [x, y] : qs) {
        if (st.count({x, y})) {
            g.add_edge(y, x);
            ++indeg[x];
        } else
            g.add_edge(x, y);
    }

    queue<int> que;
    vector<int> color(m);
    for (auto x : ls) {
        if (indeg[x] == 0) {
            color[x] = 1;
            que.emplace(x);
        }
    }

    while (!que.empty()) {
        int x = que.front();
        que.pop();
        for (auto e : g[x]) {
            if (color[e.to()])
                continue;
            color[e.to()] = 1;
            que.emplace(e.to());
        }
    }

    int ans = 0;
    for (int x : ls) {
        if (color[x])
            ++ans;
    }
    for (int x : rs) {
        if (!color[x])
            ++ans;
    }
    co(ans);

    return 0;
}
