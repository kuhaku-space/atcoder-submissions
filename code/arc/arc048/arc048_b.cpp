//confilm 0LL and 1LL
//confilm cornercases such as 0
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
#define REPR(i, m, n) for(ll (i) = (m); (i) >= (n); --(i))
#define rep(i, n) REP(i, 0, n)
#define repn(i, n) REPN(i, 1, n)
#define repr(i, n) REPR(i, n, 0)
#define repnr(i, n) REPR(i, n, 1)
#define co(n) cout << (n) << endl
#define cosp(n) cout << (n) << ' '
#define setp(n) cout << fixed << setprecision(n);
#define all(s) (s).begin(), (s).end()
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define fs first
#define sc second
template <typename T> bool chmax(T &a, const T& b){if(a < b){a = b; return true;} return false;}
template <typename T> bool chmin(T &a, const T& b){if(a > b){a = b; return true;} return false;}
const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;

int main(void){
	ll n;
	cin >> n;
	VecVec cs(100001, Vec(3));
	VecP p(n);
	rep(i, n){
		cin >> p[i].fs >> p[i].sc;
		p[i].sc--;
		cs[p[i].fs][p[i].sc]++;
	}

	repn(i, 100000){
		cs[i][0] += cs[i-1][0];
		cs[i][1] += cs[i-1][1];
		cs[i][2] += cs[i-1][2];
	}

	rep(i, n){
		ll win = 0, draw = 0, loss = 0;
		rep(j, 3) win += cs[p[i].fs-1][j];
		win += cs[p[i].fs][(p[i].sc+1)%3]-cs[p[i].fs-1][(p[i].sc+1)%3];
		draw = cs[p[i].fs][p[i].sc]-cs[p[i].fs-1][p[i].sc]-1;
		loss = n-1-win-draw;
		cosp(win); cosp(loss); co(draw);
	}

	return 0;
}
