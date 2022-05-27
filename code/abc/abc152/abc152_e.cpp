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
using Tree = vector<VecP>;
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

	Vec pn;
	pn.pb(2);

	REP(num, 3, 1e4){
		bool flg = true;
		for(ll i : pn){
			if(num%i == 0){
				flg = false;
				break;
			}
			if(i*i > num) break;
		}
		if(flg) pn.pb(num);
	}

	unordered_map<ll, ll> ump;
 
	rep(i, n){
		ll b = a[i];
		for(ll j : pn){
			if(j*j > b){
				if(b != 1) chmax(ump[b], 1LL);
				break;
			}
			if(b%j) continue;
			ll cnt = 0;
			while(b%j == 0){
				cnt++;
				b /= j;
			}
			chmax(ump[j], cnt);
		}
	}

	ll ans = 0;
	rep(i, n){
		ll b = a[i], sum = 1;
		for(P j : ump){
			ll cnt = 0;
			while(b%j.fs == 0){
				cnt++;
				b /= j.fs;
			}
			rep(k, j.sc-cnt){
				sum *= j.fs;
				sum %= MOD;
			}
		}
		ans += sum;
		ans %= MOD;
	}
	co(ans);

	return 0;
}
