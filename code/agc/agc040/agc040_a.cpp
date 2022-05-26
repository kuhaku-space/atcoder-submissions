#include <bits/stdc++.h>
using namespace std;

#define FOR(i, m, n) for(int (i) = (m); (i) < (n); (i)++)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FOR(i, 1, n+1)
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
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;

int main(void){
	string s;
	cin >> s;

	ll ans = 0, cnt = 0, num = 0;
	rep(i, s.length()){
		if(s[i] == '<'){
			if(i && s[i-1] == '>'){
				cnt = 0;
			}
			ans += ++cnt;
		}else{
			if(i && s[i-1] == '<'){
				num = cnt;
				cnt = 0;
			}
			if(cnt < num) ans += cnt++;
			else ans += ++cnt;
		}
	}

	co(ans);

	return 0;
}
