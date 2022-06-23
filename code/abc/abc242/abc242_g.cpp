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
#line 2 "/home/kuhaku/home/github/algo/lib/algorithm/Mo.hpp"

/**
 * @brief Mo's algorithm
 * @see https://ei1333.hateblo.jp/entry/2017/09/11/211011
 * @see https://snuke.hatenablog.com/entry/2016/07/01/000000
 *
 * @tparam F
 * @tparam G
 */
template <class F, class G>
struct Mo {
    Mo(int n, const F &f, const G &g)
        : left(), right(), order(), _size(n), _nl(0), _nr(0), _ptr(0), _add(f), _del(g) {}

    void add(int l, int r) {
        this->left.emplace_back(l);
        this->right.emplace_back(r);
    }
    void emplace(int l, int r) { return this->add(l, r); }
    void insert(int l, int r) { return this->add(l, r); }

    void build() {
        int q = this->left.size();
        int width = max(1, int(this->_size / sqrt(q)));
        this->order.resize(q);
        std::iota(this->order.begin(), this->order.end(), 0);
        std::sort(this->order.begin(), this->order.end(), [&](int a, int b) -> bool {
            if (this->left[a] / width != this->left[b] / width)
                return this->left[a] < this->left[b];
            return (this->left[a] / width % 2) ^ (this->right[a] < this->right[b]);
        });
    }

    int process() {
        if (this->_ptr == (int)this->order.size()) return -1;
        const auto id = this->order[this->_ptr];
        while (this->_nl > this->left[id]) this->_add(--this->_nl);
        while (this->_nr < this->right[id]) this->_add(this->_nr++);
        while (this->_nl < this->left[id]) this->_del(this->_nl++);
        while (this->_nr > this->right[id]) this->_del(--this->_nr);
        return this->order[this->_ptr++];
    }

  private:
    std::vector<int> left, right, order;
    int _size, _nl, _nr, _ptr;
    const F &_add;
    const G &_del;
};
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
#line 4 "a.cpp"

int main(void) {
    int n;
    cin >> n;
    vector<int> c(n);
    cin >> c;
    rep(i, n) c[i]--;
    vector<int> s(n);
    int sum = 0;
    auto add = [&](int x) {
        if (s[c[x]] & 1)
            ++sum;
        s[c[x]]++;
    };
    auto del = [&](int x) {
        --s[c[x]];
        if (s[c[x]] & 1)
            --sum;
    };
    Mo mo(n, add, del);
    int q;
    cin >> q;
    rep(i, q) {
        int l, r;
        cin >> l >> r;
        mo.insert(l - 1, r);
    }
    mo.build();

    vector<int> ans(q);
    rep(i, q) {
        int x = mo.process();
        ans[x] = sum;
    }
    rep(i, q) co(ans[i]);

    return 0;
}
