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

    auto &operator[](int i) { return edges[i]; }
    const auto &operator[](int i) const { return edges[i]; }
    auto begin() { return edges.begin(); }
    const auto begin() const { return edges.begin(); }
    auto end() { return edges.end(); }
    const auto end() const { return edges.end(); }
    
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
vector<T> bellman_ford(const Graph<T> &g, int s = 0,
                       T inf = numeric_limits<T>::max()) {
    int n = g.size();
    vector<T> dist(n, inf);
    dist[s] = T();
    bool flg = true;
    for (int cnt = 0; flg && cnt <= n * 2; ++cnt) {
        flg = false;
        for (int i = 0; i < n; ++i) {
            if (dist[i] == inf) continue;
            for (auto &j : g[i]) {
                if (dist[i] == -inf || chmin(dist[j.to], dist[i] + j.dist)) {
                    if (dist[j.to] == -inf)
                        continue;
                    flg = true;
                    if (cnt >= n) dist[j.to] = -inf;
                }
            }
        }
    }
    return dist;
}

int main(void){
	int n, m, p;
	cin >> n >> m >> p;
    Graph<int> g(n);

	int a, b, c;
	rep(i, m){
		cin >> a >> b >> c;
		a--, b--;
        g.add_edge(a, b, p - c);
	}

    auto ans = bellman_ford(g, 0, int(1e9));
    if (ans[n - 1] == -int(1e9) || ans[n - 1] == int(1e9))
        ans[n - 1] = 1;
    else if (ans[n - 1] > 0)
        ans[n - 1] = 0;
    co(-ans[n - 1]);

    return 0;
}
