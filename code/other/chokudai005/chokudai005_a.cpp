/*
 * Problem : https://atcoder.jp/contests/chokudai005/tasks/chokudai005_a
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

constexpr int N = 100, M = 50;
constexpr int K = 9;
constexpr int BEAM_SIZE = 30;

array<string, N> board;

struct Pos {
    int x, y;

    Pos &operator+=(const Pos &rhs) {
        x += rhs.x, y += rhs.y;
        return *this;
    }
    Pos &operator-=(const Pos &rhs) {
        x -= rhs.x, y -= rhs.y;
        return *this;
    }

    Pos operator+(const Pos &rhs) const {
        return Pos(*this) += rhs;
    }
    Pos operator-(const Pos &rhs) const {
        return Pos(*this) -= rhs;
    }

    inline bool in_board() const {
        return x >= 0 && x < N && y >= 0 && y < N;
    }
};

vector<Pos> dir = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

struct State {
    array<bitset<N>, N> is_same;
    int score, base_x, base_y;
    char ch;
    string ops;

    State() {}
    State(int x, int y) : is_same(), score(), base_x(x), base_y(y) {
        ch = board[base_x][base_y];
        is_same[base_x][base_y] = true;
        update();
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

    int count_area() const {
        int res = 0;
        for (auto i : is_same) res += i.count();
        return res;
    }

    void update() {
        array<bitset<N>, N> is_visit;
        queue<Pos> que;
        que.push(Pos{base_x, base_y});
        while (!que.empty()) {
            Pos p = que.front();
            que.pop();
            if (!p.in_board())
                continue;
            if (!is_same[p.x][p.y] && board[p.x][p.y] != ch)
                continue;
            is_same[p.x][p.y] = true;
            for (auto i : dir) {
                Pos tmp = p + i;
                if (!tmp.in_board())
                    continue;
                if (is_visit[tmp.x][tmp.y])
                    continue;
                is_visit[tmp.x][tmp.y] = true;
                if (tmp.in_board())
                    que.push(tmp);
            }
        }
    }

    bool is_finish() const {
        return score == N * N;
    }

    bool is_same_number(char k) const {
        return ch == k;
    }

    void update_board(char op) {
        ch = op;
        update();
    }

    void update_score() {
        score = count_area();
    }

    State place(char op) const {
        State res(*this);
        res.ops.push_back(op);
        if (ch == op)
            return res;
        res.update_board(op);
        res.update_score();
        return res;
    }

    string answer() const {
        return ops;
    }
};

struct beam_search {
    auto solve() {
        array<State, BEAM_SIZE> cur, nxt;
        cur[0] = State(M, M);
        cur[1] = State(M - 1, M);
        cur[2] = State(M, M - 1);
        cur[3] = State(M - 1, M - 1);
        int cur_size = 4, nxt_size = 0;
        while (true) {
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> eval_que;
            nxt_size = 0;
            for (int i = 0; i < cur_size; ++i) {
                auto &now = cur[i];
                for (char k = 1; k <= K; ++k) {
                    if (cur[i].is_same_number(k))
                        continue;
                    auto s = cur[i].place(k);
                    if (s.is_finish())
                        return s;
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
    }
};

int main(void) {
    int tmp;
    cin >> tmp >> tmp >> tmp;
    for (auto &s : board) cin >> s;
    for (auto &s : board) {
        for (auto &c : s) c -= '0';
    }
    beam_search solver;
    auto ans = solver.solve();
    cerr << ans.answer().size() << endl;
    cout << ans.answer().size() << endl;
    for (auto i : ans.answer()) cout << ans.base_x + 1 << " " << ans.base_y + 1 << " " << int(i) << endl;
}
