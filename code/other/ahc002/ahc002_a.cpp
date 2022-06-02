/*
 * Problem : https://atcoder.jp/contests/ahc002/tasks/ahc002_a
 */

#ifndef LOCAL
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
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

constexpr int BEAM_SIZE = 8000;
constexpr int N = 50;
constexpr int M = 5;
constexpr int M2 = M * M;
int tile[50][50];
int board[50][50];
int dirx[4] = {1, -1, 0, 0}, diry[4] = {0, 0, 1, -1};
char op[4] = {'D', 'U', 'R', 'L'};

inline bool in_board(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N;
}
inline bool in_mini_board(int x, int y, int ox, int oy) {
    return x >= N * ox / M && x < N * (ox + 1) / M && y >= N * oy / M && y < N * (oy + 1) / M;
}
vector<pair<int, int>> order;
vector<pair<int, int>> vec;

void make_order(int x, int y) {
    if (x < 0 || x >= M || y < 0 || y >= M)
        return;
    for (auto p : vec) {
        if (p == pair<int, int>(x, y))
            return;
    }
    vec.emplace_back(x, y);
    if (vec.size() > order.size()) {
        order = vec;
    }
    rep(dir, 4) {
        int tx = x + dirx[dir];
        int ty = y + diry[dir];
        make_order(tx, ty);
        if (vec.size() == M2 || order.size() == M2)
            return;
    }
    vec.pop_back();
}

struct beam_search {
    struct State {
        int px, py;
        int score;
        bitset<1536> is_used;
        string ops;

        State() : score() {}
        State(int _px, int _py) : px(_px), py(_py), score(), is_used() {
            score += board[px][py];
            is_used.set(tile[px][py]);
        }

        bool operator<(const State &rhs) const {
            return eval() < rhs.eval();
        }
        bool operator>(const State &rhs) const {
            return rhs < *this;
        }

        inline int eval() const {
            return score;
        }

        void update_score(int row) {}

        void _place(int dir) {
            px += dirx[dir];
            py += diry[dir];
            score += board[px][py];
            is_used.set(tile[px][py]);
            ops.push_back(op[dir]);
        }

        State place(int dir) {
            State res(*this);
            res._place(dir);
            return res;
        }

        bool is_place(int dir) {
            int x = px + dirx[dir];
            int y = py + diry[dir];
            return in_board(x, y) && !is_used[tile[x][y]];
        }

        bool is_mini_board(int ox, int oy) {
            return in_mini_board(px, py, ox, oy);
        }

        string answer() const {
            return ops;
        }
    };

    string solve(int sx, int sy) {
        string res;
        int max_score = 0;
        vector<map<pair<int, int>, State>> cur_order(order.size());
        cur_order[0][{sx, sy}] = State(sx, sy);
        array<State, BEAM_SIZE> cur, nxt;
        for (int idx = 0; idx < order.size(); ++idx) {
            int cur_size = 0, nxt_size = 0;
            for (auto &p : cur_order[idx]) {
                cur[cur_size++] = p.second;
            }
            while (cur_size && (double)clock() / CLOCKS_PER_SEC < 1.95 * (idx + 1) / order.size()) {
                priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> eval_que;
                nxt_size = 0;
                for (int i = 0; i < cur_size; ++i) {
                    auto &now = cur[i];
                    if (chmax(max_score, now.eval())) {
                        res = now.answer();
                    }
                    for (int dir = 0; dir < 4; ++dir) {
                        if (!now.is_place(dir))
                            continue;
                        auto &&s = now.place(dir);
                        bool flg = true;
                        for (int i = idx + 1; i < order.size(); ++i) {
                            if (s.is_mini_board(order[i].first, order[i].second)) {
                                chmax(cur_order[i][{s.px, s.py}], s);
                                flg = false;
                                break;
                            }
                        }
                        if (flg) {
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
                }
                swap(cur, nxt);
                cur_size = nxt_size;
            }
        }

        cerr << max_score << endl;
        return res;
    }
};

int main(void) {
    int sx, sy;
    cin >> sx >> sy;
    rep(i, N) {
        rep(j, N) cin >> tile[i][j];
    }
    rep(i, N) {
        rep(j, N) cin >> board[i][j];
    }

    make_order(sx * M / N, sy * M / N);

    beam_search solver;
    cout << solver.solve(sx, sy) << endl;

    return 0;
}
