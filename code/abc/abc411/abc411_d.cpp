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
/// @brief 永続キュー
/// @tparam T
template <class T>
struct persistent_queue {
  private:
    struct _node {
        using pointer = _node *;
        T val;
        std::vector<pointer> prev;
        _node(const T &_val) : val(_val), prev() {}
        _node(T &&_val) : val(std::move(_val)), prev() {}
        template <typename... Args>
        _node(Args &&...args) : val(std::forward<Args>(args)...), prev() {}
    };
  public:
    using node_ptr = typename _node::pointer;
    constexpr persistent_queue() : _size(), root() {}
    constexpr persistent_queue(int n, node_ptr _root) : _size(n), root(_root) {}
    constexpr int size() const { return _size; }
    constexpr bool empty() const { return _size == 0; }
    T top() const {
        node_ptr node = root;
        int k = 0;
        while ((_size - 1) >> k) {
            if ((_size - 1) >> k & 1) { node = node->prev[k]; }
            ++k;
        }
        return node->val;
    }
    T front() const { return top(); }
    persistent_queue push(const T &val) const {
        node_ptr new_node = new _node(val);
        return push_node(new_node);
    }
    persistent_queue push(T &&val) const {
        node_ptr new_node = new _node(std::move(val));
        return push_node(new_node);
    }
    template <typename... Args>
    persistent_queue emplace(Args &&...args) const {
        node_ptr new_node = new _node(std::forward<Args>(args)...);
        return push_node(new_node);
    }
    persistent_queue pop() const { return persistent_queue(_size - 1, root); }
  private:
    int _size;
    node_ptr root;
    persistent_queue push_node(node_ptr new_node) const {
        node_ptr node = root;
        new_node->prev.emplace_back(node);
        int k = 0;
        while (node) {
            if ((int)node->prev.size() > k) node = node->prev[k++];
            else node = nullptr;
            new_node->prev.emplace_back(node);
        }
        return persistent_queue(_size + 1, new_node);
    }
};
int main(void) {
    int n, q;
    cin >> n >> q;
    persistent_queue<string> ser;
    vector<persistent_queue<string>> pq(n);
    rep (i, q) {
        int t;
        cin >> t;
        if (t == 1) {
            int x;
            cin >> x;
            --x;
            pq[x] = ser;
        } else if (t == 2) {
            int x;
            string s;
            cin >> x >> s;
            --x;
            pq[x] = pq[x].push(s);
        } else {
            int x;
            cin >> x;
            --x;
            ser = pq[x];
        }
    }
    string ans;
    while (!ser.empty()) {
        ans += ser.top();
        ser = ser.pop();
    }
    co(ans);
    return 0;
}
