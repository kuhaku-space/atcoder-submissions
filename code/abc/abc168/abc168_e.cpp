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
		ModInt ret(1), mul(x);
		while(n > 0) {
			if(n & 1) ret *= mul;
			mul *= mul;
			n >>= 1;
		}
		return ret;
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

ll gcd(ll a, ll b){
	if(!b) return abs(a);
	return gcd(b, a%b);
}

int main(void){
	ll n;
	cin >> n;
	Vec a(n), b(n);
	rep(i, n) cin >> a[i] >> b[i];

	rep(i, n){
		ll g = gcd(a[i], b[i]);
		if(!g) continue;
		if(b[i] < 0) g = -g;
		if(b[i] == 0) g = a[i];
		a[i] /= g;
		b[i] /= g;
	}

	ll cnt = 0;
	map<P, P> mp;
	rep(i, n){
		if(a[i] == 0 && b[i] == 0){
			cnt++;
			continue;
		}
		if(a[i] > 0) mp[{a[i], b[i]}].fs++;
		else mp[{b[i], -a[i]}].sc++;
	}

	Mint ans = 1;
	for(auto p : mp){
		//co(p.fs);
		//co(p.sc);
		ans *= Mint(2).pow(p.sc.fs) + Mint(2).pow(p.sc.sc) - 1;
		//co(ans);
	}
	co(ans - 1 + cnt);

	return 0;
}
