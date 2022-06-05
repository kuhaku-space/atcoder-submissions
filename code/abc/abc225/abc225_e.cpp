#line 1 "a.cpp"
#define PROBLEM ""
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
#line 2 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/binary_tree/segment_tree.hpp"

/**
 * @brief セグメント木
 *
 * @tparam T 要素の型
 * @tparam F 関数の型
 */
template <class T, class F>
struct segment_tree {
    int N;
    const T e;
    const F op;
    vector<T> data;

    segment_tree() {}
    /**
     * @brief Construct a new segment tree object
     *
     * @param _n length of array
     * @param _e identity element
     * @param _op binary operation
     */
    segment_tree(int _n, T _e, F &&_op) : e(_e), op(_op) { init(_n, _e); }
    /**
     * @brief Construct a new segment tree object
     *
     * @param _n length of array
     * @param _e identity element
     * @param _op binary operation
     */
    segment_tree(int _n, T _e, const F &_op) : e(_e), op(_op) { init(_n); }

    const T &operator[](int i) const { return this->data[i + N]; }
    T at(int k) const { return this->operator[](k); }
    T get(int k) const { return this->operator[](k); }

    void init(int n, const T val) {
        for (N = 1; N < n; N <<= 1) {}
        this->data.assign(N << 1, val);
    }

    template <class U>
    void build(const vector<U> &v) {
        int n = v.size();
        for (int i = 0; i < n; ++i) this->data[N + i] = T(v[i]);
        for (int i = N - 1; i >= 1; --i)
            this->data[i] = this->op(data[i * 2], this->data[i * 2 + 1]);
    }

    void update(int k, T val) {
        assert(0 <= k && k < N);
        this->data[k += N] = val;
        while ((k >>= 1) >= 1) this->data[k] = this->op(this->data[k * 2], this->data[k * 2 + 1]);
    }
    void add(int k, T val) { this->update(k, val - this->at(k)); }

    bool chmaval(int k, T val) {
        if (this->at(k) >= val) return false;
        this->update(k, val);
        return true;
    }
    bool chmin(int k, T val) {
        if (this->at(k) <= val) return false;
        this->update(k, val);
        return true;
    }

    T all_prod() const { return this->data[1]; }
    T prod(int a, int b) const {
        assert(0 <= a && a <= N);
        assert(0 <= b && b <= N);
        T l = e, r = e;
        for (a += N, b += N; a < b; a >>= 1, b >>= 1) {
            if (a & 1) l = this->op(l, this->data[a++]);
            if (b & 1) r = this->op(this->data[--b], r);
        }
        return this->op(l, r);
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

struct S {
    int x, y;

    bool operator<(const S& rhs) const {
        return (ll)rhs.x * y < (ll)x * rhs.y;
    }
};

int main(void) {
    sonic();
    int n;
    cin >> n;
    vector<S> v(n);
    rep(i, n) cin >> v[i].x >> v[i].y;
    rep(i, n) {
        --v[i].x;
    }
    sort(all(v));

    segment_tree st(n, 0, [](auto a, auto b) {
        return max(a, b);
    });
    rep(i, n) {
        auto it = upper_bound(all(v), S{v[i].x + 1, v[i].y - 1}) - v.begin();
        st.add(i, st.prod(0, it) + 1);
    }
    co(st.all_prod());

    return 0;
}
