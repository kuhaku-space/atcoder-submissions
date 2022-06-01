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


int chromatic_number(const Graph<int> &G) {
    constexpr int64_t _MOD = (1LL << 31) - 1;
    int n = G.size();
    vector<int> neighbor(n, 0);
    for (int i = 0; i < n; ++i) {
        int s = 1 << i;
        for (auto &e : G[i]) s |= 1 << e.to;
        neighbor[i] = s;
    }
    
    vector<int> v(1 << n);
    v[0] = 1;
    for (int s = 1; s < 1 << n; ++s) {
        int c = __builtin_ctz(s);
        v[s] = v[s & ~(1 << c)] + v[s & ~neighbor[c]];
    }

    auto _mod = [](auto self, int64_t a) -> int64_t {
        a = (a & _MOD) + (a >> 31);
        return a >= _MOD ? a - _MOD : a;
    };
    auto _pow = [](auto f, int64_t a, int n) {
        int64_t res = 1;
        for (; n > 0; n >>= 1) {
            if (n & 1)
                res = f(f, res * a);
            a = f(f, a * a);
        }
        return res;
    };

    int low = 0, high = n;
    while (high - low > 1) {
        int mid = (low + high) >> 1;
        int64_t g = 0;
        for (int s = 0; s < 1 << n; ++s) {
            if ((n - __builtin_popcount(s)) & 1) g = _mod(_mod, g + _MOD - _pow(_mod, v[s], mid));
            else g = _mod(_mod, g + _pow(_mod, v[s], mid));
        }
        if (g != 0) high = mid;
        else low = mid;
    }
    return high;
}

int main(void) {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> e(n, vector<int>(n, 1));
    rep(i, m) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        e[a][b] = 0;
        e[b][a] = 0;
    }
    rep(i, n) e[i][i] = 0;

    Graph<int> g(n);
    rep(i, n) {
        rep(j, n) if (e[i][j]) g.add_edge(i, j);
    }

    co(chromatic_number(g));

    return 0;
}
