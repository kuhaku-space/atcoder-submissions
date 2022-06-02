#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ld = long double;
using P = pair<ll, ll>;
using Pld = pair<ld, ld>;
using Vec = vector<ll>;
using VecP = vector<P>;
using VecB = vector<bool>;
using VecC = vector<char>;
using VecD = vector<ld>;
using VecS = vector<string>;
template <class T>
using Vec2 = vector<vector<T>>;
#define REP(i, m, n) for (ll i = (m); i < (n); ++i)
#define REPN(i, m, n) for (ll i = (m); i <= (n); ++i)
#define REPR(i, m, n) for (ll i = (m)-1; i >= (n); --i)
#define REPNR(i, m, n) for (ll i = (m); i >= (n); --i)
#define rep(i, n) REP(i, 0, n)
#define repn(i, n) REPN(i, 1, n)
#define repr(i, n) REPR(i, n, 0)
#define repnr(i, n) REPNR(i, n, 1)
#define all(s) (s).begin(), (s).end()
template <class T1, class T2>
bool chmax(T1 &a, const T2 b) {
    return a < b ? a = b, true : false;
}
template <class T1, class T2>
bool chmin(T1 &a, const T2 b) {
    return a > b ? a = b, true : false;
}
template <class T>
istream &operator>>(istream &is, vector<T> &v) {
    for (T &i : v) is >> i;
    return is;
}
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    for (const T &i : v) os << i << ' ';
    return os;
}
void _co() {
    cout << '\n';
}
template <class Head, class... Tail>
void _co(Head &&head, Tail &&...tail) {
    cout << ' ' << head;
    _co(forward<Tail>(tail)...);
}
template <class Head, class... Tail>
void co(Head &&head, Tail &&...tail) {
    cout << head;
    _co(forward<Tail>(tail)...);
}
void ce() {
    cerr << '\n';
}
template <class Head, class... Tail>
void ce(Head &&head, Tail &&...tail) {
    cerr << head << ' ';
    ce(forward<Tail>(tail)...);
}
void sonic() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}
void setp(const int n) {
    cout << fixed << setprecision(n);
}
constexpr int64_t LINF = 1000000000000000001;
constexpr int64_t MOD = 1000000007;
constexpr int64_t MOD_N = 998244353;
constexpr long double EPS = 1e-11;
const double PI = acos(-1);

template <class T>
struct Graph {
    struct edge {
        int64_t from, to;
        T dist;

        bool operator<(const edge &rhs) const {
            return dist < rhs.dist;
        }

        bool operator>(const edge &rhs) const {
            return dist > rhs.dist;
        }

        edge &operator+=(const edge &rhs) {
            to = rhs.to;
            dist += rhs.dist;
            return *this;
        }
        edge operator+(const edge &rhs) {
            return edge(*this) += rhs;
        }
    };

    int64_t V;
    vector<T> dist;
    vector<vector<edge>> edges;

    Graph(int64_t v) : V(v) {
        edges = vector<vector<edge>>(V);
        dist = vector<T>(V, numeric_limits<T>::max());
    }

    void add_edge(int64_t a, int64_t b, T d = 1, bool is_dual = false) {
        edges[a].push_back(edge{a, b, d});
        if (is_dual)
            edges[b].push_back(edge{b, a, d});
    }

    vector<edge> get_edges(int64_t a) {
        return edges[a];
    }
};

int main(void) {
    ll n, m;
    cin >> n >> m;
    string s;
    cin >> s;

    bitset<200000> is_fin;
    Graph<ll> g(n);
    Vec cnt_a(n), cnt_b(n);

    rep(i, m) {
        ll a, b;
        cin >> a >> b;
        --a, --b;
        g.add_edge(a, b, 1, true);
        if (s[a] == 'A')
            cnt_a[b]++;
        else
            cnt_b[b]++;
        if (s[b] == 'A')
            cnt_a[a]++;
        else
            cnt_b[a]++;
    }

    queue<ll> que;
    rep(i, n) {
        if (!cnt_a[i] || !cnt_b[i]) {
            que.push(i);
            is_fin.set(i);
        }
    }

    while (!que.empty()) {
        auto v = que.front();
        que.pop();
        auto es = g.get_edges(v);
        for (auto e : es) {
            if (s[v] == 'A')
                cnt_a[e.to]--;
            else
                cnt_b[e.to]--;

            if (!is_fin[e.to] && (!cnt_a[e.to] || !cnt_b[e.to])) {
                que.push(e.to);
                is_fin.set(e.to);
            }
        }
    }

    bool flg = true;
    rep(i, n) flg &= is_fin[i];

    if (!flg)
        puts("Yes");
    else
        puts("No");

    return 0;
}