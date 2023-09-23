#line 1 "a.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"
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
#line 2 "/home/kuhaku/home/github/algo/lib/flow/hopcroft_karp.hpp"

struct hopcroft_karp {
    hopcroft_karp(int _n, int _m) : n(_n), m(_m), g(_n), match_left(_n, -1), match_right(_m, -1) {}

    void add_edge(int u, int v) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < m);
        g[u].emplace_back(v);
    }

    int bipartite_matching() {
        int flow = 0;
        std::vector<int> root(n), prev(n), qq(n);
        for (bool updated = true; updated;) {
            updated = false;
            int qi = 0, qj = 0;
            std::fill(root.begin(), root.end(), -1);
            std::fill(prev.begin(), prev.end(), -1);
            for (int i = 0; i < n; i++) {
                if (match_left[i] == -1) qq[qj++] = i, root[i] = i, prev[i] = i;
            }
            while (qi < qj) {
                int u = qq[qi++];
                if (match_left[root[u]] != -1) continue;
                for (int v : g[u]) {
                    if (match_right[v] == -1) {
                        while (v != -1)
                            match_right[v] = u, std::swap(match_left[u], v), u = prev[u];
                        updated = true, flow++;
                        break;
                    }

                    if (prev[match_right[v]] == -1)
                        v = match_right[v], prev[v] = u, root[v] = root[u], qq[qj++] = v;
                }
            }
        }
        return flow;
    }

    std::vector<std::pair<int, int>> get_pairs() const {
        std::vector<std::pair<int, int>> res;
        for (int i = 0; i < n; i++) {
            if (~match_left[i]) res.emplace_back(i, match_left[i]);
        }
        return res;
    }

  private:
    const int n, m;
    std::vector<std::vector<int>> g;
    std::vector<int> match_left, match_right;
};
#line 2 "/home/kuhaku/home/github/algo/lib/string/converter.hpp"

struct string_converter {
    char type(const char &c) const {
        return (std::islower(c) ? 'a' : std::isupper(c) ? 'A' : std::isdigit(c) ? '0' : 0);
    }
    int convert(const char &c) {
        if (!start) start = type(c);
        return c - start;
    }
    int convert(const char &c, const std::string &chars) { return chars.find(c); }
    template <typename T>
    auto convert(const T &v) {
        std::vector<decltype(convert(v[0]))> res;
        res.reserve(v.size());
        for (auto &&e : v) res.emplace_back(convert(e));
        return res;
    }
    template <typename T>
    auto convert(const T &v, const std::string &chars) {
        std::vector<decltype(convert(v[0], chars))> res;
        res.reserve(v.size());
        for (auto &&e : v) res.emplace_back(convert(e, chars));
        return res;
    }
    int operator()(const char &v, char s = 0) {
        start = s;
        return convert(v);
    }
    int operator()(const char &v, const std::string &chars) { return convert(v, chars); }
    template <typename T>
    auto operator()(const T &v, char s = 0) {
        start = s;
        return convert(v);
    }
    template <typename T>
    auto operator()(const T &v, const std::string &chars) {
        return convert(v, chars);
    }

  private:
    char start = 0;
} to_int;
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
#line 5 "a.cpp"

int main(void) {
    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    cin >> s;
    auto t = to_int(s, '0');

    auto valid = [&](int d) {
        rep (i, n) {
            bool flag = false;
            rep (j, m) {
                flag |= t[i][j] == d;
            }
            if (!flag)
                return false;
        }
        return true;
    };

    int ans = Inf;
    vector<int> ord(10);
    iota(all(ord), 0);
    shuffle(all(ord), mt19937());
    for (int d : ord) {
        if (!valid(d))
            continue;

        vector v(n, vector<int>());
        rep (i, n) {
            rep (j, m) {
                if (t[i][j] == d)
                    v[i].emplace_back(j);
            }
            int idx = 0;
            while ((int)v[i].size() < n) v[i].emplace_back(v[i][idx++] + m);
        }
        vector<int> u;
        rep (i, n) u.insert(u.end(), all(v[i]));
        sort(all(u));
        u.erase(unique(all(u)), u.end());
        vector w(n, vector<int>());
        rep (i, n) {
            int idx = 0;
            for (auto x : v[i]) {
                while (u[idx] != x) ++idx;
                w[i].emplace_back(idx);
            }
        }

        auto check = [&](int mid) {
            int s = upper_bound(all(u), mid) - u.begin();
            hopcroft_karp hk(n, s);
            rep (i, n) {
                for (auto idx : w[i]) {
                    if (u[idx] > mid)
                        break;
                    hk.add_edge(i, idx);
                }
            }
            return (hk.bipartite_matching() >= n);
        };

        if (ans != Inf && !check(ans))
            continue;
        int l = -1, r = ans;
        while (r - l > 1) {
            int mid = (l + r) / 2;
            (check(mid) ? r : l) = mid;
        }
        chmin(ans, r);
    }
    if (ans == Inf)
        ans = -1;
    co(ans);

    return 0;
}
