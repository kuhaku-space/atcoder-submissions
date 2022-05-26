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
template <typename T>
bool chmax(T &a, const T& b){if(a < b){a = b; return true;} return false;}
template <typename T>
bool chmin(T &a, const T& b){if(a > b){a = b; return true;} return false;}
const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;

int main(void){
	ll n, m;
	cin >> n >> m;
	VecVec dist(n+1, Vec(n+1, LINF));
	repn(i, n) dist[i][i] = 0;
	rep(i, m){
		ll a, b, t;
		cin >> a >> b >> t;
		dist[a][b] = t;
		dist[b][a] = t;
	}

	repn(k, n) repn(i, n) repn(j, n) dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
	Vec maxDist(n+1, 0);
	ll minDist = LINF;
	repn(i, n){
		repn(j, n) chmax(maxDist[i], dist[i][j]);
		chmin(minDist, maxDist[i]);
	}
	co(minDist);

	return 0;
}
