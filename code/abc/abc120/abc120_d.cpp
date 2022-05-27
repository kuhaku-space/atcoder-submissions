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
#define repn(i, n) REPN(i, 1, n)
#define repr(i, n) REPR(i, n, 0)
#define repnr(i, n) REPNR(i, n, 1)
#define all(s) (s).begin(), (s).end()
#define pb push_back
#define mp make_pair
#define fs first
#define sc second
template <typename T>
bool chmax(T &a, const T b){if(a < b){a = b; return true;} return false;}
template <typename T>
bool chmin(T &a, const T b){if(a > b){a = b; return true;} return false;}
template <typename T>
ll pow2(const T n){return (1LL << n);}
template <typename T>
void cosp(const T n){cout << n << ' ';}
template <typename T>
void co(const T n){cout << n << endl;}
template <typename T1, typename T2>
void co(pair<T1, T2> p){cout << p.fs << ' ' << p.sc << endl;}
template <typename T>
void co(const Vec1<T> &v){for(T i : v) cosp(i); cout << endl;}
template <typename T>
void co(initializer_list<T> v){for(T i : v) cosp(i); cout << endl;}
void sonic(){ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);}
void setp(const ll n){cout << fixed << setprecision(n);}
const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const ld PI = acos(-1);
const ld EPS = 1e-11;

struct UnionFind{
	Vec par;
	Vec ele;

	UnionFind(ll n){
		par.resize(n);
		ele.assign(n, 1);
		rep(i, n) par[i] = i;
	}

	ll root(ll x){
		if(par[x] == x) return x;
		return par[x] = root(par[x]);
	}

	void unite(ll x, ll y){
		x = root(x), y = root(y);
		if(x != y){
			par[x] = y;
			ele[y] += ele[x];
			ele[x] = 0;
		}
	}

	bool same(ll x, ll y){
		return root(x) == root(y);
	}

	ll element(ll x){
		return ele[x];
	}
};

int main(void){
	ll n, m;
	cin >> n >> m;
	VecP e(m);
	rep(i, m){
		ll a, b;
		cin >> a >> b;
		e[i] = {--a, --b};
	}


	UnionFind uf(n);

	Vec ans(m+1);
	ans[m] = n*(n-1)/2;
	repr(i, m){
		ans[i] = ans[i+1];
		if(uf.same(e[i].fs, e[i].sc)) continue;
		ans[i] -= uf.element(uf.root(e[i].fs))*uf.element(uf.root(e[i].sc));
		uf.unite(e[i].fs, e[i].sc);
	}
	repn(i, m) co(ans[i]);

	return 0;
}
