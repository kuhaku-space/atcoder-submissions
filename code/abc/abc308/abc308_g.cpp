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
#line 2 "/home/kuhaku/home/github/algo/lib/data_structure/erasable_priority_queue.hpp"

/**
 * @brief 削除付き優先順位付きキュー
 *
 * @tparam T
 */
template <class T, class Comp = std::less<>>
struct erasable_priority_queue {
    bool empty() const { return this->a.empty(); }
    auto top() const { return this->a.top(); }

    void emplace(T x) { this->a.emplace(x); }
    void insert(T x) { this->a.emplace(x); }
    void push(T x) { this->a.emplace(x); }

    void pop() { this->erase(this->a.top()); }

    void erase(T x) {
        this->b.emplace(x);
        while (!this->a.empty() && !this->b.empty() && this->a.top() == this->b.top()) {
            this->a.pop(), this->b.pop();
        }
    }

  private:
    std::priority_queue<T, std::vector<T>, Comp> a, b;
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

template <class T, int B = 31>
struct multi_binary_trie {
  private:
    struct _node {
        using pointer = _node *;
        int count;
        erasable_priority_queue<T> st;
        pointer ch[2];
        _node() : count(), ch{nullptr, nullptr} {}
    };

  public:
    using node_ptr = typename _node::pointer;

    multi_binary_trie() : root(nullptr) {}

    T operator[](int k) const {
        assert(0 <= k && k < this->size());
        return this->get(root, k);
    }
    T at(int k) const {
        return this->operator[](k);
    }
    T get(int k) const {
        return this->operator[](k);
    }
    T kth_element(int k) const {
        return this->operator[](k);
    }

    constexpr int size() const {
        return this->root ? this->root->count : 0;
    }
    constexpr bool empty() const {
        return !this->root;
    }

    void insert(T val) {
        this->root = this->insert(this->root, val);
    }
    void erase(T val) {
        if (this->count(val))
            this->root = this->erase(this->root, val);
    }

    T max_element(T bias = 0) const {
        return this->get_min(this->root, ~bias);
    }
    T min_element(T bias = 0) const {
        return this->get_min(this->root, bias);
    }
    int lower_bound(T val) {
        return this->count_lower(this->root, val);
    }
    int upper_bound(T val) {
        return this->count_lower(this->root, val + 1);
    }
    int count(T val) const {
        if (!this->root)
            return 0;
        node_ptr node = this->root;
        for (int i = B - 1; i >= 0; i--) {
            node = node->ch[val >> i & (T)1];
            if (!node)
                return 0;
        }
        return node->count;
    }

    T query() const {
        if (mst.empty())
            return 0;
        return mst.top();
    }

  private:
    erasable_priority_queue<T, greater<>> mst;
    node_ptr root;

    node_ptr insert(node_ptr node, T val, int b = B - 1) {
        if (!node)
            node = new _node();
        if (node->count == 2) {
            T x = node->st.top();
            node->st.pop();
            mst.erase(node->st.top() ^ x);
            node->st.emplace(x);
        }
        ++node->count;
        node->st.emplace(val);
        if (node->count == 2) {
            T x = node->st.top();
            node->st.pop();
            mst.emplace(node->st.top() ^ x);
            node->st.emplace(x);
        }
        if (b < 0)
            return node;
        bool f = val >> b & (T)1;
        node->ch[f] = this->insert(node->ch[f], val, b - 1);
        return node;
    }
    node_ptr erase(node_ptr node, T val, int b = B - 1) {
        assert(node);
        if (node->count == 2) {
            T x = node->st.top();
            node->st.pop();
            mst.erase(node->st.top() ^ x);
            node->st.emplace(x);
        }
        --node->count;
        node->st.erase(val);
        if (node->count == 2) {
            T x = node->st.top();
            node->st.pop();
            mst.emplace(node->st.top() ^ x);
            node->st.emplace(x);
        }
        if (!node->count)
            return nullptr;
        if (b < 0)
            return node;
        bool f = val >> b & (T)1;
        node->ch[f] = this->erase(node->ch[f], val, b - 1);
        return node;
    }
    T get_min(node_ptr node, T val, int b = B - 1) const {
        assert(node);
        if (b < 0)
            return 0;
        bool f = val >> b & (T)1;
        f ^= !node->ch[f];
        return this->get_min(node->ch[f], val, b - 1) | ((T)f << (T)b);
    }
    T get(node_ptr node, int k, int b = B - 1) const {
        if (b < 0)
            return 0;
        int m = node->ch[0] ? node->ch[0]->count : 0;
        return k < m ? this->get(node->ch[0], k, b - 1)
                     : this->get(node->ch[1], k - m, b - 1) | ((T)1 << b);
    }
    int count_lower(node_ptr node, T val, int b = B - 1) {
        if (!node || b < 0)
            return 0;
        bool f = val >> b & (T)1;
        return (f && node->ch[0] ? node->ch[0]->count : 0) +
               this->count_lower(node->ch[f], val, b - 1);
    }
};

int main(void) {
    int q;
    cin >> q;
    multi_binary_trie<int> bt;
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int x;
            cin >> x;
            bt.insert(x);
        } else if (t == 2) {
            int x;
            cin >> x;
            bt.erase(x);
        } else {
            co(bt.query());
        }
    }

    return 0;
}
