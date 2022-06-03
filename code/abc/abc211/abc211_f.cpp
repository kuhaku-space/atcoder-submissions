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

template <class T>
struct BIT {
    const int N;
    vector<T> data;

    BIT() {}
    BIT(int n, T e = T(0)) : N(n + 1), data(n + 1, e) {}
    BIT(const vector<T> &v) : N(v.size() + 1), data(v.size() + 1) { build(v); }

    const T &operator[](int i) const { return at(i); }
    const T at(int k) const { return sum(k + 1) - sum(k); }

    template <class U>
    void build(const vector<U> &v) {
        int n = v.size();
        for (int i = 0; i < n; ++i) add(i, v[i]);
    }

    // v[k] += w
    void add(int k, T w) {
        assert(0 <= k && k < N);
        for (++k; k < N; k += k & -k) data[k] += w;
    }

    // v[k] = x
    void update(int k, T x) { add(k, x - at(k)); }

    // v[0] + ... + v[k - 1]
    T sum(int k) const {
        assert(0 <= k && k <= N);
        T res = 0;
        for (; k > 0; k -= k & -k) res += data[k];
        return res;
    }
    // v[a] + ... + v[b - 1]
    T sum(int a, int b) const { return sum(b) - sum(a); }

    int lower_bound(T x) const {
        if (x <= 0) return 0;
        int k = 0;
        while (k < N) k <<= 1;
        int res = 0;
        for (; k > 0; k >>= 1) {
            if (res + k < N && data[res + k] < x) x -= data[res += k];
        }
        return res;
    }
};

// clang-format on

int main(void) {
    int n;
    cin >> n;

    map<int, vector<pair<int, int>>> mp;
    rep(_, n) {
        int m;
        cin >> m;
        vector<int> x(m), y(m);
        rep(i, m) {
            cin >> x[i] >> y[i];
        }

        map<int, vector<int>> g;
        rep(i, m) {
            g[x[i]].emplace_back(y[i]);
        }

        map<int, int> f;

        for (auto [t, v] : g) {
            sort(all(v));
            rep(i, v.size() / 2) {
                int a = 0, b = 0;
                if (f[v[i * 2]]) {
                    a = -f[v[i * 2]];
                }
                if (f[v[i * 2 + 1]]) {
                    b = -f[v[i * 2 + 1]];
                }

                if (a || b) {
                    if (a)
                        b = -a;
                    else
                        a = -b;
                } else {
                    auto it = f.upper_bound(v[i * 2 + 1]);
                    if (it != f.end()) {
                        b = -(*it).second;
                        a = -b;
                    } else {
                        a = 1;
                        b = -1;
                    }
                }
                mp[t].emplace_back(v[i * 2], a);
                if (f[v[i * 2]]) {
                    f.erase(v[i * 2]);
                } else {
                    f[v[i * 2]] = a;
                }
                mp[t].emplace_back(v[i * 2 + 1], b);
                if (f[v[i * 2 + 1]]) {
                    f.erase(v[i * 2 + 1]);
                } else {
                    f[v[i * 2 + 1]] = b;
                }
            }
        }
    }
/*
    for (auto &[x, v] : mp) {
        ce("???");
        ce(x);
        for (auto p : v)
            ce(p.first, p.second);
        ce("???");
    }
*/
    int q;
    cin >> q;
    vector<tuple<int, int, int>> p(q);
    rep(i, q) {
        int x, y;
        cin >> x >> y;
        p[i] = {x, y, i};
    }
    sort(all(p));

    BIT<int> bit(100005);

    vector<int> ans(q);
    int idx = 0;
    for (auto &[x, v] : mp) {
        while (idx < q && get<0>(p[idx]) < x) {
            ans[get<2>(p[idx])] = bit.sum(get<1>(p[idx]) + 1);
            ++idx;
        }

        for (auto p : v) {
            bit.add(p.first, p.second);
        }
    }
    for (auto i : ans)
        co(i);

    return 0;
}
