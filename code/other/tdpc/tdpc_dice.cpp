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

template <int mod>
struct ModInt {
    int x;

    ModInt() : x(0) {}

    ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}

    ModInt &operator+=(const ModInt &p) {
        if((x += p.x) >= mod) x -= mod;
        return *this;
    }

    ModInt &operator-=(const ModInt &p) {
        if((x += mod - p.x) >= mod) x -= mod;
        return *this;
    }

    ModInt &operator*=(const ModInt &p) {
        x = (int) (1LL * x * p.x % mod);
        return *this;
    }

    ModInt &operator/=(const ModInt &p) {
        *this *= p.inverse();
        return *this;
    }

    ModInt &operator++() {
        if((++x) >= mod) x -= mod;
        return *this;
    }

    ModInt operator++(int) {
        ModInt tmp(*this);
        operator++();
        return tmp;
    }

    ModInt &operator--() {
        if((x += mod - 1) >= mod) x -= mod;
        return *this;
    }

    ModInt operator--(int) {
        ModInt tmp(*this);
        operator--();
        return tmp;
    }

    ModInt operator-() const { return ModInt(-x); }

    ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }

    ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }

    ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }

    ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }

    bool operator==(const ModInt &p) const { return x == p.x; }

    bool operator!=(const ModInt &p) const { return x != p.x; }

    ModInt inverse() const {
        int a = x, b = mod, u = 1, v = 0, t;
        while(b > 0) {
            t = a / b;
            swap(a -= t * b, b);
            swap(u -= t * v, v);
        }
        return ModInt(u);
    }

    ModInt pow(int64_t n) const {
        ModInt res(1), mul(x);
        while(n > 0) {
            if(n & 1) res *= mul;
            mul *= mul;
            n >>= 1;
        }
        return res;
    }

    friend ostream &operator<<(ostream &os, const ModInt &p) {
        return os << p.x;
    }

    friend istream &operator>>(istream &is, ModInt &a) {
        int64_t t;
        is >> t;
        a = ModInt< mod >(t);
        return (is);
    }

    static int get_mod() { return mod; }
};
using Mint = ModInt<MOD>;

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
    ll n, d;
    cin >> n >> d;
    vector<vector<vector<long double>>> cur(60, Vec2<long double>(40, VecD(30)));
    auto nxt = cur;
    cur[0][0][0] = 1;

    rep(_, n){
        rep(i, 60) rep(j, 40) nxt[i][j].assign(30, 0);
        rep(i, 60){
            rep(j, 40){
                rep(k, 30){
                    nxt[i][j][k] += cur[i][j][k] / 6;
                    nxt[min(59LL, i + 1)][j][k] += cur[i][j][k] / 6;
                    nxt[i][min(39LL, j + 1)][k] += cur[i][j][k] / 6;
                    nxt[min(59LL, i + 2)][j][k] += cur[i][j][k] / 6;
                    nxt[i][j][min(29LL, k + 1)] += cur[i][j][k] / 6;
                    nxt[min(59LL, i + 1)][min(39LL, j + 1)][k] += cur[i][j][k] / 6;
                }
            }
        }
        swap(cur, nxt);
    }

    setp(10);
    auto ps = prime_factorization(d);
    Vec pf(3);
    for(P p : ps){
        if (p.first == 2) pf[0] = p.second;
        else if(p.first == 3)
            pf[1] = p.second;
        else if(p.first == 5)
            pf[2] = p.second;
        else{
            cout << 0.0 << endl;
            return 0;
        }
    }

    ld ans = 0;
    rep(i, 60){
        rep(j, 40){
            rep(k, 30){
                if (i >= pf[0] && j >= pf[1] && k >= pf[2]) ans += cur[i][j][k];
            }
        }
    }
    cout << ans << endl;

    return 0;
}
