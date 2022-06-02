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

template <int mod>
struct ModInt {
    int64_t x;

    ModInt() : x(0) {}

    ModInt(int64_t y) noexcept
        : x(y >= 0 ? y % mod : (mod - 1 - (-y - 1) % mod)) {}

    ModInt &operator+=(const ModInt &rhs) noexcept {
        if ((x += rhs.x) >= mod) x -= mod;
        return *this;
    }
    ModInt &operator-=(const ModInt &rhs) noexcept {
        if ((x += mod - rhs.x) >= mod) x -= mod;
        return *this;
    }
    ModInt &operator*=(const ModInt &rhs) noexcept {
        x = (int)(1LL * x * rhs.x % mod);
        return *this;
    }
    ModInt &operator/=(const ModInt &rhs) noexcept {
        *this *= rhs.inverse();
        return *this;
    }

    ModInt &operator++() noexcept {
        if ((++x) >= mod) x -= mod;
        return *this;
    }
    ModInt operator++(int) noexcept {
        ModInt tmp(*this);
        operator++();
        return tmp;
    }
    ModInt &operator--() noexcept {
        if ((x += mod - 1) >= mod) x -= mod;
        return *this;
    }
    ModInt operator--(int) noexcept {
        ModInt tmp(*this);
        operator--();
        return tmp;
    }

    ModInt operator-() const noexcept { return ModInt(-x); }
    ModInt operator+(const ModInt &rhs) const noexcept {
        return ModInt(*this) += rhs;
    }
    ModInt operator-(const ModInt &rhs) const noexcept {
        return ModInt(*this) -= rhs;
    }
    ModInt operator*(const ModInt &rhs) const noexcept {
        return ModInt(*this) *= rhs;
    }
    ModInt operator/(const ModInt &rhs) const noexcept {
        return ModInt(*this) /= rhs;
    }

    bool operator==(const ModInt &rhs) const noexcept { return x == rhs.x; }
    bool operator!=(const ModInt &rhs) const noexcept { return x != rhs.x; }

    ModInt inverse() const noexcept {
        int a = x, b = mod, u = 1, v = 0, t;
        while (b > 0) {
            t = a / b;
            swap(a -= t * b, b);
            swap(u -= t * v, v);
        }
        return ModInt(u);
    }

    ModInt pow(int64_t n) const noexcept {
        ModInt res(1), mul(x);
        for (; n > 0; n >>= 1) {
            if (n & 1) res *= mul;
            mul *= mul;
        }
        return res;
    }

    void pow_self(int64_t n) noexcept {
        ModInt tmp = pow(n);
        swap(*this, tmp);
    }

    friend istream &operator>>(istream &is, ModInt &rhs) {
        int64_t t;
        is >> t;
        rhs = ModInt<mod>(t);
        return (is);
    }

    friend ostream &operator<<(ostream &os, const ModInt &rhs) {
        return os << rhs.x;
    }

    int to_int() const noexcept { return x; }

    static int get_mod() noexcept { return mod; }
};
using Mint = ModInt<MOD_N>;

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

template <int mod>
struct math_mod {
    using mint = ModInt<mod>;
    vector<mint> fac, finv;

    math_mod() { _init(1 << 22); }

    void _init(int64_t n) {
        if (fac.size() > n) return;
        int m = fac.size();
        fac.resize(n + 1);
        for (int64_t i = m; i <= n; ++i) {
            if (i == 0)
                fac[i] = 1;
            else
                fac[i] = fac[i - 1] * i;
        }
        finv.resize(n + 1);
        finv[n] = fac[n].inverse();
        for (int64_t i = n - 1; i >= m; --i) finv[i] = finv[i + 1] * (i + 1);
    }

    mint fact(int64_t x) {
        assert(x >= 0);
        _init(x);
        return fac[x];
    }

    mint combi(int64_t n, int64_t k) {
        if (n < k || n < 0 || k < 0) return 0;
        _init(n);
        return fac[n] * finv[k] * finv[n - k];
    }

    mint combi_naive(int64_t n, int64_t k) const {
        if (n < k || n < 0 || k < 0) return 0;
        if (n - k < k) k = n - k;
        mint res = 1;
        for (int64_t i = 0; i < k; ++i) {
            res *= n - i;
            res /= i + 1;
        }
        return res;
    }

    mint permu(int64_t n, int64_t k) {
        if (n < k || n < 0 || k < 0) return 0;
        _init(n);
        return fac[n] * finv[n - k];
    }
};
math_mod<MOD_N> math;

// clang-format on

int main(void) {
    int n, m;
    cin >> n >> m;

    Mint ans = 0;

    map<pair<int, int>, Mint> mp;
    auto dfs = [&](auto self, int r, int k) -> Mint {
        if (mp.find({r, k}) != mp.end()) {
            return mp[{r, k}];
        }
        if (r == 0) {
            return 1;
        }
        if (k == -1) {
            return 0;
        }
        int t = 0;
        Mint res = 0;
        while (true) {
            if (r < t * k || t > n)
                break;
            res += self(self, r - t * (1 << k), k - 1) * math.combi(n, t);
            t += 2;
        }
        return mp[{r, k}] = res;
    };

    co(dfs(dfs, m, 13));

    return 0;
}
