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

// clang-format on

int main(void) {
    int n, m;
    cin >> n >> m;
    vector<int> p(n + m);
    cin >> p;
    rep(i, n + m) p[i]--;

    vector<int> pos(n + m);
    rep(i, n + m) {
        pos[p[i]] = i;
    }

    auto inA = [&](int x) {
        return pos[x] < n;
    };

    auto inB = [&](int x) {
        return pos[x] >= n;
    };

    auto f = [&](int x, int y) {
        int a = pos[x];
        int b = pos[y];
        swap(p[a], p[b]);
        swap(pos[x], pos[y]);
    };

    int ans = 0;
    deque<int> deq;
    unordered_set<int> s, t;
    rep(i, n) {
        if (pos[i] != i) {
            s.insert(i);
            if (p[i] < n && inB(i))
                deq.emplace_front(i);
            else if (p[i] >= n && inB(i))
                deq.emplace_back(i);
        }
    }
    FOR(i, n, n + m) {
        if (pos[i] != i) {
            t.insert(i);
            if (p[i] >= n && inA(i))
                deq.emplace_front(i);
            else if (p[i] < n && inA(i))
                deq.emplace_back(i);
        }
    }
    int idx = 0;
    while (s.size() || t.size()) {
        // ce("!!!", idx, "!!!");
        while (deq.size()) {
            auto x = deq.front();
            deq.pop_front();
            if (pos[x] == x)
                continue;
            auto y = p[x];
            f(x, y);
            ++ans;
            s.erase(x);
            t.erase(x);
            if (pos[y] == y) {
                s.erase(y);
                t.erase(y);
            }
            if (pos[y] == y) {
            } else if (y < n && p[y] < n && inB(y) || y >= n && p[y] >= n && inA(y)) {
                deq.emplace_front(y);
            } else if (y < n && p[y] >= n && inB(y) || y >= n && p[y] < n && inA(y)) {
                deq.emplace_back(y);
            }
        }

        if (pos[idx] != idx) {
            int y;
            if (idx < n) {
                if (t.size())
                    y = *t.begin();
                else
                    y = n;
            } else {
                if (s.size())
                    y = *s.begin();
                else
                    y = 0;
            }
            f(idx, y);
            ++ans;
            if (pos[idx] == idx) {
                s.erase(idx);
                t.erase(idx);
            } else {
                if (idx < n && p[idx] < n && inB(idx) || idx >= n && p[idx] >= n && inA(idx)) {
                    deq.emplace_front(idx);
                } else if (idx < n && p[idx] >= n && inB(idx) || idx >= n && p[idx] < n && inA(idx)) {
                    deq.emplace_back(idx);
                }
            }
            if (pos[y] == y) {
                s.erase(y);
                t.erase(y);
            } else {
                if (y < n)
                    s.insert(y);
                else
                    t.insert(y);
            }
            if (pos[y] == y) {
            } else if (y < n && p[y] < n && inB(y) || y >= n && p[y] >= n && inA(y)) {
                deq.emplace_front(y);
            } else if (y < n && p[y] >= n && inB(y) || y >= n && p[y] < n && inA(y)) {
                deq.emplace_back(y);
            }
        }
        ++idx;
        idx %= n + m;
        /*
        ce(p);
        ce(pos);
        ce("s:");
        for (auto i : s)
            ce(i);
        ce("t:");
        for (auto i : t)
            ce(i);
        ce(ans);
        if (idx == 0)
            break;
            */
    }

    co(ans);

    return 0;
}
