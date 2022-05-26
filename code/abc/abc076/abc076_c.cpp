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
	string s, t;
	cin >> s >> t;
	ll s_len = s.length(), t_len = t.length();
	if(s_len < t_len){
		puts("UNRESTORABLE");
		return 0;
	}
	bool flg = true;
	repr(i, s_len-t_len){
		flg = true;
		rep(j, t_len){
			if(s[i+j] != t[j] && s[i+j] != '?'){
				flg = false;
				break;
			}
		}
		if(flg){
			rep(j, s_len){
				if(j >= i && j < i+t_len) cout << t[j-i];
				else if(s[j] == '?') cout << 'a';
				else cout << s[j];
			}
			cout << endl;
			return 0;
		}
	}

	puts("UNRESTORABLE");
	return 0;
}
