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
constexpr ll INF = 1e9+1;
constexpr ll LINF = 1e18+1;
constexpr ll MOD = 1e9+7;
//constexpr ll MOD = 998244353;
constexpr ld PI = acos(-1);
constexpr ld EPS = 1e-11;

Vec2<ll> tree;
Vec color;

void dfs(ll node, ll c, ll par){
	color[node] = c;
	for(ll i : tree[node]){
		if(i != par) dfs(i, !c, node);
	}
}

int main(void){
	ll n;
	cin >> n;
	tree.resize(n);
	color.resize(n);
	rep(i, n - 1){
		ll a, b;
		cin >> a >> b;
		a--, b--;
		tree[a].pb(b);
		tree[b].pb(a);
	}
	ll k = n / 3;

	dfs(0, 0, -1);
	Vec cnt(2);
	rep(i, n) cnt[color[i]]++;
	Vec ans(n);
	if(cnt[0] <= k){
		ll a = 3, b = 1, c = 2;
		rep(i, n){
			if(color[i] == 0){
				ans[i] = a;
				a += 3;
			}else{
				if(b <= n){
					ans[i] = b;
					b += 3;
				}else if(c <= n){
					ans[i] = c;
					c += 3;
				}else{
					ans[i] = a;
					a += 3;
				}
			}
		}
	}else if(cnt[1] <= k){
		ll a = 3, b = 1, c = 2;
		rep(i, n){
			if(color[i] == 1){
				ans[i] = a;
				a += 3;
			}else{
				if(b <= n){
					ans[i] = b;
					b += 3;
				}else if(c <= n){
					ans[i] = c;
					c += 3;
				}else{
					ans[i] = a;
					a += 3;
				}
			}
		}
	}else{
		ll a = 3, b = 1, c = 2;
		rep(i, n){
			if(color[i] == 0){
				if(b <= n){
					ans[i] = b;
					b += 3;
				}else{
					ans[i] = a;
					a += 3;
				}
			}else{
				if(c <= n){
					ans[i] = c;
					c += 3;
				}else{
					ans[i] = a;
					a += 3;
				}
			}
		}
	}
	co(ans);

	return 0;
}
