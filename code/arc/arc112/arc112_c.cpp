#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ld = long double;
using P = pair<ll, ll>;
using Vec = vector<ll>;
using VecP = vector<P>;
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
bool chmax(T1 &a, const T2 b) { return a < b ? a = b, true : false; }
template <class T1, class T2>
bool chmin(T1 &a, const T2 b) { return a > b ? a = b, true : false; }
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
constexpr int64_t INF = 1000000000000000001;
constexpr int64_t MOD = 1000000007;
constexpr int64_t MOD_N = 998244353;
constexpr long double EPS = 1e-11;
const double PI = acos(-1);

struct S {
    bool f;
    ll a;

    bool operator<(const S &rhs) {
        if (a < 0 && rhs.a < 0) {
            if (f != rhs.f)
                return !f;
            else
                return a < rhs.a;
        } else if (a >= 0 && rhs.a >= 0) {
            if (f != rhs.f)
                return f;
            else
                return a < rhs.a;
        } else {
            return a < 0;
        }
    }

    S &operator+=(const S &rhs) {
        if (f)
            a -= rhs.a;
        else
            a += rhs.a;
        f ^= rhs.f;
        return *this;
    }
};

int main(void) {
    ll n;
    cin >> n;
    Vec p(n - 1);
    cin >> p;
    rep(i, n - 1) p[i]--;
    Vec2<ll> c(n);
    rep(i, n - 1) c[p[i]].push_back(i + 1);

    auto dfs = [&](auto self, ll r) -> S {
        S res = S{false, 0};
        res.a++;
        vector<S> s;
        for (auto i : c[r]) {
            s.push_back(self(self, i));
        }
        sort(all(s));
        for (auto i : s) res += i;
        res.f ^= true;
        return res;
    };

    auto ans = dfs(dfs, 0);
    co((n + ans.a) / 2);

    return 0;
}