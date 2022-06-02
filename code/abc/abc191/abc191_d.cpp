#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ld = long double;
using P = pair<ll, ll>;
using Vec = vector<ll>;
using VecP = vector<P>;
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
bool chmax(T1 &a, const T2 b) { return a < b ? a = b, true : false; }
template <class T1, class T2>
bool chmin(T1 &a, const T2 b) { return a > b ? a = b, true : false; }
template <class T>
istream &operator>>(istream &is, vector<T> &v) { for (T &i : v) is >> i; return is; }
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) { for (const T &i : v) os << i << ' '; return os; }
void _co() { cout << '\n'; }
template <class Head, class... Tail>
void _co(Head&& head, Tail&&... tail) { cout << ' ' << head; _co(forward<Tail>(tail)...); }
template <class Head, class... Tail>
void co(Head&& head, Tail&&... tail) { cout << head; _co(forward<Tail>(tail)...); }
void ce() { cerr << '\n'; }
template <class Head, class... Tail>
void ce(Head&& head, Tail&&... tail) { cerr << head << ' '; ce(forward<Tail>(tail)...); }
void sonic() { ios::sync_with_stdio(false); cin.tie(nullptr); }
void setp(const int n) { cout << fixed << setprecision(n); }
constexpr int64_t INF = 1000000000000000001;
constexpr int64_t MOD = 1000000007;
constexpr int64_t MOD_N = 998244353;
constexpr long double EPS = 1e-11;
const double PI = acos(-1);

int64_t floor_div(int64_t p, int64_t q) {
    int64_t res = p / q;
    if (q * res > p) --res;
    return res;
}

int main(void) {
    ld a, b, c;
    cin >> a >> b >> c;
    ll x = round(a * 10000), y = round(b * 10000), d = round(c * 10000);

    ll ans = 0;
    for (int64_t i = -2100000000; i < 2100000000; i += 10000) {
        if (i < x - d || i > x + d)
            continue;
        ll l = y, r = 2100000000;
        while (r - l > 1) {
            ll m = (l + r) / 2;
            if ((x - i) * (x - i) + (y - m) * (y - m) <= d * d)
                l = m;
            else
                r = m;
        }
        ll s = floor_div(l, 10000);
        l = -2100000000, r = y;
        while (r - l > 1) {
            ll m = (l + r) / 2;
            if ((x - i) * (x - i) + (y - m) * (y - m) <= d * d)
                r = m;
            else
                l = m;
        }
        ll t = floor_div(l, 10000);
        // ce(i, s, t);
        ans += s - t;
    }
    co(ans);
    
    return 0;
}