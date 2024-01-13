#ifndef LOCAL
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#endif

#include <algorithm>
#include <array>
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

struct Solver {
    const Position start;
    const array<string, N> &keyboard;
    const array<string, M> &queries;

    Solver(const Position start, const array<string, N> &keyboard, const array<string, M> &queries)
        : start(start), keyboard(keyboard), queries(queries) {}

    vector<string> create_merged_queries() const {
        vector<string> merged_queries;
        for (const string &str : queries) merged_queries.emplace_back(str);
        for (int k = 4; k >= 1; --k) {
            for (int loop = 0; loop < 10; ++loop) {
                shuffle(merged_queries.begin(), merged_queries.end(), xorshift);
                unordered_map<string, vector<int>> mp;
                int n = merged_queries.size();
                for (int i = 0; i < n; ++i) {
                    if (merged_queries[i].empty()) continue;
                    string st = merged_queries[i].substr(0, k);
                    if (mp.count(st) && !mp[st].empty()) {
                        int idx = mp[st].back();
                        merged_queries[idx] += merged_queries[i].substr(k);
                        merged_queries[i] = string();
                        mp[st].pop_back();
                        string en = merged_queries[idx].substr(merged_queries[idx].size() - k);
                        mp[en].emplace_back(idx);
                    } else {
                        string en = merged_queries[i].substr(merged_queries[i].size() - k);
                        mp[en].emplace_back(i);
                    }
                }
                auto it = merged_queries.begin();
                while (it != merged_queries.end()) {
                    if (it->empty()) it = merged_queries.erase(it);
                    else ++it;
                }
            }
        }
        return merged_queries;
    }

    string create_lucky_string() const {
        auto merged_queries = create_merged_queries();
        string lucky_string;
        for (const string &str : merged_queries) lucky_string += str;
        return lucky_string;
    }

    vector<Position> create_typing_key(const string &lucky_string, int &score) const {
        array<vector<Position>, 26> key_list;
        for (int x = 0; x < N; ++x) {
            for (int y = 0; y < N; ++y) {
                int c = keyboard[x][y] - 'A';
                key_list[c].emplace_back(x, y);
            }
        }

        Trace<Position> trace;
        vector<pair<int, int>> cur(1, {0, trace.push(start, -1)});
        for (char ch : lucky_string) {
            int c = ch - 'A';
            int m1 = cur.size();
            int m2 = key_list[c].size();
            vector<pair<int, int>> nxt(m2);
            for (int j = 0; j < m2; ++j) {
                Position nxt_pos = key_list[c][j];
                int min_d = 1000000000, min_idx = -1;
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

        int min_d = 1000000000, min_idx = -1;
        for (int i = 0; i < (int)cur.size(); ++i) {
            if (chmin(min_d, cur[i].first)) min_idx = cur[i].second;
        }
        vector<Position> typing_key = trace.chain(min_idx);
        typing_key.erase(typing_key.begin());
        score = min_d + lucky_string.size();
        return typing_key;
    }

    vector<Position> create_typing_key_by_merged_queries(vector<string> merged_queries,
                                                         int &score) const {
        vector<Position> typing_key;
        int min_score = 1000000000;
        for (int loop = 0; loop < 100; ++loop) {
            shuffle(merged_queries.begin(), merged_queries.end(), xorshift);
            string lucky_string;
            for (const string &str : merged_queries) lucky_string += str;
            int score;
            auto v = create_typing_key(lucky_string, score);
            if (chmin(min_score, score)) typing_key = v;
        }
        score = min_score;
        return typing_key;
    }

    vector<Position> solve() {
        vector<Position> ans;
        int min_score = 1000000000;
        for (int loop = 0; loop < 63; ++loop) {
            auto merged_queries = create_merged_queries();
            int score;
            auto v = create_typing_key_by_merged_queries(merged_queries, score);
            if (chmin(min_score, score)) ans = v;
        }
        return ans;
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
    Solver solver(Position(sx, sy), keyboard, queries);
    auto ans = solver.solve();
    for (const Position &pos : ans) cout << pos.x << ' ' << pos.y << endl;

    return 0;
}
