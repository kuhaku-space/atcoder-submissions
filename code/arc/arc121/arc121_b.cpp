// clang-format off
#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ld = long double;
using Pi = pair<int, int>;
using Pl = pair<ll, ll>;
using Vi = vector<int>;
using Vl = vector<ll>;
#define FOR(i, m, n) for(int i = (m); i < (n); ++i)
#define FORR(i, m, n) for(int i = (m)-1; i >= (n); --i)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FOR(i, 1, n+1)
#define repr(i, n) FORR(i, n, 0)
#define repnr(i, n) FORR(i, n+1, 1)
#define all(s) (s).begin(), (s).end()
template <class T, class U>
bool chmax(T &a, const U b) { return a < b ? a = b, true : false; }
template <class T, class U>
bool chmin(T &a, const U b) { return b < a ? a = b, true : false; }
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
constexpr int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
const double PI = acos(-1);

// clang-format on

int main(void) {
    int n;
    cin >> n;
    vector<ll> a(n << 1);
    vector<char> c(n << 1);
    rep(i, n << 1) cin >> a[i] >> c[i];
    n <<= 1;


    vector<vector<ll>> x(3);
    rep(i, n) {
        if (c[i] == 'R')
            x[0].emplace_back(a[i]);
        else if (c[i] == 'G')
            x[1].emplace_back(a[i]);
        else
            x[2].emplace_back(a[i]);
    }
    sort(all(x[0]));
    sort(all(x[1]));
    sort(all(x[2]));

    bool flg = true;
    rep(i, 3) flg &= x[i].size() % 2 == 0;
    if (flg) {
        co(0);
        return 0;
    }

    ll ans = INF;
    rep(i, 3) {
        if (x[0].size() % 2 == 1 && x[1].size() % 2 == 1) {
            for (auto i : x[0]) {
                auto idx = lower_bound(all(x[1]), i) - x[1].begin();
                if (idx < x[1].size()) {
                    chmin(ans, x[1][idx] - i);
                }
                if (idx > 0) {
                    chmin(ans, i - x[1][idx - 1]);
                }
            }

            if (x[2].size() >= 2) {
                vector<pair<ll, ll>> p, q;
                rep(it, x[2].size()) {
                    auto s = x[2][it];
                    auto id = lower_bound(all(x[0]), s) - x[0].begin();
                    if (id < x[0].size()) {
                        p.push_back({x[0][id] - s, it});
                    }
                    if (id > 0) {
                        p.push_back({s - x[0][id - 1], it});
                    }
                    id = lower_bound(all(x[1]), s) - x[1].begin();
                    if (id < x[1].size()) {
                        q.push_back({x[1][id] - s, it});
                    }
                    if (id > 0) {
                        q.push_back({s - x[1][id - 1], it});
                    }
                }

                sort(all(p));
                sort(all(q));
                rep(ii, min(10, (int)p.size())) {
                    rep(jj, min(10, (int)q.size())) {
                        if (p[ii].second != q[jj].second) {
                            chmin(ans, p[ii].first + q[jj].first);
                        }
                    }
                }
            }
        }
        swap(x[0], x[1]);
        swap(x[1], x[2]);
    }
    co(ans);

    return 0;
}
