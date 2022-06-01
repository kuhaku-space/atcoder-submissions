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
    int V;
    vector<vector<T>> m;

    Graph(int v) : V(v) { m = vector<vector<T>>(V, vector<T>(V)); }

    const auto &operator[](int i) const { return m[i]; }
    auto &operator[](int i) { return m[i]; }
    const auto begin() const { return m.begin(); }
    auto begin() { return m.begin(); }
    const auto end() const { return m.end(); }
    auto end() { return m.end(); }

    int size() const { return V; }

    void add_edge(int a, int b, T d = T(1)) {
        m[a][b] = d;
    }
    void add_edges(int a, int b, T d = T(1)) {
        m[a][b] = d;
        m[b][a] = d;
    }

    void complement() {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) m[i][j] = !m[i][j];
        }
    }
};

constexpr int64_t _MOD = (1LL << 31) - 1;

int64_t _mod(int64_t a){
    a = (a & _MOD) + (a >> 31);
    return a >= _MOD ? a - _MOD : a;
};
int64_t _pow(int64_t a, int n) {
    int64_t res = 1;
    for (; n > 0; n >>= 1) {
        if (n & 1)
            res = _mod(res * a);
        a = _mod(a * a);
    }
    return res;
};

int chromatic_number(const Graph<bool> &G) {
    int n = G.size();
    const int m = 1 << n;
    vector<int> neighbor(n, 0);
    for (int i = 0; i < n; ++i) {
        int s = 1 << i;
        for (int j = 0; j < n; ++j) {
            if (G[i][j])
                s |= 1 << j;
        }
        neighbor[i] = s;
    }
    
    vector<int> v(m);
    v[0] = 1;
    for (int s = 1; s < m; ++s) {
        int c = __builtin_ctz(s);
        v[s] = v[s & ~(1 << c)] + v[s & ~neighbor[c]];
    }

    int low = 0, high = n;
    while (high - low > 1) {
        int mid = (low + high) >> 1;
        int64_t g = 0;
        for (int s = 0; s < m; ++s) {
            if ((n - __builtin_popcount(s)) & 1) g = _mod(g + _MOD - _pow(v[s], mid));
            else g = _mod(g + _pow(v[s], mid));
        }
        if (g != 0) high = mid;
        else low = mid;
    }
    return high;
}

int main(void) {
    int n, m;
    scanf("%d%d", &n, &m);
    char p[15][100001];
    rep(i, n) scanf("%s", p[i]);
    Graph<bool> g(n);

    rep(i, n) {
        rep(j, n) {
            auto s = p[i], t = p[j];
            bool flg = true;
            rep(k, m) if (!(flg &= s[k] == '*' || t[k] == '*' || s[k] == t[k])) break;
            if (flg) {
                g[i][j] = true;
                g[j][i] = true;
            }
        }
    }

    g.complement();

    co(chromatic_number(g));

    return 0;
}
