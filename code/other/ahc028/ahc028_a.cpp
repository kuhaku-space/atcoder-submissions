#include <algorithm>
#include <array>
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

}  // namespace lib
using namespace lib;

constexpr int N = 15;
constexpr int M = 200;

Trace<int> trace;

struct Field {
    const Position start;
    const array<string, N> &keyboard;
    const array<string, M> &queries;
    array<vector<Position>, 26> key_list;

    Field(const Position start, const array<string, N> &keyboard, const array<string, M> &queries)
        : start(start), keyboard(keyboard), queries(queries) {
        build();
    }

    void build() {
        for (int x = 0; x < N; ++x) {
            for (int y = 0; y < N; ++y) {
                int c = keyboard[x][y] - 'A';
                key_list[c].emplace_back(x, y);
            }
        }
    }
};

struct Operation {
    int id;
};

struct State {
    using score_type = int;
    int trace_id;
    score_type score;
    string end;
    bitset<M> used;
    vector<pair<score_type, Position>> end_score;

    State() = default;
    State(Position start) : trace_id(-1), score(), end(), used(), end_score(1, {0, start}) {}

    score_type predict_score(const Operation &op, const Field &field) {
        int id = op.id;
        string target = field.queries[id];
        int k = 0;
        for (int l = 5; l >= 1; --l) {
            if (end.ends_with(target.substr(0, l))) {
                k = l;
                break;
            }
        }
        target = target.substr(k);
        end += target;
        if (end.size() > 5) end = end.substr(end.size() - 5, 5);
        vector<pair<score_type, Position>> cur = end_score;
        for (char ch : target) {
            int c = ch - 'A';
            int m1 = cur.size();
            int m2 = field.key_list[c].size();
            vector<pair<score_type, Position>> nxt(m2);
            for (int j = 0; j < m2; ++j) {
                Position nxt_pos = field.key_list[c][j];
                int min_d = inf;
                for (int i = 0; i < m1; ++i) {
                    Position cur_pos = cur[i].second;
                    int d = cur[i].first + cur_pos.dist(nxt_pos);
                    chmin(min_d, d);
                }
                nxt[j] = {min_d, nxt_pos};
            }
            cur = nxt;
        }
        score_type res = inf;
        for (auto [d, pos] : cur) chmin(res, d);
        return res;
    }

    void apply(const Operation &op, const Field &field) {
        int id = op.id;
        string target = field.queries[id];
        trace_id = trace.push(id, trace_id);
        used[id] = true;
        int k = 0;
        for (int l = 5; l >= 1; --l) {
            if (end.ends_with(target.substr(0, l))) {
                k = l;
                break;
            }
        }
        target = target.substr(k);
        end += target;
        if (end.size() > 5) end = end.substr(end.size() - 5, 5);
        vector<pair<score_type, Position>> cur = end_score;
        for (char ch : target) {
            int c = ch - 'A';
            int m1 = cur.size();
            int m2 = field.key_list[c].size();
            vector<pair<score_type, Position>> nxt(m2);
            for (int j = 0; j < m2; ++j) {
                Position nxt_pos = field.key_list[c][j];
                int min_d = inf;
                for (int i = 0; i < m1; ++i) {
                    Position cur_pos = cur[i].second;
                    int d = cur[i].first + cur_pos.dist(nxt_pos);
                    chmin(min_d, d);
                }
                nxt[j] = {min_d, nxt_pos};
            }
            cur = nxt;
        }
        end_score = cur;
        score = inf;
        for (auto [d, pos] : cur) chmin(score, d);
    }
};

constexpr int BEAM_SIZE = 100;

struct beam_search {
    const Field &field;

    string merge_queries(const vector<int> &query_order) {
        string typing_key;
        for (int idx : query_order) {
            string query = field.queries[idx];
            int k = 0;
            for (int l = 5; l >= 1; --l) {
                if (typing_key.ends_with(query.substr(0, l))) {
                    k = l;
                    break;
                }
            }
            typing_key += query.substr(k);
        }
        return typing_key;
    }

    vector<Position> create_moving_finger(string typing_key) {
        Trace<Position> trace;
        vector<pair<int, int>> cur(1, {0, trace.push(field.start, -1)});
        for (char ch : typing_key) {
            int c = ch - 'A';
            int m1 = cur.size();
            int m2 = field.key_list[c].size();
            vector<pair<int, int>> nxt(m2);
            for (int j = 0; j < m2; ++j) {
                Position nxt_pos = field.key_list[c][j];
                int min_d = inf, min_idx = -1;
                for (int i = 0; i < m1; ++i) {
                    auto [cur_pos, prev_idx] = trace.get(cur[i].second);
                    int cur_idx = cur[i].second;
                    int d = cur[i].first + cur_pos.dist(nxt_pos);
                    if (chmin(min_d, d)) min_idx = cur_idx;
                }
                nxt[j] = {min_d, trace.push(nxt_pos, min_idx)};
            }
            cur = nxt;
        }

        int min_score = inf, min_idx = -1;
        for (int i = 0; i < (int)cur.size(); ++i) {
            if (chmin(min_score, cur[i].first)) min_idx = cur[i].second;
        }
        vector<Position> moving_finger = trace.chain(min_idx);
        moving_finger.erase(moving_finger.begin());
        return moving_finger;
    }

    vector<int> create_query_order() {
        array<State, BEAM_SIZE> cur;
        cur[0] = State(field.start);
        int cur_size = 1;
        for (int turn = 0; turn < M; ++turn) {
            array<tuple<int, Operation, int>, BEAM_SIZE * 2 + M> nxt_score;
            int nxt_size = 0;
            for (int cur_idx = 0; cur_idx < cur_size; ++cur_idx) {
                for (int id = 0; id < M; ++id) {
                    if (cur[cur_idx].used[id]) continue;
                    Operation op(id);
                    nxt_score[nxt_size++] = {cur[cur_idx].predict_score(op, field), op, cur_idx};
                }
                if (nxt_size >= BEAM_SIZE * 2) {
                    nth_element(nxt_score.begin(), nxt_score.begin() + BEAM_SIZE,
                                nxt_score.begin() + nxt_size,
                                [](auto l, auto r) { return get<0>(l) < get<0>(r); });
                    nxt_size = BEAM_SIZE;
                }
            }
            if (nxt_size > BEAM_SIZE) {
                nth_element(nxt_score.begin(), nxt_score.begin() + BEAM_SIZE,
                            nxt_score.begin() + nxt_size,
                            [](auto l, auto r) { return get<0>(l) < get<0>(r); });
                nxt_size = BEAM_SIZE;
            }
            array<State, BEAM_SIZE> cur_copy = cur;
            for (int i = 0; i < nxt_size; ++i) {
                auto [score, op, cur_idx] = nxt_score[i];
                cur[i] = cur_copy[cur_idx];
                cur[i].apply(op, field);
            }
            cur_size = nxt_size;
        }

        int min_score = inf, ans_idx = -1;
        for (int i = 0; i < cur_size; ++i) {
            if (chmin(min_score, cur[i].score)) ans_idx = i;
        }
        vector<int> query_order = trace.chain(cur[ans_idx].trace_id);
        reverse(query_order.begin(), query_order.end());
        return query_order;
    }

    vector<Position> solve() {
        vector<int> query_order = create_query_order();
        string typing_key = merge_queries(query_order);
        return create_moving_finger(typing_key);
    }
};

int main(void) {
    int tmp;
    cin >> tmp >> tmp;
    int sx, sy;
    cin >> sx >> sy;
    array<string, N> keyboard;
    for (string &s : keyboard) cin >> s;
    array<string, M> queries;
    for (string &s : queries) cin >> s;
    Field field(Position(sx, sy), keyboard, queries);
    beam_search solver(field);
    auto ans = solver.solve();
    for (const Position &pos : ans) cout << pos.x << ' ' << pos.y << endl;

    return 0;
}
