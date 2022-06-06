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
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/data_structure/radix_heap.hpp"

struct radix_heap {
    vector<unsigned int> v[33];
    unsigned int last, sz;
    bool is_top;

    radix_heap() : last(), sz(), is_top() {}

    int bsr(unsigned int x) {
        if (x == 0) return -1;
        return 31 - __builtin_clz(x);
    }

    void push(unsigned int x) {
        assert(x >= last);
        ++sz;
        v[bsr(x ^ last) + 1].emplace_back(x);
    }

    unsigned int top() {
        if (is_top) pop();
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
                v[bsr(x ^ new_last) + 1].emplace_back(x);
            }
            last = new_last;
            v[i].clear();
        }
        --sz;
        v[0].pop_back();
    }
};

struct radix_heap_64 {
    vector<uint64_t> v[65];
    uint64_t last, sz;
    bool is_top;

    radix_heap_64() : last(), sz(), is_top() {}

    int bsr(uint64_t x) {
        if (x == 0) return -1;
        return 63 - __builtin_clz(x);
    }

    void push(uint64_t x) {
        assert(x >= last);
        ++sz;
        v[bsr(x ^ last) + 1].emplace_back(x);
    }

    uint64_t top() {
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
            for (auto x : v[i]) v[bsr(x ^ new_last) + 1].emplace_back(x);
            last = new_last;
            v[i].clear();
        }
        --sz;
        v[0].pop_back();
    }
};

template <class T>
struct radix_heap_dijkstra {
    vector<T> v[33];
    T last;
    unsigned int sz;
    bool is_top;

    radix_heap_dijkstra() : last(), sz(), is_top() {}

    int bsr(unsigned int x) {
        if (x == 0) return -1;
        return 31 - __builtin_clz(x);
    }

    bool empty() const { return sz == 0; }
    auto size() const { return sz; }

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
#line 4 "/home/kuhaku/atcoder/github/atcoder-lib/lib/graph/dijkstra.hpp"

/*
 * verify :
 * https://atcoder.jp/contests/abc192/tasks/abc192_e 21/02/24
 * https://atcoder.jp/contests/abc191/tasks/abc191_e 21/04/08
 * https://atcoder.jp/contests/abc190/tasks/abc190_e 21/04/08
 * https://atcoder.jp/contests/abc148/tasks/abc148_f 21/04/08
 */

template <class T>
vector<T> dijkstra(const Graph<T> &g, int s = 0, T inf = numeric_limits<T>::max()) {
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
            if (chmin(dist[i.to], e.dist + i.dist)) p_que.push(_edge{i.to, e.dist + i.dist});
        }
    }
    return dist;
}

template <class T>
vector<T> dijkstra_late(const Graph<T> &g, int s = 0, T inf = numeric_limits<T>::max()) {
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
vector<T> dijkstra_fast(const Graph<T> &g, int s = 0, T inf = numeric_limits<T>::max()) {
    struct _edge {
        int to;
        T dist;
        bool operator<(const _edge &rhs) const { return dist < rhs.dist; }
        bool operator>(const _edge &rhs) const { return rhs < *this; }
    };
    vector<T> dist(g.size(), inf);
    radix_heap_dijkstra<_edge> p_que;
    dist[s] = T();
    p_que.push(_edge{s, T()});
    while (!p_que.empty()) {
        _edge e = p_que.top();
        p_que.pop();
        if (dist[e.to] < e.dist) continue;
        for (auto &i : g[e.to]) {
            if (chmin(dist[i.to], e.dist + i.dist)) p_que.push(_edge{i.to, e.dist + i.dist});
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
#line 5 "a.cpp"

struct T {
    int len;
    int next;
    uint64_t c;

    T() : len(), next(), c() {}
    T(int _len) : len(_len), next(), c() {}
    T(int _len, int _next, uint64_t _c) : len(_len), next(_next), c(_c) {}
};

array<uint64_t, 13> arr;
vector<T> v;

struct S {
    int idx;
    char c;

    constexpr S() : idx(), c() {}
    constexpr S(int _idx) : idx(_idx), c() {}
    constexpr S(int _idx, char _c) : idx(_idx), c(_c) {}

    S operator+(const S& rhs) const {
        S res(*this);
        if (rhs.idx == -1) {
            if (v[res.idx].len % 13 == 0) {
                v.emplace_back(T{v[res.idx].len + 1, res.idx, rhs.c});
            } else {
                v.emplace_back(T{v[res.idx].len + 1, v[res.idx].next,
                                 v[res.idx].c + rhs.c * arr[v[res.idx].len % 13]});
            }
            res.idx = v.size() - 1;
        }
        return res;
    }

    bool operator<(const S& rhs) const {
        if (v[this->idx].len != v[rhs.idx].len)
            return v[this->idx].len < v[rhs.idx].len;
        int x = this->idx;
        int y = rhs.idx;
        while (x) {
            if (v[x].c != v[y].c)
                return v[x].c < v[y].c;
            x = v[x].next, y = v[y].next;
        }
        return false;
    }
};

int main(void) {
    sonic();
    string s;
    cin >> s;
    int n = s.size();
    Graph<S> g(n + 2);
    rep(i, n + 1) g.add_edge(i, i + 1, S{0});
    vector<int> p(26);
    rep(i, n) {
        int c = s[i] - 'a';
        g.add_edge(i + 1, p[c], S{-1, c});
        p[c] = i + 1;
    }
    rep(i, 26) g.add_edge(n + 1, p[i], S{-1, i});
    v.emplace_back(T());
    v.emplace_back(T(Inf));
    arr[0] = 1;
    rep(i, 12) arr[i + 1] = arr[i] * 26;
    auto dist = dijkstra(g, n + 1, S{1});
    int x = dist[0].idx;
    string ans;
    while (x) {
        int len = v[x].len % 13 ? v[x].len % 13 : 13;
        uint64_t c = v[x].c;
        string s;
        while (len) {
            s += char(c % 26 + 'a');
            c /= 26;
            --len;
        }
        reverse(all(s));
        ans += s;
        x = v[x].next;
    }
    co(ans);

    return 0;
}
