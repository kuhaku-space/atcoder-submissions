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
#define REP(i, m, n) for(ll i = (m); (i) < (n); ++(i))
#define REPN(i, m, n) for(ll i = (m); (i) <= (n); ++(i))
#define REPR(i, m, n) for(ll i = (m)-1; (i) >= (n); --(i))
#define REPNR(i, m, n) for(ll i = (m); (i) >= (n); --(i))
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
// constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-11;
const ld PI = acos(-1);

Vec v, w;
VecB fin;
Vec2<ll> dp;

ll f(ll m, ll l){
	// co({m, l});
	if (l < 0) return -LINF;
	if (m >= 512) return max(f(m / 2, l), f(m / 2, l - w[m]) + v[m]);
	if (!fin[m / 2]) f(m / 2, l);
	if(!fin[m]){
		rep(i, 100005) dp[m][i] = dp[m / 2][i];
		rep(i, 100005) if(i - w[m] >= 0) chmax(dp[m][i], dp[m / 2][i - w[m]] + v[m]);
		fin[m] = true;
	}
	return dp[m][l];
}

int main(void){
	ll n;
	cin >> n;
	v.resize(n + 1);
	w.resize(n + 1);
	repn(i, n) cin >> v[i] >> w[i];

	fin.assign(512, false);
	fin[0] = true;
	dp.resize(512);
	rep(i, 512) dp[i].assign(100005, 0);

	ll q;
	cin >> q;
	rep(i, q){
		ll m, l;
		cin >> m >> l;
		co(f(m, l));
	}

	return 0;
}
