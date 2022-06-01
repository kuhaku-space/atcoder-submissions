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

int main(void) {
    ll a,b;
    cin >> a >> b;

    setp(10);
    co((ld)(a - b) / a * 100);

    return 0;
}
