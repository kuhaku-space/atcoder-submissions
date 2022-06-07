#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/template/template.hpp"
#include <bits/stdc++.h>
using namespace std;
template <class T, class U>
bool chmax(T &a, const U &b) {
    return a < b ? a = b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U &b) {
    return b < a ? a = b, true : false;
}
constexpr int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
const double PI = acos(-1.0);
#line 3 "/home/kuhaku/atcoder/github/atcoder-lib/lib/graph/matrix_graph.hpp"

template <class T>
struct matrix_graph {
    int V;
    vector<vector<T>> m;

    matrix_graph(int v, T _e = T()) : V(v) {
        m = vector<vector<T>>(V, vector<T>(V, _e));
    }

    const auto &operator[](int i) const { return m[i]; }
    auto &operator[](int i) { return m[i]; }
    const auto begin() const { return m.begin(); }
    auto begin() { return m.begin(); }
    const auto end() const { return m.end(); }
    auto end() { return m.end(); }

    int size() const { return V; }

    void add_edge(int a, int b, T d = T(1)) { m[a][b] = d; }
    void add_edges(int a, int b, T d = T(1)) {
        m[a][b] = d;
        m[b][a] = d;
    }

    void complement() {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) m[i][j] = !m[i][j];
        }
    }
};
#line 4 "/home/kuhaku/atcoder/github/atcoder-lib/lib/graph/warshall_floyd.hpp"

template <class T>
void warshall_floyd(matrix_graph<T> &g) {
    int n = g.size();
    for (int i = 0; i < n; ++i) g[i][i] = 0;
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                chmin(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }
}
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/template/atcoder.hpp"
#pragma GCC target("avx")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#line 6 "/home/kuhaku/atcoder/github/atcoder-lib/lib/template/atcoder.hpp"
using ll = int64_t;
using ld = long double;
#define FOR(i, m, n) for(int i = (m); i < int(n); ++i)
#define FORR(i, m, n) for(int i = (m)-1; i >= int(n); --i)
#define FORL(i, m, n) for(int64_t i = (m); i < int64_t(n); ++i)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FOR(i, 1, n+1)
#define repr(i, n) FORR(i, n, 0)
#define repnr(i, n) FORR(i, n+1, 1)
#define all(s) (s).begin(), (s).end()
template<class T, class U>
std::istream &operator>>(std::istream &is, std::pair<T, U> &p) { is >> p.first >> p.second; return is; }
template <class T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) { for (T &i : v) is>>i; return is; }
template <class T, class U>
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &p) {
    return os<<'('<<p.first<< ','<<p.second<<')';
}
template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    for (auto it=v.begin(); it!=v.end(); ++it) { os<<(it==v.begin()?"":" ")<<*it; } return os;
}
template <class Head, class... Tail>
void co(Head&& head, Tail&&... tail) {
    if constexpr(sizeof...(tail)==0) std::cout<<head<<'\n'; else std::cout<<head<<' ',co(forward<Tail>(tail)...);
}
template <class Head, class... Tail>
void ce(Head&& head, Tail&&... tail) {
    if constexpr(sizeof...(tail)==0) std::cerr<<head<<'\n'; else std::cerr<<head<<' ',ce(forward<Tail>(tail)...);
}
template<typename T, typename... Args>
auto make_vector(T x, int arg, Args ...args) {
    if constexpr(sizeof...(args)==0) return std::vector<T>(arg,x); else return std::vector(arg,make_vector<T>(x,args...));
}
void sonic() { std::ios::sync_with_stdio(false); std::cin.tie(nullptr); }
void setp(const int n) { std::cout<<std::fixed<<std::setprecision(n); }
void Yes(bool is_correct) { std::cout<<(is_correct?"Yes":"No")<<std::endl; }
void YES(bool is_correct) { std::cout<<(is_correct?"YES":"NO")<<std::endl; }
#line 4 "a.cpp"

int main(void) {
    sonic();
    int n, m;
    cin >> n >> m;
    matrix_graph<ll> g(n, INF);
    vector<int> a, b, c;
    rep(i, m) {
        int s, t, u;
        cin >> s >> t >> u;
        --s, --t;
        a.emplace_back(s);
        b.emplace_back(t);
        c.emplace_back(u);
        g.add_edges(s, t, u);
    }

    warshall_floyd(g);

    int ans = 0;
    rep(i, m) {
        bool flag = false;
        rep(j, n) {
            flag |= a[i] != j && b[i] != j && (g[a[i]][j] + g[j][b[i]] <= c[i]);
        }
        ans += flag;
    }
    co(ans);

    return 0;
}
