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
typedef pair<ll, ll> P;
typedef vector<ll> Vec;

const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;

int main(void){
	ll a, b, x;
	cin >> a >> b >> x;

	ll l, r = 1, d = 1;
	while(true){
		if(a*r+b*d > x){
			l = r/10;
			d--;
			break;
		}else if(r >= 1e9){
			co(1000000000);
			return 0;
		}else{
			r *= 10;
			d++;
		}
	}

	while(r-l > 1){
		ll m = (l+r)/2;
		if(a*m+b*d <= x) l = m;
		else r = m;
	}
	co(l);

	return 0;
}
