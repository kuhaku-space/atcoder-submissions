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
constexpr int64_t LINF = 1000000000000000001;
constexpr int64_t MOD = 1000000007;
constexpr int64_t MOD_N = 998244353;
constexpr long double EPS = 1e-11;
const double PI = acos(-1);

template<class Key, class Val>
struct UMap {
    Val e;
    unordered_map<Key, Val> data;

    UMap(Val _e = Val()) : e(_e), data() {}

    Val &operator[](Key k) {
        if (data.find(k) == data.end())
            data[k] = e;
        return data[k];
    }

    void print_debug() {
        for (auto [k, v] : data) {
            cerr << k << ", " << v << endl;
        }
    }
};


int main(void) {
    ll x, y;
    cin >> x >> y;

    UMap<ll, ll> mp(LINF);

    queue<P> que;
    que.push({y, 0});
    while (!que.empty()) {
        auto [t, c] = que.front();
        que.pop();
        if (!chmin(mp[t], c))
            continue;
        chmin(mp[x], c + abs(x - t));
        if (t < x)
            continue;
        if (t & 1) {
            que.push({t >> 1, c + 2});
            que.push({(t >> 1) + 1, c + 2});
        } else
            que.push({t >> 1, c + 1});
    }
    cout << mp[x] << endl;

    // mp.print_debug();

    return 0;
}