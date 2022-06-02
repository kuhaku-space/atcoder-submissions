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

Tree tree;

int main(void){
	ll n, m;
	cin >> n >> m;
	tree.resize(n);
	Vec d(n);
	rep(i, n) cin >> d[i];
	VecP e(n);
	rep(i, n){
		e[i].fs = d[i];
		e[i].sc = i;
	}
	sort(all(e));

	rep(i, m){
		ll u, v;
		cin >> u >> v;
		u--; v--;
		tree[u].pb({v, i});
		tree[v].pb({u, i});
	}

	Vec color(n, 2);
	Vec cost(m);
	rep(i, n){
		P p = e[i];
		if(color[p.sc] != 2) continue;
		for(P j : tree[p.sc]){
			if(color[j.fs] != 2){
				color[p.sc] = !color[j.fs];
				cost[j.sc] = p.fs;
				break;
			}
		}

		if(color[p.sc] == 2){
			for(P j : tree[p.sc]){
				if(p.fs == d[j.fs]){
					color[p.sc] = 0;
					color[j.fs] = 1;
					cost[j.sc] = p.fs;
					break;
				}
			}
		}

		if(color[p.sc] == 2){
			co(-1);
			return 0;
		}
	}

	rep(i, m) if(!cost[i]) cost[i] = 1e9;
	rep(i, n){
		if(!color[i]) cout << "B";
		else cout << "W";
	}
	cout << endl;
	rep(i, m) co(cost[i]);

	return 0;
}
