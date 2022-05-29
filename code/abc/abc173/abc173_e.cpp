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
const ld PI = acos(-1);

template <int mod>
struct ModInt {
	int x;

	ModInt() : x(0) {}

	ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}

	ModInt &operator+=(const ModInt &p) {
		if((x += p.x) >= mod) x -= mod;
		return *this;
	}

	ModInt &operator-=(const ModInt &p) {
		if((x += mod - p.x) >= mod) x -= mod;
		return *this;
	}

	ModInt &operator*=(const ModInt &p) {
		x = (int) (1LL * x * p.x % mod);
		return *this;
	}

	ModInt &operator/=(const ModInt &p) {
		*this *= p.inverse();
		return *this;
	}

	ModInt operator-() const { return ModInt(-x); }

	ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }

	ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }

	ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }

	ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }

	bool operator==(const ModInt &p) const { return x == p.x; }

	bool operator!=(const ModInt &p) const { return x != p.x; }

	ModInt inverse() const {
		int a = x, b = mod, u = 1, v = 0, t;
		while(b > 0) {
			t = a / b;
			swap(a -= t * b, b);
			swap(u -= t * v, v);
		}
		return ModInt(u);
	}

	ModInt pow(int64_t n) const {
		ModInt res(1), mul(x);
		while(n > 0) {
			if(n & 1) res *= mul;
			mul *= mul;
			n >>= 1;
		}
		return res;
	}

	friend ostream &operator<<(ostream &os, const ModInt &p) {
		return os << p.x;
	}

	friend istream &operator>>(istream &is, ModInt &a) {
		int64_t t;
		is >> t;
		a = ModInt< mod >(t);
		return (is);
	}

	static int get_mod() { return mod; }
};
using Mint = ModInt<MOD>;

int main(void){
	ll n, k;
	cin >> n >> k;
	Vec a(n);
	rep(i, n) cin >> a[i];
	Mint ans = 1;

	ll cnt = 0;
	rep(i, n) if (a[i] > 0) cnt++;

	if(cnt == 0){
		sort(all(a));
		if(k % 2 == 1) reverse(all(a));
		rep(i, k) ans *= a[i];
		co(ans);
		return 0;
	}

	Vec b, c;
	rep(i, n){
		if (a[i] >= 0) b.pb(a[i]);
		else
			c.pb(a[i]);
	}

	sort(all(b));
	reverse(all(b));
	sort(all(c));
	// reverse(all(c));

	if(k & 1){
		ans *= b[0];
		b.erase(b.begin());
		k--;
	}

	a.clear();
	rep(i, b.size() / 2) a.pb(b[i * 2] * b[i * 2 + 1]);
	rep(i, c.size() / 2) a.pb(c[i * 2] * c[i * 2 + 1]);
	if (b.size() & 1 && c.size() & 1) a.pb(b.back() * c.back());

	sort(all(a));
	reverse(all(a));

	rep(i, k / 2) ans *= a[i];
	co(ans);

	return 0;
}
