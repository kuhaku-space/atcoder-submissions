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
istream &operator>>(istream &is, vector<T> &v) { for (T &i : v) is >> i; return is; }
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) { for (const T &i : v) os << i << ' '; return os; }
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

struct prime_number {
    const int sz = 1 << 22;
    bitset<1 << 22> is_not_prime;
    vector<int64_t> data;

    prime_number() { init(); }

    void init() {
        is_not_prime[0] = is_not_prime[1] = true;
        for (int64_t i = 2; i < sz; ++i) {
            if (!is_not_prime[i]) {
                data.emplace_back(i);
                for (int64_t j = 2; i * j < sz; ++j) {
                    is_not_prime[i * j] = true;
                }
            }
        }
    }

    bool is_prime(int64_t n) {
        assert(n >= 0);
        if (n < sz) return !is_not_prime[n];
        for (auto i : data) {
            if (i * i > n) break;
            if (n % i == 0) return false;
        }
        return true;
    }

    vector<int64_t> prime_numbers(int64_t n) {
        vector<int64_t> res;
        for (int i = 2; i <= n; ++i) {
            if (!is_not_prime[i])
                res.emplace_back(i);
        }
        return res;
    }

    // 素因数分解
    vector<pair<int64_t, int64_t>> prime_factorization(int64_t n) {
        vector<pair<int64_t, int64_t>> res;

        for (auto i : data) {
            int64_t cnt = 0;
            for (; n % i == 0; n /= i) cnt++;
            if (cnt) res.emplace_back(i, cnt);
            if (n < i * i) break;
        }
        if (n != 1) res.emplace_back(n, 1);

        return res;
    }

    int64_t pow_int(int64_t x, int64_t n) {
        assert(n >= 0);
        int64_t res = 1;
        for (; n > 0; n >>= 1) {
            if (n & 1) res *= x;
            x *= x;
        }
        return res;
    }

    // 約数列挙
    vector<int64_t> divisors(int64_t n) {
        auto v = prime_factorization(n);

        vector<int64_t> res, a, b, cp;
        res.emplace_back(1);
        for (auto p : v) {
            cp.resize(res.size());
            copy(res.begin(), res.end(), cp.begin());
            a.resize(res.size());
            for (int64_t k = 1; k <= p.second; ++k) {
                int64_t t = pow_int(p.first, k);
                for (int64_t i = 0; i < a.size(); ++i) a[i] = cp[i] * t;
                merge(res.begin(), res.end(), a.begin(), a.end(),
                      back_inserter(b));
                swap(res, b);
                b.clear();
            }
        }

        return res;
    }

    // 因数分解列挙
    vector<vector<int64_t>> factorization(int64_t n) {
        vector<vector<int64_t>> res;

        auto f = [&](auto self, vector<int64_t> v, int64_t a) -> void {
            if (a == 1) res.emplace_back(v);
            for (auto i : divisors(a)) {
                if (i == 1 || (!v.empty() && v.back() > i)) continue;
                v.emplace_back(i);
                self(self, v, a / i);
                v.pop_back();
            }
        };

        f(f, vector<int64_t>(), n);
        return res;
    }
};
prime_number pn;

int main(void) {
    int n;
    cin >> n;

    vector<int> ans(n);
    rep(i, n) {
        if (i == 0)
            ans[i] = 1;
        else {
            auto v = pn.divisors(i + 1);
            int m = 0;
            for (auto j : v) chmax(m, ans[j - 1]);
            ans[i] = m + 1;
        }
    }
    co(ans);

    return 0;
}
