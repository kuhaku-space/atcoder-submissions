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

struct Doubling {
    const int size = 64;
    int n;
    vector<vector<int>> data;
    vector<vector<int64_t>> score;

    Doubling(int _n) : n(_n), data(size, vector<int>(_n)), score(size, vector<int64_t>(_n)) {}

    void build(const vector<int> &v, const vector<int> &w) {
        for (int i = 0; i < n; ++i) data[0][i] = v[i];
        for (int i = 0; i < n; ++i) score[0][i] = w[v[i]];

        for (int i = 0; i < size - 1; ++i) {
            for (int j = 0; j < n; ++j) {
                data[i + 1][j] = data[i][data[i][j]];
                score[i + 1][j] = score[i][j] + score[i][data[i][j]];
            }
        }
    }

    pair<int, int64_t> solve(int f, int64_t k) {
        int64_t res = 0;
        for (int cnt = 0; k > 0; k >>= 1, ++cnt) {
            if (k & 1) {
                res += score[cnt][f];
                f = data[cnt][f];
            }
        }
        return {f, res};
    }
};

int main(void) {
    sonic();
    int n, k;
    cin >> n >> k;
    vector<int> p(n), c(n);
    cin >> p >> c;
    rep(i, n) {
        --p[i];
    }
    Doubling db(n);
    db.build(p, c);

    ll ans = -INF;
    if (k < n * 2) {
        rep(i, n) {
            ll score = 0;
            int f = i;
            rep(j, k) {
                f = p[f];
                score += c[f];
                chmax(ans, score);
            }
        }
    } else {
        rep(i, n) {
            ll score = 0;
            int f = i;
            rep(j, n) {
                f = p[f];
                score += c[f];
                chmax(ans, score);
            }
            auto [a, b] = db.solve(i, k - n);
            f = a, score = b;
            chmax(ans, score);
            rep(j, n) {
                f = p[f];
                score += c[f];
                chmax(ans, score);
            }
        }
    }
    co(ans);

    return 0;
}
