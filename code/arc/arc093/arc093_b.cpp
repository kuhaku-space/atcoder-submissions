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

int main(void){
	ll a, b;
	cin >> a >> b;

	ll x = 1, y = 1;
	vector<Vec> ans(100, Vec(100, 1));
	rep(i, 50) rep(j, 100) ans[i][j] = 0;

	rep(i, 25){
		if(y == b) break;
		rep(j, 50){
			if(y == b) break;
			ans[i*2][j*2] = 1;
			y++;
		}
	}
	repr(i, 49){
		if(x == a) break;
		rep(j, 50){
			if(x == a) break;
			ans[i*2+1][j*2] = 0;
			x++;
		}
	}

	cosp(100); co(100);
	rep(i, 100){
		rep(j, 100) cout << (!ans[i][j] ? '.' : '#');
		cout << endl;
	}

	return 0;
}
