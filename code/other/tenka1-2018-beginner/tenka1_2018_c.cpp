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
	ll n;
	cin >> n;
	Vec a(n);
	rep(i, n) cin >> a[i];
	sort(all(a));

	Vec b(n);
	ll l = 0, r = n-1;
	rep(i, n){
		if(i%2){
			b[i] = a[l];
			l++;
		}else{
			b[i] = a[r];
			r--;
		}
	}
	ll ans1 = 0, mini1 = LINF;
	repn(i, n-1){
		mini1 = min(mini1, abs(b[i]-b[i-1]));
		ans1 += abs(b[i]-b[i-1]);
	}
	if(mini1 < abs(b[n-1]-b[0])) ans1 += abs(b[n-1]-b[0])-mini1;
	l = 0, r = n-1;
	rep(i, n){
		if(i%2){
			b[i] = a[r];
			r--;
		}else{
			b[i] = a[l];
			l++;
		}
	}
	ll ans2 = 0, mini2 = LINF;
	repn(i, n-1){
		mini2 = min(mini2, abs(b[i]-b[i-1]));
		ans2 += abs(b[i]-b[i-1]);
	}
	if(mini2 < abs(b[n-1]-b[0])) ans2 += abs(b[n-1]-b[0])-mini2;
	co(max(ans1, ans2));

	return 0;
}
