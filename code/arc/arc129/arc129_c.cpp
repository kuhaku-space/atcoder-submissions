#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/template/atcoder.hpp"
#pragma GCC target("avx")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#line 2 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/template/template.hpp"
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
#line 6 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/template/atcoder.hpp"
using ll = int64_t;
using ld = long double;
#define FOR(i, m, n) for(int i = (m); i < (n); ++i)
#define FORR(i, m, n) for(int i = (m)-1; i >= (n); --i)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FOR(i, 1, n+1)
#define repr(i, n) FORR(i, n, 0)
#define repnr(i, n) FORR(i, n+1, 1)
#define all(s) (s).begin(), (s).end()
template <class T>
istream &operator>>(istream &is, vector<T> &v) { for (T &i : v) is>>i; return is; }
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    for (auto it=v.begin(); it!=v.end(); ++it) { os<<(it==v.begin()?"":" ")<<*it; } return os;
}
template <class Head, class... Tail>
void co(Head&& head, Tail&&... tail) {
    if constexpr(sizeof...(tail)==0) cout<<head<<'\n'; else cout<<head<<' ',co(forward<Tail>(tail)...);
}
template <class Head, class... Tail>
void ce(Head&& head, Tail&&... tail) {
    if constexpr(sizeof...(tail)==0) cerr<<head<<'\n'; else cerr<<head<<' ',ce(forward<Tail>(tail)...);
}
template<typename T, typename... Args>
auto make_vector(T x, int arg, Args ...args) {
    if constexpr(sizeof...(args)==0) return vector<T>(arg, x); else return vector(arg,make_vector<T>(x, args...));
}
void sonic() { ios::sync_with_stdio(false); cin.tie(nullptr); }
void setp(const int n) { cout << fixed << setprecision(n); }
#line 3 "a.cpp"

int triangular_number(int x) {
    return x * (x + 1) / 2;
}

int main(void) {
    sonic();
    int n;
    cin >> n;
    rep(i, n + 1) {
        if (triangular_number(i) > n)
            break;
        FOR(j, i, n + 1) {
            if (triangular_number(j) > n)
                break;
            FOR(k, j, n + 1) {
                if (triangular_number(k) > n)
                    break;
                if (triangular_number(i) + triangular_number(j) + triangular_number(k) == n) {
                    string ans;
                    vector<int> dp(7);
                    rep(_, 3) {
                        rep(x, i) {
                            ans += '7';
                            dp[0]++;
                            auto tmp = dp;
                            rep(y, 7) dp[(y * 10) % 7] = tmp[y];
                        }
                        repn(x, 6) {
                            if (dp[7 - x] == 0) {
                                ans += char('0' + x);
                                dp[0]++;
                                auto tmp = dp;
                                rep(y, 7) dp[y + x] = tmp[y];
                                tmp = dp;
                                rep(y, 7) dp[(y * 10) % 7] = tmp[y];
                                break;
                            }
                        }
                        swap(i, j);
                        swap(j, k);
                    }
                    co(ans);
                    return 0;
                }
            }
        }
    }

    return 0;
}
