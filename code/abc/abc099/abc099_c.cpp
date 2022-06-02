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
#define mt make_tuple
#define fs first
#define sc second

const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;
const ll MAX_N = 1e5;

Vec t(MAX_N+1, LINF);

int main(void){
	ll n;
	cin >> n;

	Vec a;
	a.pb(1);
	ll m = 6;
	while(m <= n){
		a.pb(m);
		m *= 6;
	}
	m = 9;
	while(m <= n){
		a.pb(m);
		m *= 9;
	}
	sort(all(a));

	ll cnt = 1;
	for(ll i : a) t[i] = cnt;
	while(t[n] == LINF){
		cnt++;
		repnr(i, n){
			if(t[i] != LINF){
				for(ll j : a){
					if(i+j > n) break;
					t[i+j] = min(t[i+j], cnt);
				}
			}
		}
	}
	co(t[n]);

	return 0;
}
