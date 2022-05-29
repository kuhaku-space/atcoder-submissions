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
//constexpr ll MOD = 1e9+7;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-11;
const ld PI = acos(-1);

Vec fac, finv;

ll PowMod(ll a, ll n){
	if(n < 0) return PowMod(PowMod(a, -n), MOD-2);
	if(n == 0) return 1;
	if(n == 1) return a;
	if(n%2 == 0) return PowMod(a*a%MOD, n/2);
	return a*PowMod(a*a%MOD, n/2)%MOD;
}

ll inv(ll n){
	return PowMod(n, MOD-2);
}

void init(ll n = 2e6){
	fac.resize(n+1);
	fac[0] = 1;
	repn(i, n) fac[i] = fac[i-1]*i%MOD;
	finv.resize(n+1);
	finv[n] = PowMod(fac[n], MOD-2);
	repr(i, n) finv[i] = finv[i+1]*(i+1)%MOD;
	finv[0] = 1;
}

ll combi(ll n, ll k){
	if (n < 0 || k < 0) return 0;
	return fac[n]*finv[k]%MOD*finv[n-k]%MOD;
}

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
	init();
	ll n, m;
	cin >> n >> m;

	Mint ans = 0;
	rep(i, min(n + 1, m + 1)){
		ll rest = 3 * m - i;
		if (rest & 1) continue;
		rest /= 2;

		ans += combi(n, i) * combi(rest + n - 1, rest);
		ans -= combi(n, i) * i % MOD * combi(rest - m + n - 1, rest - m);
		ans -= combi(n, i) * (n - i) % MOD * combi(rest - m - 1 + n - 1, rest - m - 1);
		// ce(ans);
	}
	co(ans);

	return 0;
}
