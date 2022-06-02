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

int main(void){
    ll n;
    cin >> n;
    Vec p(n), m(n);
    rep(i, n){
        ll x, y;
        cin >> x >> y;
        p[i] = x + y;
        m[i] = x - y;
    }
    sort(all(p));
    sort(all(m));

    co(max(p.back() - p.front(), m.back() - m.front()));

    return 0;
}
