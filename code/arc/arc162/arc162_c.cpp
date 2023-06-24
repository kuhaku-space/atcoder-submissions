#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/home/github/algo/lib/template/template.hpp"
#pragma GCC target("sse4.2,avx2,bmi2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
template <class T, class U>
bool chmax(T &a, const U &b) {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U &b) {
    return (T)b < a ? a = (T)b, true : false;
}
constexpr std::int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
constexpr double PI = M_PI;
#line 2 "/home/kuhaku/home/github/algo/lib/algorithm/mex.hpp"

/**
 * @brief Mex
 *
 */
struct minimum_excluded {
    minimum_excluded() : n(), _size(), is_exist(64), v() {}

    constexpr int operator()() const noexcept { return this->n; }
    constexpr int get() const noexcept { return this->n; }

    void add(int x) {
        if (x < 0) return;
        ++this->_size;
        if (this->_size == (int)this->is_exist.size()) {
            this->is_exist.resize(this->_size << 1);
            int cnt = 0;
            for (int i = 0; i < (int)this->v.size(); ++i) {
                if (this->v[i] < (int)this->is_exist.size()) {
                    if (this->is_exist[this->v[i]]) --this->_size;
                    else this->is_exist[this->v[i]] = true;
                } else {
                    this->v[cnt++] = this->v[i];
                }
            }
            this->v.erase(this->v.begin() + cnt, this->v.end());
        }
        if (x < (int)this->is_exist.size()) {
            if (this->is_exist[x]) --this->_size;
            else this->is_exist[x] = true;
        } else {
            this->v.emplace_back(x);
        }
        while (this->is_exist[this->n]) ++this->n;
    }

  private:
    int n, _size;
    std::vector<bool> is_exist;
    std::vector<int> v;
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
#line 6 "a.cpp"

void solve() {
    int n, k;
    cin >> n >> k;
    Graph<void> g(n);
    rep (i, n - 1) {
        int p;
        cin >> p;
        g.add_edges(i + 1, p - 1);
    }

    vector<int> v(n);
    cin >> v;
    int c = 0;
    vector<bool> u(k + 1);
    auto dfs = [&](auto self, int idx, int par) -> void {
        if (v[idx] == -1)
            ++c;
        else if (v[idx] <= k)
            u[v[idx]] = true;
        for (auto e : g[idx]) {
            if (e.to() == par)
                continue;
            self(self, e.to(), idx);
        }
    };

    bool flag = false;
    auto dfs2 = [&](auto self, int idx, int par) -> void {
        c = 0;
        u = vector<bool>(k + 1);
        dfs(dfs, idx, par);
        if (u[k] == false) {
            int t = 0;
            rep (i, k) {
                t += !u[i];
            }
            flag |= t == 0 && c <= 1;
            flag |= t <= 1 && c == 1;
        }
        for (auto e : g[idx]) {
            if (e.to() == par)
                continue;
            self(self, e.to(), idx);
        }
    };

    dfs2(dfs2, 0, -1);
    if (flag)
        co("Alice");
    else
        co("Bob");
}

int main(void) {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
