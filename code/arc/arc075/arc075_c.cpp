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
    int n, k;
    cin >> n >> k;
    vector<ll> a(n);
    cin >> a;
    rep(i, n) a[i] -= k;
    a.emplace_back(0);
    repr(i, n) a[i] += a[i + 1];

    vector<pair<ll, ll>> v(n + 1);
    rep(i, n + 1) v[i] = {a[i], -i};
    sort(all(v));
    reverse(all(v));

    BIT<int> bit(n + 1);
    ll ans = 0;
    rep(i, n + 1) {
        auto [x, y] = v[i];
        y *= -1;
        ans += bit.sum(y);
        bit.add(y, 1);
    }
    co(ans);

    return 0;
}
