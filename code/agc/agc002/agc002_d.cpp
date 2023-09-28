#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/home/github/algo/lib/template/template.hpp"
#pragma GCC target("sse4.2,avx2,bmi2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
template <class T, class U>
bool chmax(T &a, const U &b) {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U &b) {
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
#line 2 "/home/kuhaku/home/github/algo/lib/tree/partially_persistent_union_find.hpp"

/**
 * @brief 部分永続Union-Find
 *
 */
struct partially_persistent_union_find {
    partially_persistent_union_find(int _n)
        : _now(0), _data(_n, std::vector<std::pair<int, int>>(1, {0, -1})) {}

    int root(int x, int t) const {
        auto p = _data[x].back();
        if (p.first > t || p.second < 0) return x;
        return root(p.second, t);
    }
    int get_root(int x, int t) const { return root(x, t); }

    bool is_root(int x, int t) const {
        return _data[x].back().first > t || _data[x].back().second < 0;
    }

    bool same(int x, int y, int t) const { return root(x, t) == root(y, t); }
    bool is_same(int x, int y, int t) const { return same(x, y, t); }

    int size(int x, int t) const {
        x = root(x, t);
        return -std::prev(std::upper_bound(_data[x].begin(), _data[x].end(),
                                           std::pair<int, int>{t, _data.size()}))
                    ->second;
    }
    int get_size(int x, int t) const { return size(x, t); }

    int unite(int x, int y) {
        ++_now;
        x = root(x, _now), y = root(y, _now);
        if (x == y) return false;
        auto p = _data[x].back(), q = _data[y].back();
        if (p.second > q.second) std::swap(x, y), std::swap(p, q);
        _data[x].emplace_back(_now, p.second + q.second);
        _data[y].emplace_back(_now, x);
        return true;
    }

  private:
    int _now;
    std::vector<std::vector<std::pair<int, int>>> _data;
};
#line 4 "a.cpp"

int main(void) {
    int n, m;
    cin >> n >> m;
    partially_persistent_union_find uf(n);
    vector<int> v;
    rep (i, m) {
        int a, b;
        cin >> a >> b;
        uf.unite(a - 1, b - 1);
    }

    int q;
    cin >> q;
    while (q--) {
        int x, y, z;
        cin >> x >> y >> z;
        --x, --y;
        auto check = [&](int mid) {
            if (uf.same(x, y, mid))
                return uf.size(x, mid) >= z;
            return uf.size(x, mid) + uf.size(y, mid) >= z;
        };
        int l = m, r = 0;
        while (abs(l - r) > 1) {
            int mid = (l + r) / 2;
            (check(mid) ? l : r) = mid;
        }
        co(l);
    }

    return 0;
}
