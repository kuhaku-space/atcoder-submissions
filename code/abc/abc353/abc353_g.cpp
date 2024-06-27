#define PROBLEM ""
#include <cassert>
#include <cstdint>
#include <functional>
#include <limits>
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
        root = add_line(root, line, xl, xr);
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
        assert(xl <= l && l < r && r <= xr);
        line_type line = line_type{a, b};
        root = add_segment(l, r, root, line, xl, xr);
    }
    std::int64_t query(std::int64_t x) {
        assert(xl <= x && x < xr);
        return query(x, xl, xr);
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
        if (left != mid) node->left = add_line(node->left, line, l, m);
        else node->right = add_line(node->right, line, m, r);
        return node;
    }
    node_ptr add_segment(std::int64_t a, std::int64_t b, node_ptr node, line_type line,
                         std::int64_t l, std::int64_t r) {
        if (r <= a || b <= l) return node;
        if (a <= l && r <= b) return add_line(node, line, l, r);
        if (node == nullptr) node = new _node(inf_line);
        std::int64_t m = (l + r) >> 1;
        node->left = add_segment(a, b, node->left, line, l, m);
        node->right = add_segment(a, b, node->right, line, m, r);
        return node;
    }
    std::int64_t query(std::int64_t k, std::int64_t l, std::int64_t r) {
        node_ptr node = root;
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
int main(void) {
    ll n, c;
    cin >> n >> c;
    li_chao_tree<greater<>, numeric_limits<ll>::min()> lct(0, n);
    lct.add_line(-c, 0);
    int m;
    cin >> m;
    rep (i, m) {
        ll t, p;
        cin >> t >> p;
        --t;
        ll x = lct.query(t) + p;
        if (0 < t)
            lct.add_segment(c, -c * t + x, 0, t);
        lct.add_segment(-c, c * t + x, t, n);
    }
    ll ans = 0;
    rep (i, n) {
        chmax(ans, lct.query(i));
    }
    co(ans);
    return 0;
}
