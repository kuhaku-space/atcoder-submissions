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

template <class T, class F>
struct segment_tree {
    int N;
    const T e;
    const F op;
    vector<T> data;

    segment_tree() {}
    segment_tree(int _n, const T &_e, const F &_op) : e(_e), op(_op) {
        init(_n);
    }

    const T &operator[](int i) const {
        return data[i + N];
    }
    T &operator[](int i) {
        return data[i + N];
    }

    T at(int k) const {
        return data[k + N];
    }

    void init(int n) {
        for (N = 1; N < n; N <<= 1)
            ;
        data.assign(N << 1, e);
    }

    template <class U>
    void build(const vector<U> &v) {
        int n = v.size();
        for (int i = 0; i < n; ++i)
            data[N + i] = T(v[i]);
        for (int i = N - 1; i >= 1; --i)
            data[i] = op(data[i * 2], data[i * 2 + 1]);
    }

    void update(int k, const T &x) {
        assert(0 <= k && k < N);
        data[k += N] = x;
        while ((k >>= 1) >= 1)
            data[k] = op(data[k * 2], data[k * 2 + 1]);
    }

    void add(int k, const T &x) {
        assert(0 <= k && k < N);
        data[k += N] += x;
        while ((k >>= 1) >= 1)
            data[k] = op(data[k * 2], data[k * 2 + 1]);
    }

    T query(int a, int b) {
        assert(0 <= a && a <= N);
        assert(0 <= b && b <= N);
        T l = e, r = e;
        for (a += N, b += N; a < b; a >>= 1, b >>= 1) {
            if (a & 1)
                l = op(l, data[a++]);
            if (b & 1)
                r = op(data[--b], r);
        }
        return op(l, r);
    }

    template<class U>
    void f(const U &v, const vector<T> &idx) {
        for (auto i : idx)
            update(i, v[i]);
    }
};

int main(void) {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> p(m);
    rep(i, m) cin >> p[i].first >> p[i].second;
    sort(all(p));

    segment_tree st(n + 1, 0, [](auto a, auto b) {
        return max(a, b);
    });
    auto st2 = st;
    vector<int> v;
    rep(i, m) {
        if (i && p[i].first != p[i - 1].first) {
            st.f(st2, v);
            v.clear();
        }
        st2.update(p[i].second, max(st.query(0, p[i].second) + 1, st[p[i].second]));
        v.emplace_back(p[i].second);
        // ce(st2.data);
    }
    st.f(st2, v);
    co(st.query(0, n + 1));

    return 0;
}
