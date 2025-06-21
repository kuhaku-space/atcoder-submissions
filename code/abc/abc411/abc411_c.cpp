// competitive-verifier: PROBLEM
#pragma GCC optimize("Ofast,fast-math,unroll-all-loops")
#include <bits/stdc++.h>
#if !defined(ATCODER) && !defined(EVAL)
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
#define FORR(i, m, n) for (int i = (m) - 1; i >= int(n); --i)
#define FORL(i, m, n) for (std::int64_t i = (m); i < std::int64_t(n); ++i)
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
struct increment_impl {
    template <class T>
    const increment_impl &operator>>(std::vector<T> &v) const {
        for (auto &x : v) ++x;
        return *this;
    }
} Inc;
struct decrement_impl {
    template <class T>
    const decrement_impl &operator>>(std::vector<T> &v) const {
        for (auto &x : v) --x;
        return *this;
    }
} Dec;
struct sort_impl {
    template <class T>
    const sort_impl &operator>>(std::vector<T> &v) const {
        std::sort(v.begin(), v.end());
        return *this;
    }
} Sort;
struct unique_impl {
    template <class T>
    const unique_impl &operator>>(std::vector<T> &v) const {
        std::sort(v.begin(), v.end());
        v.erase(std::unique(v.begin(), v.end()), v.end());
        return *this;
    }
} Uniq;
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
/// @brief 区間をsetで管理するテク
template <class T>
struct range_set {
    range_set() : intervals(), len() {}
    std::set<std::pair<T, T>>::const_iterator begin() const { return intervals.begin(); }
    std::set<std::pair<T, T>>::const_iterator end() const { return intervals.end(); }
    int size() const { return intervals.size(); }
    T length() const { return len; }
    std::pair<T, T> get(T x) const {
        auto it = intervals.lower_bound(std::make_pair(x, x));
        if (it == intervals.end() || !contains(x, *it)) return std::make_pair(inf, inf);
        return std::make_pair(it->second, it->first);
    }
    bool contains(T x) const {
        auto it = intervals.lower_bound(std::make_pair(x, x));
        return it != intervals.end() && contains(x, *it);
    }
    bool same(T x, T y) const {
        auto it = intervals.lower_bound(std::make_pair(x, x));
        return it != intervals.end() && contains(x, *it) && contains(y, *it);
    }
    std::pair<T, T> insert(T x, T y) {
        assert(x <= y);
        if (x == y) return std::make_pair(x, y);
        auto it = intervals.lower_bound(std::make_pair(x, std::numeric_limits<T>::lowest()));
        while (it != intervals.end() && it->second <= y) {
            len -= it->first - it->second;
            x = std::min(x, it->second);
            y = std::max(y, it->first);
            it = intervals.erase(it);
        }
        len += y - x;
        intervals.emplace(y, x);
        return std::make_pair(x, y);
    }
    std::pair<T, T> insert(T x) { return insert(x, x + 1); }
    void erase(T x, T y) {
        assert(x <= y);
        if (x == y) return;
        auto it = intervals.lower_bound(std::make_pair(x, x));
        if (it == intervals.end()) return;
        if (contains(x, *it)) {
            T l = it->second, r = it->first;
            intervals.erase(it);
            if (l < x) intervals.emplace(x, l);
            if (x < r) intervals.emplace(r, x);
        }
        it = intervals.lower_bound(std::make_pair(x, x));
        while (it != intervals.end()) {
            if (y <= it->second) break;
            if (y < it->first) {
                T r = it->first;
                len -= y - it->second;
                intervals.erase(it);
                intervals.emplace(r, y);
                break;
            }
            len -= it->first - it->second;
            it = intervals.erase(it);
        }
    }
    void erase(T x) { erase(x, x + 1); }
  private:
    static constexpr T inf = std::numeric_limits<T>::max();
    std::set<std::pair<T, T>> intervals;
    T len;
    static bool contains(T x, const std::pair<T, T> &p) { return p.second <= x && x < p.first; }
};
/// @brief flip set
template <class T>
struct flip_set {
    flip_set() : data() {}
    const auto begin() const { return data.begin(); }
    auto begin() { return data.begin(); }
    const auto end() const { return data.end(); }
    auto end() { return data.end(); }
    bool empty() const { return data.empty(); }
    int size() const { return data.size(); }
    bool contains(const T &x) const { return data.count(x); }
    bool contains(T &&x) const { return data.count(std::move(x)); }
    bool flip(const T &x) {
        if (data.count(x)) return data.erase(x), false;
        else return data.emplace(x), true;
    }
    bool flip(T &&x) {
        if (data.count(x)) return data.erase(std::move(x)), false;
        else return data.emplace(x), true;
    }
  private:
    std::set<T> data;
};
int main(void) {
    int n, q;
    cin >> n >> q;
    vector<int> a(q);
    cin >> a;
    flip_set<int> fs;
    range_set<int> rs;
    for (int x : a) {
        --x;
        fs.flip(x);
        if (fs.contains(x)) {
            rs.insert(x, x + 1);
        } else {
            rs.erase(x, x + 1);
        }
        co(rs.size());
    }
    return 0;
}
