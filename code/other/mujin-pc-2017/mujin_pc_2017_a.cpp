#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/template/template.hpp"
#include <bits/stdc++.h>
using namespace std;
template <class T, class U>
bool chmax(T &a, const U &b) {
    return a < b ? a = b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U &b) {
    return b < a ? a = b, true : false;
}
constexpr int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
const double PI = acos(-1.0);
#line 3 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/algo/modint.hpp"

/**
 * @brief modint
 * 
 * @tparam mod 法
 * @ref https://github.com/ei1333/library/blob/master/math/combinatorics/mod-int.cpp "参考"
 */

template <int mod>
struct ModInt {
    int x;

    constexpr ModInt() : x(0) {}
    constexpr ModInt(int64_t y) noexcept : x(y >= 0 ? y % mod : (mod - 1 - (-y - 1) % mod)) {}

    constexpr ModInt &operator+=(const ModInt &rhs) noexcept {
        if ((x += rhs.x) >= mod) x -= mod;
        return *this;
    }
    constexpr ModInt &operator-=(const ModInt &rhs) noexcept {
        if ((x += mod - rhs.x) >= mod) x -= mod;
        return *this;
    }
    constexpr ModInt &operator*=(const ModInt &rhs) noexcept {
        x = (int)(1LL * x * rhs.x % mod);
        return *this;
    }
    constexpr ModInt &operator/=(const ModInt &rhs) noexcept {
        *this *= rhs.inverse();
        return *this;
    }

    constexpr ModInt &operator++() noexcept {
        if ((++x) >= mod) x -= mod;
        return *this;
    }
    constexpr ModInt operator++(int) noexcept {
        ModInt tmp(*this);
        operator++();
        return tmp;
    }
    constexpr ModInt &operator--() noexcept {
        if ((x += mod - 1) >= mod) x -= mod;
        return *this;
    }
    constexpr ModInt operator--(int) noexcept {
        ModInt tmp(*this);
        operator--();
        return tmp;
    }

    constexpr ModInt operator-() const noexcept { return ModInt(-x); }
    constexpr ModInt operator+(const ModInt &rhs) const noexcept { return ModInt(*this) += rhs; }
    constexpr ModInt operator-(const ModInt &rhs) const noexcept { return ModInt(*this) -= rhs; }
    constexpr ModInt operator*(const ModInt &rhs) const noexcept { return ModInt(*this) *= rhs; }
    constexpr ModInt operator/(const ModInt &rhs) const noexcept { return ModInt(*this) /= rhs; }

    constexpr bool operator==(const ModInt &rhs) const noexcept { return x == rhs.x; }
    constexpr bool operator!=(const ModInt &rhs) const noexcept { return x != rhs.x; }

    constexpr ModInt inverse() const noexcept {
        int a = x, b = mod, u = 1, v = 0, t;
        while (b > 0) {
            t = a / b;
            swap(a -= t * b, b);
            swap(u -= t * v, v);
        }
        return ModInt(u);
    }

    constexpr ModInt pow(int64_t n) const noexcept { return ModInt(*this).pow_self(n); }
    constexpr ModInt &pow_self(int64_t n) noexcept {
        ModInt res(1);
        for (; n > 0; n >>= 1) {
            if (n & 1) res *= *this;
            *this *= *this;
        }
        *this = res;
        return *this;
    }

    friend istream &operator>>(istream &is, ModInt &rhs) {
        int64_t t;
        is >> t;
        rhs = ModInt<mod>(t);
        return (is);
    }
    friend ostream &operator<<(ostream &os, const ModInt &rhs) { return os << rhs.x; }

    int to_int() const noexcept { return x; }

    static int get_mod() noexcept { return mod; }
};
#line 3 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/template/atcoder.hpp"
using ll = int64_t;
using ld = long double;
#define FOR(i, m, n) for(int i = (m); i < (n); ++i)
#define FORR(i, m, n) for(int i = (m)-1; i >= (n); --i)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FOR(i, 1, n+1)
#define repr(i, n) FORR(i, n, 0)
#define repnr(i, n) FORR(i, n+1, 1)
#define all(s) (s).begin(), (s).end()
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
#line 3 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/math/combination.hpp"

template <int mod>
struct Combination {
    using mint = ModInt<mod>;
    vector<mint> _fact, _finv;

    Combination() : _fact(), _finv() {}

    mint operator()(int n, int k) {
        if (n < k || n < 0 || k < 0) return 0;
        _init(n);
        return _fact[n] * _finv[k] * _finv[n - k];
    }

    void _init(int n) {
        if (_fact.size() > n) return;
        int m = _fact.size();
        _fact.resize(n + 1);
        for (int i = m; i <= n; ++i) {
            if (i == 0)
                _fact[i] = 1;
            else
                _fact[i] = _fact[i - 1] * i;
        }
        _finv.resize(n + 1);
        _finv[n] = _fact[n].inverse();
        for (int i = n - 1; i >= m; --i) _finv[i] = _finv[i + 1] * (i + 1);
    }

    mint fact(int x) {
        assert(x >= 0);
        _init(x);
        return _fact[x];
    }

    mint finv(int x) {
        assert(x >= 0);
        _init(x);
        return _finv[x];
    }

    mint naive(int n, int k) const {
        if (n < k || n < 0 || k < 0) return 0;
        if (n - k < k) k = n - k;
        mint res = 1;
        for (int i = 0; i < k; ++i) {
            res *= n - i;
            res /= i + 1;
        }
        return res;
    }

    mint lucas(int n, int k) {
        if (n < k || n < 0 || k < 0) return 0;
        if (n - k < k) k = n - k;
        static vector<vector<mint>> v;
        if (v.empty()) {
            v = vector<vector<mint>>(mod, vector<mint>(mod));
            for (int i = 0; i < mod; ++i) v[i][0] = 1;
            for (int i = 0; i < mod; ++i) {
                for (int j = 1; j < mod; ++j) {
                    if (i < j)
                        v[i][j] = 0;
                    else if (i - j < j)
                        v[i][j] = v[i][i - j];
                    else
                        v[i][j] = v[i][j - 1] * mint(i + 1 - j) / mint(j);
                }
            }
        }
        mint res = 1;
        while (n || k) {
            res *= v[n % mod][k % mod];
            n /= mod, k /= mod;
        }
        return res;
    }

    mint permu(int n, int k) {
        if (n < k || n < 0 || k < 0) return 0;
        _init(n);
        return _fact[n] * _finv[n - k];
    }
};
Combination<MOD> combi;
#line 5 "a.cpp"

using Mint = ModInt<MOD>;

int main(void) {
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;

    Mint ans = 1;
    int cnt = 0;
    rep(i, n) {
        if (a[i] >= cnt * 2 + 1) {
            ++cnt;
        } else {
            ans *= cnt + 1;
        }
    }
    co(ans * combi.fact(cnt));

    return 0;
}
