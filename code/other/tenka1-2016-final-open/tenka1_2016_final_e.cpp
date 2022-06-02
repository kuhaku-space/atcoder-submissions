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

template <class T, class F>
struct CHT {
    vector<pair<T, T>> lines;
    F comp;
    int head;
    CHT(T _e, F _comp) : comp(_comp), head(0) {
        lines.emplace_back(0, _e);
    };

    bool check(pair<T, T> l1, pair<T, T> l2, pair<T, T> l3) {
        if (l1 < l3)
            swap(l1, l3);
        return (l3.second - l2.second) * (l2.first - l1.first) >=
               (l2.second - l1.second) * (l3.first - l2.first);
    }

    void add(T a, T b) {
        pair<T, T> line(a, b);
        while (lines.size() >= 2 &&
               check(*(lines.end() - 2), lines.back(), line))
            lines.pop_back();
        lines.emplace_back(line);
    }

    T f(int i, T x) {
        return lines[i].first * x + lines[i].second;
    }
    T f(pair<T, T> line, T x) {
        return line.first * x + line.second;
    }

    T get(T x) {
        while(lines.size() >= 2 + head && comp(f(head, x), f(head + 1, x))){
            head++;
        }
        return f(head, x);
        // int low = -1, high = lines.size() - 1;
        // while (high - low > 1) {
        //     int mid = (high + low) / 2;
        //     if(comp(f(mid, x), f(mid + 1, x)))
        //         low = mid;
        //     else
        //         high = mid;
        // }
        // return f(high, x);
    }
};

int main(void) {
    ll n, l;
    cin >> n >> l;
    Vec sum(l);
    rep(i, n) {
        CHT cht(ll(11e11), [](ll l, ll r) { return l >= r; });
        Vec a(l);
        cin >> a;
        rep(j, l) cht.add(-j * 2, a[j] + j * j);
        rep(j, l) sum[j] += cht.get(j) + j * j;
    }
    co(*min_element(all(sum)));

    return 0;
}