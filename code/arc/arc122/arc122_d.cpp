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

vector<int> a;

int g(int k, int l1, int r1, int l2, int r2) {
    int mask = 0, res = 0;
    repr(i, k) {
        mask += 1 << i;
        unordered_set<int> st;
        FOR (j, l2, r2) {
            st.insert(a[j] & mask);
        }

        bool f = false;
        FOR (j, l1, r1) {
            if (st.find(a[j] & mask) != st.end()) {
                f = true;
                break;
            }
        }

        if (!f) {
            mask -= 1 << i;
            res += 1 << i;
        }
    }

    return (1 << k) + res;
}

int f(int k, int l, int r) {
    if (k == -1 || l == r)
        return 0;
    // ce(k, l, r);
    int idx = l;
    while (idx != r && a[idx] >= (1 << k))
        ++idx;
    int cnt = idx - l;
    if (cnt & 1) {
        return g(k, l, idx, idx, r);
    } else {
        FOR(i, l, idx) a[i] -= 1 << k;
        return max(f(k - 1, l, idx), f(k - 1, idx, r));
    }
}

int main(void) {
    int n;
    cin >> n;
    a.resize(n * 2);
    cin >> a;
    sort(all(a));
    reverse(all(a));
    co(f(30, 0, n << 1));

    return 0;
}
