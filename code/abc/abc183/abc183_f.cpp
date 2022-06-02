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

struct union_find {
    vector<int64_t> par;
    vector<unordered_map<ll, ll>> cnt;

    union_find(int64_t _n, Vec c) {
        par.resize(_n);
        cnt.resize(_n);
        for(int64_t i = 0; i < _n; ++i) par[i] = i;
        rep(i, _n) cnt[i][c[i]]++;
    }

    int64_t root(int64_t x) {
        if (par[x] == x) return x;
        return par[x] = root(par[x]);
    }

    void unite(int64_t x, int64_t y) {
        x = root(x), y = root(y);
        if (x != y) {
            if (cnt[x].size() < cnt[y].size()) swap(x, y);
            par[y] = x;
            for (auto i : cnt[y]) {
                cnt[x][i.first] += i.second;
            }
        }
    }

    int64_t query(int64_t x, ll y) {
        if (cnt[root(x)].find(y) == cnt[root(x)].end()) return 0;
        return cnt[root(x)][y];
    }

    bool same(int64_t x, int64_t y) {
        return root(x) == root(y);
    }
};

int main(void) {
    ll n, q;
    cin >> n >> q;
    Vec c(n);
    cin >> c;

    union_find uf(n, c);
    rep(i, q) {
        ll k, a, b;
        cin >> k >> a >> b;
        if (k == 1) uf.unite(--a, --b);
        else
            cout << uf.query(--a, b) << endl;
    }

    return 0;
}