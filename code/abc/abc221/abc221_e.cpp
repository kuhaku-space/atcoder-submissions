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
#line 2 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/binary_tree/BIT.hpp"

/**
 * @brief Binary Indexed Tree
 */
template <class T>
struct BIT {
    int N;
    vector<T> data;

    BIT() : N(), data() {}
    BIT(int n, T e = T(0)) : N(n + 1), data(n + 1, e) {}
    BIT(const vector<T> &v) : N(v.size() + 1), data(v.size() + 1) { this->build(v); }

    const T &operator[](int i) const { return this->at(i); }
    const T at(int k) const { return this->sum(k + 1) - this->sum(k); }
    const T get(int k) const { return this->sum(k + 1) - this->sum(k); }

    template <class U>
    void build(const vector<U> &v) {
        int n = v.size();
        for (int i = 0; i < n; ++i) this->add(i, v[i]);
    }

    /**
     * @brief v[k] = x
     *
     * @param k index
     * @param x data
     * @return void
     */
    void update(int k, T x) { this->add(k, x - this->at(k)); }
    /**
     * @brief v[k] += x
     *
     * @param k index
     * @param x data
     * @return void
     */
    void add(int k, T x) {
        assert(0 <= k && k < this->N);
        for (++k; k < N; k += k & -k) this->data[k] += x;
    }
    /**
     * @brief chmax(v[k], x)
     *
     * @param k index
     * @param x data
     * @return bool
     */
    bool chmax(int k, T x) {
        if (this->at(k) >= x) return false;
        this->update(k, x);
        return true;
    }
    /**
     * @brief chmin(v[k], x)
     *
     * @param k index
     * @param x data
     * @return bool
     */
    bool chmin(int k, T x) {
        if (this->at(k) <= x) return false;
        this->update(k, x);
        return true;
    }

    /**
     * @brief v[0] + ... + v[n - 1]
     *
     * @return T
     */
    T sum() const { return this->sum(this->N); }
    /**
     * @brief v[0] + ... + v[k - 1]
     *
     * @param k index
     * @return T
     */
    T sum(int k) const {
        assert(0 <= k && k <= this->N);
        T res = 0;
        for (; k > 0; k -= k & -k) res += this->data[k];
        return res;
    }
    /**
     * @brief v[a] + ... + v[b - 1]
     *
     * @param a first index
     * @param b last index
     * @return T
     */
    T sum(int a, int b) const { return this->sum(b) - this->sum(a); }

    /**
     * @brief BIT上で二分探索
     *
     * @param x data
     * @return int
     */
    int lower_bound(T x) const {
        if (x <= 0) return 0;
        int k = 1;
        while (k < this->N) k <<= 1;
        int res = 0;
        for (; k > 0; k >>= 1) {
            if (res + k < N && this->data[res + k] < x) x -= this->data[res += k];
        }
        return res;
    }
};
#line 3 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/math/modint.hpp"

/**
 * @brief modint
 * @ref https://github.com/ei1333/library/blob/master/math/combinatorics/mod-int.cpp "参考"
 *
 * @tparam mod 法
 */

template <int mod>
struct ModInt {
    int x;

    constexpr ModInt() : x(0) {}
    constexpr ModInt(int64_t y) noexcept : x(y >= 0 ? y % mod : (mod - 1 - ~y % mod)) {}

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
#line 2 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/template/atcoder.hpp"
#pragma GCC target("avx")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#line 6 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/template/atcoder.hpp"
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
#line 5 "a.cpp"

using Mint = ModInt<MOD_N>;

int main(void) {
    sonic();
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;

    vector<int> idx(n);
    iota(all(idx), 0);
    sort(all(idx), [&](auto x, auto y) {
        return a[x] == a[y] ? x < y : a[x] < a[y];
    });
    vector<int> v(n);
    rep(i, n) v[idx[i]] = i;
    // ce(v);

    Mint ans = 0;
    BIT<Mint> bit(n);
    repr(i, n) {
        // ce(bit.sum(v[i], n), bit.sum(v[i], n) / Mint(2).pow(v[i]));
        ans += bit.sum(v[i], n) / Mint(2).pow(i);
        bit.add(v[i], Mint(2).pow(i - 1));
    }
    co(ans);

    return 0;
}
