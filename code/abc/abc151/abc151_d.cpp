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
using Vec = vector<ll>;
using VecP = vector<P>;
using VecB = vector<bool>;
using VecC = vector<char>;
using VecD = vector<double>;
using VecS = vector<string>;
using VecVec = vector<Vec>;
using Tree = vector<VecP>;
template <typename T>
using Vec1 = vector<T>;
template <typename T>
using Vec2 = vector<vector<T> >;
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

ll h, w;
VecS s;
VecVec dist;

void init(){
	rep(i, h+2) fill(all(dist[i]), LINF);
}

void bfs(ll x, ll y){
	queue<P> que;
	dist[x][y] = 0;
	que.push({x, y});
	Vec2<ll> sign = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	while(!que.empty()){
		P p = que.front(); que.pop();
		rep(i, 4){
			ll dx = p.fs+sign[i][0], dy = p.sc+sign[i][1];
			if(s[dx][dy] == '.' && dist[dx][dy] == LINF){
				dist[dx][dy] = dist[p.fs][p.sc]+1;
				que.push({dx, dy});
			}
		}
	}
}

ll maxDist(){
	ll res = 0;
	repn(i, h) repn(j, w) if(dist[i][j] != LINF) chmax(res, dist[i][j]);
	return res;
}

int main(void){
	cin >> h >> w;
	s.resize(h+2);
	repn(i, h){
		string t;
		cin >> t;
		s[i] += "#";
		s[i] += t;
		s[i] += "#";
	}
	rep(i, w+2){
		s[0] += "#";
		s[h+1] += "#";
	}
	dist.resize(h+2);
	rep(i, h+2) dist[i].resize(w+2);

	ll ans = 0;
	repn(i, h){
		repn(j, w) if(s[i][j] == '.'){
			init();
			bfs(i, j);
			chmax(ans, maxDist());
		}
	}
	co(ans);

	return 0;
}
