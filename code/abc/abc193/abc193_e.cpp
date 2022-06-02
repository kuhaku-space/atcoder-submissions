#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ld = long double;
using Pi = pair<int, int>;
using Pl = pair<ll, ll>;
using Vi = vector<int>;
using Vl = vector<ll>;
using Vp = vector<Pl>;
template <class T>
using Vv = vector<vector<T>>;
#define FOR(i, m, n, d) for(int i = (m); i < (n); i += d)
#define FORR(i, m, n, d) for(int i = (m)-1; i >= (n); i -= d)
#define rep(i, n) FOR(i, 0, n, 1)
#define repn(i, n) FOR(i, 1, n+1, 1)
#define repr(i, n) FORR(i, n, 0, 1)
#define repnr(i, n) FORR(i, n+1, 1, 1)
#define all(s) (s).begin(), (s).end()
template <class T, class U>
bool chmax(T &a, const T b) { return a < b ? a = b, true : false; }
template <class T, class U>
bool chmin(T &a, const U b) { return b < a ? a = b, true : false; }
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
constexpr int64_t INF = 1000000000000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
const double PI = acos(-1);

/*
 * a * x + b * y = gcd(a, b) の答えを一つ求める
 * 戻り値は gcd(a, b)
 */
int64_t extGCD(const int64_t a, const int64_t b, int64_t &x, int64_t &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }

    int64_t d = extGCD(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

/*
 * 任意の i において、x % b_i = m_i となる x を求める
 * x = r + M * k (k in N) と表すことができる
 */
pair<int64_t, int64_t> chinese_rem(const vector<int64_t> &b,
                                   const vector<int64_t> &m) {
    int64_t r = 0, M = 1;
    int64_t n = b.size();
    for (int64_t i = 0; i < n; ++i) {
        int64_t p, q;
        int64_t d = extGCD(M, m[i], p, q);
        if ((b[i] - r) % d != 0) return {0, -1};
        int64_t tmp = (b[i] - r) / d * p % (m[i] / d);
        r += M * tmp;
        M *= m[i] / d;
    }
    return {r >= 0 ? r % M : M - 1 - (-r - 1) % M, M};
}

void solve() {
    ll x, y, p, q;
    cin >> x >> y >> p >> q;

    ll ans = (1LL << 62);
/*
    rep(i, 10) {
        rep(j, 10) {
            rep(k, y) {
                rep(l, q) {
                    ll a = (x + y) * 2 * i + x + k;
                    ll b = (p + q) * j + p + l;
                    if (a == b)
                        chmin(ans, a);
                }
            }
        }
    }
*/

    if (ans != (1LL << 62)) {
        co(ans);
        return;
    }

    rep(i, y) {
        rep(j, q) {
            Vl b = {x + i, p + j};
            Vl m = {(x + y) * 2, p + q};
            auto pr = chinese_rem(b, m);
            if(pr.second != -1) chmin(ans, pr.first);
        }
    }
    if (ans == (1LL << 62)) {
        co("infinity");
        return;
    }
    co(ans);
}

int main(void) {
    ll t;
    cin >> t;
    rep(i, t) solve();

    return 0;
}
