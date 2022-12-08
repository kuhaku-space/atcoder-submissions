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
#line 2 "/home/kuhaku/home/github/algo/lib/string/trie.hpp"

/**
 * @brief Trie
 * @tparam char_size 文字種
 * @tparam base
 * @see https://algo-logic.info/trie-tree/
 *
 * Usage:
 * Trie<26, 'a'> trie;
 * Trie<96, ' '> trie;
 */
template <int char_size, int base>
struct Trie {
  private:
    struct _node {
        std::vector<int> next_node;
        _node() : next_node(char_size, -1) {}
    };

  public:
    using node_type = _node;

    Trie() : root(0), nodes() { this->nodes.emplace_back(); }

    std::vector<int> insert(const string &word) {
        std::vector<int> res;
        int node_id = 0;
        for (int i = 0; i < (int)word.size(); ++i) {
            int c = word[i] - base;
            int &next_id = this->nodes[node_id].next_node[c];
            if (next_id == -1) {
                next_id = this->nodes.size();
                this->nodes.emplace_back();
            }
            node_id = next_id;
            res.emplace_back(node_id);
        }
        return res;
    }

    int search_id(const string &word) {
        int node_id = 0;
        for (int i = 0; i < (int)word.size(); ++i) {
            int c = word[i] - base;
            int &next_id = this->nodes[node_id].next_node[c];
            if (next_id == -1) return -1;
            node_id = next_id;
        }
        return node_id;
    }

    node_type get_node(int node_id) {
        assert(0 <= node_id && node_id < (int)this->nodes.size());
        return this->nodes[node_id];
    }

  private:
    int root;
    std::vector<node_type> nodes;
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
    string s;
    cin >> s;
    Trie<26, 'a'> trie;
    int q;
    cin >> q;
    vector<string> p(q);
    vector<int> w(q);
    cin >> p >> w;
    unordered_map<int, int> mp;
    rep(i, q) {
        auto v = trie.insert(p[i]);
        chmax(mp[v.back()], w[i]);
    }

    int n = s.size();
    vector<ll> dp(n + 1);
    vector<int> nodes(n);
    rep(i, n) {
        rep(j, 200) {
            if (i - j < 0)
                break;
            if (nodes[i - j] == -1)
                continue;
            auto node = trie.get_node(nodes[i - j]);
            int x = node.next_node[s[i] - 'a'];
            chmax(dp[i + 1], dp[i - j] + mp[x]);
            nodes[i - j] = x;
        }
    }
    co(dp[n]);

    return 0;
}
