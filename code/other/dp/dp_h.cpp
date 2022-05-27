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

VecS s;
VecVec dp;

int main(void){
	ll h, w;
	cin >> h >> w;
	s.resize(h);
	rep(i, h) cin >> s[i];
	dp.resize(h);
	rep(i, h) dp[i].resize(w);

	dp[0][0] = 1;
	rep(i, h) rep(j, w){
		if(s[i][j] == '.'){
			if(i) dp[i][j] += dp[i-1][j];
			if(j) dp[i][j] += dp[i][j-1];
			dp[i][j] %= MOD;
		}
	}
	co(dp[h-1][w-1]);

	return 0;
}
