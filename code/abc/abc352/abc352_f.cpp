#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/home/github/algo/lib/template/template.hpp"
#pragma GCC target("sse4.2,avx2,bmi2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
template <class T, class U>
constexpr bool chmax(T &a, const U &b) {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
constexpr bool chmin(T &a, const U &b) {
    return (T)b < a ? a = (T)b, true : false;
}
constexpr std::int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
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
        std::cout << std::fixed << std::setprecision(20);
    }

    constexpr void operator()() const {}
} sonic;
#line 5 "/home/kuhaku/home/github/algo/lib/template/atcoder.hpp"
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
#line 3 "/home/kuhaku/home/github/algo/lib/tree/weighted_union_find.hpp"

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
        if (_data[k] < 0) return k;
        int par = find(_data[k]);
        _weights[k] += _weights[_data[k]];
        return _data[k] = par;
    }

    T get_weight(int t) {
        find(t);
        return _weights[t];
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
        w += get_weight(x) - get_weight(y);
        x = find(x), y = find(y);
        if (x == y) return false;
        if (_data[x] > _data[y]) {
            std::swap(x, y);
            w *= -1;
        }
        _data[x] += _data[y];
        _data[y] = x;
        _weights[y] = w;
        return true;
    }

    int size(int x) { return -_data[find(x)]; }

    bool same(int x, int y) { return find(x) == find(y); }
    bool is_same(int x, int y) { return same(x, y); }

    /**
     * @brief get diff between x and y
     *
     * @param x
     * @param y
     * @return T v[y] - v[x]
     */
    T diff(int x, int y) { return get_weight(y) - get_weight(x); }
    T get_diff(int x, int y) { return diff(x, y); }

  private:
    std::vector<int> _data;
    std::vector<T> _weights;
};
#line 4 "a.cpp"

int main(void) {
    int n, m;
    cin >> n >> m;
    weighted_union_find<int> uf(n);
    rep (i, m) {
        int x, y, c;
        cin >> x >> y >> c;
        uf.unite(x - 1, y - 1, -c);
    }

    vector<int> leader(n);
    rep (idx, n) {
        leader[idx] = idx;
        rep (i, idx) {
            if (uf.same(i, idx)) {
                leader[idx] = i;
                break;
            }
        }
    }

    int bit = 0;
    vector<int> pos(n, -1);
    vector<unsigned> v(n);
    vector<int> ord(n);
    iota(all(ord), 0);
    sort(all(ord), [&leader, &uf](int x, int y) {
        if (leader[x] == leader[y])
            return x < y;
        if (uf.size(x) == uf.size(y))
            return leader[x] < leader[y];
        return uf.size(x) > uf.size(y);
    });
    auto dfs = [&](auto self, int k) -> void {
        if (k == n || k <= n - 2 && uf.size(ord[k]) == 1) {
            rep (i, n) {
                if (pos[i] != -1)
                    v[i] |= 1 << pos[i];
            }
            return;
        }
        int idx = ord[k];
        if (leader[idx] == idx) {
            rep (x, n) {
                if (bit >> x & 1)
                    continue;
                pos[idx] = x;
                bit ^= 1 << x;
                self(self, k + 1);
                pos[idx] = -1;
                bit ^= 1 << x;
            }
        } else {
            int l = leader[idx];
            int x = pos[l] + uf.diff(l, idx);
            if (0 <= x && x < n && (~bit >> x & 1)) {
                pos[idx] = x;
                bit ^= 1 << x;
                self(self, k + 1);
                pos[idx] = -1;
                bit ^= 1 << x;
            }
        }
    };

    dfs(dfs, 0);
    vector<int> ans(n, -1);
    rep (i, n) {
        if (popcount(v[i]) == 1) {
            rep (j, n) {
                if (v[i] >> j & 1)
                    ans[i] = j + 1;
            }
        }
    }
    co(ans);

    return 0;
}
