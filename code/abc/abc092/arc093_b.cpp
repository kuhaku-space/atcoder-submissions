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

const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;

vector<Vec> ans(100, Vec(100, 0));

int main(void){
	ll a, b;
	cin >> a >> b;
	REP(i, 50, 100){
		fill(all(ans[i]), 1);
	}
	a--; b--;

	ll x = 0, y = 0;
	while(b){
		ans[x][y] = 1;
		if(y < 98) y += 2;
		else{
			y = 0;
			x += 2;
		}
		b--;
	}
	x = 99, y = 0;
	while(a){
		ans[x][y] = 0;
		if(y < 98) y += 2;
		else{
			y = 0;
			x -= 2;
		}
		a--;
	}
	
	cosp(100); co(100);
	rep(i, 100){
		rep(j, 100){
			if(ans[i][j] == 0) cout << '.';
			else cout << '#';
		}
		cout << endl;
	}

	return 0;
}
