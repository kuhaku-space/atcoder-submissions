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
constexpr int64_t INF = 1000000000000000003;
constexpr int64_t MOD = 1000000007;
constexpr int64_t MOD_N = 998244353;
constexpr long double EPS = 1e-11;
const double PI = acos(-1);

template <int mod>
struct ModInt {
    int64_t x;

    ModInt() : x(0) {
    }

    ModInt(int64_t y) noexcept
        : x(y >= 0 ? y % mod : (mod - 1 - (-y - 1) % mod)) {
    }

    ModInt &operator+=(const ModInt &rhs) noexcept {
        if ((x += rhs.x) >= mod)
            x -= mod;
        return *this;
    }
    ModInt &operator-=(const ModInt &rhs) noexcept {
        if ((x += mod - rhs.x) >= mod)
            x -= mod;
        return *this;
    }
    ModInt &operator*=(const ModInt &rhs) noexcept {
        x = (int)(1LL * x * rhs.x % mod);
        return *this;
    }
    ModInt &operator/=(const ModInt &rhs) noexcept {
        *this *= rhs.inverse();
        return *this;
    }

    ModInt &operator++() noexcept {
        if ((++x) >= mod)
            x -= mod;
        return *this;
    }
    ModInt operator++(int) noexcept {
        ModInt tmp(*this);
        operator++();
        return tmp;
    }
    ModInt &operator--() noexcept {
        if ((x += mod - 1) >= mod)
            x -= mod;
        return *this;
    }
    ModInt operator--(int) noexcept {
        ModInt tmp(*this);
        operator--();
        return tmp;
    }

    ModInt operator-() const noexcept {
        return ModInt(-x);
    }
    ModInt operator+(const ModInt &rhs) const noexcept {
        return ModInt(*this) += rhs;
    }
    ModInt operator-(const ModInt &rhs) const noexcept {
        return ModInt(*this) -= rhs;
    }
    ModInt operator*(const ModInt &rhs) const noexcept {
        return ModInt(*this) *= rhs;
    }
    ModInt operator/(const ModInt &rhs) const noexcept {
        return ModInt(*this) /= rhs;
    }

    bool operator==(const ModInt &rhs) const noexcept {
        return x == rhs.x;
    }
    bool operator!=(const ModInt &rhs) const noexcept {
        return x != rhs.x;
    }

    ModInt inverse() const noexcept {
        int a = x, b = mod, u = 1, v = 0, t;
        while (b > 0) {
            t = a / b;
            swap(a -= t * b, b);
            swap(u -= t * v, v);
        }
        return ModInt(u);
    }

    ModInt pow(int64_t n) const noexcept {
        ModInt res(1), mul(x);
        for (; n > 0; n >>= 1) {
            if (n & 1)
                res *= mul;
            mul *= mul;
        }
        return res;
    }

    void pow_self(int64_t n) noexcept {
        ModInt tmp = pow(n);
        swap(*this, tmp);
    }

    friend ostream &operator<<(ostream &os, const ModInt &rhs) {
        return os << rhs.x;
    }

    friend istream &operator>>(istream &is, ModInt &rhs) {
        int64_t t;
        is >> t;
        rhs = ModInt<mod>(t);
        return (is);
    }

    int to_int() const noexcept {
        return x;
    }

    static int get_mod() noexcept {
        return mod;
    }
};
using Mint = ModInt<MOD_N>;

template <class T, class U, class F, class G, class H>
struct lazy_segment_tree {
    int N, logN;
    T e;
    U id;
    F op;    // (T, T) -> T
    G mapp;  // (U, T) -> T
    H comp;  // (U, U) -> U
    vector<T> data;
    vector<U> lazy;

    lazy_segment_tree(int _n, T _e, U _id, F _op, G _mapp, H _comp)
        : e(_e), id(_id), op(_op), mapp(_mapp), comp(_comp) {
        init(_n);
    }

    void init(int n) {
        for (N = 1, logN = 0; N < n; N <<= 1, ++logN)
            ;
        data.assign(N << 1, e);
        lazy.assign(N << 1, id);
    }

    template <class V>
    void build(const vector<V> &v) {
        for (int i = 0; i < v.size(); ++i) data[N + i] = v[i];
        for (int i = N - 1; i >= 1; --i)
            data[i] = op(data[i * 2], data[i * 2 + 1]);
    }

    void apply(int k, U x) {
        assert(k > 0 && k < N << 1);
        lazy[k] = comp(x, lazy[k]);

        if ((k >>= 1) >= 1) {
            data[k] = op(mapp(lazy[k * 2], data[k * 2]),
                         mapp(lazy[k * 2 + 1], data[k * 2 + 1]));
        }
    }

    T eval(int k) {
        assert(k > 0 && k < N << 1);
        if (lazy[k] == id)
            return data[k];
        if (k < N) {
            lazy[k * 2] = comp(lazy[k], lazy[k * 2]);
            lazy[k * 2 + 1] = comp(lazy[k], lazy[k * 2 + 1]);
        }
        data[k] = mapp(lazy[k], data[k]);
        lazy[k] = id;
        return data[k];
    }

    void update(int a, U x) {
        return add(a, a + 1, x);
    }
    void update(int a, int b, U x) {
        assert(a >= 0 && a <= N);
        assert(b >= 0 && b <= N);
        int l = a + N, r = b + N - 1;
        for (int i = logN; i >= 0; --i) eval(l >> i), eval(r >> i);
        for (a += N, b += N; a < b; a >>= 1, b >>= 1) {
            if (a & 1)
                eval(a), apply(a++, x);
            if (b & 1)
                eval(--b), apply(b, x);
        }
        for (int i = 0; i <= logN; ++i) apply(l >> i, id), apply(r >> i, id);
    }

    T query(int a, int b) {
        assert(a >= 0 && a <= N);
        assert(b >= 0 && b <= N);
        a += N, b += N;
        for (int i = logN; i >= 0; --i) eval(a >> i), eval((b - 1) >> i);
        T l = e, r = e;
        for (; a < b; a >>= 1, b >>= 1) {
            if (a & 1)
                l = op(l, eval(a++));
            if (b & 1)
                r = op(eval(--b), r);
        }
        return op(l, r);
    }
};

struct S {
    ll a, b, c;
};

int main(void) {
    ll n, q;
    cin >> n >> q;
    vector<int> a(n);
    cin >> a;

    auto op = [](S a, S b) { return S{a.a + b.a, a.b + b.b, a.c + b.c + a.a * b.b}; };
    auto mapp = [](bool f, S s) {
        return f ? S{s.b, s.a, s.a * s.b - s.c} : s;
    };
    auto comp = [](bool a, bool b) { return a ^ b; };

    lazy_segment_tree lst(n, S{0, 0, 0}, false, op, mapp, comp);
    vector<S> s(n);
    rep(i, n) {
        if (a[i])
            s[i] = S{1, 0, 0};
        else
            s[i] = S{0, 1, 0};
    }
    lst.build(s);

    rep(i, q) {
        int id;
        cin >> id;
        if (id == 2) {
            int l, r;
            cin >> l >> r;
            --l;
            auto [a, b, c] = lst.query(l, r);
            co(c);
        } else {
            int l, r;
            cin >> l >> r;
            --l;
            lst.update(l, r, true);
        }

        // rep(i, n) ce(lst.query(i, i + 1));
    }

    return 0;
}
