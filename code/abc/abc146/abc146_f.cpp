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
	ll n, m;
	cin >> n >> m;
	string s;
	cin >> s;

	ll cnt = 0;
	rep(i, n){
		if(s[i] == '1') cnt++;
		else cnt = 0;
		if(cnt >= m){
			co(-1);
			return 0;
		}
	}

	Vec ans;
	repnr(i, n){
		repnr(j, m){
			if(j >= i){
				ans.pb(i);
				i = 0;
				break;
			}else if(s[i-j] == '0'){
				ans.pb(j);
				i = i-j+1;
				break;
			}
		}
	}

	ll si = ans.size();
	rep(i, si){
		cosp(ans[si-1-i]);
	}
	cout << endl;

	return 0;
}
