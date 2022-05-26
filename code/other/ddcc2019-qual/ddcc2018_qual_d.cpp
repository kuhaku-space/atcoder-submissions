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

inline ll mod(ll a, ll m){
	return (a%m+m)%m;
}

ll extGCD(ll a, ll b, ll &x, ll &y){
	if(b == 0){
		x = 1, y = 0;
		return a;
	}

	ll d = extGCD(b, a%b, y, x);
	y -= a/b*x;
	return d;
}
P ChineseRem(const Vec &b, const Vec &m) {
  ll r = 0, M = 1;
  rep(i, b.size()){
    ll p, q;
    ll d = extGCD(M, m[i], p, q);
    if((b[i]-r)%d != 0) return mp(0, -1);
    ll tmp = (b[i]-r)/d*p%(m[i]/d);
    r += M*tmp;
    M *= m[i]/d;
  }
  return mp(mod(r, M), M);
}

bool check(ll n, const Vec a, const Vec m){
	rep(i, a.size()){
		ll sum = 0, t = n;
		while(t > 0){
			sum += t%(m[i]+1);
			t /= m[i]+1;
		}
		if(sum != a[i]) return false;
	}
	return true;
}

int main(void){
	Vec a, b, m;
	FORN(i, 2, 30){
		ll t;
		cin >> t;
		a.pb(t);
		b.pb(t%(i-1));
		m.pb(i-1);
	}

	P ans = ChineseRem(b, m);
	if(ans.sc == -1 || ans.fs > 1e12 || !check(ans.fs, a, m)) puts("invalid");
	else co(ans.fs);
	return 0;
}
