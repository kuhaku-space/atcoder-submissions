#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/template/atcoder.hpp"
#pragma GCC target("avx")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
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
#line 6 "/home/kuhaku/atcoder/github/atcoder-lib/lib/template/atcoder.hpp"
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
void Yes(bool is_correct) { std::cout<<(is_correct?"Yes":"No")<<std::endl; }
void YES(bool is_correct) { std::cout<<(is_correct?"YES":"NO")<<std::endl; }
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/tree/weighted_union_find.hpp"

/**
 * @brief 重み付き素集合データ構造
 *
 * @tparam T
 */
template <class T>
struct weighted_union_find {
    weighted_union_find() {}
    weighted_union_find(int size) : _data(size, -1), _weights(size) {}

    int find(int k) {
        if (this->_data[k] < 0) return k;
        auto par = this->find(this->_data[k]);
        this->_weights[k] += this->_weights[this->_data[k]];
        return this->_data[k] = par;
    }

    T get_weight(int t) {
        this->find(t);
        return this->_weights[t];
    }

    bool unite(int x, int y, T w) {
        w += this->get_weight(x) - this->get_weight(y);
        x = find(x), y = find(y);
        if (x == y) return false;
        if (this->_data[x] > this->_data[y]) {
            swap(x, y);
            w *= -1;
        }
        this->_data[x] += this->_data[y];
        this->_data[y] = x;
        this->_weights[y] = w;
        return true;
    }

    T diff(int x, int y) { return this->get_weight(y) - this->get_weight(x); }

  private:
    std::vector<int> _data;
    std::vector<T> _weights;
};
#line 4 "a.cpp"

int main(void) {
    sonic();
    int n;
    cin >> n;
    vector<int> s(n);
    cin >> s;

    weighted_union_find<ll> uf(n + 2);
    rep(i, n - 1) {
        uf.unite(i, i + 3, s[i + 1] - s[i]);
    }

    vector<ll> ans(n + 2);
    vector<ll> mi(3);
    rep(i, n + 2) {
        ans[i] = uf.diff(i % 3, i);
        chmin(mi[i % 3], ans[i]);
    }
    rep(i, n + 2) {
        ans[i] -= mi[i % 3];
    }
    if (ans[0] + ans[1] + ans[2] > s[0]) {
        co("No");
        return 0;
    }
    ll diff = s[0] - ans[0] - ans[1] - ans[2];
    rep(i, n + 2) {
        if (i % 3 == 0)
            ans[i] += diff;
    }
    co("Yes");
    co(ans);

    return 0;
}
