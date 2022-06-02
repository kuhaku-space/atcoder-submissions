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
template <typename T>
using Vec3 = vector<Vec2<T> >;
#define REP(i, m, n) for(ll (i) = (m); (i) < (n); ++(i))
#define REPN(i, m, n) for(ll (i) = (m); (i) <= (n); ++(i))
#define REPR(i, m, n) for(ll (i) = (m)-1; (i) >= (n); --(i))
#define REPNR(i, m, n) for(ll (i) = (m); (i) >= (n); --(i))
#define rep(i, n) REP(i, 0, n)
#define repn(i, n) REPN(i, 1, n)
#define repe(i, n) REPN(i, 0, n)
#define repr(i, n) REPR(i, n, 0)
#define repnr(i, n) REPNR(i, n, 1)
#define reper(i, n) REPNR(i, n, 0)
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
void sonic(){ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);}
void setp(const ll n){cout << fixed << setprecision(n);}
const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const ld PI = acos(-1);
const ld EPS = 1e-11;

template <typename T>
struct SegmentTree{
	using F = function<T(T, T)>;
	T N, d;
	F f;
	Vec1<T> data;

	SegmentTree(T n, T d, F f) : f(f), d(d){
		init(n);
	}

	void init(T n){
		N = 1;
		while(N < n) N <<= 1;
		data.assign(N*2, d);
	}

	void build(Vec1<T> v){
		rep(i, v.size()) data[N+i] = v[i];
		repnr(i, N-1) data[i] = f(data[i*2], data[i*2+1]);
	}

	void update(T k, const T x){
		k += N;
		data[k] = x;
		while(k > 1){
			k >>= 1;
			data[k] = f(data[k*2], data[k*2+1]);
		}
	}

	void add(T k, const T x){
		k += N;
		data[k] += x;
		while(k > 1){
			k >>= 1;
			data[k] = f(data[k*2], data[k*2+1]);
		}
	}

	T query(T a, T b){return query(a, b, 1, 0, N);}
	T query(T a, T b, T k, T l, T r){
		if(r <= a || b <= l) return d;
		if(a <= l && r <= b) return data[k];
		T m = (l+r)/2;
		return f(query(a, b, k*2, l, m), query(a, b, k*2+1, m, r));
	}
};

int main(void){
	ll n;
	cin >> n;
	Vec h(n), a(n);
	rep(i, n){
		cin >> h[i];
		h[i]--;
	}
	rep(i, n) cin >> a[i];

	SegmentTree<ll> st(n, 0, [](ll a, ll b){return max(a, b);});
	Vec dp(n);
	repr(i, n){
		dp[i] = a[i]+st.query(h[i]+1, n);
		st.add(h[i], dp[i]);
	}
	co(st.query(0, n));

	return 0;
}
