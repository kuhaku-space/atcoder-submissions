#include <bits/stdc++.h>
#include <random>
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
constexpr int64_t INF = 1000000000000000001;
constexpr int64_t MOD = 1000000007;
constexpr int64_t MOD_N = 998244353;
constexpr long double EPS = 1e-11;
const double PI = acos(-1);
constexpr uint64_t mod = (1ul << 61) - 1;
constexpr uint64_t mask30 = (1ul << 30) - 1;
constexpr uint64_t mask31 = (1ul << 31) - 1;
constexpr uint64_t base = MOD;

struct rolling_hash {
    uint64_t len;
    vector<uint64_t> data, p;

    rolling_hash(const string &_s) : data(1), p(1, 1), len(_s.size() + 1) {
        uint64_t x = 0, t = 1;
        for (const auto c : _s) {
            x = _mod(_mul(x, base) + c);
            data.emplace_back(x);
            t = _mod(_mul(t, base));
            p.emplace_back(t);
        }
    }

    uint64_t _mul(uint64_t a, uint64_t b) {
        uint64_t au = a >> 31, ad = a & mask31;
        uint64_t bu = b >> 31, bd = b & mask31;
        uint64_t mid = ad * bu + au * bd;
        uint64_t midu = mid >> 30, midd = mid & mask30;
        return au * bu * 2 + midu + (midd << 31) + ad * bd;
    }

    uint64_t _mod(uint64_t x) {
        uint64_t xu = x >> 61, xd = x & mod;
        uint64_t res = xu + xd;
        if (res >= mod) res -= mod;
        return res;
    }

    uint64_t _pow(uint64_t x, uint64_t k) {
        uint64_t res = 1;
        for (; k; k >>= 1) {
            if (k & 1) res = _mod(_mul(res, x));
            x = _mod(_mul(x, x));
        }
        return res;
    }

    uint64_t get(int l, int r) {
        return _mod(data[r] + mod * 4 - _mul(data[l], p[r - l]));
    }

    vector<int> search(const string &s) {
        vector<int> res;
        int n = s.size();
        if (n >= len) return res;
        uint64_t x = 0;
        for (const auto c : s) x = _mod(_mul(x, base) + c);
        for (int i = n; i < len; ++i) {
            if (_mod(data[i] + mod * 4 - _mul(data[i - n], p[n])) == x)
                res.emplace_back(i - n);
            x = _mod(_mul(x, base));
        }
        return res;
    }

    bool search(ll n) {
        set<uint64_t> st;
        queue<uint64_t> que;
        for (int i = n; i < len; ++i) {
            auto x = get(i - n, i);
            if (st.find(x) != st.end())
                return true;
            que.push(x);
            if (que.size() == n) {
                st.insert(que.front());
                que.pop();
            }
        }
        return false;
    }
};

int main(void) {
    ll n;
    cin >> n;
    string s;
    cin >> s;
    rolling_hash rh(s);

    ll l = 0, r = n + 1;
    while ((r - l) > 1) {
        ll m = (l + r) / 2;
        if (rh.search(m))
            l = m;
        else
            r = m;
    }
    co(l);

    return 0;
}