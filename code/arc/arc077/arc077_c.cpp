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
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/binary_tree/BIT.hpp"

/**
 * @brief Binary Indexed Tree
 */
template <class T>
struct BIT {
    int N;
    vector<T> data;

    BIT() : N(), data() {}
    BIT(int n, T e = T(0)) : N(n + 1), data(n + 1, e) {}
    BIT(const vector<T> &v) : N(v.size() + 1), data(v.size() + 1) { this->build(v); }

    const T at(int k) const { return this->sum(k + 1) - this->sum(k); }
    const T get(int k) const { return this->at(k); }

    template <class U>
    void build(const vector<U> &v) {
        for (int i = 0, n = v.size(); i < n; ++i) this->add(i, v[i]);
    }

    /**
     * @brief v[k] = val
     *
     * @param k index of array
     * @param val new value
     * @return void
     */
    void update(int k, T val) { this->add(k, val - this->at(k)); }
    /**
     * @brief v[k] += val
     *
     * @param k index of array
     * @param val new value
     * @return void
     */
    void add(int k, T val) {
        assert(0 <= k && k < this->N);
        for (++k; k < N; k += k & -k) this->data[k] += val;
    }
    /**
     * @brief chmax(v[k], val)
     *
     * @param k index of array
     * @param val new value
     * @return bool
     */
    bool chmax(int k, T val) {
        if (this->at(k) >= val) return false;
        this->update(k, val);
        return true;
    }
    /**
     * @brief chmin(v[k], val)
     *
     * @param k index of value
     * @param val new value
     * @return bool
     */
    bool chmin(int k, T val) {
        if (this->at(k) <= val) return false;
        this->update(k, val);
        return true;
    }

    /**
     * @brief v[0] + ... + v[n - 1]
     *
     * @return T
     */
    T all_sum() const { return this->sum(this->N); }
    /**
     * @brief v[0] + ... + v[k - 1]
     *
     * @param k index of array
     * @return T
     */
    T sum(int k) const {
        assert(0 <= k && k <= this->N);
        T res = 0;
        for (; k > 0; k -= k & -k) res += this->data[k];
        return res;
    }
    /**
     * @brief v[a] + ... + v[b - 1]
     *
     * @param a first index of array
     * @param b last index of array
     * @return T
     */
    T sum(int a, int b) const { return a < b ? this->sum(b) - this->sum(a) : 0; }

    /**
     * @brief binary search on BIT
     *
     * @param val target value
     * @return int
     */
    int lower_bound(T val) const {
        if (val <= 0) return 0;
        int k = 1;
        while (k < this->N) k <<= 1;
        int res = 0;
        for (; k > 0; k >>= 1) {
            if (res + k < this->N && this->data[res + k] < val) val -= this->data[res += k];
        }
        return res;
    }
};
#line 3 "/home/kuhaku/atcoder/github/atcoder-lib/lib/binary_tree/BIT_RSQ.hpp"

template <class T>
struct BIT_RSQ {
    BIT_RSQ(int n) : p(n + 1), q(n + 1) {}

    void init(int n) {
        p = BIT<T>(n + 1);
        q = BIT<T>(n + 1);
    }

    auto operator[](int i) const { return this->sum(i + 1) - this->sum(i); }
    auto at(int k) const { return this->operator[](k); }

    template <class U>
    void build(const vector<U> &v) {
        for (int i = 0, n = v.size(); i < n; ++i) {
            p.add(i, v[i]);
            p.add(i + 1, -v[i]);
        }
    }

    /**
     * @brief v[k] = val
     *
     * @param k index of array
     * @param val new value
     */
    void update(int k, T val) { this->add(k, k + 1, val - this->at(k)); }

    /**
     * @brief v[k] += val
     *
     * @param k index of array
     * @param val
     */
    void add(int k, T val) { this->add(k, k + 1, val); }
    /**
     * @brief v[a ... b-1] += val
     *
     * @param a first index of array
     * @param b last index of array
     * @param val
     */
    void add(int a, int b, T val) {
        p.add(a, -val * a);
        p.add(b, val * b);
        q.add(a, val);
        q.add(b, -val);
    }

    /**
     * @brief v[0] + ... v[k - 1]
     *
     * @param k index of array
     * @return auto
     */
    auto sum(int k) const { return p.sum(k) + q.sum(k) * k; }
    /**
     * @brief v[a] + ... + v[b - 1]
     *
     * @param a first index of array
     * @param b last index of array
     * @return auto
     */
    auto sum(int a, int b) const { return this->sum(b) - this->sum(a); }

  private:
    BIT<T> p, q;
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

int main(void) {
    sonic();
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    cin >> a;
    rep(i, n) {
        a[i] = (a[i] + m - 1) % m;
    }
    ll sum = 0;
    rep(i, n - 1) sum += (a[i + 1] + m - a[i]) % m;

    BIT_RSQ<ll> bit(m);
    rep(i, n - 1) {
        if (a[i] < a[i + 1]) {
            bit.add(a[i] + 2, a[i + 1] + 1, -1);
            bit.add(a[i + 1] + 1, a[i + 1] - a[i] - 1);
        } else if (a[i] > a[i + 1]) {
            bit.add(a[i] + 2, m, -1);
            bit.add(0, a[i + 1] + 1, -1);
            bit.add(a[i + 1] + 1, m + a[i + 1] - a[i] - 1);
            bit.add(0, a[i] + 2 - m);
        }
    }

    ll ans = 0;
    rep(i, m) {
        chmin(ans, bit.sum(i + 1));
    }
    co(ans + sum);

    return 0;
}
