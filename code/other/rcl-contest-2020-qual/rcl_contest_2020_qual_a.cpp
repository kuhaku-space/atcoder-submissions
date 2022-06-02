/*
 * Problem : https://atcoder.jp/contests/rcl-contest-2020-qual/tasks/rcl_contest_2020_qual_a
 */

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
constexpr double EPS = 1e-11;

constexpr int N = 1000;
constexpr int H = 125;
constexpr int W = 8;
constexpr int K = 6;
array<int, N> C;
array<int, N> V;

constexpr int BEAM_SIZE = 2210;

struct State {
    array<array<unsigned short, H>, W> board = {};
    array<unsigned char, W> h = {};
    array<unsigned char, H> score_row = {};
    int score;

    State() : score() {}

    bool operator<(const State &rhs) const {
        return eval() < rhs.eval();
    }
    bool operator>(const State &rhs) const {
        return rhs < *this;
    }

    void update_score(int id, int row) {
        if (row >= H)
            return;
        int sum = 0;
        rep(i, W) {
            if (h[i] <= row)
                break;
            int x = board[i][row];
            if (C[x] != C[id])
                continue;
            sum += V[x];
        }

        if (sum > score_row[row]) {
            score += sum - score_row[row];
            score_row[row] = sum;
        }
    }

    int eval() const {
        int res = score;
        res -= h[0] - h[W - 1];
        if (h[0] - h[W - 1] > 6)
            res -= (h[0] - h[W - 1] - 6) << 1;
        return res;
    }

    bool is_place(int col) {
        return h[col] < H && (col == 0 || h[col] != h[col - 1]);
    }

    void update(int id, int col) {
        board[col][h[col]] = id;
        update_score(id, h[col]++);
    }

    State place(int id, int col) {
        State res(*this);
        res.update(id, col);
        return res;
    }

    array<int, N> answer() const {
        array<int, N> res = {};
        rep(col, W) {
            rep(row, H) res[board[col][row]] = col;
        }
        return res;
    }
};

struct beam_search {
    auto solve() {
        array<State, BEAM_SIZE> cur, nxt;
        cur[0] = State();
        int cur_size = 1, nxt_size = 0;
        for (int t = 0; t < N; ++t) {
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> eval_que;
            nxt_size = 0;
            for (int i = 0; i < cur_size; ++i) {
                auto &now = cur[i];
                for (int col = 0; col < W; ++col) {
                    if (!now.is_place(col))
                        continue;
                    auto &&s = now.place(t, col);
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
            swap(cur, nxt);
            cur_size = nxt_size;
        }

        int idx = 0, max_eval = cur[0].eval();
        for (int i = 1; i < cur_size; ++i) {
            if (chmax(max_eval, cur[i].eval()))
                idx = i;
        }
        cerr << cur[idx].eval() << endl;
        return cur[idx].answer();
    }
};

int main(void) {
    int tmp;
    cin >> tmp >> tmp >> tmp >> tmp;
    rep(i, N) cin >> C[i] >> V[i];
    beam_search solver;

    array<int, N> ans = solver.solve();

    for (auto i : ans) cout << i << endl;

    return 0;
}
