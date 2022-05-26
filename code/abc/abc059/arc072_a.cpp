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
#define fs first
#define sc second

const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;

int main(void){
	ll n;
	cin >> n;
	Vec a(n);
	rep(i, n) cin >> a[i];

	ll ans = LINF, sum = 0, b = 0, c = 0, sign = 1;
	rep(i, n){
		sum += a[i];
		if(sum/sign <= 0){
			b += 1-sum/sign;
			sum = sign;
		}
		sign *= -1;
	}
	ans = min(ans, b);
	sum = 0, sign = -1;
	rep(i, n){
		sum += a[i];
		if(sum/sign <= 0){
			c += 1-sum/sign;
			sum = sign;
		}
		sign *= -1;
	}
	ans = min(ans, c);
	co(ans);

	return 0;
}
