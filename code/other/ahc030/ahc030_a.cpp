#include <algorithm>
#include <array>
#include <bit>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>

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

struct OilField {
    int d, max_x, max_y;
    vector<Position> oil_coordinates;

    bool contains(const Position &target, const Position &shift) const {
        return binary_search(oil_coordinates.begin(), oil_coordinates.end(), target - shift);
    }

    friend std::istream &operator>>(std::istream &is, OilField &rhs) {
        is >> rhs.d;
        rhs.max_x = rhs.max_y = 0;
        rhs.oil_coordinates.resize(rhs.d);
        for (auto &p : rhs.oil_coordinates) {
            is >> p.x >> p.y;
            chmax(rhs.max_x, p.x);
            chmax(rhs.max_y, p.y);
        }
        sort(rhs.oil_coordinates.begin(), rhs.oil_coordinates.end());
        return is;
    }
};

struct Field {
    const int N, M;
    const double EPS;
    const vector<OilField> &oil_fields;

    Field(int n, int m, double eps, const vector<OilField> &oil_fields)
        : N(n), M(m), EPS(eps), oil_fields(oil_fields) {}

    constexpr bool in_field(int x, int y) const {
        return 0 <= x && x < N && 0 <= y && y < N;
    }
};

struct Query {
    vector<pair<vector<Position>, int>> responses;

    Query() {}

    int operator()(const vector<Position> &positions) {
        cout << "q " << positions.size();
        for (const Position &pos : positions) cout << ' ' << pos.x << ' ' << pos.y;
        cout << endl;
        int result;
        cin >> result;
        responses.emplace_back(positions, result);
        return result;
    }
};

struct Answer {
    vector<pair<vector<Position>, int>> responses;
    int operator()(const vector<Position> &positions) {
        cout << "a " << positions.size();
        for (const Position &pos : positions) cout << ' ' << pos.x << ' ' << pos.y;
        cout << endl;
        int result;
        cin >> result;
        responses.emplace_back(positions, result);
        return result;
    }
};

struct Predictor {
    const Field &field;
    vector<vector<int>> board;
    Query local_query;
    Answer local_answer;
    vector<vector<Position>> shift_candidate;

    Predictor(const Field &field)
        : field(field), board(field.N, vector(field.N, -1)), local_query(), local_answer(),
          shift_candidate(field.M) {
        for (int id = 0; id < field.M; ++id) {
            for (int x = 0; x < field.N - field.oil_fields[id].max_x; ++x) {
                for (int y = 0; y < field.N - field.oil_fields[id].max_y; ++y) {
                    shift_candidate[id].emplace_back(x, y);
                }
            }
        }
    }

    void comment() {
        cout << "#";
        for (int id = 0; id < field.M; ++id) {
            cout << ' ' << shift_candidate[id].size();
        }
        cout << endl;
        cout << "# " << calc_candidate_limit(1000000000000000) << endl;
    }

    bool is_determined_position(int id) const {
        return shift_candidate[id].size() == 1;
    }

    bool is_predicted_completely() const {
        for (int id = 0; id < field.M; ++id) {
            if (shift_candidate[id].size() != 1) return false;
        }
        return true;
    }

    vector<vector<int>> get_board() const {
        return board;
    }

    vector<vector<int>> get_undefined_board() const {
        auto copy_board = board;
        for (int id = 0; id < field.M; ++id) {
            if (is_determined_position(id)) {
                Position shift = shift_candidate[id].front();
                for (Position p : field.oil_fields[id].oil_coordinates) {
                    Position pos = p + shift;
                    if (copy_board[pos.x][pos.y] > 0) --copy_board[pos.x][pos.y];
                }
            }
        }
        return copy_board;
    }

    void set_shift_candidate(const vector<Position> &shifts) {
        for (int id = 0; id < field.M; ++id) {
            shift_candidate[id].clear();
            shift_candidate[id].emplace_back(shifts[id]);
        }
    }

    void update_board(Position target, int result) {
        board[target.x][target.y] = result;
    }

    void update_shift_candidate() {
        auto copy_board = get_undefined_board();
        vector candidate_list(field.N, vector(field.N, 0u));
        for (int id = 0; id < field.M; ++id) {
            if (is_determined_position(id)) continue;
            for (auto it = shift_candidate[id].begin(); it != shift_candidate[id].end();) {
                Position shift = *it;
                bool flag = true;
                for (const Position &p : field.oil_fields[id].oil_coordinates) {
                    Position pos = p + shift;
                    flag &= copy_board[pos.x][pos.y] != 0;
                }
                if (!flag) {
                    it = shift_candidate[id].erase(it);
                    continue;
                }
                for (const Position &p : field.oil_fields[id].oil_coordinates) {
                    Position pos = p + shift;
                    candidate_list[pos.x][pos.y] |= 1 << id;
                }
                ++it;
            }
        }

        for (int x = 0; x < field.N; ++x) {
            for (int y = 0; y < field.N; ++y) {
                Position pos(x, y);
                if (copy_board[x][y] <= 0 || popcount(candidate_list[x][y]) != copy_board[x][y])
                    continue;
                for (int id = 0; id < field.M; ++id) {
                    if (~candidate_list[x][y] >> id & 1) continue;
                    for (auto it = shift_candidate[id].begin(); it != shift_candidate[id].end();) {
                        Position shift = *it;
                        if (!field.oil_fields[id].contains(pos, shift))
                            it = shift_candidate[id].erase(it);
                        else ++it;
                    }
                }
            }
        }
        comment();
    }

    int query(const vector<Position> &positions) {
        int result = local_query(positions);
        if (positions.size() == 1) update_board(positions.front(), result);
        update_shift_candidate();
        return result;
    }

    int answer(const vector<Position> &positions) {
        int result = local_answer(positions);
        return result;
    }

    vector<Position> get_measured_oil_pos() const {
        vector<Position> oil_pos;
        for (int x = 0; x < field.N; ++x) {
            for (int y = 0; y < field.N; ++y) {
                if (board[x][y] > 0) oil_pos.emplace_back(x, y);
            }
        }
        return oil_pos;
    }

    vector<Position> get_predicted_oil_pos() const {
        assert(is_predicted_completely());
        vector predicted_board(field.N, vector(field.N, 0));
        for (int id = 0; id < field.M; ++id) {
            Position shift = shift_candidate[id].front();
            for (const Position &p : field.oil_fields[id].oil_coordinates) {
                Position pos = p + shift;
                ++predicted_board[pos.x][pos.y];
            }
        }
        vector<Position> oil_pos;
        for (int x = 0; x < field.N; ++x) {
            for (int y = 0; y < field.N; ++y) {
                if (predicted_board[x][y]) oil_pos.emplace_back(x, y);
            }
        }
        return oil_pos;
    }

    vector<vector<Position>> create_candidate() const {
        auto copy_board = get_undefined_board();
        vector<vector<Position>> candidate;
        vector<Position> shifts;
        auto dfs = [&](auto self, int id) {
            if (id == field.M) {
                for (int x = 0; x < field.N; ++x) {
                    for (int y = 0; y < field.N; ++y) {
                        if (copy_board[x][y] > 0) return;
                    }
                }
                candidate.emplace_back(shifts);
                return;
            }
            if (is_determined_position(id)) {
                shifts.emplace_back(shift_candidate[id].front());
                self(self, id + 1);
                shifts.pop_back();
                return;
            }
            for (const Position &shift : shift_candidate[id]) {
                bool flag = true;
                for (Position p : field.oil_fields[id].oil_coordinates) {
                    Position pos = p + shift;
                    if (copy_board[pos.x][pos.y] == 0) {
                        flag = false;
                        break;
                    }
                }
                if (!flag) continue;
                for (Position p : field.oil_fields[id].oil_coordinates) {
                    Position pos = p + shift;
                    if (copy_board[pos.x][pos.y] != -1) --copy_board[pos.x][pos.y];
                }
                shifts.emplace_back(shift);
                self(self, id + 1);
                for (Position p : field.oil_fields[id].oil_coordinates) {
                    Position pos = p + shift;
                    if (copy_board[pos.x][pos.y] != -1) ++copy_board[pos.x][pos.y];
                }
                shifts.pop_back();
            }
        };
        dfs(dfs, 0);
        return candidate;
    }

    int count_candidate(int limit) const {
        auto copy_board = get_undefined_board();
        int res = 0;
        auto dfs = [&](auto self, int id) {
            if (res >= limit) return;
            if (id == field.M) {
                for (int x = 0; x < field.N; ++x) {
                    for (int y = 0; y < field.N; ++y) {
                        if (copy_board[x][y] > 0) return;
                    }
                }
                ++res;
                return;
            }
            if (shift_candidate[id].size() == 1) {
                self(self, id + 1);
                return;
            }
            for (const Position &shift : shift_candidate[id]) {
                if (res >= limit) break;
                bool flag = true;
                for (Position p : field.oil_fields[id].oil_coordinates) {
                    Position pos = p + shift;
                    if (copy_board[pos.x][pos.y] == 0) {
                        flag = false;
                        break;
                    }
                }
                if (!flag) continue;
                for (Position p : field.oil_fields[id].oil_coordinates) {
                    Position pos = p + shift;
                    if (copy_board[pos.x][pos.y] != -1) --copy_board[pos.x][pos.y];
                }
                self(self, id + 1);
                for (Position p : field.oil_fields[id].oil_coordinates) {
                    Position pos = p + shift;
                    if (copy_board[pos.x][pos.y] != -1) ++copy_board[pos.x][pos.y];
                }
            }
        };
        dfs(dfs, 0);
        return res;
    }

    Position select_measure_point() const {
        vector count(field.N, vector(field.N, 0));
        for (int id = 0; id < field.M; ++id) {
            for (int x = 0; x < field.N - field.oil_fields[id].max_x; ++x) {
                for (int y = 0; y < field.N - field.oil_fields[id].max_y; ++y) {
                    Position shift(x, y);
                    bool flag = true;
                    for (const Position &p : field.oil_fields[id].oil_coordinates) {
                        Position pos = p + shift;
                        flag &= board[pos.x][pos.y] != 0;
                    }
                    if (!flag) continue;
                    for (const Position &p : field.oil_fields[id].oil_coordinates) {
                        Position pos = p + shift;
                        ++count[pos.x][pos.y];
                    }
                }
            }
        }

        int max_eval = 0;
        Position res(-1, -1);
        for (int x = 0; x < field.N; ++x) {
            for (int y = 0; y < field.N; ++y) {
                if (board[x][y] != -1) continue;
                if (chmax(max_eval, count[x][y])) {
                    res = Position(x, y);
                }
            }
        }
        return res;
    }

    Position select_measure_point_from_candidate(const vector<Position> &candidate) const {
        vector count(field.N, vector(field.N, 0));
        for (int id = 0; id < field.M; ++id) {
            for (int x = 0; x < field.N - field.oil_fields[id].max_x; ++x) {
                for (int y = 0; y < field.N - field.oil_fields[id].max_y; ++y) {
                    Position shift(x, y);
                    bool flag = true;
                    for (const Position &p : field.oil_fields[id].oil_coordinates) {
                        Position pos = p + shift;
                        flag &= board[pos.x][pos.y] != 0;
                    }
                    if (!flag) continue;
                    for (const Position &p : field.oil_fields[id].oil_coordinates) {
                        Position pos = p + shift;
                        ++count[pos.x][pos.y];
                    }
                }
            }
        }

        int max_eval = 0;
        Position res(-1, -1);
        for (const Position &pos : candidate) {
            if (board[pos.x][pos.y] != -1) continue;
            if (chmax(max_eval, count[pos.x][pos.y])) {
                res = pos;
            }
        }
        return res;
    }

    int64_t calc_candidate_limit(int64_t limit) {
        int64_t res = 1;
        for (int id = 0; id < field.M; ++id) {
            res *= shift_candidate[id].size();
            if (res >= limit) return limit;
        }
        return res;
    }
};

struct State {
    vector<Position> shifts;
    int oil_reserves;
    double log_likelihood;
    double likelihood;

    State() = default;

    constexpr bool operator<(const State &rhs) const {
        return log_likelihood < rhs.log_likelihood;
    }
    constexpr bool operator>(const State &rhs) const {
        return rhs < *this;
    }
};

struct Solver {
    const Field &field;
    Predictor predictor;

    Solver(const Field &field) : field(field), predictor(field) {}

    int64_t calc_eval(const vector<vector<pair<Position, Position>>> &v) {
        return v[0].size() * v[0].size() + v[1].size() * v[1].size() + v[2].size() * v[2].size();
    }

    int64_t calc_eval(const vector<vector<vector<Position>>> &v) {
        int64_t res = 0;
        for (const auto &e : v) res += e.size() * e.size();
        return res;
    }

    vector<pair<Position, Position>> create_full_candidate() {
        vector<pair<Position, Position>> candidate;
        for (const Position &shift0 : predictor.shift_candidate[0]) {
            for (const Position &shift1 : predictor.shift_candidate[1]) {
                candidate.emplace_back(shift0, shift1);
            }
        }
        return candidate;
    }

    vector<vector<Position>> create_candidate_list() {
        vector<vector<Position>> candidate;
        for (const Position &shift0 : predictor.shift_candidate[0]) {
            for (const Position &shift1 : predictor.shift_candidate[1]) {
                candidate.emplace_back(vector<Position>{shift0, shift1});
            }
        }
        return candidate;
    }

    vector<Position> decide_shifts_by_decision_tree() {
        auto candidate = predictor.create_candidate();
        while (candidate.size() > 1) {
            vector dp(field.N, vector(field.N, vector(field.M + 1, vector<vector<Position>>())));
            for (int x = 0; x < field.N; ++x) {
                for (int y = 0; y < field.N; ++y) {
                    for (const auto &v : candidate) {
                        Position pos(x, y);
                        int s = 0;
                        for (int id = 0; id < field.M; ++id) {
                            Position p = pos - v[id];
                            s += binary_search(field.oil_fields[id].oil_coordinates.begin(),
                                               field.oil_fields[id].oil_coordinates.end(), p);
                        }
                        dp[x][y][s].emplace_back(v);
                    }
                }
            }
            Position pos;
            int64_t min_eval = inf;
            for (int x = 0; x < field.N; ++x) {
                for (int y = 0; y < field.N; ++y) {
                    if (chmin(min_eval, calc_eval(dp[x][y]))) pos = {x, y};
                }
            }
            assert(min_eval >= 0);
            if (min_eval == int64_t(candidate.size() * candidate.size())) break;
            candidate = dp[pos.x][pos.y][predictor.query({pos})];
        }
        return candidate.front();
    }

    bool solve_search_tree() {
        vector dp(field.M, vector(field.N, vector(field.N, vector(field.N, vector(field.N, 0)))));
        for (int id = 0; id < field.M; ++id) {
            for (const Position &shift : predictor.shift_candidate[id]) {
                for (Position p : field.oil_fields[id].oil_coordinates) {
                    Position pos = p + shift;
                    dp[id][shift.x][shift.y][pos.x][pos.y] = 1;
                }
            }
        }

        vector<pair<Position, Position>> candidate = create_full_candidate();

        while (candidate.size() > 1) {
            vector v(field.N, vector(field.N, vector(3, vector<pair<Position, Position>>())));
            for (int x = 0; x < field.N; ++x) {
                for (int y = 0; y < field.N; ++y) {
                    for (auto [p1, p2] : candidate) {
                        int s = dp[0][p1.x][p1.y][x][y] + dp[1][p2.x][p2.y][x][y];
                        v[x][y][s].emplace_back(p1, p2);
                    }
                }
            }

            Position pos;
            int min_eval = inf;
            for (int x = 0; x < field.N; ++x) {
                for (int y = 0; y < field.N; ++y) {
                    if (chmin(min_eval, calc_eval(v[x][y]))) pos = {x, y};
                }
            }
            int s = predictor.query({pos});
            candidate = v[pos.x][pos.y][s];
        }

        vector<Position> oil_pos;
        for (int x = 0; x < field.N; ++x) {
            for (int y = 0; y < field.N; ++y) {
                for (auto [p1, p2] : candidate) {
                    int s = dp[0][p1.x][p1.y][x][y] + dp[1][p2.x][p2.y][x][y];
                    if (s) oil_pos.emplace_back(x, y);
                }
            }
        }
        int ans = predictor.answer(oil_pos);
        return ans == 1;
    }

    bool solve_select_search() {
        Position pos = predictor.select_measure_point();
        while (pos != Position(-1, -1) && !predictor.is_predicted_completely()) {
            predictor.query({pos});
            if (predictor.calc_candidate_limit(10000000) < 10000000 &&
                predictor.count_candidate(40000) < 40000) {
                auto shifts = decide_shifts_by_decision_tree();
                predictor.set_shift_candidate(shifts);
                auto oil_pos = predictor.get_predicted_oil_pos();
                int ans = predictor.answer(oil_pos);
                return ans == 1;
            }
            pos = predictor.select_measure_point();
        }

        auto oil_pos = predictor.is_predicted_completely() ? predictor.get_predicted_oil_pos()
                                                           : predictor.get_measured_oil_pos();
        int ans = predictor.answer(oil_pos);
        return ans == 1;
    }

    double calc_mean(int v, int k) {
        return (k - v) * field.EPS + v * (1 - field.EPS);
    }

    double calc_variance(int k) {
        return k * field.EPS * (1 - field.EPS);
    }

    double calc_lower_tail_probability(double u, int v, int k) {
        if (k == 1) return u >= v;
        return (1 + std::erf((u - calc_mean(v, k)) / std::sqrt(2 * calc_variance(k))));
    }

    double calc_probability(int u, int v, int k) {
        return calc_lower_tail_probability(u + 0.5, v, k) -
               (u == 0 ? 0 : calc_lower_tail_probability(u - 0.5, v, k));
    }

    double mutual_information(const vector<State> &states, int k) {
        double res = 0;
        int n = states.size();
        for (int u = 0; u < k * 2; ++u) {
            double s = 0;
            vector<double> ps(n);
            for (int i = 0; i < n; ++i) {
                ps[i] = calc_probability(u, states[i].oil_reserves, k);
                s += ps[i] * states[i].likelihood;
            }
            double ls = log2(s);
            for (int i = 0; i < n; ++i) {
                if (ps[i] != 0) res += ps[i] * states[i].likelihood * (log2(ps[i]) - ls);
            }
            if (u >= k && s < 1e-9) break;
        }
        return res;
    }

    vector<Position> create_measured_positions(vector<State> &states) {
        double s = 0;
        double max_log = max_element(states.begin(), states.end())->log_likelihood;
        for (auto &state : states) {
            state.oil_reserves = 0;
            state.likelihood = pow(2, state.log_likelihood - max_log);
            s += state.likelihood;
        }
        for (auto &state : states) state.likelihood /= s;

        vector used(field.N, vector(field.N, 0));
        double best_mi = 0;
        int k = 0;
        for (int _ = 0; _ < 1000; ++_) {
            int x = xorshift() % field.N;
            int y = xorshift() % field.N;
            int delta = used[x][y] ? -1 : 1;
            k += delta;

            Position target(x, y);
            for (auto &state : states) {
                for (int id = 0; id < field.M; ++id) {
                    state.oil_reserves +=
                        delta * field.oil_fields[id].contains(target, state.shifts[id]);
                }
            }

            if (chmax(best_mi, mutual_information(states, k) * sqrt(k))) {
                used[x][y] += delta;
                continue;
            }

            delta *= -1;
            for (auto &state : states) {
                for (int id = 0; id < field.M; ++id) {
                    state.oil_reserves +=
                        delta * field.oil_fields[id].contains(target, state.shifts[id]);
                }
            }
        }

        vector<Position> res;
        for (int x = 0; x < field.N; ++x) {
            for (int y = 0; y < field.N; ++y) {
                if (used[x][y]) res.emplace_back(x, y);
            }
        }
        return res;
    }

    bool solve_bayesian_inference() {
        auto candidates = create_candidate_list();
        vector<State> states(candidates.size());
        for (int i = 0; i < (int)candidates.size(); ++i) {
            states[i].shifts = candidates[i];
        }
        shuffle(states.begin(), states.end(), xorshift);
        for (int loop = 0; loop < field.N * field.N; ++loop) {
            vector<State> extracted_states(states.begin(), states.begin() + 20);
            vector<Position> positions = create_measured_positions(extracted_states);

            int x = predictor.query(positions);
            for (int i = 0; i < (int)states.size(); ++i) {
                if (states[i].log_likelihood == numeric_limits<double>::lowest()) continue;
                int s = 0;
                for (const Position &pos : positions) {
                    for (int j = 0; j < field.M; ++j) {
                        s += predictor.field.oil_fields[j].contains(pos, states[i].shifts[j]);
                    }
                }
                double p = calc_probability(x, s, positions.size());
                if (p == 0) states[i].log_likelihood = numeric_limits<double>::lowest();
                else states[i].log_likelihood += log2(p);
            }

            int max_idx = max_element(states.begin(), states.end()) - states.begin();
            double sum = 0;
            for (int i = 0; i < (int)states.size(); ++i) {
                if (max_idx == i) continue;
                if (states[i].log_likelihood == numeric_limits<double>::lowest()) continue;
                sum += pow(2, states[i].log_likelihood - states[max_idx].log_likelihood);
            }
            if (sum < 0.1) {
                vector predicted_board(field.N, vector(field.N, 0));
                for (int id = 0; id < field.M; ++id) {
                    Position shift = states[max_idx].shifts[id];
                    for (const Position &p : field.oil_fields[id].oil_coordinates) {
                        Position pos = p + shift;
                        ++predicted_board[pos.x][pos.y];
                    }
                }
                vector<Position> oil_pos;
                for (int x = 0; x < field.N; ++x) {
                    for (int y = 0; y < field.N; ++y) {
                        if (predicted_board[x][y]) oil_pos.emplace_back(x, y);
                    }
                }
                if (predictor.answer(oil_pos)) return true;
            }

            sort(states.begin(), states.end(), greater<>());
        }
        return false;
    }

    void solve() {
        if (field.M == 2) {
            if (solve_bayesian_inference()) return;
            if (solve_search_tree()) return;
        }
        assert(solve_select_search());
    }
};

int main(void) {
    int n, m;
    double eps;
    cin >> n >> m >> eps;
    vector<OilField> oil_fields(m);
    for (auto &oil_field : oil_fields) cin >> oil_field;
    Field field(n, m, eps, oil_fields);
    Solver solver(field);
    solver.solve();
}
