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
    int n, k;
    cin >> n >> k;
    vector<int> a(k);
    cin >> a;

    unordered_set<int> st;
    rep(i, k) st.insert(a[i]);

    vector<int> b;
    repn(i, n) {
        if (!st.count(i))
            b.emplace_back(i);
    }

    vector<int> ans;
    auto dfs = [&](auto self, int s, int t) -> void {
        if (s == k && t == b.size()) {
        } else if (s == k) {
            ans.emplace_back(b.back());
            b.pop_back();
            self(self, s, t);
        } else if (t == b.size()) {
            ans.emplace_back(a[s]);
            self(self, s + 1, t);
        } else if (s == k - 1) {
            if (a[s] < b.back()) {
                ans.emplace_back(b.back());
                b.pop_back();
                self(self, s, t);
            } else {
                ans.emplace_back(a[s]);
                self(self, s + 1, t);
            }
        } else if (a[s] < b[t]) {
            ans.emplace_back(a[s]);
            self(self, s + 1, t);
        } else {
            ans.emplace_back(a[s]);
            ans.emplace_back(b[t]);
            self(self, s + 1, t + 1);
        }
    };

    dfs(dfs, 0, 0);
    co(ans);

    return 0;
}
