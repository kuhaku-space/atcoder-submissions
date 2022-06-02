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
using VecS = vector<string>;
using VecVec = vector<Vec>;
using Tree = vector<VecP>;
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
void setp(const ll n){cout << fixed << setprecision(n);}
const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;

VecS b;
VecVec c;
ll h, w;

void dfs(ll x, ll y){
	c[x][y] = 1;
	if(x-1 >= 0 && b[x-1][y] != '#' && !c[x-1][y]) dfs(x-1, y);
	if(y-1 >= 0 && b[x][y-1] != '#' && !c[x][y-1]) dfs(x, y-1);
	if(x+1 < h && b[x+1][y] != '#' && !c[x+1][y]) dfs(x+1, y);
	if(y+1 < w && b[x][y+1] != '#' && !c[x][y+1]) dfs(x, y+1);
}

bool is_connected(){
	rep(i, 10) rep(j, 10) if(c[i][j]) return false;
	return true;
}

int main(void){
	cin >> h >> w;
	b.resize(h);
	rep(i, h) cin >> b[i];
	c.resize(h);
	rep(i, h) c[i].resize(w);

	rep(i, h) rep(j, w) if(b[i][j] == 's') dfs(i, j);
	rep(i, h) rep(j, w) if(b[i][j] == 'g'){
		if(c[i][j]) puts("Yes");
		else puts("No");
	}

	return 0;
}
