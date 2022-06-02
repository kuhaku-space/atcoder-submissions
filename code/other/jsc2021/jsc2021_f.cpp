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
    for (auto it=v.begin(); it!=v.end(); ++it) os<<(it==v.begin()?"":" ")<<*it; return os;
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
struct Compress {
    vector<T> data;
    Compress() {}
    Compress(const vector<T>& _data) : data(_data) { build(); }

    const T& operator[](int i) const { return data[i]; }
    T& operator[](int i) { return data[i]; }

    void add(T x) { data.emplace_back(x); }

    void build() {
        sort(data.begin(), data.end());
        data.erase(unique(data.begin(), data.end()), data.end());
    }
    void build(const vector<T>& _data) {
        data = _data;
        sort(data.begin(), data.end());
        data.erase(unique(data.begin(), data.end()), data.end());
    }
    int get(T x) {
        auto it = lower_bound(data.begin(), data.end(), x);
        assert(*it == x);
        return it - data.begin();
    }

    int size() { return data.size(); }
};

template <class T>
struct BIT {
    int N;
    vector<T> data;

    BIT() {}
    BIT(int n) { init(n); }
    BIT(const vector<T> &v) { build(v); }

    const T &operator[](int i) const { return at(i); }

    const T at(int k) const { return sum(k + 1) - sum(k); }

    void init() { data = vector<T>(N + 1); }

    void init(int n) {
        for (N = 1; N < n; N <<= 1)
            ;
        data = vector<T>(N + 1);
    }

    template <class U>
    void build(const vector<U> &v) {
        int n = v.size();
        init(n);
        for (int i = 0; i < n; ++i) add(i, v[i]);
    }

    // v[k] += w
    void add(int k, T w) {
        for (++k; k <= N; k += k & -k) data[k] += w;
    }

    // v[k] = x
    void update(int k, T x) { add(k, x - at(k)); }

    // v[0] + ... + v[k - 1]
    T sum(int k) const {
        T res = 0;
        for (; k > 0; k -= k & -k) res += data[k];
        return res;
    }

    // v[a] + ... + v[b - 1]
    T sum(int a, int b) const { return sum(b) - sum(a); }

    int lower_bound(T x) const {
        if (x <= 0) return 0;
        int res = 0;
        for (int k = N; k > 0; k >>= 1) {
            if (res + k <= N && data[res + k] < x) x -= data[res += k];
        }
        return res;
    }
};

// clang-format on

int main(void) {
    int n, m, q;
    cin >> n >> m >> q;
    Vl t(q), x(q), y(q);
    rep(i, q) cin >> t[i] >> x[i] >> y[i];

    Compress<ll> cp;
    cp.add(0);
    rep(i, q) cp.add(y[i]);
    cp.build();

    BIT<ll> b1(cp.size() + 100), b2(cp.size() + 100), b3(cp.size() + 100), b4(cp.size() + 100);
    b3.add(0, n);
    b4.add(0, m);
    Vl a(n), b(m);
    ll ans = 0;
    rep(i, q) {
        --x[i];
        if (t[i] == 1) {
            int u = cp.get(a[x[i]]);
            int v = cp.get(y[i]);
            if (a[x[i]] < y[i]) {
                ans -= b2.sum(u, v);
                ans += b4.sum(u, v) * y[i];
                ans += b4.sum(0, u) * (y[i] - a[x[i]]);
            } else if (a[x[i]] > y[i]) {
                ans += b2.sum(v, u);
                ans -= b4.sum(v, u) * a[x[i]];
                ans += b4.sum(0, v) * (y[i] - a[x[i]]);
            }
            b1.add(u, -1 * a[x[i]]);
            b1.add(v, y[i]);
            b3.add(u, -1);
            b3.add(v, 1);
            a[x[i]] = y[i];
        } else {
            int u = cp.get(b[x[i]]);
            int v = cp.get(y[i]);
            if (b[x[i]] < y[i]) {
                ans -= b1.sum(u, v);
                ans += b3.sum(u, v) * y[i];
                ans += b3.sum(0, u) * (y[i] - b[x[i]]);
            } else if (b[x[i]] > y[i]) {
                ans += b1.sum(v, u);
                ans -= b3.sum(v, u) * b[x[i]];
                ans += b3.sum(0, v) * (y[i] - b[x[i]]);
            }
            b2.add(u, -1 * b[x[i]]);
            b2.add(v, y[i]);
            b4.add(u, -1);
            b4.add(v, 1);
            b[x[i]] = y[i];
        }
        co(ans);
    }

    return 0;
}
