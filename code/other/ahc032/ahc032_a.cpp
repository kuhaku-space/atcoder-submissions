#include <algorithm>
#include <array>
#include <bit>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <numeric>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <utility>
#include <vector>

constexpr int N = 9;
constexpr int M = 20;
constexpr int K = 81;
constexpr int MOD = 998244353;

using namespace std;

namespace lib {
// clang-format off

constexpr int inf = 1000000000;

template <class T, class U>
constexpr bool chmax(T &a, const U &b) {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
constexpr bool chmin(T &a, const U &b) {
    return (T)b < a ? a = (T)b, true : false;
}

struct Position {
    int x, y;

    constexpr Position() : x(), y() {}
    constexpr Position(int _x, int _y) : x(_x), y(_y) {}

    constexpr Position &operator+=(const Position &rhs) {
        this->x += rhs.x, this->y += rhs.y;
        return *this;
    }
    constexpr Position &operator-=(const Position &rhs) {
        this->x -= rhs.x, this->y -= rhs.y;
        return *this;
    }

    constexpr Position operator+(const Position &rhs) const { return Position(*this) += rhs; }
    constexpr Position operator-(const Position &rhs) const { return Position(*this) -= rhs; }

    constexpr bool operator==(const Position &rhs) const{ return x == rhs.x && y == rhs.y; }
    constexpr bool operator<(const Position &rhs) const{ return x == rhs.x ? y < rhs.y : x < rhs.x; }

    friend std::ostream &operator<<(std::ostream &os, const Position &rhs) {
        return os << rhs.x << ' ' << rhs.y;
    }

    int dist(const Position &rhs) const { return abs(x - rhs.x) + abs(y - rhs.y); }

    Position next() const {
        Position res = *this;
        if (x == N-3){
            res.x=0;
            if (y == N-3){
                res = Position(-1,-1);
            } else {
                ++res.y;
            }
        } else {
            ++res.x;
        }
        return res;
    }
};

template <class T>
struct Trace {
    int size() const { return log.size(); }

    int push(T operation, int prev_idx) {
        log.emplace_back(operation, prev_idx);
        return log.size() - 1;
    }

    std::pair<T, int> get(int idx) const { return log[idx]; }

    std::vector<T> chain(int idx, int root = -1) const {
        std::vector<T> res;
        while (idx != root) {
            res.emplace_back(log[idx].first);
            idx = log[idx].second;
        }
        std::reverse(res.begin(), res.end());
        return res;
    }

  private:
    std::vector<std::pair<T, int>> log;
};

struct Xorshift {
    using state_type = std::array<std::uint32_t, 4>;
    using result_type = std::uint32_t;
    constexpr Xorshift() : state{123456789, 362436069, 521288629, 88675123} {}

    static constexpr result_type min() { return std::numeric_limits<result_type>::min(); }
    static constexpr result_type max() { return std::numeric_limits<result_type>::max(); }
    result_type operator()() {
        std::uint32_t t = (state[0] ^ (state[0] << 11));
        state[0] = state[1], state[1] = state[2], state[2] = state[3];
        return state[3] = (state[3] ^ (state[3] >> 19)) ^ (t ^ (t >> 8));
    }
    bool operator==(const Xorshift &rhs) noexcept { return (state == rhs.state); }
    bool operator!=(const Xorshift &rhs) noexcept { return (state != rhs.state); }

    constexpr state_type serialize() const noexcept { return state; }
    constexpr void deserialize(const state_type &data) noexcept { state = data; }
    constexpr void deserialize(state_type &&data) noexcept { state = std::move(data); }

  private:
    state_type state;
};
Xorshift xorshift;

// clang-format on
}  // namespace lib
using namespace lib;

struct Stamp {
    array<array<int, 3>, 3> s;
};

array<Stamp, M> stamps;

struct Operation {
    int m;
    Position shift;

    Operation() {}
    Operation(int m, int x, int y) : m(m), shift(x, y) {}

    bool operator==(const Operation &rhs) const {
        return m == rhs.m && shift == rhs.shift;
    }
    bool operator!=(const Operation &rhs) const {
        return !(*this == rhs);
    }

    Operation next() {
        if (m == -1) return *this;
        Operation res = *this;
        if (m == M - 1) {
            res.m = 0;
            if (shift.x == N - 3) {
                res.shift.x = 0;
                if (shift.y == N - 3) {
                    res = Operation(-1, -1, -1);
                } else {
                    ++res.shift.y;
                }
            } else {
                ++res.shift.x;
            }
        } else {
            ++res.m;
        }
        return res;
    }

    friend std::ostream &operator<<(std::ostream &os, const Operation &rhs) {
        return os << rhs.m << ' ' << rhs.shift.x << ' ' << rhs.shift.y;
    }
};

Trace<Operation> trace;

struct State {
    int64_t score;
    array<array<int, N>, N> board;
    int trace_idx;
    Operation prev_op;

    State() {}
    State(const array<array<int, N>, N> &board)
        : score{board[0][0]}, board(board), trace_idx{-1}, prev_op(0, 0, 0) {}

    int64_t calc_score() const {
        int64_t res = 0;
        for (int x = 0; x < N; ++x) {
            for (int y = 0; y < N; ++y) {
                res += board[x][y];
            }
        }
        return res;
    }

    int64_t next_eval(const Operation &op) const {
        int64_t res = score;
        Position pos = prev_op.shift;
        while (pos != op.shift) {
            pos = pos.next();
            if (pos == Position(N - 3, N - 3)) {
                for (int dx = 0; dx < 3; ++dx) {
                    for (int dy = 0; dy < 3; ++dy) {
                        res += board[pos.x + dx][pos.y + dy];
                    }
                }
            } else if (pos.y == N - 3) {
                for (int dy = 0; dy < 3; ++dy) {
                    res += board[pos.x][pos.y + dy];
                }
            } else if (pos.x == N - 3) {
                for (int dx = 0; dx < 3; ++dx) {
                    res += board[pos.x + dx][pos.y];
                }
            }
        }
        if (op.shift == Position(N - 3, N - 3)) {
            for (int dx = 0; dx < 3; ++dx) {
                for (int dy = 0; dy < 3; ++dy) {
                    res -= board[op.shift.x + dx][op.shift.y + dy];
                    res += (board[op.shift.x + dx][op.shift.y + dy] + stamps[op.m].s[dx][dy]) % MOD;
                }
            }
        } else if (op.shift.y == N - 3) {
            for (int dy = 0; dy < 3; ++dy) {
                res -= board[op.shift.x][op.shift.y + dy];
                res += (board[op.shift.x][op.shift.y + dy] + stamps[op.m].s[0][dy]) % MOD;
            }
        } else if (op.shift.x == N - 3) {
            for (int dx = 0; dx < 3; ++dx) {
                res -= board[op.shift.x + dx][op.shift.y];
                res += (board[op.shift.x + dx][op.shift.y] + stamps[op.m].s[dx][0]) % MOD;
            }
        } else {
            res -= board[op.shift.x][op.shift.y];
            res += (board[op.shift.x][op.shift.y] + stamps[op.m].s[0][0]) % MOD;
        }
        return res;
    }

    int64_t eval() const {
        return score;
    }

    void apply(const Operation &op) {
        Position pos = prev_op.shift;
        while (pos != op.shift) {
            pos = pos.next();
            if (pos == Position(N - 3, N - 3)) {
                for (int dx = 0; dx < 3; ++dx) {
                    for (int dy = 0; dy < 3; ++dy) {
                        score += board[pos.x + dx][pos.y + dy];
                    }
                }
            } else if (pos.y == N - 3) {
                for (int dy = 0; dy < 3; ++dy) {
                    score += board[pos.x][pos.y + dy];
                }
            } else if (pos.x == N - 3) {
                for (int dx = 0; dx < 3; ++dx) {
                    score += board[pos.x + dx][pos.y];
                }
            }
        }
        if (op.shift == Position(N - 3, N - 3)) {
            for (int dx = 0; dx < 3; ++dx) {
                for (int dy = 0; dy < 3; ++dy) {
                    score -= board[op.shift.x + dx][op.shift.y + dy];
                    board[op.shift.x + dx][op.shift.y + dy] =
                        (board[op.shift.x + dx][op.shift.y + dy] + stamps[op.m].s[dx][dy]) % MOD;
                    score += board[op.shift.x + dx][op.shift.y + dy];
                }
            }
        } else if (op.shift.y == N - 3) {
            for (int dy = 0; dy < 3; ++dy) {
                score -= board[op.shift.x][op.shift.y + dy];
                score += (board[op.shift.x][op.shift.y + dy] + stamps[op.m].s[0][dy]) % MOD;
            }
        } else if (op.shift.x == N - 3) {
            for (int dx = 0; dx < 3; ++dx) {
                score -= board[op.shift.x + dx][op.shift.y];
                score += (board[op.shift.x + dx][op.shift.y] + stamps[op.m].s[dx][0]) % MOD;
            }
        } else {
            score -= board[op.shift.x][op.shift.y];
            score += (board[op.shift.x][op.shift.y] + stamps[op.m].s[0][0]) % MOD;
        }
        prev_op = op;
        trace_idx = trace.push(op, trace_idx);
        for (int dx = 0; dx < 3; ++dx) {
            for (int dy = 0; dy < 3; ++dy) {
                board[op.shift.x + dx][op.shift.y + dy] =
                    (board[op.shift.x + dx][op.shift.y + dy] + stamps[op.m].s[dx][dy]) % MOD;
            }
        }
    }

    vector<Operation> answer() {
        return trace.chain(trace_idx);
    }
};

template <int BEAM_SIZE>
struct beam_search {
    auto solve(const array<array<int, N>, N> &board) {
        std::array<State, BEAM_SIZE> cur, nxt;
        cur[0] = State(board);
        int cur_size = 1;
        int64_t max_score = cur[0].calc_score();
        vector<Operation> res;
        std::array<std::tuple<int64_t, int, Operation>, BEAM_SIZE * 2 + M *(N - 2) * (N - 2)>
            eval_que;
        for (int k = 0; k < K; ++k) {
            int que_idx = 0;
            for (int i = 0; i < cur_size; ++i) {
                Operation op = cur[i].prev_op;
                int cnt = 0;
                while (cnt < 50 && op.m != -1) {
                    int64_t eval = cur[i].next_eval(op);
                    eval_que[que_idx++] = std::make_tuple(eval, i, op);
                    op = op.next();
                    ++cnt;
                }
                if (que_idx >= BEAM_SIZE * 2) {
                    std::sort(eval_que.begin(), eval_que.begin() + que_idx,
                              [](auto x, auto y) { return std::get<0>(x) > std::get<0>(y); });
                    int idx = 0;
                    array<short, (N - 2) * (N - 2) * M> count = {};
                    for (int i = 0; i < que_idx; ++i) {
                        auto &&[eval, prev_idx, op] = eval_que[i];
                        int hash = (op.shift.x * (N - 2) + op.shift.y) * M + op.m;
                        if (count[hash] < 3) {
                            if (i != idx) swap(eval_que[idx], eval_que[i]);
                            ++count[hash];
                            ++idx;
                        }
                    }
                    que_idx = std::min(BEAM_SIZE, idx);
                }
            }

            if (que_idx > BEAM_SIZE) {
                std::sort(eval_que.begin(), eval_que.begin() + que_idx,
                          [](auto x, auto y) { return std::get<0>(x) > std::get<0>(y); });
                int idx = 0;
                array<short, (N - 2) * (N - 2) * M> count = {};
                for (int i = 0; i < que_idx; ++i) {
                    auto &&[eval, prev_idx, op] = eval_que[i];
                    int hash = (op.shift.x * (N - 2) + op.shift.y) * M + op.m;
                    if (count[hash] < 3) {
                        if (i != idx) swap(eval_que[idx], eval_que[i]);
                        ++count[hash];
                        ++idx;
                    }
                }
                que_idx = std::min(BEAM_SIZE, idx);
            }

            int nxt_size = std::min(BEAM_SIZE, que_idx);
            for (int i = 0; i < nxt_size; ++i) {
                auto &&[eval, prev_idx, op] = eval_que[i];
                nxt[i] = cur[prev_idx];
                nxt[i].apply(op);
                if (chmax(max_score, nxt[i].calc_score())) {
                    res = nxt[i].answer();
                }
            }

            cur = nxt;
            cur_size = nxt_size;
        }

        // std::cerr << "BeamScore = " << max_score << std::endl;
        return res;
    }
};

int main(void) {
    int tmp;
    cin >> tmp >> tmp >> tmp;
    array<array<int, N>, N> board;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> board[i][j];
        }
    }
    for (int i = 0; i < M; ++i) {
        for (int x = 0; x < 3; ++x) {
            for (int y = 0; y < 3; ++y) {
                cin >> stamps[i].s[x][y];
            }
        }
    }

    beam_search<4900> solver;
    vector<Operation> answer = solver.solve(board);

    for (Operation op : answer) {
        for (int dx = 0; dx < 3; ++dx) {
            for (int dy = 0; dy < 3; ++dy) {
                board[op.shift.x + dx][op.shift.y + dy] =
                    (board[op.shift.x + dx][op.shift.y + dy] + stamps[op.m].s[dx][dy]) % MOD;
            }
        }
    }

    int64_t max_score = 0;
    array<array<int, 3>, 3> tmp_board;
    for (int x = N - 3; x < N; ++x) {
        for (int y = N - 3; y < N; ++y) {
            tmp_board[x - (N - 3)][y - (N - 3)] = board[x][y];
            max_score += board[x][y];
        }
    }
    vector<Operation> ans, tmp_v;
    auto dfs = [&](auto self, int stamp_idx, int rest,
                   const array<array<int, 3>, 3> &local_board) -> void {
        if (rest == 0) return;
        for (int i = stamp_idx; i < M; ++i) {
            Operation op(stamp_idx, N - 3, N - 3);
            tmp_v.emplace_back(op);
            array<array<int, 3>, 3> copy_board;
            int64_t sum = 0;
            for (int dx = 0; dx < 3; ++dx) {
                for (int dy = 0; dy < 3; ++dy) {
                    copy_board[dx][dy] = (local_board[dx][dy] + stamps[op.m].s[dx][dy]) % MOD;
                    sum += copy_board[dx][dy];
                }
            }
            if (chmax(max_score, sum)) {
                ans = tmp_v;
            }
            self(self, i, rest - 1, copy_board);
            tmp_v.pop_back();
        }
    };

    dfs(dfs, 0, std::min(7, K - (int)answer.size()), tmp_board);
    for (auto op : ans) answer.emplace_back(op);

    cout << answer.size() << endl;
    for (Operation op : answer) {
        cout << op << endl;
    }

    return 0;
}
