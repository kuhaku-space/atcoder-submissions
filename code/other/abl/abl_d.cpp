#include <bits/stdc++.h>
using namespace std;
using ll = long long;
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

template <class T>
struct segment_tree {
    using F = function<T(T, T)>;
    int64_t N;
    T d;
    F f;
    vector<T> data;

    segment_tree(int64_t _n, T _d, F _f) : f(_f), d(_d) {
        init(_n);
    }

    void init(int64_t n) {
        N = 1;
        while (N < n) N <<= 1;
        data.assign(N * 2, d);
    }

    void build(vector<T> v) {
        for (size_t i = 0; i < v.size(); ++i) data[N + i] = v[i];
        for (size_t i = N - 1; i >= 1; --i) data[i] = f(data[i * 2], data[i * 2 + 1]);
    }

    T at(int64_t k) {
        k += N;
        return data[k];
    }

    void update(int64_t k, const T x) {
        k += N;
        data[k] = x;
        while (k > 1) {
            k >>= 1;
            data[k] = f(data[k * 2], data[k * 2 + 1]);
        }
    }

    void add(int64_t k, const T x) {
        k += N;
        data[k] += x;
        while(k > 1){
            k >>= 1;
            data[k] = f(data[k * 2], data[k * 2 + 1]);
        }
    }

    T query(int64_t a, int64_t b) {
        T res = d;
        for (a += N, b += N; a < b; a >>= 1, b >>= 1) {
            if (a & 1) res = f(res, data[a++]);
            if (b & 1) res = f(res, data[--b]);
        }
        return res;
    }
};

int main(void) {
    ll n, k;
    cin >> n >> k;
    Vec a(n);
    rep(i, n) cin >> a[i];

    segment_tree<ll> st(300001, 0, [](ll a, ll b) { return max(a, b); });
    rep(i, n) st.update(
        a[i], st.query(max(a[i] - k, 0LL), min(a[i] + k + 1, 300001LL)) + 1);

    co(st.query(0, 300001));

    return 0;
}