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
template <typename T>
using Vec3 = vector<Vec2<T> >;
#define REP(i, m, n) for(ll (i) = (m); (i) < (n); ++(i))
#define REPN(i, m, n) for(ll (i) = (m); (i) <= (n); ++(i))
#define REPR(i, m, n) for(ll (i) = (m)-1; (i) >= (n); --(i))
#define REPNR(i, m, n) for(ll (i) = (m); (i) >= (n); --(i))
#define rep(i, n) REP(i, 0, n)
#define repn(i, n) REPN(i, 1, n)
#define repe(i, n) REPN(i, 0, n)
#define repr(i, n) REPR(i, n, 0)
#define repnr(i, n) REPNR(i, n, 1)
#define reper(i, n) REPNR(i, n, 0)
#define all(s) (s).begin(), (s).end()
#define pb push_back
#define mp make_pair
#define fs first
#define sc second
template <typename T>
bool chmax(T &a, const T b){if(a < b){a = b; return true;} return false;}
template <typename T>
bool chmin(T &a, const T b){if(a > b){a = b; return true;} return false;}
template <typename T>
ll pow2(const T n){return (1LL << n);}
template <typename T>
void cosp(const T n){cout << n << ' ';}
template <typename T>
void co(const T n){cout << n << '\n';}
template <typename T1, typename T2>
void co(pair<T1, T2> p){cout << p.fs << ' ' << p.sc << '\n';}
template <typename T>
void co(const Vec1<T> &v){for(T i : v) cosp(i); cout << '\n';}
template <typename T>
void co(initializer_list<T> v){for(T i : v) cosp(i); cout << '\n';}
template <typename T>
void ce(const T n){cerr << n << endl;}
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
	Vec a(n);
	rep(i, n) cin >> a[i];
	Vec c(4);
	rep(i, n) c[a[i]]++;

	Vec3<Pld> dp(301, Vec2<Pld>(301, Vec1<Pld>(301)));

	dp[c[1]][c[2]][c[3]].sc = 1;

	reper(k, 300){
		reper(j, 300){
			reper(i, 300){
				if(dp[i][j][k].sc == 0.) continue;
				ll s = i+j+k;
				if(i){
					dp[i-1][j][k].fs += (dp[i][j][k].fs+(ld)n/s*dp[i][j][k].sc)*i/s;
					dp[i-1][j][k].sc += dp[i][j][k].sc*i/s;
				}
				if(j){
					dp[i+1][j-1][k].fs += (dp[i][j][k].fs+(ld)n/s*dp[i][j][k].sc)*j/s;
					dp[i+1][j-1][k].sc += dp[i][j][k].sc*j/s;
				}
				if(k){
					dp[i][j+1][k-1].fs += (dp[i][j][k].fs+(ld)n/s*dp[i][j][k].sc)*k/s;
					dp[i][j+1][k-1].sc += dp[i][j][k].sc*k/s;
				}
			}
		}
	}
	setp(15);
	co(dp[0][0][0].fs);

	return 0;
}
