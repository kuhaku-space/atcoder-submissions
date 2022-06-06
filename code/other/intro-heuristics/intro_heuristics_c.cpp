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

#include <array>
#include <chrono>
#include <cmath>
#include <iostream>
#include <queue>
#include <set>
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

template <int TL>
struct annealing {
    struct State {
        int score;
        array<int, D> ans;
        array<vector<int>, SZ> memo;

        State(const array<int, D> &arr) : ans(arr) {}

        auto get_score() const {
            return score;
        }

        auto get_char(int d) const {
            return ans[d];
        }

        void build() {
            score = 0;
            int sum = 0;
            array<int, SZ> last = {};
            rep(i, SZ) {
                memo[i].emplace_back(-1);
            }
            rep(d, D) {
                memo[ans[d]].emplace_back(d);
                char t = ans[d];
                score += S[d][t];
                sum -= C[t] * (d + 1 - last[t]);
                last[t] = d + 1;
                sum += SUM;
                score -= sum;
            }
            rep(i, SZ) {
                memo[i].emplace_back(D);
            }
        }

        auto update(int d, int e) {
            auto a = ans[d];
            if (a == e)
                return a;
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

    void solve(array<int, D> &ans) {
        State state(ans);
        state.build();
        int M;
        cin >> M;
        rep(i, M) {
            int d, e;
            cin >> d >> e;
            state.update(d - 1, e - 1);
            cout << state.get_score() << '\n';
        }
    }
};

int main(void) {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int tmp;
    cin >> tmp;
    rep(i, SZ) cin >> C[i];
    rep(i, SZ) SUM += C[i];
    rep(i, D) rep(j, SZ) cin >> S[i][j];
    array<int, D> t;
    rep(i, D) {
        int a;
        cin >> a;
        t[i] = a - 1;
    }

    annealing<1980> solver;
    solver.solve(t);

    return 0;
}
