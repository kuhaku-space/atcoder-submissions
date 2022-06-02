#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ld = long double;
using P = pair<ll, ll>;
using Vec = vector<ll>;
using VecP = vector<P>;
template <class T>
using Vec2 = vector<vector<T>>;
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
constexpr int64_t INF = 1000000000000000001;
constexpr int64_t MOD = 1000000007;
constexpr int64_t MOD_N = 998244353;
constexpr long double EPS = 1e-11;
const double PI = acos(-1);

struct Tree {
    struct node {
        int64_t to, cost;
    };
    int64_t V;
    vector<vector<node>> data;
    vector<int64_t> depth;
    vector<int64_t> parent;

    Tree(int64_t v) : V(v) {
        data = vector<vector<node>>(V);
        depth = vector<int64_t>(V);
        parent = vector<int64_t>(V);
    }

    void init(int64_t r) {
        struct _node {
            int64_t v, p, d;
        };
        stack<_node> st;
        st.push(_node{r, -1, 0});
        while (!st.empty()) {
            auto [v, p, d] = st.top();
            st.pop();
            depth[v] = d;
            parent[v] = p;
            for (auto [to, cost] : data[v]) {
                if (to == p) continue;
                st.push(_node{to, v, d + 1});
            }
        }
    }

    void build(int64_t r = 0) { init(r); }

    void add_edge(int64_t a, int64_t b, int64_t c) {
        data[a].emplace_back(node{b, c});
        data[b].emplace_back(node{a, c});
    }

    template <class F>
    void dfs(int64_t v, int64_t p, int64_t x, const F &f) {
        f(x);
        for (auto [to, cost] : data[v]) {
            if (to == p) continue;
            dfs(to, v, x ^ cost, f);
        }
    }
};

int main(void) {
    ll n, x;
    cin >> n >> x;

    Tree tree(n);
    rep(i, n - 1) {
        ll a, b, c;
        cin >> a >> b >> c;
        --a, --b;
        tree.add_edge(a, b, c);
    }

    unordered_map<ll, ll> mp;
    ll ans = 0;
    auto f = [&](ll a) {
        ans += mp[x ^ a];
        mp[a]++;
    };
    tree.dfs(0, -1, 0, f);
    co(ans);

    return 0;
}