#line 2 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/template/template.hpp"
#include <bits/stdc++.h>
using namespace std;
template <class T, class U>
bool chmax(T &a, const U &b) {
    return a < b ? a = b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U &b) {
    return b < a ? a = b, true : false;
}
constexpr int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
const double PI = acos(-1.0);
#line 2 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/binary_tree/multi_patricia_binary_trie.hpp"

/**
 * @brief 2分トライ木(重複あり)
 *
 * @tparam T
 * @tparam B ビットサイズ
 */
template <class T, int B = 31>
struct multi_patricia_binary_trie {
    struct Node {
        T val;
        int len, count;
        Node* ch[2];
        Node(T _val, int _len, int _count = 0)
            : val(_val), len(_len), count(_count), ch{nullptr, nullptr} {}
    };

    Node* root;

    multi_patricia_binary_trie() : root(nullptr) {}

    T operator[](int k) const {
        assert(0 <= k && k < this->size());
        return this->get(root, k);
    }

    int size() const { return this->root ? this->root->count : 0; }
    bool empty() const { return !this->root; }
    void insert(T val) { this->root = this->add(this->root, val); }
    void erase(T val) {
        if (this->count(val)) this->root = this->sub(this->root, val);
    }
    T kth_element(int k) const {
        assert(0 <= k && k < this->size());
        return this->get(this->root, k);
    }
    T max_element(T bias = 0) const { return this->get_min(this->root, ~bias); }
    T min_element(T bias = 0) const { return this->get_min(this->root, bias); }
    int lower_bound(T val) { return this->count_lower(this->root, val); }
    int upper_bound(T val) { return this->count_lower(this->root, val + 1); }
    int count(T val) const {
        if (!this->root) return 0;
        Node* node = this->root;
        int rest = node->len;
        for (int i = B - 1; i >= 0; i--) {
            if (!rest) {
                node = node->ch[val >> i & 1];
                rest += node->len;
            }
            if (!node || ((val ^ node->val) >> i & 1)) return 0;
            --rest;
        }
        return node->count;
    }

  private:
    Node* add(Node* node, T val, int b = B - 1) {
        if (!node) node = new Node(val, b + 1);
        ++node->count;
        if (b < 0) return node;
        int len = node->len;
        for (int i = 0; i < node->len; ++i) {
            if (((val ^ node->val) >> (b - i) & 1)) {
                len = i;
                break;
            }
        }
        if (len == b + 1) return node;
        b -= len;
        Node* itr = node;
        if (len != node->len) {
            itr = new Node(val, len, node->count);
            node->len -= len;
            --node->count;
            itr->ch[node->val >> b & 1] = node;
        }
        bool f = val >> b & 1;
        itr->ch[f] = this->add(itr->ch[f], val, b);
        return itr;
    }
    Node* sub(Node* node, T val, int b = B - 1) {
        assert(node);
        --node->count;
        if (!node->count) return nullptr;
        b -= node->len;
        if (b < 0) return node;
        bool f = val >> b & 1;
        node->ch[f] = this->sub(node->ch[f], val, b);
        return node;
    }
    T get_min(Node* node, T val, int b = B - 1) const {
        assert(node);
        b -= node->len;
        if (b < 0) return node->val;
        bool f = val >> b & 1;
        f ^= !node->ch[f];
        return this->get_min(node->ch[f], val, b);
    }
    T get(Node* node, int k, int b = B - 1) const {
        b -= node->len;
        if (b < 0) return node->val;
        int m = node->ch[0] ? node->ch[0]->count : 0;
        return k < m ? this->get(node->ch[0], k, b) : this->get(node->ch[1], k - m, b);
    }
    int count_lower(Node* node, T val, int b = B - 1) {
        if (!node || b < 0) return 0;
        b -= node->len;
        bool f = val >> b & 1;
        return (f && node->ch[0] ? node->ch[0]->count : 0) +
               this->count_lower(node->ch[f], val, b - 1);
    }
};
#line 3 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/graph/graph.hpp"

template <class T>
struct Graph {
    struct edge {
        int from, to;
        T dist;

        bool operator<(const edge &rhs) const { return this->dist < rhs.dist; }
        bool operator>(const edge &rhs) const { return rhs < *this; }
    };
    vector<vector<edge>> edges;

    Graph(int v) : edges(v) {}

    const auto &operator[](int i) const { return this->edges[i]; }
    auto &operator[](int i) { return this->edges[i]; }
    const auto begin() const { return this->edges.begin(); }
    auto begin() { return this->edges.begin(); }
    const auto end() const { return this->edges.end(); }
    auto end() { return this->edges.end(); }
    auto size() const { return this->edges.size(); }
    void add_edge(int a, int b, T d = T(1)) { this->edges[a].emplace_back(edge{a, b, d}); }
    void add_edges(int a, int b, T d = T(1)) {
        this->edges[a].emplace_back(edge{a, b, d});
        this->edges[b].emplace_back(edge{b, a, d});
    }
    void input_edge(int m, bool zero_based = false) {
        for (int i = 0; i < m; ++i) {
            int a, b;
            T d;
            cin >> a >> b >> d;
            if (zero_based)
                this->add_edge(a, b, d);
            else
                this->add_edge(a - 1, b - 1, d);
        }
    }
    void input_edges(int m, bool zero_based = false) {
        for (int i = 0; i < m; ++i) {
            int a, b;
            T d;
            cin >> a >> b >> d;
            if (zero_based)
                this->add_edges(a, b, d);
            else
                this->add_edges(a - 1, b - 1, d);
        }
    }
};

template <>
struct Graph<void> {
    vector<vector<int>> edges;

    Graph(int v) : edges(v) {}

    const auto &operator[](int i) const { return this->edges[i]; }
    auto &operator[](int i) { return this->edges[i]; }
    const auto begin() const { return this->edges.begin(); }
    auto begin() { return this->edges.begin(); }
    const auto end() const { return this->edges.end(); }
    auto end() { return this->edges.end(); }
    auto size() const { return this->edges.size(); }
    void add_edge(int a, int b) { this->edges[a].emplace_back(b); }
    void add_edges(int a, int b) {
        this->edges[a].emplace_back(b);
        this->edges[b].emplace_back(a);
    }
    void input_edge(int m, bool zero_based = false) {
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            if (zero_based)
                this->add_edge(a, b);
            else
                this->add_edge(a - 1, b - 1);
        }
    }
    void input_edges(int m, bool zero_based = false) {
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            if (zero_based)
                this->add_edges(a, b);
            else
                this->add_edges(a - 1, b - 1);
        }
    }
};
#line 2 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/template/atcoder.hpp"
#pragma GCC target("avx")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#line 6 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/template/atcoder.hpp"
using ll = int64_t;
using ld = long double;
#define FOR(i, m, n) for(int i = (m); i < (n); ++i)
#define FORR(i, m, n) for(int i = (m)-1; i >= (n); --i)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FOR(i, 1, n+1)
#define repr(i, n) FORR(i, n, 0)
#define repnr(i, n) FORR(i, n+1, 1)
#define all(s) (s).begin(), (s).end()
template <class T>
istream &operator>>(istream &is, vector<T> &v) { for (T &i : v) is>>i; return is; }
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    for (auto it=v.begin(); it!=v.end(); ++it) { os<<(it==v.begin()?"":" ")<<*it; } return os;
}
template <class Head, class... Tail>
void co(Head&& head, Tail&&... tail) {
    if constexpr(sizeof...(tail)==0) cout<<head<<'\n'; else cout<<head<<' ',co(forward<Tail>(tail)...);
}
template <class Head, class... Tail>
void ce(Head&& head, Tail&&... tail) {
    if constexpr(sizeof...(tail)==0) cerr<<head<<'\n'; else cerr<<head<<' ',ce(forward<Tail>(tail)...);
}
template<typename T, typename... Args>
auto make_vector(T x, int arg, Args ...args) {
    if constexpr(sizeof...(args)==0) return vector<T>(arg, x); else return vector(arg,make_vector<T>(x, args...));
}
void sonic() { ios::sync_with_stdio(false); cin.tie(nullptr); }
void setp(const int n) { cout << fixed << setprecision(n); }
#line 4 "a.cpp"

int main(void) {
    sonic();
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    Graph<void> g(n);
    g.input_edges(n - 1);

    multi_patricia_binary_trie<int> bt;
    auto dfs = [&](auto &&self, int idx, int par, int depth) -> int {
        bt.insert(a[idx]);

        int res = (depth & 1) ? Inf : -Inf;
        for (auto i : g[idx]) {
            if (i == par)
                continue;
            auto x = self(self, i, idx, depth + 1);
            if (depth & 1)
                chmin(res, x);
            else
                chmax(res, x);
        }
        if (abs(res) == Inf) {
            int s = bt.size();
            if (s & 1)
                res = bt.kth_element(s / 2);
            else
                res = (bt.kth_element(s / 2 - 1) + bt.kth_element(s / 2)) / 2;
        }
        bt.erase(a[idx]);
        return res;
    };

    co(dfs(dfs, 0, -1, 0));

    return 0;

    return 0;
}
