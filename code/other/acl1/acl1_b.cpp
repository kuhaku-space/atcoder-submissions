#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
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

vector<ll> prime_number;

void init_prime(){
    if (!prime_number.empty()) return;
    int sz = 5e7;
    vector<bool> memo(sz, true);
    memo[0] = memo[1] = false;
    for (int i = 0; i < sz; ++i) {
        if (memo[i]) {
            prime_number.push_back(i);
            for (int j = 2; i * j < sz; ++j) {
                memo[i * j] = false;
            }
        }
    }
}

bool is_prime(ll n){
    if(n == 1) return false;
    init_prime();
    for(ll i : prime_number){
        if (i * i > n) break;
        if (n % i == 0) return false;
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
    if (n != 1) res.push_back({n, 1});

    return res;
}

Vec divisor_enumeration(ll n){
    auto v = prime_factorization(n);

    Vec res, a, b, cp;
    res.push_back(1);
    for(auto p : v){
        cp.resize(res.size());
        copy(res.begin(), res.end(), cp.begin());
        a.resize(res.size());
        for(int k = 1; k <= p.second; ++k){
            ll t = pow(p.first, k);
            for(int i = 0; i < a.size(); ++i) a[i] = cp[i] * t;
            merge(res.begin(), res.end(), a.begin(), a.end(), back_inserter(b));
            swap(res, b);
            b.clear();
        }
    }

    return res;
}

int main(void) {
    ll n;
    cin >> n;
    auto v = divisor_enumeration(n * 2);
    vector<ll> r(2), m(2);
    r[0] = 0, r[1] = -1;
    ll ans = LINF;
    for(ll i : v){
        if (i == 1) continue;
        m[0] = n * 2 / i;
        m[1] = i;
        auto p = crt(r, m);
        if (p.first == 0 && p.second == 0) continue;
        // ce(p.first, p.second);
        chmin(ans, p.first);
    }
    co(ans);

    return 0;
}
