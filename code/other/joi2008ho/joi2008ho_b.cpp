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
	string s, t;
	cin >> s >> t;

	ll ans = 0;
	rep(i, s.length()){
		ll cnt = 0;
		rep(j, min((ll)s.length()-i, (ll)t.length())){
			if(s[i+j] == t[j]) ans = max(ans, ++cnt);
			else cnt = 0;
		}
	}
	rep(i, t.length()){
		ll cnt = 0;
		rep(j, min((ll)t.length()-i, (ll)s.length())){
			if(s[j] == t[i+j]) ans = max(ans, ++cnt);
			else cnt = 0;
		}
	}
	co(ans);

	return 0;
}
