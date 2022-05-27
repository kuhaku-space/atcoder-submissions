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
void coVec(const Vec &v){for(ll i : v) cosp(i); cout << endl;}
ll in(){ll x; cin >> x; return x;}
void sonic(){ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);}
void setp(const ll n){cout << fixed << setprecision(n);}
const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const ld PI = acos(-1);
const ld EPS = 1e-11;

int main(void){
	ll n;
	cin >> n;

	Vec2<ll> dp(n, Vec(4));

	rep(i, n){
		if(!i){
			rep(j, 4) dp[i][j] = 1;
			continue;
		}

		rep(j, 4){
			rep(k, 4)  dp[i][j] += dp[i-1][k];
			if(i >= 2){
				if(j == 1) dp[i][j] -= dp[i-2][0]+dp[i-2][2];
				if(j == 2) dp[i][j] -= dp[i-2][0];
			}
			if(i >= 3){
				if(j == 1) dp[i][j] -= dp[i-3][0]*3;
				if(j == 2) dp[i][j] += dp[i-3][2];
			}

			dp[i][j] %= MOD;
		}
	}

	ll ans = 0;
	rep(i, 4) ans += dp[n-1][i];
	while(ans < 0) ans += MOD;
	ans %= MOD;
	co(ans);

	return 0;
}
