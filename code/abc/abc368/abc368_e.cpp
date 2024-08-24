// competitive-verifier: PROBLEM
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>
#include <limits>
#include <numeric>
template <class T>
struct Add {
    using value_type = T;
    static constexpr T id() { return T(); }
    static constexpr T op(const T &lhs, const T &rhs) { return lhs + rhs; }
    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs + rhs;
    }
};
template <class T>
struct Mul {
    using value_type = T;
    static constexpr T id() { return T(1); }
    static constexpr T op(const T &lhs, const T &rhs) { return lhs * rhs; }
    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs * rhs;
    }
};
template <class T>
struct And {
    using value_type = T;
    static constexpr T id() { return std::numeric_limits<T>::max(); }
    static constexpr T op(const T &lhs, const T &rhs) { return lhs & rhs; }
    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs & rhs;
    }
};
template <class T>
struct Or {
    using value_type = T;
    static constexpr T id() { return T(); }
    static constexpr T op(const T &lhs, const T &rhs) { return lhs | rhs; }
    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs | rhs;
    }
};
template <class T>
struct Xor {
    using value_type = T;
    static constexpr T id() { return T(); }
    static constexpr T op(const T &lhs, const T &rhs) { return lhs ^ rhs; }
    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs ^ rhs;
    }
};
template <class T>
struct Min {
    using value_type = T;
    static constexpr T id() { return std::numeric_limits<T>::max(); }
    static constexpr T op(const T &lhs, const T &rhs) { return std::min(lhs, rhs); }
    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return std::min((U)lhs, rhs);
    }
};
template <class T>
struct Max {
    using value_type = T;
    static constexpr T id() { return std::numeric_limits<T>::lowest(); }
    static constexpr T op(const T &lhs, const T &rhs) { return std::max(lhs, rhs); }
    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return std::max((U)lhs, rhs);
    }
};
template <class T>
struct Gcd {
    using value_type = T;
    static constexpr T id() { return std::numeric_limits<T>::max(); }
    static constexpr T op(const T &lhs, const T &rhs) {
        return lhs == Gcd::id() ? rhs : (rhs == Gcd::id() ? lhs : std::gcd(lhs, rhs));
    }
};
template <class T>
struct Lcm {
    using value_type = T;
    static constexpr T id() { return std::numeric_limits<T>::max(); }
    static constexpr T op(const T &lhs, const T &rhs) {
        return lhs == Lcm::id() ? rhs : (rhs == Lcm::id() ? lhs : std::lcm(lhs, rhs));
    }
};
template <class T>
struct Update {
    using value_type = T;
    static constexpr T id() { return std::numeric_limits<T>::max(); }
    static constexpr T op(const T &lhs, const T &rhs) { return lhs == Update::id() ? rhs : lhs; }
    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs == Update::id() ? rhs : lhs;
    }
};
template <class T>
struct Affine {
    using P = std::pair<T, T>;
    using value_type = P;
    static constexpr P id() { return P(1, 0); }
    static constexpr P op(P lhs, P rhs) {
        return {lhs.first * rhs.first, lhs.first * rhs.second + lhs.second};
    }
};
template <class M>
struct Rev {
    using T = typename M::value_type;
    using value_type = T;
    static constexpr T id() { return M::id(); }
    static constexpr T op(T lhs, T rhs) { return M::op(rhs, lhs); }
};
/**
 * @brief 動的セグメント木
 *
 * @tparam M モノイド
 */
template <class M>
struct dynamic_segment_tree {
  private:
    using T = typename M::value_type;
    struct _node {
        std::int64_t index;
        int left, right;
        T value, product;
        constexpr _node() = default;
        constexpr _node(std::int64_t _index, T _value)
            : index(_index), left(-1), right(-1), value(_value), product(_value) {}
    };
  public:
    dynamic_segment_tree(std::int64_t n) : data(), _size(n) {}
    T operator[](std::int64_t k) const {
        if (data.empty()) return M::id();
        int idx = 0;
        std::int64_t l = 0, r = _size;
        while (idx != -1) {
            if (k == data[idx].index) return data[idx].value;
            std::int64_t m = (l + r) >> 1;
            if (k < m) r = m, idx = data[idx].left;
            else l = m, idx = data[idx].right;
        }
        return M::id();
    }
    T at(std::int64_t k) const { return operator[](k); }
    T get(std::int64_t k) const { return operator[](k); }
    void set(std::int64_t k, T x) {
        assert(0 <= k && k < _size);
        if (data.empty()) {
            data.emplace_back(k, x);
            return;
        }
        int idx = 0;
        std::vector<int> nodes;
        std::int64_t l = 0, r = _size;
        while (true) {
            nodes.emplace_back(idx);
            if (k == data[idx].index) {
                data[idx].value = x;
                break;
            }
            std::int64_t m = (l + r) >> 1;
            if (k < m) {
                if (data[idx].index < k)
                    std::swap(k, data[idx].index), std::swap(x, data[idx].value);
                if (data[idx].left == -1) {
                    data[idx].left = data.size();
                    data.emplace_back(k, x);
                    break;
                }
                r = m, idx = data[idx].left;
            } else {
                if (k < data[idx].index)
                    std::swap(k, data[idx].index), std::swap(x, data[idx].value);
                if (data[idx].right == -1) {
                    data[idx].right = data.size();
                    data.emplace_back(k, x);
                    break;
                }
                l = m, idx = data[idx].right;
            }
        }
        std::reverse(nodes.begin(), nodes.end());
        for (auto idx : nodes) {
            data[idx].product =
                M::op(M::op(data[idx].left != -1 ? data[data[idx].left].product : M::id(),
                            data[idx].value),
                      data[idx].right != -1 ? data[data[idx].right].product : M::id());
        }
    }
    void reset(std::int64_t k) { set(k, M::id()); }
    T all_prod() const { return !data.empty() ? data.front().product : M::id(); }
    T prod(std::int64_t a, std::int64_t b) const {
        assert(0 <= a && a <= _size);
        assert(0 <= b && b <= _size);
        if (data.empty()) return M::id();
        return prod(a, b, 0, 0, _size);
    }
  private:
    std::vector<_node> data;
    std::int64_t _size;
    T prod(std::int64_t a, std::int64_t b, int idx, std::int64_t l, std::int64_t r) const {
        if (idx == -1 || r <= a || b <= l) return M::id();
        if (a <= l && r <= b) return data[idx].product;
        return M::op(M::op(prod(a, b, data[idx].left, l, (l + r) >> 1),
                           a <= data[idx].index && data[idx].index < b ? data[idx].value : M::id()),
                     prod(a, b, data[idx].right, (l + r) >> 1, r));
    }
};
#ifdef ATCODER
#pragma GCC target("sse4.2,avx512f,avx512dq,avx512ifma,avx512cd,avx512bw,avx512vl,bmi2")
#endif
#pragma GCC optimize("Ofast,fast-math,unroll-all-loops")
#include <bits/stdc++.h>
#ifndef ATCODER
#pragma GCC target("sse4.2,avx2,bmi2")
#endif
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
constexpr double PI = 3.14159265358979323846;
#define FOR(i, m, n) for (int i = (m); i < int(n); ++i)
#define FORR(i, m, n) for (int i = (m)-1; i >= int(n); --i)
#define FORL(i, m, n) for (int64_t i = (m); i < int64_t(n); ++i)
#define rep(i, n) FOR (i, 0, n)
#define repn(i, n) FOR (i, 1, n + 1)
#define repr(i, n) FORR (i, n, 0)
#define repnr(i, n) FORR (i, n + 1, 1)
#define all(s) (s).begin(), (s).end()
struct Sonic {
    Sonic() {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
        std::cout << std::fixed << std::setprecision(20);
    }
    constexpr void operator()() const {}
} sonic;
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
    for (auto it = v.begin(); it != v.end(); ++it) os << (it == v.begin() ? "" : " ") << *it;
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
void Yes(bool is_correct = true) { std::cout << (is_correct ? "Yes\n" : "No\n"); }
void No(bool is_not_correct = true) { Yes(!is_not_correct); }
void YES(bool is_correct = true) { std::cout << (is_correct ? "YES\n" : "NO\n"); }
void NO(bool is_not_correct = true) { YES(!is_not_correct); }
void Takahashi(bool is_correct = true) { std::cout << (is_correct ? "Takahashi" : "Aoki") << '\n'; }
void Aoki(bool is_not_correct = true) { Takahashi(!is_not_correct); }
int main(void) {
    int n, m, x;
    cin >> n >> m >> x;
    vector<tuple<int, int, ll, ll>> a(m);
    for (auto &[u, v, s, t] : a) cin >> u >> v >> s >> t, --u, --v;
    vector<dynamic_segment_tree<Max<ll>>> dst(n, dynamic_segment_tree<Max<ll>>(1e9 + 1));
    vector<ll> ans(m);
    ans[0] = x;
    {
        auto [u, v, s, t] = a[0];
        dst[v].set(t, t + x);
    }
    vector<int> ord(m);
    iota(all(ord), 0);
    sort(all(ord), [&](int p, int q) {
        return get<2>(a[p]) < get<2>(a[q]);
    });
    for (int id : ord) {
        auto [u, v, s, t] = a[id];
        ll e = dst[u].prod(0, s + 1);
        if (e == Max<ll>::id())
            e = 0;
        e -= s;
        chmax(e, 0);
        ans[id] = e;
        dst[v].set(t, max(dst[v].get(t), t + e));
    }
    ans.erase(ans.begin());
    co(ans);
    return 0;
}
