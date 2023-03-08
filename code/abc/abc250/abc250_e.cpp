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
#line 3 "/home/kuhaku/home/github/algo/lib/math/hashint.hpp"

struct HashInt {
    static constexpr std::uint64_t get_mod() noexcept { return mod; }

    constexpr HashInt() noexcept : x(0) {}
    constexpr HashInt(int y) noexcept : x(y >= 0 ? y % mod : (mod - 1 - ~y % mod)) {}
    constexpr HashInt(unsigned int y) noexcept : x(y % mod) {}
    constexpr HashInt(long y) noexcept : x(y >= 0 ? y % mod : (mod - 1 - ~y % mod)) {}
    constexpr HashInt(unsigned long y) noexcept : x(y % mod) {}
    constexpr HashInt(long long y) noexcept : x(y >= 0 ? y % mod : (mod - 1 - ~y % mod)) {}
    constexpr HashInt(unsigned long long y) noexcept : x(y % mod) {}

    constexpr HashInt &operator+=(const HashInt &rhs) noexcept {
        if ((this->x += rhs.x) >= mod) this->x -= mod;
        return *this;
    }
    constexpr HashInt &operator-=(const HashInt &rhs) noexcept {
        if ((this->x += mod - rhs.x) >= mod) this->x -= mod;
        return *this;
    }
    constexpr HashInt &operator*=(const HashInt &rhs) noexcept {
        std::uint64_t au = this->x >> 31, ad = this->x & this->mask31;
        std::uint64_t bu = rhs.x >> 31, bd = rhs.x & this->mask31;
        std::uint64_t mid = ad * bu + au * bd;
        std::uint64_t midu = mid >> 30, midd = mid & this->mask30;
        this->x = this->_mod(au * bu * 2 + midu + (midd << 31) + ad * bd);
        return *this;
    }
    constexpr HashInt &operator/=(const HashInt &rhs) noexcept {
        *this *= rhs.inverse();
        return *this;
    }

    constexpr HashInt &operator++() noexcept {
        if ((++(this->x)) >= mod) this->x -= mod;
        return *this;
    }
    constexpr HashInt operator++(int) noexcept {
        HashInt tmp(*this);
        this->operator++();
        return tmp;
    }
    constexpr HashInt &operator--() noexcept {
        if ((this->x += mod - 1) >= mod) this->x -= mod;
        return *this;
    }
    constexpr HashInt operator--(int) noexcept {
        HashInt tmp(*this);
        this->operator--();
        return tmp;
    }

    constexpr HashInt operator-() const noexcept { return HashInt(-this->x); }
    constexpr HashInt operator+(const HashInt &rhs) const noexcept { return HashInt(*this) += rhs; }
    constexpr HashInt operator-(const HashInt &rhs) const noexcept { return HashInt(*this) -= rhs; }
    constexpr HashInt operator*(const HashInt &rhs) const noexcept { return HashInt(*this) *= rhs; }
    constexpr HashInt operator/(const HashInt &rhs) const noexcept { return HashInt(*this) /= rhs; }

    constexpr bool operator==(const HashInt &rhs) const noexcept { return this->x == rhs.x; }
    constexpr bool operator!=(const HashInt &rhs) const noexcept { return this->x != rhs.x; }

    constexpr explicit operator long() const noexcept { return x; }
    constexpr explicit operator unsigned long() const noexcept { return x; }
    constexpr explicit operator long long() const noexcept { return x; }
    constexpr explicit operator unsigned long long() const noexcept { return x; }

    constexpr HashInt inverse() const noexcept {
        std::int64_t a = x, b = mod, u = 1, v = 0, t = 0;
        while (b > 0) {
            t = a / b;
            swap(a -= t * b, b);
            swap(u -= t * v, v);
        }
        return HashInt(u);
    }

    constexpr HashInt pow(std::int64_t n) const noexcept { return HashInt(*this).pow_self(n); }
    constexpr HashInt &pow_self(std::int64_t n) noexcept {
        HashInt res(1);
        for (; n > 0; n >>= 1) {
            if (n & 1) res *= *this;
            *this *= *this;
        }
        *this = res;
        return *this;
    }

  private:
    std::uint64_t x;

    static constexpr std::uint64_t mod = (1ul << 61) - 1;
    static constexpr std::uint64_t mask30 = (1ul << 30) - 1;
    static constexpr std::uint64_t mask31 = (1ul << 31) - 1;

    constexpr std::uint64_t _mod(std::uint64_t x) const {
        std::uint64_t xu = x >> 61, xd = x & this->mod;
        std::uint64_t res = xu + xd;
        if (res >= this->mod) res -= this->mod;
        return res;
    }
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
#line 3 "a.cpp"

int main(void) {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    cin >> a >> b;

    vector<HashInt> v, u;
    rep (_, 2) {
        set<int> st;
        HashInt x = 0;
        rep (i, n) {
            if (!st.count(a[i])) {
                st.emplace(a[i]);
                x += HashInt(hash<string>()(to_string(a[i])));
            }
            v.emplace_back(x);
        }
        swap(a, b);
        swap(v, u);
    }

    int q;
    cin >> q;
    rep (i, q) {
        int x, y;
        cin >> x >> y;
        Yes(v[x - 1] == u[y - 1]);
    }

    return 0;
}
