#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
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
struct BIT {
    int64_t N;
    vector<T> data;

    BIT(int64_t n) {
        init(n);
    }

    void init(int64_t n) {
        N = 1;
        while (N <= n) N <<= 1;
        data.assign(N, 0);
    }

    void build(vector<T> v) {
        data.assign(N, 0);
        trans(0, v[0]);
        for (size_t i = 1; i < v.size(); ++i) {
            trans(i, v[i] - v[i - 1]);
        }
        trans(v.size(), -v.back());
    }

    void trans(int64_t k, T x) {
        ++k;
        while (k <= N) {
            data[k] += x;
            k += k & -k;
        }
    }

    void update(int64_t k, T x) { add(k, k + 1, x - at(k)); }

    void add(int64_t k, T x) { add(k, k + 1, x); }
    void add(int64_t a, int64_t b, T x) {
        trans(a, x);
        trans(b, -x);
    }

    T at(int64_t k) {
        ++k;
        T res = 0;
        while (k > 0) {
            res += data[k];
            k -= k & -k;
        }
        return res;
    }

    int64_t lower_bound(T x, int64_t _r) {
        int64_t l = -1, r = _r;
        while (r - l > 1) {
            int64_t m = (l + r) / 2;
            if (at(m) < x) l = m;
            else r = m;
        }
        return r;
    }
    int64_t upper_bound(T x, int64_t _r) {
        int64_t l = -1, r = _r;
        while (r - l > 1) {
            int64_t m = (l + r) / 2;
            if (at(m) > x) r = m;
            else l = m;
        }
        return r;
    }
};

int main(void) {
    ll n, l;
    cin >> n >> l;
    Vec a(n), b(n);
    rep(i, n) cin >> a[i];
    rep(i, n) cin >> b[i];
    Vec c = a;
    rep(i, n) c[i] -= i;
    c.insert(c.begin(), 1);
    c.push_back(l - n + 1);

    BIT<ll> bit(n + 2);
    bit.build(c);

    ll ans = 0;
    rep(i, n) {
        if (a[i] >= b[i]) {
            bit.add(0, n + 2, 1);
            continue;
        }
        auto t = bit.lower_bound(b[i], n + 2);
        if (bit.at(t) == b[i]) {
            ans += t - i - 1;
            while (i < n - 1 && b[i] + 1 == b[i + 1]) {
                bit.add(0, n + 2, 1);
                ++i;
            }
        } else {
            // ce("###", i, t, bit.at(5), bit.at(4));
            co(-1);
            return 0;
        }
        bit.add(0, n + 2, 1);
    }
    bit.add(0, n + 2, -1);
    ce(ans);
    repr(i, n) {
        if (a[i] <= b[i]) {
            bit.add(0, n + 2, -1);
            continue;
        }
        auto t = bit.upper_bound(b[i], n + 2);
        --t;
        if (bit.at(t) == b[i]) {
            ans += i + 1 - t;
            while (i > 0 && b[i] - 1 == b[i - 1]) {
                bit.add(0, n + 2, -1);
                --i;
            }
        } else {
            co(-1);
            return 0;
        }
        bit.add(0, n + 2, -1);
    }
    co(ans);

    return 0;
}