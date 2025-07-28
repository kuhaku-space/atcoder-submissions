// competitive-verifier: PROBLEM
#pragma GCC optimize("Ofast,fast-math,unroll-all-loops")
#include <bits/stdc++.h>
#if !defined(ATCODER) && !defined(EVAL)
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
#define FORR(i, m, n) for (int i = (m) - 1; i >= int(n); --i)
#define FORL(i, m, n) for (std::int64_t i = (m); i < std::int64_t(n); ++i)
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
struct increment_impl {
    template <class T>
    const increment_impl &operator>>(std::vector<T> &v) const {
        for (auto &x : v) ++x;
        return *this;
    }
} Inc;
struct decrement_impl {
    template <class T>
    const decrement_impl &operator>>(std::vector<T> &v) const {
        for (auto &x : v) --x;
        return *this;
    }
} Dec;
struct sort_impl {
    template <class T>
    const sort_impl &operator>>(std::vector<T> &v) const {
        std::sort(v.begin(), v.end());
        return *this;
    }
} Sort;
struct unique_impl {
    template <class T>
    const unique_impl &operator>>(std::vector<T> &v) const {
        std::sort(v.begin(), v.end());
        v.erase(std::unique(v.begin(), v.end()), v.end());
        return *this;
    }
} Uniq;
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
#include <bit>
/// @brief スパーステーブル
template <class M>
struct sparse_table {
  private:
    using T = typename M::value_type;
  public:
    sparse_table() = default;
    sparse_table(const std::vector<T> &v) : _size(v.size()), data() {
        int b = std::max(1, std::countr_zero(std::bit_ceil<unsigned>(_size)));
        data.emplace_back(v);
        for (int i = 1; i < b; ++i) data.emplace_back(_size + 1 - (1 << i));
        for (int i = 1; i < b; ++i) {
            for (int j = 0; j + (1 << i) <= _size; ++j) {
                data[i][j] = M::op(data[i - 1][j], data[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
    T prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _size);
        if (l == r) return M::id();
        if (l + 1 == r) return data[0][l];
        int b = 31 - std::countl_zero<unsigned>(r - l - 1);
        return M::op(data[b][l], data[b][r - (1 << b)]);
    }
  private:
    int _size;
    std::vector<std::vector<T>> data;
};
namespace internal {
template <class T, int N>
struct fixed_stack {
    constexpr fixed_stack() : _size(), _data() {}
    constexpr T top() const { return _data[_size - 1]; }
    constexpr bool empty() const { return _size == 0; }
    constexpr int size() const { return _size; }
    constexpr void emplace(const T &e) { _data[_size++] = e; }
    constexpr void emplace(T &&e) { _data[_size++] = e; }
    constexpr void pop() { --_size; }
    constexpr void clear() { _size = 0; }
  private:
    int _size;
    std::array<T, N> _data;
};
}  // namespace internal
/// @brief 線形 Sparse Table
template <class M>
struct linear_sparse_table {
  private:
    using T = M::value_type;
    static constexpr int W = 64;
  public:
    linear_sparse_table() = default;
    linear_sparse_table(const std::vector<T> &v) : _size(v.size()), data(v) {
        int n = v.size();
        int b = n / W;
        internal::fixed_stack<int, W + 1> st;
        std::vector<T> u(b);
        word_data.resize(b + (n > b * W));
        for (int i = 0; i < b; ++i) {
            T m = M::id();
            std::uint64_t bit = 0;
            std::vector<std::uint64_t> bits(W);
            for (int j = 0; j < W; ++j) {
                m = M::op(m, v[i * W + j]);
                while (!st.empty() && M::op(v[i * W + st.top()], v[i * W + j]) == v[i * W + j]) {
                    bit ^= std::uint64_t(1) << st.top();
                    st.pop();
                }
                bits[j] = bit;
                bit |= std::uint64_t(1) << j;
                st.emplace(j);
            }
            u[i] = m;
            word_data[i] = bits;
            st.clear();
        }
        if (n > b * W) {
            std::uint64_t bit = 0;
            std::vector<std::uint64_t> bits(n - b * W);
            for (int j = 0; j < n - b * W; ++j) {
                while (!st.empty() && M::op(v[b * W + st.top()], v[b * W + j]) == v[b * W + j]) {
                    bit ^= std::uint64_t(1) << st.top();
                    st.pop();
                }
                bits[j] = bit;
                bit |= std::uint64_t(1) << j;
                st.emplace(j);
            }
            word_data[b] = bits;
        }
        block_table = sparse_table<M>(u);
    }
    const T &operator[](int k) const { return data[k]; }
    T prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _size);
        if (l == r) return M::id();
        int lb = (l + W - 1) / W, rb = r / W;
        if (lb > rb) return word_prod(l, r);
        T res = (lb == rb ? M::id() : block_table.prod(lb, rb));
        if (l < lb * W) res = M::op(res, word_prod(l, lb * W));
        if (rb * W < r) res = M::op(res, word_prod(rb * W, r));
        return res;
    }
  private:
    int _size;
    std::vector<T> data;
    sparse_table<M> block_table;
    std::vector<std::vector<std::uint64_t>> word_data;
    T word_prod(int l, int r) const {
        if (l == r) return M::id();
        int b = l / W;
        int lw = l - b * W, rw = r - b * W;
        if ((word_data[b][rw - 1] >> lw) == 0ul) return data[r - 1];
        return data[l + std::countr_zero(word_data[b][rw - 1] >> lw)];
    }
};
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
void solve() {
    int n;
    cin >> n;
    vector<int> a(1 << n);
    cin >> a;
    linear_sparse_table<Min<int>> lst(a);
    vector<int> ans;
    auto dfs = [&](auto self, int l, int r) {
        if (l + 1 == r) {
            ans.emplace_back(a[l]);
            return;
        }
        int m = (l + r) / 2;
        if (lst.prod(l, m) < lst.prod(m, r)) {
            self(self, l, m);
            self(self, m, r);
        } else {
            self(self, m, r);
            self(self, l, m);
        }
    };
    dfs(dfs, 0, 1 << n);
    co(ans);
}
int main(void) {
    int t = 1;
    std::cin >> t;
    while (t--) solve();
    return 0;
}
