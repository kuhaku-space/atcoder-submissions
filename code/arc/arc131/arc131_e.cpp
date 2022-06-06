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
#line 3 "/home/kuhaku/atcoder/github/atcoder-lib/lib/algorithm/xorshift.hpp"

struct Xorshift {
    unsigned int x, y, z, w;

    Xorshift() { x = 123456789, y = 362436069, z = 521288629, w = 88675123; }

    using result_type = unsigned int;
    constexpr unsigned int min() { return 0; }
    constexpr unsigned int max() { return UINT32_MAX; }
    unsigned int operator()() {
        unsigned int t = (x ^ (x << 11));
        x = y, y = z, z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }

    double rand_d() { return (double)(*this)() / (1LL << 32); }
};
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/template/atcoder.hpp"
#pragma GCC target("avx")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#line 6 "/home/kuhaku/atcoder/github/atcoder-lib/lib/template/atcoder.hpp"
using ll = int64_t;
using ld = long double;
#define FOR(i, m, n) for(int i = (m); i < (n); ++i)
#define FORR(i, m, n) for(int i = (m)-1; i >= (n); --i)
#define FORL(i, m, n) for(ll i = (m); i < (n); ++i)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FOR(i, 1, n+1)
#define repr(i, n) FORR(i, n, 0)
#define repnr(i, n) FORR(i, n+1, 1)
#define all(s) (s).begin(), (s).end()
template<class T, class U>
istream &operator>>(istream &is, pair<T, U> &p) { is >> p.first >> p.second; return is; }
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
#line 4 "a.cpp"

Xorshift xor128;

int main(void) {
    sonic();
    int n;
    cin >> n;

    if (n == 3 || n == 4 || n * (n - 1) / 2 % 3) {
        co("No");
        return 0;
    }

    auto st = clock();
    while (clock() - st < 1.9 * CLOCKS_PER_SEC) {
        vector<int> sum(3);
        vector<vector<int>> v(3);
        rep(i, n - 1) {
            int x = xor128() % 3;
            v[x].emplace_back(i);
            sum[x] += n - 1 - i;
        }
        if (sum[0] == sum[1] && sum[1] == sum[2]) {
            string s = "RBW";
            vector<string> ans(n - 1);
            rep(i, n - 1) ans[i].resize(n - i - 1);
            rep(i, 3) {
                for (auto x : v[i]) {
                    FOR(j, x + 1, n) {
                        ans[x][j - x - 1] = s[i];
                    }
                }
            }
            co("Yes");
            rep(i, n - 1) co(ans[i]);
            return 0;
        }
    }

    co("No");

    return 0;
}
