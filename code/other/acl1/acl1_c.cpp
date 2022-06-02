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

ll n, m;
vector<string> board;

bool in_board(ll x, ll y){
    return x >= 0 && x < n && y >= 0 && y < m && board[x][y] != '#';
}

int main(void) {
    cin >> n >> m;
    board.resize(n);
    rep(i, n) cin >> board[i];

    const ll sz = n * m + 2;
    const ll s = sz - 2, g = sz - 1;
    const int bias = 1000;
    mcf_graph<int, ll> mf(sz);
    ll sum = 0;
    rep(i, n) rep(j, m){
        if (board[i][j] == 'o'){
            mf.add_edge(s, i * m + j, 1, 0);
            sum += bias - i - j;
        }
        if (board[i][j] != '#') mf.add_edge(i * m + j, g, 1, bias - i - j);
    }
    rep(i, n){
        rep(j, m){
            if(in_board(i, j) && in_board(i + 1, j))
                mf.add_edge(i * m + j, (i + 1) * m + j, INF, 0);
            if(in_board(i, j) && in_board(i, j + 1))
                mf.add_edge(i * m + j, i * m + j + 1, INF, 0);
        }
    }

    auto p = mf.flow(s, g);
    co(sum - p.second);

    return 0;
}
