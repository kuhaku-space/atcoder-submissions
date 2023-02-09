#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/home/github/algo/lib/template/template.hpp"
#pragma GCC target("sse4.2,avx2,bmi2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
template <class T, class U>
bool chmax(T &a, const U &b) {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U &b) {
    return (T)b < a ? a = (T)b, true : false;
}
constexpr int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
constexpr double PI = M_PI;
#line 3 "/home/kuhaku/home/github/algo/lib/math/modint.hpp"

/**
 * @brief modint
 * @see https://github.com/ei1333/library/blob/master/math/combinatorics/mod-int.cpp
 *
 * @tparam mod 法
 */
template <int mod = MOD_N>
struct ModInt {
    static constexpr int get_mod() noexcept { return mod; }

    constexpr ModInt() noexcept : x(0) {}
    constexpr ModInt(int y) noexcept : x(y >= 0 ? y % mod : (mod - 1 - ~y % mod)) {}
    constexpr ModInt(std::int64_t y) noexcept : x(y >= 0 ? y % mod : (mod - 1 - ~y % mod)) {}

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

    constexpr ModInt pow(std::int64_t n) const noexcept { return ModInt(*this).pow_self(n); }
    constexpr ModInt &pow_self(std::int64_t n) noexcept {
        ModInt res(1);
        for (; n > 0; n >>= 1) {
            if (n & 1) res *= *this;
            *this *= *this;
        }
        *this = res;
        return *this;
    }

    friend std::istream &operator>>(std::istream &is, ModInt &rhs) {
        std::int64_t t;
        is >> t;
        rhs = ModInt<mod>(t);
        return (is);
    }
    friend std::ostream &operator<<(std::ostream &os, const ModInt &rhs) { return os << rhs.x; }

  private:
    int x;
};
#line 2 "/home/kuhaku/home/github/algo/lib/matrix/matrix.hpp"

/**
 * @brief 行列ライブラリ
 *
 * @tparam T 要素の型
 */
template <class T>
struct Matrix {
    Matrix() = default;
    Matrix(int x) : v(x, std::vector<T>(x)) {}
    Matrix(int x, int y) : v(x, std::vector<T>(y)) {}
    Matrix(const std::vector<std::vector<T>> &_v) : v(_v) {}

    const auto &operator[](int i) const { return this->v[i]; }
    auto &operator[](int i) { return this->v[i]; }
    const auto begin() const { return this->v.begin(); }
    auto begin() { return this->v.begin(); }
    const auto end() const { return this->v.end(); }
    auto end() { return this->v.end(); }

    Matrix &operator+=(const Matrix &rhs) {
        assert(this->v.size() == rhs.v.size());
        assert(this->v[0].size() == rhs.v[0].size());
        for (int i = 0; i < this->v.size(); ++i) {
            for (int j = 0; j < this->v[0].size(); ++j) this->v[i][j] += rhs.v[i][j];
        }
        return *this;
    }
    Matrix &operator-=(const Matrix &rhs) {
        assert(this->v.size() == rhs.v.size());
        assert(this->v[0].size() == rhs.v[0].size());
        for (int i = 0; i < this->v.size(); ++i) {
            for (int j = 0; j < this->v[0].size(); ++j) this->v[i][j] -= rhs.v[i][j];
        }
        return *this;
    }
    Matrix &operator*=(const Matrix &rhs) {
        assert(this->v[0].size() == rhs.v.size());
        int x = this->v.size(), y = rhs.v[0].size(), z = rhs.v.size();
        std::vector<std::vector<T>> tmp(x, std::vector<T>(y));
        for (int i = 0; i < x; ++i) {
            for (int k = 0; k < z; ++k) {
                for (int j = 0; j < y; ++j) tmp[i][j] += this->v[i][k] * rhs.v[k][j];
            }
        }
        swap(this->v, tmp);
        return *this;
    }

    Matrix operator-() const {
        std::vector<std::vector<T>> tmp(this->v);
        for (auto &v : tmp)
            for (auto &x : v) x = -x;
        return Matrix(tmp);
    }

    Matrix operator+(const Matrix &rhs) const { return Matrix(*this) += rhs; }
    Matrix operator-(const Matrix &rhs) const { return Matrix(*this) -= rhs; }
    Matrix operator*(const Matrix &rhs) const { return Matrix(*this) *= rhs; }

    std::vector<T> operator*(const std::vector<T> &rhs) {
        assert(this->v[0].size() == rhs.size());
        int x = this->v.size(), y = this->v[0].size();
        std::vector<T> res(x);
        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < y; ++j) res[i] += this->v[i][j] * rhs[j];
        }
        return res;
    }

    T det() const {
        assert(this->v.size() == this->v[0].size());
        std::vector<std::vector<T>> u(v);
        int n = u.size();
        T ans = 1;
        for (int i = 0; i < n; ++i) {
            if (u[i][i] == T(0)) {
                for (int j = i + 1; j < n; ++j) {
                    if (u[j][i] != T(0)) {
                        swap(u[j], u[i]);
                        ans *= -1;
                        break;
                    }
                }
                if (u[i][i] == T(0)) return T(0);
            }
            ans *= u[i][i];
            T t = T(1) / u[i][i];
            for (int j = i; j < n; ++j) u[i][j] *= t;
            for (int k = i + 1; k < n; ++k) {
                if (u[k][i] == T(0)) continue;
                ans *= u[k][i];
                t = T(1) / u[k][i];
                for (int j = i; j < n; ++j) u[k][j] = u[k][j] * t - u[i][j];
            }
        }
        return ans;
    }

    Matrix pow(std::int64_t k) const {
        assert(this->v.size() == this->v[0].size());
        int n = this->v.size();
        Matrix res(n, n), mul(this->v);
        res.unit_matrix();
        for (; k > 0; k >>= 1) {
            if (k & 1) res *= mul;
            mul *= mul;
        }
        return res;
    }

    void unit_matrix() {
        assert(this->v.size() == this->v[0].size());
        int n = this->v.size();
        for (int i = 0; i < n; ++i) {
            this->v[i].assign(n, T(0));
            this->v[i][i] = T(1);
        }
    }

    Matrix transposed() const {
        int x = this->v[0].size(), y = this->v.size();
        std::vector<std::vector<T>> res(x, std::vector<T>(y));
        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < y; ++j) {
                res[i][j] = this->v[j][i];
            }
        }
        return Matrix(res);
    }

    void print_debug() const {
        for (auto u : this->v) {
            cerr << "[";
            for (auto x : u) cerr << x << ", ";
            cerr << "]" << endl;
        }
    }

  private:
    std::vector<std::vector<T>> v;
};
#line 3 "/home/kuhaku/home/github/algo/lib/template/macro.hpp"
#define FOR(i, m, n) for (int i = (m); i < int(n); ++i)
#define FORR(i, m, n) for (int i = (m)-1; i >= int(n); --i)
#define FORL(i, m, n) for (int64_t i = (m); i < int64_t(n); ++i)
#define rep(i, n) FOR (i, 0, n)
#define repn(i, n) FOR (i, 1, n + 1)
#define repr(i, n) FORR (i, n, 0)
#define repnr(i, n) FORR (i, n + 1, 1)
#define all(s) (s).begin(), (s).end()
#line 3 "/home/kuhaku/home/github/algo/lib/template/sonic.hpp"
struct Sonic {
    Sonic() {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
    }

    constexpr void operator()() const {}
} sonic;
#line 5 "/home/kuhaku/home/github/algo/lib/template/atcoder.hpp"
using ll = int64_t;
using ld = long double;
template <class T, class U>
std::istream &operator>>(std::istream &is, std::pair<T, U> &p) {
    return is >> p.first >> p.second;
}
template <class T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) {
    for (T &i : v) is >> i;
    return is;
}
template <class T, class U>
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &p) {
    return os << '(' << p.first << ',' << p.second << ')';
}
template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    for (auto it = v.begin(); it != v.end(); ++it) {
        os << (it == v.begin() ? "" : " ") << *it;
    }
    return os;
}
template <class Head, class... Tail>
void co(Head &&head, Tail &&...tail) {
    if constexpr (sizeof...(tail) == 0) std::cout << head << '\n';
    else std::cout << head << ' ', co(std::forward<Tail>(tail)...);
}
template <class Head, class... Tail>
void ce(Head &&head, Tail &&...tail) {
    if constexpr (sizeof...(tail) == 0) std::cerr << head << '\n';
    else std::cerr << head << ' ', ce(std::forward<Tail>(tail)...);
}
template <typename T, typename... Args>
auto make_vector(T x, int arg, Args... args) {
    if constexpr (sizeof...(args) == 0) return std::vector<T>(arg, x);
    else return std::vector(arg, make_vector<T>(x, args...));
}
void setp(int n) {
    std::cout << std::fixed << std::setprecision(n);
}
void Yes(bool is_correct = true) {
    std::cout << (is_correct ? "Yes" : "No") << '\n';
}
void No(bool is_not_correct = true) {
    Yes(!is_not_correct);
}
void YES(bool is_correct = true) {
    std::cout << (is_correct ? "YES" : "NO") << '\n';
}
void NO(bool is_not_correct = true) {
    YES(!is_not_correct);
}
void Takahashi(bool is_correct = true) {
    std::cout << (is_correct ? "Takahashi" : "Aoki") << '\n';
}
void Aoki(bool is_not_correct = true) {
    Takahashi(!is_not_correct);
}
#line 5 "a.cpp"

using Mint = ModInt<>;

int main(void) {
    ll n;
    cin >> n;
    Mint x, y;
    cin >> x >> y;
    string s;
    cin >> s;
    x /= 100, y /= 100;

    Mint p = 1;
    for (auto c : s) {
        if (c == 'T')
            p *= Mint(1) - x;
        else
            p *= Mint(1) - y;
    }
    p = Mint(1) / (Mint(1) - p);
    vector<vector<Mint>> v(24, vector<Mint>(24));
    rep (i, 24) {
        Mint q = 1;
        repn (j, 24) {
            if (s[(i + j) % 24] == 'T') {
                v[(i + j) % 24][i] = q * x * p;
                q *= Mint(1) - x;
            } else {
                v[(i + j) % 24][i] = q * y * p;
                q *= Mint(1) - y;
            }
        }
    }

    Matrix<Mint> mat(v);

    vector<Mint> f(24);
    f[23] = 1;
    auto g = mat.pow(n) * f;
    Mint ans = 0;
    rep (i, 24) {
        if (s[i] == 'A')
            ans += g[i];
    }
    co(ans);

    return 0;
}
