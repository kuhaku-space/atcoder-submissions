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
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
constexpr double PI = M_PI;
#line 2 "range_set.hpp"

template <class T>
struct range_set {
    range_set() = default;

    std::pair<T, T> get(T x) const {
        auto it = intervals.lower_bound(std::make_pair(x, x));
        if (it == std::end(intervals) || !contains(x, *it))
            return std::make_pair(inf, inf);
        return std::make_pair(it->second, it->first);
    }

    bool contains(T x) const {
        auto it = intervals.lower_bound(std::make_pair(x, x));
        return it != std::end(intervals) && contains(x, *it);
    }

    bool same(T x, T y) const {
        auto it = intervals.lower_bound(std::make_pair(x, x));
        return it != std::end(intervals) && contains(x, *it) && contains(y, *it);
    }

    std::pair<T, T> insert(T x, T y) {
        assert(x < y);
        auto it = intervals.lower_bound(std::make_pair(x, std::numeric_limits<T>::lowest()));
        while (it != std::end(intervals) && it->second <= y) {
            x = std::min(x, it->second);
            y = std::max(y, it->first);
            it = intervals.erase(it);
        }
        intervals.emplace(y, x);
        return std::make_pair(x, y);
    }

    std::pair<T, T> insert(T x) {
        return insert(x, x + 1);
    }

    void erase(T x, T y) {
        assert(x < y);
        auto it = intervals.lower_bound(std::make_pair(x, x));
        if (it == std::end(intervals))
            return;
        if (it->second != x) {
            T l = it->second, r = it->first;
            intervals.erase(it);
            intervals.emplace(x, l);
            intervals.emplace(r, x);
        }
        it = intervals.lower_bound(std::make_pair(x, x));
        while (it != std::end(intervals)) {
            if (y <= it->second)
                break;
            if (y < it->first) {
                T r = it->first;
                intervals.erase(it);
                intervals.emplace(r, y);
                break;
            }
            it = intervals.erase(it);
        }
    }

    void erase(T x) {
        erase(x, x + 1);
    }

  private:
    static constexpr T inf = std::numeric_limits<T>::max();
    std::set<std::pair<T, T>> intervals;

    static bool contains(T x, const std::pair<T, T> &p) {
        return p.second <= x && x < p.first;
    }
};
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
void setp(int n) {
    std::cout << std::fixed << std::setprecision(n);
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
    int h, w, n, m;
    cin >> h >> w >> n >> m;
    vector<vector<int>> a(h), b(w), c(h), d(w);
    rep (i, n) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        a[x].emplace_back(y);
        b[y].emplace_back(x);
    }
    rep (i, m) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        c[x].emplace_back(y);
        d[y].emplace_back(x);
    }

    vector f(h, vector(w, false));
    rep (i, h) {
        range_set<int> rs;
        rs.insert(0, w);
        for (auto y : c[i]) rs.erase(y);
        set<pair<int, int>> st;
        for (auto y : a[i]) st.emplace(rs.get(y));
        for (auto p : st) {
            FOR (j, p.first, p.second) f[i][j] = true;
        }
    }
    rep (j, w) {
        range_set<int> rs;
        rs.insert(0, h);
        for (auto x : d[j]) rs.erase(x);
        set<pair<int, int>> st;
        for (auto x : b[j]) st.emplace(rs.get(x));
        for (auto p : st) {
            // ce(p.first, p.second);
            FOR (i, p.first, p.second) f[i][j] = true;
        }
    }

    int ans = 0;
    rep (i, h) {
        rep (j, w) ans += f[i][j];
    }
    co(ans);

    return 0;
}
