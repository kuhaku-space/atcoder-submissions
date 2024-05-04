#line 1 "a.cpp"
#define PROBLEM ""
#line 1 "/home/kuhaku/home/github/algo/lib/graph/grid.hpp"
#include <cstdint>
#include <utility>

namespace internal {

template <int Idx>
struct grid_impl {
    template <class Head, class... Tail>
    constexpr grid_impl(Head &&head, Tail &&...tail)
        : limit(head), impl(std::forward<Tail>(tail)...) {}

    template <class Head, class... Tail>
    constexpr bool in_field(Head x, Tail &&...tail) const {
        return 0 <= x && x < limit && impl.in_field(std::forward<Tail>(tail)...);
    }

    template <class Head, class... Tail>
    constexpr std::int64_t flatten(Head x, Tail &&...tail) const {
        return x + limit * impl.flatten(std::forward<Tail>(tail)...);
    }

  private:
    std::int64_t limit;
    grid_impl<Idx - 1> impl;
};

template <>
struct grid_impl<0> {
    constexpr grid_impl() {}

    constexpr bool in_field() const { return true; }

    constexpr std::int64_t flatten() const { return 0; }
};

}  // namespace internal

template <int Idx>
struct Grid {
    template <class... Args, std::enable_if_t<(sizeof...(Args) == Idx)> * = nullptr>
    constexpr Grid(Args &&...args) : entity(std::forward<Args>(args)...) {}

    template <class... Args, std::enable_if_t<(sizeof...(Args) == Idx)> * = nullptr>
    constexpr bool in_field(Args &&...args) const {
        return entity.in_field(std::forward<Args>(args)...);
    }

    template <class... Args, std::enable_if_t<(sizeof...(Args) == Idx)> * = nullptr>
    constexpr std::int64_t flatten(Args &&...args) const {
        return entity.flatten(std::forward<Args>(args)...);
    }

  private:
    internal::grid_impl<Idx> entity;
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
    int h, w;
    cin >> h >> w;
    vector<string> s(h);
    cin >> s;

    int sx = 0, sy = 0;
    rep (i, h) {
        rep (j, w) {
            if (s[i][j] == 'S')
                sx = i, sy = j;
        }
    }

    int n;
    cin >> n;
    vector a(h, vector(w, 0));
    rep (i, n) {
        int r, c, e;
        cin >> r >> c >> e;
        chmax(a[r - 1][c - 1], e);
    }

    Grid<2> grid(h, w);
    vector<int> dx = {1, -1, 0, 0}, dy = {0, 0, 1, -1};
    vector visited(h, vector(w, false));
    priority_queue<tuple<int, int, int>> pq;
    visited[sx][sy] = true;
    if (a[sx][sy])
        pq.emplace(a[sx][sy], sx, sy);
    while (!pq.empty()) {
        auto [z, x, y] = pq.top();
        pq.pop();
        rep (k, 4) {
            int nx = x + dx[k], ny = y + dy[k];
            if (!grid.in_field(nx, ny) || s[nx][ny] == '#')
                continue;
            if (!visited[nx][ny]) {
                visited[nx][ny] = true;
                chmax(a[nx][ny], z - 1);
                if (a[nx][ny]) {
                    pq.emplace(a[nx][ny], nx, ny);
                }
            } else if (chmax(a[nx][ny], z - 1)) {
                pq.emplace(a[nx][ny], nx, ny);
            }
        }
    }

    // rep (i, h) ce(a[i]);

    rep (i, h) {
        rep (j, w) {
            if (s[i][j] == 'T')
                Yes(visited[i][j]);
        }
    }

    return 0;
}
