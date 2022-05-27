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
	Vec a(n), b(n);
	rep(i, n) cin >> a[i];
	rep(i, n) cin >> b[i];

	ll ans = LINF;
	rep(bit, 1LL << n){
		bitset<18> bits(bit);
		VecP c(n);
		Vec d(n);
		rep(i, n){
			if(!bits[i]) c[i] = {a[i], i};
			else c[i] = {b[i], i};
		}
		rep(i, n) d[i] = c[i].fs;
		sort(all(d));

		ll cnt = 0;
		bool flg;
		rep(i, n){
			flg = false;
			REP(j, i, n){
				if(d[i] == c[j].fs && abs(i-c[j].sc)%2 == bits[c[j].sc]){
					REPNR(k, j, i+1){
						swap(c[k], c[k-1]);
						cnt++;
					}
					flg = true;
					break;
				}
			}
			if(!flg) break;
		}
		if(flg) chmin(ans, cnt);
	}

	if(ans != LINF) co(ans);
	else co(-1);

	return 0;
}
