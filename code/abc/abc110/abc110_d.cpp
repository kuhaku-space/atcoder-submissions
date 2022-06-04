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

template <int mod>
struct ModInt {
    int x;

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

    ModInt pow(int64_t n) const noexcept { return ModInt(*this).pow_self(n); }
    ModInt &pow_self(int64_t n) noexcept {
        ModInt res(1);
        for (; n > 0; n >>= 1) {
            if (n & 1) res *= *this;
            *this *= *this;
        }
        *this = res;
        return *this;
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
using Mint = ModInt<MOD>;

template <int mod>
struct Combination {
    using mint = ModInt<mod>;
    vector<mint> fac, finv;

    Combination() {}

    mint operator()(int n, int k) {
        if (n < k || n < 0 || k < 0) return 0;
        _init(n);
        return fac[n] * finv[k] * finv[n - k];
    }

    void _init(int n) {
        if (fac.size() > n) return;
        int m = fac.size();
        fac.resize(n + 1);
        for (int i = m; i <= n; ++i) {
            if (i == 0)
                fac[i] = 1;
            else
                fac[i] = fac[i - 1] * i;
        }
        finv.resize(n + 1);
        finv[n] = fac[n].inverse();
        for (int i = n - 1; i >= m; --i) finv[i] = finv[i + 1] * (i + 1);
    }

    mint fact(int x) {
        assert(x >= 0);
        _init(x);
        return fac[x];
    }

    mint naive(int n, int k) const {
        if (n < k || n < 0 || k < 0) return 0;
        if (n - k < k) k = n - k;
        mint res = 1;
        for (int i = 0; i < k; ++i) {
            res *= n - i;
            res /= i + 1;
        }
        return res;
    }

    mint lucas(int n, int k) {
        if (n < k || n < 0 || k < 0) return 0;
        if (n - k < k) k = n - k;
        static vector<vector<mint>> v;
        if (v.empty()) {
            v = vector<vector<mint>>(mod, vector<mint>(mod));
            for (int i = 0; i < mod; ++i) v[i][0] = 1;
            for (int i = 0; i < mod; ++i) {
                for (int j = 1; j < mod; ++j) {
                    if (i < j)
                        v[i][j] = 0;
                    else if (i - j < j)
                        v[i][j] = v[i][i - j];
                    else
                        v[i][j] = v[i][j - 1] * mint(i + 1 - j) / mint(j);
                }
            }
        }
        mint res = 1;
        while (n || k) {
            res *= v[n % mod][k % mod];
            n /= mod, k /= mod;
        }
        return res;
    }

    mint permu(int n, int k) {
        if (n < k || n < 0 || k < 0) return 0;
        _init(n);
        return fac[n] * finv[n - k];
    }
};
Combination<MOD> combi;

struct prime_number {
    const int sz = 1 << 22;
    bitset<1 << 22> is_not_prime;
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
                    for (int j = i * i; j < sz; j += i << 1)
                        is_not_prime[j] = true;
                }
            }
        }
    }

    bool is_prime(int64_t n) {
        assert(n >= 0);
        if (n < sz) return !is_not_prime[n];
        for (auto i : data) {
            if ((int64_t)i * i > n) break;
            if (n % i == 0) return false;
        }
        return true;
    }

    vector<int> prime_numbers(int x) {
        vector<int> res;
        for (auto i : data) {
            if (i > x) break;
            res.emplace_back(i);
        }
        return res;
    }

    // 素因数分解
    template <class T>
    vector<pair<T, int>> prime_factorization(T x) {
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

    // 約数列挙
    template <class T>
    vector<T> divisors(T x) {
        auto v = this->prime_factorization(x);
        vector<T> res;
        res.emplace_back(1);
        for (auto p : v) {
            int n = res.size();
            res.resize(n * (p.second + 1));
            for (int i = 0; i < n * p.second; ++i) {
                res[n + i] = res[i] * p.first;
            }
            for (int i = 1; i <= p.second; ++i) {
                inplace_merge(res.begin(), res.begin() + n * i,
                              res.begin() + n * (i + 1));
            }
        }
        return res;
    }

    // 因数分解列挙
    template <class T>
    vector<vector<T>> factorization(T x) {
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
prime_number pn;

int main(void){
    ll n, m;
    cin >> n >> m;

    if (m == 1) {
        co(1);
        return 0;
    }

    auto v = pn.prime_factorization(m);

    Mint ans = 1;
	for (auto p : v) {
        ans *= combi(p.second + n - 1, n - 1);
    }
    co(ans);

    return 0;
}
