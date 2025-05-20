// competitive-verifier: PROBLEM
#include <cassert>
#include <functional>
#include <utility>
#include <queue>
/// @brief 削除可能優先度付きキュー
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
    void erase(const T &x) {
        b.push(x);
        while (!b.empty() && a.top() == b.top()) { a.pop(), b.pop(); }
    }
    void erase(T &&x) {
        b.push(std::move(x));
        while (!b.empty() && a.top() == b.top()) { a.pop(), b.pop(); }
    }
  private:
    std::priority_queue<T, std::vector<T>, Comp> a, b;
};
template <typename T, class Comp, class RComp>
struct priority_k_sum {
    priority_k_sum(int k) : _k(k), _sum() { assert(_k >= 0); }
    int size() const { return in.size() + out.size(); }
    T query() const { return _sum; }
    T sum() const { return _sum; }
    int get_k() const { return _k; }
    void set_k(int x) {
        assert(x >= 0);
        _k = x;
        modify();
    }
    void insert(const T &x) {
        _sum += x, in.emplace(x);
        modify();
    }
    void insert(T &&x) {
        _sum += x, in.emplace(std::move(x));
        modify();
    }
    void erase(const T &x) {
        assert(size());
        if (!in.empty() && !Comp()(in.top(), x)) _sum -= x, in.erase(x);
        else out.erase(x);
        modify();
    }
    void erase(T &&x) {
        assert(size());
        if (!in.empty() && !Comp()(in.top(), x)) _sum -= x, in.erase(std::move(x));
        else out.erase(std::move(x));
        modify();
    }
  private:
    int _k;
    T _sum;
    erasable_priority_queue<T, Comp> in;
    erasable_priority_queue<T, RComp> out;
    void modify() {
        while (in.size() < _k && !out.empty()) {
            auto p = out.top();
            _sum += p, in.emplace(p);
            out.pop();
        }
        while (in.size() > _k) {
            auto p = in.top();
            _sum -= p, out.emplace(p);
            in.pop();
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
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n);
    cin >> a;
    minimum_sum<ll> pq(k);
    vector<ll> ans;
    for (int i = 0; i < n; ++i) {
        pq.insert(a[i]);
        if (i >= m)
            pq.erase(a[i - m]);
        if (pq.size() == m) {
            ans.emplace_back(pq.query());
        }
    }
    co(ans);
    return 0;
}
