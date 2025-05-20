// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/bipartitematching
#include <array>
#include <cassert>
#include <concepts>
#include <vector>
/// @brief 2分トライ木
/// @see https://kazuma8128.hatenablog.com/entry/2018/05/06/022654
template <std::integral T = int, int B = 31, bool Multi = false>
struct binary_trie {
  private:
    struct node_t {
        int count;
        std::array<int, 2> ch;
        node_t() : count(), ch{-1, -1} {}
    };
  public:
    constexpr binary_trie() : nodes(1) {}
    T operator[](int k) const {
        assert(0 <= k && k < size());
        T res{};
        int idx = 0;
        for (int b = B - 1; b >= 0; --b) {
            int m = nodes[idx].ch[0] != -1 ? nodes[nodes[idx].ch[0]].count : 0;
            if (k < m) {
                idx = nodes[idx].ch[0];
            } else {
                k -= m;
                res += T(1) << b;
                idx = nodes[idx].ch[1];
            }
        }
        return res;
    }
    T at(int k) const { return operator[](k); }
    T get(int k) const { return operator[](k); }
    T kth_element(int k) const { return operator[](k); }
    constexpr bool empty() const { return nodes.front().count == 0; }
    constexpr int size() const { return nodes.front().count; }
    void insert(T val) {
        if constexpr (!Multi) {
            if (count(val)) return;
        }
        ++nodes[0].count;
        int idx = 0;
        for (int b = B - 1; b >= 0; --b) {
            bool f = val >> b & 1;
            if (nodes[idx].ch[f] == -1) {
                nodes[idx].ch[f] = nodes.size();
                nodes.emplace_back();
            }
            idx = nodes[idx].ch[f];
            ++nodes[idx].count;
        }
    }
    void erase(T val) {
        if (!count(val)) return;
        --nodes[0].count;
        int idx = 0;
        for (int b = B - 1; b >= 0; --b) {
            bool f = val >> b & 1;
            idx = nodes[idx].ch[f];
            --nodes[idx].count;
        }
    }
    T min_element(T bias = 0) const {
        assert(!empty());
        T res{};
        int idx = 0;
        for (int b = B - 1; b >= 0; --b) {
            bool f = bias >> b & 1;
            f ^= nodes[idx].ch[f] == -1 || nodes[nodes[idx].ch[f]].count == 0;
            res += T(f) << b;
            idx = nodes[idx].ch[f];
        }
        return res;
    }
    T max_element(T bias = 0) const { return min_element(~bias); }
    int count_less(T val) const {
        int res = 0, idx = 0;
        for (int b = B - 1; b >= 0; --b) {
            bool f = val >> b & 1;
            if (f && nodes[idx].ch[0] != -1) res += nodes[nodes[idx].ch[0]].count;
            idx = nodes[idx].ch[val >> b & 1];
            if (idx == -1) break;
        }
        return res;
    }
    int count(T val) const {
        int idx = 0;
        for (int b = B - 1; b >= 0; --b) {
            idx = nodes[idx].ch[val >> b & 1];
            if (idx == -1) return 0;
        }
        return nodes[idx].count;
    }
    int count(T l, T r) const { return count_less(r) - count_less(l); }
  private:
    std::vector<node_t> nodes;
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
int main(void) {
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    rep (i, n - 1) a[i + 1] ^= a[i];
    binary_trie<int, 30, true> bt;
    rep (i, n - 1) bt.insert(a[i]);
    vector<int> ans(n);
    int x = 0;
    rep (i, n - 1) {
        ans[i] = bt.min_element(x);
        x = ans[i];
        bt.erase(x);
    }
    ans[n - 1] = a[n - 1];
    repr (i, n - 1) ans[i + 1] ^= ans[i];
    co(ans);
    return 0;
}
