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

struct Pos {
    int y, x;

    std::pair<int, int> pair() const {
        return std::make_pair(y, x);
    }
};

struct bitset_2d {
    bitset_2d(int n) : _size(n), bits(n) {}

    bool get(int y, int x) const {
        return bits[y] >> x & 1;
    }

    bool get(const Pos& pos) const {
        return get(pos.y, pos.x);
    }

    void set(int y, int x) {
        bits[y] |= 1ul << x;
    }

    void set(const Pos& pos) {
        set(pos.y, pos.x);
    }

    void reset() {
        bits = std::vector<std::uint64_t>(_size);
    }

  private:
    int _size;
    std::vector<std::uint64_t> bits;
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

int measure(int i, int y, int x) {
    std::cout << i << " " << y << " " << x << std::endl;
    int v;
    std::cin >> v;
    if (v == -1) {
        std::cerr << "something went wrong. i=" << i << " y=" << y << " x=" << x << std::endl;
        exit(1);
    }
    return v;
}

void answer(const std::vector<int>& estimate) {
    std::cout << "-1 -1 -1" << std::endl;
    for (auto&& e : estimate) std::cout << e << std::endl;
}

}  // namespace Judge

struct Operation {
    int y, x, value;
};

struct Solver {
    const int L;
    const int N;
    const int S;
    const std::vector<Pos> landing_pos;

    Solver(int L, int N, int S, const std::vector<Pos>& landing_pos)
        : L(L), N(N), S(S), landing_pos(landing_pos) {}

    void solve();

    std::vector<int> create_landing_order() const {
        std::vector<std::pair<int, int>> values(N);
        for (int i = 0; i < N; ++i) {
            auto [y, x] = landing_pos[i].pair();
            values[i] = {std::min(abs(x - (L + 1) / 2), abs(L / 2 - x)) +
                             std::min(abs(y - (L + 1) / 2), abs(L / 2 - y)),
                         std::min(abs(x - (L + 1) / 2), abs(L / 2 - x)) -
                             std::min(abs(y - (L + 1) / 2), abs(L / 2 - y))};
        }
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

    void set_landing_temperature(std::vector<std::vector<int>>& temperature) const {
        auto values = create_landing_temperature();
        for (int i = 0; i < N; ++i) {
            auto&& pos = landing_pos[i];
            temperature[pos.y][pos.x] = values[i];
        }
    }

    Pos fix_pos(const Pos& p, const Pos& q) const {
        return Pos{(p.y >= q.y) ? (q.y - p.y + L < p.y - q.y ? q.y + L : q.y)
                                : (p.y - q.y + L < q.y - p.y ? q.y - L : q.y),
                   (p.x >= q.x) ? (q.x - p.x + L < p.x - q.x ? q.x + L : q.x)
                                : (p.x - q.x + L < q.x - p.x ? q.x - L : q.x)};
    }

    std::vector<Pos> create_fixed_pos(const std::vector<Pos>& original_pos, const Pos& p) const {
        const int n = original_pos.size();
        std::vector<Pos> fixed_pos(n);
        for (int i = 0; i < n; ++i) fixed_pos[i] = fix_pos(p, original_pos[i]);
        return fixed_pos;
    }

    std::vector<int> create_finished_order(const std::vector<Pos>& finished_pos,
                                           const Pos& pos) const {
        const int finished_size = finished_pos.size();
        std::vector<int> finished_order(finished_size);
        std::iota(finished_order.begin(), finished_order.end(), 0);
        std::vector<int> finished_dists(finished_size);
        for (int i = 0; i < finished_size; ++i) finished_dists[i] = dist(pos, finished_pos[i]);
        std::sort(finished_order.begin(), finished_order.end(), [&finished_dists](auto l, auto r) {
            return finished_dists[l] < finished_dists[r];
        });
        return finished_order;
    }

    int calculate_temperature(const std::vector<std::vector<int>>& temperature,
                              const std::vector<Pos>& finished_pos, const Pos& pos) const {
        auto&& finished_order = create_finished_order(finished_pos, pos);
        auto&& fixed_pos = create_fixed_pos(finished_pos, pos);
        std::vector<int> used_idx;
        for (int idx : finished_order) {
            bool added = true;
            for (auto i : used_idx) {
                if (dot(fixed_pos[i], pos, fixed_pos[idx]) < 0) {
                    added = false;
                    break;
                }
            }
            if (added)
                used_idx.emplace_back(idx);
        }
        double sum = 0;
        for (auto idx : used_idx) sum += 1. / dist(pos, finished_pos[idx]);
        double temp = 0;
        for (auto idx : used_idx) {
            auto q = finished_pos[idx];
            temp += (double)temperature[q.y][q.x] / dist(pos, q) / sum;
        }
        return round(temp);
    }

    std::vector<std::vector<int>> create_temperature() {
        std::vector<std::vector<int>> temperature(L, std::vector<int>(L, -1));
        set_landing_temperature(temperature);

        std::vector<std::vector<int>> dists(L, std::vector<int>(L, L * 2));
        for (int y = 0; y < L; ++y) {
            for (int x = 0; x < L; ++x) {
                for (auto&& p : landing_pos) {
                    chmin(dists[y][x], dist_abs(Pos{y, x}, p));
                }
            }
        }

        std::priority_queue<std::tuple<int, int, int>> p_que;
        for (int y = 0; y < L; ++y) {
            for (int x = 0; x < L; ++x) {
                if (dists[y][x] != 0)
                    p_que.emplace(dists[y][x], y, x);
            }
        }

        const std::array<Pos, 4> adj_pos = {Pos{1, 0}, {L - 1, 0}, {0, 1}, {0, L - 1}};
        std::vector<Pos> finished_pos = landing_pos;
        while (!p_que.empty()) {
            auto [d, y, x] = p_que.top();
            p_que.pop();
            if (dists[y][x] != d)
                continue;
            Pos cur_pos{y, x};
            temperature[y][x] = calculate_temperature(temperature, finished_pos, cur_pos);
            finished_pos.emplace_back(cur_pos);
            std::queue<Pos> que;
            bitset_2d visited(L);
            dists[y][x] = 0;
            que.emplace(cur_pos);
            visited.set(y, x);
            while (!que.empty()) {
                auto p = que.front();
                que.pop();
                for (auto adj : adj_pos) {
                    int ny = p.y + adj.y, nx = p.x + adj.x;
                    ny = (ny >= L ? ny - L : ny);
                    nx = (nx >= L ? nx - L : nx);
                    if (visited.get(ny, nx))
                        continue;
                    visited.set(ny, nx);
                    if (chmin(dists[ny][nx], dist_abs(cur_pos, {ny, nx}))) {
                        p_que.emplace(dists[ny][nx], ny, nx);
                        que.emplace(Pos{ny, nx});
                    }
                }
            }
        }

        return temperature;
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
                int measured_value = Judge::measure(i_in, dy, dx);
                measured_values[i_in].emplace_back(Operation{dy, dx, measured_value});
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

    int dist_abs(const Pos& l, const Pos& r) const {
        int dx = l.x - r.x, dy = l.y - r.y;
        dx = dx >= 0 ? std::min(dx, L - dx) : std::min(-dx, L + dx);
        dy = dy >= 0 ? std::min(dy, L - dy) : std::min(-dy, L + dy);
        return dx + dy;
    }

    int dot(const Pos& a, const Pos& b, const Pos& c) const {
        return (b.x - a.x) * (c.x - a.x) + (b.y - a.y) * (c.y - a.y);
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
            int measured_value = Judge::measure(i_in, movement.y, movement.x);
            measured_values[i_in].emplace_back(Operation{movement.y, movement.x, measured_value});
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
            int measured_value = Judge::measure(i_in, movement.y, movement.x);
            measured_values[i_in].emplace_back(Operation{movement.y, movement.x, measured_value});
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
            int measured_value = Judge::measure(i_in, movement.y, movement.x);
            measured_values[i_in].emplace_back(Operation{movement.y, movement.x, measured_value});
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

int main(void) {
    int L, N, S;  // 10 <= L <= 50, 60 <= N <= 100
    std::cin >> L >> N >> S;
    std::vector<Pos> landing_pos(N);
    for (int i = 0; i < N; i++) std::cin >> landing_pos[i].y >> landing_pos[i].x;
    Solver solver(L, N, S, landing_pos);
    solver.solve();
    std::cerr << "N = " << N << ", L = " << L << ", S = " << S
              << ", Time = " << (double)clock() / CLOCKS_PER_SEC << std::endl;

    return 0;
}
