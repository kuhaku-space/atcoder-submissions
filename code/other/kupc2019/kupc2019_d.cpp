#include <bits/stdc++.h>
using namespace std;

#define FOR(i, m, n) for(int (i) = (m); (i) < (n); (i)++)
#define rep(i, n) FOR(i, 0, n)
#define co(n) cout << (n) << endl
#define cosp(n) cout << (n) << ' '
#define all(s) (s).begin(), (s).end()
#define pb push_back
#define mp make_pair
#define fs first
#define sc second
typedef long long ll;
typedef pair<int, int> P;

const ll INF = 1e9+5;
const ll LINF = 1e18+1;
//const ll MOD = 1e9+7;
const ll MOD = 998244353;
const ll MAX_N = 1e5+5;

ll fac[MAX_N*2] = {};
ll inv[MAX_N] = {};
ll finv[MAX_N] = {};

ll PowMod(ll a, ll n){
	if(n == 1) return a;
	if(!(n%2)) return PowMod(a*a%MOD, n/2);
	return a*PowMod(a*a%MOD, n/2)%MOD;
}

ll fill_fac(int n){
	fac[0] = 1;
	rep(i, n) fac[i+1] = (fac[i]*(i+1))%MOD;
}

ll fill_inv(int n){
	rep(i, n+1) inv[i] = PowMod(i, MOD-2);
}

ll fill_finv(int n){
	finv[1] = 1;
	FOR(i, 2, n+1) finv[i] = (finv[i-1]*inv[i])%MOD;
}

ll catalan(int n){
	return (fac[2*n]*finv[n+1]%MOD)*finv[n]%MOD;
}

int main(void){
	int n;
	cin >> n;

	fill_fac(2*n);
	fill_inv(n+1);
	fill_finv(n+1);

	string s;
	cin >> s;

	int cnt = 1;
	ll ans = 1;
	rep(i, n){
		if(!i) continue;
		if(s[i] == s[i-1]) cnt++;
		else{
			ans *= catalan(cnt);
			ans %= MOD;
			cnt = 1;
		}
	}
	ans *= catalan(cnt);
	ans %= MOD;

	co(ans);

	return 0;
}
