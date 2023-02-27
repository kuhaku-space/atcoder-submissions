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
#line 3 "/home/kuhaku/home/github/algo/lib/graph/matrix_graph.hpp"

/**
 * @brief 隣接行列
 *
 * @tparam T
 */
template <class T>
struct matrix_graph {
    matrix_graph(int v, T e = T()) : _size(v), m(v, std::vector<T>(v, e)) {}

    const auto &operator[](int i) const { return this->m[i]; }
    auto &operator[](int i) { return this->m[i]; }
    const auto begin() const { return this->m.begin(); }
    auto begin() { return this->m.begin(); }
    const auto end() const { return this->m.end(); }
    auto end() { return this->m.end(); }

    constexpr int size() const { return this->_size; }

    void add_edge(int a, int b, T d = T(1)) { this->m[a][b] = d; }
    void add_edges(int a, int b, T d = T(1)) { this->m[a][b] = this->m[b][a] = d; }

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
    std::vector<std::vector<T>> m;
};

template <>
struct matrix_graph<void> {
    matrix_graph(int v) : _size(v), m(v, std::vector<bool>(v)) {}

    const auto &operator[](int i) const { return this->m[i]; }
    auto &operator[](int i) { return this->m[i]; }
    const auto begin() const { return this->m.begin(); }
    auto begin() { return this->m.begin(); }
    const auto end() const { return this->m.end(); }
    auto end() { return this->m.end(); }

    constexpr int size() const { return this->_size; }

    void add_edge(int a, int b) { this->m[a][b] = true; }
    void add_edges(int a, int b) { this->m[a][b] = this->m[b][a] = true; }

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

    void complement() {
        for (int i = 0; i < this->_size; ++i) {
            for (int j = 0; j < this->_size; ++j) this->m[i][j] = !this->m[i][j];
        }
    }

  private:
    int _size;
    std::vector<std::vector<bool>> m;
};
#line 4 "/home/kuhaku/home/github/algo/lib/graph/warshall_floyd.hpp"

template <class T>
void warshall_floyd(matrix_graph<T> &g) {
    int n = g.size();
    for (int i = 0; i < n; ++i) g[i][i] = T();
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                chmin(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }
}
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
using ll = int64_t;
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
#line 5 "a.cpp"

struct S {
    int cnt;
    ll weight;

    constexpr S() : cnt(), weight() {}
    constexpr S(int cnt, int weight) : cnt(cnt), weight(weight) {}

    constexpr S &operator+=(const S &rhs) {
        this->cnt += rhs.cnt;
        this->weight += rhs.weight;
        return *this;
    }

    constexpr S operator+(const S &rhs) const {
        return S(*this) += rhs;
    }

    constexpr bool operator<(const S &rhs) const {
        return this->cnt == rhs.cnt ? this->weight > rhs.weight : this->cnt < rhs.cnt;
    }
};

int main(void) {
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    matrix_graph<S> g(n, {Inf, Inf});
    rep (i, n) {
        string s;
        cin >> s;
        rep (j, n) {
            if (s[j] == 'Y')
                g.add_edge(i, j, S{1, a[j]});
        }
    }
    warshall_floyd(g);

    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        if (g[u][v].cnt > Inf / 2)
            co("Impossible");
        else
            co(g[u][v].cnt, g[u][v].weight + a[u]);
    }

    return 0;
}
