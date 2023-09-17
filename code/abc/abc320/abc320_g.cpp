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
#line 2 "/home/kuhaku/atcoder/github/algo/lib/flow/max_flow.hpp"

/**
 * @brief 最大流
 *
 * @tparam Cap
 */
template <class Cap>
struct mf_graph {
    mf_graph() : _n(0) {}
    explicit mf_graph(int n) : _n(n), g(n) {}

    int add_edge(int from, int to, Cap cap) {
        assert(0 <= from && from < _n);
        assert(0 <= to && to < _n);
        assert(0 <= cap);
        int m = int(pos.size());
        pos.emplace_back(from, int(g[from].size()));
        int from_id = int(g[from].size());
        int to_id = int(g[to].size());
        if (from == to) ++to_id;
        g[from].emplace_back(to, to_id, cap);
        g[to].emplace_back(from, from_id, 0);
        return m;
    }

    struct edge {
        int from, to;
        Cap cap, flow;
    };

    edge get_edge(int i) {
        int m = int(pos.size());
        assert(0 <= i && i < m);
        auto _e = g[pos[i].first][pos[i].second];
        auto _re = g[_e.to][_e.rev];
        return edge{pos[i].first, _e.to, _e.cap + _re.cap, _re.cap};
    }
    std::vector<edge> edges() {
        int m = int(pos.size());
        std::vector<edge> result;
        for (int i = 0; i < m; ++i) {
            result.emplace_back(get_edge(i));
        }
        return result;
    }
    void change_edge(int i, Cap new_cap, Cap new_flow) {
        int m = int(pos.size());
        assert(0 <= i && i < m);
        assert(0 <= new_flow && new_flow <= new_cap);
        auto &_e = g[pos[i].first][pos[i].second];
        auto &_re = g[_e.to][_e.rev];
        _e.cap = new_cap - new_flow;
        _re.cap = new_flow;
    }

    Cap flow(int s, int t) { return flow(s, t, std::numeric_limits<Cap>::max()); }
    Cap flow(int s, int t, Cap flow_limit) {
        assert(0 <= s && s < _n);
        assert(0 <= t && t < _n);
        assert(s != t);

        std::vector<int> level(_n), iter(_n);
        auto bfs = [&]() {
            std::fill(level.begin(), level.end(), -1);
            level[s] = 0;
            std::queue<int> que;
            que.emplace(s);
            while (!que.empty()) {
                int v = que.front();
                que.pop();
                for (auto e : g[v]) {
                    if (e.cap == 0 || level[e.to] >= 0) continue;
                    level[e.to] = level[v] + 1;
                    if (e.to == t) return;
                    que.emplace(e.to);
                }
            }
        };
        auto dfs = [&](auto self, int v, Cap up) {
            if (v == s) return up;
            Cap res = 0;
            int level_v = level[v];
            for (int &i = iter[v]; i < int(g[v].size()); ++i) {
                _edge &e = g[v][i];
                if (level_v <= level[e.to] || g[e.to][e.rev].cap == 0) continue;
                Cap d = self(self, e.to, std::min(up - res, g[e.to][e.rev].cap));
                if (d <= 0) continue;
                g[v][i].cap += d;
                g[e.to][e.rev].cap -= d;
                res += d;
                if (res == up) return res;
            }
            level[v] = _n;
            return res;
        };

        Cap flow = 0;
        while (flow < flow_limit) {
            bfs();
            if (level[t] == -1) break;
            std::fill(iter.begin(), iter.end(), 0);
            Cap f = dfs(dfs, t, flow_limit - flow);
            if (!f) break;
            flow += f;
        }
        return flow;
    }

    std::vector<bool> min_cut(int s) {
        std::vector<bool> visited(_n);
        std::queue<int> que;
        que.emplace(s);
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            visited[p] = true;
            for (auto e : g[p]) {
                if (e.cap && !visited[e.to]) {
                    visited[e.to] = true;
                    que.emplace(e.to);
                }
            }
        }
        return visited;
    }

  private:
    int _n;
    struct _edge {
        int to, rev;
        Cap cap;

        constexpr _edge(int _to, int _rev, Cap _cap) : to(_to), rev(_rev), cap(_cap) {}
    };
    std::vector<std::pair<int, int>> pos;
    std::vector<std::vector<_edge>> g;
};
#line 2 "/home/kuhaku/atcoder/github/algo/lib/string/converter.hpp"

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
#line 5 "a.cpp"

int main(void) {
    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    cin >> s;
    auto t = to_int(s, '0');

    vector pos(10, vector(n, vector<int>()));
    rep (i, n) {
        rep (j, m) {
            if ((int)pos[t[i][j]][i].size() < n)
                pos[t[i][j]][i].emplace_back(j);
        }
    }

    rep (i, 10) {
        rep (j, n) {
            if (pos[i][j].empty())
                continue;
            if ((int)pos[i][j].size() < n) {
                int idx = 0;
                while (pos[i][j].size() < n) pos[i][j].emplace_back(pos[i][j][idx++] + m);
            }
        }
    }
    auto valid = [&](int d) {
        rep (i, n) {
            if (pos[d][i].empty())
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

        vector v = pos[d];
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
            mf_graph<int> mf(n + s + 2);
            int st = n + s, gl = st + 1;
            rep (i, n) mf.add_edge(st, i, 1);
            rep (i, s) mf.add_edge(n + i, gl, 1);
            rep (i, n) {
                for (auto idx : w[i]) {
                    if (u[idx] > mid)
                        break;
                    mf.add_edge(i, n + idx, 1);
                }
            }
            return (mf.flow(st, gl) >= n);
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
