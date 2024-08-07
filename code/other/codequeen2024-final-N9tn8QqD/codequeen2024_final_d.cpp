#include <bits/stdc++.h>

using namespace std;
#define SZ(x) (int) (x).size()
#define REP(i, n) for(int i = 0; i < (n); i++)
#define FOR(i, a, b) for(auto i = (a); i < (b); i++)
#define For(i, a, b, c) \
	for(auto i = (a); i != (b); i += (c))
#define REPR(i, n) for(auto i = (n) - 1; i >= 0; i--)
#define ALL(s) (s).begin(), (s).end()
#define so(V) sort(ALL(V))
#define rev(V) reverse(ALL(V))
#define uni(v) v.erase(unique(ALL(v)), (v).end())
#define eb emplace_back

typedef unsigned long long ull;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<bool> vb;
typedef vector<vi> vvi;
typedef vector<vll> vvll;
typedef pair<int, int> PI;
typedef pair<ll, ll> PL;
const double EPS = 1e-6;
const int MOD = 1e9 + 7;
const int INF = (1 << 30);
const ll LINF = 1e18;
const double math_PI = acos(-1);

template<typename T>
vector<T> make_v(size_t a) {
	return vector<T>(a);
}

template<typename T, typename... Ts>
auto make_v(size_t a, Ts... ts) {
	return vector<decltype(make_v<T>(ts...))>(
		a, make_v<T>(ts...));
}

template<typename T, typename V>
typename enable_if<is_class<T>::value == 0>::type fill_v(
	T &t, const V &v) {
	t = v;
}

template<typename T, typename V>
typename enable_if<is_class<T>::value != 0>::type fill_v(
	T &t, const V &v) {
	for(auto &e: t) fill_v(e, v);
}

template<class T>
bool chmax(T &a, const T &b) {
	if(a < b) {
		a = b;
		return true;
	}
	return false;
}

template<class T>
bool chmin(T &a, const T &b) {
	if(a > b) {
		a = b;
		return true;
	}
	return false;
}

template<typename S, typename T>
istream &operator>>(istream &is, pair<S, T> &p) {
	cin >> p.first >> p.second;
	return is;
}

template<typename T>
istream &operator>>(istream &is, vector<T> &vec) {
	for(T &x: vec) is >> x;
	return is;
}

template<typename T>
string join(vector<T> &vec, string splitter) {
	stringstream ss;
	REP(i, SZ(vec)) {
		if(i != 0) ss << splitter;
		ss << vec[i];
	}
	return ss.str();
}

template<typename T>
ostream &operator<<(ostream &os, vector<T> &vec) {
	os << join(vec, " ");
	return os;
}

#ifdef LOCAL
#include "./cpp-dump/dump.hpp"
#include "./cpp-dump/mytypes.hpp"
#define dump(...) cpp_dump(__VA_ARGS__)
namespace cp = cpp_dump;
#else
#define dump(...)
#define preprocess(...)
#define CPP_DUMP_SET_OPTION(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT(...)
#define CPP_DUMP_DEFINE_EXPORT_ENUM(...)
#define CPP_DUMP_DEFINE_DANGEROUS_EXPORT_OBJECT(...)
#endif
template<class T = ll>
struct Edge {
public:
	int from, to;
	T cost;
	Edge() {
	}
	Edge(int _from, int _to, T _cost) {
		from = _from;
		to = _to;
		cost = _cost;
	}
};
template<class T = ll>
using Edges = vector<Edge<T>>;
template<class T = ll>
using Graph = vector<Edges<T>>;

template<typename T = ll>
class GraphBuilder {
private:
	int N, M;
	Graph<T> G;
	int index = 1;
	bool m_weighted = false;
	bool m_directed = false;
	bool m_tree_format = false;

public:
	GraphBuilder(int N): N(N), M(N - 1) {
		G = Graph<T>(N);
	}

	GraphBuilder(int N, int M): N(N), M(M) {
		G = Graph<T>(N);
	}

	GraphBuilder& setIndex(int index = 1) {
		this->index = index;
		return *this;
	}

	GraphBuilder& weighted(bool weighted = true) {
		this->m_weighted = weighted;
		return *this;
	}

	GraphBuilder& directed(bool directed = true) {
		this->m_directed = directed;
		return *this;
	}

	GraphBuilder& useTreeFormat(bool tree_format = true) {
		this->m_tree_format = tree_format;
		return *this;
	}

	Graph<T> build(istream& in) {
		if(this->m_tree_format) {
			FOR(i, 1, N) {
				int p;
				cin >> p;
				p -= index;
				T c(1);
				if(m_weighted) {
					in >> c;
				}
				G[p].eb(p, i, c);
				if(!m_directed) {
					G[i].eb(i, p, c);
				}
			}
		} else {
			REP(i, M) {
				int u, v;
				in >> u >> v;
				u -= index;
				v -= index;
				T c(1);
				if(m_weighted) {
					in >> c;
				}
				G[u].eb(u, v, c);
				if(!m_directed) {
					G[v].eb(v, u, c);
				}
			}
		}
		return G;
	}

	vector<vector<T>> buildMatrix(istream& in,
								  T non_edge = LINF) {
		vector<vector<T>> G(N, vector<T>(N, non_edge));
		if(this->m_tree_format) {
			FOR(i, 1, N) {
				int p;
				cin >> p;
				p -= index;
				T c(1);
				if(m_weighted) {
					in >> c;
				}
				G[p][i] = c;
				if(!m_directed) {
					G[i][p] = c;
				}
			}
		} else {
			REP(i, M) {
				int u, v;
				in >> u >> v;
				u -= index;
				v -= index;
				T c(1);
				if(m_weighted) {
					in >> c;
				}
				G[u][v] = c;
				if(!m_directed) {
					G[v][u] = c;
				}
			}
		}
		return G;
	}

	Edges<T> buildEdgeList(istream& in) {
		Edges<T> edges;
		if(this->m_tree_format) {
			FOR(i, 1, N) {
				int p;
				cin >> p;
				p -= index;
				T c(1);
				if(m_weighted) {
					in >> c;
				}
				edges.eb(p, i, c);
				if(!m_directed) {
					edges.eb(i, p, c);
				}
			}
		} else {
			REP(i, M) {
				int u, v;
				in >> u >> v;
				u -= index;
				v -= index;
				T c(1);
				if(m_weighted) {
					in >> c;
				}
				edges.eb(u, v, c);
				if(!m_directed) {
					edges.eb(v, u, c);
				}
			}
		}
		return edges;
	}
};
vll dijkstra(int s, const Graph<ll>& G) {
	using P = pair<ll, int>;
	priority_queue<P, vector<P>, greater<>> que;
	vll D(SZ(G), LINF);
	D[s] = 0;
	que.push(P(0, s));
	while(!que.empty()) {
		P p = que.top();
		que.pop();
		int v = p.second;
		if(D[v] < p.first) continue;
		for(Edge e: G[v]) {
			if(D[e.to] > D[v] + e.cost) {
				D[e.to] = D[v] + e.cost;
				que.push(P(D[e.to], e.to));
			}
		}
	}
	return D;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	int N, M, K;
	cin >> N >> M >> K;
	auto G = GraphBuilder(N, M).weighted(true).build(cin);
	vector<vll> dist(N);
	REP(i, N) {
		dist[i] = dijkstra(i, G);
	}
	priority_queue<PL, vector<PL>, greater<PL>> Q;
	REP(i, K) {
		ll a, b;
		cin >> a >> b;
		--a;
		Q.push({ b, a });
	}
	dump(Q);
	vll V(K + 1);
	vll T(K + 1);
	vll dp(K + 1, -K);
	dp[0] = 0;
	ll ans = 0;
	FOR(i, 1, K + 1) {
		auto [t, v] = Q.top();
		Q.pop();
		T[i] = t;
		V[i] = v;
		REP(j, i) {
			if(dist[V[j]][v] + T[j] <= T[i]) {
				chmax(dp[i], dp[j] + 1);
				chmax(ans, dp[i]);
			}
		}
	}
	cout << ans << endl;
	return 0;
}
