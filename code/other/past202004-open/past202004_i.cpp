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
#define REP(i, m, n) for(ll i = (m); (i) < (n); ++(i))
#define REPN(i, m, n) for(ll i = (m); (i) <= (n); ++(i))
#define REPR(i, m, n) for(ll i = (m)-1; (i) >= (n); --(i))
#define REPNR(i, m, n) for(ll i = (m); (i) >= (n); --(i))
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
void co(void){cout << '\n';}
template <typename T>
void co(const T n){cout << n << '\n';}
template <typename T1, typename T2>
void co(pair<T1, T2> p){cout << p.fs << ' ' << p.sc << '\n';}
template <typename T>
void co(const Vec1<T> &v){for(T i : v) cosp(i); co();}
template <typename T>
void co(initializer_list<T> v){for(T i : v) cosp(i); co();}
template <typename T>
void ce(const T n){cerr << n << endl;}
void sonic(){ios::sync_with_stdio(false); cin.tie(0);}
void setp(const ll n){cout << fixed << setprecision(n);}
constexpr int INF = 1e9+1;
constexpr ll LINF = 1e18+1;
constexpr ll MOD = 1e9+7;
//constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-11;
const ld PI = acos(-1);

template <typename T>
struct SegmentTree{
	using F = function<T(T, T)>;
	ll N;
	T d;
	F f;
	Vec1<T> data;

	SegmentTree(ll n, T d, F f) : f(f), d(d){
		init(n);
	}

	void init(ll n){
		N = 1;
		while(N < n) N <<= 1;
		data.assign(N*2, d);
	}

	void build(Vec1<T> v){
		rep(i, v.size()) data[N+i] = v[i];
		repnr(i, N-1) data[i] = f(data[i*2], data[i*2+1]);
	}

	T at(ll k){
		k += N;
		return data[k];
	}

	void update(ll k, const T x){
		k += N;
		data[k] = x;
		while(k > 1){
			k >>= 1;
			data[k] = f(data[k*2], data[k*2+1]);
		}
	}

	void add(ll k, const T x){
		k += N;
		data[k] += x;
		while(k > 1){
			k >>= 1;
			data[k] = f(data[k*2], data[k*2+1]);
		}
	}

	ll q(ll k, ll x){
		k += N;
		ll res = 1;
		while(k > 3){
			k >>= 1;
			if(data[k] != x) break;
			res++;
		}
		return res;
	}

	T query(ll a, ll b){return query(a, b, 1, 0, N);}
	T query(ll a, ll b, ll k, ll l, ll r){
		if(r <= a || b <= l) return d;
		if(a <= l && r <= b) return data[k];
		ll m = (l+r)/2;
		return f(query(a, b, k*2, l, m), query(a, b, k*2+1, m, r));
	}
};

int main(void){
	ll n;
	cin >> n;
	ll m = pow2(n);
	Vec a(m);
	rep(i, m) cin >> a[i];

	SegmentTree<ll> st(m, 0, [](ll a, ll b){return max(a, b);});
	st.build(a);

	for(int i = 0; i < m; ++i){
		cout << st.q(i, a[i]) << endl;
	}

	return 0;
}
