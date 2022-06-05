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
#line 2 "/home/kuhaku/kuhaku/github/atcoder-lib/lib/binary_tree/BIT.hpp"

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
    const T get(int k) const { return this->operator[](k); }

    template <class U>
    void build(const vector<U> &v) {
        int n = v.size();
        for (int i = 0; i < n; ++i) this->add(i, v[i]);
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
    T sum(int a, int b) const { return this->sum(b) - this->sum(a); }

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
            if (res + k < N && this->data[res + k] < val) val -= this->data[res += k];
        }
        return res;
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

int main(void) {
    sonic();
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<BIT<int>> bit(3, BIT<int>(3 * n));
    vector<BIT<int>> tib(3, BIT<int>(3 * n));
    rep(i, 3 * n) {
        if (s[i] == 'A') {
            bit[0].add(i, 1);
            tib[0].add(3 * n - 1 - i, 1);
        } else if (s[i] == 'B') {
            bit[1].add(i, 1);
            tib[1].add(3 * n - 1 - i, 1);
        } else {
            bit[2].add(i, 1);
            tib[2].add(3 * n - 1 - i, 1);
        }
    }

    string ans(3 * n, '0');
    vector<int> x(3);
    char cnt = '1';
    rep(_, 6) {
        bool flg = false;
        rep(i, 3 * n) {
            if (ans[i] == '0') {
                x[0] = s[i] - 'A';
                flg = true;
                break;
            }
        }
        repr(i, 3 * n) {
            if (ans[i] == '0' && s[i] - 'A' != x[0]) {
                x[2] = s[i] - 'A';
                break;
            }
        }
        if (!flg)
            break;
        x[1] = 3 - x[0] - x[2];
        int maxi = 0;
        repn(i, n) {
            auto it1 = bit[x[0]].lower_bound(i);
            if (it1 >= 3 * n)
                continue;
            auto it2 = tib[x[2]].lower_bound(i);
            if (it2 >= 3 * n)
                continue;
            if (bit[x[1]].sum(it1 + 1, 3 * n - it2) >= i)
                maxi = i;
        }

        int sum = 0;
        int idx = 0;
        rep(i, 3 * n) {
            if (idx < 2 && bit[x[idx]].at(i)) {
                bit[x[idx]].add(i, -1);
                tib[x[idx]].add(3 * n - 1 - i, -1);
                ans[i] = cnt;
                ++sum;
            }
            if (sum == maxi) {
                sum = 0;
                ++idx;
            }
        }
        sum = 0;
        repr(i, 3 * n) {
            if (sum < maxi && bit[x[2]].at(i)) {
                bit[x[2]].add(i, -1);
                tib[x[2]].add(3 * n - 1 - i, -1);
                ans[i] = cnt;
                ++sum;
            }
        }
        ++cnt;
    }
    co(ans);

    return 0;
}
