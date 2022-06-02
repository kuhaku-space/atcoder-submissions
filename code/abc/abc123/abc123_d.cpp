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
const ld PI = acos(-1);
const ld EPS = 1e-11;

int main(void){
	ll x, y, z, k;
	cin >> x >> y >> z >> k;
	Vec a(x), b(y), c(z);
	rep(i, x) cin >> a[i];
	rep(i, y) cin >> b[i];
	rep(i, z) cin >> c[i];
	sort(all(a));
	sort(all(b));
	sort(all(c));
	reverse(all(a));
	reverse(all(b));
	reverse(all(c));

	priority_queue<P> que;
	que.push({a[0]+b[0]+c[0], 0});
	unordered_set<ll> ust;
	ll i = 0;
	while(i < k){
		P p = que.top(); que.pop();
		if(ust.find(p.sc) == ust.end()){
			i++;
			co(p.fs);
			ust.insert(p.sc);
			ll u, v, w;
			w = p.sc%z;
			p.sc /= z;
			v = p.sc%y;
			p.sc /= y;
			u = p.sc;
			if(u+1 < x) que.push({a[u+1]+b[v]+c[w], ((u+1)*x+v)*y+w});
			if(v+1 < y) que.push({a[u]+b[v+1]+c[w], (u*x+v+1)*y+w});
			if(w+1 < z) que.push({a[u]+b[v]+c[w+1], (u*x+v)*y+w+1});
		}
	}

	return 0;
}
