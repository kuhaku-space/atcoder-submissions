#ifndef LOCAL
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#endif

#include <array>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;
using ll = int64_t;
#define FOR(i, m, n) for (int i = (m); i < (n); ++i)
#define rep(i, n) FOR(i, 0, n)
template <class T, class U>
constexpr bool chmax(T &a, const U &b) noexcept {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
constexpr bool chmin(T &a, const U &b) noexcept {
    return (T)b < a ? a = (T)b, true : false;
}
constexpr int Inf = 1000000003;
constexpr int64_t INF = 1000000000000000003;

constexpr int BOARD_SIZE = 30;

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

    constexpr Position operator+(const Position &rhs) const {
        return Position(*this) += rhs;
    }
    constexpr Position operator-(const Position &rhs) const {
        return Position(*this) -= rhs;
    }

    constexpr bool operator==(const Position &rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    friend ostream &operator<<(ostream &os, const Position &rhs) {
        return os << rhs.x << ' ' << rhs.y;
    }
};

array<Position, 4> adjacent = {Position{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int main(void) {
    array<array<int, BOARD_SIZE>, BOARD_SIZE> board;
    rep(i, BOARD_SIZE) {
        rep(j, BOARD_SIZE) {
            char c;
            cin >> c;
            board[i][j] = c - '0';
            assert(0 <= board[i][j] && board[i][j] <= 7);
        }
    }

    array<array<int, 4>, 4> dp = {
        array<int, 4>{7, 3, -1, 0}, {1, 6, 0, -1}, {-1, 2, 7, 1}, {2, -1, 3, 6}};
    array<array<int, 3>, 4> sxs = {array<int, 3>{6, 0, 0}, {14, 14, 7}, {21, 15, 15}, {29, 29, 22}};
    array<array<int, 3>, 4> sys = {array<int, 3>{0, 10, 20}, {9, 19, 29}, {0, 10, 20}, {9, 19, 29}};
    array<array<int, 4>, 4> gxs = {array<int, 4>{0, 0, 7}, {6, 14, 14}, {15, 15, 22}, {21, 29, 29}};
    array<array<int, 4>, 4> gys = {array<int, 4>{10, 20, 29}, {0, 9, 19}, {10, 20, 29}, {0, 9, 19}};
    array<array<int, 4>, 4> ds = {array<int, 4>{2, 1, 1}, {3, 3, 0}, {2, 1, 1}, {3, 3, 0}};

    int u, d, l, r;
    auto in_board = [&](Position pos) -> bool {
        return u <= pos.x && pos.x < d && l <= pos.y && pos.y < r;
    };
    array<array<int, BOARD_SIZE / 2>, BOARD_SIZE / 2> rotate;
    array<array<int, BOARD_SIZE / 2>, BOARD_SIZE / 2> ans;
    int max_size = 0;
    int sx, sy, gx, gy;
    auto dfs = [&](auto self, Position pos, int dir, int cnt) -> void {
        if (!in_board(pos)) {
            if (pos == Position(gx, gy) && chmax(max_size, cnt))
                ans = rotate;
            return;
        } else if (rotate[pos.x - u][pos.y - l] != -1) {
            return;
        }
        if (board[pos.x][pos.y] < 6) {
            int next_dir = (dir + 1) % 4;
            Position next_pos = pos + adjacent[next_dir];
            rotate[pos.x - u][pos.y - l] = dp[dir][next_dir];
            self(self, next_pos, next_dir, cnt + 1);
            next_dir = (dir + 3) % 4;
            next_pos = pos + adjacent[next_dir];
            rotate[pos.x - u][pos.y - l] = dp[dir][next_dir];
            self(self, next_pos, next_dir, cnt + 1);
        } else {
            int next_dir = dir;
            Position next_pos = pos + adjacent[next_dir];
            rotate[pos.x - u][pos.y - l] = dp[dir][next_dir];
            self(self, next_pos, next_dir, cnt + 1);
        }
        rotate[pos.x - u][pos.y - l] = -1;
    };

    array<array<int, BOARD_SIZE>, BOARD_SIZE> answer;
    rep(x, 4) {
        rep(y, 3) {
            sx = sxs[x][y];
            sy = sys[x][y];
            gx = gxs[x][y];
            gy = gys[x][y];
            u = BOARD_SIZE * x / 4;
            d = BOARD_SIZE * (x + 1) / 4;
            l = BOARD_SIZE * y / 3;
            r = BOARD_SIZE * (y + 1) / 3;

            max_size = 0;
            for (auto &v : rotate) v.fill(-1);
            for (auto &v : ans) v.fill(-1);
            dfs(dfs, Position(sx, sy), ds[x][y], 0);
            cerr << max_size << endl;
            rep(i, d - u) {
                rep(j, r - l) {
                    answer[u + i][l + j] = ans[i][j];
                }
            }
        }
    }

    string str;
    rep(i, BOARD_SIZE) {
        rep(j, BOARD_SIZE) {
            if (answer[i][j] == -1)
                str += '0';
            else if (answer[i][j] >= 6) {
                assert(answer[i][j] == 6 || answer[i][j] == 7);
                assert(board[i][j] == 6 || board[i][j] == 7);
                if (board[i][j] == answer[i][j])
                    str += '0';
                else
                    str += '1';
            } else {
                if (board[i][j] >= 4)
                    board[i][j] %= 2;
                str += '0' + (answer[i][j] - board[i][j] + 4) % 4;
            }
        }
    }
    cout << str << endl;
}
