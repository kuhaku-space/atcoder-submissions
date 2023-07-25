#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/home/github/algo/lib/template/template.hpp"
#pragma GCC target("sse4.2,avx2,bmi2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
template <class T, class U>
bool chmax(T &a, const U &b) {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U &b) {
    return (T)b < a ? a = (T)b, true : false;
}
constexpr std::int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
constexpr double PI = M_PI;
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
using namespace std;
using ll = std::int64_t;
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

struct S {
    unsigned int x;

    S operator+=(const S &rhs) {
        x ^= rhs.x;
        return *this;
    }
    S operator*=(const S &rhs) {
        x &= rhs.x;
        return *this;
    }

    S operator+(const S &rhs) const {
        return S(*this) += rhs;
    }
    S operator*(const S &rhs) const {
        return S(*this) *= rhs;
    }

    friend std::istream &operator>>(std::istream &is, S &rhs) {
        return is >> rhs.x;
    }
    friend std::ostream &operator<<(std::ostream &os, const S &rhs) {
        return os << rhs.x;
    }
};

template <class T>
T kitamasa(std::vector<T> a, std::vector<T> d, std::int64_t n) {
    assert(a.size() == d.size());
    const int k = d.size();
    if (n < k)
        return a[n];
    std::vector<int> fs;
    while (n > k * 2) {
        fs.emplace_back(n & 1);
        n >>= 1;
    }
    vector<T> x = d, y(k);
    for (int i = k; i < n; ++i) {
        std::swap(x, y);
        for (int i = 0; i < k; ++i) x[i] = d[i] * y[k - 1];
        for (int i = 0; i + 1 < k; ++i) x[i + 1] += y[i];
    }
    std::reverse(std::begin(fs), std::end(fs));
    vector<vector<T>> v(k, vector<T>(k));
    for (auto &&f : fs) {
        v[0] = x;
        for (int i = 0; i + 1 < k; ++i) {
            for (int j = 0; j < k; ++j) v[i + 1][j] = d[j] * v[i][k - 1];
            for (int j = 0; j + 1 < k; ++j) v[i + 1][j + 1] += v[i][j];
        }
        std::fill(std::begin(x), std::end(x), T());
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < k; ++j) x[j] += v[0][i] * v[i][j];
        }
        if (f) {
            std::swap(x, y);
            for (int i = 0; i < k; ++i) x[i] = d[i] * y[k - 1];
            for (int i = 0; i + 1 < k; ++i) x[i + 1] += y[i];
        }
    }
    T res{};
    for (int i = 0; i < k; ++i) res += x[i] * a[i];
    return res;
}

int main(void) {
    int k, n;
    cin >> k >> n;
    vector<S> a(k), c(k);
    cin >> a >> c;
    reverse(all(c));

    co(kitamasa(a, c, n - 1));

    return 0;
}
