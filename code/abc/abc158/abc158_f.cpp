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
//constexpr ll MOD = 1e9+7;
constexpr ll MOD = 998244353;
constexpr ld PI = acos(-1);
constexpr ld EPS = 1e-11;

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
	VecP r(n);
	rep(i, n) cin >> r[i].fs >> r[i].sc;
	sort(all(r));
	Vec x(n), d(n);
	rep(i, n){
		x[i] = r[i].fs;
		d[i] = r[i].sc;
	}
	SegmentTree<ll> st(n, 0, [](ll a, ll b){return max(a, b);});
	repr(i, n){
		ll p = lower_bound(all(x), x[i] + d[i]) - x.begin();
		st.update(i, i);
		ll m = st.query(i, p);
		st.update(i, m);
	}

	Vec dp1(n), dp2(n);
	ll ans = 1;
	dp1[n - 1] = 1, dp2[n - 1] = 1;
	repr(i, n - 1){
		ll p = st.query(i, i + 1);
		if(p == n - 1) dp2[i] = 1;
		else if(p == i) dp2[i] = (dp1[i + 1] + dp2[i + 1]) % MOD;
		else dp2[i] = (dp1[p + 1] + dp2[p + 1]) % MOD;
		dp1[i] = (dp1[i + 1] + dp2[i + 1]) % MOD;
	}
	//co(dp1);
	//co(dp2);
	co((dp1[0] + dp2[0]) % MOD);

	return 0;
}
