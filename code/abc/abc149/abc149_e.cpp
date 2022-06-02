#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ld = long double;
using P = pair<ll, ll>;
using Pld = pair<ld, ld>;
using Vec = vector<ll>;
using VecP = vector<P>;
using VecB = vector<bool>;
using VecC = vector<char>;
using VecD = vector<ld>;
using VecS = vector<string>;
template <class T>
using Vec2 = vector<vector<T>>;
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
template <class T1, class T2>
bool chmax(T1 &a, const T2 b){if(a < b){a = b; return true;} return false;}
template <class T1, class T2>
bool chmin(T1 &a, const T2 b){if(a > b){a = b; return true;} return false;}
ll pow2(const int n){return (1LL << n);}
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
	for (const T &i : v) os << i << ' ';
	return os;
}
void co() { cout << '\n'; }
template <class Head, class... Tail>
void co(Head&& head, Tail&&... tail) {
	cout << head << ' ';
	co(forward<Tail>(tail)...);
}
void ce() { cerr << '\n'; }
template <class Head, class... Tail>
void ce(Head&& head, Tail&&... tail) {
	cerr << head << ' ';
	ce(forward<Tail>(tail)...);
}
void sonic(){ios::sync_with_stdio(false); cin.tie(0);}
void setp(const int n){cout << fixed << setprecision(n);}
constexpr int INF = 1000000001;
constexpr ll LINF = 1000000000000000001;
constexpr ll MOD = 1000000007; // primitive_root is 5
constexpr ll MOD_N = 998244353; // primitive_root is 3
constexpr ld EPS = 1e-11;
const double PI = acos(-1);

template <int mod>
struct ModInt {
    int64_t x;

    ModInt() : x(0) {}

    ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}

    ModInt &operator+=(const ModInt &rhs) {
        if((x += rhs.x) >= mod) x -= mod;
        return *this;
    }

    ModInt &operator-=(const ModInt &rhs) {
        if((x += mod - rhs.x) >= mod) x -= mod;
        return *this;
    }

    ModInt &operator*=(const ModInt &rhs) {
        x = (int) (1LL * x * rhs.x % mod);
        return *this;
    }

    ModInt &operator/=(const ModInt &rhs) {
        *this *= rhs.inverse();
        return *this;
    }

    ModInt &operator++() {
        if((++x) >= mod) x -= mod;
        return *this;
    }

    ModInt operator++(int) {
        ModInt tmp(*this);
        operator++();
        return tmp;
    }

    ModInt &operator--() {
        if((x += mod - 1) >= mod) x -= mod;
        return *this;
    }

    ModInt operator--(int) {
        ModInt tmp(*this);
        operator--();
        return tmp;
    }

    ModInt operator-() const { return ModInt(-x); }

    ModInt operator+(const ModInt &rhs) const { return ModInt(*this) += rhs; }

    ModInt operator-(const ModInt &rhs) const { return ModInt(*this) -= rhs; }

    ModInt operator*(const ModInt &rhs) const { return ModInt(*this) *= rhs; }

    ModInt operator/(const ModInt &rhs) const { return ModInt(*this) /= rhs; }

    bool operator==(const ModInt &rhs) const { return x == rhs.x; }

    bool operator!=(const ModInt &rhs) const { return x != rhs.x; }

    ModInt inverse() const {
        int a = x, b = mod, u = 1, v = 0, t;
        while (b > 0) {
            t = a / b;
            swap(a -= t * b, b);
            swap(u -= t * v, v);
        }
        return ModInt(u);
    }

    ModInt pow(int64_t n) const {
        ModInt res(1), mul(x);
        while (n > 0) {
            if(n & 1) res *= mul;
            mul *= mul;
            n >>= 1;
        }
        return res;
    }

    friend ostream &operator<<(ostream &os, const ModInt &rhs) {
        return os << rhs.x;
    }

    friend istream &operator>>(istream &is, ModInt &a) {
        int64_t t;
        is >> t;
        a = ModInt< mod >(t);
        return (is);
    }

    int to_int() const { return x; }

    static int get_mod() { return mod; }
};
using Mint = ModInt<MOD>;

template<int mod, int primitive_root>
struct NTT {
    using mint = ModInt<mod>;
    int get_mod() const { return mod; }
	void _ntt(vector<int64_t> &a, bool inv) {
		int64_t N = a.size();
		int64_t pr = primitive_root;
		static bool is_first = true;
		static vector<mint> vbw(30), vibw(30);
		if (is_first) {
			is_first = false;
			for (size_t i = 0; i < 30; ++i) {
				vbw[i] = mint(pr).pow((mod - 1) >> (i + 1));
				vibw[i] = vbw[i].inverse();
			}
		}
		for (size_t i = 0, j = 1; j < N - 1; ++j) {
			for (size_t k = N >> 1; k > (i ^= k); k >>= 1);
			if (i > j) swap(a[i], a[j]);
		}
		for (size_t k = 0, t = 1; t < N; ++k, t <<= 1) {
			mint bw = vbw[k];
			if (inv) bw = vibw[k];
			for (size_t i = 0; i < N; i += t * 2) {
				mint w = 1;
				for (size_t j = 0; j < t; ++j) {
					int64_t l = i + j, r = i + j + t;
					mint c = a[l], d = w * a[r];
					a[l] = (c + d).to_int();
					a[r] = (c - d).to_int();
					w *= bw;
				}
			}
		}
		if (inv) {
			mint m = mint(N).inverse();
			for (size_t i = 0; i < N; ++i) a[i] = (m * a[i]).to_int();
		}
	}

	vector<int64_t> convolution(vector<int64_t> a, vector<int64_t> b){
        int64_t n = a.size() + b.size() - 1;
        int64_t N = 1;
		while (N < n) N <<= 1;
		a.resize(N); b.resize(N);

		_ntt(a, false);
		_ntt(b, false);

        vector<ll> res(N);
        for (int64_t i = 0; i < N; ++i) {
            res[i] = a[i] * b[i] % mod;
        }

        _ntt(res, true);
        res.resize(n);
        return res;
	}

	void convolution_self(vector<int64_t> &a, vector<int64_t> b){
        int64_t n = a.size() + b.size() - 1;
        int64_t N = 1;
		while (N < n) N <<= 1;
		a.resize(N); b.resize(N);

		_ntt(a, false);
		_ntt(b, false);

        vector<ll> res(N);
        for (int64_t i = 0; i < N; ++i) {
            (a[i] *= b[i]) % mod;
        }

        _ntt(a, true);
        a.resize(n);
	}
};

using NTT_1 = NTT<167772161, 3>; // 2^25 * 5 + 1
using NTT_2 = NTT<469762049, 3>; // 2^26 * 7 + 1
using NTT_3 = NTT<1224736769, 3>; // 2^24 * 73 + 1

template <class T>
struct formal_power_series {
    vector<T> data;
    
    formal_power_series(vector<T> _v) : data(_v) {}

	const T& operator[](const int64_t x) const {
        return data[x];
    }

    size_t size() const {
        return data.size();
    }

    void resize(size_t _sz) {
        data.resize(_sz);
    }

    void pow(int64_t x) {
        NTT<MOD_N, 3> ntt;
        int64_t n = size();
        vector<int64_t> ans(n);
        ans[0] = 1;
        while (x) {
            if (x & 1) {
                ntt.convolution_self(ans, data);
                ans.resize(n);
            }
            x >>= 1;
            ntt.convolution_self(data, data);
            resize(n);
        }
        swap(data, ans);
    }

    void conv_naive(const formal_power_series &a) {
        int64_t n = size() + a.size() - 1;
        vector<T> ans(n);
        for (size_t i = 0; i < a.size(); ++i) {
            if (a[i] == 0) continue;
            for (size_t j = 0; j < size(); ++j) {
                ans[i + j] += data[j] * a[i];
            }
        }
        swap(data, ans);
    }

	void cumsum() {
		for (size_t i = 0; i < size() - 1; ++i) {
            data[i + 1] += data[i];
        }
	}

	void cumsum_inv() {
		for (size_t i = size() - 1; i > 0; --i) {
            data[i] -= data[i - 1];
        }
	}
};

int64_t inv_mod(int64_t a, int64_t mod) {
	int64_t b = mod, u = 1, v = 0, t;
	while (b > 0) {
		t = a / b;
		swap(a -= t * b, b);
		swap(u -= t * v, v);
	}
	return u >= 0 ? u % mod : (mod - (-u) % mod) % mod;
}

int64_t pow_mod(int64_t a, int64_t n, int64_t mod){
    if (n < 0) return inv_mod(pow_mod(a, -n, mod), mod);
    int64_t res = 1, mul = a;
	while (n > 0) {
        if (n & 1) (res *= mul) %= mod;
        (mul *= mul) %= mod;
		n >>= 1;
	}
	return res;
}

ll garner(vector<ll> r, vector<ll> m, int mod) {
    int64_t n = r.size();
	r.emplace_back(0);
    m.emplace_back(mod);

    vector<ll> coffs(n + 1, 1);
	vector<ll> constants(n + 1, 0);
    for (size_t i = 0; i < n; ++i) {
        int64_t v = (r[i] - constants[i]) * inv_mod(coffs[i], m[i]) % m[i];
		if (v < 0) v += m[i];

		for (size_t j = i + 1; j < n + 1; ++j) {
			(constants[j] += coffs[j] * v) %= m[j];
			(coffs[j] *= m[i]) %= m[j];
		}
    }

    return constants[n];
}

vector<int64_t> convolution(vector<int64_t> a, vector<int64_t> b, int mod) {
    const int64_t n = a.size() + b.size() - 1;
    for (auto& i : a) i %= mod;
	for (auto& i : b) i %= mod;
	NTT_1 ntt1; NTT_2 ntt2; NTT_3 ntt3;
	auto x = ntt1.convolution(a, b);
	auto y = ntt2.convolution(a, b);
	auto z = ntt3.convolution(a, b);

    vector<int64_t> res(n);
	vector<int64_t> r(3), m(3);
    for (int64_t i = 0; i < n; ++i) {
        r[0] = x[i], m[0] = ntt1.get_mod();
		r[1] = y[i], m[1] = ntt2.get_mod();
		r[2] = z[i], m[2] = ntt3.get_mod();
		res[i] = garner(r, m, mod);
    }

    return res;
}

vector<int64_t> power(vector<int64_t> v, int64_t x) {
	int64_t n = v.size();
	vector<int64_t> res(n);
	res[0] = 1;
	while (x > 0) {
		if (x & 1) {
            res = convolution(res, v, MOD);
            res.resize(n);
        }
		x >>= 1;
		v = convolution(v, v, MOD);
		v.resize(n);
    }
    return res;
}

struct combination {
    vector<Mint> fac, finv;

    combination() {
        init(3000000);
    }

    void init(const int n) {
        if (fac.size() > n) return;
        const int m = fac.size();
        fac.resize(n + 1);
        for (int64_t i = m; i <= n; ++i) {
            if (i == 0) fac[i] = 1;
            else fac[i] = fac[i - 1] * i;
        }
        finv.resize(n + 1);
        finv[n] = fac[n].inverse();
        for (int64_t i = n - 1; i >= m; --i) finv[i] = finv[i + 1] * (i + 1);
    }

    Mint combi(int64_t n, int64_t k) {
        if (n < k || n < 0 || k < 0) return 0;
        init(n);
        return fac[n] * finv[k] * finv[n - k];
    }
};
combination combi;

struct FFT {
    using CP = complex<double>;

    void _fft(vector<CP> &a, bool inv) {
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
        for (size_t k = 0, t = 1; t < N; ++k, t <<= 1) {
            CP bw = vbw[k];
            if (inv) bw = vibw[k];
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

    vector<int64_t> convolution(const vector<int64_t> &a, const vector<int64_t> &b) {
        int64_t n = a.size() + b.size() - 1;
        int64_t N = 1;
        while (N < n) N <<= 1;

        vector<CP> va(N), vb(N);
        for (int64_t i = 0; i < a.size(); ++i) {
            va[i] = CP(a[i]);
        }
        for (int64_t i = 0; i < b.size(); ++i) {
            vb[i] = CP(b[i]);
        }

        _fft(va, false);
        _fft(vb, false);

        for (size_t i = 0; i < N; ++i) va[i] *= vb[i];

        _fft(va, true);

        vector<int64_t> res(n);
        for (int64_t i = 0; i < n; ++i) {
            res[i] = int64_t(va[i].real() + 0.5);
        }
        return res;
    }

    void convolution_self(vector<int64_t> &a, const vector<int64_t> &b) {
        int64_t n = a.size() + b.size() - 1;
        int64_t N = 1;
        while (N < n) N <<= 1;

        vector<CP> va(N), vb(N);
        for (int64_t i = 0; i < a.size(); ++i) {
            va[i] = CP(a[i]);
        }
        for (int64_t i = 0; i < b.size(); ++i) {
            vb[i] = CP(b[i]);
        }

        _fft(va, false);
        _fft(vb, false);

        for (size_t i = 0; i < N; ++i) va[i] *= vb[i];

        _fft(va, true);

        a.resize(n);
        for (int64_t i = 0; i < n; ++i) {
            a[i] = int64_t(va[i].real() + 0.5);
        }
    }
};

int main(void) {
    ll n, m;
    cin >> n >> m;
    Vec a(100001);
    rep(i, n) {
        ll t;
        cin >> t;
        ++a[t];
    }
    FFT fft;
    auto v = fft.convolution(a, a);
    // ce(v);

    ll ans = 0;
    repr(i, 200001) {
        if (m == 0) break;
        ans += i * min(m, v[i]);
        m -= min(m, v[i]);
        // ce(ans);
    }
    co(ans);

    return 0;
}
