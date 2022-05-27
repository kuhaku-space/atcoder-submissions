/*
confirm 0LL and 1LL
confirm cornercases such as 0
confirm times of cin < 10^6
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using P = pair<ll, ll>;
using Vec = vector<ll>;
using VecP = vector<P>;
using VecB = vector<bool>;
using VecC = vector<char>;
using VecS = vector<string>;
using VecVec = vector<Vec>;
using Tree = vector<VecP>;
#define REP(i, m, n) for(ll (i) = (m); (i) < (n); ++(i))
#define REPN(i, m, n) for(ll (i) = (m); (i) <= (n); ++(i))
#define REPR(i, m, n) for(ll (i) = (m)-1; (i) >= (n); --(i))
#define REPNR(i, m, n) for(ll (i) = (m); (i) >= (n); --(i))
#define rep(i, n) REP(i, 0, n)
#define repn(i, n) REPN(i, 1, n)
#define repr(i, n) REPR(i, n, 0)
#define repnr(i, n) REPNR(i, n, 1)
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
template <typename T>
void co(const T n){cout << n << endl;}
template <typename T>
void cosp(const T n){cout << n << ' ';}
void coVec(const Vec &v){for(ll i : v) cosp(i); cout << endl;}
void sonic(){ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);}
void setp(const ll n){cout << fixed << setprecision(n);}
const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;

ll PowMod(ll a, ll n){
	if(n == 1) return a;
	if(!(n%2)) return PowMod(a*a%MOD, n/2);
	return a*PowMod(a*a%MOD, n/2)%MOD;
}

ll inv(ll a){
	return PowMod(a, MOD-2);
}

int main(void){
	ll n;
	cin >> n;
	Vec x(n), d(n-1);
	rep(i, n) cin >> x[i];
	rep(i, n-1) d[i] = x[i+1]-x[i];
	ll p = 1;
	repn(i, n-1){
		p *= i;
		p %= MOD;
	}
	Vec c(n);
	rep(i, n){
		c[i] = inv(i+1);
		if(i) c[i] += c[i-1];
		c[i] %= MOD;
	}
	ll ans = 0;
	rep(i, n-1){
		ans += d[i]*c[i]%MOD*p%MOD;
		ans %= MOD;
	}
	co(ans);

	return 0;
}
