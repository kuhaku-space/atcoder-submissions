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

constexpr int calc_c(int n) {
    int res = 1;
    while (n > 64) {
        res *= 64;
        n /= 64;
    }
    return res;
}

template <int N, class D = void>
struct tree64 {
    static constexpr int C = calc_c(N);

    uint64_t map;
    array<tree64<C>, (N - 1) / C + 1> child;

    tree64() : map(0), child() {}

    int bsf(const uint64_t x) const { return __builtin_ctzll(x); }
    int bsr(const uint64_t x) const { return 63 - __builtin_clzll(x); }

    bool insert(const int key) {
        const int pos = key / C;
        map |= 1ULL << pos;
        return child[pos].insert(key % C);
    }

    bool erase(const int key) {
        const int pos = key / C;
        const bool res = child[pos].erase(key % C);
        if (child[pos]._get_map() == 0) {
            map &= ~(1ULL << pos);
        }
        return res;
    }

    bool contains(const int key) const {
        return child[key / C].contains(key % C);
    }

    int min() const {
        const int pos = bsf(map);
        return pos * C + child[pos].min();
    }

    int max() const {
        const int pos = bsr(map);
        return pos * C + child[pos].max();
    }

    int pred(const int key) const {
        const int pos = key / C;
        const int t = child[pos].pred(key % C);
        if (t != -1) {
            return pos * C + t;
        }
        const uint64_t masked = map & ~(~0ULL << pos);
        if (masked == 0) {
            return -1;
        }
        const int pos2 = bsr(masked);
        return pos2 * C + child[pos2].max();
    }

    int succ(const int key) const {
        const int pos = key / C;
        const int t = child[pos].succ(key % C);
        if (t != -1) {
            return pos * C + t;
        }
        const uint64_t masked = map & ~(~0ULL >> (63 - pos));
        if (masked == 0) {
            return -1;
        }
        const int pos2 = bsf(masked);
        return pos2 * C + child[pos2].min();
    }

    uint64_t _get_map() const { return map; }
};

template <int N>
struct tree64<N, typename enable_if<(N <= 64)>::type> {
    uint64_t map;

    tree64() : map(0) {}

    int bsf(const uint64_t x) const { return __builtin_ctzll(x); }
    int bsr(const uint64_t x) const { return 63 - __builtin_clzll(x); }

    bool insert(const int key) {
        const uint64_t pop = 1ULL << key;
        if ((map & pop) != 0) {
            return false;
        } else {
            map |= pop;
            return true;
        }
    }

    bool erase(const int key) {
        const uint64_t pop = 1ULL << key;
        if ((map & pop) != 0) {
            map &= ~pop;
            return true;
        } else {
            return false;
        }
    }

    bool contains(const int key) const { return (map & 1ULL << key) != 0; }

    int min() const { return bsf(map); }

    int max() const { return bsr(map); }

    int pred(const int key) const {
        const uint64_t masked = map & ~(~0ULL << key);
        if (masked == 0) {
            return -1;
        }
        return bsr(masked);
    }

    int succ(const int key) const {
        const uint64_t masked = map & (~0ULL << key);
        if (masked == 0) {
            return -1;
        }
        return bsf(masked);
    }

    uint64_t _get_map() const { return map; }
};

// clang-format on

int main(void) {
    int n;
    cin >> n;
    vector<int> d(n);
    cin >> d;
    sort(all(d));
    d.erase(unique(all(d)), d.end());
    co(d.size());

    return 0;
}
