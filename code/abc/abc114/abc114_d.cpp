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
template <class T1, class T2>
bool chmax(T1 &a, const T2 b) { if (a < b) { a = b; return true; } return false; }
template <class T1, class T2>
bool chmin(T1 &a, const T2 b) { if (a > b) { a = b; return true; } return false; }
template <class T>
istream &operator>>(istream &is, vector<T> &v) { for (T &i : v) is >> i; return is; }
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) { for (const T &i : v) os << i << ' '; return os; }
void co() { cout << '\n'; }
template <class Head, class... Tail>
void co(Head&& head, Tail&&... tail) { cout << head << ' '; co(forward<Tail>(tail)...); }
void ce() { cerr << '\n'; }
template <class Head, class... Tail>
void ce(Head&& head, Tail&&... tail) { cerr << head << ' '; ce(forward<Tail>(tail)...); }
void sonic() { ios::sync_with_stdio(false); cin.tie(nullptr); }
void setp(const int n) { cout << fixed << setprecision(n); }
constexpr int64_t LINF = 1000000000000000001;
constexpr int64_t MOD = 1000000007;
constexpr int64_t MOD_N = 998244353;
constexpr long double EPS = 1e-11;
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
        for (int64_t i = 2; i < sz; ++i) {
            if (!is_not_prime[i]) {
                data.push_back(i);
                for (int64_t j = 2; i * j < sz; ++j) {
                    is_not_prime[i * j] = true;
                }
            }
        }
    }

    bool is_prime(int64_t n) {
        if (n == 1) return false;
        for (auto i : data) {
            if (i * i > n) break;
            if (n % i == 0) return false;
        }
        return true;
    }

    vector<pair<int64_t, int64_t>> prime_factorization(int64_t n) {
        vector<pair<int64_t, int64_t>> res;

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

    int64_t pow_int(int64_t x, int64_t n) {
        int64_t res = 1;
        while (n) {
            if (n & 1) res *= x;
            x *= x;
            n >>= 1;
        }
        return res;
    }

    vector<int64_t> divisors(int64_t n) {
        auto v = prime_factorization(n);

        vector<int64_t> res, a, b, cp;
        res.push_back(1);
        for (auto p : v) {
            cp.resize(res.size());
            copy(res.begin(), res.end(), cp.begin());
            a.resize(res.size());
            for (int64_t k = 1; k <= p.second; ++k) {
                int64_t t = pow_int(p.first, k);
                for (int64_t i = 0; i < a.size(); ++i) a[i] = cp[i] * t;
                merge(res.begin(), res.end(), a.begin(), a.end(), back_inserter(b));
                swap(res, b);
                b.clear();
            }
        }

        return res;
    }

    vector<vector<int64_t>> factorization(int64_t n) {
        vector<vector<int64_t>> res;

        auto f = [&](auto g, vector<int64_t> v, int64_t a) -> void {
            if (a == 1) res.push_back(v);
            for (auto i : divisors(a)) {
                if (i == 1 || (!v.empty() && v.back() > i)) continue;
                v.push_back(i);
                g(g, v, a / i);
                v.pop_back();
            }
        };

        f(f, vector<int64_t>(), n);
        return res;
    }
};
prime_number pn;

int main(void) {
    ll n;
    cin >> n;

    Vec cnt(100);

    REPN(i, 2, n) {
        auto v = pn.prime_factorization(i);
        for (auto p : v) {
            cnt[p.first] += p.second;
        }
    }

    Vec cs(100);
    rep(i, 100) cs[cnt[i]]++;
    repr(i, 99) {
        cs[i] += cs[i + 1];
    }

    auto vs = pn.factorization(75);
    for (auto &v : vs) reverse(all(v));

    ll ans = 0;
    for (auto &v : vs) {
        ll a = 1, c = 0;
        for (auto i : v) {
            if (cs[i - 1] <= c) {
                a = 0;
                break;
            }
            a *= cs[i - 1] - c;
            ++c;
        }
        if (v.size() == 3) a /= 2;
        ans += a;
    }
    cout << ans << endl;

    return 0;
}