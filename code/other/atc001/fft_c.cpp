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
#line 2 "/home/kuhaku/home/github/algo/lib/fft/fft.hpp"

// i * j = g^(x + y) としてFFTに帰着
// verify : https://atcoder.jp/contests/agc047/tasks/agc047_c 21/02/24

namespace FFT {

void _fft(std::vector<std::complex<double>> &a, bool inv) {
    int N = a.size();
    static bool is_first = true;
    static std::array<std::complex<double>, 30> vbw, vibw;
    if (is_first) {
        is_first = false;
        for (int i = 0; i < 30; ++i) {
            vbw[i] = std::polar(1.0, 2.0 * PI / (1 << (i + 1)));
            vibw[i] = std::polar(1.0, -2.0 * PI / (1 << (i + 1)));
        }
    }
    for (int i = 0, j = 1; j < N - 1; ++j) {
        for (int k = N >> 1; k > (i ^= k); k >>= 1)
            ;
        if (i > j) swap(a[i], a[j]);
    }
    for (int k = 0, t = 1; t < N; ++k, t <<= 1) {
        std::complex<double> bw = vbw[k];
        if (inv) bw = vibw[k];
        for (int i = 0; i < N; i += t * 2) {
            std::complex<double> w(1.0);
            for (int j = 0; j < t; ++j) {
                int l = i + j, r = i + j + t;
                std::complex<double> c = a[l], d = a[r] * w;
                a[l] = c + d, a[r] = c - d;
                w *= bw;
            }
        }
    }
    if (inv) {
        for (int i = 0; i < N; ++i) a[i] /= N;
    }
}

template <class T>
void convolution_self(std::vector<T> &a, const std::vector<T> &b) {
    int n = a.size() + b.size() - 1;
    int N = 1;
    while (N < n) N <<= 1;

    std::vector<std::complex<double>> va(N), vb(N);
    for (int i = 0; i < (int)a.size(); ++i) va[i] = std::complex<double>(a[i]);
    for (int i = 0; i < (int)b.size(); ++i) vb[i] = std::complex<double>(b[i]);
    _fft(va, false), _fft(vb, false);
    for (int i = 0; i < N; ++i) va[i] *= vb[i];
    _fft(va, true);

    a.resize(n);
    if constexpr (std::numeric_limits<T>::is_integer)
        for (int i = 0; i < n; ++i) a[i] = T(va[i].real() + 0.5);
    else
        for (int i = 0; i < n; ++i) a[i] = va[i].real();
}

template <class T>
std::vector<T> convolution(const std::vector<T> &a, const std::vector<T> &b) {
    std::vector<T> res = a;
    convolution_self(res, b);
    return res;
}

}  // namespace FFT
#line 3 "/home/kuhaku/home/github/algo/lib/template/atcoder.hpp"
using ll = int64_t;
using ld = long double;
#define FOR(i, m, n) for (int i = (m); i < int(n); ++i)
#define FORR(i, m, n) for (int i = (m)-1; i >= int(n); --i)
#define FORL(i, m, n) for (int64_t i = (m); i < int64_t(n); ++i)
#define rep(i, n) FOR (i, 0, n)
#define repn(i, n) FOR (i, 1, n + 1)
#define repr(i, n) FORR (i, n, 0)
#define repnr(i, n) FORR (i, n + 1, 1)
#define all(s) (s).begin(), (s).end()
template <class T, class U>
std::istream &operator>>(std::istream &is, std::pair<T, U> &p) {
    is >> p.first >> p.second;
    return is;
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
    else std::cout << head << ' ', co(forward<Tail>(tail)...);
}
template <class Head, class... Tail>
void ce(Head &&head, Tail &&...tail) {
    if constexpr (sizeof...(tail) == 0) std::cerr << head << '\n';
    else std::cerr << head << ' ', ce(forward<Tail>(tail)...);
}
template <typename T, typename... Args>
auto make_vector(T x, int arg, Args... args) {
    if constexpr (sizeof...(args) == 0) return std::vector<T>(arg, x);
    else return std::vector(arg, make_vector<T>(x, args...));
}
void sonic() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}
void setp(const int n) {
    std::cout << std::fixed << std::setprecision(n);
}
void Yes(bool is_correct = true) {
    std::cout << (is_correct ? "Yes" : "No") << std::endl;
}
void No(bool is_not_correct = true) {
    Yes(!is_not_correct);
}
void YES(bool is_correct = true) {
    std::cout << (is_correct ? "YES" : "NO") << std::endl;
}
void NO(bool is_not_correct = true) {
    YES(!is_not_correct);
}
void Takahashi(bool is_correct = true) {
    std::cout << (is_correct ? "Takahashi" : "Aoki") << std::endl;
}
void Aoki(bool is_not_correct = true) {
    Takahashi(!is_not_correct);
}
#line 4 "a.cpp"

int main(void) {
    sonic();

    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    repn(i, n) cin >> a[i] >> b[i];

    FFT::convolution_self(a, b);

    repn(i, 2 * n) co(a[i]);

    return 0;
}
