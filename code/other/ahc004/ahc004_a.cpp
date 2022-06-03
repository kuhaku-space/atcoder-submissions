#ifndef LOCAL
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#endif

#include <sys/time.h>

#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;
using ll = int64_t;
#define FOR(i, m, n) for (int i = (m); i < (n); ++i)
#define rep(i, n) FOR(i, 0, n)
template <class T, class U>
bool chmax(T &a, const U &b) {
    return a < b ? a = b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U &b) {
    return b < a ? a = b, true : false;
}
constexpr int INF = 1000000003;
constexpr ll LINF = 1000000000000000003;

/*
 * Usage:
 * Trie<26, 'a'> trie;
 * Trie<96, ' '> trie;
 */
template <int char_size, int base>
struct Trie {
    struct Node {
        vector<int> next_node, accept, common;
        int c;
        Node(int _c) : c(_c), common(), next_node(char_size, -1) {}
    };
    vector<Node> nodes;
    int root;
    Trie() : root(0) {
        nodes.emplace_back(Node(root));
    }

    void insert(const string &word) {
        insert(word, nodes[0].common.size());
    }
    void insert(const string &word, int word_id) {
        int node_id = 0;
        for (int i = 0; i < word.size(); ++i) {
            int c = word[i] - base;
            int &next_id = nodes[node_id].next_node[c];
            if (next_id == -1) {
                next_id = nodes.size();
                nodes.emplace_back(Node(c));
            }
            nodes[node_id].common.emplace_back(word_id);
            node_id = next_id;
        }
        nodes[node_id].accept.emplace_back(word_id);
    }

    bool search(const string &word, bool prefix = false) {
        int node_id = 0;
        for (int i = 0; i < word.size(); i++) {
            int c = word[i] - base;
            int next_id = nodes[node_id].next_node[c];
            if (next_id == -1)
                return false;
            node_id = next_id;
        }
        return (prefix) ? true : nodes[node_id].accept.size() > 0;
    }

    int search_id(const string &word) {
        int node_id = 0;
        for (int i = 0; i < word.size(); i++) {
            int c = word[i] - base;
            int next_id = nodes[node_id].next_node[c];
            if (next_id == -1)
                return -1;
            node_id = next_id;
        }
        return node_id;
    }

    int next_id(int node_id, char ch) {
        int c = ch - base;
        return nodes[node_id].next_node[c];
    }
};
Trie<8, 'A'> trie;
vector<string> tasks;

constexpr int N = 20;
constexpr int K = 8;

constexpr int BEAM_SIZE = 1350;
constexpr int REWARD = 1024;

struct State {
    array<array<char, N>, N> board;
    array<bitset<N>, N> is_used;
    bitset<800> exists;
    int score, score_y;
    array<int, N> score_x;

    State() : score(), score_y() {
        score_x.fill(0);
    }

    bool operator<(const State &rhs) const {
        return eval() < rhs.eval();
    }
    bool operator>(const State &rhs) const {
        return rhs < *this;
    }

    int eval() const {
        return score;
    }

    int next_eval(int x, int y, char c) const {
        return score;
    }

    void update_score(int x, int y) {
        string s;
        score -= score_x[y];
        score_x[y] = 0;
        for (int i = x; i >= 0 && x - i + 1 <= 12; --i) {
            s.insert(s.begin(), board[i][y]);
            int id = trie.search_id(s);
            if (id != -1) {
                for (auto idx : trie.nodes[id].accept) {
                    if (!exists[idx]) {
                        score += REWARD;
                        exists[idx] = true;
                    }
                }
                if (trie.nodes[id].accept.size())
                    for (int j = i; j <= x; ++j)
                        is_used[j][y] = true;
                if (x == N - 1) {
                    for (int j = 0; j + x - i + 2 <= 12; ++j) {
                        id = trie.next_id(id, board[j][y]);
                        if (id == -1)
                            break;
                        for (auto idx : trie.nodes[id].accept) {
                            if (!exists[idx]) {
                                score += REWARD;
                                exists[idx] = true;
                            }
                        }
                        if (trie.nodes[id].accept.size())
                            for (int k = i; k <= N + j; ++k)
                                is_used[k % N][y] = true;
                    }
                } else {
                    for (auto idx : trie.nodes[id].common) {
                        if (!exists[idx]) {
                            score_x[y] += 1 << (x - i);
                        }
                    }
                }
            }
        }
        score += score_x[y];

        s = string();
        score -= score_y;
        score_y = 0;
        for (int i = y; i >= 0 && y - i + 1 <= 12; --i) {
            s.insert(s.begin(), board[x][i]);
            int id = trie.search_id(s);
            if (id != -1) {
                for (auto idx : trie.nodes[id].accept) {
                    if (!exists[idx]) {
                        score += REWARD;
                        exists[idx] = true;
                    }
                }
                if (trie.nodes[id].accept.size())
                    for (int j = i; j <= y; ++j)
                        is_used[x][j] = true;
                if (y == N - 1) {
                    for (int j = 0; j + y - i + 2 <= 12; ++j) {
                        id = trie.next_id(id, board[x][j]);
                        if (id == -1)
                            break;
                        for (auto idx : trie.nodes[id].accept) {
                            if (!exists[idx]) {
                                score += REWARD;
                                exists[idx] = true;
                            }
                        }
                        if (trie.nodes[id].accept.size())
                            for (int k = i; k <= N + j; ++k)
                                is_used[x][k % N] = true;
                    }
                } else {
                    for (auto idx : trie.nodes[id].common) {
                        if (!exists[idx]) {
                            score_y += 1 << (y - i);
                        }
                    }
                }
            }
        }
        score += score_y;
    }

    void _place(int x, int y, char c) {
        board[x][y] = c;
        update_score(x, y);
    }

    State place(int x, int y, char c) {
        State res(*this);
        res._place(x, y, c);
        return res;
    }

    auto answer() {
        rep(x, N) {
            rep(y, N) {
                cerr << board[x][y];
                if (!is_used[x][y])
                    board[x][y] = '.';
            }
            cerr << endl;
        }
        return board;
    }
};

struct beam_search {
    auto solve() {
        array<State, BEAM_SIZE> cur, nxt;
        cur[0] = State();
        int cur_size = 1, nxt_size = 0;
        for (int x = 0; x < N; ++x) {
            for (int y = 0; y < N; ++y) {
                priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> eval_que;
                nxt_size = 0;
                for (int i = 0; i < cur_size; ++i) {
                    for (int k = 0; k < K; ++k) {
                        auto &&s = cur[i].place(x, y, 'A' + k);
                        int eval = s.eval();
                        if (nxt_size < BEAM_SIZE) {
                            nxt[nxt_size] = s;
                            eval_que.push({eval, nxt_size++});
                        } else if (eval > eval_que.top().first) {
                            int idx = eval_que.top().second;
                            eval_que.pop();
                            nxt[idx] = s;
                            eval_que.push({eval, idx});
                        }
                    }
                }
                // cerr << eval_que.top().first << endl;
                swap(cur, nxt);
                cur_size = nxt_size;
            }
        }

        int idx = 0, max_eval = cur[0].eval();
        for (int i = 1; i < cur_size; ++i) {
            if (chmax(max_eval, cur[i].eval()))
                idx = i;
        }
        cerr << max_eval << endl;
        return cur[idx].answer();
    }
};

int main(void) {
    int n, m;
    cin >> n >> m;
    tasks.resize(m);
    for (auto &s : tasks) {
        cin >> s;
        trie.insert(s);
    }

    beam_search solver;
    auto ans = solver.solve();
    rep(x, N) {
        rep(y, N) cout << ans[x][y];
        cout << endl;
    }

    return 0;
}