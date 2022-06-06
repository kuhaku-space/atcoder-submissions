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
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/segment_tree/segment_tree_virtual.hpp"

/**
 * @brief セグメント木
 *
 * @tparam T 要素の型
 * @tparam F 関数の型
 */
template <class T>
struct segment_tree {
    int N;
    const T e;
    vector<T> data;

    segment_tree() {}
    segment_tree(int _n, T _e) : e(_e) { this->init(_n, _e); }

    const T &operator[](int i) const { return this->data[i + this->N]; }
    T at(int k) const { return this->operator[](k); }
    T get(int k) const { return this->operator[](k); }

    void init(int n, const T val) {
        for (this->N = 1; this->N < n; this->N <<= 1) {}
        this->data.assign(this->N << 1, val);
    }

    template <class U>
    void build(const vector<U> &v) {
        for (int i = 0, n = v.size(); i < n; ++i) this->data[this->N + i] = T(v[i]);
        for (int i = this->N - 1; i >= 1; --i)
            this->data[i] = this->op(this->data[i * 2], this->data[i * 2 + 1]);
    }

    void apply(int k, T val) {
        assert(0 <= k && k < this->N);
        k += this->N;
        this->data[k] = f(val, this->data[k]);
        while ((k >>= 1) >= 1) this->data[k] = this->op(this->data[k * 2], this->data[k * 2 + 1]);
    }

    T all_prod() const { return this->data[1]; }
    T prod(int a, int b) const {
        assert(0 <= a && b <= this->N);
        T l = e, r = e;
        for (a += this->N, b += this->N; a < b; a >>= 1, b >>= 1) {
            if (a & 1) l = this->op(l, this->data[a++]);
            if (b & 1) r = this->op(this->data[--b], r);
        }
        return this->op(l, r);
    }

  protected:
    virtual T op(T a, T b) const = 0;
    virtual T f(T val, T x) const = 0;
};
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/template/atcoder.hpp"
#pragma GCC target("avx")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#line 6 "/home/kuhaku/atcoder/github/atcoder-lib/lib/template/atcoder.hpp"
using ll = int64_t;
using ld = long double;
#define FOR(i, m, n) for(int i = (m); i < (n); ++i)
#define FORR(i, m, n) for(int i = (m)-1; i >= (n); --i)
#define FORL(i, m, n) for(ll i = (m); i < (n); ++i)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FOR(i, 1, n+1)
#define repr(i, n) FORR(i, n, 0)
#define repnr(i, n) FORR(i, n+1, 1)
#define all(s) (s).begin(), (s).end()
template<class T, class U>
istream &operator>>(istream &is, pair<T, U> &p) { is >> p.first >> p.second; return is; }
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

template <class T>
struct seg_tree : segment_tree<T> {
    seg_tree(int _n, T _e = T()) : segment_tree<T>(_n, _e) {}
    T op(T a, T b) const {
        return a + b;
    }
    T f(T a, T x) const {
        return a;
    }
};

constexpr int sz = 1000005;

int main(void) {
    sonic();
    int n;
    cin >> n;
    vector<int> x(n), y(n);
    rep(i, n) cin >> x[i] >> y[i];

    vector<double> v(sz);
    repn(i, sz - 1) v[i] = log2(i) + v[i - 1];

    auto combi = [&](int a, int b) -> double {
        if (a < 0 || b < 0 || a < b)
            return 0;
        return v[a] - v[a - b] - v[b];
    };
    seg_tree<double> st(n - 1);
    rep(i, n - 1) st.apply(i, combi(x[i + 1] - x[i] + y[i + 1] - y[i], x[i + 1] - x[i]));

    int q;
    cin >> q;
    rep(i, q) {
        int t;
        cin >> t;
        if (t == 1) {
            int k, a, b;
            cin >> k >> a >> b;
            --k;
            x[k] = a, y[k] = b;
            if (k)
                st.apply(k - 1, combi(x[k] - x[k - 1] + y[k] - y[k - 1], x[k] - x[k - 1]));
            if (k != n - 1)
                st.apply(k, combi(x[k + 1] - x[k] + y[k + 1] - y[k], x[k + 1] - x[k]));
        } else {
            int l1, r1, l2, r2;
            cin >> l1 >> r1 >> l2 >> r2;
            --l1, --r1, --l2, --r2;
            if (st.prod(l1, r1) > st.prod(l2, r2)) {
                co("FIRST");
            } else {
                co("SECOND");
            }
        }
    }

    return 0;
}
