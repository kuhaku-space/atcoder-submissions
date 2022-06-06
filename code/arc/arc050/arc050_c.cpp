#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/template/template.hpp"
#include <bits/stdc++.h>
using namespace std;
template <class T, class U>
bool chmax(T &a, const U &b) {
    return a < b ? a = b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U &b) {
    return b < a ? a = b, true : false;
}
constexpr int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
const double PI = acos(-1.0);
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/math/chinese_rem.hpp"

/*
 * a * x + b * y = gcd(a, b) の答えを一つ求める
 * 戻り値は gcd(a, b)
 */
int64_t extGCD(const int64_t a, const int64_t b, int64_t &x, int64_t &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }

    int64_t d = extGCD(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

/*
 * 任意の i において、x % b_i = m_i となる x を求める
 * x = r + M * k (k in N) と表すことができる
 */
template <class T, class U>
pair<int64_t, int64_t> chinese_rem(const vector<T> &b, const vector<U> &m) {
    int64_t r = 0, M = 1;
    int n = b.size();
    for (int i = 0; i < n; ++i) {
        int64_t p, q;
        int64_t d = extGCD(M, m[i], p, q);
        if ((b[i] - r) % d != 0) return {0, -1};
        int64_t tmp = (b[i] - r) / d * p % (m[i] / d);
        r += M * tmp;
        M *= m[i] / d;
    }
    return {r >= 0 ? r % M : M - 1 - (-r - 1) % M, M};
}
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/math/pow.hpp"

template <class T>
T power(T a, int64_t n) {
    T res(1), mul(a);
    for (; n > 0; n >>= 1) {
        if (n & 1) res *= mul;
        mul *= mul;
    }
    return res;
}

int64_t pow_int(int64_t a, int64_t n) {
    assert(n >= 0);
    int64_t res = 1, mul = a;
    for (; n > 0; n >>= 1) {
        if (n & 1) res *= mul;
        mul *= mul;
    }
    return res;
}

int64_t inv_mod(int64_t a, int64_t mod) {
    int64_t b = mod, u = 1, v = 0, t;
    while (b > 0) {
        t = a / b;
        swap(a -= t * b, b);
        swap(u -= t * v, v);
    }
    return u >= 0 ? u % mod : (mod - (-u) % mod) % mod;
}

int64_t pow_mod(int64_t a, int64_t n, int64_t mod) {
    // if (n < 0) return inv_mod(pow_mod(a, -n, mod), mod);
    int64_t res = 1, mul = a;
    for (; n > 0; n >>= 1) {
        if (n & 1) (res *= mul) %= mod;
        (mul *= mul) %= mod;
    }
    return res;
}
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/math/prime_number.hpp"

struct prime_number {
    static constexpr int sz = 1 << 22;
    bitset<sz> is_not_prime;
    vector<int> data;

    prime_number() { init(); }

    void init() {
        is_not_prime[0] = is_not_prime[1] = true;
        for (int i = 2; i < sz; ++i) {
            if (!is_not_prime[i]) {
                data.emplace_back(i);
                if ((int64_t)i * i >= sz) continue;
                if (i == 2) {
                    for (int j = i * i; j < sz; j += i) is_not_prime[j] = true;
                } else {
                    for (int j = i * i; j < sz; j += i << 1) is_not_prime[j] = true;
                }
            }
        }
    }

    constexpr bool is_prime(int64_t n) const {
        assert(n >= 0);
        if (n < sz) return !is_not_prime[n];
        for (auto i : data) {
            if ((int64_t)i * i > n) break;
            if (n % i == 0) return false;
        }
        return true;
    }

    vector<int> prime_numbers(int x) const {
        vector<int> res;
        for (auto i : data) {
            if (i > x) break;
            res.emplace_back(i);
        }
        return res;
    }

    /**
     * @brief 素因数分解
     *
     * @tparam T
     * @param x
     * @return vector<pair<T, int>>
     */
    template <class T>
    vector<pair<T, int>> prime_factorization(T x) const {
        if (x == 1) return vector<pair<T, int>>(1, {1, 1});
        vector<pair<T, int>> res;
        for (auto i : data) {
            int cnt = 0;
            for (; x % i == 0; x /= i) ++cnt;
            if (cnt) res.emplace_back(i, cnt);
            if ((int64_t)i * i > x) break;
        }
        if (x != 1) res.emplace_back(x, 1);
        return res;
    }

    /**
     * @brief 約数列挙
     *
     * @tparam T
     * @param x
     * @return vector<T>
     */
    template <class T>
    vector<T> divisors(T x) const {
        if (x == 1) return vector<T>(1, 1);
        auto v = this->prime_factorization(x);
        vector<T> res;
        res.emplace_back(1);
        for (auto p : v) {
            int n = res.size();
            res.resize(n * (p.second + 1));
            for (int i = 0; i < n * p.second; ++i) { res[n + i] = res[i] * p.first; }
            for (int i = 1; i <= p.second; ++i) {
                inplace_merge(res.begin(), res.begin() + n * i, res.begin() + n * (i + 1));
            }
        }
        return res;
    }

    // 因数分解列挙
    template <class T>
    vector<vector<T>> factorization(T x) const {
        vector<vector<T>> res;
        auto f = [&](auto self, vector<T> v, T a) -> void {
            if (a == 1) res.emplace_back(v);
            for (auto i : divisors(a)) {
                if (i == 1 || (!v.empty() && v.back() > i)) continue;
                v.emplace_back(i);
                self(self, v, a / i);
                v.pop_back();
            }
        };
        f(f, vector<T>(), x);
        return res;
    }
};
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/template/atcoder.hpp"
#pragma GCC target("avx")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#line 6 "/home/kuhaku/atcoder/github/atcoder-lib/lib/template/atcoder.hpp"
using ll = int64_t;
using ld = long double;
#define FOR(i, m, n) for(int i = (m); i < (n); ++i)
#define FORR(i, m, n) for(int i = (m)-1; i >= (n); --i)
#define FORL(i, m, n) for(ll i = (m); i < (n); ++i)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FOR(i, 1, n+1)
#define repr(i, n) FORR(i, n, 0)
#define repnr(i, n) FORR(i, n+1, 1)
#define all(s) (s).begin(), (s).end()
template<class T, class U>
istream &operator>>(istream &is, pair<T, U> &p) { is >> p.first >> p.second; return is; }
template <class T>
istream &operator>>(istream &is, vector<T> &v) { for (T &i : v) is>>i; return is; }
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    for (auto it=v.begin(); it!=v.end(); ++it) { os<<(it==v.begin()?"":" ")<<*it; } return os;
}
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
#line 6 "a.cpp"

prime_number pn;

int main(void) {
    sonic();
    ll a, b;
    int m;
    cin >> a >> b >> m;
    ll c = gcd(a, b);

    unordered_map<ll, ll> mf, mg, mh;

    auto g = [&](auto self, ll k, int p) -> ll {
        if (k == 0)
            return 1;
        if (mg.count(k))
            return mg[k];
        if (k & 1)
            return mg[k] = self(self, k - 1, p) * 10 % p;
        else
            return mg[k] = self(self, k / 2, p) * self(self, k / 2, p) % p;
    };

    auto f = [&](auto self, ll k, int p) -> ll {
        if (k == 0)
            return 0;
        if (mf.count(k))
            return mf[k];

        if (k & 1)
            return mf[k] = (self(self, k - 1, p) * 10 + 1) % p;
        else
            return mf[k] = (self(self, k / 2, p) * g(g, k / 2, p) % p + self(self, k / 2, p)) % p;
    };

    auto h = [&](auto self, ll k, int p) -> ll {
        if (k == 0)
            return 0;
        if (mh.count(k))
            return mh[k];
        if (k & 1)
            return mh[k] = (self(self, k - 1, p) * g(g, c, p) + 1) % p;
        else
            return mh[k] = (self(self, k / 2, p) * g(g, c * k / 2, p) + self(self, k / 2, p)) % p;
    };

    auto x = f(f, a, m);
    auto y = h(h, b / c, m);
    co(x * y % m);

    return 0;
}
