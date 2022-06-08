#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/template/template.hpp"
#pragma GCC target("avx2,bmi2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
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
constexpr double PI = M_PI;
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/binary_tree/BIT.hpp"

/**
 * @brief フェニック木
 *
 * @tparam T
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
#line 3 "/home/kuhaku/atcoder/github/atcoder-lib/lib/template/atcoder.hpp"
using ll = int64_t;
using ld = long double;
#define FOR(i, m, n) for(int i = (m); i < int(n); ++i)
#define FORR(i, m, n) for(int i = (m)-1; i >= int(n); --i)
#define FORL(i, m, n) for(int64_t i = (m); i < int64_t(n); ++i)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FOR(i, 1, n+1)
#define repr(i, n) FORR(i, n, 0)
#define repnr(i, n) FORR(i, n+1, 1)
#define all(s) (s).begin(), (s).end()
template<class T, class U>
std::istream &operator>>(std::istream &is, std::pair<T, U> &p) { is >> p.first >> p.second; return is; }
template <class T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) { for (T &i : v) is>>i; return is; }
template <class T, class U>
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &p) {
    return os<<'('<<p.first<< ','<<p.second<<')';
}
template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    for (auto it=v.begin(); it!=v.end(); ++it) { os<<(it==v.begin()?"":" ")<<*it; } return os;
}
template <class Head, class... Tail>
void co(Head&& head, Tail&&... tail) {
    if constexpr(sizeof...(tail)==0) std::cout<<head<<'\n'; else std::cout<<head<<' ',co(forward<Tail>(tail)...);
}
template <class Head, class... Tail>
void ce(Head&& head, Tail&&... tail) {
    if constexpr(sizeof...(tail)==0) std::cerr<<head<<'\n'; else std::cerr<<head<<' ',ce(forward<Tail>(tail)...);
}
template<typename T, typename... Args>
auto make_vector(T x, int arg, Args ...args) {
    if constexpr(sizeof...(args)==0) return std::vector<T>(arg,x); else return std::vector(arg,make_vector<T>(x,args...));
}
void sonic() { std::ios::sync_with_stdio(false); std::cin.tie(nullptr); }
void setp(const int n) { std::cout<<std::fixed<<std::setprecision(n); }
void Yes(bool is_correct=true) { std::cout<<(is_correct?"Yes":"No")<<std::endl; }
void No(bool is_not_correct=true) { Yes(!is_not_correct); }
void YES(bool is_correct=true) { std::cout<<(is_correct?"YES":"NO")<<std::endl; }
void NO(bool is_not_correct=true) { YES(!is_not_correct); }
void Takahashi(bool is_correct=true) { std::cout<<(is_correct?"Takahashi":"Aoki")<<std::endl; }
void Aoki(bool is_not_correct=true) { Takahashi(!is_not_correct); }
#line 4 "a.cpp"

int main(void) {
    sonic();
    int n, p;
    cin >> n >> p;

    int bias = n + 5;
    vector<BIT<ll>> dp;
    rep(i, bias + 10) dp.emplace_back(n + 1);
    repn(i, n) {
        if (i < 10)
            dp[bias - 2].add(i, 26);
        else if (i < 100)
            dp[bias - 3].add(i, 26);
        else if (i < 1000)
            dp[bias - 4].add(i, 26);
        else
            dp[bias - 5].add(i, 26);
    }
    repn(j, n) {
        rep(i, bias + 4) {
            ll sum = 0;
            sum += dp[i + 2].sum(max(0, j - 9), max(0, j)) % p;
            sum += dp[i + 3].sum(max(0, j - 99), max(0, j - 9)) % p;
            sum += dp[i + 4].sum(max(0, j - 999), max(0, j - 99)) % p;
            sum += dp[i + 5].sum(max(0, j - 9999), max(0, j - 999)) % p;
            dp[i].update(j, (dp[i].at(j) + sum * 25) % p);
        }
    }
    ll ans = 0;
    rep(i, bias + 10) {
        if (i + n - bias > 0)
            ans += dp[i].at(n) % p;
    }
    co(ans % p);

    return 0;
}
