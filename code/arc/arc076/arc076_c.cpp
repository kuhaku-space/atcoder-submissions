// clang-format off
#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ld = long double;
#define FOR(i, m, n) for(int i = (m); i < (n); ++i)
#define FORR(i, m, n) for(int i = (m)-1; i >= (n); --i)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FOR(i, 1, n+1)
#define repr(i, n) FORR(i, n, 0)
#define repnr(i, n) FORR(i, n+1, 1)
#define all(s) (s).begin(), (s).end()
template <class T, class U>
bool chmax(T &a, const U b) { return a < b ? a = b, true : false; }
template <class T, class U>
bool chmin(T &a, const U b) { return b < a ? a = b, true : false; }
template <class T>
istream &operator>>(istream &is, vector<T> &v) { for (T &i : v) is>>i; return is; }
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    for (auto it=v.begin(); it!=v.end(); ++it) { os<<(it==v.begin()?"":" ")<<*it; } return os;
}
template <class Head, class... Tail>
void co(Head&& head, Tail&&... tail) {
    if constexpr(sizeof...(tail)==0) cout<<head<<'\n'; else cout<<head<<' ',co(forward<Tail>(tail)...);
}
template <class Head, class... Tail>
void ce(Head&& head, Tail&&... tail) {
    if constexpr(sizeof...(tail)==0) cerr<<head<<'\n'; else cerr<<head<<' ',ce(forward<Tail>(tail)...);
}
template<typename T, typename... Args>
auto make_vector(T x, int arg, Args ...args) {
    if constexpr(sizeof...(args)==0) return vector<T>(arg, x); else return vector(arg,make_vector<T>(x, args...));
}
void sonic() { ios::sync_with_stdio(false); cin.tie(nullptr); }
void setp(const int n) { cout << fixed << setprecision(n); }
constexpr int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
const double PI = acos(-1);

// clang-format on

int main(void) {
    int r, c, n;
    cin >> r >> c >> n;
    vector<int> x1(n), y1(n), x2(n), y2(n);

    rep(i, n) {
        cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
    }

    auto is_edge = [&](int x, int y) {
        return (x == 0 || x == r) || (y == 0 || y == c);
    };

    vector<int> idx;

    rep(i, n) {
        if (is_edge(x1[i], y1[i]) && is_edge(x2[i], y2[i]))
            idx.emplace_back(i);
    }

    if (idx.empty()) {
        puts("YES");
        return 0;
    }

    auto f = [&](int x, int y) {
        if (x == 0)
            return 0;
        if (y == c)
            return 1;
        if (x == r)
            return 2;
        return 3;
    };

    vector<vector<tuple<int, int, int>>> v(4);

    for (auto i : idx) {
        v[f(x1[i], y1[i])].emplace_back(x1[i], y1[i], i);
        v[f(x2[i], y2[i])].emplace_back(x2[i], y2[i], i);
    }

    rep(i, 4) {
        sort(all(v[i]));
        if (i >= 2) {
            reverse(all(v[i]));
        }
    }

    stack<tuple<int, int, int>> q;

    rep(i, 4) {
        for (auto t : v[i]) {
            if (q.empty()) {
                q.push(t);
            } else {
                auto s = q.top();
                if (get<2>(t) == get<2>(s))
                    q.pop();
                else
                    q.push(t);
            }
        }
    }

    bool ans = q.empty();

    if (ans)
        puts("YES");
    else
        puts("NO");

    return 0;
}
