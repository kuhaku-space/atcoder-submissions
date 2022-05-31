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
template <class T1, class T2>
bool chmax(T1 &a, const T2 b) { if (a < b) { a = b; return true; } return false; }
template <class T1, class T2>
bool chmin(T1 &a, const T2 b) { if (a > b) { a = b; return true; } return false; }
template <class T>
istream &operator>>(istream &is, vector<T> &v) { for (T &i : v) is >> i; return is; }
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) { for (const T &i : v) os << i << ' '; return os; }
void co() { cout << '\n'; }
template <class Head, class... Tail>
void co(Head&& head, Tail&&... tail) { cout << head << ' '; co(forward<Tail>(tail)...); }
void ce() { cerr << '\n'; }
template <class Head, class... Tail>
void ce(Head&& head, Tail&&... tail) { cerr << head << ' '; ce(forward<Tail>(tail)...); }
void sonic() { ios::sync_with_stdio(false); cin.tie(nullptr); }
void setp(const int n) { cout << fixed << setprecision(n); }
constexpr int64_t LINF = 1000000000000000001;
constexpr int64_t MOD = 1000000007;
constexpr int64_t MOD_N = 998244353;
constexpr long double EPS = 1e-11;
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

template <int mod>
struct math_mod {
    using mint = ModInt<mod>;
    vector<mint> fac, finv;

    math_mod() {
        _init(3000000);
    }

    void _init(const int64_t n) {
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

    mint fact(int64_t x) {
        assert(x >= 0 && x < fac.size());
        return fac[x];
    }

    mint combi(int64_t n, int64_t k) {
        if (n < k || n < 0 || k < 0) return 0;
        if (k * 2 > n) k = n - k;
        if (k < 10000000) {
            mint ans = 1;
            rep(i, k) ans *= n - i;
            rep(i, k) ans /= i + 1;
            return ans;
        }
        _init(n);
        return fac[n] * finv[k] * finv[n - k];
    }

    mint permu(int64_t n, int64_t k) {
        if (n < k || n < 0 || k < 0) return 0;
        _init(n);
        return fac[n] * finv[n - k];
    }
};
math_mod<MOD> math;

int main(void) {
    ll n, m;
    cin >> n >> m;
    Vec a(n);
    cin >> a;

    ll s = accumulate(all(a), 0LL);

    co(math.combi(n + m, m - s));

    return 0;
}