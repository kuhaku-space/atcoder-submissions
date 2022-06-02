#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ld = long double;
using P = pair<ll, ll>;
using Pld = pair<ld, ld>;
using Vec = vector<ll>;
using VecP = vector<P>;
using VecB = vector<bool>;
using VecC = vector<char>;
using VecD = vector<ld>;
using VecS = vector<string>;
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
bool chmax(T1 &a, const T2 b) { if (a < b) { a = b; return true; } return false; }
template <class T1, class T2>
bool chmin(T1 &a, const T2 b) { if (a > b) { a = b; return true; } return false; }
template <class T>
istream &operator>>(istream &is, vector<T> &v) { for (T &i : v) is >> i; return is; }
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) { for (const T &i : v) os << i << ' '; return os; }
void _co() { cout << '\n'; }
template <class Head, class... Tail>
void _co(Head&& head, Tail&&... tail) { cout << ' ' << head; _co(forward<Tail>(tail)...); }
template <class Head, class... Tail>
void co(Head&& head, Tail&&... tail) { cout << head; _co(forward<Tail>(tail)...); }
void ce() { cerr << endl; }
template <class Head, class... Tail>
void ce(Head&& head, Tail&&... tail) { cerr << head << ' '; ce(forward<Tail>(tail)...); }
void sonic() { ios::sync_with_stdio(false); cin.tie(nullptr); }
void setp(const int n) { cout << fixed << setprecision(n); }
constexpr int64_t LINF = 1000000000000000001;
constexpr int64_t MOD = 1000000007;
constexpr int64_t MOD_N = 998244353;
constexpr long double EPS = 1e-11;
const double PI = acos(-1);

Vec c;
Vec d;

template <class T>
struct Graph {
    struct edge {
        int64_t from, to;
        T dist;

        bool operator<(const edge &rhs) const {
            return dist < rhs.dist;
        }
        
        bool operator>(const edge &rhs) const {
            return dist > rhs.dist;
        }

        edge &operator+=(const edge &rhs) {
            to = rhs.to;
            dist += rhs.dist;
            return *this;
        }
        edge operator+(const edge &rhs) {
            return edge(*this) += rhs;
        }
    };

    int64_t V;
    vector<T> dist;
    vector<vector<edge>> edges;
    bitset<1048576> negative_cycle;

    Graph(int64_t v) : V(v) {
        edges.resize(v);
        dist.assign(v, numeric_limits<T>::max());
    }

    void add_edge(int64_t a, int64_t b, T d = 1) {
        edges[a].push_back(edge{a, b, d});
        edges[b].push_back(edge{b, a, d});
    }

    void dfs(int64_t x, int64_t p) {
        for (auto i : edges[x]) {
            if (i.to == p)
                continue;
            c[i.to] += c[x];
            dfs(i.to, x);
        }
    }

    void dijkstra(int64_t s) {
        dist.assign(V, numeric_limits<T>::max());
        priority_queue<edge, vector<edge>, greater<edge>> p_que;
        p_que.push(edge{s, s, T()});
        while (!p_que.empty()) {
            edge e = p_que.top(); p_que.pop();
            if (e.dist >= dist[e.to]) continue;
            dist[e.to] = e.dist;
            for (auto i : edges[e.to]) p_que.push(e + i);
        }
    }

    void bellman_ford(int64_t s){
        dist.assign(V, numeric_limits<T>::max());
        dist[s] = T();
        negative_cycle = bitset<1048576>();

        bool flg = true;
        int64_t cnt = 0;
        while (flg && cnt <= V * 2) {
            flg = false;
            for (int64_t i = 0; i < V; ++i) {
                if (dist[i] == numeric_limits<T>::max()) continue;
                for (auto j : edges[i]) {
                    if (chmin(dist[j.to], dist[i] + j.dist)) {
                        flg = true;
                        if (cnt >= V) negative_cycle.set(j.to);
                    }
                }
            }
            ++cnt;
        }
    }

    T get_dist(int64_t a) {
        return dist[a];
    }

    bool is_visit(int64_t a) {
        return dist[a] != numeric_limits<T>::max();
    }

    bool is_negative_cycle(int64_t a) {
        return negative_cycle[a];
    }/*

    T kruskal() {
        union_find uf(V);
        T res = T();
        vector<edge> edge_list;
        for (auto v : edges) {
            for (auto e : v) edge_list.push_back(e);
        }
        sort(edge_list.begin(), edge_list.end());
        for (edge e : edge_list) {
            if (!uf.is_same(e.from, e.to)) {
                uf.unite(e.from, e.to);
                res += e.dist;
            }
        }
        return res;
    }*/

    vector<int64_t> topological_sort() {
        vector<int64_t> res;
        bitset<1048576> is_seen;
        for (int64_t i = 0; i < V; ++i) {
            if (is_seen[i]) continue;
            stack<int64_t> st;
            st.push(~i);
            st.push(i);
            while (!st.empty()) {
                auto v = st.top();
                st.pop();
                if (v < 0) {
                    if (!is_seen[~v]) res.push_back(~v);
                    is_seen.set(~v);
                    continue;
                }
                for (auto e : edges[v]) {
                    if (is_seen[e.to]) continue;
                    st.push(~e.to);
                    st.push(e.to);
                }
            }
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

struct LCA {
    int64_t V, logV;
    vector<vector<int64_t>> data;
    vector<int64_t> depth;
    vector<vector<int64_t>> parent;
    
    LCA(int64_t v) {
        V = v;
        logV = 0;
        while (v > (1LL << logV)) logV++;
        data = vector<vector<int64_t>>(V);
        depth = vector<int64_t>(V);
        parent = vector<vector<int64_t>>(logV, vector<int64_t>(V));
    }
    
    void init(int64_t v) {
        struct node {
            int64_t v, par, d;
        };
        stack<node> st;
        st.push(node{v, -1, 0});
        while (!st.empty()) {
            auto t = st.top();
            st.pop();
            depth[t.v] = t.d;
            parent[0][t.v] = t.par;
            for (auto i : data[t.v]) {
                if (i == t.par) continue;
                st.push(node{i, t.v, t.d + 1});
            }
        }
    }
    
    void build() {
        init(0);
        for (int64_t k = 0; k < logV - 1; ++k) {
			for (int64_t v = 0; v < V; ++v) {
				if (parent[k][v] < 0) parent[k + 1][v] = -1;
				else parent[k + 1][v] = parent[k][parent[k][v]];
			}
		}
	}

    void add_edge(int64_t a, int64_t b) {
        data[a].push_back(b);
        data[b].push_back(a);
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

    int64_t par(int64_t a, int64_t d) {
		for (int64_t k = 0; k < logV; ++k) {
			if (d >> k & 1) a = parent[k][a];
		}
        return a;
    }

    int64_t get_depth(int64_t a) {
        return depth[a];
    }
};

int main(void) {
    ll n;
    cin >> n;
    LCA lca(n);
    Graph<ll> g(n);
    Vec a(n), b(n);
    rep(i, n - 1) cin >> a[i] >> b[i];
    rep(i, n - 1) {
        --a[i], --b[i];
        // ce(a[i], b[i]);
        lca.add_edge(a[i], b[i]);
        g.add_edge(a[i], b[i]);
    }

    c.resize(n);
    d.resize(n);
    lca.build();

    ll q;
    cin >> q;
    ll sum = 0;
    rep(i, q) {
        ll t, e, x;
        cin >> t >> e >> x;
        --e;
        // sum += x;
        if (t == 1) {
            // c[b[e]] -= x;
            if(lca.lca(a[e], b[e]) == b[e]) {
                // ce(a[e], lca.par(a[e], lca.get_depth(a[e]) - lca.get_depth(b[e]) - 1));
                c[lca.par(a[e], lca.get_depth(a[e]) - lca.get_depth(b[e]) - 1)] += x;
                // sum += x;
            } else {
                sum += x;
                c[b[e]] -= x;
            }
        } else {
            // c[a[e]] -= x;
            if(lca.lca(a[e], b[e]) == a[e]) {
                // ce(b[e], lca.par(b[e], lca.get_depth(b[e]) - lca.get_depth(a[e]) - 1));
                c[lca.par(b[e], lca.get_depth(b[e]) - lca.get_depth(a[e]) - 1)] += x;
                // sum += x;
            } else {
                sum += x;
                c[a[e]] -= x;
            }
        }
    }

    g.dfs(0, 0);

    rep(i, n) co(sum + c[i]);

    return 0;
}