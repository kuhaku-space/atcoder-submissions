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
	ll h, w, d;
	cin >> h >> w >> d;

	vector<P> b(h*w+1);
	Vec csum(h*w+1);
	rep(i, h){
		rep(j, w){
			ll a;
			cin >> a;
			b[a] = mp(i, j);
		}
	}

	repn(i, h*w){
		if(i >= d) csum[i] = abs(b[i].fs-b[i-d].fs)+abs(b[i].sc-b[i-d].sc)+csum[i-d];
	}

	ll q;
	cin >> q;
	rep(i, q){
		ll l, r, ans = 0;
		cin >> l >> r;
		co(csum[r]-csum[l]);
	}

	return 0;
}
