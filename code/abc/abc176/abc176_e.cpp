#include <bits/stdc++.h>
using namespace std;
using ll = long long;
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
template <class T>
bool chmax(T &a, const T b){if(a < b){a = b; return true;} return false;}
template <class T>
bool chmin(T &a, const T b){if(a > b){a = b; return true;} return false;}
ll pow2(const int n){return (1LL << n);}
void co() { cout << endl; }
template <class Head, class... Tail>
void co(Head&& head, Tail&&... tail) {
    cout << head << ' ';
    co(forward<Tail>(tail)...);
}
void ce() { cerr << endl; }
template <class Head, class... Tail>
void ce(Head&& head, Tail&&... tail) {
    cerr << head << ' ';
    ce(forward<Tail>(tail)...);
}
void sonic(){ios::sync_with_stdio(false); cin.tie(0);}
void setp(const int n){cout << fixed << setprecision(n);}
constexpr int INF = 1e9+1;
constexpr ll LINF = 1e18L+1;
constexpr ll MOD = 1e9L+7;
constexpr ll MOD_N = 998244353;
constexpr ld EPS = 1e-11;
const double PI = acos(-1);

int main(void){
    ll h, w, m;
    cin >> h >> w >> m;
    set<P> st;
    Vec cnt1(h), cnt2(w);
    rep(i, m){
        ll x, y;
        cin >> x >> y;
        --x, --y;
        cnt1[x]++;
        cnt2[y]++;
        st.insert({x, y});
    }

    Vec maxh, maxw;
    ll max1 = -LINF, max2 = -LINF;
    rep(i, h) chmax(max1, cnt1[i]);
    rep(i, w) chmax(max2, cnt2[i]);
    rep(i, h){
        if (cnt1[i] == max1) maxh.push_back(i);
    }
    rep(i, w){
        if (cnt2[i] == max2) maxw.push_back(i);
    }

    if(maxh.size() * maxw.size() > m){
        co(max1 + max2);
        return 0;
    }

    for(ll i : maxh){
        for(ll j : maxw){
            if(st.find({i, j}) == st.end()){
                // ce(i, j);
                co(max1 + max2);
                return 0;
            }
        }
    }

    co(max1 + max2 - 1);
    return 0;
}
