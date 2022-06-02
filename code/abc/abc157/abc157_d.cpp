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
void co(const T n){cout << n << '\n';}
template <typename T1, typename T2>
void co(pair<T1, T2> p){cout << p.fs << ' ' << p.sc << '\n';}
template <typename T>
void co(const Vec1<T> &v){for(T i : v) cosp(i); cout << '\n';}
template <typename T>
void co(initializer_list<T> v){for(T i : v) cosp(i); cout << '\n';}
template <typename T>
void ce(const T n){cerr << n << endl;}
void sonic(){ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);}
void setp(const ll n){cout << fixed << setprecision(n);}
const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const ld PI = acos(-1);
const ld EPS = 1e-11;

template <typename T>
struct UnionFind{
	Vec1<T> par;

	UnionFind(T n){
		par.resize(n);
		rep(i, n) par[i] = i;
	}

	T root(T x){
		if(par[x] == x) return x;
		return par[x] = root(par[x]);
	}

	void unite(T x, T y){
		x = root(x), y = root(y);
		if(x != y) par[x] = y;
	}

	bool same(T x, T y){
		return root(x) == root(y);
	}
};

int main(void){
	ll n, m, k;
	cin >> n >> m >> k;

	UnionFind<ll> uf(n);
	Vec f(n);
	rep(i, m){
		ll a, b;
		cin >> a >> b;
		a--, b--;
		uf.unite(a, b);
		f[a]++, f[b]++;
	}
	Vec cnt(n);
	rep(i, n) cnt[uf.root(i)]++;
	//co(cnt);
	Vec ans(n);
	rep(i, n) ans[i] = cnt[uf.root(i)]-1;
	//co(ans);
	rep(i, n) ans[i] -= f[i];
	rep(i, k){
		ll c, d;
		cin >> c >> d;
		c--, d--;
		if(uf.same(c, d)){
			ans[c]--;
			ans[d]--;
		}
	}
	co(ans);

	return 0;
}
