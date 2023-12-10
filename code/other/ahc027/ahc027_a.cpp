#ifndef LOCAL
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#endif

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <iostream>
#include <numeric>
#include <queue>
#include <random>
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
};

}  // namespace lib

// 汚れやすい床と汚れにくい床に分類する
// 汚れにくい床をいくつかのグループに分割する
// 各グループについてすべての床を通る経路を探索する
// 全グループの始点と終点を結ぶような経路を探索する
// グループ間の経路を探索する

struct Field {
    const int N;
    std::vector<std::array<int, 4>> adj_idx;
    const std::vector<std::vector<int>> &D;

    Field(int n, const std::vector<std::string> &h, const std::vector<std::string> &v,
          const std::vector<std::vector<int>> &d)
        : N(n), adj_idx(n * n), D(d) {
        for (int x = 0; x < N; ++x) {
            for (int y = 0; y < N; ++y) {
                int idx = to_line(x, y);
                adj_idx[idx][0] = (in_field(x + 1, y) && h[x][y] == '0') ? to_line(x + 1, y) : -1;
                adj_idx[idx][1] = (in_field(x, y + 1) && v[x][y] == '0') ? to_line(x, y + 1) : -1;
                adj_idx[idx][2] =
                    (in_field(x - 1, y) && h[x - 1][y] == '0') ? to_line(x - 1, y) : -1;
                adj_idx[idx][3] =
                    (in_field(x, y - 1) && v[x][y - 1] == '0') ? to_line(x, y - 1) : -1;
            }
        }
    }

    bool in_field(int x, int y) const { return 0 <= x && x < N && 0 <= y && y < N; }

    int to_line(int x, int y) const { return x * N + y; }
};

struct Solver {
    const Field &field;

    Solver(const Field &f) : field(f) {}

    std::string solve() const {
        std::string res;
        std::string op = "DRUL";
        std::vector<bool> visited(field.N * field.N);
        auto dfs = [&](auto self, int idx) -> void {
            visited[idx] = true;
            for (int i = 0; i < 4; ++i) {
                int nxt = field.adj_idx[idx][i];
                if (nxt != -1 && !visited[nxt]) {
                    res += op[i];
                    self(self, nxt);
                    res += op[(i + 2) % 4];
                }
            }
        };
        dfs(dfs, 0);
        return res;
    }
};

int main(void) {
    int N;
    std::cin >> N;
    std::vector<std::string> H(N - 1);
    for (auto &s : H) std::cin >> s;
    std::vector<std::string> V(N);
    for (auto &s : V) std::cin >> s;
    std::vector D(N, std::vector(N, 0));
    for (auto &v : D) {
        for (auto &e : v) std::cin >> e;
    }
    Field field(N, H, V, D);
    Solver solver(field);
    std::cout << solver.solve() << std::endl;

    return 0;
}
