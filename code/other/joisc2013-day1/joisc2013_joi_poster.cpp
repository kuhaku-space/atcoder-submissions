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
	ll n, w, h;
	cin >> n >> w >> h;
	VecP s(n);
	rep(i, n) cin >> s[i].fs >> s[i].sc;

	ll ans = 0;
	for(P a : s){
		for(P b : s){
			if(a == b) continue;
			double r1 = sqrt(pow(a.fs-b.fs, 2)+pow(a.sc-b.sc, 2));
			if(a.fs+r1 > w || a.fs-r1 < 0) continue;
			if(a.sc+r1 > h || a.sc-r1 < 0) continue;
			for(P c : s){
				if(a == c || b == c) continue;
				for(P d : s){
					if(a == d || b == d || c == d) continue;
					double r2 = sqrt(pow(c.fs-d.fs, 2)+pow(c.sc-d.sc, 2));
					if(c.fs+r2 > w || c.fs-r2 < 0) continue;
					if(c.sc+r2 > h || c.sc-r2 < 0) continue;
					double dist = sqrt(pow(a.fs-c.fs, 2)+pow(a.sc-c.sc, 2));
					if(r1 > r2+dist+EPS) ans++;
				}
			}
		}
	}
	co(ans);

	return 0;
}
