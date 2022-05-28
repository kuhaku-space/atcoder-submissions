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
void sonic(){ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);}
void setp(const ll n){cout << fixed << setprecision(n);}
constexpr ll INF = 1e9+1;
constexpr ll LINF = 1e18+1;
constexpr ll MOD = 1e9+7;
//constexpr ll MOD = 998244353;
constexpr ld PI = acos(-1);
constexpr ld EPS = 1e-11;

Vec2<ll> tree;
Vec par, size, dp, dpPar;

Vec fac, finv;

ll PowMod(ll a, ll n){
	if(n == 1) return a;
	if(n%2 == 0) return PowMod(a*a%MOD, n/2);
	return a*PowMod(a*a%MOD, n/2)%MOD;
}

ll inv(ll a){
	return PowMod(a, MOD-2);
}

void init(ll n = 2e5+10){
	fac.resize(n+1);
	fac[0] = 1;
	repn(i, n) fac[i] = fac[i-1]*i%MOD;
	finv.resize(n+1);
	finv[n] = PowMod(fac[n], MOD-2);
	repr(i, n) finv[i] = finv[i+1]*(i+1)%MOD;
	finv[0] = 1;
}

ll combi(ll n, ll k){
	return fac[n]*finv[k]%MOD*finv[n-k]%MOD;
}

ll dfs(ll node, ll p){
	ll cnt = 0;
	par[node] = p;
	for(ll i : tree[node]){
		if(i != p) cnt += dfs(i, node);
	}
	return size[node] = cnt + 1;
}

ll f(ll node, ll p){
	ll res = 1;
	for(ll i : tree[node]){
		if(i == p) continue;
		res *= f(i, node);
		res %= MOD;
		res *= finv[size[i]];
		res %= MOD;
	}

	res *= fac[size[node] - 1];
	res %= MOD;

	return dp[node] = res;
}

ll g(ll node){
	if(dpPar[node] != LINF) return dpPar[node];
	ll n = tree.size();

	ll res = 1;
	ll p = par[node];
	if(p != 0){
		res *= g(p);
		res *= finv[n - size[p]];
		res %= MOD;
	}
	res *= dp[p];
	res %= MOD;
	res *= inv(combi(size[p] - 1, size[node]));
	res %= MOD;
	res *= inv(dp[node]);
	res %= MOD;
	res *= finv[size[p] - 1 - size[node]];
	res %= MOD;
	res *= fac[n - 1 - size[node]];
	res %= MOD;

	return dpPar[node] = res;
}

int main(void){
	init();
	ll n;
	cin >> n;
	tree.resize(n);
	par.resize(n);
	size.resize(n);
	dp.assign(n, LINF);
	dpPar.assign(n, LINF);
	rep(i, n - 1){
		ll a, b;
		cin >> a >> b;
		a--, b--;
		tree[a].pb(b);
		tree[b].pb(a);
	}

	dfs(0, -1);

	co(f(0, -1));
	repn(i, n - 1) co(combi(n - 1, size[i] - 1) * dp[i] % MOD * g(i) % MOD);
	//co(dp);
	//co(dpPar);

	return 0;
}
