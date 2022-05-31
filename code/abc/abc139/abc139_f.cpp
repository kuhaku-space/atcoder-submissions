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

struct Pos {
    ll x, y;

    Pos() {
        x = 0, y = 0;
    }

    void input() {
        cin >> x >> y;
    }

    void swap() {
        std::swap(x, y);
    }

    ll dist() {
        return x * x + y * y;
    }

    Pos &operator+=(const Pos &rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    bool operator<(const Pos &rhs) const {
        return atan2(x, y) < atan2(rhs.x, rhs.y);
    }
    bool operator>(const Pos &rhs) const {
        return atan2(x, y) > atan2(rhs.x, rhs.y);
    }
};


int main(void) {
    ll n;
    cin >> n;
    vector<Pos> ps(n);
    rep(i, n) ps[i].input();
    sort(all(ps));

    setp(15);

    Pos ans;
    rep(i, n) {
        Pos sum;
        rep(j, n) {
            sum += ps[(i + j) % n];
            if (ans.dist() < sum.dist()) {
                ans = sum;
            }
        }
    }

    co(sqrt((ld)ans.dist()));

    return 0;
}