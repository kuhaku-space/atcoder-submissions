#ifndef LOCAL
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#endif

#include <algorithm>
#include <array>
#include <cstdint>
#include <functional>
#include <iostream>
#include <numeric>
#include <queue>
#include <random>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;
using ll = int64_t;
#define FOR(i, m, n) for (int i = (m); i < (n); ++i)
#define rep(i, n) FOR (i, 0, n)
template <class T, class U>
constexpr bool chmax(T &a, const U &b) noexcept {
    return a < b ? a = b, true : false;
}
template <class T, class U>
constexpr bool chmin(T &a, const U &b) noexcept {
    return b < a ? a = b, true : false;
}
constexpr int Inf = 1000000003;
constexpr int64_t INF = 1000000000000000003;

constexpr int N = 30;
constexpr int BALL_NUM = 465;
constexpr int SIZE = 900;

struct Position {
    int x, y;

    constexpr Position() : x(-1), y(-1) {}
    constexpr Position(int t) : x(t / N), y(t % N) {}
    constexpr Position(int _x, int _y) : x(_x), y(_y) {}

    constexpr Position &operator+=(const Position &rhs) noexcept {
        this->x += rhs.x, this->y += rhs.y;
        return *this;
    }
    constexpr Position &operator-=(const Position &rhs) noexcept {
        this->x -= rhs.x, this->y -= rhs.y;
        return *this;
    }

    constexpr Position operator+(const Position &rhs) const noexcept {
        return Position(*this) += rhs;
    }
    constexpr Position operator-(const Position &rhs) const noexcept {
        return Position(*this) -= rhs;
    }
    constexpr bool operator==(const Position &rhs) const noexcept {
        return this->x == rhs.x && this->y == rhs.y;
    }
    constexpr bool operator!=(const Position &rhs) const noexcept {
        return !(*this == rhs);
    }

    constexpr bool in_field() const {
        return 0 <= x && x < N && 0 <= y && y <= x;
    }

    constexpr int to_line() const {
        return x * N + y;
    }
};

constexpr std::array<Position, 2> lower_pos = {Position{1, 0}, {1, 1}},
                                  upper_pos = {Position{-1, -1}, {-1, 0}};

struct Operation {
    int x, y;

    constexpr Operation() : x(), y() {}
    constexpr Operation(int _x, int _y) : x(_x), y(_y) {}
    constexpr Operation(Position p, Position q) : x(p.to_line()), y(q.to_line()) {}
};

std::array<std::uint64_t, BALL_NUM> identity;

void set_identity() {
    std::mt19937_64 mt;
    std::generate(identity.begin(), identity.end(), std::ref(mt));
}

template <class T>
struct Trace {
    int push(T operation, int prev_idx) {
        log.emplace_back(operation, prev_idx);
        return log.size() - 1;
    }

    std::pair<T, int> get(int idx) {
        return log[idx];
    }

  private:
    std::vector<std::pair<T, int>> log;
};
Trace<Operation> trace;

template <int BEAM_SIZE>
struct beam_search {
    struct State {
        State() : score(), trace_idx(-1), seed(), ball_num{} {}

        bool operator<(const State &rhs) const {
            return eval() < rhs.eval();
        }
        bool operator>(const State &rhs) const {
            return rhs < *this;
        }

        int eval() const {
            return score;
        }

        auto get_seed() const {
            return seed;
        }

        void init() {
            rep (i, N) {
                rep (j, i + 1) {
                    cin >> ball_num[i * N + j];
                }
            }
        }

        int predict_score(Operation operation) {
            return score + ball_num[operation.x] - ball_num[operation.y];
        }

        bool can_place(Position pos1, Position pos2) const {
            return pos1.in_field() && pos2.in_field() &&
                   ball_num[pos1.to_line()] > ball_num[pos2.to_line()];
        }

        State apply(Operation operation) const {
            State res(*this);
            res._place(operation);
            return res;
        }

        auto answer() const {
            vector<Operation> res;
            int idx = trace_idx;
            while (idx != -1) {
                auto [operation, prev_idx] = trace.get(idx);
                res.emplace_back(operation);
                idx = prev_idx;
            }
            std::reverse(res.begin(), res.end());
            return res;
        }

      private:
        int score, trace_idx;
        std::uint64_t seed;
        array<int, SIZE> ball_num;

        void _place(Operation operation) {
            trace_idx = trace.push(operation, trace_idx);
            int x = operation.x, y = operation.y;
            score += ball_num[x] - ball_num[y];
            swap(ball_num[x], ball_num[y]);
        }
    };

    auto solve() {
        set_identity();
        std::array<State, BEAM_SIZE> cur, nxt;
        State init_state;
        init_state.init();
        cur[0] = init_state;
        int cur_size = 1, nxt_size = 0;
        for (int t = 0; t < 10000; ++t) {
            std::vector<std::tuple<int, Operation, int>> eval_que;
            nxt_size = 0;
            for (int i = 0; i < cur_size; ++i) {
                int cnt = 0;
                for (int cur_idx = 0; cur_idx < SIZE - N; ++cur_idx) {
                    auto cur_pos = Position(cur_idx);
                    if (!cur_pos.in_field()) continue;
                    for (auto adj : lower_pos) {
                        if (!cur[i].can_place(cur_pos, cur_pos + adj)) continue;
                        ++cnt;
                        auto operation = Operation(cur_pos, cur_pos + adj);
                        auto eval = cur[i].predict_score(operation);
                        eval_que.emplace_back(eval, operation, i);
                    }
                }
                if (cnt == 0) {
                    std::cerr << 100000 - 5 * cur[i].answer().size() << std::endl;
                    return cur[i].answer();
                }
            }
            std::sort(eval_que.begin(), eval_que.end(), [](auto l, auto r) {
                return std::get<0>(l) > std::get<0>(r);
            });

            std::unordered_set<std::uint64_t> st;
            for (int i = 0; i < (int)eval_que.size(); i++) {
                auto [eval, operation, prev_idx] = eval_que[i];
                auto x = cur[prev_idx].get_seed();
                x ^= identity[operation.x];
                x ^= identity[operation.y];
                if (st.emplace(x).second) nxt[nxt_size++] = cur[prev_idx].apply(operation);
                if (nxt_size == BEAM_SIZE) break;
            }
            swap(cur, nxt);
            cur_size = nxt_size;
        }
    }
};

int main(void) {
    beam_search<40> solver;
    auto ans = solver.solve();
    cout << ans.size() << '\n';
    for (auto [l, r] : ans) {
        auto p = Position(l), q = Position(r);
        cout << p.x << ' ' << p.y << ' ' << q.x << ' ' << q.y << '\n';
    }

    return 0;
}
