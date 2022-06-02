#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ld = long double;
using P = pair<ll, ll>;
using Pld = pair<ld, ld>;
using Vec = vector<ll>;
using VecP = vector<P>;
using VecB = vector<bool>;
using VecC = vector<char>;
using VecD = vector<ld>;
using VecS = vector<string>;
template <class T>
using Vec2 = vector<vector<T>>;
#define REP(i, m, n) for(ll i = (m); i < (n); ++i)
#define REPN(i, m, n) for(ll i = (m); i <= (n); ++i)
#define REPR(i, m, n) for(ll i = (m)-1; i >= (n); --i)
#define REPNR(i, m, n) for(ll i = (m); i >= (n); --i)
#define rep(i, n) REP(i, 0, n)
#define repn(i, n) REPN(i, 1, n)
#define repr(i, n) REPR(i, n, 0)
#define repnr(i, n) REPNR(i, n, 1)
#define all(s) (s).begin(), (s).end()
#define pb push_back
#define fs first
#define sc second
template <class T1, class T2>
bool chmax(T1 &a, const T2 b){if(a < b){a = b; return true;} return false;}
template <class T1, class T2>
bool chmin(T1 &a, const T2 b){if(a > b){a = b; return true;} return false;}
ll pow2(const int n){return (1LL << n);}
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    for (const T &i : v) os << i << ' ';
    return os;
}
void co() { cout << '\n'; }
template <class Head, class... Tail>
void co(Head&& head, Tail&&... tail) {
    cout << head << ' ';
    co(forward<Tail>(tail)...);
}
void ce() { cerr << '\n'; }
template <class Head, class... Tail>
void ce(Head&& head, Tail&&... tail) {
    cerr << head << ' ';
    ce(forward<Tail>(tail)...);
}
void sonic(){ios::sync_with_stdio(false); cin.tie(0);}
void setp(const int n){cout << fixed << setprecision(n);}
constexpr int INF = 1000000001;
constexpr ll LINF = 1000000000000000001;
constexpr ll MOD = 1000000007;
constexpr ll MOD_N = 998244353;
constexpr ld EPS = 1e-11;
const double PI = acos(-1);

int main(void) {
    ll h, w, n, m;
    cin >> h >> w >> n >> m;
    Vec a(n), b(n);
    rep(i, n) cin >> a[i] >> b[i];
    Vec c(m), d(m);
    rep(i, m) cin >> c[i] >> d[i];
    set<P> st;

    vector<map<ll, bool>> hs(h), ws(w);
    rep(i, n) --a[i], --b[i];
    rep(i, m) --c[i], --d[i];
    rep(i, m) st.insert({c[i], d[i]});
    rep(i, n) {
        hs[a[i]][b[i]] = true;
        ws[b[i]][a[i]] = true;
    }
    rep(i, m) {
        hs[c[i]][d[i]] = false;
        ws[d[i]][c[i]] = false;
    }

    ll ans = 0;
    rep(i, h) {
        rep(j, w) {
            if (st.find({i, j}) != st.end()) continue;
            auto p = hs[i].lower_bound(j);
            if (p != hs[i].end() && p->second) {
                ans++;
                continue;
            }
            if (p != hs[i].begin() && prev(p)->second) {
                ans++;
                continue;
            }
            auto q = ws[j].lower_bound(i);
            if (q != ws[j].end() && q->second) {
                ans++;
                continue;
            }
            if (q != ws[j].begin() && prev(q)->second) {
                ans++;
                continue;
            }
            // ce(i, j);
        }
    }
    co(ans);

    return 0;
}