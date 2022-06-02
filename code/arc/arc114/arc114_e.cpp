#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ld = long double;
using Pi = pair<int, int>;
using Pl = pair<ll, ll>;
using Vi = vector<int>;
using Vl = vector<ll>;
using Vp = vector<Pl>;
template <class T>
using Vv = vector<vector<T>>;
#define FOR(i, m, n) for (int i = (m); i < (n); ++i)
#define FORR(i, m, n) for (int i = (m)-1; i >= (n); --i)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FOR(i, 1, n + 1)
#define repr(i, n) FORR(i, n, 0)
#define repnr(i, n) FORR(i, n + 1, 1)
#define all(s) (s).begin(), (s).end()
template <class T, class U>
bool chmax(T &a, const U b) {
    return a < b ? a = b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U b) {
    return b < a ? a = b, true : false;
}
template <class T>
istream &operator>>(istream &is, vector<T> &v) {
    for (T &i : v) is >> i;
    return is;
}
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    for (const T &i : v) os << i << ' ';
    return os;
}
void _co() {
    cout << '\n';
}
template <class Head, class... Tail>
void _co(Head &&head, Tail &&...tail) {
    cout << ' ' << head;
    _co(forward<Tail>(tail)...);
}
template <class Head, class... Tail>
void co(Head &&head, Tail &&...tail) {
    cout << head;
    _co(forward<Tail>(tail)...);
}
void ce() {
    cerr << '\n';
}
template <class Head, class... Tail>
void ce(Head &&head, Tail &&...tail) {
    cerr << head << ' ';
    ce(forward<Tail>(tail)...);
}
void sonic() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}
void setp(const int n) {
    cout << fixed << setprecision(n);
}
constexpr int64_t INF = 1000000000000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
const double PI = acos(-1);

template <int mod>
struct ModInt {
    int64_t x;

    ModInt() : x(0) {
    }

    ModInt(int64_t y) noexcept
        : x(y >= 0 ? y % mod : (mod - 1 - (-y - 1) % mod)) {
    }

    ModInt &operator+=(const ModInt &rhs) noexcept {
        if ((x += rhs.x) >= mod)
            x -= mod;
        return *this;
    }
    ModInt &operator-=(const ModInt &rhs) noexcept {
        if ((x += mod - rhs.x) >= mod)
            x -= mod;
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
        if ((++x) >= mod)
            x -= mod;
        return *this;
    }
    ModInt operator++(int) noexcept {
        ModInt tmp(*this);
        operator++();
        return tmp;
    }
    ModInt &operator--() noexcept {
        if ((x += mod - 1) >= mod)
            x -= mod;
        return *this;
    }
    ModInt operator--(int) noexcept {
        ModInt tmp(*this);
        operator--();
        return tmp;
    }

    ModInt operator-() const noexcept {
        return ModInt(-x);
    }
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

    bool operator==(const ModInt &rhs) const noexcept {
        return x == rhs.x;
    }
    bool operator!=(const ModInt &rhs) const noexcept {
        return x != rhs.x;
    }

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
            if (n & 1)
                res *= mul;
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

    int to_int() const noexcept {
        return x;
    }

    static int get_mod() noexcept {
        return mod;
    }
};
using Mint = ModInt<MOD_N>;

template <int mod>
struct math_mod {
    using mint = ModInt<mod>;
    vector<mint> fac, finv;

    math_mod() {
        _init(1 << 22);
    }

    void _init(int64_t n) {
        if (fac.size() > n)
            return;
        int m = fac.size();
        fac.resize(n + 1);
        for (int64_t i = m; i <= n; ++i) {
            if (i == 0)
                fac[i] = 1;
            else
                fac[i] = fac[i - 1] * i;
        }
        finv.resize(n + 1);
        finv[n] = fac[n].inverse();
        for (int64_t i = n - 1; i >= m; --i) finv[i] = finv[i + 1] * (i + 1);
    }

    mint fact(int64_t x) {
        assert(x >= 0);
        _init(x);
        return fac[x];
    }

    mint combi(int64_t n, int64_t k) {
        if (n < k || n < 0 || k < 0)
            return 0;
        _init(n);
        return fac[n] * finv[k] * finv[n - k];
    }

    mint combi_naive(int64_t n, int64_t k) const {
        if (n < k || n < 0 || k < 0)
            return 0;
        if (n - k < k)
            k = n - k;
        mint res = 1;
        for (int64_t i = 0; i < k; ++i) {
            res *= n - i;
            res /= i + 1;
        }
        return res;
    }

    mint permu(int64_t n, int64_t k) {
        if (n < k || n < 0 || k < 0)
            return 0;
        _init(n);
        return fac[n] * finv[n - k];
    }
};
math_mod<MOD_N> math;

int main(void) {
    ll h, w;
    cin >> h >> w;
    ll h1, w1, h2, w2;
    cin >> h1 >> w1 >> h2 >> w2;
    h1--, w1--, h2--, w2--;

    if (h1 > h2)
        swap(h1, h2);
    if (w1 > w2)
        swap(w1, w2);

    Mint ans = 0;
    rep(_, 2) {
        rep(i, h - 1) {
            int cnt = w2 - w1;
            if (h1 <= i && i < h2)
                cnt += h2 - h1;
            else if (i < h1)
                cnt += h2 - i;
            else
                cnt += i - h1 + 1;
            ans += Mint(cnt).inverse();
        }
        swap(h1, w1);
        swap(h2, w2);
        swap(h, w);
    }

    co(ans);

    return 0;
}
