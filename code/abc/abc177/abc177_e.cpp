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
template <class T1, class T2>
bool chmax(T1 &a, const T2 b){if(a < b){a = b; return true;} return false;}
template <class T1, class T2>
bool chmin(T1 &a, const T2 b){if(a > b){a = b; return true;} return false;}
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

ll gcd(ll a, ll b){
    if(!b) return a;
    return gcd(b, a%b);
}

vector<ll> prime_number;

void init_prime(){
    if (!prime_number.empty()) return;
    int sz = 5e6 + 500;
    vector<bool> memo(sz, true);
    memo[0] = memo[1] = false;
    for (int i = 0; i < sz; ++i){
        if(memo[i]){
            prime_number.push_back(i);
            for (int j = 2; i * j < sz; ++j){
                memo[i * j] = false;
            }
        }
    }
}

bool is_prime(ll n){
    if(n == 1) return false;
    init_prime();
    for(ll i : prime_number){
        if(i * i > n) return true;
        if(n % i == 0) return false;
    }
    return true;
}

vector<P> prime_factorization(ll n){
    vector<P> res;

    init_prime();
    for (ll i : prime_number) {
        ll cnt = 0;
        while (n % i == 0) {
            n /= i;
            cnt++;
        }
        if (cnt) res.push_back({i, cnt});
        if (n < i * i) break;
    }
    if(n != 1) res.push_back({n, 1});

    return res;
}

int main(void){
    ll n;
    cin >> n;
    Vec a(n);
    rep(i, n) cin >> a[i];

    ll g = a[0];
    rep(i, n) g = gcd(g, a[i]);

    bitset<1000005> used;
    bool flg = true;
    rep(i, n){
        if (a[i] == 1) continue;
        auto v = prime_factorization(a[i]);
        for(P p : v){
            if(used[p.first]){
                flg = false;
            }
            used.set(p.first);
        }
        if (!flg) break;
    }
    if (flg) puts("pairwise coprime");
    else if(g == 1)
        puts("setwise coprime");
    else
        puts("not coprime");

    return 0;
}
