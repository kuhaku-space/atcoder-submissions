// competitive-verifier: PROBLEM
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
    int n, k;
    cin >> n >> k;
    vector<ll> a(n), b(n);
    cin >> a >> b;
    vector<int> ord(n);
    iota(all(ord), 0);
    sort(all(ord), [&](int x, int y) {
        return a[x] < a[y];
    });
    minimum_sum<ll> ms(k);
    ll ans = INF;
    rep (i, n) {
        ms.insert(b[ord[i]]);
        if (i >= k - 1) {
            chmin(ans, a[ord[i]] * ms.query());
        }
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
