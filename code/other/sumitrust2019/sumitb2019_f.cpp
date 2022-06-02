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
	ll t1, t2, a1, a2, b1, b2;
	cin >> t1 >> t2 >> a1 >> a2 >> b1 >> b2;

	ll x1 = t1*a1, x2 = t2*a2, y1 = t1*b1, y2 = t2*b2;
	if(x1+x2 == y1+y2){
		puts("infinity");
		return 0;
	}

	if(x1 < y1){
		swap(x1, y1);
		swap(x2, y2);
	}

	if(x1+x2 > y1+y2){
		co(0);
		return 0;
	}

	ll diff = y1+y2-x1-x2;
	ll ans = (x1-y1)/diff*2+1;
	if((x1-y1)%diff == 0) ans--;
	co(ans);

	return 0;
}
