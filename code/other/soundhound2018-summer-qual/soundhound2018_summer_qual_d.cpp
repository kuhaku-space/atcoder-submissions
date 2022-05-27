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
#define mp make_pair
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
template <typename T>
void co(const T n){cout << n << '\n';}
template <typename T1, typename T2>
void co(pair<T1, T2> p){cout << p.fs << ' ' << p.sc << '\n';}
template <typename T>
void co(const Vec1<T> &v){for(T i : v) cosp(i); cout << '\n';}
template <typename T>
void co(initializer_list<T> v){for(T i : v) cosp(i); cout << '\n';}
template <typename T>
void ce(const T n){cerr << n << endl;}
void sonic(){ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);}
void setp(const ll n){cout << fixed << setprecision(n);}
const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const ld PI = acos(-1);
const ld EPS = 1e-11;

Graph graph1, graph2;
Vec dist1, dist2;

void dijkstra1(ll s){
	priority_queue<P, vector<P>, greater<P> > que;
	que.push({0, s});
	while(!que.empty()){
		P o = que.top(); que.pop();
		if(o.fs >= dist1[o.sc]) continue;
		dist1[o.sc] = o.fs;
		for(P i : graph1[o.sc]) que.push({o.fs+i.sc, i.fs});
	}
}

void dijkstra2(ll s){
	priority_queue<P, vector<P>, greater<P> > que;
	que.push({0, s});
	while(!que.empty()){
		P o = que.top(); que.pop();
		if(o.fs >= dist2[o.sc]) continue;
		dist2[o.sc] = o.fs;
		for(P i : graph2[o.sc]) que.push({o.fs+i.sc, i.fs});
	}
}

int main(void){
	ll n, m, s, t;
	cin >> n >> m >> s >> t;
	s--, t--;
	graph1.resize(n);
	graph2.resize(n);
	dist1.assign(n, LINF);
	dist2.assign(n, LINF);
	rep(i, m){
		ll u, v, a, b;
		cin >> u >> v >> a >> b;
		u--, v--;
		graph1[u].pb({v, a});
		graph1[v].pb({u, a});
		graph2[u].pb({v, b});
		graph2[v].pb({u, b});
	}
	dijkstra1(s);
	dijkstra2(t);

	Vec ans(n);
	rep(i, n) ans[i] = dist1[i]+dist2[i];
	repr(i, n-1) chmin(ans[i], ans[i+1]);
	rep(i, n) ans[i] = 1e15-ans[i];
	co(ans);

	return 0;
}
