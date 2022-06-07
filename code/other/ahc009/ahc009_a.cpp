#ifndef LOCAL
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#endif

#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;
using ll = int64_t;
#define FOR(i, m, n) for (int i = (m); i < (n); ++i)
#define rep(i, n) FOR(i, 0, n)
template <class T, class U>
constexpr bool chmax(T &a, const U &b) noexcept {
    return a < b ? a = b, true : false;
}
template <class T, class U>
constexpr bool chmin(T &a, const U &b) noexcept {
    return b < a ? a = b, true : false;
}
constexpr int Inf = 1000000003;
constexpr int64_t INF = 1000000000000000003;

constexpr int N = 20;

// clang-format off
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

    constexpr bool operator==(const Position &rhs) const {
        return this->x == rhs.x && this->y == rhs.y;
    }

    constexpr bool operator!=(const Position &rhs) const {
        return !(*this == rhs);
    }

    constexpr bool in_board() const {
        return 0 <= this->x && this->x < N && 0 <= this->y && this->y < N;
    }
};
// clang-format on

Position dir_pos[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
string dir_ch = "UDLR";

struct Operation {
    int index;

    constexpr Operation(int _index) : index(_index) {}

    Position get_position() const {
        return dir_pos[index];
    }

    char get_char() const {
        return dir_ch[index];
    }
};

Position S, T;
double P;
vector<string> H(N), V(N - 1);
array<array<int, N>, N> dist;
array<double, N * N + 1> sq;
array<array<int, N>, N> visited;

bool can_move(Position pos, Operation op) {
    return visited[pos.x][pos.y] >> op.index & 1;
}

bool _can_move(Position pos, Operation op) {
    if (!pos.in_board() || !(pos + op.get_position()).in_board())
        return false;
    if (op.index == 0)
        return V[pos.x - 1][pos.y] == '0';
    else if (op.index == 1)
        return V[pos.x][pos.y] == '0';
    else if (op.index == 2)
        return H[pos.x][pos.y - 1] == '0';
    else if (op.index == 3)
        return H[pos.x][pos.y] == '0';
    return false;
}

bool _can_move(Position pos, int index) {
    return _can_move(pos, Operation(index));
}

void bfs() {
    rep(i, N) dist[i].fill(Inf);
    queue<Position> que;
    dist[T.x][T.y] = 0;
    que.emplace(T);
    while (!que.empty()) {
        auto p = que.front();
        que.pop();
        for (auto i : dir_pos) {
            auto q = p + i;
            if (q.in_board() && chmin(dist[q.x][q.y], dist[p.x][p.y] + 1)) {
                que.emplace(q);
            }
        }
    }
}

void init() {
    rep(i, N * N + 1) sq[i] = sqrt(sqrt(i));
    rep(i, N) {
        visited[i].fill(0);
        rep(j, N) {
            rep(k, 4) if (_can_move(Position(i, j), k)) visited[i][j] |= 1 << k;
        }
    }
}

template <int BEAM_SIZE>
struct beam_search {
    struct State {
        State() : score(), sum(), board{}, operations() {
            board[S.x][S.y] = 1;
            update_score();
        }

        bool operator<(const State &rhs) const {
            return this->eval() < rhs.eval();
        }
        bool operator>(const State &rhs) const {
            return rhs < *this;
        }

        constexpr double eval() const {
            return score + sum;
        }
        constexpr double final_eval() const {
            return score + board[T.x][T.y] * 200;
        }

        void update_score(int turn = 0) {
            sum = 0;
            rep(i, N) {
                rep(j, N) {
                    if (dist[i][j] && dist[i][j] < 200 - turn) {
                        sum += board[i][j] / sq[dist[i][j]];
                        // sum += board[i][j] * pow(1 - P, dist[i][j]);
                    }
                }
            }
            score += board[T.x][T.y];
        }

        auto place(int turn, int index) const {
            auto res(*this);
            res._place(turn, index);
            return res;
        }

        auto answer() const {
            string res;
            for (auto &i : operations) res += i.get_char();
            return res;
        }

      private:
        double score, sum;
        array<array<double, N>, N> board;
        vector<Operation> operations;

        void _place(int turn, int index) {
            operations.emplace_back(index);
            array<array<double, N>, N> next = {};
            rep(i, N) {
                rep(j, N) {
                    if (board[i][j] == 0) {
                        continue;
                    } else if (Position(i, j) == T) {
                        next[i][j] += board[i][j];
                        continue;
                    }
                    if (can_move(Position(i, j), Operation(index))) {
                        auto new_pos = Position(i, j) + Operation(index).get_position();
                        next[i][j] += board[i][j] * P;
                        next[new_pos.x][new_pos.y] += board[i][j] * (1 - P);
                    } else {
                        next[i][j] += board[i][j];
                    }
                }
            }
            board = next;
            update_score(turn);
        }
    };

    auto solve() {
        init();
        bfs();
        std::array<State, BEAM_SIZE> cur, nxt;
        cur[0] = State();
        int cur_size = 1, nxt_size = 0;
        for (int t = 0; t < 200; ++t) {
            std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>,
                                std::greater<>>
                eval_que;
            nxt_size = 0;
            for (int i = 0; i < cur_size; ++i) {
                for (int k = 0; k < 4; ++k) {
                    auto &&s = cur[i].place(t, k);
                    double eval = s.eval();
                    if (nxt_size < BEAM_SIZE) {
                        nxt[nxt_size] = s;
                        eval_que.emplace(eval, nxt_size++);
                    } else if (eval > eval_que.top().first) {
                        int idx = eval_que.top().second;
                        eval_que.pop();
                        nxt[idx] = s;
                        eval_que.emplace(eval, idx);
                    }
                }
            }
            swap(cur, nxt);
            cur_size = nxt_size;
        }

        int idx = 0;
        double max_eval = cur[0].final_eval();
        for (int i = 1; i < cur_size; ++i) {
            if (chmax(max_eval, cur[i].final_eval()))
                idx = i;
        }
        std::cerr << (int)round(max_eval * 250000) << std::endl;
        return cur[idx].answer();
    }
};

int main(void) {
    cin >> S.x >> S.y >> T.x >> T.y;
    cin >> P;
    rep(i, N) cin >> H[i];
    rep(i, N - 1) cin >> V[i];
    beam_search<1300> solver;

    cout << solver.solve() << endl;

    return 0;
}
