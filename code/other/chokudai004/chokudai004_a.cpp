/*
 * Problem : https://atcoder.jp/contests/chokudai004/tasks/chokudai004_a
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
constexpr ll LINF = 1000000000000000003;

constexpr int N = 30;
int B[3];
array<array<int, N>, N> L, R;

constexpr int BEAM_SIZE = 7250;

struct State {
    array<array<unsigned char, N>, N> board;
    int score;

    State() : score() {}

    void update_score(int next_score) {
        score = next_score;
    };

    int eval() const {
        return score;
    }

    int next_eval(int row, int col, int m) const {
        int res = score;
        int sum = m;
        rep(i, row) {
            sum += board[row - 1 - i][col];
            if (sum > B[2])
                break;
            rep(j, 3) if (sum == B[j]) res += sum;
        }
        sum = m;
        rep(i, col) {
            sum += board[row][col - 1 - i];
            if (sum > B[2])
                break;
            rep(j, 3) if (sum == B[j]) res += sum;
        }
        return res;
    }

    void _place(int row, int col, int m, int next_score) {
        board[row][col] = m;
        score = next_score;
    }

    State place(int row, int col, int m, int next_score) {
        State res = *this;
        res._place(row, col, m, next_score);
        return res;
    }

    auto answer() {
        return board;
    }
};

struct beam_search {
    auto solve() {
        array<State, BEAM_SIZE> cur, nxt;
        cur[0] = State();
        int cur_size = 1, nxt_size = 0;
        rep(row, N) {
            rep(col, N) {
                priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> eval_que;
                nxt_size = 0;
                for (int i = 0; i < cur_size; ++i) {
                    auto &now = cur[i];
                    FOR(num, L[row][col], R[row][col] + 1) {
                        int eval = now.next_eval(row, col, num);
                        if (nxt_size < BEAM_SIZE) {
                            nxt[nxt_size] = now;
                            nxt[nxt_size]._place(row, col, num, eval);
                            eval_que.push({eval, nxt_size++});
                        } else if (eval > eval_que.top().first) {
                            int idx = eval_que.top().second;
                            eval_que.pop();
                            nxt[idx] = now;
                            nxt[idx]._place(row, col, num, eval);
                            eval_que.push({eval, idx});
                        }
                    }
                }
                swap(cur, nxt);
                cur_size = nxt_size;
            }
        }

        int idx = 0, max_eval = cur[0].eval();
        for (int i = 0; i < cur_size; ++i) {
            if (chmax(max_eval, cur[i].eval()))
                idx = i;
        }
        cerr << max_eval << endl;
        return cur[idx].answer();
    }
};

int main(void) {
    int tmp;
    cin >> tmp;
    rep(i, 3) cin >> B[i];
    rep(i, N) rep(j, N) cin >> L[i][j];
    rep(i, N) rep(j, N) cin >> R[i][j];

    beam_search solver;
    auto ans = solver.solve();

    for (auto &i : ans) {
        for (auto j : i) cout << int(j) << ' ';
        cout << endl;
    }

    return 0;
}
