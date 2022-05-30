#include <bits/stdc++.h>
using namespace std;
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
template <class T>
bool chmax(T &a, const T b){if(a < b){a = b; return true;} return false;}
template <class T>
bool chmin(T &a, const T b){if(a > b){a = b; return true;} return false;}
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

ll h, w;
Vec2<ll> dist;
VecS board;
Vec dx = {2, 1, 0, -1, -2}, dy = {2, 1, 0, -1, -2};

bool in_board(ll x, ll y){
    return x >= 0 && x < h && y >= 0 && y < w && board[x][y] == '.';
}

void bfs_01(ll fx, ll fy) {
    using PP = pair<ll, P>;
    deque<PP> deq;
    deq.push_front({0, {fx, fy}});
    while (!deq.empty()) {
        PP o = deq.front();
        P p = o.second;
        // co(p.first, p.second);
        deq.pop_front();
        if (o.first >= dist[p.first][p.second]) continue;
        dist[p.first][p.second] = o.first;
        for (ll i : dx){
            for(ll j : dx){
                ll x = p.first + i;
                ll y = p.second + j;
                if (((!i || !j) && (abs(i) <= 1 && abs(j) <= 1)) && in_board(x, y)) deq.push_front({o.first, {x, y}});
                else if(in_board(x, y))
                    deq.push_back({o.first + 1, {x, y}});
            }
        }
    }
}

int main(void){
    cin >> h >> w;
    ll fx, fy, ex, ey;
    cin >> fx >> fy >> ex >> ey;
    --fx, --fy, --ex, --ey;
    dist.resize(h);
    rep(i, h) dist[i].resize(w, LINF);
    board.resize(h);
    rep(i, h) cin >> board[i];

    bfs_01(fx, fy);
    ll ans = dist[ex][ey];
    if (ans == LINF) ans = -1;
    co(ans);

    return 0;
}
