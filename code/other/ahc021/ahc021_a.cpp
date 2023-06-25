#ifndef LOCAL
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#endif

#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
using ll = int64_t;
#define FOR(i, m, n) for (int i = (m); i < (n); ++i)
#define rep(i, n) FOR (i, 0, n)
template <class T, class U>
constexpr bool chmax(T &a, const U &b) noexcept {
    return a < (T)b ? a = b, true : false;
}
template <class T, class U>
constexpr bool chmin(T &a, const U &b) noexcept {
    return (T)b < a ? a = b, true : false;
}
constexpr int Inf = 1000000003;
constexpr int64_t INF = 1000000000000000003;

constexpr int N = 30;
constexpr int SIZE = 900;
constexpr int BALL_NUM = 465;

struct Pos {
    int x, y;

    constexpr Pos() : x(-1), y(-1) {}
    constexpr Pos(int t) : x(t / N), y(t % N) {}
    constexpr Pos(int _x, int _y) : x(_x), y(_y) {}

    constexpr Pos &operator+=(const Pos &rhs) noexcept {
        this->x += rhs.x, this->y += rhs.y;
        return *this;
    }
    constexpr Pos &operator-=(const Pos &rhs) noexcept {
        this->x -= rhs.x, this->y -= rhs.y;
        return *this;
    }

    constexpr Pos operator+(const Pos &rhs) const noexcept {
        return Pos(*this) += rhs;
    }
    constexpr Pos operator-(const Pos &rhs) const noexcept {
        return Pos(*this) -= rhs;
    }
    constexpr bool operator==(const Pos &rhs) const noexcept {
        return this->x == rhs.x && this->y == rhs.y;
    }
    constexpr bool operator!=(const Pos &rhs) const noexcept {
        return !(*this == rhs);
    }

    bool in_field() const {
        return 0 <= x && x < N && 0 <= y && y <= x;
    }

    int to_line() const {
        return x * N + y;
    }
};

constexpr std::array<Pos, 2> lower_pos = {Pos{1, 0}, {1, 1}};
constexpr std::array<Pos, 2> upper_pos = {Pos{-1, -1}, {-1, 0}};
constexpr std::array<Pos, 2> horizontal_pos = {Pos{0, -1}, {0, 1}};

std::array<int, BALL_NUM> default_height;

constexpr void init_default_height() {
    int cnt = 0;
    rep (i, N) {
        rep (j, i + 1) {
            default_height[cnt++] = i;
        }
    }
}

constexpr int abs_pow(int x) {
    return x * x;
}

template <int BEAM_SIZE>
struct beam_search {
    struct State {
        State() : score(), opp_num(), ball_num{}, ball_pos{}, operations() {}

        bool operator<(const State &rhs) const {
            return eval() < rhs.eval();
        }
        bool operator>(const State &rhs) const {
            return rhs < *this;
        }

        int rest() const {
            return score;
        }

        int eval() const {
            return score + current_score();
        }

        void init() {
            rep (i, N) {
                rep (j, i + 1) {
                    cin >> ball_num[i * N + j];
                    ball_pos[ball_num[i * N + j]] = {i, j};
                }
            }
            init_score();
        }

        void init_score() {
            rep (i, SIZE) {
                auto p = Pos(i);
                if (!p.in_field()) continue;
                score += max(0, p.x - default_height[ball_num[i]]);
            }
        }

        bool can_place(Pos move) const {
            auto nxt_pos = ball_pos[opp_num] + move;
            return nxt_pos.in_field() && opp_num < ball_num[nxt_pos.to_line()];
        }

        bool can_move() const {
            return can_place(upper_pos[0]) || can_place(upper_pos[1]);
        }

        auto place(Pos move) const {
            auto res(*this);
            auto cur_pos = ball_pos[opp_num];
            res._place(cur_pos, cur_pos + move);
            return res;
        }

        void place_inplace(Pos move) {
            auto cur_pos = ball_pos[opp_num];
            _place(cur_pos, cur_pos + move);
        }

        auto answer() const {
            return operations;
        }

        void assert_opp() const {
            assert(ball_pos[opp_num].x - default_height[opp_num] == 1);
        }

        int current_score() const {
            return operations.size();
        }

      private:
        int score, opp_num;
        array<int, SIZE> ball_num;
        array<Pos, BALL_NUM> ball_pos;
        vector<pair<int, int>> operations;

        void _place(Pos pos1, Pos pos2) {
            int x = pos1.to_line(), y = pos2.to_line();
            int b1 = ball_num[x], b2 = ball_num[y];
            operations.emplace_back(x, y);
            score -= max(0, pos1.x - default_height[b1]);
            score -= max(0, pos2.x - default_height[b2]);
            swap(ball_num[x], ball_num[y]);
            swap(ball_pos[b1], ball_pos[b2]);
            score += max(0, pos1.x - default_height[b2]);
            score += max(0, pos2.x - default_height[b1]);
            while (opp_num < BALL_NUM && ball_pos[opp_num].x == default_height[opp_num]) ++opp_num;
        }
    };

    auto solve() {
        vector<pair<int, int>> res;
        int min_score = 1000000000;
        std::array<State, BEAM_SIZE> cur, nxt;
        State init_state;
        init_state.init();
        cur[0] = init_state;
        int cur_size = 1, nxt_size = 0;
        for (int t = 0; t < 10000; ++t) {
            std::priority_queue<std::pair<int, int>> eval_que;
            nxt_size = 0;
            for (int i = 0; i < cur_size; ++i) {
                if (cur[i].current_score() >= min_score) continue;
                bool not_move = true;
                for (auto adj : upper_pos) {
                    if (!cur[i].can_place(adj)) continue;
                    not_move = false;
                    auto &&s = cur[i].place(adj);
                    int eval = s.eval();
                    if (s.rest() == 0) {
                        auto &&ans = s.answer();
                        if (chmin(min_score, ans.size())) res = ans;
                    }
                    if (nxt_size < BEAM_SIZE) {
                        nxt[nxt_size] = s;
                        eval_que.emplace(eval, nxt_size++);
                    } else if (eval < eval_que.top().first) {
                        int idx = eval_que.top().second;
                        eval_que.pop();
                        nxt[idx] = s;
                        eval_que.emplace(eval, idx);
                    }
                }
                if (not_move) {
                    cur[i].assert_opp();
                    for (auto adj : horizontal_pos) {
                        State tmp_state = cur[i];
                        while (!tmp_state.can_move()) {
                            if (tmp_state.can_place(adj)) tmp_state.place_inplace(adj);
                            else break;
                        }
                        if (tmp_state.can_move()) {
                            for (auto adj : upper_pos) {
                                if (!tmp_state.can_place(adj)) {
                                    continue;
                                }
                                auto &&s = tmp_state.place(adj);
                                int eval = s.eval();
                                if (s.rest() == 0) {
                        auto &&ans = s.answer();
                        if (chmin(min_score, ans.size())) res = ans;
                                }
                                if (nxt_size < BEAM_SIZE) {
                                    nxt[nxt_size] = s;
                                    eval_que.emplace(eval, nxt_size++);
                                } else if (eval < eval_que.top().first) {
                                    int idx = eval_que.top().second;
                                    eval_que.pop();
                                    nxt[idx] = s;
                                    eval_que.emplace(eval, idx);
                                }
                            }
                        }
                    }
                }
                if ((double)clock() / CLOCKS_PER_SEC >= 1.95) break;
            }
            if ((double)clock() / CLOCKS_PER_SEC >= 1.95) break;
            swap(cur, nxt);
            cur_size = nxt_size;
        }

        std::cerr << min_score << std::endl;
        return res;
    }
};

int main(void) {
    init_default_height();
    beam_search<150> solver;
    auto ans = solver.solve();
    cout << ans.size() << endl;
    for (auto [l, r] : ans) {
        auto p = Pos(l), q = Pos(r);
        cout << p.x << ' ' << p.y << ' ' << q.x << ' ' << q.y << endl;
    }

    return 0;
}
