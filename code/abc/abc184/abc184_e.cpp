#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ld = long double;
using P = pair<ll, ll>;
using Vec = vector<ll>;
using VecP = vector<P>;
template <class T>
using Vec2 = vector<vector<T>>;
#define REP(i, m, n) for (ll i = (m); i < (n); ++i)
#define REPN(i, m, n) for (ll i = (m); i <= (n); ++i)
#define REPR(i, m, n) for (ll i = (m)-1; i >= (n); --i)
#define REPNR(i, m, n) for (ll i = (m); i >= (n); --i)
#define rep(i, n) REP(i, 0, n)
#define repn(i, n) REPN(i, 1, n)
#define repr(i, n) REPR(i, n, 0)
#define repnr(i, n) REPNR(i, n, 1)
#define all(s) (s).begin(), (s).end()
template <class T1, class T2>
bool chmax(T1 &a, const T2 b) {
    return a < b ? a = b, true : false;
}
template <class T1, class T2>
bool chmin(T1 &a, const T2 b) {
    return a > b ? a = b, true : false;
}
template <class T>
istream &operator>>(istream &is, vector<T> &v) {
    for (T &i : v) is >> i;
    return is;
}
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    for (const T &i : v) os << i << ' ';
    return os;
}
void _co() {
    cout << '\n';
}
template <class Head, class... Tail>
void _co(Head &&head, Tail &&...tail) {
    cout << ' ' << head;
    _co(forward<Tail>(tail)...);
}
template <class Head, class... Tail>
void co(Head &&head, Tail &&...tail) {
    cout << head;
    _co(forward<Tail>(tail)...);
}
void ce() {
    cerr << '\n';
}
template <class Head, class... Tail>
void ce(Head &&head, Tail &&...tail) {
    cerr << head << ' ';
    ce(forward<Tail>(tail)...);
}
void sonic() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}
void setp(const int n) {
    cout << fixed << setprecision(n);
}
constexpr int64_t INF = 1000000000000000001;
constexpr int64_t MOD = 1000000007;
constexpr int64_t MOD_N = 998244353;
constexpr long double EPS = 1e-11;
const double PI = acos(-1);

struct S {
    ll x, y, d;
};

int main(void) {
    ll h, w;
    cin >> h >> w;
    vector<string> s(h);
    rep(i, h) cin >> s[i];

    queue<S> que;
    rep(i, h) {
        rep(j, w) {
            if (s[i][j] == 'S')
                que.push(S{i, j, 0});
        }
    }

    unordered_map<char, vector<P>> ump;
    rep(i, h) rep(j, w) {
        ll c = s[i][j];
        if (c >= 'a' && c <= 'z')
            ump[c].push_back({i, j});
    }

    auto in_board = [&](ll x, ll y) {
        return x >= 0 && x < h && y >= 0 && y < w && s[x][y] != '#';
    };

    bitset<26> is_used;
    Vec2<ll> dist(h, Vec(w, INF));
    Vec dx = {1, -1, 0, 0}, dy = {0, 0, 1, -1};
    while (!que.empty()) {
        auto [x, y, d] = que.front();
        que.pop();
        if (!chmin(dist[x][y], d))
            continue;
        rep(i, 4) {
            ll a = x + dx[i], b = y + dy[i];
            if (!in_board(a, b))
                continue;
            que.push(S{a, b, d + 1});
        }

        ll c = s[x][y];
        if (c >= 'a' && c <= 'z' && !is_used[c - 'a']) {
            is_used.set(c - 'a');
            for (auto [a, b] : ump[c]) {
                que.push(S{a, b, d + 1});
            }
        }
    }

    ll ans;
    rep(i, h) rep(j, w) {
        if (s[i][j] == 'G')
            ans = dist[i][j];
    }
    if (ans == INF)
        ans = -1;
    co(ans);

    return 0;
}