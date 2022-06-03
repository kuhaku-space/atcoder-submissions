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
constexpr int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
const double PI = acos(-1);

template <class T>
struct Matrix {
    vector<vector<T>> v;

    Matrix(int64_t x) { v = vector<vector<T>>(x, vector<T>(x)); }
    Matrix(int64_t x, int64_t y) { v = vector<vector<T>>(x, vector<T>(y)); }
    Matrix(const vector<vector<T>> &_v) : v(_v) {}

    const vector<T> &operator[](const int64_t i) const {
        assert(i >= 0 && i < v.size());
        return v[i];
    }
    vector<T> &operator[](const int64_t i) {
        assert(i >= 0 && i < v.size());
        return v[i];
    }

    Matrix &operator+=(const Matrix &rhs) {
        assert(v.size() == rhs.v.size());
        assert(v[0].size() == rhs.v[0].size());
        for (int64_t i = 0; i < v.size(); ++i) {
            for (int64_t j = 0; j < v[0].size(); ++j) v[i][j] += rhs.v[i][j];
        }
        return *this;
    }
    Matrix &operator-=(const Matrix &rhs) {
        assert(v.size() == rhs.v.size());
        assert(v[0].size() == rhs.v[0].size());
        for (int64_t i = 0; i < v.size(); ++i) {
            for (int64_t j = 0; j < v[0].size(); ++j) v[i][j] -= rhs.v[i][j];
        }
        return *this;
    }
    Matrix &operator*=(const Matrix &rhs) {
        assert(v[0].size() == rhs.v.size());
        int64_t x = v.size(), y = rhs.v[0].size(), z = rhs.v.size();
        vector<vector<T>> tmp(x, vector<T>(y));
        for (int64_t i = 0; i < x; ++i) {
            for (int64_t k = 0; k < z; ++k) {
                for (int64_t j = 0; j < y; ++j) 
                    tmp[i][j] += v[i][k] * rhs.v[k][j];
            }
        }
        swap(v, tmp);
        return *this;
    }

    Matrix operator-() const {
        vector<vector<T>> tmp = v;
        for (auto &i : tmp)
            for (auto &j : i) j = -j;
        return Matrix(tmp);
    }

    Matrix operator+(const Matrix &rhs) const { return Matrix(*this) += rhs; }
    Matrix operator-(const Matrix &rhs) const { return Matrix(*this) -= rhs; }
    Matrix operator*(const Matrix &rhs) const { return Matrix(*this) *= rhs; }

    Matrix pow(int64_t n) const {
        Matrix res(v), mul(v);
        res.unit_matrix();
        for (; n > 0; n >>= 1) {
            if (n & 1) res *= mul;
            mul *= mul;
        }
        return res;
    }

    void unit_matrix() {
        assert(v.size() == v[0].size());
        int64_t n = v.size();
        for (int64_t i = 0; i < n; ++i) {
            v[i].assign(n, T(0));
            v[i][i] = T(1);
        }
    }

    Matrix transposed() const {
        int64_t x = v[0].size(), y = v.size();
        vector<vector<T>> res(x, vector<T>(y));
        for (int64_t i = 0; i < x; ++i) {
            for (int64_t j = 0; j < y; ++j) {
                res[i][j] = v[j][i];
            }
        }
        return Matrix(res);
    }

    void print_debug() const {
        for (auto i : v) {
            cerr << "[";
            for (auto j : i) cerr << j << ", ";
            cerr << "]" << endl;
        }
    }
};

template <int mod>
struct ModInt {
    int x;

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

    ModInt pow(int64_t n) const noexcept { return ModInt(*this).pow_self(n); }
    ModInt &pow_self(int64_t n) noexcept {
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
    friend ostream &operator<<(ostream &os, const ModInt &rhs) {
        return os << rhs.x;
    }

    int to_int() const noexcept { return x; }

    static int get_mod() noexcept { return mod; }
};
using Mint = ModInt<MOD_N>;

// clang-format on

int main(void) {
    ll h, w;
    cin >> h >> w;

    Matrix<Mint> mt(1 << h), f(1, 1 << h);
    f[0][0] = 1;

    rep(i, 1 << h) {
        rep(j, 1 << h) {
            vector<vector<Mint>> a(2, vector<Mint>(2));
            auto b = a;
            a[0][0] = 1;
            rep(k, h) {
                if (i >> k & 1) {
                    if (j >> k & 1) {
                    } else {
                        b[0][0] = a[0][0] + a[1][1];
                    }
                } else {
                    if (j >> k & 1) {
                        b[1][1] = a[0][0] + a[1][1];
                    } else {
                        b[0][1] = a[0][0] + a[1][1];
                        b[0][0] = a[0][0] + a[1][1] + a[0][1];
                    }
                }
                a = b;
                b[0][0] = b[0][1] = b[1][0] = b[1][1] = 0;
            }
            mt[i][j] = (j >> (h - 1) & 1) ? a[1][1] : a[0][0];
            // ce(i, j, mt[i][j]);
        }
    }

    co((f * mt.pow(w))[0][0]);

    return 0;
}
