#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ld = long double;
using P = pair<ll, ll>;
using Vi = vector<int>;
using Vl = vector<ll>;
using Vp = vector<P>;
template <class T>
using Vv = vector<vector<T>>;
#define REP(i, m, n) for(ll i = (m); i < (n); ++i)
#define REPN(i, m, n) for(ll i = (m); i <= (n); ++i)
#define REPR(i, m, n) for(ll i = (m)-1; i >= (n); --i)
#define REPNR(i, m, n) for(ll i = (m); i >= (n); --i)
#define rep(i, n) REP(i, 0, n)
#define repn(i, n) REPN(i, 1, n)
#define repr(i, n) REPR(i, n, 0)
#define repnr(i, n) REPNR(i, n, 1)
#define all(s) (s).begin(), (s).end()
template <class T1, class T2>
bool chmax(T1 &a, const T2 b) { return a < b ? a = b, true : false; }
template <class T1, class T2>
bool chmin(T1 &a, const T2 b) { return a > b ? a = b, true : false; }
template <class T>
istream &operator>>(istream &is, vector<T> &v) { for (T &i : v) is >> i; return is; }
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) { for (const T &i : v) os << i << ' '; return os; }
void _co() { cout << '\n'; }
template <class Head, class... Tail>
void _co(Head&& head, Tail&&... tail) { cout << ' ' << head; _co(forward<Tail>(tail)...); }
template <class Head, class... Tail>
void co(Head&& head, Tail&&... tail) { cout << head; _co(forward<Tail>(tail)...); }
void ce() { cerr << '\n'; }
template <class Head, class... Tail>
void ce(Head&& head, Tail&&... tail) { cerr << head << ' '; ce(forward<Tail>(tail)...); }
void sonic() { ios::sync_with_stdio(false); cin.tie(nullptr); }
void setp(const int n) { cout << fixed << setprecision(n); }
constexpr int64_t INF = 1000000000000000003;
constexpr int64_t MOD = 1000000007;
constexpr int64_t MOD_N = 998244353;
constexpr long double EPS = 1e-11;
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

    Graph(int v) : V(v) { edges = vector<vector<edge>>(V); }

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
vector<int> scc(const Graph<T> &g) {
    int n = g.size();
    Graph<T> rg(n);
    vector<int> comp(n, -1), order;
    bitset<1 << 20> used;

    for (auto &es : g) {
        for (auto &e : es) rg.add_edge(e.to, e.from);
    }

    auto dfs = [&](auto self, int idx) {
        if (used[idx]) return;
        used.set(idx);
        for (auto &e : g[idx]) self(self, e.to);
        order.emplace_back(idx);
    };
    auto rdfs = [&](auto self, int idx, int cnt) {
        if (~comp[idx]) return;
        comp[idx] = cnt;
        for (auto &e : rg[idx]) self(self, e.to, cnt);
    };

    for (int i = 0; i < n; i++) dfs(dfs, i);
    reverse(order.begin(), order.end());
    int ptr = 0;
    for (auto i : order) {
        if (comp[i] == -1) rdfs(rdfs, i, ptr++);
    }

    return comp;
};

struct two_sat {
    int n;
    Graph<int> G;

    two_sat(int _n) : n(_n), G(_n * 2) {}

    void add(int i, bool f, int j, bool g) {
        i <<= 1, j <<= 1;
        G.add_edge(i + (f ? 0 : 1), j + (g ? 1 : 0));
        G.add_edge(j + (g ? 0 : 1), i + (f ? 1 : 0));
    }

    vector<int> solve() {
        auto v = scc(G);
        return v;
    }

    bool is_satisfy(const vector<int> &v) {
        for (int i = 0; i < n; ++i) {
            if (v[i * 2] == v[i * 2 + 1])
                return false;
        }
        return true;
    }

    vector<bool> build(const vector<int> &v) {
        vector<bool> res(n);
        for (int i = 0; i < n; ++i) {
            res[i] = v[i * 2] < v[i * 2 + 1];
        }
        return res;
    }
};

int main(void) {
    int n, d;
    cin >> n >> d;
    Vi x(n), y(n);
    rep(i, n) cin >> x[i] >> y[i];

    two_sat ts(n);

    rep(i, n) {
        rep(j, n) {
            if (i == j)
                continue;
            if (abs(x[i] - x[j]) < d)
                ts.add(i, 0, j, 0);
            if (abs(x[i] - y[j]) < d)
                ts.add(i, 0, j, 1);
            if (abs(y[i] - x[j]) < d)
                ts.add(i, 1, j, 0);
            if (abs(y[i] - y[j]) < d)
                ts.add(i, 1, j, 1);
        }
    }

    auto v = ts.solve();
    if (!ts.is_satisfy(v)) {
        puts("No");
        return 0;
    }

    puts("Yes");
    auto ans = ts.build(v);
    rep(i, n) {
        co(ans[i] ? x[i] : y[i]);
    }

    return 0;
}
