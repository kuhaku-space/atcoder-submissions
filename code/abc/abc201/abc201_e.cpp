// clang-format off
#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ld = long double;
using Pi = pair<int, int>;
using Pl = pair<ll, ll>;
using Vi = vector<int>;
using Vl = vector<ll>;
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
        edges[a].push_back(edge{a, b, d});
        edges[b].push_back(edge{b, a, d});
    }
};

template <int mod>
struct ModInt {
    int x;

    ModInt() : x(0) {}

    ModInt(int64_t y) noexcept
        : x(y >= 0 ? y % mod : (mod - 1 - (-y - 1) % mod)) {}

    ModInt &operator+=(const ModInt &rhs) noexcept {
        if ((x += rhs.x) >= mod) x -= mod;
        return *this;
    }
    ModInt &operator-=(const ModInt &rhs) noexcept {
        if ((x += mod - rhs.x) >= mod) x -= mod;
        return *this;
    }
    ModInt &operator*=(const ModInt &rhs) noexcept {
        x = (int)(1LL * x * rhs.x % mod);
        return *this;
    }
    ModInt &operator/=(const ModInt &rhs) noexcept {
        *this *= rhs.inverse();
        return *this;
    }

    ModInt &operator++() noexcept {
        if ((++x) >= mod) x -= mod;
        return *this;
    }
    ModInt operator++(int) noexcept {
        ModInt tmp(*this);
        operator++();
        return tmp;
    }
    ModInt &operator--() noexcept {
        if ((x += mod - 1) >= mod) x -= mod;
        return *this;
    }
    ModInt operator--(int) noexcept {
        ModInt tmp(*this);
        operator--();
        return tmp;
    }

    ModInt operator-() const noexcept { return ModInt(-x); }
    ModInt operator+(const ModInt &rhs) const noexcept {
        return ModInt(*this) += rhs;
    }
    ModInt operator-(const ModInt &rhs) const noexcept {
        return ModInt(*this) -= rhs;
    }
    ModInt operator*(const ModInt &rhs) const noexcept {
        return ModInt(*this) *= rhs;
    }
    ModInt operator/(const ModInt &rhs) const noexcept {
        return ModInt(*this) /= rhs;
    }

    bool operator==(const ModInt &rhs) const noexcept { return x == rhs.x; }
    bool operator!=(const ModInt &rhs) const noexcept { return x != rhs.x; }

    ModInt inverse() const noexcept {
        int a = x, b = mod, u = 1, v = 0, t;
        while (b > 0) {
            t = a / b;
            swap(a -= t * b, b);
            swap(u -= t * v, v);
        }
        return ModInt(u);
    }

    ModInt pow(int64_t n) const noexcept { return ModInt(*this).pow_self(n); }
    void pow_self(int64_t n) noexcept {
        ModInt res(1);
        for (; n > 0; n >>= 1) {
            if (n & 1) res *= *this;
            *this *= *this;
        }
        *this = res;
    }

    friend istream &operator>>(istream &is, ModInt &rhs) {
        int64_t t;
        is >> t;
        rhs = ModInt<mod>(t);
        return (is);
    }
    friend ostream &operator<<(ostream &os, const ModInt &rhs) {
        return os << rhs.x;
    }

    int to_int() const noexcept { return x; }

    static int get_mod() noexcept { return mod; }
};
using Mint = ModInt<MOD>;

// clang-format on

int main(void) {
    int n;
    cin >> n;
    Graph<ll> g(n);
    rep(i, n - 1) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        --u, --v;
        g.add_edges(u, v, w);
    }

    auto dfs = [&](auto self, int idx, int par, ll w) -> pair<int, vector<int>> {
        int s = 0;
        vector<int> v(60);
        for (auto e : g[idx]) {
            if (e.to == par)
                continue;
            auto [x, y] = self(self, e.to, idx, e.dist);
            s += x;
            for (int i = 0; i < 60; ++i) v[i] += y[i];
        }

        for (int i = 0; i < 60; ++i) {
            if (w >> i & 1) {
                v[i] = s - v[i] + 1;
            }
        }

        return {s + 1, v};
    };

    auto [s, v] = dfs(dfs, 0, -1, 0);
    Mint ans = 0;
    for (int i = 0; i < 60; ++i) ans += Mint(1LL << i) * v[i] * (n - 1 - v[i]) + Mint(1LL << i) * v[i];
    co(ans);

    return 0;
}
