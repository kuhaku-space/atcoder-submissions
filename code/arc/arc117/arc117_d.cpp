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

vector<int> tree_dist(const Graph<void> &g, int r = 0) {
    struct S {
        int idx, p, d;
    };
    vector<int> res(g.size());
    stack<S> st;
    st.push({r, -1, 0});
    while (!st.empty()) {
        auto [idx, p, d] = st.top();
        st.pop();
        res[idx] = d;
        for (auto i : g[idx]) {
            if (i == p)
                continue;
            st.push({i, idx, d + 1});
        }
    }
    return res;
}

struct Tree {
    const Graph<void> g;
    vector<int> parent;

    Tree(const Graph<void> &_g) : g(_g), parent(_g.size()) {}

    void build(int r = 0) {
        struct node {
            int v, p, d;
        };
        stack<node> st;
        st.push(node{r, -1, 0});
        while (!st.empty()) {
            auto [v, p, d] = st.top();
            st.pop();
            parent[v] = p;
            for (auto i : g[v]) {
                if (i == p) continue;
                st.push(node{i, v, d + 1});
            }
        }
    }

    bool contain(int v, int p, int y) {
        static vector<bool> is_fin(g.size());
        static vector<bool> is_contain(g.size());
        if (is_fin[v]) return is_contain[v];
        bool res = v == y;
        for (auto i : g[v]) {
            if (i == p) continue;
            res |= contain(i, v, y);
        }
        is_fin[v] = true;
        return is_contain[v] = res;
    }

    int dfs(int v, int p, int cnt, int y, Vi &ans) {
        ans[v] = cnt;
        int last = -1;
        for (auto i : g[v]) {
            if (i == p) continue;
            if (contain(i, v, y)) {
                last = i;
                continue;
            }
            ++cnt;
            cnt = dfs(i, v, cnt, y, ans);
            ++cnt;
        }

        if (~last) {
            ++cnt;
            cnt = dfs(last, v, cnt, y, ans);
            ++cnt;
        }
        return cnt;
    }
};

// clang-format on

int main(void) {
    sonic();
    int n;
    cin >> n;
    Graph<void> g(n);
    rep(i, n - 1) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g.add_edges(a, b);
    }

    auto v = tree_dist(g);
    int x = max_element(all(v)) - v.begin();
    auto u = tree_dist(g, x);
    int y = max_element(all(u)) - u.begin();
    Tree tree(g);
    Vi ans(n);
    tree.dfs(x, -1, 1, y, ans);
    co(ans);

    return 0;
}
