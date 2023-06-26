#ifndef LOCAL
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#endif

#include <array>
#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>

using ll = std::int64_t;
#define FOR(i, m, n) for (int i = (m); i < (n); ++i)
#define rep(i, n) FOR (i, 0, n)
template <class T, class U>
constexpr bool chmax(T &a, const U &b) noexcept {
    return a < (T)b ? a = b, true : false;
}
template <class T, class U>
constexpr bool chmin(T &a, const U &b) noexcept {
    return (T)b < a ? a = b, true : false;
}
constexpr int Inf = 1000000003;
constexpr std::int64_t INF = 1000000000000000003;

constexpr int N = 30;
constexpr int BALL_NUM = 465;
constexpr int FIELD_SIZE = 900;

struct Position {
    int x, y;

    constexpr Position() : x(), y() {}
    constexpr Position(int t) : x(t / N), y(t % N) {}
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

    friend std::ostream &operator<<(std::ostream &os, const Position &rhs) {
        return os << rhs.x << ' ' << rhs.y;
    }

    constexpr Position upper_left() const {
        return *this + Position{-1, -1};
    }
    constexpr Position upper_right() const {
        return *this + Position{-1, 0};
    }

    constexpr bool in_field() const {
        return 0 <= x && x < N && 0 <= y && y < N;
    }

    constexpr int to_line() const {
        return x * N + y;
    }
};

std::array<Position, 2> upper_direction = {Position{-1, -1}, {-1, 0}};

struct Operation {
    int l, r;

    constexpr Operation() : l(), r() {}
    constexpr Operation(int _l, int _r) : l(_l), r(_r) {}
    constexpr Operation(Position p, Position q) : l(p.to_line()), r(q.to_line()) {}
};

struct Solver {
    struct State {
        State() : field{}, ball_pos{}, operations() {}

        void input() {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < i + 1; j++) {
                    std::cin >> field[i * N + j];
                    ball_pos[field[i * N + j]] = i * N + j;
                }
            }
        }

        auto answer() const {
            return operations;
        }

        bool can_swap(Position lower, Position upper) {
            return lower.in_field() && upper.in_field() &&
                   field[lower.to_line()] < field[upper.to_line()];
        }

        bool can_move(int ball_num) {
            auto p = Position(ball_pos[ball_num]);
            return can_swap(p, p.upper_left()) || can_swap(p, p.upper_right());
        }

        void move(int ball_num) {
            while (can_move(ball_num)) {
                auto p = Position(ball_pos[ball_num]);
                auto left = p.upper_left(), right = p.upper_right();
                if (!can_swap(p, left)) {
                    apply(Operation(p, right));
                } else if (!can_swap(p, right)) {
                    apply(Operation(p, left));
                } else {
                    int lvalue = field[left.to_line()], rvalue = field[right.to_line()];
                    if (lvalue > rvalue) apply(Operation(p, left));
                    else apply(Operation(p, right));
                }
            }
        }

        void apply(Operation operation) {
            operations.emplace_back(operation);
            auto l = field[operation.l], r = field[operation.r];
            std::swap(field[operation.l], field[operation.r]);
            std::swap(ball_pos[l], ball_pos[r]);
        }

      private:
        std::array<int, FIELD_SIZE> field;
        std::array<int, BALL_NUM> ball_pos;
        std::vector<Operation> operations;
    };

    auto solve() {
        State state;
        state.input();

        for (int ball_num = 0; ball_num < BALL_NUM; ball_num++) {
            state.move(ball_num);
        }

        return state.answer();
    }
};

int main(void) {
    Solver solver;
    auto operations = solver.solve();
    std::cout << operations.size() << std::endl;
    for (auto operation : operations) {
        auto p = Position(operation.l), q = Position(operation.r);
        std::cout << p << ' ' << q << std::endl;
    }

    return 0;
}
