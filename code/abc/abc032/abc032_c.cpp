//confilm 0LL and 1LL
//confilm cornercase such as 0
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
template <typename T> bool chmax(T &a, const T& b){if(a < b){a = b; return true;} return false;}
template <typename T> bool chmin(T &a, const T& b){if(a > b){a = b; return true;} return false;}
const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;

int main(void){
	ll n, k;
	cin >> n >> k;
	Vec a(n);
	rep(i, n) cin >> a[i];

	bool flg = false;
	rep(i, n) flg |= a[i] == 0;
	if(flg){
		co(n);
		return 0;
	}

	ll ans = 0, p = 1;
	ll l = 0, r = 0;
	while(l < n){
		if(p <= k && r < n || l == r){
			p *= a[r++];
			if(p <= k) chmax(ans, r-l);
		}else{
			p /= a[l++];
			if(p <= k) chmax(ans, r-l);
		}
	}
	co(ans);

	return 0;
}