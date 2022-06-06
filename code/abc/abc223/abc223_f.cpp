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
#line 2 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/binary_tree/segment_tree_virtual.hpp"

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
        assert(0 <= a && a <= this->N);
        assert(0 <= b && b <= this->N);
        T l = e, r = e;
        for (a += this->N, b += this->N; a < b; a >>= 1, b >>= 1) {
            if (a & 1) l = this->op(l, this->data[a++]);
            if (b & 1) r = this->op(this->data[--b], r);
        }
        return this->op(l, r);
    }

  protected:
    virtual T op(T a, T b) const = 0;
    virtual T f(T val, T x) = 0;
};
#line 3 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/binary_tree/RSQ.hpp"

template <class T>
struct RSMQ {
    struct segment_tree_max : segment_tree<pair<T, T>> {
        segment_tree_max(int _n, pair<T, T> _e) : segment_tree<pair<T, T>>(_n, _e) {}
        pair<T, T> op(pair<T, T> a, pair<T, T> b) const {
            return make_pair(max(a.first, a.second + b.first), a.second + b.second);
        }
        pair<T, T> f(pair<T, T> val, pair<T, T> x) {
            T y = val.second + x.second;
            return make_pair(y, y);
        }
    };

    segment_tree_max st;

    RSMQ(int _n, T _e) : st(_n + 1, make_pair(_e, T(0))) {}

    void apply(int k, T val) { this->apply(k, k + 1, val); }
    void apply(int a, int b, T val) {
        this->st.add(a, make_pair(val, val));
        this->st.add(b, make_pair(-val, -val));
    }
    void add(int k, T val) { this->apply(k, k + 1, val); }
    void add(int a, int b, T val) { this->apply(a, b, val); }

    T prod(int a, int b) { return this->st.prod(0, a).second + this->st.prod(a, b).first; }

    T at(int k) { return this->st.prod(0, k).second; }
    T get(int k) { return this->at(k); }
};

template <class T>
struct RSmQ {
    struct segment_tree_min : segment_tree<pair<T, T>> {
        segment_tree_min(int _n, pair<T, T> _e) : segment_tree<pair<T, T>>(_n, _e) {}
        pair<T, T> op(pair<T, T> a, pair<T, T> b) const {
            return make_pair(min(a.first, a.second + b.first), a.second + b.second);
        }
        pair<T, T> f(pair<T, T> val, pair<T, T> x) {
            T y = val.second + x.second;
            return make_pair(y, y);
        }
    };
    segment_tree_min st;

    RSmQ(int _n, T _e) : st(_n + 1, make_pair(_e, T(0))) {
        this->st.init(_n + 1, make_pair(T(0), T(0)));
    }

    void apply(int k, T val) { this->apply(k, k + 1, val); }
    void apply(int a, int b, T val) {
        this->st.apply(a, make_pair(val, val));
        this->st.apply(b, make_pair(-val, -val));
    }
    void add(int k, T val) { this->apply(k, k + 1, val); }
    void add(int a, int b, T val) { this->apply(a, b, val); }

    T prod(int a, int b) { return this->st.prod(0, a).second + this->st.prod(a, b).first; }

    T at(int k) { return this->st.prod(0, k + 1).second; }
    T get(int k) { return this->at(k); }
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
    int n, q;
    cin >> n >> q;
    RSmQ<ll> st(n, Inf);
    string s;
    cin >> s;
    rep(i, n) {
        if (s[i] == '(') {
            st.add(i, n, 1);
        } else {
            st.add(i, n, -1);
        }
    }

    rep(i, q) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r;
            cin >> l >> r;
            --l, --r;
            if (s[l] == '(' && s[r] == ')')
                st.add(l, r, -2);
            else if (s[l] == ')' && s[r] == '(')
                st.add(l, r, 2);
            swap(s[l], s[r]);
        } else {
            int l, r;
            cin >> l >> r;
            --l, --r;
            int x = st.at(l - 1);
            if (x == st.at(r) && x <= st.prod(l, r))
                co("Yes");
            else
                co("No");
        }
    }

    return 0;
}
