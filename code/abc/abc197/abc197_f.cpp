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

template <class T>
struct Graph {
    struct edge {
        int id;
        int from, to;
        T dist;

        bool operator<(const edge &rhs) const {
            return dist < rhs.dist;
        }
        bool operator>(const edge &rhs) const {
            return rhs < *this;
        }
    };

    int V, E;
    vector<vector<edge>> edges;

    Graph(int v) : V(v), E(), edges(v) {}

    const auto &operator[](int i) const {
        return edges[i];
    }
    auto &operator[](int i) {
        return edges[i];
    }
    const auto begin() const {
        return edges.begin();
    }
    auto begin() {
        return edges.begin();
    }
    const auto end() const {
        return edges.end();
    }
    auto end() {
        return edges.end();
    }

    int size() const {
        return V;
    }

    void add_edge(int a, int b, T d = T(1)) {
        edges[a].push_back(edge{E++, a, b, d});
    }
    void add_edges(int a, int b, T d = T(1)) {
        edges[a].push_back(edge{E++, a, b, d});
        edges[b].push_back(edge{E++, b, a, d});
    }
};

struct S {
    int d, from, to;
};


int main(void) {
    int n, m;
    cin >> n >> m;

    Graph<char> g(n);
    rep(i, m) {
        int a, b;
        char c;
        cin >> a >> b >> c;
        --a, --b;
        g.add_edges(a, b, c);
    }

    auto dp = make_vector<int>(Inf, n, n);
    queue<S> que;
    que.push({0, 0, n - 1});
    while (!que.empty()) {
        auto s = que.front();
        que.pop();
        if (!chmin(dp[s.from][s.to], s.d))
            continue;
        for (auto e : g[s.from]) {
            for (auto f : g[s.to]) {
                if (e.dist == f.dist)
                    que.push({s.d + 1, e.to, f.to});
            }
        }
    }
    co(dp[n - 1][0] == Inf ? -1 : dp[n - 1][0]);

    return 0;
}
