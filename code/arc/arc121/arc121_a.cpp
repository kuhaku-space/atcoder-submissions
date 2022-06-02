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
    vector<pair<pair<int, int>, int>> p(n);
    rep(i, n) cin >> p[i].first.first >> p[i].first.second;
    rep(i, n) p[i].second = i;

    sort(all(p));
    vector<pair<int, pair<int, int>>> x;
    int a = p[n - 1].second, b = p[0].second;
    if (a > b)
        swap(a, b);
    x.push_back({p[n - 1].first.first - p[0].first.first, {a, b}});
    a = p[n - 2].second, b = p[0].second;
    if (a > b)
        swap(a, b);
    x.push_back({p[n - 2].first.first - p[0].first.first, {a, b}});
    a = p[n - 1].second, b = p[1].second;
    if (a > b)
        swap(a, b);
    x.push_back({p[n - 1].first.first - p[1].first.first, {a, b}});
    sort(all(p), [](auto a, auto b) { return a.first.second < b.first.second; });
    a = p[n - 1].second, b = p[0].second;
    if (a > b)
        swap(a, b);
    x.push_back({p[n - 1].first.second - p[0].first.second, {a, b}});
    a = p[n - 2].second, b = p[0].second;
    if (a > b)
        swap(a, b);
    x.push_back({p[n - 2].first.second - p[0].first.second, {a, b}});
    a = p[n - 1].second, b = p[1].second;
    if (a > b)
        swap(a, b);
    x.push_back({p[n - 1].first.second - p[1].first.second, {a, b}});

    sort(all(x));
    reverse(all(x));

    if (x[0].second == x[1].second)
        co(x[2].first);
    else
        co(x[1].first);

    return 0;
}
