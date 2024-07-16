// competitive-verifier: PROBLEM
#include <cassert>
#include <queue>
#include <string>
#include <vector>
/**
 * @brief Aho Corasick 法
 * @see https://naoya-2.hatenadiary.org/entry/20090405/aho_corasick
 * @see https://ei1333.github.io/library/string/aho-corasick.hpp.html
 *
 * @tparam char_size
 * @tparam base
 */
template <int char_size, int base>
struct aho_corasick {
  private:
    struct _node {
        std::vector<int> next_node;
        _node() : next_node(char_size, -1) {}
        int next(int x) const { return next_node[x]; }
    };
  public:
    using node_type = _node;
    aho_corasick() : nodes(), failure() { nodes.emplace_back(); }
    int size() const { return nodes.size(); }
    int get_failure(int k) const { return failure[k]; }
    std::vector<int> build() {
        failure = std::vector<int>(size(), 0);
        std::vector<int> ord;
        ord.emplace_back(0);
        for (int k = 0; k < size(); ++k) {
            int x = ord[k];
            for (int i = 0; i < char_size; ++i) {
                int next_x = nodes[x].next(i);
                if (next_x != -1) {
                    ord.emplace_back(next_x);
                    if (k == 0) continue;
                    int y = x;
                    do {
                        y = failure[y];
                        int next_y = nodes[y].next(i);
                        if (next_y != -1) {
                            failure[next_x] = next_y;
                            break;
                        }
                    } while (y != 0);
                }
            }
        }
        return ord;
    }
    std::vector<int> insert(const std::string &word) {
        std::vector<int> res;
        int node_id = 0;
        for (int i = 0; i < (int)word.size(); ++i) {
            int &next_id = nodes[node_id].next_node[word[i] - base];
            if (next_id == -1) {
                next_id = nodes.size();
                nodes.emplace_back();
            }
            node_id = next_id;
            res.emplace_back(node_id);
        }
        return res;
    }
    int search(const char c, int now = 0) {
        int next_id = nodes[now].next(c - base);
        while (next_id == -1 && now != 0) {
            now = failure[now];
            next_id = nodes[now].next(c - base);
        }
        return next_id != -1 ? next_id : 0;
    }
    std::vector<int> search(const std::string &str, int now = 0) {
        std::vector<int> res;
        res.emplace_back(now);
        for (auto c : str) {
            now = search(c, now);
            res.emplace_back(now);
        }
        return res;
    }
    node_type get_node(int node_id) const {
        assert(0 <= node_id && node_id < (int)nodes.size());
        return nodes[node_id];
    }
  private:
    std::vector<node_type> nodes;
    std::vector<int> failure;
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
    string s;
    cin >> s;
    int q;
    cin >> q;
    vector<int> a(q);
    aho_corasick<26, 'a'> aho;
    rep (i, q) {
        string t;
        cin >> t;
        auto v = aho.insert(t);
        a[i] = v.back();
    }
    auto ord = aho.build();
    auto v = aho.search(s);
    vector<ll> dp(aho.size());
    for (int x : v) ++dp[x];
    reverse(all(ord));
    for (int i : ord) {
        dp[aho.get_failure(i)] += dp[i];
    }
    rep (i, q) co(dp[a[i]]);
    return 0;
}
