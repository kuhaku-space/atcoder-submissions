#include <bits/stdc++.h>
using namespace std;
using ll = long long ;
using P = pair<ll, ll>;
using Vec = vector<ll>;
using VecP = vector<P>;
#define REP(i, m, n) for(ll (i) = (m); (i) < (n); ++(i))
#define REPN(i, m, n) for(ll (i) = (m); (i) <= (n); ++(i))
#define REPR(i, m, n) for(ll (i) = (m); (i) >= (n); --(i))
#define rep(i, n) REP(i, 0, n)
#define repn(i, n) REPN(i, 1, n)
#define repr(i, n) REPR(i, n, 0)
#define repnr(i, n) REPR(i, n, 1)
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
bool flg = false;

void query(ll n, string s){
	if(n == s.length()) flg = true;
	string t;
	t = s.substr(n, 5);
	if(t == "dream") query(n+5, s);
	if(t == "erase") query(n+5, s);
	t = s.substr(n, 6);
	if(t == "eraser") query(n+6, s);
	t = s.substr(n, 7);
	if(t == "dreamer") query(n+7, s);
}

int main(void){
	string s;
	cin >> s;

	query(0, s);
	if(flg) puts("YES");
	else puts("NO");

	return 0;
}
