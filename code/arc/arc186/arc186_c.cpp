// competitive-verifier: PROBLEM
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
    T operator[](int i) const { return sum(i, i + 1); }
    T at(int k) const { return operator[](k); }
    T get(int k) const { return operator[](k); }
    template <class U>
    void build(const std::vector<U> &v) {
        for (int i = 0, n = v.size(); i < n; ++i) data[i + 1] = v[i];
        for (int i = 1; i < _size; ++i) {
            if (i + (i & -i) < _size) data[i + (i & -i)] += data[i];
        }
    }
    void set(int k, T val) { add(k, val - at(k)); }
    void update(int k, T val) { set(k); }
    void add(int k, T val) {
        assert(0 <= k && k < _size - 1);
        for (++k; k < _size; k += k & -k) data[k] += val;
    }
    bool chmax(int k, T val) {
        if (at(k) >= val) return false;
        set(k, val);
        return true;
    }
    bool chmin(int k, T val) {
        if (at(k) <= val) return false;
        set(k, val);
        return true;
    }
    T all_prod() const { return prod(_size - 1); }
    T prod(int k) const { return sum(k); }
    T prod(int a, int b) const { return sum(a, b); }
    T all_sum() const { return sum(_size - 1); }
    T sum(int k) const {
        assert(0 <= k && k < _size);
        T res = 0;
        for (; k > 0; k -= k & -k) res += data[k];
        return res;
    }
    T sum(int a, int b) const {
        assert(0 <= a && a <= b && b < _size);
        T res = T();
        while (a != b) {
            if (a < b) {
                res += data[b];
                b -= b & -b;
            } else {
                res -= data[a];
                a -= a & -a;
            }
        }
        return res;
    }
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
#ifdef ATCODER
#pragma GCC target("sse4.2,avx512f,avx512dq,avx512ifma,avx512cd,avx512bw,avx512vl,bmi2")
#endif
#pragma GCC optimize("Ofast,fast-math,unroll-all-loops")
#include <bits/stdc++.h>
#ifndef ATCODER
#pragma GCC target("sse4.2,avx2,bmi2")
#endif
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
constexpr double PI = 3.14159265358979323846;
#define FOR(i, m, n) for (int i = (m); i < int(n); ++i)
#define FORR(i, m, n) for (int i = (m)-1; i >= int(n); --i)
#define FORL(i, m, n) for (int64_t i = (m); i < int64_t(n); ++i)
#define rep(i, n) FOR (i, 0, n)
#define repn(i, n) FOR (i, 1, n + 1)
#define repr(i, n) FORR (i, n, 0)
#define repnr(i, n) FORR (i, n + 1, 1)
#define all(s) (s).begin(), (s).end()
struct Sonic {
    Sonic() {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
        std::cout << std::fixed << std::setprecision(20);
    }
    constexpr void operator()() const {}
} sonic;
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
    for (auto it = v.begin(); it != v.end(); ++it) os << (it == v.begin() ? "" : " ") << *it;
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
void Yes(bool is_correct = true) { std::cout << (is_correct ? "Yes\n" : "No\n"); }
void No(bool is_not_correct = true) { Yes(!is_not_correct); }
void YES(bool is_correct = true) { std::cout << (is_correct ? "YES\n" : "NO\n"); }
void NO(bool is_not_correct = true) { YES(!is_not_correct); }
void Takahashi(bool is_correct = true) { std::cout << (is_correct ? "Takahashi" : "Aoki") << '\n'; }
void Aoki(bool is_not_correct = true) { Takahashi(!is_not_correct); }
template <typename T, typename Comp = std::less<T>, typename RComp = std::greater<T>>
struct priority_k_sum {
    priority_k_sum(int k) : k(k), sum() {
        assert(k >= 0);
    }
    T query() const {
        return sum;
    }
    void insert(T x) {
        sum += x;
        in.emplace(x);
        modify();
    }
    void erase(T x) {
        assert(size());
        if (!in.empty() && in.top() == x)
            sum -= x, in.pop();
        else if (!in.empty() && RComp()(in.top(), x))
            sum -= x, d_in.emplace(x);
        else
            d_out.emplace(x);
        modify();
    }
    void set_k(int x) {
        assert(x >= 0);
        k = x;
        modify();
    }
    int get_k() const {
        return k;
    }
    int size() const {
        return (int)in.size() + (int)out.size() - (int)d_in.size() - (int)d_out.size();
    }
  private:
    int k;
    T sum;
    std::priority_queue<T, std::vector<T>, Comp> in, d_in;
    std::priority_queue<T, std::vector<T>, RComp> out, d_out;
    void modify() {
        while ((int)in.size() - (int)d_in.size() < k && !out.empty()) {
            auto p = out.top();
            out.pop();
            if (!d_out.empty() && p == d_out.top())
                d_out.pop();
            else
                sum += p, in.emplace(p);
        }
        while ((int)in.size() - (int)d_in.size() > k) {
            auto p = in.top();
            in.pop();
            if (!d_in.empty() && p == d_in.top())
                d_in.pop();
            else
                sum -= p, out.emplace(p);
        }
        while (!d_in.empty() && in.top() == d_in.top()) in.pop(), d_in.pop();
    }
};
template <typename T>
using maximum_sum = priority_k_sum<T, std::greater<T>, std::less<T>>;
template <typename T>
using minimum_sum = priority_k_sum<T, std::less<T>, std::greater<T>>;
void solve() {
    int n, m;
    cin >> n >> m;
    vector<ll> v(n), p(n);
    rep (i, n) cin >> v[i] >> p[i];
    vector<int> ord;
    rep (i, n) {
        ord.emplace_back(i);
    }
    sort(all(ord), [&](int x, int y) {
        if (v[x] == v[y])
            return p[x] > p[y];
        return v[x] > v[y];
    });
    ll ans = 0;
    fenwick_tree<ll> ft1(n), ft2(n);
    rep (i, ord.size()) {
        int x = ord[i];
        ft1.set(i, p[x] - 1);
        ft2.set(i, max(0l, v[x] - p[x]));
    }
    minimum_sum<ll> ms(m - 1);
    rep (i, ord.size()) {
        if (ms.size() >= m - 1)
            chmax(ans, ft2.sum(i, ord.size()) - ms.query());
        int x = ord[i];
        ms.insert(p[x] - 1);
    }
    co(ans);
}
int main(void) {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
