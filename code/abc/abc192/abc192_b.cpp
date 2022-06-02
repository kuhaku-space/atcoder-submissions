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
#define REP(i, m, n) for(int i = (m); i < (n); ++i)
#define FOR(i, m, n, d) for(int i = (m); i < (n); i += d)
#define FORR(i, m, n, d) for(int i = (m)-1; i >= (n); i -= d)
#define rep(i, n) REP(i, 0, n)
#define repn(i, n) FOR(i, 1, n+1, 1)
#define repr(i, n) FORR(i, n, 0, 1)
#define repnr(i, n) FORR(i, n+1, 1)
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
constexpr int64_t INF = 1000000000000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-11;
const double PI = acos(-1);

int main(void) {
    string s;
    cin >> s;
    int n = s.size();
    bool ans = true;
    repr(i, n) {
        if (i & 1)
            ans &= s[i] >= 'A' && s[i] <= 'Z';
        else
            ans &= s[i] >= 'a' && s[i] <= 'z';
    }
    co(ans ? "Yes" : "No");

    return 0;
}
