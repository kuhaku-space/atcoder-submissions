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

int main(void) {
    sonic();
    int n;
    cin >> n;
    vector<ll> x(n), y(n);
    vector<char> d(n);
    rep(i, n) cin >> x[i] >> y[i] >> d[i];
    rep(i, n) {
        x[i] *= 2;
        y[i] *= 2;
    }

    set<ll> st;
    st.insert(0);
    rep(_, 4) {
        ll umax = -INF, lrmax = -INF, dmax = -INF;
        rep(i, n) {
            if (d[i] == 'U')
                chmax(umax, y[i]);
            else if (d[i] == 'D')
                chmax(dmax, y[i]);
            else
                chmax(lrmax, y[i]);
        }

        if (umax != -INF && lrmax != -INF) {
            st.insert(max(0L, lrmax - umax));
        }
        if (lrmax != -INF && dmax != -INF) {
            st.insert(max(0L, dmax - lrmax));
        }
        if (umax != -INF && dmax != -INF) {
            st.insert(max(0L, (dmax - umax) / 2));
        }

        string s = "ULDRU";
        rep(i, n) {
            ll t = x[i];
            x[i] = -y[i];
            y[i] = t;
            rep(j, 4) {
                if (d[i] == s[j]) {
                    d[i] = s[j + 1];
                    break;
                }
            }
        }
    }

    long double ans = INF;
    for (auto t : st) {
        // ce(t);
        ll xmax = -INF, xmin = INF, ymax = -INF, ymin = INF;
        rep(i, n) {
            ll dx = 0, dy = 0;
            if (d[i] == 'R')
                dx = t;
            else if (d[i] == 'L')
                dx = -t;
            else if (d[i] == 'U')
                dy = t;
            else
                dy = -t;
            chmax(xmax, x[i] + dx);
            chmin(xmin, x[i] + dx);
            chmax(ymax, y[i] + dy);
            chmin(ymin, y[i] + dy);
        }
        chmin(ans, (long double)(xmax - xmin) * (ymax - ymin) / 4);
    }
    setp(10);
    co(ans);

    return 0;
}
