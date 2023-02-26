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

class CentroidDecomposition {
  private:
    int V;
    vector<vector<int>> G;
    vector<bool> used;
    // sz:重心分解後の最大部分木に含まれる頂点の数(自分を含める)
    // par:重心分解後の親の頂点
    vector<int> sz, par;
    // 部分木のサイズを計算
    void calcSize(int u, int p) {
        sz[u] = 1;
        for (int v : G[u]) {
            if (!used[v] && v != p) {
                calcSize(v, u);
                sz[u] += sz[v];
            }
        }
    }
    void cdBuild(int u, int p) {
        calcSize(u, -1);
        int tot = sz[u];
        bool ok = false;
        int pp = -1;
        // いま見ている部分木での重心を見つける
        while (!ok) {
            ok = true;
            for (int v : G[u]) {
                if (!used[v] && v != pp && 2 * sz[v] > tot) {
                    pp = u, u = v, ok = false;
                    break;
                }
            }
        }
        par[u] = p;
        // 何らかの操作
        used[u] = true;
        // 深さ優先でたどる
        for (int v : G[u]) {
            if (!used[v]) {
                cdBuild(v, u);
            }
        }
    }

  public:
    CentroidDecomposition(int node_size)
        : V(node_size), G(V), used(V, false), sz(V, 0), par(V, -1) {}
    void add_edge(int u, int v) {
        G[u].push_back(v), G[v].push_back(u);
    }
    void build() {
        cdBuild(0, -1);
    }

    auto get_parent() {
        return this->par;
    }
};

int main(void) {
    int n;
    cin >> n;
    CentroidDecomposition g(n);
    rep (i, n - 1) {
        int u, v;
        cin >> u >> v;
        g.add_edge(u - 1, v - 1);
    }

    g.build();
    auto ans = g.get_parent();
    for_each(all(ans), [](auto &x) {
        if (x != -1)
            ++x;
    });
    co(ans);

    return 0;
}
