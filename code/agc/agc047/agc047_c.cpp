#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using P = pair<ll, ll>;
using Vec = vector<ll>;
#define REP(i, m, n) for(ll i = (m); i < (n); ++i)
#define rep(i, n) REP(i, 0, n)
template <typename T>
bool chmax(T &a, const T b){if(a < b){a = b; return true;} return false;}
template <typename T>
bool chmin(T &a, const T b){if(a > b){a = b; return true;} return false;}
constexpr ll LINF = 1e18L+1;
constexpr ll MOD = 1e9+7;
const double PI = acos(-1.0);

namespace FFT {
using CP = complex<double>;

void _fft(vector<CP> &a, bool inv) {
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
        for (int i = 0; i < N; ++i) a[i] /= N;
    }
}

template <class T>
void convolution_self(vector<T> &a, const vector<T> &b) {
    int n = a.size() + b.size() - 1;
    int N = 1;
    while (N < n) N <<= 1;

    vector<CP> va(N), vb(N);
    for (int i = 0; i < a.size(); ++i) va[i] = CP(a[i]);
    for (int i = 0; i < b.size(); ++i) vb[i] = CP(b[i]);
    _fft(va, false), _fft(vb, false);
    for (int i = 0; i < N; ++i) va[i] *= vb[i];
    _fft(va, true);

    a.resize(n);
    for (int i = 0; i < n; ++i) a[i] = T(va[i].real() + 0.5);
}

template <class T>
vector<T> convolution(const vector<T> &a, const vector<T> &b) {
    vector<T> res = a;
    convolution_self(res, b);
    return res;
}
}  // namespace FFT

// i * j = g^(x + y) としてFFTに帰着
int64_t pow_mod(int64_t a, int64_t n, int64_t mod) {
    int64_t res = 1, mul = a;
    for (; n > 0; n >>= 1) {
        if (n & 1) (res *= mul) %= mod;
        (mul *= mul) %= mod;
    }
    return res;
}

int get_primitive_root(const int mod) {
    if (mod == 998244353) return 3;
    int64_t divs[20] = {};
    divs[0] = 2;
    int64_t cnt = 1;
    int64_t x = (mod - 1) / 2;
    while (x % 2 == 0) x /= 2;
    for (int64_t i = 3; i * i <= x; i += 2) {
        if (x % i == 0) {
            divs[cnt++] = i;
            while (x % i == 0) x /= i;
        }
    }
    if (x > 1) divs[cnt++] = x;
    for (int64_t g = 2;; ++g) {
        bool ok = true;
        for (int64_t i = 0; i < cnt; ++i) {
            if (pow_mod(g, (mod - 1) / divs[i], mod) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
    return 0;
}

constexpr int pr = 200003;

int main(void) {
    int n;
    cin >> n;
    Vec a(pr);
    ll ans = 0;
    rep(i, n){
        ll t;
        cin >> t;
        a[t]++;
        ans -= t * t % pr;
    }

    int r = get_primitive_root(pr);

    Vec b(pr);
    ll t = 1;
    rep(i, pr-1){
        b[i] = a[t];
        (t *= r) %= pr;
    }

    b = FFT::convolution(b, b);

    t = 1;
    Vec c(pr);
    rep(i, b.size()){
        c[t] += b[i];
        (t *= r) %= pr;
    }

    rep(i, pr){
        ans += i * c[i];
    }
    cout << ans / 2 << endl;

    return 0;
}
