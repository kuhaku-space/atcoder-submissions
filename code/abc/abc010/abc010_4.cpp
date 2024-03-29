#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using P = pair<ll, ll>;
using Pld = pair<ld, ld>;
using Vec = vector<ll>;
using VecP = vector<P>;
using VecC = vector<char>;
using VecD = vector<ld>;
using VecS = vector<string>;
template <typename T>
using Vec1 = vector<T>;
template <typename T>
using Vec2 = vector<Vec1<T> >;
#define REP(i, m, n) for(ll i = (m); i < (n); ++i)
#define REPN(i, m, n) for(ll i = (m); i <= (n); ++i)
#define REPR(i, m, n) for(ll i = (m)-1; i >= (n); --i)
#define REPNR(i, m, n) for(ll i = (m); i >= (n); --i)
#define rep(i, n) REP(i, 0, n)
#define repn(i, n) REPN(i, 1, n)
#define repr(i, n) REPR(i, n, 0)
#define repnr(i, n) REPNR(i, n, 1)
#define all(s) (s).begin(), (s).end()
#define pb push_back
#define fs first
#define sc second
template <typename T>
bool chmax(T &a, const T b){if(a < b){a = b; return true;} return false;}
template <typename T>
bool chmin(T &a, const T b){if(a > b){a = b; return true;} return false;}
template <typename T>
ll pow2(const T n){return (1LL << n);}
template <typename T>
void cosp(const T n){cout << n << ' ';}
void co(void){cout << '\n';}
template <typename T>
void co(const T n){cout << n << '\n';}
template <typename T1, typename T2>
void co(pair<T1, T2> p){cout << p.fs << ' ' << p.sc << '\n';}
template <typename T>
void co(const Vec1<T> &v){for(T i : v) cosp(i); co();}
template <typename T>
void co(initializer_list<T> v){for(T i : v) cosp(i); co();}
template <typename T>
void ce(const T n){cerr << n << endl;}
void sonic(){ios::sync_with_stdio(false); cin.tie(0);}
void setp(const ll n){cout << fixed << setprecision(n);}
constexpr int INF = 1e9+1;
constexpr ll LINF = 1e18+1;
constexpr ll MOD = 1e9+7;
// constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-11;
const ld PI = acos(-1);

using Graph = vector<unordered_map<ll, ll> >;
using VecB = vector<bool>;
Graph graph;
VecB used;

ll dfs(ll v, ll t, ll f){
	if (v == t) return f;
	used[v] = true;
	for(auto &i : graph[v]){
		if(!used[i.fs] && i.sc){
			ll d = dfs(i.fs, t, min(f, i.sc));
			if (d){
				i.sc -= d;
				graph[i.fs][v] += d;
				return d;
			}
		}
	}
	return 0;
}

// 最大流を求める
ll ford_fulkerson(ll s, ll t){
	ll res = 0;
	while(true){
		used.assign(used.size(), false);
		ll f = dfs(s, t, LINF);
		if (!f) break;
		res += f;
	}
	return res;
}

int main(void){
	ll n, g, e;
	cin >> n >> g >> e;
	graph.resize(n + 1);
	used.resize(n + 1);
	Vec p(g);
	rep(i, g) cin >> p[i];
	rep(i, g) graph[p[i]][n]++;
	rep(i, e){
		ll a, b;
		cin >> a >> b;
		graph[a][b]++;
		graph[b][a]++;
	}

	co(ford_fulkerson(0, n));

	return 0;
}
