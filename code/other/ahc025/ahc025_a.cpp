#ifndef LOCAL
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#endif

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <iostream>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <tuple>
#include <vector>

template <class T, class U>
constexpr bool chmax(T &a, const U &b) {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
constexpr bool chmin(T &a, const U &b) {
    return (T)b < a ? a = (T)b, true : false;
}

namespace lib {

using int128_t = __int128_t;

struct Xorshift {
    using result_type = unsigned int;
    constexpr Xorshift() : x(123456789), y(362436069), z(521288629), w(88675123) {}

    static constexpr result_type min() { return std::numeric_limits<result_type>::min(); }
    static constexpr result_type max() { return std::numeric_limits<result_type>::max(); }
    result_type operator()() {
        result_type t = (x ^ (x << 11));
        x = y, y = z, z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }

    result_type rand_range(int a, int b) { return a + operator()() % (b - a + 1); }
    double random() { return (double)operator()() / max(); }

  private:
    result_type x, y, z, w;
} xor128;

}  // namespace lib
using namespace lib;

struct item_relation {
    item_relation(int n) : N(n), is_light(n), is_heavy(n), is_same(n) {}

    bool is_lighter(int x, int y) const { return is_light[x] >> y & 1; }
    bool is_heavier(int x, int y) const { return is_heavy[x] >> y & 1; }

    bool is_possible_to_be_lighter(int x, int y) const {
        return (~is_heavy[x] >> y & 1) && (~is_same[x] >> y & 1);
    }

    bool is_possible_to_be_heavier(int x, int y) const {
        return (~is_light[x] >> y & 1) && (~is_same[x] >> y & 1);
    }

    void set_relation(int x, int y, int op) {
        int128_t visited = 0;
        auto dfs_h = [&](auto self, int idx) -> void {
            is_light[idx] |= is_light[x];
            visited |= int128_t(1) << idx;
            for (int i = 0; i < N; ++i) {
                if (visited >> i & 1) continue;
                if (is_heavy[idx] >> i & 1) self(self, i);
            }
        };
        auto dfs_l = [&](auto self, int idx) -> void {
            is_heavy[idx] |= is_heavy[y];
            visited |= int128_t(1) << idx;
            for (int i = 0; i < N; ++i) {
                if (visited >> i & 1) continue;
                if (is_light[idx] >> i & 1) self(self, i);
            }
        };
        if (op == 0) {
            is_same[x] |= int128_t(1) << y, is_same[y] |= int128_t(1) << x;
            is_light[x] |= is_light[y], is_light[y] = is_light[x];
            is_heavy[x] |= is_heavy[y], is_heavy[y] = is_heavy[x];
            visited = 0, dfs_h(dfs_h, x);
            visited = 0, dfs_h(dfs_h, y);
            visited = 0, dfs_l(dfs_l, x);
            visited = 0, dfs_l(dfs_l, y);
        } else {
            if (op == 1) std::swap(x, y);
            is_light[x] |= is_light[y], is_heavy[y] |= is_heavy[x];
            is_light[x] |= int128_t(1) << y, is_heavy[y] |= int128_t(1) << x;
            visited = 0, dfs_h(dfs_h, x);
            visited = 0, dfs_l(dfs_l, y);
        }
    }

  private:
    const int N;
    std::vector<int128_t> is_light, is_heavy, is_same;
};

struct group_relation {
    group_relation(int d) : D(d), is_light(d), is_heavy(d), is_same(d) {}

    int compare(int x, int y) const {
        if (is_lighter(x, y)) return -1;
        if (is_heavier(x, y)) return 1;
        return equals(x, y) ? 0 : 2;
    }

    bool is_unique(int x) const { return unique >> x & 1; }
    bool is_lighter(int x, int y) const { return is_light[x] >> y & 1; }
    bool is_heavier(int x, int y) const { return is_heavy[x] >> y & 1; }
    bool equals(int x, int y) const { return is_same[x] >> y & 1; }

    bool is_possible_to_be_lighter(int x, int y) const {
        return (~is_heavy[x] >> y & 1) && (~is_same[x] >> y & 1);
    }

    bool is_possible_to_be_heavier(int x, int y) const {
        return (~is_light[x] >> y & 1) && (~is_same[x] >> y & 1);
    }

    int get_lightest_idx(int x) const {
        while (true) {
            std::vector<int> candidate_idx;
            for (int i = 0; i < D; ++i) {
                if (is_heavier(x, i)) candidate_idx.emplace_back(i);
            }
            if (candidate_idx.empty()) break;
            x = candidate_idx[xor128() % candidate_idx.size()];
        }
        return x;
    }

    int get_heaviest_idx(int x) const {
        int y = x;
        while (true) {
            std::vector<int> candidate_idx;
            for (int i = 0; i < D; ++i) {
                if (is_lighter(y, i)) candidate_idx.emplace_back(i);
            }
            if (candidate_idx.empty()) break;
            y = candidate_idx[xor128() % candidate_idx.size()];
            if (!is_unique(y)) x = y;
        }
        return x;
    }

    void reset_relation(int x, int y) {
        is_light[x] = is_light[y] = 0;
        is_heavy[x] = is_heavy[y] = 0;
        is_same[x] = is_same[y] = 0;
        int mask = ~((1 << x) | (1 << y));
        unique &= mask;
        for (int i = 0; i < D; ++i) {
            is_light[i] &= mask;
            is_heavy[i] &= mask;
            is_same[i] &= mask;
        }
    }

    void update_relation(int x, int y, int op) {
        reset_relation(x, y);
        if (op == 0) {
            is_same[x] = 1 << y, is_same[y] = 1 << x;
        } else {
            if (op == 1) std::swap(x, y);
            is_light[x] = 1 << y, is_heavy[y] = 1 << x;
        }
    }

    void set_relation(int x, int y, int op) {
        int128_t visited = 0;
        auto dfs_h = [&](auto self, int idx) -> void {
            is_light[idx] |= is_light[x];
            visited |= int128_t(1) << idx;
            for (int i = 0; i < D; ++i) {
                if (visited >> i & 1) continue;
                if (is_heavy[idx] >> i & 1) self(self, i);
            }
        };
        auto dfs_l = [&](auto self, int idx) -> void {
            is_heavy[idx] |= is_heavy[y];
            visited |= int128_t(1) << idx;
            for (int i = 0; i < D; ++i) {
                if (visited >> i & 1) continue;
                if (is_light[idx] >> i & 1) self(self, i);
            }
        };
        if (op == 0) {
            is_same[x] |= int128_t(1) << y, is_same[y] |= int128_t(1) << x;
            is_light[x] |= is_light[y], is_light[y] = is_light[x];
            is_heavy[x] |= is_heavy[y], is_heavy[y] = is_heavy[x];
            visited = 0, dfs_h(dfs_h, x);
            visited = 0, dfs_h(dfs_h, y);
            visited = 0, dfs_l(dfs_l, x);
            visited = 0, dfs_l(dfs_l, y);
        } else {
            if (op == 1) std::swap(x, y);
            is_light[x] |= is_light[y], is_heavy[y] |= is_heavy[x];
            is_light[x] |= int128_t(1) << y, is_heavy[y] |= int128_t(1) << x;
            visited = 0, dfs_h(dfs_h, x);
            visited = 0, dfs_l(dfs_l, y);
        }
    }

    void set_unique(int x) { unique |= 1 << x; }

  private:
    const int D;
    int unique;
    std::vector<int> is_light, is_heavy, is_same;
};

struct Operation {
    Operation(const std::vector<int> &_u, const std::vector<int> &_v) : u(_u), v(_v) {}

    const Operation &none() { return *this; }

    const Operation &move(int l) {
        assert(0 <= l && l < (int)u.size());
        std::swap(u[l], u.back());
        v.emplace_back(u.back());
        u.pop_back();
        return *this;
    }

    const Operation &swap(int l, int r) {
        assert(0 <= l && l < (int)u.size());
        assert(0 <= r && r < (int)v.size());
        std::swap(u[l], v[r]);
        return *this;
    }

    const Operation &remove(int l) {
        assert(0 <= l && l < (int)u.size());
        std::swap(u[l], u.back());
        u.pop_back();
        return *this;
    }

    const Operation &remove(int l, int r) {
        assert(0 <= l && l < (int)u.size());
        assert(0 <= r && r < (int)v.size());
        std::swap(u[l], u.back());
        std::swap(v[r], v.back());
        u.pop_back();
        v.pop_back();
        return *this;
    }

    std::vector<int> get_u() const { return u; }
    std::vector<int> get_v() const { return v; }

  private:
    std::vector<int> u, v;
};

struct Query {
    Query(int n, int d, int q) : N(n), D(d), Q(q), q() {}

    constexpr int get() const { return q; }
    constexpr bool is_completed() const { return q == Q; }

    int comp(const Operation &op) { return comp(op.get_u(), op.get_v()); }

    template <class T, class U>
    int comp(T &&l, U &&r) {
        if (l.empty() && r.empty()) return 0;
        if (l.empty()) return -1;
        if (r.empty()) return 1;
        ++q;
        std::cout << l.size() << ' ' << r.size();
        for (auto &x : l) std::cout << ' ' << x;
        for (auto &x : r) std::cout << ' ' << x;
        std::cout << std::endl;
        char op;
        std::cin >> op;
        return op == '=' ? 0 : op == '<' ? -1 : 1;
    }

    int comp(int l, int r) {
        ++q;
        std::cout << 1 << ' ' << 1 << ' ' << l << ' ' << r << std::endl;
        char op;
        std::cin >> op;
        return op == '=' ? 0 : op == '<' ? -1 : 1;
    }

  private:
    const int N, D, Q;
    int q;
};

struct QuerySimulation {
    QuerySimulation(int n, int d, int q) : N(n), D(d), Q(q), q(), W(n) {
        std::exponential_distribution<> dist(1.0 / 100000);
        for (int i = 0; i < n; ++i) {
            double x = std::max(1.0, std::round(dist(xor128)));
            while (x > 100000 * n / d) x = std::max(1.0, std::round(dist(xor128)));
            W[i] = x;
        }
    }

    constexpr bool is_completed() const { return q >= Q; }

    std::int64_t score(const std::vector<int> &group) const {
        std::vector<double> s(D);
        for (int i = 0; i < N; ++i) { s[group[i]] += W[i]; }
        double x = 0, y = 0;
        for (int i = 0; i < D; ++i) {
            x += s[i] * s[i];
            y += s[i];
        }
        x /= D, y /= D;
        return 1 + round(100 * sqrt(x - y * y));
    }

    int comp(const Operation &op) { return comp(op.get_u(), op.get_v()); }

    template <class T, class U>
    int comp(T &&l, U &&r) {
        if (l.empty() && r.empty()) return 0;
        if (l.empty()) return -1;
        if (r.empty()) return 1;
        ++q;
        int s = 0, t = 0;
        for (auto x : l) s += W[x];
        for (auto x : r) t += W[x];
        return s == t ? 0 : s < t ? -1 : 1;
    }

    int comp(int l, int r) {
        ++q;
        return W[l] == W[r] ? 0 : W[l] < W[r] ? -1 : 1;
    }

  private:
    const int N, D, Q;
    int q;
    std::vector<int> W;
};

template <class QUERY>
struct Solver {
    Solver(int n, int d, int q)
        : N(n), D(d), Q(q), query(n, d, q), i_relation(n), g_relation(d), group(d) {
        for (int i = 0; i < N; ++i) { group[i % d].emplace_back(i); }
    }

    std::int64_t score() const { return query.score(answer()); }

    std::vector<int> answer() const {
        std::vector<int> res(N);
        for (int i = 0; i < D; ++i) {
            for (auto x : group[i]) res[x] = i;
        }
        return res;
    }

    void debug() const {
        std::cout << "#c";
        for (auto x : answer()) std::cout << ' ' << x;
        std::cout << std::endl;
    }

    std::pair<int, int> select_target_index() {
        int x = xor128() % D, y = xor128() % D;
        while (x == y) y = xor128() % D;
        if (g_relation.is_heavier(x, y)) std::swap(x, y);
        if (g_relation.is_lighter(x, y)) {
            x = g_relation.get_lightest_idx(x);
            y = g_relation.get_heaviest_idx(y);
        }
        return {x, y};
    }

    void apply(int x, int y, const Operation &operation) {
        group[x] = operation.get_u();
        group[y] = operation.get_v();
        debug();
    }

    int compare(int x, int y) {
        if (g_relation.compare(x, y) != 2) return g_relation.compare(x, y);
        int op = query.comp(Operation(group[x], group[y]).none());
        g_relation.set_relation(x, y, op);
        return op;
    }

    std::vector<int> solve() {
        while (!query.is_completed()) {
            for (int i = 0; i < D; ++i) {
                if (group[i].size() == 1) g_relation.set_unique(i);
            }
            auto [x, y] = select_target_index();
            auto u = group[x], v = group[y];
            int op = compare(x, y);
            if (query.is_completed()) break;
            if (op == 0) continue;
            if (op == -1) std::swap(x, y), std::swap(u, v);
            if (u.size() == 1) continue;
            int l = xor128() % u.size();
            if (int op = query.comp(Operation(u, v).move(l)); op != -1) {
                g_relation.update_relation(x, y, op);
                apply(x, y, Operation(u, v).move(l));
                continue;
            }
            std::vector<int> candidate_idx;
            for (int i = 0; i < (int)v.size(); ++i) {
                if (i_relation.is_possible_to_be_lighter(v[i], u[l])) candidate_idx.emplace_back(i);
            }
            if (candidate_idx.empty()) {
                if (query.is_completed()) break;
                if (query.comp(Operation(u, v).remove(l)) == 1) {
                    g_relation.update_relation(x, y, 1);
                    apply(x, y, Operation(u, v).remove(l));
                }
                continue;
            }
            int r = candidate_idx[xor128() % candidate_idx.size()];
            if (query.is_completed()) break;
            op = query.comp(Operation(u, v).swap(l, r));
            if (op == 0) {
                g_relation.update_relation(x, y, 0);
                apply(x, y, Operation(u, v).swap(l, r));
                continue;
            } else if (op == 1) {
                if (!i_relation.is_lighter(v[r], u[l])) {
                    if (query.is_completed()) break;
                    int op = query.comp(v[r], u[l]);
                    i_relation.set_relation(v[r], u[l], op);
                    if (op != -1) continue;
                }
            } else {
                i_relation.set_relation(v[r], u[l], -1);
                if (query.is_completed()) break;
                int op = query.comp(Operation(u, v).remove(l, r));
                if (op != 1) continue;
            }
            g_relation.update_relation(x, y, op);
            apply(x, y, Operation(u, v).swap(l, r));
        }
        return answer();
    }

  private:
    const int N, D, Q;
    QUERY query;
    item_relation i_relation;
    group_relation g_relation;
    std::vector<std::vector<int>> group;
};

int main(void) {
    int N, D, Q;
    std::cin >> N >> D >> Q;
    Solver<Query> solver(N, D, Q);
    auto ans = solver.solve();
    for (auto x : ans) std::cout << x << ' ';
    std::cout << std::endl;

    return 0;
}
