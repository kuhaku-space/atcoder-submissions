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
bool chmax(T &a, const T& b){if(a < b){a = b; return true;} return false;}
template <typename T>
bool chmin(T &a, const T& b){if(a > b){a = b; return true;} return false;}
template <typename T>
void co(const T n){cout << n << endl;}
template <typename T>
void cosp(const T n){cout << n << ' ';}
template <typename T>
void coVec(const Vec &v){for(ll i : v) cosp(i); cout << endl;}
void sonic(){ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);}
void setp(const ll n){cout << fixed << setprecision(n);}
const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const ld PI = acos(-1);
const ld EPS = 1e-11;

Graph tree;

bitset<50> dfs(ll node, ll e, bitset<50> bits){
	if(node == e) return bits;
	bitset<50> res(0);
	for(P i : tree[node]) if(!bits[i.sc]){
		bits.set(i.sc);
		res |= dfs(i.fs, e, bits);
		bits.reset(i.sc);
	}
	return res;
}

int main(void){
	ll n;
	cin >> n;
	tree.resize(n);
	VecP e(n);
	rep(i, n-1){
		ll a, b;
		cin >> a >> b;
		a--, b--;
		tree[a].pb({b, i});
		tree[b].pb({a, i});
		e[i] = {a, b};
	}
	ll m;
	cin >> m;
	VecP q(m);
	rep(i, m){
		ll u, v;
		cin >> u >> v;
		u--, v--;
		q[i] = {u, v};
	}

	Vec1<bitset<50> > edges(m);
	rep(i, m){
		edges[i] = dfs(q[i].fs, q[i].sc, 0);
	}

	ll ans = (1LL << (n-1));
	rep(bit, (1LL << m)){
		if(!bit) continue;
		bitset<20> bits(bit);
		ll cnt = bits.count();
		bitset<50> edge(0);
		rep(i, m) if(bits[i] == 1){
			edge |= edges[i];
		}
		ll pow = n-1-edge.count();
		if(cnt%2) ans -= (1LL << pow);
		else ans += (1LL << pow);
	}
	co(ans);

	return 0;
}
