#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/home/github/algo/lib/template/template.hpp"
#pragma GCC target("sse4.2,avx2,bmi2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
template <class T, class U>
bool chmax(T &a, const U &b) {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U &b) {
    return (T)b < a ? a = (T)b, true : false;
}
constexpr int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
constexpr double PI = M_PI;
#line 3 "/home/kuhaku/home/github/algo/lib/template/macro.hpp"
#define FOR(i, m, n) for (int i = (m); i < int(n); ++i)
#define FORR(i, m, n) for (int i = (m)-1; i >= int(n); --i)
#define FORL(i, m, n) for (int64_t i = (m); i < int64_t(n); ++i)
#define rep(i, n) FOR (i, 0, n)
#define repn(i, n) FOR (i, 1, n + 1)
#define repr(i, n) FORR (i, n, 0)
#define repnr(i, n) FORR (i, n + 1, 1)
#define all(s) (s).begin(), (s).end()
#line 3 "/home/kuhaku/home/github/algo/lib/template/sonic.hpp"
struct Sonic {
    Sonic() {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
    }

    constexpr void operator()() const {}
} sonic;
#line 5 "/home/kuhaku/home/github/algo/lib/template/atcoder.hpp"
using ll = int64_t;
using ld = long double;
template <class T, class U>
std::istream &operator>>(std::istream &is, std::pair<T, U> &p) {
    return is >> p.first >> p.second;
}
template <class T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) {
    for (T &i : v) is >> i;
    return is;
}
template <class T, class U>
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &p) {
    return os << '(' << p.first << ',' << p.second << ')';
}
template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    for (auto it = v.begin(); it != v.end(); ++it) {
        os << (it == v.begin() ? "" : " ") << *it;
    }
    return os;
}
template <class Head, class... Tail>
void co(Head &&head, Tail &&...tail) {
    if constexpr (sizeof...(tail) == 0) std::cout << head << '\n';
    else std::cout << head << ' ', co(std::forward<Tail>(tail)...);
}
template <class Head, class... Tail>
void ce(Head &&head, Tail &&...tail) {
    if constexpr (sizeof...(tail) == 0) std::cerr << head << '\n';
    else std::cerr << head << ' ', ce(std::forward<Tail>(tail)...);
}
template <typename T, typename... Args>
auto make_vector(T x, int arg, Args... args) {
    if constexpr (sizeof...(args) == 0) return std::vector<T>(arg, x);
    else return std::vector(arg, make_vector<T>(x, args...));
}
void setp(int n) {
    std::cout << std::fixed << std::setprecision(n);
}
void Yes(bool is_correct = true) {
    std::cout << (is_correct ? "Yes" : "No") << '\n';
}
void No(bool is_not_correct = true) {
    Yes(!is_not_correct);
}
void YES(bool is_correct = true) {
    std::cout << (is_correct ? "YES" : "NO") << '\n';
}
void NO(bool is_not_correct = true) {
    YES(!is_not_correct);
}
void Takahashi(bool is_correct = true) {
    std::cout << (is_correct ? "Takahashi" : "Aoki") << '\n';
}
void Aoki(bool is_not_correct = true) {
    Takahashi(!is_not_correct);
}
#line 2 "/home/kuhaku/home/github/algo/lib/tree/weighted_union_find.hpp"

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

    /**
     * @brief v[y] = v[x] + w
     *
     * @param x
     * @param y
     * @param w
     * @return true unite correctly
     * @return false already united
     */
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

    bool same(int x, int y) { return this->find(x) == this->find(y); }
    bool is_same(int x, int y) { return this->same(x, y); }

    /**
     * @brief get diff between x and y
     *
     * @param x
     * @param y
     * @return T v[y] - v[x]
     */
    T diff(int x, int y) { return this->get_weight(y) - this->get_weight(x); }
    T get_diff(int x, int y) { return this->diff(x, y); }

  private:
    std::vector<int> _data;
    std::vector<T> _weights;
};
#line 4 "a.cpp"

int main(void) {
    int n, m, q;
    cin >> n >> m >> q;
    weighted_union_find<ll> uf(n);
    vector<bool> inf(n);
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        --a, --b;
        if (!uf.same(a, b)) {
            uf.unite(a, b, c);
        } else {
            inf[a] = inf[a] | (uf.diff(a, b) != c);
        }
    }
    rep(i, n) {
        inf[uf.find(i)] = inf[uf.find(i)] | inf[i];
    }

    while (q--) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        if (!uf.same(x, y)) {
            co("nan");
        } else if (inf[uf.find(x)]) {
            co("inf");
        } else {
            co(uf.diff(x, y));
        }
    }

    return 0;
}
