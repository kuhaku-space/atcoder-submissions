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

struct Tree {
    int64_t V, logV;
    vector<vector<int64_t>> data;
    vector<int64_t> depth;
    vector<vector<int64_t>> parent;

    Tree(int64_t v) : V(v), logV(0) {
        while (V > (1LL << logV)) ++logV;
        data = vector<vector<int64_t>>(V);
        depth = vector<int64_t>(V);
        parent = vector<vector<int64_t>>(logV, vector<int64_t>(V));
    }

    void init(int64_t r) {
        struct node {
            int64_t v, p, d;
        };
        stack<node> st;
        st.push(node{r, -1, 0});
        while (!st.empty()) {
            auto [v, p, d] = st.top();
            st.pop();
            depth[v] = d;
            parent[0][v] = p;
            for (auto i : data[v]) {
                if (i == p) continue;
                st.push(node{i, v, d + 1});
            }
        }
    }

    void build(int64_t r = 0) {
        init(r);
        for (int64_t k = 0; k < logV - 1; ++k) {
            for (int64_t v = 0; v < V; ++v) {
                if (parent[k][v] < 0)
                    parent[k + 1][v] = -1;
                else
                    parent[k + 1][v] = parent[k][parent[k][v]];
            }
        }
    }

    void add_edge(int64_t a, int64_t b) {
        data[a].emplace_back(b);
        data[b].emplace_back(a);
    }

    int64_t lca(int64_t u, int64_t v) {
        if (depth[u] > depth[v]) swap(u, v);
        for (int64_t k = 0; k < logV; ++k) {
            if ((depth[v] - depth[u]) >> k & 1) v = parent[k][v];
        }
        if (u == v) return u;

        for (int64_t k = logV - 1; k >= 0; --k) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }

    int64_t get_depth(int64_t a) { return depth[a]; }
    int64_t get_parent(int64_t a) { return parent[0][a]; }

    int64_t get_ancestor(int64_t a, int64_t d) {
        for (int64_t k = 0; d; d >>= 1, ++k) {
            if (d & 1) a = parent[k][a];
        }
        return a;
    }
};

// clang-format on

int main(void) {
    int n, q;
    cin >> n >> q;
    Tree tree(n);
    rep(i, n - 1) {
        int a, b;
        cin >> a >> b;
        tree.add_edge(a - 1, b - 1);
    }

    tree.build();

    rep(i, q) {
        int c, d;
        cin >> c >> d;
        --c, --d;
        int dist = tree.get_depth(c) + tree.get_depth(d) - 2 * tree.lca(c, d);
        if (dist & 1)
            puts("Road");
        else
            puts("Town");
    }

    return 0;
}
