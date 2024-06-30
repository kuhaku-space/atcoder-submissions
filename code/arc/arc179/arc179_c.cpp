#define PROBLEM ""
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
int cnt = 0;
template <class T, class Comp>
void merge_sort_detail(int l, int r, vector<T> &v, Comp comp) {
    int n = r - l;
    if (n <= 1)
        return;
    int m = (l + r) / 2;
    merge_sort_detail(l, m, v, comp);
    merge_sort_detail(m, r, v, comp);
    vector<T> u(n);
    int i = l, j = m, k = 0;
    while (i < m && j < r) {
        if (comp(v[i], v[j]))
            u[k++] = v[i++];
        else
            u[k++] = v[j++];
    }
    while (i < m) u[k++] = v[i++];
    while (j < r) u[k++] = v[j++];
    for (int i = l; i < r; ++i) v[i] = u[i - l];
}
template <class T, class Comp>
void merge_sort(vector<T> &v, Comp comp) {
    int n = v.size();
    merge_sort_detail(0, n, v, comp);
}
template <class T, class Comp>
int binary_search(T e, vector<T> &v, Comp comp) {
    int n = v.size();
    int l = -1, r = n;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (comp(v[m], e))
            l = m;
        else
            r = m;
    }
    return r;
}
int main(void) {
    int n;
    cin >> n;
    auto comp = [](int x, int y) {
        ++cnt;
        co("?", x, y);
        cout << flush;
        int q;
        cin >> q;
        return q == 1;
    };
    vector<int> a(n);
    iota(all(a), 1);
    merge_sort(a, comp);
    while (a.size() > 1) {
        int x = a.front(), y = a.back();
        co("+", x, y);
        cout << flush;
        int q;
        cin >> q;
        a.pop_back();
        a.erase(a.begin());
        a.emplace(a.begin() + binary_search(q, a, comp), q);
    }
    assert(cnt <= 17450);
    co("!");
    cout << flush;
    return 0;
}
