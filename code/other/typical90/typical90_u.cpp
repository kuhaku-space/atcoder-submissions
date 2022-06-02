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

    vector<vector<edge>> edges;

    Graph(int v) : edges(v) {}

    const auto &operator[](int i) const { return edges[i]; }
    auto &operator[](int i) { return edges[i]; }
    const auto begin() const { return edges.begin(); }
    auto begin() { return edges.begin(); }
    const auto end() const { return edges.end(); }
    auto end() { return edges.end(); }
    auto size() const { return edges.size(); }
    void add_edge(int a, int b, T d = T(1)) {
        edges[a].emplace_back(edge{a, b, d});
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
    vector<bool> used(n);

    for (auto &es : g) {
        for (auto &e : es) rg.add_edge(e.to, e.from);
    }

    auto dfs = [&](auto self, int idx) {
        if (used[idx]) return;
        used[idx] = true;
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

// clang-format on

int main(void) {
    int n, m;
    cin >> n >> m;
    Graph<int> g(n);
    rep(i, m) {
        int a,b;
        cin >> a >> b;
        --a, --b;
        g.add_edge(a, b);
    }

    auto v = scc(g);
    Vi cnt(n);
    rep(i, n) cnt[v[i]]++;

    ll ans = 0;
    rep(i, n) {
        if (cnt[i]) ans += (ll)cnt[i] * (cnt[i] - 1) / 2;
    }
    co(ans);

    return 0;
}
