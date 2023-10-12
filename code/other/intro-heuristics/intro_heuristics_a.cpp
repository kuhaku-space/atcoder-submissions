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
#include <numeric>
#include <queue>
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
    double rand_d() { return (double)operator()() / max(); }

  private:
    result_type x, y, z, w;
};

using namespace std::chrono;

struct Timer {
    Timer() : start(system_clock::now()) {}

    std::int64_t operator()() const { return get_time(); }

    std::int64_t get_time() const {
        return duration_cast<milliseconds>(system_clock::now() - start).count();
    }

    void reset() { start = system_clock::now(); }

  private:
    system_clock::time_point start;
};

template <int TL>
struct SA {
    SA() : timer(), xor128() {}

    auto get_time() { return timer.get_time(); }

    /**
     * @brief 温度関数
     *
     * @param t 時間
     * @return double
     */
    double temperature(double t) {
        t /= TL;
        return std::pow(T0, 1.0 - t) * std::pow(T1, t);
    }
    double temperature() { return temperature(get_time()); }

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
        if (diff_score >= 0) return true;
        return std::exp((double)diff_score / temp) >= xor128.rand_d();
    }

  private:
    static constexpr double T0 = 2e3, T1 = 6e2;
    Timer timer;
    Xorshift xor128;
};

template <class T>
struct Trace {
    int push(T x, int prev_idx) {
        log.emplace_back(x, prev_idx);
        return log.size() - 1;
    }

    std::pair<T, int> get(int idx) { return log[idx]; }

  private:
    std::vector<std::pair<T, int>> log;
};

}  // namespace lib

constexpr int CONTEST_SIZE = 26;
constexpr int D = 365;
std::array<int, CONTEST_SIZE> C;
int SUM = 0;
std::array<std::array<int, CONTEST_SIZE>, D> S;

struct Operation {
    int d, t;
};

lib::Trace<Operation> trace;

template <int BEAM_SIZE>
struct beam_search {
    struct State {
        std::array<short, CONTEST_SIZE> last;
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

        int eval() const { return score; }

        State apply(Operation op) const {
            State res{*this};
            res.place(op);
            return res;
        }

        void place(Operation op) {
            trace_idx = trace.push(op, trace_idx);
            update_score(op);
        }

        std::array<char, D> answer() {
            std::array<char, D> ans = {};
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
        std::array<State, BEAM_SIZE> cur, nxt;
        cur[0] = State();
        int cur_size = 1;
        for (int d = 0; d < D; ++d) {
            std::vector<std::tuple<int, int, Operation>> eval_que;
            eval_que.reserve(cur_size * CONTEST_SIZE);
            for (int i = 0; i < cur_size; ++i) {
                for (int t = 0; t < CONTEST_SIZE; ++t) {
                    int eval = cur[i].next_eval(d, t);
                    eval_que.emplace_back(eval, i, Operation{d, t});
                }
            }
            if (eval_que.size() > BEAM_SIZE) {
                std::nth_element(eval_que.begin(), eval_que.begin() + BEAM_SIZE, eval_que.end(),
                                 [](auto x, auto y) { return std::get<0>(x) > std::get<0>(y); });
            }
            int nxt_size = std::min(BEAM_SIZE, (int)eval_que.size());
            for (int i = 0; i < nxt_size; ++i) {
                auto &&[eval, prev_idx, operation] = eval_que[i];
                nxt[i] = cur[prev_idx].apply(operation);
            }
            std::swap(cur, nxt);
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
        std::array<char, D> ans;
        std::array<std::vector<int>, CONTEST_SIZE> memo;

        State(const std::array<char, D> &arr) : ans(arr) {}

        auto get_score() const { return score; }

        auto get_char(int d) const { return ans[d]; }

        void build() {
            score = 0;
            int sum = 0;
            std::array<short, CONTEST_SIZE> last = {};
            for (int i = 0; i < CONTEST_SIZE; ++i) { memo[i].emplace_back(-1); }
            for (int d = 0; d < D; ++d) {
                memo[ans[d]].emplace_back(d);
                char t = ans[d];
                sum += SUM - C[t] * (d + 1 - last[t]);
                score += S[d][t] - sum;
                last[t] = d + 1;
            }
            for (int i = 0; i < CONTEST_SIZE; ++i) { memo[i].emplace_back(D); }
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

    lib::SA<TL> sa;
    lib::Xorshift xor128;

    int get_time() { return sa.get_time(); }

    int solve(std::array<char, D> &ans) {
        State state(ans);
        state.build();
        int max_score = state.get_score();

        int score = max_score;
        while (sa.get_time() < TL) {
            double temp = sa.temperature();
            for (int loop = 0; loop < 300; ++loop) {
                if (xor128() % 2) {
                    int d = xor128() % D;
                    char e = xor128() % CONTEST_SIZE;
                    auto p = state.update(d, e);
                    int new_score = state.get_score();
                    if (!sa.is_update(new_score - score, temp)) {
                        state.update(d, p);
                    } else {
                        score = new_score;
                    }
                } else {
                    int d1 = xor128() % (D - 1);
                    int d2 = std::min((int)(d1 + 1 + xor128() % 10), D - 1);
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

                if (chmax(max_score, score)) { ans = state.ans; }
            }
        }

        return max_score;
    }
};

int calc_score(const std::array<char, D> &ans) {
    int score = 1000000, sum = 0;
    std::array<short, CONTEST_SIZE> last{};
    for (int d = 0; d < D; ++d) {
        int t = ans[d];
        sum += SUM - C[t] * (d + 1 - last[t]);
        score += S[d][t] - sum;
        last[t] = d + 1;
    }
    return score;
}

int main(void) {
    int tmp;
    std::cin >> tmp;
    for (int i = 0; i < CONTEST_SIZE; ++i) { std::cin >> C[i]; }
    SUM = std::reduce(std::begin(C), std::end(C));
    for (int i = 0; i < D; ++i) {
        for (int j = 0; j < CONTEST_SIZE; ++j) { std::cin >> S[i][j]; }
    }

    beam_search<4000> solver1;
    annealing<1985> solver2;
    auto ans = solver1.solve();
    std::cerr << (double)clock() / CLOCKS_PER_SEC << ' ' << calc_score(ans) << std::endl;
    std::cerr << "Score = " << solver2.solve(ans) + 1000000 << std::endl;
    for (auto i : ans) std::cout << (int)i + 1 << std::endl;

    return 0;
}
