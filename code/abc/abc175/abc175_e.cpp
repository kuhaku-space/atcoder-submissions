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
template <typename T>
using Vec2 = vector<vector<T>>;
#define REP(i, m, n) for(ll i = (m); i < (n); ++i)
#define REPN(i, m, n) for(ll i = (m); i <= (n); ++i)
#define REPR(i, m, n) for(ll i = (m)-1; i >= (n); --i)
#define REPNR(i, m, n) for(ll i = (m); i >= (n); --i)
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
void co(const vector<T> &v){for(T i : v) cosp(i); co();}
template <typename T>
void co(initializer_list<T> v){for(T i : v) cosp(i); co();}
void ce(void){cerr << '\n';}
template <typename T>
void ce(const T n){cerr << n << '\n';}
template <typename T>
void cesp(const T n){cerr << n << ' ';}
template <typename T>
void ce(initializer_list<T> v){for(T i : v) cesp(i); ce();}
void sonic(){ios::sync_with_stdio(false); cin.tie(0);}
void setp(const ll n){cout << fixed << setprecision(n);}
constexpr int INF = 1e9+1;
constexpr ll LINF = 1e18+1;
constexpr ll MOD = 1e9+7;
// constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-11;
const double PI = acos(-1);

ll dp[3010][3010][4] = {};

int main(void){
	ll r, c, k;
	cin >> r >> c >> k;
	Vec x(k), y(k), v(k);
	rep(i, k) cin >> x[i] >> y[i] >> v[i];

	map<P, ll> item;
	rep(i, k) item[{x[i] - 1, y[i] - 1}] = v[i];

	rep(i, r) {
		rep(j, c) {
			bool flg = (item.find({i, j}) != item.end());
			ll t = 0;
			if (flg) t = item[{i, j}];
			rep(k, 4) {
				if (!i && !j) {
					dp[i][j][1] = t;
					continue;
				}

				if (!j) {
					chmax(dp[i][j][k], dp[i - 1][j][k]);
					chmax(dp[i][j][1], dp[i - 1][j][k] + t);
					continue;
				}

				if (!i) {
					chmax(dp[i][j][k], dp[i][j - 1][k]);
					if (k) chmax(dp[i][j][k], dp[i][j - 1][k - 1] + t);
					continue;
				}

				chmax(dp[i][j][k], dp[i - 1][j][k]);
				chmax(dp[i][j][1], dp[i - 1][j][k] + t);
				chmax(dp[i][j][k], dp[i][j - 1][k]);
				if (k) chmax(dp[i][j][k], dp[i][j - 1][k - 1] + t);
			}
		}
	}

	ll ans = 0;
	rep(i, 4) chmax(ans, dp[r - 1][c - 1][i]);
	co(ans);

	return 0;
}
