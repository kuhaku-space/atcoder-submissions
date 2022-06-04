// clang-format off
#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ld = long double;
#define FOR(i, m, n) for(int i = (m); i < (n); ++i)
#define FORR(i, m, n) for(int i = (m)-1; i >= (n); --i)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FOR(i, 1, n+1)
#define repr(i, n) FORR(i, n, 0)
#define repnr(i, n) FORR(i, n+1, 1)
#define all(s) (s).begin(), (s).end()
template <class T, class U>
bool chmax(T &a, const U b) { return a < b ? a = b, true : false; }
template <class T, class U>
bool chmin(T &a, const U b) { return b < a ? a = b, true : false; }
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
constexpr int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
const double PI = acos(-1);

template <class T>
struct Graph {
    struct edge {
        int from, to;
        T dist;

        bool operator<(const edge &rhs) const { return dist < rhs.dist; }
        bool operator>(const edge &rhs) const { return rhs < *this; }
    };
    vector<vector<edge>> edges;

    Graph(int v) : edges(v) {}

    const auto &operator[](int i) const { return edges[i]; }
    auto &operator[](int i) { return edges[i]; }
    const auto begin() const { return edges.begin(); }
    auto begin() { return edges.begin(); }
    const auto end() const { return edges.end(); }
    auto end() { return edges.end(); }
    auto size() const { return edges.size(); }
    void add_edge(int a, int b, T d = T(1)) {
        edges[a].emplace_back(edge{a, b, d});
    }
    void add_edges(int a, int b, T d = T(1)) {
        edges[a].emplace_back(edge{a, b, d});
        edges[b].emplace_back(edge{b, a, d});
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

    const auto &operator[](int i) const { return edges[i]; }
    auto &operator[](int i) { return edges[i]; }
    const auto begin() const { return edges.begin(); }
    auto begin() { return edges.begin(); }
    const auto end() const { return edges.end(); }
    auto end() { return edges.end(); }
    auto size() const { return edges.size(); }
    void add_edge(int a, int b) { edges[a].emplace_back(b); }
    void add_edges(int a, int b) {
        edges[a].emplace_back(b);
        edges[b].emplace_back(a);
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

struct union_find {
    vector<int> data;

    union_find(int _n) : data(_n, -1) {}

    int root(int x) {
        return data[x] < 0 ? x : data[x] = root(data[x]);
    }

    bool is_root(int x) {
        return data[x] < 0;
    }

    void unite(int x, int y) {
        x = root(x), y = root(y);
        if (x != y) {
            if (data[y] < data[x]) swap(x, y);
            data[x] += data[y];
            data[y] = x;
        }
    }

    int size(int x) { return -data[root(x)]; }

    bool same(int x, int y) { return root(x) == root(y); }
};

// clang-format on

int main(void) {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(n);
    cin >> a >> b;
    union_find uf(n);
    rep(i, m) {
        int x,y;
        cin >> x >> y;
        uf.unite(x - 1, y - 1);
    }

    vector<ll> c(n), d(n);
    rep(i, n) {
        c[uf.root(i)] += a[i];
        d[uf.root(i)] += b[i];
    }

    bool flg = true;
    rep(i, n) flg &= c[i] == d[i];
    if (flg) {
        puts("Yes");
    } else {
        puts("No");
    }

    return 0;
}
