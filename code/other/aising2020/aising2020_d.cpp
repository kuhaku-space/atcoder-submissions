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

int main(void){
	ll n;
	cin >> n;
	Vec r(n + 1);
	repn(i, n){
		ll t = i;
		ll cnt = 0;
		while(t){
			cnt += t & 1;
			t >>= 1;
		}
		r[i] = r[i % cnt] + 1;
	}
	// co(r);

	string s;
	cin >> s;
	ll cnt = 0;
	rep(i, n) if (s[i] == '1') cnt++;

	Vec p1(n), p2(n);
	repr(i, n){
		if (cnt == 1 || cnt == 0) break;
		if (i == n - 1) p1[i] = 1 % (cnt - 1);
		else
			p1[i] = p1[i + 1] * 2 % (cnt - 1);
	}

	repr(i, n){
		if (i == n - 1) p2[i] = 1;
		else
			p2[i] = p2[i + 1] * 2 % (cnt + 1);
	}

	ll x1 = 0, x2 = 0;
	rep(i, n){
		x1 <<= 1, x2 <<= 1;
		if (s[i] == '1') x1++, x2++;
		if(cnt != 1 && cnt != 0) x1 %= (cnt - 1);
		x2 %= (cnt + 1);
	}

	rep(i, n){
		if(s[i] == '0'){
			co(r[(x2 + p2[i]) % (cnt + 1)] + 1);
		}else{
			if (cnt == 1) co(0);
			else
				co(r[(x1 - p1[i] + cnt - 1) % (cnt - 1)] + 1);
		}
	}

	return 0;
}
