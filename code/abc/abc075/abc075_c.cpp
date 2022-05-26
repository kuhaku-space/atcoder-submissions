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
const ll MAX_H = 2e5;
const ll MAX_W = 2e5;

Vec par;

void init(ll n){
  repn(i, n) par[i] = i;
}

ll find(ll x){
  if(par[x] == x) return x;
  else return par[x] = find(par[x]);
}

void unionRoot(ll x, ll y){
  x = find(x);
  y = find(y);
  if(x != y) par[x] = y;
}

int main(void){
	ll n, m;
	cin >> n >> m;
	par.resize(n+1);
	VecP edges(m);
	rep(i, m){
		cin >> edges[i].fs >> edges[i].sc;
	}

	ll ans = 0;
	rep(i, m){
		init(n);
		rep(j, m){
			if(i == j) continue;
			unionRoot(edges[j].fs, edges[j].sc);
		}

		ll cnt = 0;
		repn(i, n) if(find(i) == i) cnt++;
		if(cnt >= 2) ans++;
	}
	co(ans);

	return 0;
}
