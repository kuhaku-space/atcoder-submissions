#line 1 "a.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_A"
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
#line 3 "/home/kuhaku/atcoder/github/atcoder-lib/lib/graph/dijkstra.hpp"

/**
 * @brief ダイクストラ法
 *
 * @tparam T
 * @param g グラフ
 * @param s 始点
 * @param inf
 * @return vector<T>
 */
template <class T>
std::vector<T> dijkstra(const Graph<T> &g, int s = 0, T inf = std::numeric_limits<T>::max()) {
    struct _edge {
        int to;
        T dist;
        constexpr _edge() : to(), dist() {}
        constexpr _edge(int _to, T _dist) : to(_to), dist(_dist) {}
        bool operator<(const _edge &rhs) const { return this->dist < rhs.dist; }
        bool operator>(const _edge &rhs) const { return rhs < *this; }
    };
    std::vector<T> dist(g.size(), inf);
    std::priority_queue<_edge, std::vector<_edge>, std::greater<_edge>> p_que;
    dist[s] = T();
    p_que.emplace(s, T());
    while (!p_que.empty()) {
        _edge e = p_que.top();
        p_que.pop();
        if (dist[e.to] < e.dist) continue;
        for (auto &i : g[e.to]) {
            if (chmin(dist[i.to], e.dist + i.dist)) p_que.emplace(i.to, e.dist + i.dist);
        }
    }
    return dist;
}
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
#line 5 "a.cpp"

template <class T, class U>
struct heap {
    int _size;
    vector<pair<int, U>> v;
    vector<int> u;

    heap(int n) : _size(), v(n + 1), u(n) {}

    T top() const {
        return T(v[1].first, v[1].second);
    }
    int size() const {
        return _size;
    }
    bool empty() const {
        return _size == 0;
    }

    void push(int a, U b) {
        if (u[a]) {
            update(a, b);
            return;
        }
        ++_size;
        v[_size] = make_pair(a, b);
        u[a] = _size;

        int idx = _size;
        while (idx > 1 && v[idx].second < v[idx >> 1].second) {
            swap(u[a], u[v[idx >> 1].first]);
            swap(v[idx], v[idx >> 1]);
            idx >>= 1;
        }
    }
    void emplace(int a, U b) {
        push(a, b);
    }

    void pop() {
        u[v[_size].first] = 1;
        v[1] = v[_size];
        --_size;

        int idx = 1;
        while (idx * 2 <= _size) {
            int k = (idx * 2 == _size
                         ? idx * 2
                         : (v[idx * 2].second < v[idx * 2 + 1].second ? idx * 2 : idx * 2 + 1));
            if (v[idx].second < v[k].second)
                break;
            swap(u[v[idx].first], u[v[k].first]);
            swap(v[idx], v[k]);
            idx = k;
        }
    }

    void update(int a, U b) {
        if (v[u[a]].second <= b)
            return;
        v[u[a]].second = b;
        int idx = u[a];
        while (idx > 1 && v[idx].second < v[idx >> 1].second) {
            swap(u[a], u[v[idx >> 1].first]);
            swap(v[idx], v[idx >> 1]);
            idx >>= 1;
        }
    }
};

/*
template <class T>
std::vector<T> dijkstra(const Graph<T> &g, int s = 0, T inf = std::numeric_limits<T>::max()) {
    struct _edge {
        int to;
        T dist;
        constexpr _edge() : to(), dist() {}
        constexpr _edge(int _to, T _dist) : to(_to), dist(_dist) {}
        bool operator<(const _edge &rhs) const {
            return this->dist < rhs.dist;
        }
        bool operator>(const _edge &rhs) const {
            return rhs < *this;
        }
    };
    std::vector<T> dist(g.size(), inf);
    heap<_edge, T> p_que(g.size());
    dist[s] = T();
    p_que.emplace(s, T());
    while (!p_que.empty()) {
        _edge e = p_que.top();
        p_que.pop();
        if (dist[e.to] < e.dist)
            continue;
        for (auto &i : g[e.to]) {
            if (chmin(dist[i.to], e.dist + i.dist))
                p_que.emplace(i.to, e.dist + i.dist);
        }
    }
    return dist;
}*/

struct S {
    ll t, k;

    S &operator+=(const S &rhs) {
        t += rhs.k - 1 - (rhs.k + t - 1) % rhs.k;
        t += rhs.t;
        return *this;
    }
    S operator+(const S &rhs) const {
        return S(*this) += rhs;
    }

    bool operator<(const S &rhs) const {
        return t < rhs.t;
    }
    bool operator>(const S &rhs) const {
        return rhs < *this;
    }
    bool operator<=(const S &rhs) const {
        return !(rhs < *this);
    }
    bool operator>=(const S &rhs) const {
        return !(*this < rhs);
    }
};

int main(void) {
    sonic();
    int n, m, x, y;
    cin >> n >> m >> x >> y;
    --x, --y;
    Graph<S> g(n);

    rep(i, m) {
        int a, b, t, k;
        cin >> a >> b >> t >> k;
        --a, --b;
        g.add_edges(a, b, S{t, k});
    }

    auto ans = dijkstra(g, x, S{INF, 0});
    if (ans[y].t == INF)
        ans[y].t = -1;
    co(ans[y].t);

    return 0;
}
