#include <bits/stdc++.h>
using namespace std;
using ll = long long ;
using P = pair<ll, ll>;
using Vec = vector<ll>;
using VecP = vector<P>;
#define FOR(i, m, n) for(ll (i) = (m); (i) < (n); ++(i))
#define FORN(i, m, n) for(ll (i) = (m); (i) <= (n); ++(i))
#define FORR(i, m, n) for(ll (i) = (m); (i) >= (n); --(i))
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FORN(i, 1, n)
#define repr(i, n) FORR(i, n, 0)
#define repnr(i, n) FORR(i, n, 1)
#define co(n) cout << (n) << endl
#define cosp(n) cout << (n) << ' '
#define setp(n) cout << fixed << setprecision(n);
#define all(s) (s).begin(), (s).end()
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define fs first
#define sc second

const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;
const ll MAX_N = 1e5;

Vec par(MAX_N+1);

void init(ll n){
  repn(i, n) par[i] = i;
}

ll find(ll x){
  if(par[x] == x) return x;
  else return par[x] = find(par[x]);
}

void union_root(ll x, ll y){
  x = find(x);
  y = find(y);
  if(x != y) par[x] = y;
}


int main(void){
	ll n, m;
	cin >> n >> m;
	init(n);
	ll x, y, z;
	rep(i, m){
		cin >> x >> y >> z;
		union_root(x, y);
	}
	ll ans = 0;
	repn(i, n) if(par[i] == i) ans++;
	co(ans);

	return 0;
}
