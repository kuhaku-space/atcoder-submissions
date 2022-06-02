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

struct union_find {
    vector<int64_t> par;
    vector<int64_t> sz;

    union_find(int64_t _n) {
        par.resize(_n);
        sz.assign(_n, 1);
        for(int64_t i = 0; i < _n; ++i) par[i] = i;
    }

    int64_t root(int64_t x) {
        if (par[x] == x) return x;
        return par[x] = root(par[x]);
    }

    void unite(int64_t x, int64_t y) {
        x = root(x), y = root(y);
        if (x != y) {
            if (sz[x] > sz[y]) swap(x, y);
            par[y] = x;
            sz[x] += sz[y];
        }
    }

    int64_t size(int64_t x) {
        return sz[root(x)];
    }

    bool same(int64_t x, int64_t y) {
        return root(x) == root(y);
    }
};

int main(void) {
    ll n;
    cin >> n;
    Vec x(n), y(n);
    rep(i, n) cin >> x[i] >> y[i];
    ld l = 0, r = LINF;
    while(r - l > EPS) {
        ld m = (l + r) / 2;
        union_find uf(n + 2);
        rep(i, n) {
            REP(j, i + 1, n) {
                if (pow<ld>(x[i] - x[j], 2) + pow<ld>(y[i] - y[j], 2) <= pow(m * 2, 2))
                    uf.unite(i, j);
            }
        }

        rep(i, n) {
            if (100 - y[i] <= m * 2) uf.unite(n, i);
        }

        rep(i, n) {
            if (y[i] + 100 <= m * 2) uf.unite(n + 1, i);
        }

        if (uf.same(n, n + 1)) r = m;
        else
            l = m;
    }
    setp(10);
    co(l);

    return 0;
}