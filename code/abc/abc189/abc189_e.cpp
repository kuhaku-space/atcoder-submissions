#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ld = long double;
using P = pair<ll, ll>;
using Vec = vector<ll>;
using VecP = vector<P>;
template <class T>
using Vec2 = vector<vector<T>>;
#define REP(i, m, n) for (ll i = (m); i < (n); ++i)
#define REPN(i, m, n) for (ll i = (m); i <= (n); ++i)
#define REPR(i, m, n) for (ll i = (m)-1; i >= (n); --i)
#define REPNR(i, m, n) for (ll i = (m); i >= (n); --i)
#define rep(i, n) REP(i, 0, n)
#define repn(i, n) REPN(i, 1, n)
#define repr(i, n) REPR(i, n, 0)
#define repnr(i, n) REPNR(i, n, 1)
#define all(s) (s).begin(), (s).end()
template <class T1, class T2>
bool chmax(T1 &a, const T2 b) {
    return a < b ? a = b, true : false;
}
template <class T1, class T2>
bool chmin(T1 &a, const T2 b) {
    return a > b ? a = b, true : false;
}
template <class T>
istream &operator>>(istream &is, vector<T> &v) {
    for (T &i : v) is >> i;
    return is;
}
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    for (const T &i : v) os << i << ' ';
    return os;
}
void _co() {
    cout << '\n';
}
template <class Head, class... Tail>
void _co(Head &&head, Tail &&...tail) {
    cout << ' ' << head;
    _co(forward<Tail>(tail)...);
}
template <class Head, class... Tail>
void co(Head &&head, Tail &&...tail) {
    cout << head;
    _co(forward<Tail>(tail)...);
}
void ce() {
    cerr << '\n';
}
template <class Head, class... Tail>
void ce(Head &&head, Tail &&...tail) {
    cerr << head << ' ';
    ce(forward<Tail>(tail)...);
}
void sonic() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}
void setp(const int n) {
    cout << fixed << setprecision(n);
}
constexpr int64_t LINF = 1000000000000000001;
constexpr int64_t MOD = 1000000007;
constexpr int64_t MOD_N = 998244353;
constexpr long double EPS = 1e-11;
const double PI = acos(-1);

struct S {
    ll p, a, b;

    bool operator<(const S &rhs) const {
        return a < rhs.a;
    }
};

struct T {
    ll a, b, c, d, e, f;

    T() : a(1), b(0), c(0), d(1), e(0), f(0) {
    }

    ll get_x(ll x, ll y) const {
        return a * x + b * y + e;
    }

    ll get_y(ll x, ll y) const {
        return c * x + d * y + f;
    }

    void query(ll p, ll q) {
        T t = *this;
        if (p == 1) {
            swap(a, c);
            swap(b, d);
            swap(e, f);
            c *= -1;
            d *= -1;
            f *= -1;
        } else if (p == 2) {
            a = -t.c;
            b = -t.d;
            e = -t.f;
            c = t.a;
            d = t.b;
            f = t.e;
        } else if (p == 3) {
            a *= -1;
            b *= -1;
            e *= -1;
            e += q * 2;
        } else {
            c *= -1;
            d *= -1;
            f *= -1;
            f += q * 2;
        }
    }
};

struct A {
    ll x, y;

    friend A &operator*=(A &lhs, const T &rhs) {
        ll tx = lhs.x, ty = lhs.y;
        lhs.x = rhs.get_x(tx, ty);
        lhs.y = rhs.get_y(tx, ty);
        return lhs;
    }
};

int main(void) {
    ll n;
    cin >> n;
    Vec x(n), y(n);
    rep(i, n) cin >> x[i] >> y[i];

    ll m;
    cin >> m;
    Vec op(m), p(m);
    rep(i, m) {
        cin >> op[i];
        if (op[i] >= 3)
            cin >> p[i];
    }

    ll q;
    cin >> q;
    Vec a(q), b(q);
    rep(i, q) cin >> a[i] >> b[i];
    vector<S> s(q);
    rep(i, q) s[i] = S{i, a[i], b[i]};
    sort(all(s));

    vector<A> ans(q);
    rep(i, q) ans[i] = A{x[b[i] - 1], y[b[i] - 1]};

    ll c = 0;
    T t;
    rep(i, m + 1) {
        while (c < q && s[c].a == i) {
            ans[s[c++].p] *= t;
        }

        if (i == m)
            break;
        t.query(op[i], p[i]);
        // ce(t.a, t.b, t.c, t.d, t.e, t.f);
    }

    rep(i, q) co(ans[i].x, ans[i].y);

    return 0;
}