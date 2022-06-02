/*
confirm 0LL and 1LL
confirm cornercases such as 0
confirm times of cin < 10^6
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using P = pair<ll, ll>;
using Vec = vector<ll>;
using VecP = vector<P>;
using VecB = vector<bool>;
using VecC = vector<char>;
using VecD = vector<double>;
using VecS = vector<string>;
using VecVec = vector<Vec>;
using Tree = vector<VecP>;
template <typename T>
using Vec1 = vector<T>;
template <typename T>
using Vec2 = vector<vector<T> >;
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

Vec fac, inv, finv;

ll PowMod(ll a, ll n){
	if(n == 1) return a;
	if(!(n%2)) return PowMod(a*a%MOD, n/2);
	return a*PowMod(a*a%MOD, n/2)%MOD;
}

void fill_fac(ll n){
	fac.resize(n+1);
	fac[0] = 1;
	repn(i, n) fac[i] = (fac[i-1]*i)%MOD;
}

void fill_inv(int n){
	inv.resize(n+1);
	inv[0] = 1;
	repn(i, n) inv[i] = PowMod(i, MOD-2);
}

void fill_finv(int n){
	fill_inv(n);
	finv.resize(n+1);
	finv[0] = 1;
	repn(i, n) finv[i] = (finv[i-1]*inv[i])%MOD;
}

ll combi(int n, int k){
	return fac[n]*finv[k]%MOD*finv[n-k]%MOD;
}

int main(void){
	ll n, k;
	cin >> n >> k;
	Vec a(n);
	rep(i, n) cin >> a[i];
	sort(all(a));
	fill_fac(n);
	fill_finv(n);

	ll ans = 0;
	repn(i, n){
		if(n-i < k-1) break;
		ans += a[n-i]*combi(n-i, k-1);
		ans %= MOD;
	}
	repn(i, n){
		if(n-i < k-1) break;
		ans -= a[i-1]*combi(n-i, k-1);
		ans %= MOD;
		ans += MOD;
		ans %= MOD;
	}
	co(ans);

	return 0;
}
