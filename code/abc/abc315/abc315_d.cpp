#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/atcoder/github/algo/lib/template/template.hpp"
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
#line 3 "/home/kuhaku/atcoder/github/algo/lib/template/macro.hpp"
#define FOR(i, m, n) for (int i = (m); i < int(n); ++i)
#define FORR(i, m, n) for (int i = (m)-1; i >= int(n); --i)
#define FORL(i, m, n) for (int64_t i = (m); i < int64_t(n); ++i)
#define rep(i, n) FOR (i, 0, n)
#define repn(i, n) FOR (i, 1, n + 1)
#define repr(i, n) FORR (i, n, 0)
#define repnr(i, n) FORR (i, n + 1, 1)
#define all(s) (s).begin(), (s).end()
#line 3 "/home/kuhaku/atcoder/github/algo/lib/template/sonic.hpp"
struct Sonic {
    Sonic() {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
    }

    constexpr void operator()() const {}
} sonic;
#line 5 "/home/kuhaku/atcoder/github/algo/lib/template/atcoder.hpp"
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

int main(void) {
    int h, w;
    cin >> h >> w;
    vector<string> s(h);
    cin >> s;
    vector<unordered_map<char, int>> mx(h), my(w);
    rep (i, h) {
        rep (j, w) {
            mx[i][s[i][j]]++;
            my[j][s[i][j]]++;
        }
    }

    stack<tuple<int, int, char>> st;
    vector<bool> fx(h), fy(w);
    rep (i, h) {
        if (mx[i].size() == 1 && mx[i].begin()->second >= 2)
            st.emplace(0, i, mx[i].begin()->first);
    }
    rep (i, w) {
        if (my[i].size() == 1 && my[i].begin()->second >= 2)
            st.emplace(1, i, my[i].begin()->first);
    }

    while (!st.empty()) {
        while (!st.empty()) {
            auto [p, q, r] = st.top();
            st.pop();
            if (p == 0 && fx[q])
                continue;
            if (p == 1 && fy[q])
                continue;
            if (p == 0) {
                fx[q] = true;
                rep (i, w) {
                    if (my[i].count(r) && --my[i][r] == 0) {
                        my[i].erase(r);
                    }
                }
            }
            if (p == 1) {
                fy[q] = true;
                rep (i, h) {
                    if (mx[i].count(r) && --mx[i][r] == 0) {
                        mx[i].erase(r);
                    }
                }
            }
        }
        rep (i, h) {
            if (!fx[i] && mx[i].size() == 1 && mx[i].begin()->second >= 2)
                st.emplace(0, i, mx[i].begin()->first);
        }
        rep (i, w) {
            if (!fy[i] && my[i].size() == 1 && my[i].begin()->second >= 2)
                st.emplace(1, i, my[i].begin()->first);
        }
    }
    int cx = 0, cy = 0;
    rep (i, h) cx += !fx[i];
    rep (i, w) cy += !fy[i];
    co(cx * cy);

    return 0;
}
