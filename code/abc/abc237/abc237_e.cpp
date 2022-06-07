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

template <class T>
struct Graph {
    struct edge {
        int from, to;
        T dist;
        constexpr edge() : from(), to(), dist() {}
        constexpr edge(int _from, int _to, T _dist) : from(_from), to(_to), dist(_dist) {}
        bool operator<(const edge &rhs) const { return this->dist < rhs.dist; }
        bool operator>(const edge &rhs) const { return rhs < *this; }
    };
    std::vector<std::vector<edge>> edges;

    Graph(int v) : edges(v) {}

    const auto &operator[](int i) const { return this->edges[i]; }
    auto &operator[](int i) { return this->edges[i]; }
    const auto begin() const { return this->edges.begin(); }
    auto begin() { return this->edges.begin(); }
    const auto end() const { return this->edges.end(); }
    auto end() { return this->edges.end(); }
    auto size() const { return this->edges.size(); }
    void add_edge(int a, int b, T d = T(1)) { this->edges[a].emplace_back(a, b, d); }
    void add_edges(int a, int b, T d = T(1)) {
        this->edges[a].emplace_back(a, b, d);
        this->edges[b].emplace_back(b, a, d);
    }
    void input_edge(int m, bool zero_based = false) {
        for (int i = 0; i < m; ++i) {
            int a, b;
            T d;
            cin >> a >> b >> d;
            if (zero_based)
                this->add_edge(a, b, d);
            else
                this->add_edge(a - 1, b - 1, d);
        }
    }
    void input_edges(int m, bool zero_based = false) {
        for (int i = 0; i < m; ++i) {
            int a, b;
            T d;
            cin >> a >> b >> d;
            if (zero_based)
                this->add_edges(a, b, d);
            else
                this->add_edges(a - 1, b - 1, d);
        }
    }
};

template <>
struct Graph<void> {
    std::vector<std::vector<int>> edges;

    Graph(int v) : edges(v) {}

    const auto &operator[](int i) const { return this->edges[i]; }
    auto &operator[](int i) { return this->edges[i]; }
    const auto begin() const { return this->edges.begin(); }
    auto begin() { return this->edges.begin(); }
    const auto end() const { return this->edges.end(); }
    auto end() { return this->edges.end(); }
    auto size() const { return this->edges.size(); }
    void add_edge(int a, int b) { this->edges[a].emplace_back(b); }
    void add_edges(int a, int b) {
        this->edges[a].emplace_back(b);
        this->edges[b].emplace_back(a);
    }
    void input_edge(int m, bool zero_based = false) {
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            if (zero_based)
                this->add_edge(a, b);
            else
                this->add_edge(a - 1, b - 1);
        }
    }
    void input_edges(int m, bool zero_based = false) {
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            if (zero_based)
                this->add_edges(a, b);
            else
                this->add_edges(a - 1, b - 1);
        }
    }
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
#line 3 "/home/kuhaku/atcoder/github/atcoder-lib/lib/graph/dijkstra_potential.hpp"

template <class T, class U>
std::vector<T> dijkstra(const Graph<T> &graph, const vector<U> &potential, int s = 0,
                        T inf = std::numeric_limits<T>::max()) {
    struct _edge {
        int to;
        T dist;
        constexpr _edge() : to(), dist() {}
        constexpr _edge(int _to, T _dist) : to(_to), dist(_dist) {}
        bool operator<(const _edge &rhs) const { return this->dist < rhs.dist; }
        bool operator>(const _edge &rhs) const { return rhs < *this; }
    };
    int n = graph.size();
    std::vector<T> dists(n, inf);
    std::priority_queue<_edge, std::vector<_edge>, std::greater<_edge>> p_que;
    dists[s] = T();
    p_que.emplace(s, T());
    while (!p_que.empty()) {
        auto e = p_que.top();
        p_que.pop();
        if (dists[e.to] < e.dist) continue;
        for (auto &i : graph[e.to]) {
            if (chmin(dists[i.to], e.dist + i.dist + potential[e.to] - potential[i.to]))
                p_que.emplace(i.to, e.dist + i.dist + potential[e.to] - potential[i.to]);
        }
    }
    for (int i = 0; i < n; ++i) { dists[i] += potential[i] - potential[s]; }
    return dists;
}
#line 5 "a.cpp"

int main(void) {
    sonic();
    int n, m;
    cin >> n >> m;
    vector<int> h(n);
    cin >> h;
    Graph<ll> g(n);
    rep(i, m) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        if (h[x] == h[y]) {
            g.add_edge(x, y, 0);
            g.add_edge(y, x, 0);
        } else if (h[x] > h[y]) {
            g.add_edge(x, y, h[y] - h[x]);
            g.add_edge(y, x, 2 * (h[x] - h[y]));
        } else {
            g.add_edge(x, y, 2 * (h[y] - h[x]));
            g.add_edge(y, x, h[x] - h[y]);
        }
    }

    auto dist = dijkstra(g, h);
    co(-(*min_element(all(dist))));

    return 0;
}
