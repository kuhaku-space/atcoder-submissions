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
int to_int(const string &s, const vector<ll> &p) {
    int n = s.size();
    int res = 0;
    rep (i, n) {
        if (s[i] == 'B')
            res += p[i];
        else if (s[i] == 'W')
            res += p[i] * 2;
    }
    return res;
}
int main(void) {
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    s += "..";
    t += "..";
    int len = 1;
    rep (i, n + 2) len *= 3;
    vector<ll> dp(len, INF);
    vector<ll> p(n + 2, 1);
    rep (i, n + 1) p[i + 1] = p[i] * 3;
    int x = to_int(s, p);
    queue<int> que;
    dp[x] = 0;
    que.emplace(x);
    while (!que.empty()) {
        int a = que.front();
        que.pop();
        string u(n + 2, '.');
        int b = a;
        rep (i, n + 2) {
            if (b % 3 == 1) {
                u[i] = 'B';
            } else if (b % 3 == 2) {
                u[i] = 'W';
            }
            b /= 3;
        }
        pair<int, int> q;
        rep (i, n + 2) {
            if (u[i] == '.') {
                q = {i, i + 1};
                break;
            }
        }
        rep (i, n + 1) {
            if (u[i] != '.' && u[i + 1] != '.') {
                swap(u[i], u[q.first]);
                swap(u[i + 1], u[q.second]);
                int y = to_int(u, p);
                if (chmin(dp[y], dp[a] + 1)) {
                    que.emplace(y);
                }
                swap(u[i], u[q.first]);
                swap(u[i + 1], u[q.second]);
            }
        }
    }
    if (dp[to_int(t, p)] == INF) {
        co(-1);
    } else {
        co(dp[to_int(t, p)]);
    }
    return 0;
}
