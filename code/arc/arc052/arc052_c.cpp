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

        bool operator<(const edge &rhs) const { return this->dist < rhs.dist; }
        bool operator>(const edge &rhs) const { return rhs < *this; }
    };
    vector<vector<edge>> edges;

    Graph(int v) : edges(v) {}

    const auto &operator[](int i) const { return this->edges[i]; }
    auto &operator[](int i) { return this->edges[i]; }
    const auto begin() const { return this->edges.begin(); }
    auto begin() { return this->edges.begin(); }
    const auto end() const { return this->edges.end(); }
    auto end() { return this->edges.end(); }
    auto size() const { return this->edges.size(); }
    void add_edge(int a, int b, T d = T(1)) { this->edges[a].emplace_back(edge{a, b, d}); }
    void add_edges(int a, int b, T d = T(1)) {
        this->edges[a].emplace_back(edge{a, b, d});
        this->edges[b].emplace_back(edge{b, a, d});
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
    vector<vector<int>> edges;

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
#define FOR(i, m, n) for(int i = (m); i < (n); ++i)
#define FORR(i, m, n) for(int i = (m)-1; i >= (n); --i)
#define FORL(i, m, n) for(ll i = (m); i < (n); ++i)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FOR(i, 1, n+1)
#define repr(i, n) FORR(i, n, 0)
#define repnr(i, n) FORR(i, n+1, 1)
#define all(s) (s).begin(), (s).end()
template<class T, class U>
istream &operator>>(istream &is, pair<T, U> &p) { is >> p.first >> p.second; return is; }
template <class T>
istream &operator>>(istream &is, vector<T> &v) { for (T &i : v) is>>i; return is; }
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    for (auto it=v.begin(); it!=v.end(); ++it) { os<<(it==v.begin()?"":" ")<<*it; } return os;
}
template <class Head, class... Tail>
void co(Head&& head, Tail&&... tail) {
    if constexpr(sizeof...(tail)==0) cout<<head<<'\n'; else cout<<head<<' ',co(forward<Tail>(tail)...);
}
template <class Head, class... Tail>
void ce(Head&& head, Tail&&... tail) {
    if constexpr(sizeof...(tail)==0) cerr<<head<<'\n'; else cerr<<head<<' ',ce(forward<Tail>(tail)...);
}
template<typename T, typename... Args>
auto make_vector(T x, int arg, Args ...args) {
    if constexpr(sizeof...(args)==0) return vector<T>(arg, x); else return vector(arg,make_vector<T>(x, args...));
}
void sonic() { ios::sync_with_stdio(false); cin.tie(nullptr); }
void setp(const int n) { cout << fixed << setprecision(n); }
#line 4 "a.cpp"

template <class T>
vector<unordered_map<int, T>> dijkstra(const Graph<T> &g, int s = 0,
                                       T inf = numeric_limits<T>::max()) {
    struct _edge {
        int to;
        T dist;
        bool operator<(const _edge &rhs) const {
            return dist < rhs.dist;
        }
        bool operator>(const _edge &rhs) const {
            return rhs < *this;
        }
    };

    vector<int> m(g.size(), Inf);
    vector<unordered_map<int, T>> dist(g.size());
    priority_queue<_edge, vector<_edge>, greater<_edge>> p_que;
    dist[s][0] = T();
    p_que.push(_edge{s, T()});
    while (!p_que.empty()) {
        _edge e = p_que.top();
        p_que.pop();
        if (dist[e.to].count(e.dist.first) && dist[e.to][e.dist.first] < e.dist)
            continue;
        for (auto &i : g[e.to]) {
            auto p = make_pair(e.dist.first + i.dist.first, e.dist.second + i.dist.second);
            if (m[i.to] + 150 < p.first)
                continue;
            chmin(m[i.to], p.first);
            if (!dist[i.to].count(p.first))
                dist[i.to][p.first] = inf;
            if (chmin(dist[i.to][p.first], p))
                p_que.push(_edge{i.to, p});
        }
    }
    return dist;
}

int main(void) {
    sonic();
    int n, m;
    cin >> n >> m;
    Graph<pair<int, int>> g(n);
    rep(i, m) {
        int a, b, c;
        cin >> a >> b >> c;
        if (!a)
            g.add_edges(b, c, make_pair(0, 1));
        else
            g.add_edges(b, c, make_pair(1, 0));
    }

    auto dist = dijkstra(g, 0, make_pair(Inf, Inf));
    rep(i, n) {
        ll ans = INF;
        for (auto q : dist[i]) {
            auto p = q.second;
            chmin(ans, (ll)p.first * (p.first + 1) / 2 + p.second);
        }
        co(ans);
    }

    return 0;
}
