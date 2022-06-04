#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/template/template.hpp"
#include <bits/stdc++.h>
using namespace std;
template <class T, class U>
bool chmax(T &a, const U &b) {
    return a < b ? a = b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U &b) {
    return b < a ? a = b, true : false;
}
constexpr int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
const double PI = acos(-1.0);
#line 3 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/template/atcoder.hpp"
using ll = int64_t;
using ld = long double;
#define FOR(i, m, n) for(int i = (m); i < (n); ++i)
#define FORR(i, m, n) for(int i = (m)-1; i >= (n); --i)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FOR(i, 1, n+1)
#define repr(i, n) FORR(i, n, 0)
#define repnr(i, n) FORR(i, n+1, 1)
#define all(s) (s).begin(), (s).end()
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
#line 3 "a.cpp"

int main(void) {
    setp(20);
    int n, d;
    cin >> n >> d;
    int x, y;
    cin >> x >> y;
    if (x % d || y % d) {
        co(0);
        return 0;
    }

    x /= d;
    y /= d;

    int s = abs(x) + abs(y);
    if (s > n || (n - s) % 2) {
        co(0);
        return 0;
    }

    ld ans = 0;
    rep(i, n - s + 1) {
        if (i & 1)
            continue;
        ld t = 1;
        stack<int> st;
        rep(i, n) st.push(4);
        rep(j, i / 2) st.push(j + 1);
        rep(j, i / 2 + abs(x)) st.push(j + 1);
        rep(j, (n - s - i) / 2) st.push(j + 1);
        rep(j, (n - s - i) / 2 + abs(y)) st.push(j + 1);
        rep(j, n) {
            t *= j + 1;
            while (st.size() && t > 1) {
                t /= st.top();
                st.pop();
            }
        }
        while (st.size()) {
            t /= st.top();
            st.pop();
        }
        ans += t;
    }
    co(ans);

    return 0;
}
