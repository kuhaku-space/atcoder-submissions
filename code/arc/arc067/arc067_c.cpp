#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/template/template.hpp"
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
#line 3 "/home/kuhaku/atcoder/github/atcoder-lib/lib/math/modint.hpp"

/**
 * @brief modint
 * @details [参考](https://github.com/ei1333/library/blob/master/math/combinatorics/mod-int.cpp)
 *
 * @tparam mod 法
 */

template <int mod>
struct ModInt {
    constexpr ModInt() noexcept : x(0) {}
    constexpr ModInt(int y) noexcept : x(y >= 0 ? y % mod : (mod - 1 - ~y % mod)) {}
    constexpr ModInt(int64_t y) noexcept : x(y >= 0 ? y % mod : (mod - 1 - ~y % mod)) {}

    constexpr ModInt &operator+=(const ModInt &rhs) noexcept {
        if ((this->x += rhs.x) >= mod) this->x -= mod;
        return *this;
    }
    constexpr ModInt &operator-=(const ModInt &rhs) noexcept {
        if ((this->x += mod - rhs.x) >= mod) this->x -= mod;
        return *this;
    }
    constexpr ModInt &operator*=(const ModInt &rhs) noexcept {
        this->x = (int)(1LL * this->x * rhs.x % mod);
        return *this;
    }
    constexpr ModInt &operator/=(const ModInt &rhs) noexcept {
        *this *= rhs.inverse();
        return *this;
    }

    constexpr ModInt &operator++() noexcept {
        if ((++(this->x)) >= mod) this->x -= mod;
        return *this;
    }
    constexpr ModInt operator++(int) noexcept {
        ModInt tmp(*this);
        this->operator++();
        return tmp;
    }
    constexpr ModInt &operator--() noexcept {
        if ((this->x += mod - 1) >= mod) this->x -= mod;
        return *this;
    }
    constexpr ModInt operator--(int) noexcept {
        ModInt tmp(*this);
        this->operator--();
        return tmp;
    }

    constexpr ModInt operator-() const noexcept { return ModInt(-this->x); }
    constexpr ModInt operator+(const ModInt &rhs) const noexcept { return ModInt(*this) += rhs; }
    constexpr ModInt operator-(const ModInt &rhs) const noexcept { return ModInt(*this) -= rhs; }
    constexpr ModInt operator*(const ModInt &rhs) const noexcept { return ModInt(*this) *= rhs; }
    constexpr ModInt operator/(const ModInt &rhs) const noexcept { return ModInt(*this) /= rhs; }

    constexpr bool operator==(const ModInt &rhs) const noexcept { return this->x == rhs.x; }
    constexpr bool operator!=(const ModInt &rhs) const noexcept { return this->x != rhs.x; }

    explicit operator int() const noexcept { return x; }

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

    static int get_mod() noexcept { return mod; }

  private:
    int x;
};
#line 3 "/home/kuhaku/atcoder/github/atcoder-lib/lib/math/combination.hpp"

template <int mod>
struct Combination {
    using mint = ModInt<mod>;

    Combination() : _fact(), _finv() {}

    mint operator()(int n, int k) {
        if (n < k || n < 0 || k < 0) return 0;
        this->_init(n);
        return this->_fact[n] * this->_finv[k] * this->_finv[n - k];
    }

    mint fact(int x) {
        assert(x >= 0);
        this->_init(x);
        return this->_fact[x];
    }

    mint finv(int x) {
        assert(x >= 0);
        this->_init(x);
        return this->_finv[x];
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
        this->_init(n);
        return this->_fact[n] * this->_finv[n - k];
    }

  private:
    vector<mint> _fact, _finv;

    void _init(int n) {
        if (this->_fact.size() > n) return;
        int m = this->_fact.size();
        this->_fact.resize(n + 1);
        for (int i = m; i <= n; ++i) {
            if (i == 0)
                this->_fact[i] = 1;
            else
                this->_fact[i] = this->_fact[i - 1] * i;
        }
        this->_finv.resize(n + 1);
        this->_finv[n] = this->_fact[n].inverse();
        for (int i = n - 1; i >= m; --i) this->_finv[i] = this->_finv[i + 1] * (i + 1);
    }
};
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/template/atcoder.hpp"
#pragma GCC target("avx")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#line 6 "/home/kuhaku/atcoder/github/atcoder-lib/lib/template/atcoder.hpp"
using ll = int64_t;
using ld = long double;
#define FOR(i, m, n) for(int i = (m); i < (n); ++i)
#define FORR(i, m, n) for(int i = (m)-1; i >= (n); --i)
#define FORL(i, m, n) for(ll i = (m); i < (n); ++i)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FOR(i, 1, n+1)
#define repr(i, n) FORR(i, n, 0)
#define repnr(i, n) FORR(i, n+1, 1)
#define all(s) (s).begin(), (s).end()
template<class T, class U>
istream &operator>>(istream &is, pair<T, U> &p) { is >> p.first >> p.second; return is; }
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
#line 5 "a.cpp"

using Mint = ModInt<MOD>;
Combination<MOD> combi;

int main(void) {
    sonic();
    int n, a, b, c, d;
    cin >> n >> a >> b >> c >> d;

    vector<Mint> dp(n + 1);
    dp[n] = 1;
    for (int i = a; i <= b; ++i) {
        auto v = dp;
        for (int j = 1; j <= n; ++j) {
            for (int k = c; k <= min(d, j / i); ++k) {
                dp[j - k * i] += v[j] * combi(j, k * i) * combi.fact(k * i) / combi.fact(i).pow(k) /
                                 combi.fact(k);
            }
        }
    }
    co(dp[0]);

    return 0;
}
