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
constexpr double PI = M_PI;
#line 2 "/home/kuhaku/home/github/algo/lib/math/pow.hpp"

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
#line 2 "/home/kuhaku/home/github/algo/lib/segment_tree/monoid.hpp"

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
    static constexpr T id = T(0);
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
#line 4 "/home/kuhaku/home/github/algo/lib/segment_tree/segment_tree.hpp"

/**
 * @brief セグメント木
 * @details [参考](https://noshi91.hatenablog.com/entry/2020/04/22/212649)
 *
 * @tparam M モノイド
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
    void reset(int k) { this->set(k, M::id); }

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
#line 3 "/home/kuhaku/home/github/algo/lib/template/atcoder.hpp"
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
template <class T, class U>
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &p) {
    return os<<'('<<p.first<< ','<<p.second<<')';
}
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
void Yes(bool is_correct=true) { std::cout<<(is_correct?"Yes":"No")<<std::endl; }
void No(bool is_not_correct=true) { Yes(!is_not_correct); }
void YES(bool is_correct=true) { std::cout<<(is_correct?"YES":"NO")<<std::endl; }
void NO(bool is_not_correct=true) { YES(!is_not_correct); }
void Takahashi(bool is_correct=true) { std::cout<<(is_correct?"Takahashi":"Aoki")<<std::endl; }
void Aoki(bool is_not_correct=true) { Takahashi(!is_not_correct); }
#line 4 "a.cpp"

template <class T>
struct Gcd {
    using value_type = T;
    static constexpr T id = T();
    static constexpr T op(const T &lhs, const T &rhs) {
        return lhs == Gcd::id ? rhs : std::gcd(lhs, rhs);
    }
};

int main(void) {
    sonic();
    int n, q;
    cin >> n >> q;
    vector<int> a(n), b(n);
    cin >> a >> b;
    segment_tree<Gcd<int>> st1(n - 1), st2(n - 1);
    rep(i, n - 1) {
        st1.set(i, abs(a[i] - a[i + 1]));
        st2.set(i, abs(b[i] - b[i + 1]));
    }

    rep(_, q) {
        int x, y, z, w;
        cin >> x >> y >> z >> w;
        int p = st1.prod(x - 1, y - 1);
        int q = st2.prod(z - 1, w - 1);
        int r = Gcd<int>::op(p, q);
        int ans = Gcd<int>::op(a[x - 1] + b[z - 1], r);
        co(ans);
    }

    return 0;
}
