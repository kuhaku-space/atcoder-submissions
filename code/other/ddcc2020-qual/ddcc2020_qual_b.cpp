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
	ll n;
	cin >> n;
	Vec a(n);
	rep(i, n) cin >> a[i];
	ll sum = 0;
	rep(i, n) sum += a[i];

	ll dif = 0;
	ll s = 0;
	rep(i, n){
		s += a[i]*2;
		if(s < sum) dif = sum-s;
		else{
			dif = min(dif, s-sum);
			break;
		}
	}

	co(dif);

	return 0;
}
