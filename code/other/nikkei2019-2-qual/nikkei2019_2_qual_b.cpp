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
typedef pair<int, int> P;

const ll INF = 1e9+1;
const ll LINF = 1e18+1;
//const ll MOD = 1e9+7;
const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;
const int MAX_N = 1e5;
int dist[MAX_N] = {};

int main(void){
	int n;
	cin >> n;

	vector<int> d(n);
	rep(i, n){
		cin >> d[i];
		dist[d[i]]++;
	}

	if(d[0] != 0 || dist[0] != 1){
		co(0);
		return 0;
	}
	rep(i, n){
		if(!dist[i]){
			FOR(j, i, n){
				if(dist[j]){
					co(0);
					return 0;
				}
			}
			break;
		}
	}
	
	ll ans = 1;
	repn(i, n-1){
		if(!dist[i]) break;
		rep(j, dist[i]){
			ans *= dist[i-1];
			ans %= MOD;
		}
	}

	co(ans);

	return 0;
}
