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
void coVec(const Vec &v){for(ll i : v) cosp(i); cout << endl;}
template <typename T>
void coVec(const Vec1<T> &v){for(T i : v) cosp(i); cout << endl;}
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
	Vec a(n), b(n);
	rep(i, n) cin >> a[i];
	rep(i, n) cin >> b[i];

	priority_queue<P> que;
	rep(i, n) if(a[i] != b[i]) que.push({b[i], i});
	ll ans = 0;
	while(!que.empty()){
		P p = que.top(); que.pop();
		ll s = b[(p.sc-1+n)%n]+b[(p.sc+1)%n];
		ll t = (b[p.sc]-max(b[(p.sc-1+n)%n], b[(p.sc+1)%n]))/s+1;
		if(b[p.sc]-t*s >= a[p.sc]){
			b[p.sc] -= t*s;
			ans += t;
		}else{
			t = (b[p.sc]-a[p.sc])/s;
			if(!t){
				co(-1);
				return 0;
			}
			b[p.sc] -= t*s;
			ans += t;
		}
		if(b[p.sc] > a[p.sc]){
			que.push({b[p.sc], p.sc});
		}
	}
	co(ans);

	return 0;
}
