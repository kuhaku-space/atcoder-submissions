// clang-format off
#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ld = long double;
using Pi = pair<int, int>;
using Pl = pair<ll, ll>;
using Vi = vector<int>;
using Vl = vector<ll>;
#define FOR(i, m, n) for(ll i = (m); i < (n); ++i)
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

    ll bfs(int r) {
        vector<int> cnt(size());
        static vector<bool> is_visit(size());
        ll res = 1;
        queue<pair<int, int>> q;
        q.push({r, -1});
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            if (is_visit[x]) continue;
            is_visit[x] = true;
            if (cnt[x] >= 3) return 0;
            res *= 3 - cnt[x];
            for (auto i : edges[x]) {
                if (i.to == y) continue;
                ++cnt[i.to];
                q.push({i.to, x});
            }
        }
        return res;
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
    int n, m;
    cin >> n >> m;
    Graph<void> g(n);
    rep(i, m) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g.add_edges(a, b);
    }

    vector<int> id(n, -1), color(n, -1);
    int cnt = 0, f = 0;
    auto dfs = [&](auto self, int idx) -> void {
        if (id[idx] != -1)
            return;
        id[idx] = cnt++;
        for (auto i : g[idx]) self(self, i);
    };

    ll sum = 0;
    auto solve = [&](auto self, int idx) {
        if (idx == cnt) {
            ++sum;
            return;
        }
        int x = 0;
        rep(i, n) if (id[i] == idx) x = i;
        rep(c, 3) {
            bool flg = true;
            for (auto i : g[x]) {
                if (color[i] == c)
                    flg = false;
            }
            if (flg) {
                color[x] = c;
                self(self, idx + 1);
            }
        }
        color[x] = -1;
    };

    ll ans = 1;
    rep(i, n) {
        f = cnt;
        sum = 0;
        dfs(dfs, i);
        if (f == cnt)
            continue;
        solve(solve, f);
        ans *= sum;
    }
    co(ans);

    return 0;
}
