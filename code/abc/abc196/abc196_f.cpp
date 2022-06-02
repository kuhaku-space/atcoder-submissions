// clang-format off
#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ld = long double;
using Pi = pair<int, int>;
using Pl = pair<ll, ll>;
using Vi = vector<int>;
using Vl = vector<ll>;
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
istream &operator>>(istream &is, vector<T> &v) { for (T &i : v) is >> i; return is; }
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) { for (const T &i : v) os << i << ' '; return os; }
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
// clang-format on

template <int mod>
struct ModInt {
    int64_t x;

    ModInt() : x(0) {}

    ModInt(int64_t y) noexcept
        : x(y >= 0 ? y % mod : (mod - 1 - (-y - 1) % mod)) {}

    ModInt &operator+=(const ModInt &rhs) noexcept {
        if ((x += rhs.x) >= mod) x -= mod;
        return *this;
    }
    ModInt &operator-=(const ModInt &rhs) noexcept {
        if ((x += mod - rhs.x) >= mod) x -= mod;
        return *this;
    }
    ModInt &operator*=(const ModInt &rhs) noexcept {
        x = (int)(1LL * x * rhs.x % mod);
        return *this;
    }
    ModInt &operator/=(const ModInt &rhs) noexcept {
        *this *= rhs.inverse();
        return *this;
    }

    ModInt &operator++() noexcept {
        if ((++x) >= mod) x -= mod;
        return *this;
    }
    ModInt operator++(int) noexcept {
        ModInt tmp(*this);
        operator++();
        return tmp;
    }
    ModInt &operator--() noexcept {
        if ((x += mod - 1) >= mod) x -= mod;
        return *this;
    }
    ModInt operator--(int) noexcept {
        ModInt tmp(*this);
        operator--();
        return tmp;
    }

    ModInt operator-() const noexcept { return ModInt(-x); }
    ModInt operator+(const ModInt &rhs) const noexcept {
        return ModInt(*this) += rhs;
    }
    ModInt operator-(const ModInt &rhs) const noexcept {
        return ModInt(*this) -= rhs;
    }
    ModInt operator*(const ModInt &rhs) const noexcept {
        return ModInt(*this) *= rhs;
    }
    ModInt operator/(const ModInt &rhs) const noexcept {
        return ModInt(*this) /= rhs;
    }

    bool operator==(const ModInt &rhs) const noexcept { return x == rhs.x; }
    bool operator!=(const ModInt &rhs) const noexcept { return x != rhs.x; }

    ModInt inverse() const noexcept {
        int a = x, b = mod, u = 1, v = 0, t;
        while (b > 0) {
            t = a / b;
            swap(a -= t * b, b);
            swap(u -= t * v, v);
        }
        return ModInt(u);
    }

    ModInt pow(int64_t n) const noexcept {
        ModInt res(1), mul(x);
        for (; n > 0; n >>= 1) {
            if (n & 1) res *= mul;
            mul *= mul;
        }
        return res;
    }

    void pow_self(int64_t n) noexcept {
        ModInt tmp = pow(n);
        swap(*this, tmp);
    }

    friend istream &operator>>(istream &is, ModInt &rhs) {
        int64_t t;
        is >> t;
        rhs = ModInt<mod>(t);
        return (is);
    }

    friend ostream &operator<<(ostream &os, const ModInt &rhs) {
        return os << rhs.x;
    }

    int to_int() const noexcept { return x; }

    static int get_mod() noexcept { return mod; }
};
using Mint = ModInt<MOD>;

template <int mod, int primitive_root>
struct NTT {
    using mint = ModInt<mod>;
    const int get_mod() const { return mod; }
    template <class T>
    void _ntt(vector<T> &a, bool inv) {
        int N = a.size();
        int pr = primitive_root;
        static bool is_first = true;
        static vector<mint> vbw(30), vibw(30);
        if (is_first) {
            is_first = false;
            for (int i = 0; i < 30; ++i) {
                vbw[i] = mint(pr).pow((mod - 1) >> (i + 1));
                vibw[i] = vbw[i].inverse();
            }
        }
        for (int i = 0, j = 1; j < N - 1; ++j) {
            for (int k = N >> 1; k > (i ^= k); k >>= 1)
                ;
            if (i > j) swap(a[i], a[j]);
        }
        for (int k = 0, t = 1; t < N; ++k, t <<= 1) {
            mint bw = vbw[k];
            if (inv) bw = vibw[k];
            for (int i = 0; i < N; i += t * 2) {
                mint w = 1;
                for (int j = 0; j < t; ++j) {
                    int l = i + j, r = i + j + t;
                    mint c = a[l], d = w * a[r];
                    a[l] = (c + d).to_int();
                    a[r] = (c - d).to_int();
                    w *= bw;
                }
            }
        }
        if (inv) {
            int m = mint(N).inverse().to_int();
            for (int i = 0; i < N; ++i) a[i] = T(1LL * a[i] * m % mod);
        }
    }

    template <class T>
    void convolution_self(vector<T> &a, vector<T> b) {
        int n = a.size() + b.size() - 1;
        int N = 1;
        while (N < n) N <<= 1;
        a.resize(N), b.resize(N);

        _ntt(a, false), _ntt(b, false);

        for (int i = 0; i < N; ++i) a[i] = T(1LL * a[i] * b[i] % mod);

        _ntt(a, true);
        a.resize(n);
    }

    template <class T>
    vector<T> convolution(const vector<T> &a, const vector<T> &b) {
        vector<T> res = a;
        convolution_self(res, b);
        return res;
    }
};

using NTT_N = NTT<MOD_N, 3>;
NTT_N ntt;

int main(void) {
    string s, t;
    cin >> s >> t;
    int n = s.size();
    int m = t.size();

    reverse(all(t));

    vector<int> a(n), b(n), c(m), d(m);
    rep(i, n) {
        a[i] = s[i] == '0';
        b[i] = 1 - a[i];
    }
    rep(i, m) {
        c[i] = t[i] == '0';
        d[i] = 1 - c[i];
    }

    ntt.convolution_self(a, d);
    ntt.convolution_self(b, c);
    rep(i, a.size()) a[i] += b[i];
    // ce(a);

    int ans = Inf;
    FOR(i, m - 1, n) {
        chmin(ans, a[i]);
    }
    co(ans);

    return 0;
}
