// competitive-verifier: PROBLEM
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
/// @brief 重み付きグラフ
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
/// @brief 重みなしグラフ
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
void solve() {
    int n;
    cin >> n;
    vector<string> s(n);
    cin >> s;
    vector dp(n, vector(n, Inf));
    queue<pair<int, int>> que;
    rep (i, n) {
        dp[i][i] = 0;
        que.emplace(i, i);
    }
    rep (i, n) {
        rep (j, n) {
            if (s[i][j] != '-') {
                if (chmin(dp[i][j], 1))
                    que.emplace(i, j);
            }
        }
    }
    while (!que.empty()) {
        auto [x, y] = que.front();
        que.pop();
        rep (i, n) {
            rep (j, n) {
                if (s[i][x] == s[y][j] && s[i][x] != '-') {
                    if (chmin(dp[i][j], dp[x][y] + 2))
                        que.emplace(i, j);
                }
            }
        }
    }
    rep (i, n) {
        rep (j, n) {
            if (dp[i][j] == Inf)
                dp[i][j] = -1;
        }
    }
    rep (i, n) co(dp[i]);
}
int main(void) {
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}
