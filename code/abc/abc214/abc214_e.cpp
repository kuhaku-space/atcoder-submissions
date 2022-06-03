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

void solve() {
    int n;
    cin >> n;
    vector<int> l(n), r(n);
    rep(i, n) {
        cin >> l[i] >> r[i];
    }

    set<int> st;
    rep(i, n) {
        st.insert(l[i]);
        st.insert(r[i]);
    }

    map<int, vector<int>> mp;
    rep(i, n) mp[l[i]].emplace_back(r[i]);

    priority_queue<int, vector<int>, greater<>> que;
    int t = *min_element(all(l)) - 1;
    for (auto x : st) {
        rep(i, x - t - 1) {
            if (que.empty())
                break;
            que.pop();
        }

        if (mp.count(x)) {
            for (auto y : mp[x])
                que.push(y);
        }

        if (que.size())
            que.pop();

        if (que.size() && que.top() <= x) {
            puts("No");
            return;
        }
        t = x;
    }

    puts("Yes");
    return;
}

int main(void) {
    int t;
    cin >> t;
    rep(_, t) solve();

    return 0;
}
