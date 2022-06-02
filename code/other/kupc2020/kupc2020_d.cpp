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
void ce() { cerr << endl; }
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

struct prime_number {
    vector<int64_t> data;

    prime_number() {
        init();
    }

    void init() {
        constexpr int sz = 4194304;
        bitset<sz> is_not_prime;
        is_not_prime[0] = is_not_prime[1] = true;
        for (size_t i = 2; i < sz; ++i) {
            if (!is_not_prime[i]) {
                data.push_back(i);
                for (size_t j = 2; i * j < sz; ++j) {
                    is_not_prime[i * j] = true;
                }
            }
        }
    }

    bool is_prime(int64_t n) {
        if(n == 1) return false;
        for (auto i : data) {
            if (i * i > n) break;
            if (n % i == 0) return false;
        }
        return true;
    }

    vector<pair<ll, ll>> prime_factorization(int64_t n) {
        vector<pair<ll, ll>> res;

        for (auto i : data) {
            int64_t cnt = 0;
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

    vector<ll> divisors(int64_t n) {
        auto v = prime_factorization(n);

        vector<ll> res, a, b, cp;
        res.push_back(1);
        for (auto p : v) {
            cp.resize(res.size());
            copy(res.begin(), res.end(), cp.begin());
            a.resize(res.size());
            for(size_t k = 1; k <= p.second; ++k){
                int64_t t = pow(p.first, k);
                for (size_t i = 0; i < a.size(); ++i) a[i] = cp[i] * t;
                merge(res.begin(), res.end(), a.begin(), a.end(), back_inserter(b));
                swap(res, b);
                b.clear();
            }
        }

        return res;
    }
};
prime_number pn;

int main(void) {
    ll n;
    cin >> n;
    if(pn.is_prime(n)) {
        puts("impossible");
        return 0;
    }

    ll sz = 0;
    REP(i, 2, n) {
        if(n % i == 0) {
            sz = i;
            break;
        }
    }

    ll tmp = n / sz;
    Vec2<ll> ans(tmp);
    ll cnt = 0;
    while(sz) {
        if(sz > 3 || sz == 2) {
            rep(i, tmp) ans[i].push_back(++cnt);
            repr(i, tmp) ans[i].push_back(++cnt);
            sz -= 2;
            continue;
        }

        rep(i, tmp) ans[i].push_back(++cnt);
        repr(i, (tmp + 1) / 2) {
            ans[i * 2].push_back(++cnt);
        }
        repr(i, tmp / 2) {
            ans[i * 2 + 1].push_back(++cnt);
        }
        repr(i, tmp / 2) {
            ans[i * 2 + 1].push_back(++cnt);
        }
        repr(i, (tmp + 1) / 2) {
            ans[i * 2].push_back(++cnt);
        }
        sz -= 3;
    }

    co(ans.size());
    for(auto v : ans) {
        cout << v.size() << ' ';
        for(auto i : v) {
            cout << i * 2 - 1 << ' ';
        }
        cout << endl;
    }

    return 0;
}