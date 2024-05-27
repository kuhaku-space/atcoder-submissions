#include <algorithm>
#include <array>
#include <bit>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <numeric>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <utility>
#include <vector>

constexpr int N = 5;

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

    Position next() const {
        Position res = *this;
        if (x == N-3){
            res.x=0;
            if (y == N-3){
                res = Position(-1,-1);
            } else {
                ++res.y;
            }
        } else {
            ++res.x;
        }
        return res;
    }
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

string move(int s, int g) {
    string res;
    res += 'P';
    res += string(N - 1, 'R');
    if (s < g) {
        res += string(g - s, 'D');
    } else if (s > g) {
        res += string(s - g, 'U');
    }
    res += 'Q';
    if (s < g) {
        res += string(g - s, 'U');
    } else if (s > g) {
        res += string(s - g, 'D');
    }
    res += string(N - 1, 'L');
    return res;
}

int main(void) {
    int tmp;
    cin >> tmp;

    array<array<int, N>, N> containers;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> containers[i][j];
        }
    }

    array<string, N> answer;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int x = containers[i][j] / N;
            string s = move(i, x);
            for (int k = 0; k < N; ++k) {
                if (k == i) answer[k] += s;
                else answer[k] += string(s.size(), '.');
            }
        }
    }

    for (int i = 0; i < N; ++i) answer[i] += 'B';
    for (int i = 0; i < N; ++i) cout << answer[i] << endl;

    return 0;
}
