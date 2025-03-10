// competitive-verifier: PROBLEM
#include <cassert>
#include <functional>
#include <queue>
#include <vector>
#include <utility>
/**
 * @brief 削除可能優先度付きキュー
 *
 * @tparam T
 */
template <class T, class Comp = std::less<>>
struct erasable_priority_queue {
    bool empty() const { return a.empty(); }
    int size() const { return a.size() - b.size(); }
    T top() const { return a.top(); }
    void insert(const T &x) { a.push(x); }
    void insert(T &&x) { a.push(std::move(x)); }
    void push(const T &x) { a.push(x); }
    void push(T &&x) { a.push(std::move(x)); }
    template <typename... Args>
    void emplace(Args &&...args) {
        a.emplace(std::forward<Args>(args)...);
    }
    void pop() { erase(a.top()); }
    void erase(T x) {
        b.emplace(x);
        while (!b.empty() && a.top() == b.top()) { a.pop(), b.pop(); }
    }
  private:
    std::priority_queue<T, std::vector<T>, Comp> a, b;
};
template <typename T, class Comp, class RComp>
struct priority_k_sum {
    priority_k_sum(int k) : k(k), sum() { assert(k >= 0); }
    T query() const { return sum; }
    void insert(T x) {
        sum += x;
        in.emplace(x);
        modify();
    }
    void erase(T x) {
        assert(size());
        if (!in.empty() && !Comp()(in.top(), x)) sum -= x, in.erase(x);
        else out.erase(x);
        modify();
    }
    void set_k(int x) {
        assert(x >= 0);
        k = x;
        modify();
    }
    int get_k() const { return k; }
    int size() const { return in.size() + out.size(); }
  private:
    int k;
    T sum;
    erasable_priority_queue<T, Comp> in;
    erasable_priority_queue<T, RComp> out;
    void modify() {
        while (in.size() < k && !out.empty()) {
            auto p = out.top();
            out.pop();
            sum += p, in.emplace(p);
        }
        while (in.size() > k) {
            auto p = in.top();
            in.pop();
            sum -= p, out.emplace(p);
        }
    }
};
template <typename T>
using maximum_sum = priority_k_sum<T, std::greater<T>, std::less<T>>;
template <typename T>
using minimum_sum = priority_k_sum<T, std::less<T>, std::greater<T>>;
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
    int n, m;
    cin >> n >> m;
    array<vector<ll>, 3> v = {};
    rep (i, n) {
        int t, x;
        cin >> t >> x;
        v[t].emplace_back(x);
    }
    auto [a, b, c] = v;
    maximum_sum<ll> ms(m);
    for (auto x : a) ms.insert(x);
    ll ans = ms.query();
    sort(all(c));
    reverse(all(c));
    priority_queue<ll> pq;
    for (auto x : b) pq.emplace(x);
    for (auto x : c) {
        rep (i, x) {
            if (pq.empty())
                break;
            ms.insert(pq.top());
            pq.pop();
        }
        ms.set_k(--m);
        if (m == 0)
            break;
        chmax(ans, ms.query());
    }
    co(ans);
    return 0;
}
