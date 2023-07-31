/**
 * @file main.cpp
 * @author kuhaku-space (kuhakuspace2000@gmail.com)
 * @brief Introduction to Heuristics Contest solution
 * @version 0.1
 * @date 2021-12-13
 * @details [問題](https://atcoder.jp/contests/intro-heuristics/tasks/intro_heuristics_a)
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef LOCAL
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#endif

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <iostream>
#include <queue>
#include <set>
#include <tuple>
#include <vector>

using namespace std;
using ll = int64_t;
#define FOR(i, m, n) for (int i = (m); i < (n); ++i)
#define rep(i, n) FOR (i, 0, n)
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

constexpr double T0 = 2e3, T1 = 6e2;

// clang-format off
struct Xorshift {
    using result_type = unsigned int;
    constexpr Xorshift() : x(123456789), y(362436069), z(521288629), w(88675123) {}
    constexpr Xorshift(result_type _w) : x(123456789), y(362436069), z(521288629), w(_w) {}

    constexpr result_type min() const { return std::numeric_limits<result_type>::min(); }
    constexpr result_type max() const { return std::numeric_limits<result_type>::max(); }
    result_type operator()() {
        result_type t = (x ^ (x << 11));
        x = y, y = z, z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }

    result_type rand_range(int a, int b) { return a + this->operator()() % (b - a + 1); }
    double rand_d() { return (double)this->operator()() / this->max(); }

  private:
    result_type x, y, z, w;
};

struct Timer {
    std::chrono::system_clock::time_point start;

    Timer() : start(std::chrono::system_clock::now()) {}

    int64_t operator()() const { return this->get_time(); }

    int64_t get_time() const {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now() - start)
            .count();
    }

    void reset() { this->start = std::chrono::system_clock::now(); }
};

template <int TL>
struct SA {
    Timer timer;
    Xorshift xor128;

    SA() : timer(), xor128() {}

    auto get_time() {
        return this->timer.get_time();
    }

    /**
     * @brief 温度関数
     *
     * @param t 時間
     * @return double
     */
    double temperature(double t) {
        t /= TL;
        return pow(T0, 1.0 - t) * pow(T1, t);
    }
    double temperature() {
        return this->temperature(this->get_time());
    }

    /**
     * @brief 遷移関数
     *
     * @tparam T スコアの型
     * @param diff_score 差分スコア
     * @param temp 温度
     * @return true
     * @return false
     */
    template <class T>
    bool is_update(T diff_score, double temp) {
        if (diff_score >= 0)
            return true;
        return exp((double)diff_score / temp) >= this->xor128.rand_d();
    }
};
// clang-format on

Xorshift xor128;

constexpr int SZ = 26;
constexpr int D = 365;
array<int, SZ> C;
int SUM = 0;
array<array<int, SZ>, D> S;

struct Operation {
    int d, t;
};

template <class T>
struct Trace {
    int push(T x, int prev_idx) {
        log.emplace_back(x, prev_idx);
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
        array<short, SZ> last;
        int score, sum, trace_idx;

        State() : last{}, score(), sum(), trace_idx(-1) {}

        void update_score(Operation op) {
            int d = op.d, t = op.t;
            sum += SUM - C[t] * (d + 1 - last[t]);
            score += S[d][t] - sum;
            last[t] = d + 1;
        }

        int next_eval(int d, int t) {
            return score + S[d][t] + C[t] * (d + 1 - last[t]) - sum - SUM;
        }

        int eval() const {
            return score;
        }

        State apply(Operation op) const {
            State res{*this};
            res.place(op);
            return res;
        }

        void place(Operation op) {
            trace_idx = trace.push(op, trace_idx);
            update_score(op);
        }

        array<char, D> answer() {
            array<char, D> ans = {};
            int idx = trace_idx;
            while (idx != -1) {
                auto [op, prev_idx] = trace.get(idx);
                ans[op.d] = op.t;
                idx = prev_idx;
            }
            return ans;
        }
    };

    auto solve() {
        array<State, BEAM_SIZE> cur, nxt;
        cur[0] = State();
        int cur_size = 1;
        rep (d, D) {
            vector<tuple<int, int, Operation>> eval_que;
            eval_que.reserve(cur_size * SZ);
            for (int i = 0; i < cur_size; ++i) {
                rep (t, SZ) {
                    int eval = cur[i].next_eval(d, t);
                    eval_que.emplace_back(eval, i, Operation{d, t});
                }
            }
            if (eval_que.size() > BEAM_SIZE) {
                nth_element(eval_que.begin(), eval_que.begin() + BEAM_SIZE, eval_que.end(),
                            [](auto x, auto y) {
                                return get<0>(x) > get<0>(y);
                            });
            }
            int nxt_size = 0;
            for (int i = 0; i < min(BEAM_SIZE, (int)eval_que.size()); i++) {
                auto &&[eval, prev_idx, operation] = eval_que[i];
                nxt[i] = cur[prev_idx].apply(operation);
            }
            swap(cur, nxt);
            cur_size = nxt_size;
        }

        int idx = 0, max_eval = cur[0].eval();
        for (int i = 1; i < cur_size; ++i) {
            if (chmax(max_eval, cur[i].eval())) idx = i;
        }
        return cur[idx].answer();
    }
};

template <int TL>
struct annealing {
    struct State {
        int score;
        array<char, D> ans;
        array<vector<int>, SZ> memo;

        State(const array<char, D> &arr) : ans(arr) {}

        auto get_score() const {
            return score;
        }

        auto get_char(int d) const {
            return ans[d];
        }

        void build() {
            score = 0;
            int sum = 0;
            array<short, SZ> last = {};
            rep (i, SZ) {
                memo[i].emplace_back(-1);
            }
            rep (d, D) {
                memo[ans[d]].emplace_back(d);
                char t = ans[d];
                sum += SUM - C[t] * (d + 1 - last[t]);
                score += S[d][t] - sum;
                last[t] = d + 1;
            }
            rep (i, SZ) {
                memo[i].emplace_back(D);
            }
        }

        auto update(int d, char e) {
            auto a = ans[d];
            if (a == e) return a;
            auto it = lower_bound(memo[a].begin(), memo[a].end(), d);
            auto ne = *next(it), pr = *prev(it);
            score -= C[a] * (ne - d) * (d - pr);
            memo[a].erase(it);
            it = lower_bound(memo[e].begin(), memo[e].end(), d);
            ne = *it, pr = *prev(it);
            score += C[e] * (ne - d) * (d - pr);
            score += S[d][e] - S[d][a];
            memo[e].emplace(it, d);
            ans[d] = e;
            return a;
        }
    };

    SA<TL> sa;

    int get_time() {
        return sa.get_time();
    }

    int solve(array<char, D> &ans) {
        State state(ans);
        state.build();
        int max_score = state.get_score();

        int score = max_score;
        while (sa.get_time() < TL) {
            double temp = sa.temperature();
            rep (i, 300) {
                if (xor128() % 2) {
                    int d = xor128() % D;
                    char e = xor128() % SZ;
                    auto p = state.update(d, e);
                    int new_score = state.get_score();
                    if (!sa.is_update(new_score - score, temp)) {
                        state.update(d, p);
                    } else {
                        score = new_score;
                    }
                } else {
                    int d1 = xor128() % (D - 1);
                    int d2 = min((int)(d1 + 1 + xor128() % 10), D - 1);
                    auto q = state.get_char(d2);
                    auto p = state.update(d1, q);
                    q = state.update(d2, p);
                    int new_score = state.get_score();
                    if (!sa.is_update(new_score - score, temp)) {
                        state.update(d1, p);
                        state.update(d2, q);
                    } else {
                        score = new_score;
                    }
                }

                if (chmax(max_score, score)) {
                    ans = state.ans;
                }
            }
        }

        return max_score;
    }
};

int main(void) {
    int tmp;
    cin >> tmp;
    rep (i, SZ) cin >> C[i];
    rep (i, SZ) SUM += C[i];
    rep (i, D)
        rep (j, SZ) cin >> S[i][j];

    beam_search<4000> solver1;
    annealing<1985> solver2;
    auto ans = solver1.solve();
    cerr << (double)clock() / CLOCKS_PER_SEC << endl;
    cerr << "Score = " << solver2.solve(ans) + 1000000 << endl;
    for (auto i : ans) cout << (int)i + 1 << endl;

    return 0;
}
