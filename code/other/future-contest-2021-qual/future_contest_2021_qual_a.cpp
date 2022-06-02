/*
 * Probrem : https://atcoder.jp/contests/future-contest-2021-qual/tasks/future_contest_2021_qual_a
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

struct Pos {
    int x, y;

    void input() {
        cin >> x >> y;
    }

    bool operator==(const Pos &rhs) const {
        return x == rhs.x && y == rhs.y;
    }
    bool operator<(const Pos &rhs) const {
        return x < rhs.x;
    }

    int dist(const Pos &p) const {
        return abs(x - p.x) + abs(y - p.y);
    }
};

constexpr int BEAM_SIZE = 28000;
constexpr int N = 20, M = 100;

array<Pos, M> init_pos;
array<Pos, M> fin_pos;

string move_op(const Pos &from, const Pos &to) {
    string res;
    int dx = to.x - from.x, dy = to.y - from.y;
    if (dx > 0)
        res += string(dx, 'D');
    else if (dx < 0)
        res += string(-dx, 'U');
    if (dy > 0)
        res += string(dy, 'R');
    else if (dy < 0)
        res += string(-dy, 'L');
    return res;
}

struct State {
    Pos now_pos;
    vector<int> deck;
    bitset<M> is_have;
    int score = 4000;

    State() {
        now_pos = Pos{0, 0};
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

    bool yet_have(int id) const {
        return is_have[id];
    }

    int next_score(int id) const {
        return score - now_pos.dist(init_pos[id]) - (deck.empty() ? 0 : fin_pos[id].dist(fin_pos[deck.back()]));
    }

    void update_score(int id) {
        score -= now_pos.dist(init_pos[id]) + (deck.empty() ? 0 : fin_pos[id].dist(fin_pos[deck.back()]));
        deck.emplace_back(id);
        is_have.set(id);
        now_pos = init_pos[id];
    }

    void take(int id) {
        update_score(id);
    }

    void put() {
        score -= init_pos[deck.back()].dist(fin_pos[deck.back()]);
        score -= fin_pos[deck.front()].dist(fin_pos[0]);
    }

    string answer() {
        string op;
        now_pos = Pos{0, 0};
        for (int i = 0; i < M; ++i) {
            op += move_op(now_pos, init_pos[deck[i]]) + "I";
            now_pos = init_pos[deck[i]];
        }
        for (int i = M - 1; i >= 0; --i) {
            int t = deck[i];
            op += move_op(now_pos, fin_pos[t]) + "O";
            now_pos = fin_pos[t];
        }
        op += move_op(now_pos, fin_pos[0]);
        string s1, s2;
        rep(i, 10) {
            s1 += "IR";
            s2 += "IL";
        }
        s1.pop_back();
        s2.pop_back();
        rep(i, 5) op += s1 + "D" + s2 + "D";
        op.pop_back();
        return op;
    }
};

struct beam_search {
    string solve() {
        array<State, BEAM_SIZE> cur, nxt;
        cur[0] = State();
        int cur_size = 1, nxt_size = 0;
        for (int t = 0; t < M; ++t) {
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> eval_que;
            nxt_size = 0;
            for (int i = 0; i < cur_size; ++i) {
                auto &now = cur[i];
                for (int id = 0; id < M; ++id) {
                    if (now.yet_have(id))
                        continue;
                    int eval = now.next_score(id);
                    if (nxt_size < BEAM_SIZE) {
                        nxt[nxt_size] = now;
                        nxt[nxt_size].take(id);
                        eval_que.push({eval, nxt_size++});
                    } else if (eval > eval_que.top().first) {
                        int idx = eval_que.top().second;
                        eval_que.pop();
                        nxt[idx] = now;
                        nxt[idx].take(id);
                        eval_que.push({eval, idx});
                    }
                }
            }
            swap(cur, nxt);
            cur_size = nxt_size;
        }
        for (int i = 0; i < cur_size; ++i) {
            cur[i].put();
        }

        int idx = 0, max = cur[0].eval();
        for (int i = 1; i < cur_size; ++i) {
            if (chmax(max, cur[i].eval()))
                idx = i;
        }
        cerr << cur[idx].eval() << endl;
        return cur[idx].answer();
    }
};

void init() {
    rep(i, M) init_pos[i].input();
    rep(i, M) {
        if ((i / 10) & 1)
            fin_pos[i] = Pos{5 + i / 10, 14 - i % 10};
        else
            fin_pos[i] = Pos{5 + i / 10, 5 + i % 10};
    }
}

int main(void) {
    init();
    beam_search solver;
    auto ans = solver.solve();
    cout << ans << endl;
}
