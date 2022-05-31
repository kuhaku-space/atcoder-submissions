#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ld = long double;
using P = pair<ll, ll>;
using Pld = pair<ld, ld>;
using Vec = vector<ll>;
using VecP = vector<P>;
using VecB = vector<bool>;
using VecC = vector<char>;
using VecD = vector<ld>;
using VecS = vector<string>;
template <class T>
using Vec2 = vector<vector<T>>;
#define REP(i, m, n) for(ll i = (m); i < (n); ++i)
#define REPN(i, m, n) for(ll i = (m); i <= (n); ++i)
#define REPR(i, m, n) for(ll i = (m)-1; i >= (n); --i)
#define REPNR(i, m, n) for(ll i = (m); i >= (n); --i)
#define rep(i, n) REP(i, 0, n)
#define repn(i, n) REPN(i, 1, n)
#define repr(i, n) REPR(i, n, 0)
#define repnr(i, n) REPNR(i, n, 1)
#define all(s) (s).begin(), (s).end()
template <class T1, class T2>
bool chmax(T1 &a, const T2 b) { if (a < b) { a = b; return true; } return false; }
template <class T1, class T2>
bool chmin(T1 &a, const T2 b) { if (a > b) { a = b; return true; } return false; }
template <class T>
istream &operator>>(istream &is, vector<T> &v) { for (T &i : v) is >> i; return is; }
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) { for (const T &i : v) os << i << ' '; return os; }
void co() { cout << '\n'; }
template <class Head, class... Tail>
void co(Head&& head, Tail&&... tail) { cout << head << ' '; co(forward<Tail>(tail)...); }
void ce() { cerr << '\n'; }
template <class Head, class... Tail>
void ce(Head&& head, Tail&&... tail) { cerr << head << ' '; ce(forward<Tail>(tail)...); }
void sonic() { ios::sync_with_stdio(false); cin.tie(nullptr); }
void setp(const int n) { cout << fixed << setprecision(n); }
constexpr int64_t LINF = 1000000000000000001;
constexpr int64_t MOD = 1000000007;
constexpr int64_t MOD_N = 998244353;
constexpr long double EPS = 1e-11;
const double PI = acos(-1);

int main(void) {
    ll n, c;
    cin >> n >> c;
    Vec x(n), v(n);
    rep(i, n) cin >> x[i] >> v[i];

    Vec a(n);
    rep(i, n) a[i] = v[i];
    rep(i, n - 1) a[i + 1] += a[i];
    rep(i, n) a[i] -= x[i];

    Vec b(n);
    rep(i, n) b[i] = v[i];
    repr(i, n - 1) b[i] += b[i + 1];
    rep(i, n) b[i] -= c - x[i];

    Vec maxa(n);
    rep(i, n) chmax(maxa[i], a[i] - x[i]);
    rep(i, n - 1) chmax(maxa[i + 1], maxa[i]);
    Vec maxb(n);
    rep(i, n) chmax(maxb[i], b[i] - c + x[i]);
    repr(i, n - 1) chmax(maxb[i], maxb[i + 1]);

    ll ans = 0;
    chmax(ans, *max_element(all(a)));
    chmax(ans, *max_element(all(b)));
    rep(i, n) {
        if (i < n - 1) chmax(ans, a[i] + maxb[i + 1]);
        if (i) chmax(ans, b[i] + maxa[i - 1]);
    }
    cout << ans << endl;

    return 0;
}