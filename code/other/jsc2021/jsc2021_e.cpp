// clang-format off
#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ld = long double;
using Pi = pair<int, int>;
using Pl = pair<ll, ll>;
using Vi = vector<int>;
using Vl = vector<ll>;
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
    int k;
    cin >> k;
    string s;
    cin >> s;
    int n = s.size();

    if (k == 0) {
        string t = s;
        reverse(all(t));
        if (s.size() == 1) {
            co("impossible");
        } else if (s.empty() || s != t) {
            co(0);
        } else
            co(1);
        return 0;
    }

    if (k != 0) {
        rep(i, k - 1) n >>= 1;
        if (n == 0 || n == 2 || n == 3) {
            co("impossible");
            return 0;
        }
    }

    n = s.size();
    int x = s.size();
    Vi id(n);
    iota(all(id), 0);
    int ans = 0;
    rep(_, k) {
        unordered_map<char, int> ump;
        int cnt = 0;
        rep(i, n) {
            if ((x & 1) && id[i] == x / 2) {
                ++ump[s[i]];
                id[i] = -1;
                ++cnt;
            } else if (id[i] >= x / 2) {
                id[i] = x - 1 - id[i];
            }
        }

        if (x & 1) {
            int max = 0;
            for (auto p : ump) chmax(max, p.second);
            ans += cnt - max;
        }
        x >>= 1;
    }

    int a = Inf;
    string st;
    vector<unordered_map<char, int>> ump(x);
    Vi cnt(x);
    rep(i, n) {
        if (id[i] != -1) {
            ++ump[id[i]][s[i]];
            ++cnt[id[i]];
        }
    }

    rep(i, x) {
        int max = 0, b = 0;
        char c;
        for (auto p : ump[i]) {
            chmax(b, p.second);
            if (max < b) {
                swap(max, b);
                c = p.first;
            }
        }

        ans += cnt[i] - max;
        if (!(x & 1) || i != x / 2) {
            chmin(a, max - b);
        }
        st += c;
    }

    // ce(st);
    string ts = st;
    reverse(all(ts));
    if (!st.empty() && st == ts) {
        ans += a;
    }

    co(ans);

    return 0;
}
