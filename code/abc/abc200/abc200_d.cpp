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
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;

    rep(i, n) a[i] %= 200;

    auto it = min_element(all(a));
    if (*it == 0) {
        if (a.size() == 1) {
            co("No");
        } else {
            int x = it - a.begin() + 1;
            int y = x == 1 ? 2 : 1;
            co("Yes");
            co(1, y);
            co(2, min(x, y), max(x, y));
        }
        return 0;
    }

    vector<vector<int>> dp0(200), dp1(200);

    rep(i, n) {
        auto dp2 = dp0, dp3 = dp1;
        rep(j, 200) {
            if (!dp0[j].empty()) {
                int k = (j + a[i]) % 200;
                if (dp2[k].empty()) {
                    dp2[k] = dp0[j];
                    dp2[k].emplace_back(i);
                }
                k = (j - a[i] + 200) % 200;
                if (dp3[k].empty()) {
                    dp3[k] = dp0[j];
                    dp3[k].emplace_back(~i);
                }
            } else if (!dp1[j].empty()) {
                int k = (j + a[i]) % 200;
                if (dp3[k].empty()) {
                    dp3[k] = dp1[j];
                    dp3[k].emplace_back(i);
                }
                k = (j - a[i] + 200) % 200;
                if (dp3[k].empty()) {
                    dp3[k] = dp1[j];
                    dp3[k].emplace_back(~i);
                }
            }
        }
        if (dp2[a[i]].empty())
            dp2[a[i]].emplace_back(i);
        dp0 = dp2, dp1 = dp3;
    }

    if (!dp1[0].empty()) {
        vector<int> a, b;
        for (auto i : dp1[0]) {
            if (i >= 0)
                a.emplace_back(i + 1);
            else
                b.emplace_back(~i + 1);
        }
        puts("Yes");
        co(a.size(), a);
        co(b.size(), b);
    } else if (!dp0[0].empty() && dp0[0].size() != n) {
        set<int> st;
        for (auto i : dp0[0])
            st.insert(i);

        int x = 0;
        rep(i, n) {
            if (!st.count(i)) {
                x = i;
                break;
            }
        }
        st.insert(x);
        vector<int> a;
        for (auto i : st)
            a.emplace_back(i + 1);
        puts("Yes");
        co(1, x + 1);
        co(a.size(), a);
    } else {
        puts("No");
    }

    return 0;
}
