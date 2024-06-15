#define PROBLEM ""
#pragma GCC target("sse4.2,avx2,bmi2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
template <class T, class U>
constexpr bool chmax(T &a, const U &b) {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
constexpr bool chmin(T &a, const U &b) {
    return (T)b < a ? a = (T)b, true : false;
}
constexpr std::int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr double EPS = 1e-7;
constexpr double PI = 3.14159265358979323846;
#define FOR(i, m, n) for (int i = (m); i < int(n); ++i)
#define FORR(i, m, n) for (int i = (m)-1; i >= int(n); --i)
#define FORL(i, m, n) for (int64_t i = (m); i < int64_t(n); ++i)
#define rep(i, n) FOR (i, 0, n)
#define repn(i, n) FOR (i, 1, n + 1)
#define repr(i, n) FORR (i, n, 0)
#define repnr(i, n) FORR (i, n + 1, 1)
#define all(s) (s).begin(), (s).end()
struct Sonic {
    Sonic() {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
        std::cout << std::fixed << std::setprecision(20);
    }
    constexpr void operator()() const {}
} sonic;
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
int main(void) {
    int h, w, k;
    cin >> h >> w >> k;
    vector xs(h, vector(w + 1, false)), ys(h + 1, vector(w, false));
    rep (i, h) {
        xs[i][0] = true;
        xs[i][w] = true;
    }
    rep (j, w) {
        ys[0][j] = true;
        ys[h][j] = true;
    }
    rep (i, h) xs[i][w - 1] = true;
    int x = h;
    rep (i, h / 2) {
        if (k <= x)
            break;
        repr (j, w - 1) {
            if (k <= x)
                break;
            xs[i * 2][j + 1] = false;
            xs[i * 2 + 1][j + 1] = false;
            xs[i * 2][j] = true;
            xs[i * 2 + 1][j] = true;
            ys[i * 2 + 1][j + 1] = true;
            ys[i * 2 + 2][j] = true;
            x += 2;
        }
    }
    if (h & 1) {
        rep (j, (w - 1) / 2) {
            if (k <= x)
                break;
            xs[h - 2][j * 2 + 1] = true;
            xs[h - 1][j * 2 + 2] = true;
            ys[h - 1][j * 2] = false;
            ys[h - 1][j * 2 + 1] = false;
            x += 2;
        }
    }
    if (x != k) {
        No();
        return 0;
    }
    Yes();
    string s;
    rep (j, 2 * w - 1) {
        s += '+';
    }
    s += 'S';
    s += '+';
    co(s);
    rep (i, h) {
        s = "";
        rep (j, w) {
            if (j == 0)
                s += '+';
            else if (xs[i][j])
                s += '|';
            else
                s += '.';
            s += 'o';
        }
        s += '+';
        co(s);
        if (i == h - 1)
            break;
        s = "";
        rep (j, w) {
            s += '+';
            if (ys[i + 1][j])
                s += '-';
            else
                s += '.';
        }
        s += '+';
        co(s);
    }
    s = "";
    rep (j, 2 * w - 1) {
        s += '+';
    }
    s += 'G';
    s += '+';
    co(s);
    return 0;
}
