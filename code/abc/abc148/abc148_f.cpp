// clang-format off
#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ld = long double;
using Pi = pair<int, int>;
using Pl = pair<ll, ll>;
using Vi = vector<int>;
using Vl = vector<ll>;
#define FOR(i, m, n) for(int i = (m); i < (n); ++i)
#define FORR(i, m, n) for(int i = (m)-1; i >= (n); --i)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FOR(i, 1, n+1)
#define repr(i, n) FORR(i, n, 0)
#define repnr(i, n) FORR(i, n+1, 1)
#define all(s) (s).begin(), (s).end()
template <class T, class U>
bool chmax(T &a, const U b) { return a < b ? a = b, true : false; }
template <class T, class U>
bool chmin(T &a, const U b) { return b < a ? a = b, true : false; }
template <class T>
istream &operator>>(istream &is, vector<T> &v) { for (T &i : v) is>>i; return is; }
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    for (auto it=v.begin(); it!=v.end(); ++it) os<<(it==v.begin()?"":" ")<<*it; return os;
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
constexpr int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
const double PI = acos(-1);

template <class T>
struct Graph {
    struct edge {
        int from, to;
        T dist;

        bool operator<(const edge &rhs) const { return dist < rhs.dist; }
        bool operator>(const edge &rhs) const { return rhs < *this; }
    };

    int V;
    vector<vector<edge>> edges;

    Graph(int v) : V(v), edges(v) {}

    const auto &operator[](int i) const { return edges[i]; }
    auto &operator[](int i) { return edges[i]; }
    const auto begin() const { return edges.begin(); }
    auto begin() { return edges.begin(); }
    const auto end() const { return edges.end(); }
    auto end() { return edges.end(); }

    int size() const { return V; }

    void add_edge(int a, int b, T d = T(1)) {
        edges[a].push_back(edge{a, b, d});
    }
    void add_edges(int a, int b, T d = T(1)) {
        edges[a].push_back(edge{a, b, d});
        edges[b].push_back(edge{b, a, d});
    }
};

template <class T>
struct radix_heap {
    vector<T> v[33];
    T last;
    unsigned int sz;
    bool is_top;

    radix_heap() : last(), sz(), is_top() {}

    int bsr(unsigned int x) {
        if (x == 0) return -1;
        return 31-__builtin_clz(x);
    }

    bool empty() const {
        return sz == 0;
    }

    auto size() const {
        return sz;
    }

    void push(T x) {
        assert(x.dist >= last.dist);
        ++sz;
        v[bsr(x.dist ^ last.dist) + 1].emplace_back(x);
    }

    auto top() {
        if (!is_top) pop();
        is_top = true;
        return last;
    }

    void pop() {
        if (is_top) {
            is_top = false;
            return;
        }
        assert(sz);
        if (!v[0].size()) {
            int i = 1;
            while (!v[i].size()) ++i;
            auto new_last = *min_element(v[i].begin(), v[i].end());
            for (auto x : v[i]) {
                v[bsr(x.dist ^ new_last.dist) + 1].emplace_back(x);
            }
            v[i].clear();
        }
        --sz;
        last = v[0].back();
        v[0].pop_back();
    }
};

template <class T>
vector<T> dijkstra(const Graph<T> &g, int s = 0,
                   T inf = numeric_limits<T>::max()) {
    struct _edge {
        int to;
        T dist;
        bool operator<(const _edge &rhs) const { return dist < rhs.dist; }
        bool operator>(const _edge &rhs) const { return rhs < *this; }
    };
    vector<T> dist(g.size(), inf);
    priority_queue<_edge, vector<_edge>, greater<_edge>> p_que;
    p_que.push(_edge{s, T()});
    while (!p_que.empty()) {
        _edge e = p_que.top();
        p_que.pop();
        if (chmin(dist[e.to], e.dist))
            for (auto &i : g[e.to]) p_que.push(_edge{i.to, e.dist + i.dist});
    }
    return dist;
}

template <class T>
vector<T> dijkstra_fast(const Graph<T> &g, int s = 0,
                        T inf = numeric_limits<T>::max()) {
    struct _edge {
        int to;
        T dist;
        bool operator<(const _edge &rhs) const { return dist < rhs.dist; }
        bool operator>(const _edge &rhs) const { return rhs < *this; }
    };
    vector<T> dist(g.size(), inf);
    priority_queue<_edge, vector<_edge>, greater<_edge>> p_que;
    dist[s] = T();
    p_que.push(_edge{s, T()});
    while (!p_que.empty()) {
        _edge e = p_que.top();
        p_que.pop();
        if (dist[e.to] < e.dist) continue;
        for (auto &i : g[e.to]) {
            if (chmin(dist[i.to], e.dist + i.dist))
                p_que.push(_edge{i.to, e.dist + i.dist});
        }
    }
    return dist;
}
/*
template <class T>
vector<T> dijkstra_fast(const Graph<T> &g, int s = 0,
                        T inf = numeric_limits<T>::max()) {
    struct _edge {
        int to;
        T dist;
        bool operator<(const _edge &rhs) const { return dist < rhs.dist; }
        bool operator>(const _edge &rhs) const { return rhs < *this; }
    };
    vector<T> dist(g.size(), inf);
    radix_heap<_edge> p_que;
    dist[s] = T();
    p_que.push(_edge{s, T()});
    while (!p_que.empty()) {
        _edge e = p_que.top();
        p_que.pop();
        if (dist[e.to] < e.dist) continue;
        for (auto &i : g.edges[e.to]) {
            if (chmin(dist[i.to], e.dist + i.dist))
                p_que.push(_edge{i.to, e.dist + i.dist});
        }
    }
    return dist;
}
*/
// clang-format on

int main(void) {
    int n;
    cin >> n;
    int u, v;
    cin >> u >> v;
    --u, --v;

    Graph<int> g(n);

    rep(i, n - 1) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g.add_edges(a, b);
    }

    auto d = dijkstra(g, u);
    auto e = dijkstra(g, v);
    rep(i, n) d[i] -= e[i];
    int ans = 0;
    rep(i, n) {
        if (d[i] < 0)
            chmax(ans, e[i] - 1);
    }
    co(ans);

    return 0;
}
