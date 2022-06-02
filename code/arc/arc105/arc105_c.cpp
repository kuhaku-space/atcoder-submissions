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

struct S {
    ll l, v;
    
    bool operator>(const S &rhs) const {
        return v > rhs.v;
    }
    bool operator<(const S &rhs) const {
        return v < rhs.v;
    }
    bool operator==(const S &rhs) const {
        return v == rhs.v;
    }

    void input() {
        cin >> l >> v;
    }


};


int main(void) {
    ll n, m;
    cin >> n >> m;
    Vec w(n);
    rep(i, n) cin >> w[i];
    ll max_w = *max_element(all(w));

    vector<S> ss(m);
    rep(i, m) ss[i].input();
    rep(i, m) {
        if(max_w > ss[i].v) {
            co(-1);
            return 0;
        }
    }

    sort(all(ss));
    Vec max_l(m);
    rep(i, m) {
        max_l[i] = ss[i].l;
        if (i) chmax(max_l[i], max_l[i - 1]);
    }

    Vec p(n);
    rep(i, n) p[i] = i;
    ll ans = LINF;
    do {
        Vec cs(n);
        rep(i, n) {
            cs[i] = w[p[i]];
            if (i) cs[i] += cs[i - 1];
        }
        // ce(cs);

        Vec q(n, 0);
        rep(i, n) {
            REP(j, i + 1, n) {
                ll pos = lower_bound(all(ss), S{0, cs[j]}) - ss.begin();
                if (pos == 0) continue;
                chmax(q[j], q[i] + max_l[pos - 1]);
            }
            REP(j, i + 1, n) cs[j] -= w[p[i]];
        }
        chmin(ans, q.back());
        // ce(ans);
    } while (next_permutation(all(p)));
    co(ans);

    return 0;
}