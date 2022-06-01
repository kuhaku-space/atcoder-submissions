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
constexpr int Inf = 1000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
const double PI = acos(-1);

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

int main(void) {
    ll a, b;
    cin >> a >> b;

    vector<bitset<20>> fs(b - a + 1);
    vector<int> prime = {2,  3,  5,  7,  11, 13, 17, 19, 23, 29,
                         31, 37, 41, 43, 47, 53, 59, 61, 67, 71};
    rep(i, b - a + 1) {
        rep(j, 20) {
            if ((a + i) % prime[j] == 0)
                fs[i][j] = true;
        }
    }

    int sz = 1 << 20;
    vector<Mint> dp(sz);
    dp[0] = 1;
    rep(i, b - a + 1) {
        rep(j, sz) {
            bitset<20> b(j);
            if ((b & fs[i]) == bitset<20>()) {
                dp[(b | fs[i]).to_ullong()] += dp[b.to_ullong()];
            }
        }
    }

    co(accumulate(all(dp), Mint(0)));

    return 0;
}
