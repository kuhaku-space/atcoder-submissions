#line 1 "a.cpp"
#define PROBLEM "https://atcoder.jp/contests/abc241/tasks/abc241_e"
#line 2 "/home/kuhaku/atcoder/github/algo/lib/template/template.hpp"
#pragma GCC target("sse4.2,avx2,bmi2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
template <class T, class U>
bool chmax(T &a, const U &b) {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U &b) {
    return (T)b < a ? a = (T)b, true : false;
}
constexpr std::int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
constexpr double PI = M_PI;
#line 2 "/home/kuhaku/atcoder/github/algo/lib/algorithm/doubling.hpp"

/**
 * @brief ダブリング
 *
 * @tparam L
 * @tparam Monoid モノイド
 */
template <int L, class Monoid = void>
struct Doubling {
  private:
    using T = Monoid::value_type;

  public:
    template <class U>
    Doubling(const std::vector<int> &to, const std::vector<U> &v) : Doubling(to.size()) {
        build(to, v);
    }
    std::pair<int, T> jump(int f, std::uint64_t k) { return solve(f, k); }
    std::pair<int, T> solve(int f, std::uint64_t k) {
        T res = Monoid::id;
        for (int cnt = 0; k > 0; k >>= 1, ++cnt) {
            if (k & 1) {
                res = Monoid::op(res, data[cnt][f]);
                f = table[cnt][f];
            }
        }
        return std::make_pair(f, res);
    }

  private:
    int _size;
    std::vector<std::vector<int>> table;
    std::vector<std::vector<T>> data;

    Doubling(int n) : _size(n), table(L, std::vector<int>(n)), data(L, std::vector<T>(n)) {}

    template <class U>
    void build(const std::vector<int> &to, const std::vector<U> &v) {
        assert(to.size() == v.size());
        for (int i = 0; i < _size; ++i) {
            assert(-1 <= to[i] && to[i] < _size);
            table[0][i] = to[i];
            data[0][i] = v[i];
        }

        for (int i = 0; i < L - 1; ++i) {
            for (int j = 0; j < _size; ++j) {
                int k = table[i][j];
                if (k != -1) {
                    table[i + 1][j] = table[i][k];
                    data[i + 1][j] = Monoid::op(data[i][j], data[i][k]);
                } else {
                    table[i + 1][j] = table[i][j];
                    data[i + 1][j] = data[i][j];
                }
            }
        }
    }
};

/**
 * @brief ダブリング
 *
 * @tparam L
 */
template <int L>
struct Doubling<L, void> {
    Doubling(const std::vector<int> &v) : Doubling(v.size()) { build(v); }

    int jump(int f, std::uint64_t k) { return solve(f, k); }
    int solve(int f, std::uint64_t k) {
        for (int cnt = 0; k > 0; k >>= 1, ++cnt) {
            if (k & 1) f = data[cnt][f];
        }
        return f;
    }

  private:
    int _size;
    std::vector<std::vector<int>> data;

    Doubling(int n) : _size(n), data(L, std::vector<int>(n)) {}

    void build(const std::vector<int> &v) {
        for (int i = 0; i < _size; ++i) {
            assert(-1 <= v[i] && v[i] < _size);
            data[0][i] = v[i];
        }

        for (int i = 0; i < L - 1; ++i) {
            for (int j = 0; j < _size; ++j) {
                if (data[i][j] != -1) data[i + 1][j] = data[i][data[i][j]];
            }
        }
    }
};
#line 3 "/home/kuhaku/atcoder/github/algo/lib/template/macro.hpp"
#define FOR(i, m, n) for (int i = (m); i < int(n); ++i)
#define FORR(i, m, n) for (int i = (m)-1; i >= int(n); --i)
#define FORL(i, m, n) for (int64_t i = (m); i < int64_t(n); ++i)
#define rep(i, n) FOR (i, 0, n)
#define repn(i, n) FOR (i, 1, n + 1)
#define repr(i, n) FORR (i, n, 0)
#define repnr(i, n) FORR (i, n + 1, 1)
#define all(s) (s).begin(), (s).end()
#line 3 "/home/kuhaku/atcoder/github/algo/lib/template/sonic.hpp"
struct Sonic {
    Sonic() {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
    }

    constexpr void operator()() const {}
} sonic;
#line 5 "/home/kuhaku/atcoder/github/algo/lib/template/atcoder.hpp"
using namespace std;
using ll = std::int64_t;
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

struct Monoid {
    using value_type = ll;
    static constexpr ll id = 0;
    static constexpr ll op(const ll &lhs, const ll &rhs) {
        return lhs + rhs;
    }
};

int main(void) {
    int n;
    ll k;
    cin >> n >> k;
    vector<int> a(n);
    cin >> a;
    vector<int> to(n);
    rep (i, n) to[i] = (i + a[i]) % n;
    Doubling<40, Monoid> db(to, a);
    co(db.solve(0, k).second);

    return 0;
}
