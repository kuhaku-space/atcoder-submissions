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
istream &operator>>(istream &is, vector<T> &v) { for (T &i : v) is >> i; return is; }
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) { for (const T &i : v) os << i << ' '; return os; }
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
// clang-format on

struct Tree {
    int V;
    vector<vector<int>> data;
    vector<int> depth;
    vector<int> parent;

    Tree(int v) : V(v), data(v), depth(v), parent(v) {}

    void init(int r = 0) {
        struct node {
            int v, p, d;
        };
        stack<node> st;
        st.push(node{r, -1, 0});
        while (!st.empty()) {
            auto [v, p, d] = st.top();
            st.pop();
            depth[v] = d;
            parent[v] = p;
            for (auto i : data[v]) {
                if (i == p) continue;
                st.push(node{i, v, d + 1});
            }
        }
    }

    void build(int r = 0) { init(r); }

    void add_edge(int a, int b) {
        data[a].emplace_back(b);
        data[b].emplace_back(a);
    }

    void bfs(int s) {
        struct node {
            int v, p;
        };
        stack<node> st;
        st.push(node{s, -1});
        while (!st.empty()) {
            auto [v, p] = st.top();
            st.pop();
            parent[v] = p;
            for (auto i : data[v]) {
                if (i == p) continue;
                st.push(node{i, v});
            }
        }
    }

    Pi dfs(int v, int p, int m) {
        int s = 0, mi = 0, ma = 0;
        for (auto i : data[v]) {
            if (i == p) continue;
            auto q = dfs(i, v, m);
            s += q.first;
            chmin(mi, q.second);
            chmax(ma, q.second);
        }

        if (-mi < ma)
            return {s, ma - 1};
        if (-mi >= m)
            return {s + 1, m};
        return {s, mi - 1};
    }
};

int main(void) {
    int n, k;
    cin >> n >> k;
    Tree tree(n);
    rep(i, n - 1) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        tree.add_edge(u, v);
    }

    tree.build();

    int l = 0, r = n;
    while (r - l > 1) {
        int m = (l + r) / 2;
        auto p = tree.dfs(0, 0, m);
        if (p.second < 0)
            p.first++;
        if (p.first <= k)
            r = m;
        else
            l = m;
    }
    co(r);

    return 0;
}
