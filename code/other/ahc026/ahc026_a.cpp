#ifndef LOCAL
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#endif

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <iostream>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <tuple>
#include <vector>

template <class T, class U>
constexpr bool chmax(T &a, const U &b) {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
constexpr bool chmin(T &a, const U &b) {
    return (T)b < a ? a = (T)b, true : false;
}

namespace lib {

struct Xorshift {
    using result_type = unsigned int;
    constexpr Xorshift() : x(123456789), y(362436069), z(521288629), w(88675123) {}

    static constexpr result_type min() { return std::numeric_limits<result_type>::min(); }
    static constexpr result_type max() { return std::numeric_limits<result_type>::max(); }
    result_type operator()() {
        result_type t = (x ^ (x << 11));
        x = y, y = z, z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }

    result_type rand_range(int a, int b) { return a + operator()() % (b - a + 1); }
    double random() { return (double)operator()() / max(); }

  private:
    result_type x, y, z, w;
} xor128;

template <class T>
struct Trace {
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

}  // namespace lib
using namespace lib;

constexpr int N = 200, M = 10;

struct Operation {
    int v, i, j, k;
};

Trace<Operation> trace;

template <int BEAM_SIZE>
struct BeamSearch {
    struct State {
        int trace_id;
        int score;
        std::array<std::vector<int>, M> boxes;

        State() {}

        State(const std::array<std::vector<int>, M> &boxes)
            : trace_id(-1), score(10000), boxes(boxes) {}

        std::pair<int, int> get_pos(int id) {
            for (int i = 0; i < M; ++i) {
                for (int j = 0; j < (int)boxes[i].size(); ++j) {
                    if (boxes[i][j] == id) return {i, j};
                }
            }
            return {-1, -1};
        }

        bool can_remove(int x, int y) const { return (int)boxes[x].size() == y + 1; }
        int get_next_id(int x, int y) const { return boxes[x][y + 1]; }

        int eval() const { return score; }

        int next_eval(const Operation &op) const {
            return op.i == -1 ? score : score - (boxes[op.j].size() - op.k + 1);
        }

        std::vector<int> get_candidate_idx(int i) const {
            std::array<int, M> ord, min_box;
            for (int j = 0; j < M; ++j) {
                if (boxes[j].empty()) min_box[j] = 10000;
                else min_box[j] = *std::min_element(boxes[j].begin(), boxes[j].end());
            }
            std::iota(ord.begin(), ord.end(), 0);
            std::sort(ord.begin(), ord.end(),
                      [&](int x, int y) { return min_box[x] > min_box[y]; });
            return std::vector<int>{ord[0], ord[1]};
        }

        void apply(const Operation &op) {
            if (op.i == -1) {
                trace_id = trace.push(op, trace_id);
                boxes[op.j].pop_back();
                return;
            }
            int idx = op.k + 1;
            std::vector<int> v{idx};
            while (idx < (int)boxes[op.j].size()) {
                int it = std::min_element(boxes[op.j].begin() + idx, boxes[op.j].end()) -
                         boxes[op.j].begin() + 1;
                v.emplace_back(it);
                idx = it;
            }
            for (int i = v.size() - 2; i >= 0; --i) {
                score -= v[i + 1] - v[i] + 1;
                boxes[op.i].insert(boxes[op.i].end(), boxes[op.j].begin() + v[i],
                                   boxes[op.j].begin() + v[i + 1]);
                trace_id = trace.push(Operation{boxes[op.j][v[i]], op.i, 0, 0}, trace_id);
            }
            trace_id = trace.push(Operation{boxes[op.j][op.k], -1, 0, 0}, trace_id);
            boxes[op.j].erase(boxes[op.j].begin() + op.k, boxes[op.j].end());
        }

        auto answer() const { return trace.chain(trace_id); }
    };

    std::vector<Operation> solve(const std::array<std::vector<int>, M> &boxes) {
        std::array<State, BEAM_SIZE> cur, nxt;
        cur[0] = State(boxes);
        int cur_size = 1;
        std::array<std::tuple<int, int, Operation>, BEAM_SIZE * 2 + M> eval_que;
        for (int id = 0; id < N; ++id) {
            int que_idx = 0;
            for (int i = 0; i < cur_size; ++i) {
                auto [j, k] = cur[i].get_pos(id);
                if (cur[i].can_remove(j, k)) {
                    int eval = cur[i].eval();
                    eval_que[que_idx++] = std::make_tuple(eval, i, Operation{id, -1, j, k});
                } else {
                    if (cur_size > 6561) {
                        for (auto m : cur[i].get_candidate_idx(j)) {
                            if (m == j) continue;
                            auto op = Operation{cur[i].get_next_id(j, k), m, j, k};
                            int eval = cur[i].next_eval(op);
                            eval_que[que_idx++] = std::make_tuple(eval, i, op);
                        }
                    } else {
                        for (int m = 0; m < M; ++m) {
                            if (m == j) continue;
                            auto op = Operation{cur[i].get_next_id(j, k), m, j, k};
                            int eval = cur[i].next_eval(op);
                            eval_que[que_idx++] = std::make_tuple(eval, i, op);
                        }
                    }
                }
                if (que_idx >= BEAM_SIZE * 2) {
                    std::nth_element(
                        eval_que.begin(), eval_que.begin() + BEAM_SIZE, eval_que.begin() + que_idx,
                        [](auto x, auto y) { return std::get<0>(x) > std::get<0>(y); });
                    que_idx = BEAM_SIZE;
                }
            }
            if (que_idx > BEAM_SIZE) {
                std::nth_element(eval_que.begin(), eval_que.begin() + BEAM_SIZE,
                                 eval_que.begin() + que_idx,
                                 [](auto x, auto y) { return std::get<0>(x) > std::get<0>(y); });
            }
            int nxt_size = std::min(BEAM_SIZE, que_idx);
            for (int i = 0; i < nxt_size; ++i) {
                auto [eval, prev_idx, op] = eval_que[i];
                nxt[i] = cur[prev_idx];
                nxt[i].apply(op);
            }
            std::swap(cur, nxt);
            cur_size = nxt_size;
        }

        int idx = 0, max_eval = cur[0].eval();
        for (int i = 1; i < cur_size; ++i) {
            if (chmax(max_eval, cur[i].eval())) idx = i;
        }
        // std::cerr << "Score = " << max_eval << std::endl;
        return cur[idx].answer();
    }
};

int main(void) {
    int tmp;
    std::cin >> tmp >> tmp;
    std::array<std::vector<int>, M> boxes;
    for (int i = 0; i < M; ++i) {
        boxes[i].resize(N / M);
        for (int j = 0; j < N / M; ++j) {
            std::cin >> boxes[i][j];
            --boxes[i][j];
        }
    }

    BeamSearch<12000> solver;
    auto operations = solver.solve(boxes);
    for (auto [v, i, j, k] : operations) { std::cout << v + 1 << ' ' << i + 1 << std::endl; }

    return 0;
}
