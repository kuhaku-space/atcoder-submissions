#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/template/atcoder.hpp"
#pragma GCC target("avx")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
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
#line 2 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/tree/union_find.hpp"

/**
 * @brief 素集合データ構造
 *
 */
struct union_find {
    vector<int> data;

    union_find() : data() {}
    union_find(int _n) : data(_n, -1) {}

    int root(int x) { return data[x] < 0 ? x : data[x] = this->root(data[x]); }

    bool is_root(int x) { return data[x] < 0; }

    void unite(int x, int y) {
        x = this->root(x), y = this->root(y);
        if (x != y) {
            if (data[x] > data[y]) swap(x, y);
            data[x] += data[y];
            data[y] = x;
        }
    }

    int size(int x) { return -data[this->root(x)]; }

    bool same(int x, int y) { return this->root(x) == this->root(y); }
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

    int to_int() const noexcept { return x; }

    static int get_mod() noexcept { return mod; }
};
#line 5 "a.cpp"

int main(void) {
    sonic();
    int n, m;
    cin >> n >> m;
    vector<int> u(m), v(m);
    rep(i, m){
        cin >> u[i] >> v[i];
        --u[i], --v[i];
    }

    if (n != m) {
        co(0);
        return 0;
    }

    union_find uf(n);
    rep(i, m) {
        uf.unite(u[i], v[i]);
    }

    vector<int> cnt(n);
    rep(i, m){
        cnt[uf.root(u[i])]++;
    }

    using Mint = ModInt<MOD_N>;

    int ans = 0;
    rep(i, n){
        if (uf.is_root(i)){
            if (uf.size(i)!=cnt[i]) {
                co(0);
                return 0;
            }
            ++ans;
        }
    }

    co(Mint(2).pow(ans));

    return 0;
}
