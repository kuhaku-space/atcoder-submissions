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
#define REP(i, m, n) for(ll i = ll(m); i < ll(n); ++i)
#define REPN(i, m, n) for(ll i = ll(m); i <= ll(n); ++i)
#define REPR(i, m, n) for(ll i = ll(m)-1; i >= ll(n); --i)
#define REPNR(i, m, n) for(ll i = ll(m); i >= ll(n); --i)
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
void sonic() { ios::sync_with_stdio(false); cin.tie(0); }
void setp(const int n) { cout << fixed << setprecision(n); }
constexpr int64_t LINF = 1000000000000000001;
constexpr int64_t MOD = 1000000007;
constexpr int64_t MOD_N = 998244353;
constexpr long double EPS = 1e-11;
const double PI = acos(-1);


vector<set<ll>> par;
VecS ss;
ll n;

void dfs(ll x, ll p) {
    if (par[p].find(x) != par[p].end()) return;
    par[p].insert(x);
    rep(i, n) {
        if (ss[i][x] == '1') dfs(i, p);
    }
}

int main(void) {
    cin >> n;
    par.resize(n);
    ss.resize(n);
    rep(i, n) cin >> ss[i];
    rep(i, n) dfs(i, i);

    ld ans = 0;
    rep(i, n) {
        ans += 1.0L / par[i].size();
    }
    setp(20);
    cout << ans << endl;

    return 0;
}