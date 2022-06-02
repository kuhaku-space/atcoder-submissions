/*
confirm 0LL and 1LL
confirm cornercases such as 0
confirm times of cin < 10^6
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using P = pair<ll, ll>;
using Pld = pair<ld, ld>;
using Vec = vector<ll>;
using VecP = vector<P>;
using VecB = vector<bool>;
using VecC = vector<char>;
using VecD = vector<ld>;
using VecS = vector<string>;
using Graph = vector<VecP>;
template <typename T>
using Vec1 = vector<T>;
template <typename T>
using Vec2 = vector<Vec1<T> >;
#define REP(i, m, n) for(ll (i) = (m); (i) < (n); ++(i))
#define REPN(i, m, n) for(ll (i) = (m); (i) <= (n); ++(i))
#define REPR(i, m, n) for(ll (i) = (m)-1; (i) >= (n); --(i))
#define REPNR(i, m, n) for(ll (i) = (m); (i) >= (n); --(i))
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
//constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-11;
const ld PI = acos(-1);

Vec2<P> graph;

int main(void){
	ll n, m, s;
	cin >> n >> m >> s;
	graph.resize(n);
	Vec a(m), b(m);
	rep(i, m){
		ll u, v;
		cin >> u >> v >> a[i] >> b[i];
		u--, v--;
		graph[u].pb({v, i});
		graph[v].pb({u, i});
	}
	Vec c(n), d(n);
	rep(i, n) cin >> c[i] >> d[i];

	Vec2<ll> dist(n, Vec(2500, LINF));
	using PP = pair<ll, P>;
	priority_queue<PP, vector<PP>, greater<> > pq;
	pq.push({0, {s, 0}});
	while(!pq.empty()){
		auto p = pq.top(); pq.pop();
		ll x = p.fs, y = p.sc.fs, z = p.sc.sc;
		//co({x, y, z});
		chmin(y, 2499LL);
		if(!chmin(dist[z][y], x)) continue;
		pq.push({x + d[z], {y + c[z], z}});
		for(P i : graph[z]){
			if(y >= a[i.sc]) pq.push({x + b[i.sc], {y - a[i.sc], i.fs}});
		}
	}

	Vec ans(n, LINF);
	rep(i, n) rep(j, 2500) chmin(ans[i], dist[i][j]);
	REP(i, 1, n) co(ans[i]);

	return 0;
}
