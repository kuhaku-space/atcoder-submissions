#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/home/github/algo/lib/template/template.hpp"
#pragma GCC target("sse4.2,avx2,bmi2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
template <class T, class U>
bool chmax(T &a, const U &b) {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U &b) {
    return (T)b < a ? a = (T)b, true : false;
}
constexpr int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
constexpr double PI = M_PI;
#line 3 "/home/kuhaku/home/github/algo/lib/graph/graph.hpp"

/**
 * @brief 重み付きグラフ
 *
 * @tparam T 辺の重みの型
 */
template <class T>
struct Graph {
  private:
    struct _edge {
        constexpr _edge() : _from(), _to(), _weight() {}
        constexpr _edge(int from, int to, T weight) : _from(from), _to(to), _weight(weight) {}
        bool operator<(const _edge &rhs) const { return this->weight() < rhs.weight(); }
        bool operator>(const _edge &rhs) const { return rhs < *this; }

        constexpr int from() const { return this->_from; }
        constexpr int to() const { return this->_to; }
        constexpr T weight() const { return this->_weight; }

      private:
        int _from, _to;
        T _weight;
    };

  public:
    using edge_type = typename Graph<T>::_edge;

    Graph(int v) : _size(v), edges(v) {}

    const auto &operator[](int i) const { return this->edges[i]; }
    auto &operator[](int i) { return this->edges[i]; }
    const auto begin() const { return this->edges.begin(); }
    auto begin() { return this->edges.begin(); }
    const auto end() const { return this->edges.end(); }
    auto end() { return this->edges.end(); }
    constexpr int size() const { return this->_size; }

    void add_edge(const edge_type &e) { this->edges[e.from()].emplace_back(e); }
    void add_edge(int from, int to, T weight = T(1)) {
        this->edges[from].emplace_back(from, to, weight);
    }
    void add_edges(int from, int to, T weight = T(1)) {
        this->edges[from].emplace_back(from, to, weight);
        this->edges[to].emplace_back(to, from, weight);
    }

    void input_edge(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            T weight;
            cin >> from >> to >> weight;
            this->add_edge(from - base, to - base, weight);
        }
    }
    void input_edges(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            T weight;
            cin >> from >> to >> weight;
            this->add_edges(from - base, to - base, weight);
        }
    }

  private:
    int _size;
    std::vector<std::vector<edge_type>> edges;
};

template <>
struct Graph<void> {
  private:
    struct _edge {
        constexpr _edge() : _from(), _to() {}
        constexpr _edge(int from, int to) : _from(from), _to(to) {}

        constexpr int from() const { return this->_from; }
        constexpr int to() const { return this->_to; }
        constexpr int weight() const { return 1; }
        bool operator<(const _edge &rhs) const { return false; }
        bool operator>(const _edge &rhs) const { return rhs < *this; }

      private:
        int _from, _to;
    };

  public:
    using edge_type = typename Graph<void>::_edge;

    Graph(int v) : _size(v), edges(v) {}

    const auto &operator[](int i) const { return this->edges[i]; }
    auto &operator[](int i) { return this->edges[i]; }
    const auto begin() const { return this->edges.begin(); }
    auto begin() { return this->edges.begin(); }
    const auto end() const { return this->edges.end(); }
    auto end() { return this->edges.end(); }
    constexpr int size() const { return this->_size; }

    void add_edge(const edge_type &e) { this->edges[e.from()].emplace_back(e); }
    void add_edge(int from, int to) { this->edges[from].emplace_back(from, to); }
    void add_edges(int from, int to) {
        this->edges[from].emplace_back(from, to);
        this->edges[to].emplace_back(to, from);
    }

    void input_edge(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            cin >> from >> to;
            this->add_edge(from - base, to - base);
        }
    }
    void input_edges(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            cin >> from >> to;
            this->add_edges(from - base, to - base);
        }
    }

  private:
    int _size;
    std::vector<std::vector<edge_type>> edges;
};
#line 3 "/home/kuhaku/home/github/algo/lib/math/modint.hpp"

/**
 * @brief modint
 * @see https://github.com/ei1333/library/blob/master/math/combinatorics/mod-int.cpp
 *
 * @tparam mod 法
 */
template <int mod = MOD_N>
struct ModInt {
    static constexpr int get_mod() noexcept { return mod; }

    constexpr ModInt() noexcept : x(0) {}
    constexpr ModInt(int y) noexcept : x(y >= 0 ? y % mod : (mod - 1 - ~y % mod)) {}
    constexpr ModInt(std::int64_t y) noexcept : x(y >= 0 ? y % mod : (mod - 1 - ~y % mod)) {}

    constexpr ModInt &operator+=(const ModInt &rhs) noexcept {
        if ((this->x += rhs.x) >= mod) this->x -= mod;
        return *this;
    }
    constexpr ModInt &operator-=(const ModInt &rhs) noexcept {
        if ((this->x += mod - rhs.x) >= mod) this->x -= mod;
        return *this;
    }
    constexpr ModInt &operator*=(const ModInt &rhs) noexcept {
        this->x = (int)(1LL * this->x * rhs.x % mod);
        return *this;
    }
    constexpr ModInt &operator/=(const ModInt &rhs) noexcept {
        *this *= rhs.inverse();
        return *this;
    }

    constexpr ModInt &operator++() noexcept {
        if ((++(this->x)) >= mod) this->x -= mod;
        return *this;
    }
    constexpr ModInt operator++(int) noexcept {
        ModInt tmp(*this);
        this->operator++();
        return tmp;
    }
    constexpr ModInt &operator--() noexcept {
        if ((this->x += mod - 1) >= mod) this->x -= mod;
        return *this;
    }
    constexpr ModInt operator--(int) noexcept {
        ModInt tmp(*this);
        this->operator--();
        return tmp;
    }

    constexpr ModInt operator-() const noexcept { return ModInt(-this->x); }
    constexpr ModInt operator+(const ModInt &rhs) const noexcept { return ModInt(*this) += rhs; }
    constexpr ModInt operator-(const ModInt &rhs) const noexcept { return ModInt(*this) -= rhs; }
    constexpr ModInt operator*(const ModInt &rhs) const noexcept { return ModInt(*this) *= rhs; }
    constexpr ModInt operator/(const ModInt &rhs) const noexcept { return ModInt(*this) /= rhs; }

    constexpr bool operator==(const ModInt &rhs) const noexcept { return this->x == rhs.x; }
    constexpr bool operator!=(const ModInt &rhs) const noexcept { return this->x != rhs.x; }

    explicit operator int() const noexcept { return x; }

    constexpr ModInt inverse() const noexcept {
        int a = x, b = mod, u = 1, v = 0, t;
        while (b > 0) {
            t = a / b;
            swap(a -= t * b, b);
            swap(u -= t * v, v);
        }
        return ModInt(u);
    }

    constexpr ModInt pow(std::int64_t n) const noexcept { return ModInt(*this).pow_self(n); }
    constexpr ModInt &pow_self(std::int64_t n) noexcept {
        ModInt res(1);
        for (; n > 0; n >>= 1) {
            if (n & 1) res *= *this;
            *this *= *this;
        }
        *this = res;
        return *this;
    }

    friend std::istream &operator>>(std::istream &is, ModInt &rhs) {
        std::int64_t t;
        is >> t;
        rhs = ModInt<mod>(t);
        return (is);
    }
    friend std::ostream &operator<<(std::ostream &os, const ModInt &rhs) { return os << rhs.x; }

  private:
    int x;
};
#line 3 "/home/kuhaku/home/github/algo/lib/math/combination.hpp"

template <int mod>
struct Combination {
    using mint = ModInt<mod>;

    Combination() : _fact(), _finv() {}

    mint operator()(int n, int k) {
        if (n < k || n < 0 || k < 0) return 0;
        this->_init(n);
        return this->_fact[n] * this->_finv[k] * this->_finv[n - k];
    }

    mint fact(int x) {
        assert(x >= 0);
        this->_init(x);
        return this->_fact[x];
    }

    mint finv(int x) {
        assert(x >= 0);
        this->_init(x);
        return this->_finv[x];
    }

    mint naive(int n, int k) const {
        if (n < k || n < 0 || k < 0) return 0;
        if (n - k < k) k = n - k;
        mint res = 1;
        for (int i = 0; i < k; ++i) {
            res *= n - i;
            res /= i + 1;
        }
        return res;
    }

    mint lucas(int n, int k) {
        if (n < k || n < 0 || k < 0) return 0;
        if (n - k < k) k = n - k;
        static vector<vector<mint>> v;
        if (v.empty()) {
            v = vector<vector<mint>>(mod, vector<mint>(mod));
            for (int i = 0; i < mod; ++i) v[i][0] = 1;
            for (int i = 0; i < mod; ++i) {
                for (int j = 1; j < mod; ++j) {
                    if (i < j) v[i][j] = 0;
                    else if (i - j < j) v[i][j] = v[i][i - j];
                    else v[i][j] = v[i][j - 1] * mint(i + 1 - j) / mint(j);
                }
            }
        }
        mint res = 1;
        while (n || k) {
            res *= v[n % mod][k % mod];
            n /= mod, k /= mod;
        }
        return res;
    }

    mint permu(int n, int k) {
        if (n < k || n < 0 || k < 0) return 0;
        this->_init(n);
        return this->_fact[n] * this->_finv[n - k];
    }

  private:
    vector<mint> _fact, _finv;

    void _init(int n) {
        if (this->_fact.size() > n) return;
        int m = this->_fact.size();
        this->_fact.resize(n + 1);
        for (int i = m; i <= n; ++i) {
            if (i == 0) this->_fact[i] = 1;
            else this->_fact[i] = this->_fact[i - 1] * i;
        }
        this->_finv.resize(n + 1);
        this->_finv[n] = this->_fact[n].inverse();
        for (int i = n - 1; i >= m; --i) this->_finv[i] = this->_finv[i + 1] * (i + 1);
    }
};
#line 3 "/home/kuhaku/home/github/algo/lib/template/atcoder.hpp"
using ll = int64_t;
using ld = long double;
#define FOR(i, m, n) for (int i = (m); i < int(n); ++i)
#define FORR(i, m, n) for (int i = (m)-1; i >= int(n); --i)
#define FORL(i, m, n) for (int64_t i = (m); i < int64_t(n); ++i)
#define rep(i, n) FOR (i, 0, n)
#define repn(i, n) FOR (i, 1, n + 1)
#define repr(i, n) FORR (i, n, 0)
#define repnr(i, n) FORR (i, n + 1, 1)
#define all(s) (s).begin(), (s).end()
template <class T, class U>
std::istream &operator>>(std::istream &is, std::pair<T, U> &p) {
    is >> p.first >> p.second;
    return is;
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
    else std::cout << head << ' ', co(forward<Tail>(tail)...);
}
template <class Head, class... Tail>
void ce(Head &&head, Tail &&...tail) {
    if constexpr (sizeof...(tail) == 0) std::cerr << head << '\n';
    else std::cerr << head << ' ', ce(forward<Tail>(tail)...);
}
template <typename T, typename... Args>
auto make_vector(T x, int arg, Args... args) {
    if constexpr (sizeof...(args) == 0) return std::vector<T>(arg, x);
    else return std::vector(arg, make_vector<T>(x, args...));
}
void sonic() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}
void setp(const int n) {
    std::cout << std::fixed << std::setprecision(n);
}
void Yes(bool is_correct = true) {
    std::cout << (is_correct ? "Yes" : "No") << std::endl;
}
void No(bool is_not_correct = true) {
    Yes(!is_not_correct);
}
void YES(bool is_correct = true) {
    std::cout << (is_correct ? "YES" : "NO") << std::endl;
}
void NO(bool is_not_correct = true) {
    YES(!is_not_correct);
}
void Takahashi(bool is_correct = true) {
    std::cout << (is_correct ? "Takahashi" : "Aoki") << std::endl;
}
void Aoki(bool is_not_correct = true) {
    Takahashi(!is_not_correct);
}
#line 5 "a.cpp"

Combination<MOD> combi;
using Mint = ModInt<MOD>;
struct Monoid {
    using value_type = pair<int, Mint>;
    static constexpr value_type id = {0, 1};
    static value_type op(const value_type& lhs, const value_type& rhs) {
        return {lhs.first + rhs.first,
                lhs.second * rhs.second * combi(lhs.first + rhs.first, lhs.first)};
    }

    template <class T>
    static constexpr value_type f(const value_type& v, T u) {
        return v;
    }

    static value_type g(const value_type& v, int u) {
        return {v.first + 1, v.second};
    }
};

template <class M, class T>
struct ReRooting {
  private:
    using Value = typename M::value_type;

  public:
    ReRooting(const Graph<T>& g) : graph(g), dp(g.size()), data(g.size()) {
        this->build();
    }

    const Value& operator[](int i) const {
        return data[i];
    }
    Value& operator[](int i) {
        return data[i];
    }

  private:
    Graph<T> graph;
    std::vector<std::vector<Value>> dp;
    std::vector<Value> data;

    void build() {
        this->dfs(0);
        this->bfs(0);
    }

    Value dfs(int v, int p = -1) {
        Value res = M::id;
        int deg = graph[v].size();
        dp[v] = std::vector<Value>(deg, M::id);
        for (int i = 0; i < deg; ++i) {
            auto e = graph[v][i];
            if (e.to() == p)
                continue;
            dp[v][i] = M::f(dfs(e.to(), v), e.weight());
            res = M::op(res, dp[v][i]);
        }
        return M::g(res, v);
    }
    void bfs(int v, int p = -1, Value dp_p = M::id) {
        int deg = graph[v].size();
        std::vector<Value> dp_r(deg + 1, M::id);
        for (int i = deg - 1; i >= 0; --i) {
            auto e = graph[v][i];
            if (e.to() == p)
                dp[v][i] = M::f(dp_p, e.weight());
            dp_r[i] = M::op(dp[v][i], dp_r[i + 1]);
        }
        Value dp_l = M::id;
        for (int i = 0; i < deg; ++i) {
            int u = graph[v][i].to();
            if (u != p)
                this->bfs(u, v, M::g(M::op(dp_l, dp_r[i + 1]), u));
            dp_l = M::op(dp_l, dp[v][i]);
        }
        data[v] = M::g(dp_l, v);
    }
};

int main(void) {
    sonic();
    int n;
    cin >> n;
    Graph<void> g(n);
    g.input_edges(n - 1);
    ReRooting<Monoid, void> re(g);

    rep(i, n) co(re[i].second);

    return 0;
}
