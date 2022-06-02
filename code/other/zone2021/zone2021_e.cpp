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

// clang-format on

int main(void) {
    sonic();
    int r, c;
    cin >> r >> c;
    auto a = make_vector(0, r, c - 1);
    auto b = make_vector(0, r - 1, c);
    cin >> a >> b;

    auto dijkstra = [&](int n, int s = 0,
                        int inf = numeric_limits<int>::max()) -> vector<int> {
        struct _edge {
            int to;
            int dist;
            bool operator<(const _edge &rhs) const {
                return dist < rhs.dist;
            }
            bool operator>(const _edge &rhs) const {
                return rhs < *this;
            }
        };
        vector<int> dist(n << 1, inf);
        priority_queue<_edge> p_que;
        p_que.push(_edge{s, 0});
        dist[s] = 0;
        while (!p_que.empty()) {
            _edge e = p_que.top();
            p_que.pop();
            if (dist[e.to] < e.dist)
                continue;
            bool f = false;
            if (e.to >= n) {
                f = true;
                e.to -= n;
            }
            int x = e.to / c;
            int y = e.to % c;
            if (y < c - 1) {
                if (chmin(dist[x * c + y + 1], -e.dist + a[x][y]))
                    p_que.push(_edge{x * c + y + 1, e.dist - a[x][y]});
            }
            if (y > 0)
                if (chmin(dist[x * c + y - 1], -e.dist + a[x][y - 1]))
                    p_que.push(_edge{x * c + y - 1, e.dist - a[x][y - 1]});
            if (x < r - 1) {
                if (f) {
                    if (chmin(dist[n + (x + 1) * c + y], -e.dist + b[x][y]))
                        p_que.push(
                            _edge{n + (x + 1) * c + y, e.dist - b[x][y]});
                } else {
                    if (chmin(dist[(x + 1) * c + y], -e.dist + b[x][y]))
                        p_que.push(_edge{(x + 1) * c + y, e.dist - b[x][y]});
                }
            }
            if (!f) {
                repn(i, r) {
                    if (x - i < 0)
                        break;
                    if (chmin(dist[n + (x - i) * c + y], -e.dist + i + 1))
                        p_que.push(_edge{n + (x - i) * c + y, e.dist - i - 1});
                }
            }
        }
        return dist;
    };

    auto ans = dijkstra(r * c);
    // ce(ans);
    co(min(ans[r * c - 1], ans[r * c * 2 - 1]));

    return 0;
}
