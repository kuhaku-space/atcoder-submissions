//confilm 0LL and 1LL
//confilm cornercases such as 0
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using P = pair<ll, ll>;
using Vec = vector<ll>;
using VecP = vector<P>;
using VecB = vector<bool>;
using VecC = vector<char>;
using VecVec = vector<Vec>;
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
template <typename T>
bool chmax(T &a, const T& b){if(a < b){a = b; return true;} return false;}
template <typename T>
bool chmin(T &a, const T& b){if(a > b){a = b; return true;} return false;}
void sonic(){ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);}
const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;

int main(void){
	ll n;
	cin >> n;
	string s;
	cin >> s;
	Vec cntW(n), cntB(n);
	rep(i, n){
		if(s[i] == '#') cntB[i]++;
		if(i) cntB[i] += cntB[i-1];
	}
	repr(i, n){
		if(s[i] == '.') cntW[i]++;
		if(i < n-1) cntW[i] += cntW[i+1];
	}

	ll ans = min(cntW[0], cntB[n-1]);
	rep(i, n-1) chmin(ans, cntW[i+1]+cntB[i]);
	co(ans);

	return 0;
}
