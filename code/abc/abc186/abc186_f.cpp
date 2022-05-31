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

template <typename T>
struct BIT {
    int64_t N;
    vector<T> data;

    BIT(int64_t n) {
        init(n);
    }

    const T &operator[](const int64_t i) const {
        return at(i);
    }

    T at(int64_t k) { return sum(k + 1) - sum(k); }

    void init(int64_t n) {
        N = 1;
        while (N < n) N <<= 1;
        data.assign(N + 1, 0);
    }

    void build(vector<T> v) {
        init(N);
        for (int i = 0; i < v.size(); ++i) {
            add(i, v[i]);
        }
    }

    // v[k] += w
    void add(int64_t k, T w) {
        for (int64_t x = k + 1; x <= N; x += x & -x) {
            data[x] += w;
        }
    }

    // v[k] = x
    void update(int64_t k, T x) {
        add(k, x - at(k));
    }

    // v[0] + ... + v[k - 1]
    T sum(int64_t k) {
        T res = 0;
        for (int64_t x = k; x > 0; x -= x & -x) {
            res += data[x];
        }
        return res;
    }

    // v[a] + ... + v[b - 1]
    T sum(int64_t a, int64_t b) { return sum(b) - sum(a); }

    T lower_bound(T k) {
        int64_t l = 0, r = N;
        while (r - l > 1) {
            int64_t m = (l + r) / 2;
            if (sum(m) >= k) r = m;
            else l = m;
        }
        return r;
    }
};

int main(void) {
    ll h, w;
    cin >> h >> w;
    ll m;
    cin >> m;
    VecP ps(m);
    rep(i, m) cin >> ps[i].first >> ps[i].second;
    sort(all(ps));

    Vec my(h + 1, w + 1);
    rep(i, m) chmin(my[ps[i].first], ps[i].second);
    repn(i, h) {
        if (my[i - 1] == 1) my[i] = 1;
    }

    BIT<ll> bit(w + 1);
    set<ll> st;

    if (my[1] <= w) {
        REPN(i, my[1], w) {
            bit.add(i, 1);
            st.insert(i);
        }
    }
    ce(st.size());

    ll ans = 0;
    ll pos = 0;
    repn(i, h) {
        while (pos < m && ps[pos].first == i) {
            if (st.find(ps[pos].second) == st.end()) {
                bit.add(ps[pos].second, 1);
                st.insert(ps[pos].second);
            }
            ++pos;
        }
        ans += bit.sum(my[i], w + 1);
    }
    co(h * w - ans);

    return 0;
}