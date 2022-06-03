// clang-format off
#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ld = long double;
#define FOR(i, m, n) for(int i = (m); i < (n); ++i)
#define FORR(i, m, n) for(int i = (m)-1; i >= (n); --i)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FOR(i, 1, n+1)
#define repr(i, n) FORR(i, n, 0)
#define repnr(i, n) FORR(i, n+1, 1)
#define all(s) (s).begin(), (s).end()
template <class T, class U>
bool chmax(T &a, const U b) { return a < b ? a = b, true : false; }
template <class T, class U>
bool chmin(T &a, const U b) { return b < a ? a = b, true : false; }
template <class T>
istream &operator>>(istream &is, vector<T> &v) { for (T &i : v) is>>i; return is; }
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    for (auto it=v.begin(); it!=v.end(); ++it) { os<<(it==v.begin()?"":" ")<<*it; } return os;
}
template <class Head, class... Tail>
void co(Head&& head, Tail&&... tail) {
    if constexpr(sizeof...(tail)==0) cout<<head<<'\n'; else cout<<head<<' ',co(forward<Tail>(tail)...);
}
template <class Head, class... Tail>
void ce(Head&& head, Tail&&... tail) {
    if constexpr(sizeof...(tail)==0) cerr<<head<<'\n'; else cerr<<head<<' ',ce(forward<Tail>(tail)...);
}
template<typename T, typename... Args>
auto make_vector(T x, int arg, Args ...args) {
    if constexpr(sizeof...(args)==0) return vector<T>(arg, x); else return vector(arg,make_vector<T>(x, args...));
}
void sonic() { ios::sync_with_stdio(false); cin.tie(nullptr); }
void setp(const int n) { cout << fixed << setprecision(n); }
constexpr int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
const double PI = acos(-1);

namespace FFT_MOD {
using CP = complex<double>;

void _fft(valarray<CP> &a, bool inv) {
    int N = a.size();
    static bool is_first = true;
    static vector<CP> vbw(30), vibw(30);
    if (is_first) {
        is_first = false;
        for (int i = 0; i < 30; ++i) {
            vbw[i] = polar(1.0, 2.0 * PI / (1 << (i + 1)));
            vibw[i] = polar(1.0, -2.0 * PI / (1 << (i + 1)));
        }
    }
    for (int i = 0, j = 1; j < N - 1; ++j) {
        for (int k = N >> 1; k > (i ^= k); k >>= 1)
            ;
        if (i > j) swap(a[i], a[j]);
    }
    for (int k = 0, t = 1; t < N; ++k, t <<= 1) {
        CP bw = vbw[k];
        if (inv) bw = vibw[k];
        for (int i = 0; i < N; i += t * 2) {
            CP w(1.0);
            for (int j = 0; j < t; ++j) {
                int l = i + j, r = i + j + t;
                CP c = a[l], d = a[r] * w;
                a[l] = c + d, a[r] = c - d;
                w *= bw;
            }
        }
    }
    if (inv) {
        a /= N;
    }
}

template <class T>
void _convolution_self(valarray<T> &a, const valarray<T> &b) {
    int n = a.size() + b.size() - 1;
    int N = 1;
    while (N < n) N <<= 1;

    valarray<CP> va(N), vb(N);
    for (int i = 0; i < a.size(); ++i) va[i] = CP(a[i]);
    for (int i = 0; i < b.size(); ++i) vb[i] = CP(b[i]);
    _fft(va, false), _fft(vb, false);
    va *= vb;
    _fft(va, true);

    a.resize(n);
    for (int i = 0; i < n; ++i) a[i] = T(va[i].real() + 0.5);
}

template <class T>
valarray<T> _convolution(const valarray<T> &a, const valarray<T> &b) {
    valarray<T> res = a;
    _convolution_self(res, b);
    return res;
}

template <class T>
vector<T> convolution(const vector<T> &a, const vector<T> &b, int mod) {
    int n = a.size(), m = b.size();
    valarray<T> v(n), w(m);
    for (int i = 0; i < n; ++i) v[i] = a[i];
    for (int i = 0; i < m; ++i) w[i] = b[i];
    auto f1 = v, f2 = v;
    auto g1 = w, g2 = w;
    f1 >>= 15;
    f2 &= (1 << 15) - 1;
    g1 >>= 15;
    g2 &= (1 << 15) - 1;

    auto x = _convolution(f1, g1);
    x %= mod;
    auto z = _convolution(f2, g2);
    z %= mod;
    f1 += f2;
    g1 += g2;
    auto y = _convolution(f1, g1);
    y -= x;
    y -= z;
    y %= mod;
    x <<= 15;
    x += y;
    x <<= 15;
    x += z;
    x %= mod;
    vector<T> res(n + m - 1);
    for (int i = 0; i < n + m - 1; ++i) res[i] = x[i];
    return res;
}
}  // namespace FFT_MOD

int64_t pow_mod(int64_t a, int64_t n, int64_t mod) {
    // if (n < 0) return inv_mod(pow_mod(a, -n, mod), mod);
    int64_t res = 1, mul = a;
    for (; n > 0; n >>= 1) {
        if (n & 1) (res *= mul) %= mod;
        (mul *= mul) %= mod;
    }
    return res;
}

// clang-format on

int main(void) {
    int n, c;
    cin >> n >> c;
    vector<int> a(n);
    auto b = a;
    cin >> a >> b;

    vector<ll> v(1, 1);
    rep(i, n) {
        vector<ll> t(c + 1);
        rep(j, c + 1) {
            FOR(k, a[i], b[i] + 1) {
                t[j] += pow_mod(k, j, MOD);
            }
            t[j] %= MOD;
        }
        v = FFT_MOD::convolution(v, t, MOD);
        v.resize(c + 1);
        ce(v);
    }
    co(v[c]);

    return 0;
}
