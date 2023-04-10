#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/home/github/algo/lib/template/template.hpp"
#pragma GCC target("sse4.2,avx2,bmi2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
template <class T, class U>
bool chmax(T &a, const U &b) {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U &b) {
    return (T)b < a ? a = (T)b, true : false;
}
constexpr int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
constexpr double PI = M_PI;
#line 3 "/home/kuhaku/home/github/algo/lib/math/pow.hpp"

std::int64_t safe_mod(std::int64_t a, std::int64_t mod) {
    a %= mod;
    return a >= 0 ? a : a + mod;
}

std::int64_t pow_int(std::int64_t a, std::int64_t n) {
    assert(n >= 0);
    std::int64_t res = 1, mul = a;
    for (; n > 0; n >>= 1) {
        if (n & 1) res *= mul;
        mul *= mul;
    }
    return res;
}

std::int64_t inv_mod(std::int64_t a, std::int64_t mod) {
    std::int64_t b = mod, u = 1, v = 0, t;
    while (b > 0) {
        t = a / b;
        swap(a -= t * b, b);
        swap(u -= t * v, v);
    }
    return u >= 0 ? u % mod : (mod - (-u) % mod) % mod;
}

std::int64_t pow_mod(std::int64_t a, std::int64_t n, std::int64_t mod) {
    if (n < 0) return inv_mod(pow_mod(a, -n, mod), mod);
    std::int64_t res = 1, mul = safe_mod(a, mod);
    for (; n > 0; n >>= 1) {
        if (n & 1) (res *= mul) %= mod;
        (mul *= mul) %= mod;
    }
    return res;
}

int ceil_pow2(std::int64_t n) {
    int x = 0;
    while ((std::uint64_t(1) << x) < (std::uint64_t)(n)) ++x;
    return x;
}

int floor_pow2(std::int64_t n) {
    int x = 0;
    while ((std::uint64_t(1) << (x + 1)) <= (std::uint64_t)(n)) ++x;
    return x;
}
#line 2 "/home/kuhaku/home/github/algo/lib/math/prime_number.hpp"

/**
 * @brief 素数ライブラリ
 *
 * @tparam N
 */
template <int N = 1 << 22>
struct prime_number {
    prime_number() : is_not_prime(), data() { this->init(); }

    /**
     * @brief 素数判定
     *
     * @param n
     * @return bool
     */
    bool is_prime(std::int64_t n) const {
        assert(n >= 0);
        if (n < N) return !this->is_not_prime[n];
        for (auto i : this->data) {
            if ((std::int64_t)i * i > n) break;
            if (n % i == 0) return false;
        }
        return true;
    }

    std::vector<int> prime_numbers(int x) const {
        std::vector<int> res;
        for (auto i : this->data) {
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
     * @return std::vector<pair<T, int>>
     */
    template <class T>
    std::vector<pair<T, int>> prime_factorization(T x) const {
        if (x == 1) return std::vector<pair<T, int>>();
        std::vector<pair<T, int>> res;
        for (auto i : this->data) {
            int cnt = 0;
            for (; x % i == 0; x /= i) ++cnt;
            if (cnt) res.emplace_back(i, cnt);
            if ((std::int64_t)i * i > x) break;
        }
        if (x != 1) res.emplace_back(x, 1);
        return res;
    }

    /**
     * @brief 約数列挙
     *
     * @tparam T
     * @param x
     * @return std::vector<T>
     */
    template <class T>
    std::vector<T> divisors(T x) const {
        if (x == 1) return std::vector<T>(1, 1);
        auto v = this->prime_factorization(x);
        std::vector<T> res;
        res.emplace_back(1);
        for (auto p : v) {
            int n = res.size();
            res.resize(n * (p.second + 1));
            for (int i = 0; i < n * p.second; ++i) {
                res[n + i] = res[i] * p.first;
            }
            for (int i = 1; i <= p.second; ++i) {
                std::inplace_merge(res.begin(), res.begin() + n * i, res.begin() + n * (i + 1));
            }
        }
        return res;
    }

    /**
     * @brief 因数分解列挙
     *
     * @tparam T
     * @param x
     * @return std::vector<std::vector<T>>
     */
    template <class T>
    std::vector<std::vector<T>> factorization(T x) const {
        std::vector<std::vector<T>> res;
        auto f = [&](auto self, std::vector<T> v, T a) -> void {
            if (a == 1) res.emplace_back(v);
            for (auto i : this->divisors(a)) {
                if (i == 1 || (!v.empty() && v.back() > i)) continue;
                v.emplace_back(i);
                self(self, v, a / i);
                v.pop_back();
            }
        };
        f(f, std::vector<T>(), x);
        return res;
    }

  private:
    std::bitset<N> is_not_prime;
    std::vector<int> data;

    void init() {
        this->is_not_prime[0] = this->is_not_prime[1] = true;
        for (int i = 2; i < N; ++i) {
            if (!this->is_not_prime[i]) {
                this->data.emplace_back(i);
                if ((std::int64_t)i * i >= N) continue;
                if (i == 2) {
                    for (int j = i * i; j < N; j += i) this->is_not_prime[j] = true;
                } else {
                    for (int j = i * i; j < N; j += i << 1) this->is_not_prime[j] = true;
                }
            }
        }
    }
};
#line 3 "/home/kuhaku/home/github/algo/lib/segment_tree/monoid.hpp"

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
struct And {
    using value_type = T;
    static constexpr T id = std::numeric_limits<T>::max();
    static constexpr T op(const T &lhs, const T &rhs) { return lhs & rhs; }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs & rhs;
    }
};

template <class T>
struct Or {
    using value_type = T;
    static constexpr T id = T(0);
    static constexpr T op(const T &lhs, const T &rhs) { return lhs | rhs; }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs | rhs;
    }
};

template <class T>
struct Xor {
    using value_type = T;
    static constexpr T id = T(0);
    static constexpr T op(const T &lhs, const T &rhs) { return lhs ^ rhs; }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs ^ rhs;
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

template <class T>
struct Affine {
    using value_type = std::pair<T, T>;
    static constexpr std::pair<T, T> id = std::pair<T, T>(1, 0);
    static constexpr std::pair<T, T> op(std::pair<T, T> lhs, std::pair<T, T> rhs) {
        return {lhs.first * rhs.first, lhs.first * rhs.second + lhs.second};
    }
};

template <class M>
struct Rev {
    using T = typename M::value_type;
    using value_type = T;
    static constexpr T id = M::id;
    static constexpr T op(T lhs, T rhs) { return M::op(rhs, lhs); }
};
#line 5 "/home/kuhaku/home/github/algo/lib/segment_tree/segment_tree.hpp"

/**
 * @brief セグメント木
 * @see https://noshi91.hatenablog.com/entry/2020/04/22/212649
 *
 * @tparam M モノイド
 */
template <class M>
struct segment_tree {
  private:
    using T = typename M::value_type;

  public:
    segment_tree() : segment_tree(0) {}
    explicit segment_tree(int n, T e = M::id) : segment_tree(std::vector<T>(n, e)) {}
    template <class U>
    explicit segment_tree(const std::vector<U> &v) : _n(v.size()) {
        this->_log = ceil_pow2(this->_n);
        this->_size = 1 << this->_log;
        this->data = std::vector<T>(this->_size << 1, M::id);
        for (int i = 0; i < this->_n; ++i) this->data[this->_size + i] = T(v[i]);
        for (int i = this->_size - 1; i >= 1; --i) this->update(i);
    }

    const T &operator[](int k) const { return this->data[k + this->_size]; }
    T at(int k) const { return this->operator[](k); }
    T get(int k) const { return this->operator[](k); }

    void set(int k, T val) {
        assert(0 <= k && k < this->_n);
        k += this->_size;
        this->data[k] = val;
        for (int i = 1; i <= this->_log; ++i) this->update(k >> i);
    }
    void reset(int k) { this->set(k, M::id); }

    T all_prod() const { return this->data[1]; }
    T prod(int a, int b) const {
        assert(0 <= a && b <= this->_n);
        T l = M::id, r = M::id;
        for (a += this->_size, b += this->_size; a < b; a >>= 1, b >>= 1) {
            if (a & 1) l = M::op(l, this->data[a++]);
            if (b & 1) r = M::op(this->data[--b], r);
        }
        return M::op(l, r);
    }

    template <class F>
    int max_right(F f) const {
        return this->max_right(0, f);
    }

    template <class F>
    int max_right(int l, F f) const {
        assert(0 <= l && l <= this->_n);
        assert(f(M::id));
        if (l == this->_n) return this->_n;
        l += this->_size;
        T sm = M::id;
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(M::op(sm, this->data[l]))) {
                while (l < this->_size) {
                    l = (2 * l);
                    if (f(M::op(sm, this->data[l]))) {
                        sm = M::op(sm, this->data[l]);
                        l++;
                    }
                }
                return l - this->_size;
            }
            sm = M::op(sm, this->data[l]);
            l++;
        } while ((l & -l) != l);
        return this->_n;
    }

    int max_right(T x) const { return this->max_right(0, x); }

    int max_right(int r, T x) const {
        return this->max_right(r, [&x](auto y) {
            return !(y < x);
        });
    }

    template <class F>
    int min_left(F f) const {
        return this->min_left(this->_n, f);
    }

    template <class F>
    int min_left(int r, F f) const {
        assert(0 <= r && r <= this->_n);
        assert(f(M::id));
        if (r == 0) return 0;
        r += this->_size;
        T sm = M::id;
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(M::op(this->data[r], sm))) {
                while (r < this->_size) {
                    r = (2 * r + 1);
                    if (f(M::op(this->data[r], sm))) {
                        sm = M::op(this->data[r], sm);
                        r--;
                    }
                }
                return r + 1 - this->_size;
            }
            sm = M::op(this->data[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

    int min_left(T x) const { return this->min_left(this->_n, x); }

    int min_left(int r, T x) const {
        return this->min_left(r, [&x](auto y) {
            return !(y < x);
        });
    }

  private:
    int _n, _size, _log;
    std::vector<T> data;

    void update(int k) { this->data[k] = M::op(this->data[2 * k], this->data[2 * k + 1]); }
};
#line 3 "/home/kuhaku/home/github/algo/lib/template/macro.hpp"
#define FOR(i, m, n) for (int i = (m); i < int(n); ++i)
#define FORR(i, m, n) for (int i = (m)-1; i >= int(n); --i)
#define FORL(i, m, n) for (int64_t i = (m); i < int64_t(n); ++i)
#define rep(i, n) FOR (i, 0, n)
#define repn(i, n) FOR (i, 1, n + 1)
#define repr(i, n) FORR (i, n, 0)
#define repnr(i, n) FORR (i, n + 1, 1)
#define all(s) (s).begin(), (s).end()
#line 3 "/home/kuhaku/home/github/algo/lib/template/sonic.hpp"
struct Sonic {
    Sonic() {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
    }

    constexpr void operator()() const {}
} sonic;
#line 5 "/home/kuhaku/home/github/algo/lib/template/atcoder.hpp"
using ll = int64_t;
using ld = long double;
template <class T, class U>
std::istream &operator>>(std::istream &is, std::pair<T, U> &p) {
    return is >> p.first >> p.second;
}
template <class T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) {
    for (T &i : v) is >> i;
    return is;
}
template <class T, class U>
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &p) {
    return os << '(' << p.first << ',' << p.second << ')';
}
template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    for (auto it = v.begin(); it != v.end(); ++it) {
        os << (it == v.begin() ? "" : " ") << *it;
    }
    return os;
}
template <class Head, class... Tail>
void co(Head &&head, Tail &&...tail) {
    if constexpr (sizeof...(tail) == 0) std::cout << head << '\n';
    else std::cout << head << ' ', co(std::forward<Tail>(tail)...);
}
template <class Head, class... Tail>
void ce(Head &&head, Tail &&...tail) {
    if constexpr (sizeof...(tail) == 0) std::cerr << head << '\n';
    else std::cerr << head << ' ', ce(std::forward<Tail>(tail)...);
}
template <typename T, typename... Args>
auto make_vector(T x, int arg, Args... args) {
    if constexpr (sizeof...(args) == 0) return std::vector<T>(arg, x);
    else return std::vector(arg, make_vector<T>(x, args...));
}
void setp(int n) {
    std::cout << std::fixed << std::setprecision(n);
}
void Yes(bool is_correct = true) {
    std::cout << (is_correct ? "Yes" : "No") << '\n';
}
void No(bool is_not_correct = true) {
    Yes(!is_not_correct);
}
void YES(bool is_correct = true) {
    std::cout << (is_correct ? "YES" : "NO") << '\n';
}
void NO(bool is_not_correct = true) {
    YES(!is_not_correct);
}
void Takahashi(bool is_correct = true) {
    std::cout << (is_correct ? "Takahashi" : "Aoki") << '\n';
}
void Aoki(bool is_not_correct = true) {
    Takahashi(!is_not_correct);
}
#line 6 "a.cpp"

prime_number pn;

struct S {
    static int m;
    ll p;
};

struct Monoid {
    using T = S;
    using value_type = T;
    static constexpr T id = S{1};
    static T op(const T &lhs, const T &rhs) {
        return T{(lhs.p * rhs.p) % S::m};
    }
};

int S::m = 1;

int main(void) {
    int n, m;
    cin >> n >> m;
    S::m = m;

    ll ans = 0;
    segment_tree<Monoid> st(n + 1);
    vector<ll> cnt(n + 1);
    vector<int> q;
    cnt[2]--;
    auto x = pn.prime_factorization(n);
    for (auto p : x) {
        if (p.first == 1)
            continue;
        cnt[p.first] += p.second * 2;
        q.emplace_back(p.first);
    }

    FOR (i, 1, n) {
        auto v = pn.prime_factorization(i);
        for (auto p : v) {
            cnt[p.first] -= p.second;
            q.emplace_back(p.first);
        }

        auto w = pn.prime_factorization(n - i);

        for (auto p : v) {
            cnt[p.first] += p.second * i;
            q.emplace_back(p.first);
        }

        for (auto p : w) {
            cnt[p.first] += p.second * (n - i);
            q.emplace_back(p.first);
        }

        sort(all(q));
        q.erase(unique(all(q)), q.end());
        for (auto x : q) {
            st.set(x, S{pow_mod(x, cnt[x], m)});
        }
        q.clear();

        ans += st.all_prod().p;

        for (auto p : v) {
            cnt[p.first] -= p.second * i;
            q.emplace_back(p.first);
        }

        for (auto p : w) {
            cnt[p.first] -= p.second * (n - i - 1);
            q.emplace_back(p.first);
        }
    }

    co(ans % m);

    return 0;
}
