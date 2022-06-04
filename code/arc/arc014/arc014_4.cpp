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

// clang-format on

int main(void) {
    int all, n, m;
    cin >> all >> n >> m;
    vector<int> l(n);
    cin >> l;
    sort(all(l));
    vector<int> x(m), y(m);
    rep(i, m) cin >> x[i] >> y[i];

    Compress<ll> com;
    rep(i, n - 1) com.add(l[i + 1] - l[i] - 1);
    rep(i, m) com.add(x[i] + y[i]);

    BIT<ll> b(com.size()), c(com.size());
    com.build();

    rep(i, n - 1) {
        int d = l[i + 1] - l[i] - 1;
        b.add(com.get(d), 1);
        c.add(com.get(d), d);
    }

    rep(i, m) {
        // ce(c.sum(com.get(x[i] + y[i])), b.sum(com.get(x[i] + y[i])));
        int f = l[0] - max(l[0] - x[i], 1);
        int g = min(l[n - 1] + y[i], all) - l[n - 1];
        co(c.sum(com.get(x[i] + y[i])) + (n - 1 - b.sum(com.get(x[i] + y[i]))) * (x[i] + y[i]) + f + g + n);
    }

    return 0;
}
