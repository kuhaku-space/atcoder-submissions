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
template <class T1, class T2>
bool chmax(T1 &a, const T2 b) { if (a < b) { a = b; return true; } return false; }
template <class T1, class T2>
bool chmin(T1 &a, const T2 b) { if (a > b) { a = b; return true; } return false; }
template <class T>
istream &operator>>(istream &is, vector<T> &v) { for (T &i : v) is >> i; return is; }
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) { for (const T &i : v) os << i << ' '; return os; }
void _co() { cout << '\n'; }
template <class Head, class... Tail>
void _co(Head&& head, Tail&&... tail) { cout << ' ' << head; _co(forward<Tail>(tail)...); }
template <class Head, class... Tail>
void co(Head&& head, Tail&&... tail) { cout << head; _co(forward<Tail>(tail)...); }
void ce() { cerr << '\n'; }
template <class Head, class... Tail>
void ce(Head&& head, Tail&&... tail) { cerr << head << ' '; ce(forward<Tail>(tail)...); }
void sonic() { ios::sync_with_stdio(false); cin.tie(nullptr); }
void setp(const int n) { cout << fixed << setprecision(n); }
constexpr int64_t LINF = 1000000000000000001;
constexpr int64_t MOD = 1000000007;
constexpr int64_t MOD_N = 998244353;
constexpr long double EPS = 1e-11;
const double PI = acos(-1);

template <class T>
struct BIT {
    int64_t N;
    vector<T> data;

    BIT() {}

    BIT(int64_t n) { init(n); }

    const T &operator[](int64_t i) const { return at(i); }

    const T at(int64_t k) const { return sum(k + 1) - sum(k); }

    void init() { data = vector<T>(N + 1); }

    void init(int64_t n) {
        N = 1;
        while (N < n) N <<= 1;
        data = vector<T>(N + 1);
    }

    void build(const vector<T> &v) {
        init(v.size());
        for (int i = 0; i < v.size(); ++i) {
            add(i, v[i]);
        }
    }

    // v[k] += w
    void add(int64_t k, T w) {
        for (++k; k <= N; k += k & -k) {
            data[k] += w;
        }
    }

    // v[k] = x
    void update(int64_t k, T x) { add(k, x - at(k)); }

    // v[0] + ... + v[k - 1]
    T sum(int64_t k) const {
        T res = 0;
        for (; k > 0; k -= k & -k) {
            res += data[k];
        }
        return res;
    }

    // v[a] + ... + v[b - 1]
    T sum(int64_t a, int64_t b) const { return sum(b) - sum(a); }

    int64_t lower_bound(T x) const {
        if (x <= 0) return 0;
        int64_t res = 0;
        for (int64_t k = N; k > 0; k >>= 1) {
            if (res + k <= N && data[res + k] < x) {
                x -= data[res + k];
                res += k;
            }
        }
        return res;
    }

    int64_t min_diff(ll b, ll e) const {
        ll l = b, r = e;
        while (r - l > 2) {
            // ce(l, r);
            ll m1 = (l * 2 + r) / 3;
            ll m2 = (l + r * 2) / 3;
            // ce(m1, m2);
            ll x = abs(sum(b, m1) - sum(m1, e));
            ll y = abs(sum(b, m2) - sum(m2, e));
            // ce(x, y);
            if (x < y)
                r = m2;
            else
                l = m1;
        }
        return (l + r) / 2;
    }
};

int main(void) {
    ll n;
    cin >> n;
    Vec a(n);
    cin >> a;

    BIT<ll> bit(n);
    bit.build(a);

    ll ans = LINF;
    REP(i, 2, n - 1) {
        ll x = bit.min_diff(0, i);
        ll y = bit.min_diff(i, n);
        Vec v;
        v.push_back(bit.sum(0, x));
        v.push_back(bit.sum(x, i));
        v.push_back(bit.sum(i, y));
        v.push_back(bit.sum(y, n));
        chmin(ans, *max_element(all(v)) - *min_element(all(v)));
    }
    co(ans);

    return 0;
}