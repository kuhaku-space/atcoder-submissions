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
/// @brief ローリングハッシュ
/// @see https://qiita.com/keymoon/items/11fac5627672a6d6a9f6
/// @see https://yosupo.hatenablog.com/entry/2023/08/06/181942
struct rolling_hash {
    rolling_hash() : _size(), base((std::uint64_t)std::random_device()() + 2), data(), p() {}
    rolling_hash(const std::string &_s, std::uint64_t base = (std::uint64_t)std::random_device()() + 2)
        : _size(_s.size()), base(base), data(1), p(1, 1) {
        std::uint64_t x = 0, t = 1, y;
        for (const auto c : _s) {
            x = _mul(x, base) + c;
            x = (__builtin_usubl_overflow(x, mod, &y) ? x : y);
            data.emplace_back(x);
            t = _mul(t, base);
            p.emplace_back(t);
        }
    }
    std::uint64_t get_base() const { return base; }
    /// get hash of s[0...r]
    std::uint64_t get(int r) const { return data[r]; }
    /// get hash of s[l...r]
    std::uint64_t get(int l, int r) const {
        assert(0 <= l && l <= r && r <= _size);
        std::uint64_t x = data[r] + mod - _mul(data[l], p[r - l]), y;
        return __builtin_usubl_overflow(x, mod, &y) ? x : y;
    }
    /// get hash of s.substr(pos, len)
    std::uint64_t substr(int pos, int len = std::numeric_limits<int>::max()) const {
        assert(0 <= pos && pos <= _size);
        len = std::min(len, _size - pos);
        std::uint64_t x = data[pos + len] + mod - _mul(data[pos], p[len]), y;
        return __builtin_usubl_overflow(x, mod, &y) ? x : y;
    }
    /// search string
    std::vector<int> search(const std::string &s) {
        std::vector<int> res;
        int n = s.size();
        if (n > _size) return res;
        std::uint64_t x = 0, y;
        for (char c : s) {
            x = _mul(x, base) + c;
            x = (__builtin_usubl_overflow(x, mod, &y) ? x : y);
        }
        for (int i = 0; i <= _size - n; ++i) {
            if (get(i, i + n) == x) res.emplace_back(i);
        }
        return res;
    }
    std::uint64_t hash(const std::string &s) const {
        std::uint64_t x = 0, y;
        for (const auto c : s) {
            x = _mul(x, base) + c;
            x = (__builtin_usubl_overflow(x, mod, &y) ? x : y);
        }
        return x;
    }
  private:
    static constexpr std::uint64_t mod = (1ul << 61) - 1;
    int _size;
    std::uint64_t base;
    std::vector<std::uint64_t> data, p;
    constexpr std::uint64_t _mul(std::uint64_t a, std::uint64_t b) const {
        __uint128_t t = (__uint128_t)a * b;
        a = (t >> 61) + (t & mod);
        return __builtin_usubl_overflow(a, mod, &b) ? a : b;
    }
    constexpr std::uint64_t _pow(std::uint64_t x, std::uint64_t k) const {
        std::uint64_t res = 1;
        for (; k; k >>= 1) {
            if (k & 1) res = _mul(res, x);
            x = _mul(x, x);
        }
        return res;
    }
};
int main(void) {
    int n, k;
    cin >> n >> k;
    vector<string> a(n);
    cin >> a;
    sort(all(a), [&](string l, string r) {
        if (l + r == r + l)
            return l < r;
        return l + r < r + l;
    });
    a.erase(unique(all(a)), a.end());
    string s;
    rep (i, 20) s += a[0];
    rolling_hash rh(s);
    vector<uint64_t> h(a.size());
    rep (i, a.size()) h[i] = rh.hash(a[i]);
    vector b(a[0].size(), vector<int>());
    rep (i, a[0].size()) {
        rep (j, a.size()) {
            if (rh.substr(i, a[j].size()) == h[j])
                b[i].emplace_back(j);
        }
    }
    vector<int> dp(k * a[0].size() + 10, -Inf);
    dp[0] = 0;
    rep (i, dp.size()) {
        if (dp[i] == -Inf)
            continue;
        for (int j : b[i % a[0].size()]) {
            if (i + a[j].size() < dp.size())
                chmax(dp[i + a[j].size()], dp[i] + 1);
        }
    }
    int len = Inf;
    rep (i, dp.size()) {
        if (dp[i] == k)
            chmin(len, i);
    }
    assert(len != Inf);
    string ans;
    while (ans.size() < len) ans += a[0];
    while (ans.size() > len) ans.pop_back();
    co(ans);
    return 0;
}
