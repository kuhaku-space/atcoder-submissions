#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/template/template.hpp"
#include <bits/stdc++.h>
using namespace std;
template <class T, class U>
bool chmax(T &a, const U &b) {
    return a < b ? a = b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U &b) {
    return b < a ? a = b, true : false;
}
constexpr int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
const double PI = acos(-1.0);
#line 3 "/home/kuhaku/atcoder/github/atcoder-lib/lib/graph/graph.hpp"

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
        bool operator<(const _edge &rhs) const { return this->weight() < rhs.weight(); }
        bool operator>(const _edge &rhs) const { return rhs < *this; }

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
        bool operator<(const _edge &rhs) const { return false; }
        bool operator>(const _edge &rhs) const { return rhs < *this; }

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
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/template/atcoder.hpp"
#pragma GCC target("avx")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#line 6 "/home/kuhaku/atcoder/github/atcoder-lib/lib/template/atcoder.hpp"
using ll = int64_t;
using ld = long double;
#define FOR(i, m, n) for(int i = (m); i < int(n); ++i)
#define FORR(i, m, n) for(int i = (m)-1; i >= int(n); --i)
#define FORL(i, m, n) for(int64_t i = (m); i < int64_t(n); ++i)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FOR(i, 1, n+1)
#define repr(i, n) FORR(i, n, 0)
#define repnr(i, n) FORR(i, n+1, 1)
#define all(s) (s).begin(), (s).end()
template<class T, class U>
std::istream &operator>>(std::istream &is, std::pair<T, U> &p) { is >> p.first >> p.second; return is; }
template <class T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) { for (T &i : v) is>>i; return is; }
template <class T, class U>
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &p) {
    return os<<'('<<p.first<< ','<<p.second<<')';
}
template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    for (auto it=v.begin(); it!=v.end(); ++it) { os<<(it==v.begin()?"":" ")<<*it; } return os;
}
template <class Head, class... Tail>
void co(Head&& head, Tail&&... tail) {
    if constexpr(sizeof...(tail)==0) std::cout<<head<<'\n'; else std::cout<<head<<' ',co(forward<Tail>(tail)...);
}
template <class Head, class... Tail>
void ce(Head&& head, Tail&&... tail) {
    if constexpr(sizeof...(tail)==0) std::cerr<<head<<'\n'; else std::cerr<<head<<' ',ce(forward<Tail>(tail)...);
}
template<typename T, typename... Args>
auto make_vector(T x, int arg, Args ...args) {
    if constexpr(sizeof...(args)==0) return std::vector<T>(arg,x); else return std::vector(arg,make_vector<T>(x,args...));
}
void sonic() { std::ios::sync_with_stdio(false); std::cin.tie(nullptr); }
void setp(const int n) { std::cout<<std::fixed<<std::setprecision(n); }
void Yes(bool is_correct) { std::cout<<(is_correct?"Yes":"No")<<std::endl; }
void YES(bool is_correct) { std::cout<<(is_correct?"YES":"NO")<<std::endl; }
#line 4 "a.cpp"

template <class T>
pair<T, int> operator+(pair<T, int> lhs, T rhs) {
    return {lhs.first + rhs, lhs.second};
}

template <class U>
vector<std::vector<pair<U, int>>> dijkstra(const Graph<U> &g, vector<int> &a, vector<int> &b) {
    using T = pair<U, int>;
    struct _node {
        constexpr _node() : _to(), _dist() {}
        constexpr _node(int to, T dist) : _to(to), _dist(dist) {}
        constexpr bool operator<(const _node &rhs) const {
            return this->dist() < rhs.dist();
        }
        constexpr bool operator>(const _node &rhs) const {
            return rhs < *this;
        }

        constexpr int to() const {
            return this->_to;
        }
        constexpr T dist() const {
            return this->_dist;
        }

      private:
        int _to;
        T _dist;
    };
    vector<std::vector<T>> dists(2, vector<T>(g.size(), {INF, -1}));
    std::priority_queue<_node, std::vector<_node>, std::greater<>> p_que;
    for (auto s : b) {
        dists[0][s] = T(0, a[s]);
        p_que.emplace(s, T(0, a[s]));
    }
    while (!p_que.empty()) {
        auto node = p_que.top();
        p_que.pop();
        if (dists[0][node.to()] != node.dist() && dists[1][node.to()] != node.dist())
            continue;
        for (auto &e : g[node.to()]) {
            if (dists[0][e.to()].second == node.dist().second) {
                if (chmin(dists[0][e.to()], node.dist() + e.weight())) {
                    p_que.emplace(e.to(), node.dist() + e.weight());
                }
            } else {
                if (chmin(dists[1][e.to()], node.dist() + e.weight())) {
                    if (dists[0][e.to()] > dists[1][e.to()])
                        swap(dists[0][e.to()], dists[1][e.to()]);
                    p_que.emplace(e.to(), node.dist() + e.weight());
                }
            }
        }
    }
    return dists;
}

int main(void) {
    sonic();
    int n, m, k, l;
    cin >> n >> m >> k >> l;
    vector<int> a(n), b(l);
    cin >> a >> b;
    rep(i, n) a[i]--;
    rep(i, l) b[i]--;
    Graph<ll> g(n);
    g.input_edges(m);

    auto ans = dijkstra(g, a, b);
    vector<ll> v;
    rep(i, n) {
        if (ans[0][i].second != a[i]) {
            v.emplace_back(ans[0][i].first == INF ? -1 : ans[0][i].first);
        } else {
            v.emplace_back(ans[1][i].first == INF ? -1 : ans[1][i].first);
        }
    }
    co(v);

    return 0;
}
