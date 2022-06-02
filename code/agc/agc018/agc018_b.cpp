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
	ll n, m;
	cin >> n >> m;

	Vec2<ll> a(n, Vec(m));
	rep(i, n) rep(j, m) cin >> a[i][j];

	ll l = 0, r = n;
	while(r-l > 1){
		ll mid = (l+r)/2;
		Vec pos(n);
		bool flg;
		VecB sports(m+1, true);
		while(true){
			flg = true;
			Vec cnt(m+1);
			rep(i, n) cnt[a[i][pos[i]]]++;
			repn(i, m) flg &= (cnt[i] <= mid);
			if(flg) break;
			repn(i, m) sports[i] = sports[i]&(cnt[i] <= mid);
			bool flag = false;
			repn(i, m) flag |= sports[i];
			if(!flag) break;
			rep(i, n) while(!sports[a[i][pos[i]]]) pos[i]++;
			rep(i, n) if(pos[i] >= m) break;
		}
		if(flg) r = mid;
		else l = mid;
	}
	co(r);

	return 0;
}
