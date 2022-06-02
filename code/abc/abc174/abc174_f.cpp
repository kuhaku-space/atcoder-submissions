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
#define REP(i, m, n) for(ll i = (m); i < (n); ++i)
#define REPN(i, m, n) for(ll i = (m); i <= (n); ++i)
#define REPR(i, m, n) for(ll i = (m)-1; i >= (n); --i)
#define REPNR(i, m, n) for(ll i = (m); i >= (n); --i)
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
// constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-11;
const double PI = acos(-1);

template <typename T>
struct BIT{
	ll N;
	Vec1<T> data;

	BIT(ll n){
		init(n);
	}

	void init(ll n){
		N = 1;
		while(N < n) N <<= 1;
		data.assign(N, 0);
	}

	void build(Vec1<T> v){
		init(N);
		rep(i, v.size()) add(i, v[i]);
	}

	void add(ll k, T x){
		k++;
		while(k <= N){
			data[k] += x;
			k += k & -k;
		}
	}

	T sum(ll k){
		k++;
		T res = 0;
		while(k){
			res += data[k];
			k -= k & -k;
		}
		return res;
	}
	T sum(ll a, ll b){return sum(b - 1) - sum(a - 1);}

	T at(ll k){return sum(k) - sum(k - 1);}

	
	T lower_bound(T k){
		ll l = 0, r = N;
		while(r - l >= 2){
			ll m = (l + r) / 2;
			if(sum(m) >= k) r = m;
			else l = m;
		}
		return r;
	}
};

bool asc(pair<P, ll> &a, pair<P, ll> &b) {
	if (a.fs.sc == b.fs.sc) return a.fs.fs < b.fs.fs;
	return a.fs.sc < b.fs.sc;
}

int main(void){
	ll n, q;
	cin >> n >> q;
	Vec c(n);
	rep(i, n) cin >> c[i];
	vector<pair<P, ll>> p(q);
	rep(i, q) cin >> p[i].fs.fs >> p[i].fs.sc;
	rep(i, q) p[i].sc = i;

	sort(all(p), asc);

	Vec ans(q);
	BIT<ll> bit(n);
	unordered_map<ll, ll> ump;
	ll cnt = 0;
	rep(i, n) {
		if (ump.find(c[i]) == ump.end()) {
			bit.add(i, 1);
			ump[c[i]] = i;
		} else {
			bit.add(ump[c[i]], -1);
			bit.add(i, 1);
			ump[c[i]] = i;
		}

		while (cnt < q && p[cnt].fs.sc == i + 1) {
			ans[p[cnt].sc] = bit.sum(p[cnt].fs.fs - 1, p[cnt].fs.sc);
			cnt++;
		}
	}
	rep(i, q) co(ans[i]);

	return 0;
}
