#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/home/github/algo/lib/binary_tree/fenwick_tree.hpp"
#include <cassert>
#include <vector>

/**
 * @brief フェニック木
 * @see http://hos.ac/slides/20140319_bit.pdf
 *
 * @tparam T
 */
template <class T>
struct fenwick_tree {
    fenwick_tree() : _size(), data() {}
    fenwick_tree(int n) : _size(n + 1), data(n + 1) {}
    template <class U>
    fenwick_tree(const std::vector<U> &v) : _size((int)v.size() + 1), data((int)v.size() + 1) {
        build(v);
    }

    T operator[](int i) const { return sum(i + 1) - sum(i); }
    T at(int k) const { return operator[](k); }
    T get(int k) const { return operator[](k); }

    template <class U>
    void build(const std::vector<U> &v) {
        for (int i = 0, n = v.size(); i < n; ++i) add(i, v[i]);
    }

    /**
     * @brief v[k] = val
     *
     * @param k index of array
     * @param val new value
     * @return void
     */
    void update(int k, T val) { add(k, val - at(k)); }
    /**
     * @brief v[k] += val
     *
     * @param k index of array
     * @param val new value
     * @return void
     */
    void add(int k, T val) {
        assert(0 <= k && k < _size);
        for (++k; k < _size; k += k & -k) data[k] += val;
    }
    /**
     * @brief chmax(v[k], val)
     *
     * @param k index of array
     * @param val new value
     * @return bool
     */
    bool chmax(int k, T val) {
        if (at(k) >= val) return false;
        update(k, val);
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
        if (at(k) <= val) return false;
        update(k, val);
        return true;
    }

    /**
     * @brief v[0] + ... + v[n - 1]
     *
     * @return T
     */
    T all_sum() const { return sum(_size); }
    /**
     * @brief v[0] + ... + v[k - 1]
     *
     * @param k index of array
     * @return T
     */
    T sum(int k) const {
        assert(0 <= k && k <= _size);
        T res = 0;
        for (; k > 0; k -= k & -k) res += data[k];
        return res;
    }
    /**
     * @brief v[a] + ... + v[b - 1]
     *
     * @param a first index of array
     * @param b last index of array
     * @return T
     */
    T sum(int a, int b) const { return a < b ? sum(b) - sum(a) : 0; }

    /**
     * @brief binary search on fenwick_tree
     *
     * @param val target value
     * @return int
     */
    int lower_bound(T val) const {
        if (val <= 0) return 0;
        int k = 1;
        while (k < _size) k <<= 1;
        int res = 0;
        for (; k > 0; k >>= 1) {
            if (res + k < _size && data[res + k] < val) val -= data[res += k];
        }
        return res;
    }

  private:
    int _size;
    std::vector<T> data;
};
#line 2 "/home/kuhaku/home/github/algo/lib/binary_tree/fenwick_tree_raq.hpp"

/**
 * @brief フェニック木（区間加算、区間総和）
 *
 * @tparam T
 */
template <class T>
struct fenwick_tree_raq {
    fenwick_tree_raq() = default;
    fenwick_tree_raq(int n) : p(n + 1), q(n + 1) {}

    auto operator[](int i) const { return sum(i + 1) - sum(i); }
    auto at(int k) const { return operator[](k); }

    template <class U>
    void build(const std::vector<U> &v) {
        for (int i = 0, n = v.size(); i < n; ++i) add(i, v[i]);
    }

    /**
     * @brief v[k] = val
     *
     * @param k index of array
     * @param val new value
     */
    void update(int k, T val) { add(k, k + 1, val - at(k)); }

    /**
     * @brief v[k] += val
     *
     * @param k index of array
     * @param val
     */
    void add(int k, T val) { add(k, k + 1, val); }
    /**
     * @brief v[a ... b-1] += val
     *
     * @param a first index of array
     * @param b last index of array
     * @param val
     */
    void add(int a, int b, T val) {
        p.add(a, -val * a);
        p.add(b, val * b);
        q.add(a, val);
        q.add(b, -val);
    }

    /**
     * @brief v[0] + ... v[k - 1]
     *
     * @param k index of array
     * @return T
     */
    T sum(int k) const { return p.sum(k) + q.sum(k) * k; }
    /**
     * @brief v[a] + ... + v[b - 1]
     *
     * @param a first index of array
     * @param b last index of array
     * @return T
     */
    T sum(int a, int b) const { return sum(b) - sum(a); }

  private:
    fenwick_tree<T> p, q;
};
#line 2 "/home/kuhaku/home/github/algo/lib/template/template.hpp"
#pragma GCC target("sse4.2,avx2,bmi2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
template <class T, class U>
constexpr bool chmax(T &a, const U &b) {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
constexpr bool chmin(T &a, const U &b) {
    return (T)b < a ? a = (T)b, true : false;
}
constexpr std::int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr double EPS = 1e-7;
constexpr double PI = M_PI;
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
        std::cout << std::fixed << std::setprecision(20);
    }

    constexpr void operator()() const {}
} sonic;
#line 5 "/home/kuhaku/home/github/algo/lib/template/atcoder.hpp"
using namespace std;
using ll = std::int64_t;
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
#line 4 "a.cpp"

int main(void) {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    cin >> a >> b;
    fenwick_tree_raq<ll> ft(n);
    rep (i, n) ft.update(i, a[i]);
    rep (i, m) {
        int x = b[i];
        ll k = ft[x];
        ll r = k % n;
        ft.update(x, 0);
        ft.add(0, n, k / n);
        if (x + r < n) {
            ft.add(x + 1, x + r + 1, 1);
        } else {
            ft.add(x + 1, n, 1);
            ft.add(0, r - (n - x - 1), 1);
        }
    }
    vector<ll> ans(n);
    rep (i, n) ans[i] = ft[i];
    co(ans);

    return 0;
}
