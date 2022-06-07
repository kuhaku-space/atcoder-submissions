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
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/tree/union_find.hpp"

/**
 * @brief 素集合データ構造
 *
 */
struct union_find {
    union_find() : data() {}
    union_find(int _n) : data(_n, -1) {}

    int root(int x) { return this->data[x] < 0 ? x : this->data[x] = this->root(this->data[x]); }
    int get_root(int x) { return this->root(x); }

    bool is_root(int x) { return this->data[x] < 0; }

    bool unite(int x, int y) {
        x = this->root(x), y = this->root(y);
        if (x == y) return false;
        if (this->data[x] > this->data[y]) swap(x, y);
        this->data[x] += this->data[y];
        this->data[y] = x;
        return true;
    }

    int size(int x) { return -(this->data[this->root(x)]); }
    int get_size(int x) { return this->size(x); }

    bool same(int x, int y) { return this->root(x) == this->root(y); }
    bool is_same(int x, int y) { return this->same(x, y); }

  private:
    vector<int> data;
};
#line 4 "a.cpp"

int main(void) {
    sonic();
    int n, m;
    cin >> n >> m;
    vector<int> d(n);
    cin >> d;

    if (accumulate(all(d), 0LL) != 2 * n - 2) {
        co(-1);
        return 0;
    }

    union_find uf(n);
    vector<int> a(m), b(m);
    rep(i, m) cin >> a[i] >> b[i];
    rep(i, m) {
        --a[i], --b[i];
        --d[a[i]], --d[b[i]];
        if (!uf.unite(a[i], b[i])) {
            co(-1);
            return 0;
        }
    }

    rep(i, n) {
        if (d[i] < 0) {
            co(-1);
            return 0;
        }
    }

    vector<vector<int>> v(n);
    rep(i, n) v[i] = vector<int>(d[i], i);
    rep(i, n) {
        int r = uf.root(i);
        if (i != r) {
            if (v[i].size() > v[r].size())
                swap(v[i], v[r]);
            v[r].insert(v[r].end(), all(v[i]));
        }
    }

    priority_queue<pair<int, int>> pq;
    rep(i, n) {
        if (uf.is_root(i) && v[i].size())
            pq.emplace(v[i].size(), i);
    }

    vector<pair<int, int>> ans;
    while (pq.size() >= 2) {
        auto [e, i] = pq.top();
        pq.pop();
        auto [f, j] = pq.top();
        pq.pop();
        ans.emplace_back(v[i].back(), v[j].back());
        v[i].pop_back();
        v[j].pop_back();
        uf.unite(i, j);
        if (uf.is_root(j)) {
            swap(i, j);
            swap(v[i], v[j]);
        }
        v[i].insert(v[i].end(), all(v[j]));
        e += f - 2;
        if (e)
            pq.emplace(e, i);
    }

    if (pq.size()) {
        co(-1);
        return 0;
    }

    for (auto p : ans) {
        co(p.first + 1, p.second + 1);
    }

    return 0;
}
