// clang-format off
#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ld = long double;
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

template <>
struct Graph<void> {
    vector<vector<int>> edges;

    Graph(int v) : edges(v) {}

    const auto &operator[](int i) const { return edges[i]; }
    auto &operator[](int i) { return edges[i]; }
    const auto begin() const { return edges.begin(); }
    auto begin() { return edges.begin(); }
    const auto end() const { return edges.end(); }
    auto end() { return edges.end(); }
    auto size() const { return edges.size(); }
    void add_edge(int a, int b) { edges[a].emplace_back(b); }
    void add_edges(int a, int b) {
        edges[a].emplace_back(b);
        edges[b].emplace_back(a);
    }
};

// clang-format on

int main(void) {
    int n;
    cin >> n;
    Graph<void> g(n);
    rep(i, n - 1) {
        int a, b;
        cin >> a >> b;
        g.add_edges(a - 1, b - 1);
    }

    int k;
    cin >> k;
    vector<int> ans(n, -1);
    rep(i, k) {
        int v, p;
        cin >> v >> p;
        ans[v - 1] = p;
    }
    vector<int> color(n);

    auto coloring = [&](auto self, int idx, int par) -> void {
        if (par == -1)
            color[idx] = 0;
        else
            color[idx] = !color[par];
        for (auto i : g[idx]) {
            if (i == par)
                continue;
            self(self, i, idx);
        }
    };

    coloring(coloring, 0, -1);

    vector<int> a, b;
    rep(i, n) {
        if (color[i] == 0 && ans[i] != -1)
            a.emplace_back(ans[i]);
        else if (color[i] == 1 && ans[i] != -1)
            b.emplace_back(ans[i]);
    }

    int r = 0;
    if (a.size()) {
        r = a[0] % 2;
    } else if (b.size()) {
        r = (b[0] + 1) % 2;
    }

    for (auto i : a) {
        if (r != i % 2) {
            puts("No");
            return 0;
        }
    }
    for (auto i : b) {
        if (r == i % 2) {
            puts("No");
            return 0;
        }
    }

    vector<int> ls(n, -Inf), rs(n, Inf);

    auto dfs = [&](auto self, int idx, int par, int l, int r) -> pair<int, int> {
        if (ans[idx] != -1) {
            chmax(l, ans[idx]);
            chmin(r, ans[idx]);
        }
        chmax(ls[idx], l);
        chmin(rs[idx], r);
        l = ls[idx];
        r = rs[idx];

        for (auto i : g[idx]) {
            if (i == par)
                continue;
            auto [x, y] = self(self, i, idx, l - 1, r + 1);
            chmax(ls[idx], x);
            chmin(rs[idx], y);
        }

        return {ls[idx] - 1, rs[idx] + 1};
    };

    dfs(dfs, 0, -1, -Inf, Inf);
    dfs(dfs, 0, -1, ls[0], rs[0]);

        rep(i, n) {
        if (ls[i] > rs[i]) {
            puts("No");
            return 0;
        }
    }

    puts("Yes");
    for (auto i : ls)
        co(i);

    return 0;
}
