//confirm 0LL and 1LL
//confirm cornercases such as 0
//confirm times of cin < 1^6
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using P = pair<ll, ll>;
using Vec = vector<ll>;
using VecP = vector<P>;
using VecB = vector<bool>;
using VecC = vector<char>;
using VecVec = vector<Vec>;
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
void co(T n){cout << n << endl;}
template <typename T>
void cosp(T n){cout << n << ' ';}
void coVec(const Vec &v){for(ll i : v) cosp(i); cout << endl;}
void sonic(){ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);}
void setp(ll n){cout << fixed << setprecision(n);}
const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;

int main(void){
	ll n;
	cin >> n;
	VecP p(n+1);
	repn(i, n){
		cin >> p[i].fs;
		p[i].sc = i;
	}
	sort(all(p));

	Vec noSwap1(n), noSwap2(n+1);
	repn(i, n) if(i != 1 && p[i].sc > p[i].sc) noSwap1[i] = noSwap1[i-1]+1;
	repnr(i, n) if(i != n && p[i].sc < p[i+1].sc) noSwap2[i] = noSwap2[i+1]+1;
	ll ans = 0;
	repn(i, n) chmax(ans, noSwap1[i]+noSwap2[i]);
	ans = n-1-ans;
	co(ans);

	return 0;
}
