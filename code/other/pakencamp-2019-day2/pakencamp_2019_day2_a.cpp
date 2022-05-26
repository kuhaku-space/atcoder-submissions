/*
confirm 0LL and 1LL
confirm cornercases such as 0
confirm times of cin < 10^6
*/
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
void co(const T n){cout << n << endl;}
template <typename T>
void cosp(const T n){cout << n << ' ';}
void coVec(const Vec &v){for(ll i : v) cosp(i); cout << endl;}
void sonic(){ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);}
void setp(ll n){cout << fixed << setprecision(n);}
const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;
const ll N = 100;
const ll K = 4;
const ll Q = 240;
VecVec A(N, Vec(N));
VecVec ANS(N, Vec(N));
VecP QUERY(Q);

void input(){
	ll n, k, q;
	cin >> n >> k >> q;
	rep(i, N) rep(j, N) cin >> A[i][j];
	rep(i, Q) cin >> QUERY[i].fs >> QUERY[i].sc;
}

void solve(){
	Vec cnt(N);
	rep(i, Q) cnt[QUERY[i].sc]++;
	ll maxi = 0, y = 0;
	rep(i, N-5) if(chmax(maxi, cnt[i]+cnt[i+1]+cnt[i+2])) y = i;
	rep(i, N){
		ANS[i][y] = 1;
		ANS[i][y+1] = 2;
		ANS[i][y+2] = 3;
		ANS[i][y+3] = 4;
		ANS[i][y+4] = 1;
		ANS[i][y+5] = 2;
	}
	REPN(j, y+1, y+4){
		ANS[0][j] = 1;
		ANS[N-1][j] = 2;
	}
	rep(j, N){
		if(ANS[0][j]) break;
		rep(i, N) ANS[i][j] = 1;
	}
	repr(j, N){
		if(ANS[0][j]) break;
		rep(i, N) ANS[i][j] = 2;
	}
}

void output(){
	rep(i, N) coVec(ANS[i]);
}

int main(void){
	input();
	solve();
	output();

	return 0;
}
