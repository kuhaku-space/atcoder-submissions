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
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/binary_tree/BIT.hpp"

/**
 * @brief フェニック木
 * 
 * @tparam T 
 */
template <class T>
struct BIT {
    int N;
    vector<T> data;

    BIT() : N(), data() {}
    BIT(int n, T e = T(0)) : N(n + 1), data(n + 1, e) {}
    BIT(const vector<T> &v) : N(v.size() + 1), data(v.size() + 1) { this->build(v); }

    const T at(int k) const { return this->sum(k + 1) - this->sum(k); }
    const T get(int k) const { return this->at(k); }

    template <class U>
    void build(const vector<U> &v) {
        for (int i = 0, n = v.size(); i < n; ++i) this->add(i, v[i]);
    }

    /**
     * @brief v[k] = val
     *
     * @param k index of array
     * @param val new value
     * @return void
     */
    void update(int k, T val) { this->add(k, val - this->at(k)); }
    /**
     * @brief v[k] += val
     *
     * @param k index of array
     * @param val new value
     * @return void
     */
    void add(int k, T val) {
        assert(0 <= k && k < this->N);
        for (++k; k < N; k += k & -k) this->data[k] += val;
    }
    /**
     * @brief chmax(v[k], val)
     *
     * @param k index of array
     * @param val new value
     * @return bool
     */
    bool chmax(int k, T val) {
        if (this->at(k) >= val) return false;
        this->update(k, val);
        return true;
    }
    /**
     * @brief chmin(v[k], val)
     *
     * @param k index of value
     * @param val new value
     * @return bool
     */
    bool chmin(int k, T val) {
        if (this->at(k) <= val) return false;
        this->update(k, val);
        return true;
    }

    /**
     * @brief v[0] + ... + v[n - 1]
     *
     * @return T
     */
    T all_sum() const { return this->sum(this->N); }
    /**
     * @brief v[0] + ... + v[k - 1]
     *
     * @param k index of array
     * @return T
     */
    T sum(int k) const {
        assert(0 <= k && k <= this->N);
        T res = 0;
        for (; k > 0; k -= k & -k) res += this->data[k];
        return res;
    }
    /**
     * @brief v[a] + ... + v[b - 1]
     *
     * @param a first index of array
     * @param b last index of array
     * @return T
     */
    T sum(int a, int b) const { return a < b ? this->sum(b) - this->sum(a) : 0; }

    /**
     * @brief binary search on BIT
     *
     * @param val target value
     * @return int
     */
    int lower_bound(T val) const {
        if (val <= 0) return 0;
        int k = 1;
        while (k < this->N) k <<= 1;
        int res = 0;
        for (; k > 0; k >>= 1) {
            if (res + k < this->N && this->data[res + k] < val) val -= this->data[res += k];
        }
        return res;
    }
};
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/math/prime_number.hpp"

struct prime_number {
    static constexpr int sz = 1 << 20;
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
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/math/pow.hpp"

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
    if (n < 0) return inv_mod(pow_mod(a, -n, mod), mod);
    int64_t res = 1, mul = a;
    for (; n > 0; n >>= 1) {
        if (n & 1) (res *= mul) %= mod;
        (mul *= mul) %= mod;
    }
    return res;
}

int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < (unsigned int)(n)) x++;
    return x;
}
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/segment_tree/monoid.hpp"

template <class T>
struct Add {
    using value_type = T;
    static constexpr T id = T(0);
    static constexpr T op(const T &lhs, const T &rhs) { return lhs + rhs; }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs + rhs;
    }
};

template <class T>
struct Min {
    using value_type = T;
    static constexpr T id = numeric_limits<T>::max();
    static constexpr T op(const T &lhs, const T &rhs) { return min(lhs, rhs); }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return min((U)lhs, rhs);
    }
};

template <class T>
struct Max {
    using value_type = T;
    static constexpr T id = numeric_limits<T>::min();
    static constexpr T op(const T &lhs, const T &rhs) { return max(lhs, rhs); }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return max((U)lhs, rhs);
    }
};

template <class T>
struct Update {
    using value_type = T;
    static constexpr T id = numeric_limits<T>::max();
    static constexpr T op(const T &lhs, const T &rhs) { return lhs == Update::id ? rhs : lhs; }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs == Update::id ? rhs : lhs;
    }
};
#line 4 "/home/kuhaku/atcoder/github/atcoder-lib/lib/segment_tree/segment_tree.hpp"

/**
 * @brief セグメント木
 * @details [参考](https://noshi91.hatenablog.com/entry/2020/04/22/212649)
 *
 * @tparam M
 * @tparam F
 */
template <class M>
struct segment_tree {
    using T = typename M::value_type;

    segment_tree() {}
    segment_tree(int n, T e = M::id) { this->init(n, e); }

    const T &operator[](int i) const { return this->data[i + this->_size]; }
    T at(int k) const { return this->operator[](k); }
    T get(int k) const { return this->operator[](k); }

    void init(int n, T val) {
        this->_log = ceil_pow2(n);
        this->_size = 1 << this->_log;
        this->data.assign(this->_size << 1, val);
    }

    template <class U>
    void build(const vector<U> &v) {
        for (int i = 0, n = v.size(); i < n; ++i) this->data[this->_size + i] = T(v[i]);
        for (int i = this->_size - 1; i >= 1; --i) this->update(i);
    }

    void set(int k, T val) {
        assert(0 <= k && k < this->_size);
        k += this->_size;
        this->data[k] = val;
        for (int i = 1; i <= this->_log; i++) this->update(k >> i);
    }

    T all_prod() const { return this->data[1]; }
    T prod(int a, int b) const {
        assert(0 <= a && b <= this->_size);
        T l = M::id, r = M::id;
        for (a += this->_size, b += this->_size; a < b; a >>= 1, b >>= 1) {
            if (a & 1) l = M::op(l, this->data[a++]);
            if (b & 1) r = M::op(this->data[--b], r);
        }
        return M::op(l, r);
    }

  private:
    int _size, _log;
    std::vector<T> data;

    void update(int k) { this->data[k] = M::op(this->data[2 * k], this->data[2 * k + 1]); }
};
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/template/atcoder.hpp"
#pragma GCC target("avx")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#line 6 "/home/kuhaku/atcoder/github/atcoder-lib/lib/template/atcoder.hpp"
using ll = int64_t;
using ld = long double;
#define FOR(i, m, n) for(int i = (m); i < int(n); ++i)
#define FORR(i, m, n) for(int i = (m)-1; i >= int(n); --i)
#define FORL(i, m, n) for(int64_t i = (m); i < int64_t(n); ++i)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FOR(i, 1, n+1)
#define repr(i, n) FORR(i, n, 0)
#define repnr(i, n) FORR(i, n+1, 1)
#define all(s) (s).begin(), (s).end()
template<class T, class U>
std::istream &operator>>(std::istream &is, std::pair<T, U> &p) { is >> p.first >> p.second; return is; }
template <class T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) { for (T &i : v) is>>i; return is; }
template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    for (auto it=v.begin(); it!=v.end(); ++it) { os<<(it==v.begin()?"":" ")<<*it; } return os;
}
template <class Head, class... Tail>
void co(Head&& head, Tail&&... tail) {
    if constexpr(sizeof...(tail)==0) std::cout<<head<<'\n'; else std::cout<<head<<' ',co(forward<Tail>(tail)...);
}
template <class Head, class... Tail>
void ce(Head&& head, Tail&&... tail) {
    if constexpr(sizeof...(tail)==0) std::cerr<<head<<'\n'; else std::cerr<<head<<' ',ce(forward<Tail>(tail)...);
}
template<typename T, typename... Args>
auto make_vector(T x, int arg, Args ...args) {
    if constexpr(sizeof...(args)==0) return std::vector<T>(arg,x); else return std::vector(arg,make_vector<T>(x,args...));
}
void sonic() { std::ios::sync_with_stdio(false); std::cin.tie(nullptr); }
void setp(const int n) { std::cout<<std::fixed<<std::setprecision(n); }
void Yes(bool is_correct) { std::cout<<(is_correct?"Yes":"No")<<std::endl; }
void YES(bool is_correct) { std::cout<<(is_correct?"YES":"NO")<<std::endl; }
#line 6 "a.cpp"

template <class T>
struct Xor {
    using value_type = T;
    static constexpr T id = 0;
    static constexpr T op(const T &lhs, const T &rhs) {
        return lhs ^ rhs;
    }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs ^ rhs;
    }
};

struct XorShift {
    using result_type = uint64_t;
    result_type x;

    constexpr XorShift() : x(123456789) {}

    constexpr result_type min() const {
        return std::numeric_limits<result_type>::min();
    }
    constexpr result_type max() const {
        return std::numeric_limits<result_type>::max();
    }
    result_type operator()() {
        x ^= x << 13;
        x ^= x >> 7;
        x ^= x << 17;
        return x;
    }
};
XorShift xor64;

int main(void) {
    sonic();
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    cin >> a;

    prime_number pn;
    auto primes = pn.prime_numbers(1000000);
    unordered_map<int, int> count;
    unordered_map<int, pair<XorShift::result_type, XorShift::result_type>> mp;
    rep(i, primes.size()) mp[primes[i]] = make_pair(xor64(), xor64());

    vector<vector<pair<int, int>>> vs(1000001);
    FOR(i, 2, 1000001) {
        vs[i] = pn.prime_factorization(i);
    }

    segment_tree<Xor<ll>> st(n);

    rep(i, n) {
        if (a[i] == 1)
            continue;
        auto v = vs[a[i]];
        for (auto p : v) {
            auto q = mp[p.first];
            rep(_, p.second) {
                if (count[p.first] % 3 != 1)
                    st.set(i, st[i] ^ q.first);
                if (count[p.first] % 3 != 0)
                    st.set(i, st[i] ^ q.second);
                ++count[p.first];
            }
        }
    }

    rep(i, q) {
        int l, r;
        cin >> l >> r;
        Yes(st.prod(l - 1, r) == 0);
    }

    return 0;
}
