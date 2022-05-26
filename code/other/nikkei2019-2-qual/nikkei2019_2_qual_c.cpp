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
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;
const int MAX_N = 1e5;
int main(void){
	int n;
	cin >> n;

	vector<P> a(n);
	vector<P> b(n);
	rep(i, n) cin >> a[i].fs;
	rep(i, n) cin >> b[i].fs;
	rep(i, n) a[i].sc = b[i].sc = i;
	sort(all(a)); sort(all(b));

	rep(i, n) if(a[i].fs > b[i].fs) return puts("No"), 0;
	rep(i, n-1) if(a[i+1].fs <= b[i].fs) return puts("Yes"), 0;

	vector<int> cr(n);
	rep(i, n) cr[a[i].sc] = b[i].sc;
	int cnt = 0, x = 0;
	do{
		cnt++;
		x = cr[x];
	}while(x);
	puts(cnt == n ? "No" : "Yes");

	return 0;
}
