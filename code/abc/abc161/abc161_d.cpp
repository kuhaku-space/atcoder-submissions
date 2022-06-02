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
void co(void){cout << '\n';}
template <typename T>
void co(const T n){cout << n << '\n';}
template <typename T1, typename T2>
void co(pair<T1, T2> p){cout << p.fs << ' ' << p.sc << '\n';}
template <typename T>
void co(const Vec1<T> &v){for(T i : v) cosp(i); co();}
template <typename T>
void co(initializer_list<T> v){for(T i : v) cosp(i); co();}
template <typename T>
void ce(const T n){cerr << n << endl;}
void sonic(){ios::sync_with_stdio(false); cin.tie(0);}
void setp(const ll n){cout << fixed << setprecision(n);}
constexpr int INF = 1e9+1;
constexpr ll LINF = 1e18+1;
constexpr ll MOD = 1e9+7;
//constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-11;
const ld PI = acos(-1);

ll dp[15][10] = {};
ll k;

string ans(ll x, ll y, ll sum){
	//co({x, y, sum});
	if(x < 0) return "";
	if(y < 9) sum -= dp[x - 1][y + 1];
	if(sum < k) return to_string(y) + ans(x - 1, y + 1, sum + dp[x - 1][y + 1]);
	sum -= dp[x - 1][y];
	if(sum < k) return to_string(y) + ans(x - 1, y, sum + dp[x - 1][y]);
	return to_string(y) + ans(x - 1, y - 1, sum);
}

int main(void){
	cin >> k;

	ll x, y;
	ll sum = 0;
	rep(i, 15){
		rep(j, 10){
			if(i == 0){
				dp[i][j] = 1;
			}else{
				dp[i][j] += dp[i - 1][j];
				if(j > 0) dp[i][j] += dp[i - 1][j - 1];
				if(j < 9) dp[i][j] += dp[i - 1][j + 1];
			}

			if(j) sum += dp[i][j];
			if(sum >= k){
				x = i, y = j;
				break;
			}
		}
		if(sum >= k) break;
	}

	co(ans(x, y, sum));

	return 0;
}
