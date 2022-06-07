#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/template/template.hpp"
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
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/data_structure/binary_heap.hpp"

template <class Key, class Value, class Comp = std::less<>>
struct binary_heap {
  private:
    struct _node {
        using pointer = _node *;

        Key key;
        Value value;
        int index;

        constexpr _node(Key _key, Value _value) : key(_key), value(_value), index() {}

        constexpr bool operator<(const _node &rhs) const { return this->value < rhs.value; }

        constexpr std::pair<Key, Value> get_pair() const { return make_pair(key, value); }
        constexpr int get_index() const { return this->index; }
        constexpr void set_index(int new_index) { this->index = new_index; }
    };

  public:
    using node_pointer = typename _node::pointer;

    binary_heap() : _size(), nodes(1), comp() {}

    auto top() const { return this->nodes[1]->get_pair(); }
    constexpr int size() const { return this->_size; }
    constexpr bool empty() const { return this->size() == 0; }

    node_pointer push(Key key, Value value) {
        auto node = new _node(key, value);
        this->nodes.emplace_back(node);

        int index = this->increment_size();
        while (index > 1 && comp(this->nodes[index >> 1]->value, this->nodes[index]->value)) {
            std::swap(this->nodes[index], this->nodes[index >> 1]);
            this->nodes[index]->set_index(index);
            index >>= 1;
        }
        this->nodes[index]->set_index(index);

        return node;
    }
    node_pointer emplace(Key key, Value value) { return this->push(key, value); }

    void pop() {
        this->nodes[1] = this->nodes[this->decrement_size()];
        this->nodes.pop_back();

        int index = 1 << 1;
        while (index <= this->size()) {
            if (index < this->size() &&
                comp(this->nodes[index]->value, this->nodes[index + 1]->value))
                ++index;
            if (comp(this->nodes[index]->value, this->nodes[index >> 1]->value)) break;
            std::swap(this->nodes[index >> 1], this->nodes[index]);
            this->nodes[index >> 1]->set_index(index >> 1);
            index <<= 1;
        }
        this->nodes[index >> 1]->set_index(index >> 1);
    }

    void update(node_pointer node, Value value) {
        if (comp(node->value, value))
            node->value = value;
        else
            return;
        int index = node->get_index();
        while (index > 1 && comp(this->nodes[index >> 1]->value, this->nodes[index]->value)) {
            std::swap(this->nodes[index], this->nodes[index >> 1]);
            this->nodes[index]->set_index(index);
            index >>= 1;
        }
        this->nodes[index]->set_index(index);
    }

  private:
    int _size;
    std::vector<node_pointer> nodes;
    Comp comp;

    constexpr int increment_size() { return ++(this->_size); }
    constexpr int decrement_size() { return (this->_size)--; }
};
#line 3 "/home/kuhaku/atcoder/github/atcoder-lib/lib/graph/graph.hpp"

template <class T>
struct Graph {
  private:
    struct edge {
        int from, to;
        T dist;
        constexpr edge() : from(), to(), dist() {}
        constexpr edge(int _from, int _to, T _dist) : from(_from), to(_to), dist(_dist) {}
        bool operator<(const edge &rhs) const { return this->dist < rhs.dist; }
        bool operator>(const edge &rhs) const { return rhs < *this; }
    };

  public:
    using edge_type = edge;

    Graph(int v) : edges(v) {}

    const auto &operator[](int i) const { return this->edges[i]; }
    auto &operator[](int i) { return this->edges[i]; }
    const auto begin() const { return this->edges.begin(); }
    auto begin() { return this->edges.begin(); }
    const auto end() const { return this->edges.end(); }
    auto end() { return this->edges.end(); }
    auto size() const { return this->edges.size(); }
    void add_edge(int a, int b, T d = T(1)) { this->edges[a].emplace_back(a, b, d); }
    void add_edges(int a, int b, T d = T(1)) {
        this->edges[a].emplace_back(a, b, d);
        this->edges[b].emplace_back(b, a, d);
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

  private:
    std::vector<std::vector<edge>> edges;
};

template <>
struct Graph<void> {
    using edge_type = std::pair<int, int>;
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

  private:
    std::vector<std::vector<int>> edges;
};
#line 4 "/home/kuhaku/atcoder/github/atcoder-lib/lib/graph/dijkstra_heap.hpp"

template <class T>
std::vector<T> dijkstra(const Graph<T> &g, int s = 0, T inf = std::numeric_limits<T>::max()) {
    std::vector<T> dists(g.size(), inf);
    using b_heap = binary_heap<int, T, greater<>>;
    b_heap p_que;
    std::vector<typename b_heap::node_pointer> nodes(g.size());
    dists[s] = T();
    p_que.emplace(s, T());
    while (!p_que.empty()) {
        auto [to, dist] = p_que.top();
        p_que.pop();
        if (dists[to] < dist) continue;
        for (auto &i : g[to]) {
            if (chmin(dists[i.to], dist + i.dist)) {
                if (!nodes[i.to])
                    nodes[i.to] = p_que.push(i.to, dist + i.dist);
                else
                    p_que.update(nodes[i.to], dist + i.dist);
            }
        }
    }
    return dists;
}
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/template/atcoder.hpp"
#pragma GCC target("avx")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#line 6 "/home/kuhaku/atcoder/github/atcoder-lib/lib/template/atcoder.hpp"
using ll = int64_t;
using ld = long double;
#define FOR(i, m, n) for(int i = (m); i < int(n); ++i)
#define FORR(i, m, n) for(int i = (m)-1; i >= int(n); --i)
#define FORL(i, m, n) for(int64_t i = (m); i < int64_t(n); ++i)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FOR(i, 1, n+1)
#define repr(i, n) FORR(i, n, 0)
#define repnr(i, n) FORR(i, n+1, 1)
#define all(s) (s).begin(), (s).end()
template<class T, class U>
std::istream &operator>>(std::istream &is, std::pair<T, U> &p) { is >> p.first >> p.second; return is; }
template <class T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) { for (T &i : v) is>>i; return is; }
template <class T, class U>
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &p) {
    return os<<'('<<p.first<< ','<<p.second<<')';
}
template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    for (auto it=v.begin(); it!=v.end(); ++it) { os<<(it==v.begin()?"":" ")<<*it; } return os;
}
template <class Head, class... Tail>
void co(Head&& head, Tail&&... tail) {
    if constexpr(sizeof...(tail)==0) std::cout<<head<<'\n'; else std::cout<<head<<' ',co(forward<Tail>(tail)...);
}
template <class Head, class... Tail>
void ce(Head&& head, Tail&&... tail) {
    if constexpr(sizeof...(tail)==0) std::cerr<<head<<'\n'; else std::cerr<<head<<' ',ce(forward<Tail>(tail)...);
}
template<typename T, typename... Args>
auto make_vector(T x, int arg, Args ...args) {
    if constexpr(sizeof...(args)==0) return std::vector<T>(arg,x); else return std::vector(arg,make_vector<T>(x,args...));
}
void sonic() { std::ios::sync_with_stdio(false); std::cin.tie(nullptr); }
void setp(const int n) { std::cout<<std::fixed<<std::setprecision(n); }
void Yes(bool is_correct) { std::cout<<(is_correct?"Yes":"No")<<std::endl; }
void YES(bool is_correct) { std::cout<<(is_correct?"YES":"NO")<<std::endl; }
#line 5 "a.cpp"

double dist(double a, double b, double c, double d) {
    return sqrt((a - b) * (a - b) + (c - d) * (c - d));
}

int main(void) {
    sonic();
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    int n;
    cin >> n;
    vector<int> x(n), y(n), r(n);
    rep(i, n) cin >> x[i] >> y[i] >> r[i];
    x.emplace_back(a);
    y.emplace_back(b);
    r.emplace_back(0);
    x.emplace_back(c);
    y.emplace_back(d);
    r.emplace_back(0);

    Graph<double> g(n + 2);
    rep(i, n + 2) {
        FOR(j, i + 1, n + 2) {
            g.add_edges(i, j, max(0.0, dist(x[i], x[j], y[i], y[j]) - r[i] - r[j]));
        }
    }

    setp(20);
    co(dijkstra(g, n)[n + 1]);

    return 0;
}
