#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <limits>
#include <numeric>
#include <random>
#include <vector>

using namespace std;
template <class T, class U>
bool chmax(T &a, const U b) {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U b) {
    return (T)b < a ? a = (T)b, true : false;
}

constexpr int N = 200;

struct Pos {
    int y, x;

    constexpr Pos() : y(-1), x(-1) {}
    constexpr Pos(int _y, int _x) : y(_y), x(_x) {}

    constexpr Pos &operator+=(const Pos &rhs) noexcept {
        this->x += rhs.x, this->y += rhs.y;
        return *this;
    }
    constexpr Pos &operator-=(const Pos &rhs) noexcept {
        this->x -= rhs.x, this->y -= rhs.y;
        return *this;
    }

    constexpr Pos operator+(const Pos &rhs) const noexcept {
        return Pos(*this) += rhs;
    }
    constexpr Pos operator-(const Pos &rhs) const noexcept {
        return Pos(*this) -= rhs;
    }
    constexpr bool operator==(const Pos &rhs) const noexcept {
        return this->x == rhs.x && this->y == rhs.y;
    }
    constexpr bool operator!=(const Pos &rhs) const noexcept {
        return !(*this == rhs);
    }

    bool in_board() {
        return 0 <= x && x < N && 0 <= y && y < N;
    }

    int dist(const Pos &pos) const {
        return abs(x - pos.x) + abs(y - pos.y);
    }
};

int dist(const Pos &lhs, const Pos &rhs) {
    return lhs.dist(rhs);
}

enum class Response { not_broken, broken, finish, invalid };

struct Field {
    int C;
    int total_cost;
    array<array<int, N>, N> is_broken;

    Field(int C) : C(C), total_cost(), is_broken{} {}

    Response query(int y, int x, int power) {
        total_cost += power + C;
        cout << y << " " << x << " " << power << endl;  // endl does flush
        int r;
        cin >> r;
        switch (r) {
            case 0:
                return Response::not_broken;
            case 1:
                is_broken[y][x] = 1;
                return Response::broken;
            case 2:
                is_broken[y][x] = 1;
                return Response::finish;
            default:
                return Response::invalid;
        }
    }
};

struct Solver {
    int C;
    Field field;
    vector<Pos> source_pos;
    vector<Pos> house_pos;

    Solver(int C, const vector<Pos> &source_pos, const vector<Pos> &house_pos)
        : C(C), field(C), source_pos(source_pos), house_pos(house_pos) {}

    void solve() {
        vector<int> x_pos, y_pos;
        for (auto source : source_pos) {
            x_pos.emplace_back(source.x);
            y_pos.emplace_back(source.y);
        }
        for (auto house : house_pos) {
            x_pos.emplace_back(house.x);
            y_pos.emplace_back(house.y);
        }

        sort(x_pos.begin(), x_pos.end());
        x_pos.erase(unique(x_pos.begin(), x_pos.end()), x_pos.end());
        sort(y_pos.begin(), y_pos.end());
        y_pos.erase(unique(y_pos.begin(), y_pos.end()), y_pos.end());

        vector<vector<Pos>> board =
            (house_pos.size() < 10 ? find_exact_solution() : find_approximate_solution());

        // from each house, go straight to the first source
        for (Pos house : house_pos) {
            int x_start = lower_bound(x_pos.begin(), x_pos.end(), house.x) - x_pos.begin();
            int y_start = lower_bound(y_pos.begin(), y_pos.end(), house.y) - y_pos.begin();
            while (board[y_start][x_start] != Pos()) {
                auto p = board[y_start][x_start];
                int x_next = p.x, y_next = p.y;
                move(Pos(y_pos[y_start], x_pos[x_start]), Pos(y_pos[y_next], x_pos[x_next]));
                x_start = x_next, y_start = y_next;
            }
        }

        // should receive Response::finish and exit before entering here
        assert(false);
    }

    vector<vector<Pos>> find_exact_solution() {
        vector<int> x_pos, y_pos;
        for (auto source : source_pos) {
            x_pos.emplace_back(source.x);
            y_pos.emplace_back(source.y);
        }
        for (auto house : house_pos) {
            x_pos.emplace_back(house.x);
            y_pos.emplace_back(house.y);
        }

        sort(x_pos.begin(), x_pos.end());
        x_pos.erase(unique(x_pos.begin(), x_pos.end()), x_pos.end());
        sort(y_pos.begin(), y_pos.end());
        y_pos.erase(unique(y_pos.begin(), y_pos.end()), y_pos.end());

        vector<int> house_index(house_pos.size());
        iota(house_index.begin(), house_index.end(), 0);

        int min_score = numeric_limits<int>::max();
        vector<vector<Pos>> min_board;
        do {
            int x_size = x_pos.size();
            int y_size = y_pos.size();
            vector<vector<Pos>> board(y_size, vector<Pos>(x_size));
            vector<Pos> candidate_pos = source_pos;
            int score = 0;
            for (auto index : house_index) {
                auto house = house_pos[index];
                int x_start = lower_bound(x_pos.begin(), x_pos.end(), house.x) - x_pos.begin();
                int y_start = lower_bound(y_pos.begin(), y_pos.end(), house.y) - y_pos.begin();
                Pos goal = candidate_pos[0];
                for (auto candidate : candidate_pos) {
                    if (house.dist(candidate) < house.dist(goal)) {
                        goal = candidate;
                    }
                }
                score += house.dist(goal);
                int x_goal = lower_bound(x_pos.begin(), x_pos.end(), goal.x) - x_pos.begin();
                int y_goal = lower_bound(y_pos.begin(), y_pos.end(), goal.y) - y_pos.begin();
                while (x_start != x_goal) {
                    candidate_pos.emplace_back(y_pos[y_start], x_pos[x_start]);
                    int x_next = (x_start < x_goal ? x_start + 1 : x_start - 1);
                    board[y_start][x_start] = Pos(y_start, x_next);
                    x_start = x_next;
                }
                while (y_start != y_goal) {
                    candidate_pos.emplace_back(y_pos[y_start], x_pos[x_start]);
                    int y_next = (y_start < y_goal ? y_start + 1 : y_start - 1);
                    board[y_start][x_start] = Pos(y_next, x_start);
                    y_start = y_next;
                }
            }
            if (chmin(min_score, score))
                min_board = board;
        } while (next_permutation(house_index.begin(), house_index.end()));

        return min_board;
    }

    vector<vector<Pos>> find_approximate_solution() {
        vector<int> x_pos, y_pos;
        for (auto source : source_pos) {
            x_pos.emplace_back(source.x);
            y_pos.emplace_back(source.y);
        }
        for (auto house : house_pos) {
            x_pos.emplace_back(house.x);
            y_pos.emplace_back(house.y);
        }

        sort(x_pos.begin(), x_pos.end());
        x_pos.erase(unique(x_pos.begin(), x_pos.end()), x_pos.end());
        sort(y_pos.begin(), y_pos.end());
        y_pos.erase(unique(y_pos.begin(), y_pos.end()), y_pos.end());

        mt19937 rnd;
        vector<int> house_index(house_pos.size());
        iota(house_index.begin(), house_index.end(), 0);

        int min_score = numeric_limits<int>::max();
        vector<vector<Pos>> min_board;
        while ((double)clock() / CLOCKS_PER_SEC < 4) {
            shuffle(house_index.begin(), house_index.end(), rnd);
            int x_size = x_pos.size();
            int y_size = y_pos.size();
            vector<vector<Pos>> board(y_size, vector<Pos>(x_size));
            vector<Pos> candidate_pos = source_pos;
            int score = 0;
            for (auto index : house_index) {
                auto house = house_pos[index];
                int x_start = lower_bound(x_pos.begin(), x_pos.end(), house.x) - x_pos.begin();
                int y_start = lower_bound(y_pos.begin(), y_pos.end(), house.y) - y_pos.begin();
                Pos goal = candidate_pos[0];
                for (auto candidate : candidate_pos) {
                    if (house.dist(candidate) < house.dist(goal)) {
                        goal = candidate;
                    }
                }
                score += house.dist(goal);
                int x_goal = lower_bound(x_pos.begin(), x_pos.end(), goal.x) - x_pos.begin();
                int y_goal = lower_bound(y_pos.begin(), y_pos.end(), goal.y) - y_pos.begin();
                while (x_start != x_goal) {
                    candidate_pos.emplace_back(y_pos[y_start], x_pos[x_start]);
                    int x_next = (x_start < x_goal ? x_start + 1 : x_start - 1);
                    board[y_start][x_start] = Pos(y_start, x_next);
                    x_start = x_next;
                }
                while (y_start != y_goal) {
                    candidate_pos.emplace_back(y_pos[y_start], x_pos[x_start]);
                    int y_next = (y_start < y_goal ? y_start + 1 : y_start - 1);
                    board[y_start][x_start] = Pos(y_next, x_start);
                    y_start = y_next;
                }
            }
            if (chmin(min_score, score))
                min_board = board;
        }

        return min_board;
    }

    void update_power(int &new_power, int sum_power, int &prev_power, const int power) {
        if (prev_power == -1)
            new_power = clamp(sum_power - (C >= 128 ? 100 : 5000), power, 5000);
        else
            new_power = clamp(sum_power * 2 - prev_power - (C >= 128 ? 100 : 5000), power, 5000);
        prev_power = sum_power;
    }

    void move(Pos start, Pos goal) {
        // you can output comment
        cout << "# move from (" << start.y << "," << start.x << ") to (" << goal.y << "," << goal.x
             << ")" << endl;
        // const int power = (C <= 4 ? 50 : 200);
        const int power = (C <= 1 ? 40 : C <= 2 ? 50 : C <= 4 ? 50 : C <= 64 ? 200 : 200);
        int prev_power = -1;
        int new_power = power;

        // down/up
        if (start.y < goal.y) {
            for (int y = start.y; y < goal.y; y++) {
                int sum_power = destruct(y, start.x, new_power, power);
                update_power(new_power, sum_power, prev_power, power);
            }
        } else {
            for (int y = start.y; y > goal.y; y--) {
                int sum_power = destruct(y, start.x, new_power, power);
                update_power(new_power, sum_power, prev_power, power);
            }
        }

        // right/left
        if (start.x < goal.x) {
            for (int x = start.x; x <= goal.x; x++) {
                int sum_power = destruct(goal.y, x, new_power, power);
                update_power(new_power, sum_power, prev_power, power);
            }
        } else {
            for (int x = start.x; x >= goal.x; x--) {
                int sum_power = destruct(goal.y, x, new_power, power);
                update_power(new_power, sum_power, prev_power, power);
            }
        }
    }

    int destruct(int y, int x, int new_power, const int power) {
        // excavate (y, x) with fixed power until destruction
        int sum_power = 0;
        while (!field.is_broken[y][x]) {
            Response result = field.query(y, x, new_power);
            sum_power += new_power;
            if (result == Response::not_broken) {
                new_power = power;
            } else if (result == Response::finish) {
                cerr << "total_cost = " << field.total_cost << endl;
                exit(0);
            } else if (result == Response::invalid) {
                cerr << "invalid: y=" << y << " x=" << x << endl;
                exit(1);
            }
        }
        return sum_power;
    }
};

int main() {
    int N, W, K, C;
    cin >> N >> W >> K >> C;
    vector<Pos> source_pos(W);
    vector<Pos> house_pos(K);
    for (int i = 0; i < W; i++) {
        cin >> source_pos[i].y >> source_pos[i].x;
    }
    for (int i = 0; i < K; i++) {
        cin >> house_pos[i].y >> house_pos[i].x;
    }

    Solver solver(C, source_pos, house_pos);
    solver.solve();
}
