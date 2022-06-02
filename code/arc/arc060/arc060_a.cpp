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
using Pld = pair<ld, ld>;
using Vec = vector<ll>;
using VecP = vector<P>;
using VecB = vector<bool>;
using VecC = vector<char>;
using VecD = vector<ld>;
using VecS = vector<string>;
using VecVec = vector<Vec>;
using Graph = vector<VecP>;
template <typename T>
using Vec1 = vector<T>;
template <typename T>
using Vec2 = vector<Vec1<T> >;
#define REP(i, m, n) for(ll (i) = (m); (i) < (n); ++(i))
#define REPN(i, m, n) for(ll (i) = (m); (i) <= (n); ++(i))
#define REPR(i, m, n) for(ll (i) = (m)-1; (i) >= (n); --(i))
#define REPNR(i, m, n) for(ll (i) = (m); (i) >= (n); --(i))
#define rep(i, n) REP(i, 0, n)
#define repe(i, n) REPN(i, 0, n)
#define repn(i, n) REPN(i, 1, n)
#define repr(i, n) REPR(i, n, 0)
#define repnr(i, n) REPNR(i, n, 1)
#define all(s) (s).begin(), (s).end()
#define pb push_back
#define mp make_pair
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
template <typename T>
void coVec(const Vec1<T> &v){for(T i : v) cosp(i); cout << endl;}
template <typename T>
void ce(const T n){cerr << n << endl;}
template <typename T>
void cesp(const T n){cerr << n << ' ';}
template <typename T>
void ceVec(const Vec1<T> &v){for(T i : v) cesp(i); cerr << endl;}
void sonic(){ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);}
void setp(const ll n){cout << fixed << setprecision(n);}
const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const ld PI = acos(-1);
const ld EPS = 1e-11;

int main(void){
	ll n, a;
	cin >> n >> a;
	Vec x(n+1);
	repn(i, n) cin >> x[i];

	ll zero = 0;
	repn(i, n) x[i] -= a;

	Vec2<ll> dp1(n+1, Vec(2505)), dp2(n+1, Vec(2505));
	dp1[0][0] = 1, dp2[0][0] = 1;
	repn(i, n){
		rep(j, 2505) dp1[i][j] = dp1[i-1][j];
		rep(j, 2505) dp2[i][j] = dp2[i-1][j];
		if(x[i] == 0) zero++;
		else if(x[i] > 0){
			rep(j, 2505) if(j >= x[i]) dp1[i][j] += dp1[i-1][j-x[i]]; 
		}else{
			rep(j, 2505) if(j >= -x[i]) dp2[i][j] += dp2[i-1][j+x[i]];
		}
	}

	ll ans = 0;
	rep(i, 2505) ans += dp1[n][i]*dp2[n][i];

	ans <<= zero;
	ans--;
	co(ans);

	return 0;
}
