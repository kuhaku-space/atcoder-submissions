#include <bits/stdc++.h>
using namespace std;

#define FOR(i, m, n) for(int (i) = (m); (i) < (n); (i)++)
#define FORN(i, m, n) for(int (i) = (m); (i) <= (n); (i)++)
#define FORR(i, m, n) for(int (i) = (m); (i) >= (n); (i)--)
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
#define fs first
#define sc second
typedef long long ll;
typedef pair<int, int> P;
typedef vector<int> Vec;

const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;
const int MAX_N = 1e6+1;

ll fac[MAX_N] = {};
ll inv[MAX_N] = {};
ll finv[MAX_N] = {};

ll PowMod(ll a, ll n){
	if(n == 1) return a;
	if(!(n%2)) return PowMod(a*a%MOD, n/2);
	return a*PowMod(a*a%MOD, n/2)%MOD;
}

void fill_fac(int n){
	fac[0] = 1;
	repn(i, n) fac[i] = (fac[i-1]*i)%MOD;
}

void fill_inv(int n){
	inv[0] = 1;
	repn(i, n) inv[i] = PowMod(i, MOD-2);
}

void fill_finv(int n){
	fill_inv(n);

	finv[0] = 1;
	repn(i, n) finv[i] = (finv[i-1]*inv[i])%MOD;
}

int init(int n){
	fill_fac(n);
	fill_finv(n);
}

ll combi(int n, int k){
	return fac[n]*finv[k]%MOD*finv[n-k]%MOD;
}

int main(void){
	int x, y;
	cin >> x >> y;

	if((x+y)%3 || x*2 < y || y*2 < x){
		co(0);
		return 0;
	}

	int tmp = (x+y)/3;
	x -= tmp; y -= tmp;

	init(x+y);
	co(combi(x+y, x));

	return 0;
}
