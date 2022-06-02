#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using ll = long long;
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
#define pb push_back
#define fs first
#define sc second
template <class T1, class T2>
bool chmax(T1 &a, const T2 b){if(a < b){a = b; return true;} return false;}
template <class T1, class T2>
bool chmin(T1 &a, const T2 b){if(a > b){a = b; return true;} return false;}
ll pow2(const int n){return (1LL << n);}
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    for (const T &i : v) os << i << ' ';
    return os;
}
void co() { cout << '\n'; }
template <class Head, class... Tail>
void co(Head&& head, Tail&&... tail) {
    cout << head << ' ';
    co(forward<Tail>(tail)...);
}
void ce() { cerr << '\n'; }
template <class Head, class... Tail>
void ce(Head&& head, Tail&&... tail) {
    cerr << head << ' ';
    ce(forward<Tail>(tail)...);
}
void sonic(){ios::sync_with_stdio(false); cin.tie(0);}
void setp(const int n){cout << fixed << setprecision(n);}
constexpr int INF = 1000000001;
constexpr ll LINF = 1000000000000000001;
constexpr ll MOD = 1000000007;
constexpr ll MOD_N = 998244353;
constexpr ld EPS = 1e-11;
const double PI = acos(-1);

int main(void) {
    ll n, k;
    cin >> n >> k;
    Vec2<ll> a(n, Vec(n));
    rep(i, n) rep(j, n) cin >> a[i][j];

    const ll sz = n * n + 2 * n + 2, n2 = n * n;
    mcf_graph<int, ll> mcf(sz);
    mcf.add_edge(sz - 2, sz - 1, n * k, INF);
    rep(i, n){
        mcf.add_edge(sz - 2, n2 + i, k, 0);
        mcf.add_edge(n2 + n + i, sz - 1, k, 0);
        rep(j, n){
            mcf.add_edge(n2 + i, i * n + j, 1, INF - a[i][j]);
            mcf.add_edge(i * n + j, n2 + n + j, 1, 0);
        }
    }

    auto p = mcf.flow(sz - 2, sz - 1, n * k);
    co(n * k * INF - p.second);

    vector<string> ans;
    string s;
    rep(i, n) s += '.';
    rep(i, n) ans.push_back(s);
    auto edges = mcf.edges();
    for (auto e : edges) {
        if(e.to >= 0 && e.to < n2){
            if (e.flow) ans[e.to / n][e.to % n] = 'X';
        }
    }
    rep(i, n) co(ans[i]);

    return 0;
}