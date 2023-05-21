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
#line 2 "/home/kuhaku/home/github/algo/lib/algorithm/mo.hpp"

/**
 * @brief Mo's algorithm
 * @see https://ei1333.hateblo.jp/entry/2017/09/11/211011
 * @see https://snuke.hatenablog.com/entry/2016/07/01/000000
 *
 * @tparam F
 * @tparam G
 */
template <class F, class G, class H = F, class I = G>
struct Mo {
    Mo(int n, F f, G g)
        : _left(), _right(), _order(), _size(n), _nl(0), _nr(0), _ptr(0), _addl(f), _addr(f),
          _dell(g), _delr(g) {}
    Mo(int n, F fl, H fr, G gl, I gr)
        : _left(), _right(), _order(), _size(n), _nl(0), _nr(0), _ptr(0), _addl(fl), _addr(fr),
          _dell(gl), _delr(gr) {}

    void input(int q, int bias = 1, int closed = 0) {
        for (int i = 0; i < q; ++i) {
            int l, r;
            std::cin >> l >> r;
            this->add(l - bias, r - bias + closed);
        }
    }

    void add(int l, int r) {
        this->_left.emplace_back(l);
        this->_right.emplace_back(r);
    }
    void emplace(int l, int r) { return this->add(l, r); }
    void insert(int l, int r) { return this->add(l, r); }

    void build() {
        int q = this->_left.size();
        int width = std::max(1, int(this->_size / sqrt(q)));
        this->_order.resize(q);
        std::iota(this->_order.begin(), this->_order.end(), 0);
        std::sort(this->_order.begin(), this->_order.end(), [&](int a, int b) -> bool {
            if (this->_left[a] / width != this->_left[b] / width)
                return this->_left[a] < this->_left[b];
            return (this->_left[a] / width % 2 == 0) ? (this->_right[a] < this->_right[b])
                                                     : (this->_right[b] < this->_right[a]);
        });
    }

    int process() {
        if (this->_ptr == (int)this->_order.size()) return -1;
        const auto id = this->_order[this->_ptr];
        while (this->_nl > this->_left[id]) this->_addl(--this->_nl);
        while (this->_nr < this->_right[id]) this->_addr(this->_nr++);
        while (this->_nl < this->_left[id]) this->_dell(this->_nl++);
        while (this->_nr > this->_right[id]) this->_delr(--this->_nr);
        return this->_order[this->_ptr++];
    }

  private:
    std::vector<int> _left, _right, _order;
    int _size, _nl, _nr, _ptr;
    F _addl;
    H _addr;
    G _dell;
    I _delr;
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
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    cin >> a;

    ll sum = 0;
    vector<ll> c(200005);
    auto add = [&](int x) {
        x = a[x];
        ++c[x];
        sum += (c[x] - 2) * (c[x] - 1) / 2;
    };
    auto del = [&](int x) {
        x = a[x];
        --c[x];
        sum -= c[x] * (c[x] - 1) / 2;
    };

    Mo mo(n, add, del);
    mo.input(q, 1, 1);
    mo.build();

    vector<ll> ans(q);
    rep (i, q) {
        int x = mo.process();
        ans[x] = sum;
    }
    for (auto x : ans) co(x);

    return 0;
}
