#include <bits/stdc++.h>
using namespace std;
using ll = long long ;
using P = pair<ll, ll>;
using Vec = vector<ll>;
using VecP = vector<P>;
#define REP(i, m, n) for(ll (i) = (m); (i) < (n); ++(i))
#define REPN(i, m, n) for(ll (i) = (m); (i) <= (n); ++(i))
#define REPR(i, m, n) for(ll (i) = (m); (i) >= (n); --(i))
#define rep(i, n) REP(i, 0, n)
#define repn(i, n) REPN(i, 1, n)
#define repr(i, n) REPR(i, n, 0)
#define repnr(i, n) REPR(i, n, 1)
#define co(n) cout << (n) << endl
#define cosp(n) cout << (n) << ' '
#define setp(n) cout << fixed << setprecision(n);
#define all(s) (s).begin(), (s).end()
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define fs first
#define sc second
template <typename T> bool chmax(T &a, const T& b){if(a < b){a = b; return true;} return false;}
template <typename T> bool chmin(T &a, const T& b){if(a > b){a = b; return true;} return false;}
const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;

ll mod(ll n, ll m){
	return ((n%m)+m)%m;
}

int main(void){
	ll n, x, d;
	cin >> n >> x >> d;
	if(d < 0){
		d = -d;
		x = -x;
	}

	if(!d){
		if(!x) co(1);
		else co(n+1);
		return 0;
	}

	map<ll, VecP> range;
	rep(i, n+1){
		ll p = i*x/d;
		ll r = mod(i*x, d);
		ll b = p+i*(0+i-1)/2;
		ll e = p+i*(n-1+n-i)/2;
		range[r].pb(mp(b, e));
	}

	ll ans = 0;
	for(auto itr : range){
		VecP &v = itr.sc;
		sort(all(v));
		ll e = -LINF;
		for(P r : v){
			if(r.fs > e) ans += r.sc-r.fs+1;
			else ans += max(0LL, r.sc-e);
			chmax(e, r.sc);
		}
	}
	co(ans);

	return 0;
}
