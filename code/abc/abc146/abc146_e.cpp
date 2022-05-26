#include <bits/stdc++.h>
using namespace std;
using ll = long long ;
using P = pair<ll, ll>;
using Vec = vector<ll>;
#define FOR(i, m, n) for(ll (i) = (m); (i) < (n); (i)++)
#define FORN(i, m, n) for(ll (i) = (m); (i) <= (n); (i)++)
#define FORR(i, m, n) for(ll (i) = (m); (i) >= (n); (i)--)
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
	ll n, k;
	cin >> n >> k;
	Vec a(n+1);
	repn(i, n) cin >> a[i];
	Vec s(n+1);
	repn(i, n) s[i] = s[i-1]+a[i];

	map<ll, ll> mp;
	mp[0] = 1;
	ll ans = 0;
	repn(i, n){
		if(i >= k) mp[(s[i-k]-i+k)%k]--;
		ans += mp[(s[i]-i)%k]++;
	}
	co(ans);

	return 0;
}
