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
// using ld = long double;
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
    vector<int> as(10), bs(10);
    for (auto c : a) as[c - '0']++;
    for (auto c : b) bs[c - '0']++;

    auto cs = as;
    auto ds = bs;

    rep(i, 10) {
        int m = min(cs[i], ds[9 - i]);
        cs[i] -= m;
        ds[9 - i] -= m;
    }

    bool f = false;
    FOR(s, 10, 19) {
        rep(i, s + 1) {
            if (i >= 10 || s - i >= 10)
                continue;
            f = min(cs[i], ds[s - i]) >= 1;
            if (f)
                break;
        }
        if (f)
            break;
    }

    deque<tuple<int, int, int>> ans;
    if (!f) {
        bool flg = false;
        repn(i, 9) {
            if (cs[i]) {
                FOR(j, 10 - i, 10) {
                    if (bs[j]) {
                        as[i]--;
                        bs[j]--;
                        ans.emplace_front(1, i, j);
                        flg = true;
                        break;
                    }
                }
            }
            if (flg)
                break;
        }

        if (!flg) {
            repn(i, 9) {
                repn(j, 9) {
                    if (i + j >= 10 && as[i] && bs[j]) {
                        as[i]--;
                        bs[j]--;
                        ans.emplace_front(1, i, j);
                        flg = true;
                        break;
                    }
                }
                if (flg)
                    break;
            }
        }
    }

    rep(i, 10) {
        int m = min(as[i], bs[9 - i]);
        as[i] -= m;
        bs[9 - i] -= m;
        ans.emplace_back(m, i, 9 - i);
    }
    FOR(s, 10, 19) {
        rep(i, s + 1) {
            if (i >= 10 || s - i >= 10)
                continue;
            int m = min(as[i], bs[s - i]);
            as[i] -= m;
            bs[s - i] -= m;
            ans.emplace_front(m, i, s - i);
        }
    }

    string ansA, ansB;
    for (auto [x, y, z] : ans) {
        ansA += string(x, char('0' + y));
        ansB += string(x, char('0' + z));
    }

    repnr(i, 9) {
        ansA += string(as[i], char('0' + i));
        ansB += string(bs[i], char('0' + i));
    }
    reverse(all(ansA));
    reverse(all(ansB));
    co(ansA);
    co(ansB);

    return 0;
}
