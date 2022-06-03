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
using VecVec = vector<Vec>;
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
bool chmax(T &a, const T& b){if(a < b){a = b; return true;} return false;}
template <typename T>
bool chmin(T &a, const T& b){if(a > b){a = b; return true;} return false;}
template <typename T>
void co(const T n){cout << n << endl;}
template <typename T>
void cosp(const T n){cout << n << ' ';}
void coVec(const Vec &v){for(ll i : v) cosp(i); cout << endl;}
ll in(){ll x; cin >> x; return x;}
void sonic(){ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);}
void setp(const ll n){cout << fixed << setprecision(n);}
const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const ld PI = acos(-1);
const ld EPS = 1e-11;

Graph graph;

bool acsy(const pair<P, ll> &a, const pair<P, ll> &b){
	ll y1 = a.fs.sc, y2 = b.fs.sc;
	return y1 < y2;
}

struct UnionFind{
	Vec par;

	UnionFind(ll n) : par(n){
		rep(i, n) par[i] = i;
	}

	ll root(ll x){
		if(par[x] == x) return x;
		return par[x] = root(par[x]);
	}

	void unite(ll x, ll y){
		x = root(x), y = root(y);
		if(x != y) par[x] = y;
	}

	bool same(ll x, ll y){
		return root(x) == root(y);
	}
};

int main(void){
	ll n;
	cin >> n;
	graph.resize(n);
	Vec1<pair<P, ll> > p(n);
	rep(i, n){
		cin >> p[i].fs.fs >> p[i].fs.sc;
		p[i].sc = i;
	}

	sort(all(p));
	rep(i, n-1){
			graph[p[i].sc].pb({abs(p[i].fs.fs-p[i+1].fs.fs), p[i+1].sc});
			graph[p[i+1].sc].pb({abs(p[i].fs.fs-p[i+1].fs.fs), p[i].sc});
	}
	sort(all(p), acsy);
	rep(i, n-1){
			graph[p[i].sc].pb({abs(p[i].fs.sc-p[i+1].fs.sc), p[i+1].sc});
			graph[p[i+1].sc].pb({abs(p[i].fs.sc-p[i+1].fs.sc), p[i].sc});
	}

	ll ans = 0;
	UnionFind uf(n);
	using pa = pair<ll, P>;
	priority_queue<pa, Vec1<pa>, greater<> > que;
	for(P i : graph[0]) que.push({i.fs, {0, i.sc}});
	while(!que.empty()){
		pa i = que.top(); que.pop();
		if(uf.same(i.sc.fs, i.sc.sc)) continue;
		uf.unite(i.sc.fs, i.sc.sc);
		ans += i.fs;
		for(P o : graph[i.sc.sc]){
			que.push({o.fs, {i.sc.sc, o.sc}});
		}
	}
	co(ans);

	return 0;
}
