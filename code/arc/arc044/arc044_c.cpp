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
#line 3 "a.cpp"

int main(void) {
    sonic();
    int h, w, q;
    cin >> h >> w >> q;

    unordered_map<int, int> ansx, ansy;
    set<int> sx, sy;
    rep(i, h) sx.emplace(i);
    rep(i, w) sy.emplace(i);

    vector<tuple<int, int, int>> v;
    rep(i, q) {
        int a, b, c;
        cin >> a >> b >> c;
        v.emplace_back(a - 1, b, c - 1);
    }
    sort(all(v));
    reverse(all(v));

    int idx = 0;
    repr(i, 100000) {
        vector<int> vx, vy;
        while (idx < q && get<0>(v[idx]) == i) {
            if (get<1>(v[idx]) == 0)
                vx.emplace_back(get<2>(v[idx]));
            else
                vy.emplace_back(get<2>(v[idx]));
            ++idx;
        }

        if (vx.size() == h || vy.size() == w) {
            co(-1);
            return 0;
        }

        for (auto x : vx) sx.erase(x);
        for (auto y : vy) sy.erase(y);

        vector<pair<int, int>> u;
        for (auto x : vx) {
            auto it = sx.lower_bound(x);
            if (it == sx.end()) {
                u.emplace_back(x, ansx[*prev(it)] + x - *prev(it));
            } else if (it == sx.begin()) {
                u.emplace_back(x, ansx[*it] + *it - x);
            } else {
                u.emplace_back(x, min(ansx[*it] + *it - x, ansx[*prev(it)] + x - *prev(it)));
            }
        }
        for (auto p : u) ansx[p.first] = p.second;
        u.clear();
        for (auto y : vy) {
            auto it = sy.lower_bound(y);
            if (it == sy.end()) {
                u.emplace_back(y, ansy[*prev(it)] + y - *prev(it));
            } else if (it == sy.begin()) {
                u.emplace_back(y, ansy[*it] + *it - y);
            } else {
                u.emplace_back(y, min(ansy[*it] + *it - y, ansy[*prev(it)] + y - *prev(it)));
            }
        }
        for (auto p : u) ansy[p.first] = p.second;

        for (auto x : vx) sx.emplace(x);
        for (auto y : vy) sy.emplace(y);
    }

    // for (auto p : ansx) ce(p.first, p.second);
    // for (auto p : ansy) ce(p.first, p.second);
    int minx = Inf, miny = Inf;
    rep(i, h) chmin(minx, ansx[i]);
    rep(i, w) chmin(miny, ansy[i]);
    co(minx + miny);

    return 0;
}
