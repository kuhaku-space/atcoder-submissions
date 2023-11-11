#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/home/github/algo/lib/template/template.hpp"
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
        std::cout << std::fixed << std::setprecision(20);
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

bool next_permutation(std::vector<int> &v, int n) {
    assert((int)v.size() <= n);
    if ((int)v.size() == n) {
        return std::next_permutation(v.begin(), v.end());
    }
    std::vector<bool> used(n);
    for (auto e : v) used[e] = true;
    for (int i = v.back() + 1; i < n; ++i) {
        if (!used[i]) {
            v.back() = i;
            return true;
        }
    }
    used[v.back()] = false;
    for (int i = (int)v.size() - 2; i >= 0; --i) {
        used[v[i]] = false;
        if (v[i] > v[i + 1])
            continue;
        for (int j = v[i] + 1; j < n; ++j) {
            if (!used[j]) {
                v[i] = j;
                used[j] = true;
                break;
            }
        }
        ++i;
        for (int j = 0; i < (int)v.size(); ++j) {
            if (!used[j]) {
                v[i] = j;
                ++i;
            }
        }
        return true;
    }
    for (int i = 0; i < (int)v.size(); ++i) v[i] = i;
    return false;
}

bool is_ok(const std::vector<string> &s, string c) {
    int n = c.size();
    rep (j, n) {
        vector<int> v(3, -1);
        rep (i, n) {
            if (s[i][j] == '.')
                continue;
            v[s[i][j] - 'A'] = i;
        }
        if (*min_element(all(v)) != v[c[j] - 'A'] || v[c[j] - 'A'] == -1)
            return false;
    }
    return true;
}

int main(void) {
    int n;
    cin >> n;
    string r, c;
    cin >> r >> c;
    vector<string> s(n);
    vector<string> ans;
    auto dfs = [&](auto self, int x) {
        if (!ans.empty())
            return;
        if (x == n) {
            if (is_ok(s, c)) {
                ans = s;
            }
            return;
        }
        vector<int> ord(3);
        iota(all(ord), 0);
        do {
            if (min_element(all(ord)) - ord.begin() != (r[x] - 'A'))
                continue;
            string t(n, '.');
            rep (i, 3) t[ord[i]] = 'A' + i;
            s[x] = t;
            self(self, x + 1);
        } while (next_permutation(ord, n));
    };
    dfs(dfs, 0);
    if (ans.empty()) {
        No();
    } else {
        Yes();
        for (auto e : ans) co(e);
    }

    return 0;
}
