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
#line 3 "/home/kuhaku/home/github/algo/lib/data_structure/li_chao_tree.hpp"

/**
 * @brief Li Chao Tree
 *
 * @tparam Comp 比較関数
 * @tparam Inf
 */
template <class Comp = std::less<>, std::int64_t Inf = std::numeric_limits<std::int64_t>::max()>
struct li_chao_tree {
  private:
    struct _line {
        std::int64_t a, b;

        constexpr _line(std::int64_t _a, std::int64_t _b) : a(_a), b(_b) {}
        constexpr std::int64_t operator()(std::int64_t x) const { return a * x + b; }
    };

    const _line inf_line = {0, Inf};

    struct _node {
        using pointer = _node *;
        pointer left, right;
        _line line;

        constexpr _node(_line line) : left(nullptr), right(nullptr), line(line) {}
    };

  public:
    using line_type = _line;
    using node_ptr = typename _node::pointer;

    static constexpr std::int64_t inf = Inf;

    constexpr li_chao_tree(std::int64_t _xr) : root(nullptr), xl(0), xr(_xr) {}
    constexpr li_chao_tree(std::int64_t _xl, std::int64_t _xr) : root(nullptr), xl(_xl), xr(_xr) {}

    /**
     * @brief Add line ($ax+b$)
     *
     * @param a
     * @param b
     */
    void add_line(std::int64_t a, std::int64_t b) {
        line_type line = line_type{a, b};
        this->root = this->add_line(this->root, line, this->xl, this->xr);
    }

    /**
     * @brief Add segment ($ax+b$)
     *
     * @param a
     * @param b
     * @param l
     * @param r
     */
    void add_segment(std::int64_t a, std::int64_t b, std::int64_t l, std::int64_t r) {
        assert(this->xl <= l && l < r && r <= this->xr);
        line_type line = line_type{a, b};
        this->root = this->add_segment(l, r, this->root, line, this->xl, this->xr);
    }

    std::int64_t query(std::int64_t x) {
        assert(this->xl <= x && x < this->xr);
        return this->query(x, this->xl, this->xr);
    }

  private:
    node_ptr root;
    std::int64_t xl, xr;
    Comp comp;

    node_ptr add_line(node_ptr node, line_type line, std::int64_t l, std::int64_t r) {
        if (node == nullptr) return new _node(line);
        if (l + 1 == r) {
            if (comp(line(l), node->line(l))) node->line = line;
            return node;
        }
        std::int64_t m = (l + r) >> 1;
        bool left = comp(line(l), node->line(l));
        bool right = comp(line(r), node->line(r));
        if (left && right) {
            node->line = line;
            return node;
        }
        if (!left && !right) return node;
        bool mid = comp(line(m), node->line(m));
        if (mid) std::swap(node->line, line);
        if (left != mid) node->left = this->add_line(node->left, line, l, m);
        else node->right = this->add_line(node->right, line, m, r);
        return node;
    }

    node_ptr add_segment(std::int64_t a, std::int64_t b, node_ptr node, line_type line,
                         std::int64_t l, std::int64_t r) {
        if (r <= a || b <= l) return node;
        if (a <= l && r <= b) return this->add_line(node, line, l, r);
        if (node == nullptr) node = new _node(inf_line);
        std::int64_t m = (l + r) >> 1;
        node->left = this->add_segment(a, b, node->left, line, l, m);
        node->right = this->add_segment(a, b, node->right, line, m, r);
        return node;
    }

    std::int64_t query(std::int64_t k, std::int64_t l, std::int64_t r) {
        node_ptr node = this->root;
        std::int64_t s = Inf;
        while (node != nullptr) {
            std::int64_t m = (l + r) >> 1;
            if (comp(node->line(k), s)) s = node->line(k);
            if (k < m) r = m, node = node->left;
            else l = m, node = node->right;
        }
        return s;
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
    int n;
    ll c;
    cin >> n >> c;
    vector<ll> h(n);
    cin >> h;

    li_chao_tree lct(0, Inf);
    vector<ll> dp(n);
    lct.add_line(-2 * h[0], h[0] * h[0] + c);
    repn (i, n - 1) {
        dp[i] = lct.query(h[i]) + h[i] * h[i];
        lct.add_line(-2 * h[i], h[i] * h[i] + c + dp[i]);
    }
    // ce(dp);
    co(dp[n - 1]);

    return 0;
}
