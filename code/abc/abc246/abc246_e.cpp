#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/template/atcoder.hpp"
#pragma GCC target("avx")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
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
#line 3 "a.cpp"

int dx[4] = {1, 1, -1, -1};
int dy[4] = {1, -1, 1, -1};

int main(void) {
    sonic();
    int n;
    int sx, sy, tx, ty;
    cin >> n >> sx >> sy >> tx >> ty;
    --sx, --sy, --tx, --ty;
    vector<string> s(n);
    cin >> s;

    int dp[n][n][4];
    rep(i, n) {
        rep(j, n) {
            rep(k, 4) dp[i][j][k] = Inf;
        }
    }

    rep(i, 4) dp[sx][sy][i] = 1;

    auto in_board = [&](int x, int y) {
        return 0 <= x && x < n && 0 <= y && y < n && s[x][y] == '.';
    };

    queue<tuple<int, int, int>> que;
    rep(i, 4) que.emplace(sx, sy, i);
    while (!que.empty()) {
        auto [x, y, z] = que.front();
        que.pop();
        rep(k, 4) {
            if (k == z) {
                if (in_board(x + dx[k], y + dy[k]) &&
                    chmin(dp[x + dx[k]][y + dy[k]][k], dp[x][y][z]))
                    que.emplace(x + dx[k], y + dy[k], k);
            } else {
                if (in_board(x + dx[k], y + dy[k]) &&
                    chmin(dp[x + dx[k]][y + dy[k]][k], dp[x][y][z] + 1))
                    que.emplace(x + dx[k], y + dy[k], k);
            }
        }
    }

    int ans = Inf;
    rep(i, 4) chmin(ans, dp[tx][ty][i]);
    if (ans == Inf)
        ans = -1;
    co(ans);

    return 0;
}
