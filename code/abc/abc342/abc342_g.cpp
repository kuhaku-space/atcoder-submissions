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
#line 2 "/home/kuhaku/home/github/algo/lib/data_structure/erasable_priority_queue.hpp"

/**
 * @brief 削除可能優先度付きキュー
 *
 * @tparam T
 */
template <class T, class Comp = std::less<>>
struct erasable_priority_queue {
    bool empty() const { return a.empty(); }
    int size() const { return a.size() - b.size(); }
    T top() const { return a.top(); }

    void insert(const T &x) { a.push(x); }
    void insert(T &&x) { a.push(std::move(x)); }
    void push(const T &x) { a.push(x); }
    void push(T &&x) { a.push(std::move(x)); }
    template <typename... Args>
    void emplace(Args &&...args) {
        a.emplace(std::forward<Args>(args)...);
    }

    void pop() { erase(a.top()); }

    void erase(T x) {
        b.emplace(x);
        while (!b.empty() && a.top() == b.top()) {
            a.pop(), b.pop();
        }
    }

  private:
    std::priority_queue<T, std::vector<T>, Comp> a, b;
};
#line 2 "/home/kuhaku/home/github/algo/lib/internal/internal_bit.hpp"

namespace internal {

// @return same with std::bit::bit_ceil
unsigned int bit_ceil(unsigned int n) {
    unsigned int x = 1;
    while (x < (unsigned int)(n)) x *= 2;
    return x;
}

// @param n `1 <= n`
// @return same with std::bit::countl_zero
int countl_zero(unsigned int n) { return __builtin_clz(n); }

// @param n `1 <= n`
// @return same with std::bit::countr_zero
int countr_zero(unsigned int n) { return __builtin_ctz(n); }

// @param n `1 <= n`
// @return same with std::bit::countr_zero
constexpr int countr_zero_constexpr(unsigned int n) {
    int x = 0;
    while (!(n & (1 << x))) x++;
    return x;
}

}  // namespace internal
#line 5 "/home/kuhaku/home/github/algo/lib/segment_tree/monoid.hpp"

template <class T>
struct Add {
    using value_type = T;
    static constexpr T id = T(0);
    static constexpr T op(const T &lhs, const T &rhs) { return lhs + rhs; }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs + rhs;
    }
};

template <class T>
struct And {
    using value_type = T;
    static constexpr T id = std::numeric_limits<T>::max();
    static constexpr T op(const T &lhs, const T &rhs) { return lhs & rhs; }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs & rhs;
    }
};

template <class T>
struct Or {
    using value_type = T;
    static constexpr T id = T(0);
    static constexpr T op(const T &lhs, const T &rhs) { return lhs | rhs; }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs | rhs;
    }
};

template <class T>
struct Xor {
    using value_type = T;
    static constexpr T id = T(0);
    static constexpr T op(const T &lhs, const T &rhs) { return lhs ^ rhs; }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs ^ rhs;
    }
};

template <class T>
struct Min {
    using value_type = T;
    static constexpr T id = std::numeric_limits<T>::max();
    static constexpr T op(const T &lhs, const T &rhs) { return std::min(lhs, rhs); }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return std::min((U)lhs, rhs);
    }
};

template <class T>
struct Max {
    using value_type = T;
    static constexpr T id = std::numeric_limits<T>::min();
    static constexpr T op(const T &lhs, const T &rhs) { return std::max(lhs, rhs); }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return std::max((U)lhs, rhs);
    }
};

template <class T>
struct Update {
    using value_type = T;
    static constexpr T id = std::numeric_limits<T>::max();
    static constexpr T op(const T &lhs, const T &rhs) { return lhs == Update::id ? rhs : lhs; }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs == Update::id ? rhs : lhs;
    }
};

template <class T>
struct Affine {
    using value_type = std::pair<T, T>;
    static constexpr std::pair<T, T> id = std::pair<T, T>(1, 0);
    static constexpr std::pair<T, T> op(std::pair<T, T> lhs, std::pair<T, T> rhs) {
        return {lhs.first * rhs.first, lhs.first * rhs.second + lhs.second};
    }
};

template <class M>
struct Rev {
    using T = typename M::value_type;
    using value_type = T;
    static constexpr T id = M::id;
    static constexpr T op(T lhs, T rhs) { return M::op(rhs, lhs); }
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
#line 7 "a.cpp"

template <class T>
struct dual_segment_tree {
    dual_segment_tree() : dual_segment_tree(0) {}
    explicit dual_segment_tree(int n) : _n(n) {
        _size = internal::bit_ceil(_n);
        _log = internal::countr_zero(_size);
        data.resize(_size << 1);
    }

    T get(int k, T x) {
        assert(0 <= k && k < _n);
        T res = x;
        k += _size;
        for (int i = _log; i >= 0; --i) {
            if (!data[k >> i].empty())
                chmax(res, data[k >> i].top());
        }
        return res;
    }

    void apply(int a, std::pair<int, T> val) {
        apply(a, a + 1, val);
    }
    void apply(int a, int b, std::pair<int, T> val) {
        assert(0 <= a && a <= _n);
        assert(0 <= b && b <= _n);
        a += _size, b += _size;
        for (; a < b; a >>= 1, b >>= 1) {
            if (a & 1)
                all_apply(a++, val);
            if (b & 1)
                all_apply(--b, val);
        }
    }

  private:
    int _n, _size, _log;
    std::vector<erasable_priority_queue<T>> data;

    void all_apply(int k, std::pair<int, T> val) {
        if (val.first == 1)
            data[k].emplace(val.second);
        else
            data[k].erase(val.second);
    }
};

int main(void) {
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    dual_segment_tree<int> dst(n);
    int q;
    cin >> q;
    vector<tuple<int, int, int>> query(q);
    rep (i, q) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            --l;
            dst.apply(l, r, {1, x});
            query[i] = {l, r, x};
        } else if (t == 2) {
            int idx;
            cin >> idx;
            auto [l, r, x] = query[idx - 1];
            dst.apply(l, r, {2, x});
        } else {
            int idx;
            cin >> idx;
            co(dst.get(idx - 1, a[idx - 1]));
        }
    }

    return 0;
}
