// clang-format off
#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ld = long double;
using Pi = pair<int, int>;
using Pl = pair<ll, ll>;
using Vi = vector<int>;
using Vl = vector<ll>;
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

// clang-format on

struct union_find {
    vector<int> par;
    vector<int> sz;
    vector<int> color;
    vector<bool> f;
    vector<vector<int>> data;

    union_find(int _n) : par(_n), sz(_n, 1), color(_n, -1), f(_n), data(_n) {
        iota(par.begin(), par.end(), 0);
        for (int i = 0; i < _n; ++i) {
            data[i].emplace_back(i);
        }
    }

    int root(int x) {
        if (par[x] == x)
            return x;
        return par[x] = root(par[x]);
    }

    void unite(int x, int y, int d) {
        if (is_same(x, y)) {
            if ((color[x] + color[y]) % 2 != d % 2) {
                f[root(x)] = true;
            }
            return;
        } else if (x != y) {
            if (color[x] == -1 && color[y] == -1) {
                color[x] = 0;
                color[y] = d % 2;
            } else if (color[x] == -1) {
                color[x] = (color[y] + d) % 2;
            } else if (color[y] == -1) {
                color[y] = (color[x] + d) % 2;
            } else if ((color[x] + color[y]) % 2 != d % 2) {
                for (auto i : data[root(y)]) {
                    color[i] = !color[i];
                }
            }
            x = root(x), y = root(y);
            if (sz[x] < sz[y])
                swap(x, y);
            par[y] = x;
            sz[x] += sz[y];
            if (f[y]) {
                f[x] = true;
            }
            data[x].insert(data[x].end(), data[y].begin(), data[y].end());
        }
    }

    int size(int x) {
        return sz[root(x)];
    }

    bool is_same(int x, int y) {
        return root(x) == root(y);
    }

    bool query(int x, int y) {
        return is_same(x, y) && (f[root(x)] || color[x] == color[y]);
    }
};

int main(void) {
    int n, q;
    cin >> n >> q;
    union_find uf(n);

    rep(i, q) {
        int w, x, y, z;
        cin >> w >> x >> y >> z;
        --x, --y;
        if (w == 1){
            uf.unite(x, y, z);
        } else {
            if (uf.query(x,y))
                puts("YES");
            else
                puts("NO");
        }
        // ce(uf.color);
    }

    return 0;
}
