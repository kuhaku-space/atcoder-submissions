#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/template/atcoder.hpp"
#pragma GCC target("avx")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
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
#line 6 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/template/atcoder.hpp"
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
    int n, m;
    cin >> n >> m;
    priority_queue<pair<int, int>> p;
    rep(i, n * 2) {
        p.push({n * 2 - i - 1, i});
    }
    vector<string> s(n * 2);
    cin >> s;
    rep(i, m) {
        priority_queue<pair<int, int>> q;
        rep(j, n) {
            auto x = p.top();
            p.pop();
            auto y = p.top();
            p.pop();
            int a, b;
            switch (s[x.second][i]) {
                case 'G':
                    a = 0;
                    break;
                case 'C':
                    a = 1;
                    break;
                case 'P':
                    a = 2;
                    break;
                default:
                    break;
            }
            switch (s[y.second][i]) {
                case 'G':
                    b = 0;
                    break;
                case 'C':
                    b = 1;
                    break;
                case 'P':
                    b = 2;
                    break;
                default:
                    break;
            }

            if ((a - b + 3) % 3 == 2) {
                q.push({x.first + n * 2, x.second});
                q.push({y.first, y.second});
            } else if ((a - b + 3) % 3 == 1) {
                q.push({x.first, x.second});
                q.push({y.first + n * 2, y.second});
            } else {
                q.push({x.first, x.second});
                q.push({y.first, y.second});
            }
        }
        p = q;
    }

    rep(i, n * 2) {
        auto a = p.top();
        p.pop();
        co(a.second + 1);
    }

    return 0;
}
