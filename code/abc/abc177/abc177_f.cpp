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
void co() { cout << endl; }
template <class Head, class... Tail>
void co(Head&& head, Tail&&... tail) {
    cout << head << ' ';
    co(forward<Tail>(tail)...);
}
void ce() { cerr << endl; }
template <class Head, class... Tail>
void ce(Head&& head, Tail&&... tail) {
    cerr << head << ' ';
    ce(forward<Tail>(tail)...);
}
void sonic(){ios::sync_with_stdio(false); cin.tie(0);}
void setp(const int n){cout << fixed << setprecision(n);}
constexpr int INF = 1e9+1;
constexpr ll LINF = 1e18L+1;
constexpr ll MOD = 1e9L+7;
constexpr ll MOD_N = 998244353;
constexpr ld EPS = 1e-11;
const double PI = acos(-1);

template <class T>
struct segment_tree{
    using F = function<T(T, T)>;
    ll N;
    T d;
    F f;
    vector<T> data;

    segment_tree(ll _n, T _d, F _f) : f(_f), d(_d) {
        init(_n);
    }

    void init(ll n) {
        N = 1;
        while(N < n) N <<= 1;
        data.assign(N * 2, d);
    }

    void build(vector<T> v) {
        for (int i = 0; i < v.size(); ++i) data[N + i] = v[i];
        for (int i = N - 1; i >= 1; --i) data[i] = f(data[i * 2], data[i * 2 + 1]);
    }

    T at(ll k) {
        k += N;
        return data[k];
    }

    void update_min(ll k, const T x) {
        k += N;
        chmin(data[k], x);
        while(k > 1){
            k >>= 1;
            data[k] = f(data[k * 2], data[k * 2 + 1]);
        }
    }

    void update(ll k, const T x) {
        k += N;
        data[k] = x;
        while(k > 1){
            k >>= 1;
            data[k] = f(data[k * 2], data[k * 2 + 1]);
        }
    }

    void add(ll k, const T x) {
        k += N;
        data[k] += x;
        while(k > 1){
            k >>= 1;
            data[k] = f(data[k * 2], data[k * 2 + 1]);
        }
    }

    T query(ll a, ll b) {
        T res = d;
        for (a += N, b += N; a < b; a >>= 1, b >>= 1){
            if (a & 1) res = f(res, data[a++]);
            if (b & 1) res = f(res, data[--b]);
        }
        return res;
    }
};

int main(void){
    ll h, w;
    cin >> h >> w;
    Vec a(h), b(h);
    rep(i, h) cin >> a[i] >> b[i];
    rep(i, h) --a[i], --b[i];
    map<ll, ll> mp;
    set<ll> st;
    rep(i, w) st.insert(i);
    segment_tree<ll> seg(w + 1, LINF, [](ll a, ll b) { return min(a, b); });
    rep(i, w) seg.update(i, 0);

    rep(i, h){
        auto it1 = st.lower_bound(a[i]);
        auto it2 = st.upper_bound(b[i]);
        for (auto it = it1; it != it2; ++it){
            seg.update_min(b[i] + 1, seg.at(*it) + b[i] + 1 - *it);
            seg.update(*it, LINF);
        }
        st.erase(it1, it2);
        st.insert(b[i] + 1);
        ll ans = seg.query(0, w) + i + 1;
        if (ans >= LINF) ans = -1;
        co(ans);
    }

    return 0;
}
