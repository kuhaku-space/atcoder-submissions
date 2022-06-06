#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/template/atcoder.hpp"
#pragma GCC target("avx")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#line 2 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/template/template.hpp"
#include <bits/stdc++.h>
using namespace std;
template <class T, class U>
bool chmax(T &a, const U &b) {
    return a < b ? a = b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U &b) {
    return b < a ? a = b, true : false;
}
constexpr int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
const double PI = acos(-1.0);
#line 6 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/template/atcoder.hpp"
using ll = int64_t;
using ld = long double;
#define FOR(i, m, n) for(int i = (m); i < (n); ++i)
#define FORR(i, m, n) for(int i = (m)-1; i >= (n); --i)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FOR(i, 1, n+1)
#define repr(i, n) FORR(i, n, 0)
#define repnr(i, n) FORR(i, n+1, 1)
#define all(s) (s).begin(), (s).end()
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
#line 3 "a.cpp"

struct union_find {
    vector<int> data;

    union_find() : data() {}
    union_find(int _n) : data(_n, -1) {}

    int root(int x) {
        return this->data[x] < 0 ? x : this->data[x] = this->root(data[x]);
    }
    int get_root(int x) {
        return this->root(x);
    }

    bool is_root(int x) {
        return this->data[x] < 0;
    }

    bool unite(int x, int y) {
        x = this->root(x), y = this->root(y);
        if (x != y) {
            if (this->data[x] > this->data[y])
                swap(x, y);
            this->data[x] += this->data[y];
            this->data[y] = x;
            return true;
        }
        return false;
    }

    int size(int x) {
        return -(this->data[this->root(x)]);
    }
    int get_size(int x) {
        return this->size(x);
    }

    bool same(int x, int y) {
        return this->root(x) == this->root(y);
    }
    bool is_same(int x, int y) {
        return this->same(x, y);
    }
};

int main(void) {
    sonic();
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> a(m);
    rep(i, m) cin >> a[i].first >> a[i].second;

    rep(i, m) {
        --a[i].first, --a[i].second;
        if (a[i].first > a[i].second)
            swap(a[i].first, a[i].second);
    }
    sort(all(a));
    reverse(all(a));

    union_find uf(n);
    vector<int> ans(n + 1);
    int cnt = 0;
    int idx = 0;
    repr(i, n) {
        ++cnt;
        while (idx < m && a[idx].first == i) {
            cnt -= uf.unite(a[idx].first, a[idx].second);
            ++idx;
        }
        ans[i] = cnt;
    }
    repn(i, n) co(ans[i]);

    return 0;
}
