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
    sonic();
    string a, b;
    cin >> a >> b;

    vector<int> idx;
    int n = a.size();
    rep(i, n) {
        if (a[i] != b[i])
            idx.emplace_back(i);
    }

    if (idx.size() > 6 || idx.size() == 1) {
        co("NO");
        return 0;
    }

    unordered_map<char, int> mp;
    rep(i, n) {
        mp[a[i]]++;
    }

    bool dbl = false;
    for (auto p : mp) dbl |= p.second >= 2;

    auto same = [&]() {
        for (auto i : idx) {
            if (a[i] != b[i])
                return false;
        }
        return true;
    };

    int sz = idx.size();
    auto dfs = [&](auto &&self, int cnt) {
        if (cnt == 0) {
            return same();
        } else if (same()) {
            return cnt == 2 || dbl;
        }
        rep(i, sz) {
            FOR(j, i + 1, sz) {
                swap(b[idx[i]], b[idx[j]]);
                if (self(self, cnt - 1))
                    return true;
                swap(b[idx[i]], b[idx[j]]);
            }
        }
        return false;
    };

    if (dfs(dfs, 3))
        co("YES");
    else
        co("NO");

    return 0;
}
