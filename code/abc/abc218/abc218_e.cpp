// clang-format off
#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ld = long double;
#define FOR(i, m, n) for(int i = (m); i < (n); ++i)
#define FORR(i, m, n) for(int i = (m)-1; i >= (n); --i)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FOR(i, 1, n+1)
#define repr(i, n) FORR(i, n, 0)
#define repnr(i, n) FORR(i, n+1, 1)
#define all(s) (s).begin(), (s).end()
template <class T, class U>
bool chmax(T &a, const U b) { return a < b ? a = b, true : false; }
template <class T, class U>
bool chmin(T &a, const U b) { return b < a ? a = b, true : false; }
template <class T>
istream &operator>>(istream &is, vector<T> &v) { for (T &i : v) is>>i; return is; }
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    for (auto it=v.begin(); it!=v.end(); ++it) { os<<(it==v.begin()?"":" ")<<*it; } return os;
}
template <class Head, class... Tail>
void co(Head&& head, Tail&&... tail) {
    if constexpr(sizeof...(tail)==0) cout<<head<<'\n'; else cout<<head<<' ',co(forward<Tail>(tail)...);
}
template <class Head, class... Tail>
void ce(Head&& head, Tail&&... tail) {
    if constexpr(sizeof...(tail)==0) cerr<<head<<'\n'; else cerr<<head<<' ',ce(forward<Tail>(tail)...);
}
template<typename T, typename... Args>
auto make_vector(T x, int arg, Args ...args) {
    if constexpr(sizeof...(args)==0) return vector<T>(arg, x); else return vector(arg,make_vector<T>(x, args...));
}
void sonic() { ios::sync_with_stdio(false); cin.tie(nullptr); }
void setp(const int n) { cout << fixed << setprecision(n); }
constexpr int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
const double PI = acos(-1);

struct union_find {
    vector<int> data;

    union_find(int _n) : data(_n, -1) {}

    int root(int x) { return data[x] < 0 ? x : data[x] = this->root(data[x]); }

    bool is_root(int x) { return data[x] < 0; }

    void unite(int x, int y) {
        x = this->root(x), y = this->root(y);
        if (x != y) {
            if (data[x] > data[y]) swap(x, y);
            data[x] += data[y];
            data[y] = x;
        }
    }

    int size(int x) { return -data[this->root(x)]; }

    bool same(int x, int y) { return this->root(x) == this->root(y); }
};

// clang-format on

struct S {
    int a, b, c;
};

int main(void) {
    int n, m;
    cin >> n >> m;
    union_find uf(n);
    vector<S> v(m);
    rep(i, m) cin >> v[i].a >> v[i].b >> v[i].c;
    sort(all(v), [&](S x, S y) {
        return x.c < y.c;
    });

    ll ans = 0;
    rep(i, m) {
        if (uf.same(v[i].a - 1, v[i].b - 1)) {
            ans += max(0, v[i].c);
        } else {
            uf.unite(v[i].a - 1, v[i].b - 1);
        }
    }
    co(ans);

    return 0;
}
