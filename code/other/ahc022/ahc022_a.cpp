#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>
#include <queue>
#include <set>
#include <vector>

template <class T, class U>
bool chmax(T& a, const U b) {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
bool chmin(T& a, const U b) {
    return (T)b < a ? a = (T)b, true : false;
}

struct Xorshift {
    using state_type = std::array<std::uint32_t, 4>;
    using result_type = std::uint32_t;
    constexpr Xorshift() : state{123456789, 362436069, 521288629, 88675123} {}

    static constexpr result_type min() {
        return std::numeric_limits<result_type>::min();
    }
    static constexpr result_type max() {
        return std::numeric_limits<result_type>::max();
    }
    result_type operator()() {
        std::uint32_t t = (state[0] ^ (state[0] << 11));
        state[0] = state[1], state[1] = state[2], state[2] = state[3];
        return state[3] = (state[3] ^ (state[3] >> 19)) ^ (t ^ (t >> 8));
    }
    bool operator==(const Xorshift& rhs) noexcept {
        return (this->state == rhs.state);
    }
    bool operator!=(const Xorshift& rhs) noexcept {
        return (this->state != rhs.state);
    }

    constexpr state_type serialize() const noexcept {
        return this->state;
    }
    constexpr void deserialize(const state_type state) noexcept {
        this->state = state;
    }

    /**
     * @brief a以上b以下の整数を生成
     *
     * @param a
     * @param b
     * @return int [a, b]
     */
    int rand_range(int a, int b) {
        return a + this->operator()() % (b - a + 1);
    }

    /**
     * @brief 0.0以上1.0未満の浮動小数点数を生成
     *
     * @return double [0.0, 1.0)
     */
    double random() {
        return (double)this->operator()() / this->max();
    }

  private:
    state_type state;
} xorshift;

int L;  // 10 <= L <= 50
int N;  // 60 <= N <= 100
int S;  // 1 <= S <= 900

struct Pos {
    int y, x;

    int norm1(const Pos& p) const {
        int dy = std::abs(y - p.y), dx = std::abs(x - p.x);
        dy = std::min(dy, L - dy);
        dx = std::min(dx, L - dx);
        return dx + dy;
    }

    int norm2(const Pos& p) const {
        int dy = std::abs(y - p.y), dx = std::abs(x - p.x);
        dy = std::min(dy, L - dy);
        dx = std::min(dx, L - dx);
        return dx * dx + dy * dy;
    }

    int distance_to_center() const {
        return std::abs(x - L / 2) + std::abs(y - L / 2);
    }

    std::pair<int, int> pair() const {
        return std::make_pair(y, x);
    }
};

struct Operation {
    int y, x, value;
};

namespace Judge {

void set_temperature(const std::vector<std::vector<int>>& temperature) {
    for (const std::vector<int>& row : temperature) {
        for (int i = 0; i < (int)row.size(); i++) {
            std::cout << row[i] << (i == (int)row.size() - 1 ? "\n" : " ");
        }
    }
    std::cout.flush();
}

Operation measure(int i, int y, int x) {
    std::cout << i << " " << y << " " << x << std::endl;
    int v;
    std::cin >> v;
    if (v == -1) {
        std::cerr << "something went wrong. i=" << i << " y=" << y << " x=" << x << std::endl;
        exit(1);
    }
    return Operation{y, x, v};
}

void answer(const std::vector<int>& estimate) {
    std::cout << "-1 -1 -1" << std::endl;
    for (auto&& e : estimate) std::cout << e << std::endl;
}

}  // namespace Judge

struct Solver {
    const std::vector<Pos> landing_pos;

    Solver(const std::vector<Pos>& landing_pos) : landing_pos(landing_pos) {}

    void solve();

    std::vector<int> create_landing_order() const {
        std::vector<int> values(N);
        for (int i = 0; i < N; ++i) values[i] = landing_pos[i].distance_to_center();
        std::vector<int> ord(N);
        std::iota(ord.begin(), ord.end(), 0);
        std::sort(ord.begin(), ord.end(), [&values](auto x, auto y) {
            return values[x] > values[y];
        });
        return ord;
    }

    std::vector<int> create_temperature_value() const {
        std::vector<int> values(N);
        if (S == 900 && N < 88)
            return values;
        for (int i = 0; i < N; ++i) {
            if (S <= 4)
                values[i] = 500 - N / 2 * 3 + 3 * i;
            else if (S <= 16)
                values[i] = 500 - N / 2 * 5 + 5 * i;
            else
                values[i] = 100 + 800 * i / (N - 1);
        }
        return values;
    }

    std::vector<int> create_landing_temperature() const {
        auto&& ord = create_landing_order();
        auto&& values = create_temperature_value();
        std::vector<int> landing_temperature(N);
        for (int i = 0; i < N; ++i) landing_temperature[ord[i]] = values[i];
        return landing_temperature;
    }

    void set_landing_temperature(std::vector<std::vector<double>>& temperature) const {
        auto values = create_landing_temperature();
        for (int i = 0; i < N; ++i) {
            auto&& pos = landing_pos[i];
            temperature[pos.y][pos.x] = values[i];
        }
    }

    std::vector<std::vector<int>> create_temperature() {
        std::vector<std::vector<double>> temperature(L, std::vector<double>(L, 500));
        set_landing_temperature(temperature);
        std::set<std::pair<int, int>> st;
        for (auto&& p : landing_pos) st.emplace(p.pair());
        for (int loop = 0; loop < 20 * L; ++loop) {
            std::vector<std::vector<double>> temp = temperature;
            const std::vector<int> dx = {1, L - 1, 0, 0}, dy = {0, 0, 1, L - 1};
            for (int y = 0; y < L; ++y) {
                for (int x = 0; x < L; ++x) {
                    if (st.count({y, x}))
                        continue;
                    double sum = 0;
                    for (int k = 0; k < 4; ++k) {
                        int ny = y + dy[k], nx = x + dx[k];
                        ny = ny < L ? ny : ny - L;
                        nx = nx < L ? nx : nx - L;
                        sum += temperature[ny][nx];
                    }
                    temp[y][x] = sum / 4;
                }
            }
            temperature = temp;
        }

        std::vector<std::vector<int>> res(L, std::vector<int>(L));
        for (int y = 0; y < L; ++y) {
            for (int x = 0; x < L; ++x) {
                res[y][x] = temperature[y][x];
            }
        }
        return res;
    }

    double get_mean_squared_error(const std::vector<std::vector<int>>& temperature,
                                  const std::vector<Operation>& operations,
                                  const Pos& cur_pos) const {
        double res = 0;
        for (auto&& op : operations) {
            int y = cur_pos.y + op.y;
            int x = cur_pos.x + op.x;
            y = y < 0 ? y + L : y >= L ? y - L : y;
            x = x < 0 ? x + L : x >= L ? x - L : x;
            assert(0 <= y && y < L);
            assert(0 <= x && y < L);
            int dt = temperature[y][x] - op.value;
            res += dt * dt;
        }
        return sqrt(res / operations.size());
    }

    template <int SD = -1>
    std::vector<int> predict(const std::vector<std::vector<int>>& temperature) {
        std::vector<int> estimate(N);
        if (S == 900 && N < 88)
            return estimate;
        std::vector<int> ord(N);
        std::iota(ord.begin(), ord.end(), 0);
        std::vector<std::vector<Operation>> measured_values(N);
        int loop_cnt = 10000 / N;
        for (int loop = 0; loop < loop_cnt; loop++) {
            for (int i_in = 0; i_in < N; i_in++) {
                int max_d = 7;
                int dy = xorshift() % (max_d * 2 + 1) - max_d;
                int dx = xorshift() % (max_d * 2 + 1) - max_d;
                while (abs(dx) + abs(dy) > std::min(L / 2, max_d * 2)) {
                    dy = xorshift() % (max_d * 2 + 1) - max_d;
                    dx = xorshift() % (max_d * 2 + 1) - max_d;
                }
                measured_values[i_in].emplace_back(Judge::measure(i_in, dy, dx));
            }
            bool fin = true;
            std::vector<int> counter(N);
            for (int i = 0; i < N; ++i) {
                int min_idx = 0;
                double min_mse = std::numeric_limits<double>::max();
                for (int j = 0; j < N; ++j) {
                    if (chmin(min_mse, get_mean_squared_error(temperature, measured_values[i],
                                                              landing_pos[j])))
                        min_idx = j;
                }
                estimate[i] = min_idx;
                if (++counter[min_idx] >= 2)
                    fin = false;
            }
            if (fin)
                break;
        }
        return estimate;
    }

    int dist(const Pos& l, const Pos& r) const {
        int dx = l.x - r.x, dy = l.y - r.y;
        dx = dx >= 0 ? std::min(dx, L - dx) : std::min(-dx, L + dx);
        dy = dy >= 0 ? std::min(dy, L - dy) : std::min(-dy, L + dy);
        return dx * dx + dy * dy;
    }
};

template <>
std::vector<int> Solver::predict<1>(const std::vector<std::vector<int>>& temperature) {
    std::vector<Pos> movements(L * L + 1);
    for (int y = 0; y < L; ++y) {
        for (int x = 0; x < L; ++x) {
            movements[y * L + x] = Pos{y - L / 2, x - L / 2};
        }
    }
    std::sort(movements.begin(), movements.end(), [](auto x, auto y) {
        return abs(x.y) + abs(x.x) < abs(y.y) + abs(y.x);
    });
    std::vector<int> ord(N);
    std::iota(ord.begin(), ord.end(), 0);
    std::vector<std::vector<Operation>> measured_values(N);
    std::vector<int> estimate(N), counter(N);
    for (auto&& movement : movements) {
        for (int i_in = 0; i_in < N; i_in++) {
            if (measured_values[i_in].size() >= 2 && counter[estimate[i_in]] == 1)
                continue;
            std::cout << "# measure i=" << i_in << " y=0 x=0" << std::endl;
            measured_values[i_in].emplace_back(Judge::measure(i_in, movement.y, movement.x));
        }
        bool fin = true;
        counter = std::vector<int>(N);
        for (int i = 0; i < N; ++i) {
            int min_idx = 0;
            double min_mse = std::numeric_limits<double>::max();
            for (int j = 0; j < N; ++j) {
                if (chmin(min_mse,
                          get_mean_squared_error(temperature, measured_values[i], landing_pos[j])))
                    min_idx = j;
            }
            estimate[i] = min_idx;
            if (++counter[min_idx] >= 2)
                fin = false;
        }
        if (fin)
            break;
    }
    return estimate;
}

template <>
std::vector<int> Solver::predict<2>(const std::vector<std::vector<int>>& temperature) {
    std::vector<Pos> movements(L * L);
    for (int y = 0; y < L; ++y) {
        for (int x = 0; x < L; ++x) {
            movements[y * L + x] = Pos{y - L / 2, x - L / 2};
        }
    }
    std::sort(movements.begin(), movements.end(), [](auto x, auto y) {
        return abs(x.y) + abs(x.x) < abs(y.y) + abs(y.x);
    });
    std::shuffle(movements.begin() + 1, movements.begin() + 25, xorshift);
    std::vector<int> ord(N);
    std::iota(ord.begin(), ord.end(), 0);
    std::vector<std::vector<Operation>> measured_values(N);
    std::vector<int> estimate(N), counter(N);
    for (auto&& movement : movements) {
        for (int i_in = 0; i_in < N; i_in++) {
            if (measured_values[i_in].size() >= 5 && counter[estimate[i_in]] == 1)
                continue;
            measured_values[i_in].emplace_back(Judge::measure(i_in, movement.y, movement.x));
        }
        bool fin = true;
        counter = std::vector<int>(N);
        for (int i = 0; i < N; ++i) {
            int min_idx = 0;
            double min_mse = std::numeric_limits<double>::max();
            for (int j = 0; j < N; ++j) {
                if (chmin(min_mse,
                          get_mean_squared_error(temperature, measured_values[i], landing_pos[j])))
                    min_idx = j;
            }
            estimate[i] = min_idx;
            if (++counter[min_idx] >= 2)
                fin = false;
        }
        if (fin)
            break;
    }
    return estimate;
}

template <>
std::vector<int> Solver::predict<3>(const std::vector<std::vector<int>>& temperature) {
    std::vector<Pos> movements(L * L);
    for (int y = 0; y < L; ++y) {
        for (int x = 0; x < L; ++x) {
            movements[y * L + x] = Pos{y - L / 2, x - L / 2};
        }
    }
    std::sort(movements.begin(), movements.end(), [](auto x, auto y) {
        return abs(x.y) + abs(x.x) < abs(y.y) + abs(y.x);
    });
    std::vector<int> ord(N);
    std::iota(ord.begin(), ord.end(), 0);
    std::vector<std::vector<Operation>> measured_values(N);
    std::vector<int> estimate(N), counter(N);
    std::vector<double> mse(N);
    while (true) {
        std::vector<bool> measured(N);
        for (int i_in = 0; i_in < N; i_in++) {
            if (measured_values[i_in].size() >= (S <= 49   ? 5
                                                 : S <= 64 ? 10
                                                           : 14) &&
                counter[estimate[i_in]] == 1)
                continue;
            int r = measured_values[i_in].size() == 0
                        ? 0
                        : xorshift() % ((L / 2 * (L / 2 + 1)) * 2 + 1);
            auto movement = movements[r];
            measured_values[i_in].emplace_back(Judge::measure(i_in, movement.y, movement.x));
            measured[i_in] = true;
        }
        bool fin = true;
        counter = std::vector<int>(N);
        for (int i = 0; i < N; ++i) {
            int min_idx = 0;
            double min_mse = std::numeric_limits<double>::max();
            if (measured[i]) {
                for (int j = 0; j < N; ++j) {
                    if (chmin(min_mse, get_mean_squared_error(temperature, measured_values[i],
                                                              landing_pos[j])))
                        min_idx = j;
                }
                estimate[i] = min_idx;
                mse[i] = min_mse;
            } else {
                min_idx = estimate[i];
            }
            if (++counter[min_idx] >= 2)
                fin = false;
        }
        if (fin)
            break;
    }
    return estimate;
}

void Solver::solve() {
    const std::vector<std::vector<int>> temperature = create_temperature();
    Judge::set_temperature(temperature);
    const std::vector<int> estimate = S == 1    ? predict<1>(temperature)
                                      : S <= 9  ? predict<2>(temperature)
                                      : S <= 81 ? predict<3>(temperature)
                                                : predict(temperature);
    Judge::answer(estimate);
}

struct OnePointSolver {
    const std::vector<Pos> landing_pos;

    OnePointSolver(const std::vector<Pos>& landing_pos) : landing_pos(landing_pos) {}

    std::vector<std::vector<int>> create_temperature() const {
        std::vector<std::vector<int>> dists(L, std::vector<int>(L));
        for (auto&& pos : landing_pos) {
            for (int y = 0; y < L; ++y) {
                for (int x = 0; x < L; ++x) {
                    dists[y][x] += pos.norm2(Pos{y, x});
                }
            }
        }

        int ry = 0, rx = 0;
        int min_dist = std::numeric_limits<int>::max();
        for (int y = 0; y < L; ++y) {
            for (int x = 0; x < L; ++x) {
                if (chmin(min_dist, dists[y][x]))
                    ry = y, rx = x;
            }
        }

        std::vector<std::vector<int>> temperature(L, std::vector<int>(L));
        temperature[ry][rx] = 1000;
        return temperature;
    }

    std::vector<int> predict(const std::vector<std::vector<int>>& temperature) const {
        Pos one_point;
        for (int y = 0; y < L; ++y) {
            for (int x = 0; x < L; ++x) {
                if (temperature[y][x] == 1000)
                    one_point = Pos{y, x};
            }
        }

        std::vector<int> ord(N);
        std::iota(ord.begin(), ord.end(), 0);
        std::sort(ord.begin(), ord.end(), [&](auto l, auto r) {
            return one_point.norm1(landing_pos[l]) < one_point.norm1(landing_pos[r]);
        });

        std::vector<int> estimate(N, -1);
        std::vector<bool> finished(N);
        for (int i = 0; i < N; ++i) {
            std::vector<std::vector<Operation>> operations(N);
            for (int loop = 0; loop < 2; ++loop) {
                for (int idx : ord) {
                    if (finished[idx])
                        continue;
                    auto p = diff(one_point, landing_pos[idx]);
                    auto op = Judge::measure(i, p.y, p.x);
                    if (probability_greater_than(op.value) < 1e-9) {
                        estimate[i] = idx;
                        break;
                    }
                    operations[idx].emplace_back(op);
                }
                if (estimate[i] != -1)
                    break;
            }
            if (estimate[i] == -1) {
                double max_probability = 0;
                for (int idx = 0; idx < N; ++idx) {
                    if (finished[idx])
                        continue;
                    double p = 1;
                    for (auto op : operations[idx]) p *= probability_less_than(op.value);
                    if (chmax(max_probability, p))
                        estimate[i] = idx;
                }
                std::cerr << i << " " << max_probability << std::endl;
            }
            finished[estimate[i]] = true;
        }
        return estimate;
    }

    void solve() {
        const std::vector<std::vector<int>> temperature = create_temperature();
        Judge::set_temperature(temperature);
        const std::vector<int> estimate = predict(temperature);
        Judge::answer(estimate);
    }

    Pos diff(const Pos& p, const Pos& q) const {
        int dy = p.y - q.y, dx = p.x - q.x;
        return Pos{dy >= 0 ? (dy < L - dy ? dy : dy - L) : (-dy < L + dy ? dy : dy + L),
                   dx >= 0 ? (dx < L - dx ? dx : dx - L) : (-dx < L + dx ? dx : dx + L)};
    }

    double probability_less_than(int value, int mean = 0) const {
        if (value == 1000)
            return 1;
        return (1 + std::erf((double)(value - mean) / std::sqrt(2 * S * S))) / 2;
    }

    double probability_greater_than(int value, int mean = 0) const {
        if (value == 0)
            return 1;
        return (1 - std::erf((double)(value - mean) / std::sqrt(2 * S * S))) / 2;
    }
};

int main(void) {
    std::cin >> L >> N >> S;
    std::vector<Pos> landing_pos(N);
    for (int i = 0; i < N; i++) std::cin >> landing_pos[i].y >> landing_pos[i].x;
    Solver solver(landing_pos);
    solver.solve();
    std::cerr << "N = " << N << ", L = " << L << ", S = " << S
              << ", Time = " << (double)clock() / CLOCKS_PER_SEC << std::endl;

    return 0;
}
