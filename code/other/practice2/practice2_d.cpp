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
void co() { cout << endl; }
template <class Head, class... Tail>
void co(Head&& head, Tail&&... tail) {
    cout << head << ' ';
    co(forward<Tail>(tail)...);
}
void ce() { cerr << endl; }
template <class Head, class... Tail>
void ce(Head&& head, Tail&&... tail) {
    cerr << head << ' ';
    ce(forward<Tail>(tail)...);
}
void sonic(){ios::sync_with_stdio(false); cin.tie(0);}
void setp(const int n){cout << fixed << setprecision(n);}
constexpr int INF = 1e9+1;
constexpr ll LINF = 1e18L+1;
constexpr ll MOD = 1e9L+7;
constexpr ll MOD_N = 998244353;
constexpr ld EPS = 1e-11;
const double PI = acos(-1);

Vec dir_x = {1, -1, 0, 0};
Vec dir_y = {0, 0, 1, -1};

vector<string> board;

bool in_board(ll x, ll y){
    return x >= 0 && x < board.size() && y >= 0 && y < board[0].size() &&
           board[x][y] == '.';
}

ll xytop(ll x, ll y){
    return x * board[0].size() + y + 1;
}

P ptoxy(ll p){
    --p;
    return {p / board[0].size(), p % board[0].size()};
}

int main(void){
    ll n, m;
    cin >> n >> m;
    board.resize(n);
    rep(i, n) cin >> board[i];

    const ll sz = n * m;
    const ll s = 0, t = sz + 1;
    mf_graph<ll> mf(sz + 2);
    rep(i, n) rep(j, m){
        ll a = xytop(i, j);
        if ((i + j) & 1) mf.add_edge(a, t, 1);
        else
            mf.add_edge(s, a, 1);
    }
    rep(i, n) rep(j, m){
        if ((i + j) & 1) continue;
        rep(k, 4){
            ll x = i + dir_x[k], y = j + dir_y[k];
            if(in_board(i, j) && in_board(x, y))
                mf.add_edge(xytop(i, j), xytop(x, y), 1);
        }
    }

    co(mf.flow(s, t));

    auto edges = mf.edges();
    for(auto e : edges){
        if (e.from == s || e.to == t || e.flow == 0) continue;
        ll x1, x2, y1, y2;
        P p;
        p = ptoxy(e.from);
        x1 = p.first, y1 = p.second;
        p = ptoxy(e.to);
        x2 = p.first, y2 = p.second;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        // ce(x1, y1, x2, y2);
        if(x1 == x2){
            board[x1][y1] = '>';
            board[x2][y2] = '<';
        }else{
            board[x1][y1] = 'v';
            board[x2][y2] = '^';
        }
    }
    // ce("ok!!!!");
    rep(i, n) co(board[i]);

    return 0;
}
