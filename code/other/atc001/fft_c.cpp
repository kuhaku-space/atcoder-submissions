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
void ce(void){cerr << '\n';}
template <typename T>
void ce(const T n){cerr << n << '\n';}
template <typename T>
void cesp(const T n){cerr << n << ' ';}
template <typename T>
void ce(initializer_list<T> v){for(T i : v) cesp(i); ce();}
void sonic(){ios::sync_with_stdio(false); cin.tie(0);}
void setp(const ll n){cout << fixed << setprecision(n);}
constexpr int INF = 1e9+1;
constexpr ll LINF = 1e18+1;
// constexpr ll MOD = 1e9+7;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-11;
const double PI = acos(-1);

using CP = complex<double>;

void fft(vector<CP> &a, bool inv) {
	int64_t N = a.size();
    static bool is_first = true;
	static vector<CP> vbw(30), vibw(30);
	if (is_first) {
		is_first = false;
		for (size_t i = 0; i < 30; ++i) {
			vbw[i] = polar(1.0,  2.0 * PI / (1 << (i + 1)));
			vibw[i] = polar(1.0, -2.0 * PI / (1 << (i + 1)));
		}
	}
	for (size_t i = 0, j = 1; j < N - 1; ++j) {
		for (size_t k = N >> 1; k > (i ^= k); k >>= 1);
		if (i > j) swap(a[i], a[j]);
	}
	for (size_t i = 0, t = 1; t < N; ++i, t <<= 1) {
		CP bw = vbw[i];
		if (inv) bw = vibw[i];
		for (size_t i = 0; i < N; i += t * 2) {
		    CP w(1.0);
			for (size_t j = 0; j < t; ++j) {
				int64_t l = i + j, r = i + j + t;
				CP c = a[l], d = a[r] * w;
				a[l] = c + d;
				a[r] = c - d;
				w *= bw;
			}
		}
	}
	if (inv) {
		for (size_t i = 0; i < N; ++i) a[i] /= N;
	}
}

void conv(vector<CP> &a, vector<CP> &b) {
    int64_t n = a.size() + b.size() - 1;
    int64_t N = 1;
    while (N < n) N <<= 1;

    a.resize(N);
    b.resize(N);

    fft(a, false);
    fft(b, false);

    for (size_t i = 0; i < N; ++i) a[i] *= b[i];

    fft(a, true);
    a.resize(n);
}

int main(void){
	ll n;
	cin >> n;
	vector<CP> va(n + 1), vb(n + 1);
	rep(i, n){
		ll a, b;
		cin >> a >> b;
		va[i + 1] = CP(a);
		vb[i + 1] = CP(b);
	}
 
	conv(va, vb);
 
	repn(i, 2 * n) co(int(va[i].real() + 0.5));

	return 0;
}
