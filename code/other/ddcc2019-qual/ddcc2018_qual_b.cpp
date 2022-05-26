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
typedef vector<int> Vec;

const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;
int n;

bool inner(int x, int y){
	if((x+y)*2 >= n && (x+y)*2 <= n*3 && (x-y)*2 >= -n && (x-y)*2 <= n) return true;
	else return false;
}

bool corner(int k){
	if(inner(k/n, k%n) && inner(k/n, k%n+1) && inner(k/n+1, k%n) && inner(k/n+1, k%n+1)) return true;
	else return false;
}

int main(void){
	cin >> n;

	int ans = 0;
	rep(i, n*n) if(corner(i)) ans++;
	co(ans);

	return 0;
}
