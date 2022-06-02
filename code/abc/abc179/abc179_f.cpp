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

template <typename T>
struct lasy_segment_tree{
    using F = function<T(T, T)>;
    ll N;
    T d;
    F f;
    vector<T> data;
    vector<T> lazy;

    lasy_segment_tree(ll _n, T _d, F _f) : f(_f), d(_d){
        init(_n);
    }

    void init(ll n){
        N = 1;
        while(N < n) N <<= 1;
        data.assign(N*2, d);
        lazy.assign(N*2, 0);
    }

    void build(vector<T> v){
        for (int i = 0; i < v.size(); ++i) data[N + i] = v[i];
        for (int i = N - 1; i >= 1; --i) data[i] = f(data[i * 2], data[i * 2 + 1]);
    }

    void eval(ll k){
        if (lazy[k] == 0) return;
        if (k < N) {
            lazy[k * 2] += lazy[k];
            lazy[k * 2 + 1] += lazy[k];
        }
        data[k] += lazy[k];
        lazy[k] = 0;
    }

    T add(ll a, T x){
        return add(a, a + 1, x, 1, 0, N);
    }
    T add(ll a, ll b, T x){
        return add(a, b, x, 1, 0, N);
    }
    T add(ll a, ll b, T x, ll k, ll l, ll r){
        eval(k);
        if(r <= a || b <= l) return data[k];
        if(a <= l && r <= b){
            lazy[k] += x;
            return data[k] + lazy[k];
        }
        ll m = (l + r) / 2;
        return data[k] =
                   f(add(a, b, x, k * 2, l, m), add(a, b, x, k * 2 + 1, m, r));
    }

    T query(ll a, ll b){
        return query(a, b, 1, 0, N);
    }
    T query(ll a, ll b, ll k, ll l, ll r){
        eval(k);
        if(r <= a || b <= l) return d;
        if(a <= l && r <= b) return data[k];
        ll m = (l + r) / 2;
        return f(query(a, b, k * 2, l, m), query(a, b, k * 2 + 1, m, r));
    }

};

int main(void) {
    ll n, q;
    cin >> n >> q;

    lasy_segment_tree<ll> lst_x(n, LINF, [](ll a, ll b){return min(a, b);});
    lasy_segment_tree<ll> lst_y(n, LINF, [](ll a, ll b){return min(a, b);});
    Vec a(n, n - 2);
    lst_x.build(a);
    lst_y.build(a);

    ll ans = (n - 2) * (n - 2);
    while(q--){
        ll x, y;
        cin >> x >> y;
        y -= 2;
        if(x == 1){
            ll t = lst_x.query(y, y + 1);
            ans -= t;
            if(lst_y.query(0, 1) > y){
                lst_y.add(0, t, -(lst_y.query(0, 1) - y));
            }
        }else{
            ll t = lst_y.query(y, y + 1);
            ans -= t;
            if(lst_x.query(0, 1) > y){
                lst_x.add(0, t, -(lst_x.query(0, 1) - y));
            }
        }
        ce(ans);
    }
    co(ans);

    return 0;
}