#pragma once
#ifdef ATCODER
#pragma GCC target("sse4.2,avx512f,avx512dq,avx512ifma,avx512cd,avx512bw,avx512vl,bmi2")
#endif
#pragma GCC optimize("Ofast,fast-math,unroll-all-loops")
#include <bits/stdc++.h>
#ifndef ATCODER
#pragma GCC target("sse4.2,avx2,bmi2")
#endif

constexpr int N = 100;
constexpr int L = 500'000;

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
    int rand_range(int a, int b) { return a + operator()() % (b - a + 1); }
    double random() { return (double)operator()() / max(); }

  private:
    state_type state;
} rnd;

struct Timer {
    std::chrono::system_clock::time_point start;

    Timer() : start(std::chrono::system_clock::now()) {}

    int64_t operator()() const { return this->get_time(); }

    int64_t get_time() const {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now() - start)
            .count();
    }

    void reset() { start = std::chrono::system_clock::now(); }
};

constexpr double T0 = 0.001, T1 = 0.00002;
template <int TL>
struct SA {
    Timer timer;
    Xorshift xor128;

    SA() : timer(), xor128() {}

    auto get_time() { return timer.get_time(); }

    double temperature(double t) {
        t /= TL;
        return std::pow(T0, 1.0 - t) * std::pow(T1, t);
    }
    double temperature() { return temperature(get_time()); }

    template <class T>
    bool is_update(T diff_score, double temp) {
        if (diff_score >= 0) return true;
        return std::exp((double)diff_score / temp) >= xor128.random();
    }
};

// clang-format on
}  // namespace lib
using namespace lib;

struct Solver {
    array<int, N> t;
    array<double, N> sorted_probability;

    void input() {
        int tmp;
        cin >> tmp >> tmp;
        for (int i = 0; i < N; ++i) {
            cin >> t[i];
            sorted_probability[i] = (double)t[i] / L;
        }
        sort(sorted_probability.begin(), sorted_probability.end());
    }

    array<double, N> update_probability(array<double, N> probability,
                                        const array<pair<int, int>, N> &transition) {
        array<double, N> next_probability;
        for (int loop = 0; loop < 20; ++loop) {
            next_probability.fill(0);
            for (int i = 0; i < N; ++i) {
                next_probability[transition[i].first] += probability[i] / 2;
                next_probability[transition[i].second] += probability[i] / 2;
            }
            probability = next_probability;
        }
        return probability;
    }

    double eval(array<double, N> probability) {
        sort(probability.begin(), probability.end());
        double diff = 0;
        for (int i = 0; i < N; ++i) diff += abs(probability[i] - sorted_probability[i]);
        return diff;
    }

    array<int, N> simulate(const array<pair<int, int>, N> &transition) {
        bitset<N> flag;
        int x = 0;
        array<int, N> cnt = {};
        for (int i = 0; i < L; ++i) {
            ++cnt[x];
            flag.flip(x);
            if (flag[x]) x = transition[x].first;
            else x = transition[x].second;
        }
        return cnt;
    }

    array<pair<int, int>, N> answer(const array<pair<int, int>, N> &transition) {
        array<int, N> cnt = simulate(transition);
        array<int, N> ord_t, ord_c, inv_c;
        iota(ord_t.begin(), ord_t.end(), 0);
        sort(ord_t.begin(), ord_t.end(), [&](int x, int y) { return t[x] > t[y]; });
        iota(ord_c.begin(), ord_c.end(), 0);
        sort(ord_c.begin(), ord_c.end(), [&](int x, int y) { return cnt[x] > cnt[y]; });
        for (int i = 0; i < N; ++i) inv_c[ord_c[i]] = i;
        array<pair<int, int>, N> result;
        for (int i = 0; i < N; ++i) {
            result[ord_t[i]].first = ord_t[inv_c[transition[ord_c[i]].first]];
            result[ord_t[i]].second = ord_t[inv_c[transition[ord_c[i]].second]];
        }
        return result;
    }

    array<pair<int, int>, N> solve() {
        array<pair<int, int>, N> transition;
        for (int i = 0; i < N; ++i) {
            int r = rnd() % 10 + 1;
            int t = i - r;
            if (t < 0) t += N;
            transition[i].first = t;
            if (i < N - 1) transition[i].second = i + 1;
            else transition[i].second = 0;
        }
        array<int, N> cnt = simulate(transition);
        array<double, N> probability, next_probability;
        for (int i = 0; i < N; ++i) probability[i] = (double)cnt[i] / L;
        probability = update_probability(probability, transition);
        double diff = eval(probability);
        SA<1900> sa;
        double temp = sa.temperature();
        int loop = 0;
        while ((double)clock() / CLOCKS_PER_SEC < 1.9) {
            ++loop;
            int r = rnd() % N;
            int x = r - rnd() % 50 - 1;
            if (x < 0) x += N;
            int y = transition[r].first;
            transition[r].first = x;
            next_probability = update_probability(probability, transition);
            double next_diff = eval(next_probability);
            if (sa.is_update<double>(diff - next_diff, temp)) {
                diff = next_diff;
                probability = next_probability;
            } else {
                transition[r].first = y;
            }
            if ((loop & 127) == 0) temp = sa.temperature();
        }
        return answer(transition);
    }
};

int main(void) {
    Solver solver;
    solver.input();
    auto answer = solver.solve();
    for (int i = 0; i < N; ++i) {
        cout << answer[i].first << ' ' << answer[i].second << endl;
    }

    return 0;
}
