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

template <class T>
struct Graph {
    struct edge {
        int to;
        T dist;

        bool operator<(const edge &rhs) const { return dist < rhs.dist; }

        bool operator>(const edge &rhs) const { return dist > rhs.dist; }

        edge &operator+=(const edge &rhs) {
            to = rhs.to;
            dist += rhs.dist;
            return *this;
        }
        edge operator+(const edge &rhs) { return edge(*this) += rhs; }
    };

    int V;
    vector<T> dist;
    vector<int> color;
    bitset<1 << 17> is_visit;
    vector<vector<edge>> edges;

    Graph(int64_t v) : V(v) {
        edges = vector<vector<edge>>(V);
        dist = vector<T>(V, 1);
        color = vector<int>(V);
    }

    void add_edge(int64_t a, int64_t b, T d = 1, bool is_dual = false) {
        edges[a].push_back(edge{b, d});
        if (is_dual) edges[b].push_back(edge{a, d});
    }
    void add_edges(int64_t a, int64_t b, T d = 1) {
        edges[a].push_back(edge{b, d});
        edges[b].push_back(edge{a, d});
    }

    void bfs(int64_t v, T d, int64_t c) {
        queue<edge> que;
        que.push(edge{v, -d});
        while (!que.empty()) {
            auto e = que.front();
            que.pop();
            if (!chmin(dist[e.to], e.dist)) continue;
            if(!is_visit[e.to]) color[e.to] = c, is_visit[e.to] = true;
            for (auto i : edges[e.to]) que.push(e + i);
        }
    }
};

int main(void) {
    sonic();
    int n, m;
    cin >> n >> m;

    Graph<int> g(n);
    rep(i, m) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g.add_edges(a, b);
    }

    int q;
    cin >> q;
    vector<int> v(q), d(q), c(q);
    rep(i, q) cin >> v[i] >> d[i] >> c[i];

    repr(i, q) g.bfs(v[i] - 1, d[i], c[i]);
    rep(i, n) co(g.color[i]);

    return 0;
}