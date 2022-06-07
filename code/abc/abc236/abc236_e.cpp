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
#line 3 "a.cpp"

double solve1(int n, const vector<int> &a) {
    double l = 0, r = *max_element(all(a));
    while (r - l > 1e-5) {
        double m = (l + r) / 2;
        vector<double> dp(n);
        rep(i, n) {
            if (i == 0)
                dp[i] = a[i] - m;
            else if (i == 1)
                dp[i] = max(0.0, dp[i - 1]) + a[i] - m;
            else
                dp[i] = max(dp[i - 2], dp[i - 1]) + a[i] - m;
        }

        if (dp[n - 2] >= 0 || dp[n - 1] >= 0)
            l = m;
        else
            r = m;
    }
    return l;
}

int solve2(int n, const vector<int> &a) {
    vector<int> b = a;
    sort(all(b));
    int l = 0, r = n;
    while (r - l > 1) {
        int m = (l + r) / 2;
        int x = b[m];
        vector<int> dp(n);
        rep(i, n) {
            int y = (a[i] >= x ? 1 : -1);
            if (i == 0)
                dp[i] = y;
            else if (i == 1)
                dp[i] = max(0, dp[i - 1]) + y;
            else
                dp[i] = max(dp[i - 2], dp[i - 1]) + y;
        }

        if (dp[n - 2] >= 1 || dp[n - 1] >= 1)
            l = m;
        else
            r = m;
    }
    return b[l];
}

int main(void) {
    sonic();
    setp(10);
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    co(solve1(n, a));
    co(solve2(n, a));

    return 0;
}
