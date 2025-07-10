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
/// @brief めぐる式二分探索
template <class T, class F>
std::int64_t meguru_binary_search(T ok, T ng, F check) {
    while (std::abs(ok - ng) > 1) {
        T mid = std::midpoint(ok, ng);
        (check(mid) ? ok : ng) = mid;
    }
    return ok;
}
/// @brief 座標圧縮
template <class T>
struct coordinate_compression {
    coordinate_compression() = default;
    coordinate_compression(const std::vector<T> &_data) : data(_data) { build(); }
    const T &operator[](int i) const { return data[i]; }
    T front() const { return data.front(); }
    T back() const { return data.back(); }
    void add(T x) { data.emplace_back(x); }
    void build() {
        std::sort(data.begin(), data.end());
        data.erase(std::unique(data.begin(), data.end()), data.end());
    }
    bool exists(T x) const {
        auto it = std::lower_bound(data.begin(), data.end(), x);
        return it != data.end() && *it == x;
    }
    int get(T x) const { return std::distance(data.begin(), std::lower_bound(data.begin(), data.end(), x)); }
    int lower_bound(T x) const { return std::distance(data.begin(), std::lower_bound(data.begin(), data.end(), x)); }
    int upper_bound(T x) const { return std::distance(data.begin(), std::upper_bound(data.begin(), data.end(), x)); }
    std::vector<int> compress(const std::vector<T> &v) const {
        int n = v.size();
        std::vector<int> res(n);
        for (int i = 0; i < n; ++i) res[i] = get(v[i]);
        return res;
    }
    int size() const { return data.size(); }
  private:
    std::vector<T> data;
};
/// @brief 座標圧縮
template <class T>
std::vector<int> compress(const std::vector<T> &v) {
    coordinate_compression cps(v);
    std::vector<int> res;
    res.reserve(std::size(v));
    for (auto &&x : v) res.emplace_back(cps.get(x));
    return res;
}
/// @brief 二次元累積和
template <class T>
struct cumulative_sum_2d {
    cumulative_sum_2d(int _n, int _m) : v(_n, std::vector<T>(_m)), n(_n), m(_m) {}
    cumulative_sum_2d(const std::vector<std::vector<T>> &_v) : v(_v) { build(); }
    void set(int x, int y, T val) { v[x][y] = val; }
    void add(int x, int y, T val) { v[x][y] += val; }
    void build() {
        n = v.size();
        assert(n > 0);
        m = v[0].size();
        assert(m > 0);
        v.resize(n + 1);
        for (int i = 0; i <= n; ++i) v[i].resize(m + 1);
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) v[i][j] += v[i][j + 1];
        }
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) v[i][j] += v[i + 1][j];
        }
    }
    T get(int x1, int y1, int x2, int y2) {
        assert(0 <= x1 && x1 <= x2 && x2 <= n && 0 <= y1 && y1 <= y2 && y2 <= m);
        return v[x1][y1] - v[x1][y2] - v[x2][y1] + v[x2][y2];
    }
  private:
    std::vector<std::vector<T>> v;
    int n, m;
};
/// @brief 重み付きグラフ
template <class T>
struct Graph {
  private:
    struct _edge {
        constexpr _edge() : _from(), _to(), _weight() {}
        constexpr _edge(int from, int to, T weight) : _from(from), _to(to), _weight(weight) {}
        constexpr bool operator<(const _edge &rhs) const { return weight() < rhs.weight(); }
        constexpr bool operator>(const _edge &rhs) const { return rhs < *this; }
        constexpr int from() const { return _from; }
        constexpr int to() const { return _to; }
        constexpr T weight() const { return _weight; }
      private:
        int _from, _to;
        T _weight;
    };
  public:
    using edge_type = typename Graph<T>::_edge;
    Graph() : _size(), edges() {}
    Graph(int v) : _size(v), edges(v) {}
    const auto &operator[](int i) const { return edges[i]; }
    auto &operator[](int i) { return edges[i]; }
    const auto begin() const { return edges.begin(); }
    auto begin() { return edges.begin(); }
    const auto end() const { return edges.end(); }
    auto end() { return edges.end(); }
    constexpr int size() const { return _size; }
    void add_edge(const edge_type &e) { edges[e.from()].emplace_back(e); }
    void add_edge(int from, int to, T weight = T(1)) { edges[from].emplace_back(from, to, weight); }
    void add_edges(int from, int to, T weight = T(1)) {
        edges[from].emplace_back(from, to, weight);
        edges[to].emplace_back(to, from, weight);
    }
    void input_edge(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            T weight;
            std::cin >> from >> to >> weight;
            add_edge(from - base, to - base, weight);
        }
    }
    void input_edges(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            T weight;
            std::cin >> from >> to >> weight;
            add_edges(from - base, to - base, weight);
        }
    }
  private:
    int _size;
    std::vector<std::vector<edge_type>> edges;
};
/// @brief 重みなしグラフ
template <>
struct Graph<void> {
  private:
    struct _edge {
        constexpr _edge() : _from(), _to() {}
        constexpr _edge(int from, int to) : _from(from), _to(to) {}
        constexpr int from() const { return _from; }
        constexpr int to() const { return _to; }
        constexpr int weight() const { return 1; }
        constexpr bool operator<(const _edge &rhs) const { return weight() < rhs.weight(); }
        constexpr bool operator>(const _edge &rhs) const { return rhs < *this; }
      private:
        int _from, _to;
    };
  public:
    using edge_type = typename Graph<void>::_edge;
    Graph() : _size(), edges() {}
    Graph(int v) : _size(v), edges(v) {}
    const auto &operator[](int i) const { return edges[i]; }
    auto &operator[](int i) { return edges[i]; }
    const auto begin() const { return edges.begin(); }
    auto begin() { return edges.begin(); }
    const auto end() const { return edges.end(); }
    auto end() { return edges.end(); }
    constexpr int size() const { return _size; }
    void add_edge(const edge_type &e) { edges[e.from()].emplace_back(e); }
    void add_edge(int from, int to) { edges[from].emplace_back(from, to); }
    void add_edges(int from, int to) {
        edges[from].emplace_back(from, to);
        edges[to].emplace_back(to, from);
    }
    void input_edge(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            std::cin >> from >> to;
            add_edge(from - base, to - base);
        }
    }
    void input_edges(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            std::cin >> from >> to;
            add_edges(from - base, to - base);
        }
    }
  private:
    int _size;
    std::vector<std::vector<edge_type>> edges;
};
#include <concepts>
/// @brief 素集合データ構造
/// @details Implement (union by size) + (path compression)
/// @see https://github.com/atcoder/ac-library/blob/master/atcoder/dsu.hpp
struct union_find {
    union_find() = default;
    explicit union_find(int _n) : _rank(_n), data(_n, -1) {}
    const int &operator[](std::size_t x) const { return data[x]; }
    int &operator[](std::size_t x) { return data[x]; }
    int root(int x) { return data[x] < 0 ? x : data[x] = root(data[x]); }
    int get_root(int x) { return root(x); }
    bool is_root(int x) const { return data[x] < 0; }
    bool same(int x, int y) { return root(x) == root(y); }
    bool is_same(int x, int y) { return same(x, y); }
    int rank() { return _rank; }
    int size(int x) { return -(data[root(x)]); }
    int get_size(int x) { return size(x); }
    std::vector<int> leaders() {
        std::vector<int> res;
        for (int i = 0; i < (int)data.size(); ++i) {
            if (is_root(i)) res.emplace_back(i);
        }
        return res;
    }
    bool unite(int x, int y) {
        x = root(x), y = root(y);
        if (x == y) return false;
        --_rank;
        if (data[x] > data[y]) std::swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return true;
    }
    template <class F>
    requires std::invocable<F, int, int, bool>
    bool unite(int x, int y, F f) {
        x = root(x), y = root(y);
        bool swapped = false;
        if (x != y) {
            if (data[x] > data[y]) std::swap(x, y), swapped = true;
            data[x] += data[y];
            data[y] = x;
        }
        f(x, y, swapped);
        return x != y;
    }
    template <class F>
    requires std::invocable<F, int, int>
    bool unite(int x, int y, F f) {
        x = root(x), y = root(y);
        if (x != y) {
            if (data[x] > data[y]) std::swap(x, y);
            data[x] += data[y];
            data[y] = x;
        }
        f(x, y);
        return x != y;
    }
  private:
    int _rank;
    std::vector<int> data;
};
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    a = compress(a);
    union_find uf(n);
    int ans = 0;
    rep (i, n) {
        ans += uf.unite(a[i], a[n - 1 - i]);
    }
    co(ans);
}
int main(void) {
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}
