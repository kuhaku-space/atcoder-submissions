#include <bits/stdc++.h>
using namespace std;

template <class T, class U>
constexpr bool chmax(T &a, const U &b) noexcept {
    return a < b ? a = b, true : false;
}
template <class T, class U>
constexpr bool chmin(T &a, const U &b) noexcept {
    return b < a ? a = b, true : false;
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

    constexpr Position operator+(const Position &rhs) const {
        return Position(*this) += rhs;
    }
    constexpr Position operator-(const Position &rhs) const {
        return Position(*this) -= rhs;
    }

    constexpr bool operator==(const Position &rhs) const {
        return this->x == rhs.x && this->y == rhs.y;
    }
    constexpr bool operator!=(const Position &rhs) const {
        return !(*this == rhs);
    }
};

array<Position, 4> dir_pos = {Position{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
array<char, 4> dir_op = {'L', 'U', 'R', 'D'};

template <int BEAM_SIZE, int N, int T = 2 * N *N *N>
struct beam_search {
    static bool in_board(Position p) {
        return in_board(p.x, p.y);
    }
    static bool in_board(int x, int y) {
        return 0 <= x && x < N && 0 <= y && y < N;
    }

    struct State {
        State() : turn(), score(), final_score() {}

        bool operator<(const State &rhs) const {
            return this->eval() < rhs.eval();
        }
        bool operator>(const State &rhs) const {
            return rhs < *this;
        }

        void init() {
            ans.fill(0);
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    char c;
                    cin >> c;
                    if ('0' <= c && c <= '9')
                        board[i][j] = c - '0';
                    else
                        board[i][j] = c - 'a' + 10;
                    if (!board[i][j])
                        space = Position(i, j);
                }
            }
            this->update_score();
        }

        double eval() const {
            return final_score * turn / T + score * (T - turn) / T;
        }

        double final_eval() const {
            return final_score;
        }

        array<unsigned long, N> get_hash() const {
            array<unsigned long, N> res = {};
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    res[i] = res[i] << 4 | board[i][j];
                }
            }
            return res;
        }

        void update_score() {
            bitset<N * N + 1> cycle;
            array<array<int, N>, N> group = {};
            int cnt = 1;

            auto dfs = [&](auto self, Position pos, Position prev) -> void {
                if (group[pos.x][pos.y]) {
                    if (group[pos.x][pos.y] == cnt) {
                        cycle[cnt] = true;
                    }
                    return;
                }
                group[pos.x][pos.y] = cnt;
                for (int k = 0; k < 4; ++k) {
                    auto next_pos = pos + dir_pos[k];
                    if (next_pos != prev && in_board(next_pos) && (board[pos.x][pos.y] >> k & 1) &&
                        (board[next_pos.x][next_pos.y] >> ((k + 2) % 4) & 1))
                        self(self, next_pos, pos);
                }
            };

            for (int x = 0; x < N; ++x) {
                for (int y = 0; y < N; ++y) {
                    if (group[x][y])
                        continue;
                    dfs(dfs, Position(x, y), Position(x, y));
                    ++cnt;
                }
            }

            array<int, N *N + 1> sum = {};

            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    ++sum[group[i][j]];
                }
            }

            this->score = 0;
            this->final_score = 0;
            for (int i = 1; i <= N * N; ++i) {
                this->score += sum[i] * sum[i];
                if (!cycle[i])
                    chmax(this->final_score, 5e5 * sum[i] / (N * N - 1));
            }
            this->score *= 5e5;
        }

        void swap(Position p, Position q) {
            std::swap(board[p.x][p.y], board[q.x][q.y]);
        }

        bool can_place(int k) const {
            return in_board(space + dir_pos[k]);
        }

        auto place(int k) const {
            auto res(*this);
            res._place(k);
            return res;
        }

        auto answer() const {
            return make_pair(this->turn, this->ans);
        }

      private:
        int turn;
        double score, final_score;
        Position space;
        array<array<int, N>, N> board;
        array<long, 2 * N * N * N / 32 + 1> ans;

        void _place(int k) {
            ans[turn / 32] |= (long)k << ((turn % 32) * 2);
            this->swap(space, space + dir_pos[k]);
            space += dir_pos[k];
            this->update_score();
            ++turn;
        }
    };

    auto solve() {
        std::array<State, BEAM_SIZE> cur, nxt;
        State state = State();
        state.init();
        cur[0] = state;
        int cur_size = 1, nxt_size = 0;
        double max_eval = state.final_eval();
        set<array<unsigned long, N>> st;
        for (int t = 0; t < 2 * N * N * N; ++t) {
            std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>,
                                std::greater<>>
                eval_que;
            nxt_size = 0;
            for (int i = 0; i < cur_size; ++i) {
                for (int k = 0; k < 4; ++k) {
                    if (!cur[i].can_place(k))
                        continue;
                    auto &&s = cur[i].place(k);
                    auto &&h = s.get_hash();
                    if (st.count(h))
                        continue;
                    if (chmax(max_eval, s.final_eval())) {
                        state = s;
                    }
                    auto eval = s.eval();
                    if (nxt_size < BEAM_SIZE) {
                        nxt[nxt_size] = s;
                        eval_que.emplace(eval, nxt_size++);
                        st.emplace(h);
                    } else if (eval > eval_que.top().first) {
                        int idx = eval_que.top().second;
                        eval_que.pop();
                        nxt[idx] = s;
                        eval_que.emplace(eval, idx);
                        st.emplace(h);
                    }
                }
            }
            swap(cur, nxt);
            cur_size = nxt_size;
        }

        std::cerr << max_eval << std::endl;
        return state.answer();
    }
};

int main(void) {
    int n, t;
    cin >> n >> t;

    string s;
    if (n == 6) {
        beam_search<1300, 6> solver;
        auto [turn, ans] = solver.solve();
        for (int i = 0; i < turn; ++i) {
            s += dir_op[ans[i / 32] >> ((i % 32) * 2) & 3];
        }
    } else if (n == 7) {
        beam_search<640, 7> solver;
        auto [turn, ans] = solver.solve();
        for (int i = 0; i < turn; ++i) {
            s += dir_op[ans[i / 32] >> ((i % 32) * 2) & 3];
        }
    } else if (n == 8) {
        beam_search<400, 8> solver;
        auto [turn, ans] = solver.solve();
        for (int i = 0; i < turn; ++i) {
            s += dir_op[ans[i / 32] >> ((i % 32) * 2) & 3];
        }
    } else if (n == 9) {
        beam_search<230, 9> solver;
        auto [turn, ans] = solver.solve();
        for (int i = 0; i < turn; ++i) {
            s += dir_op[ans[i / 32] >> ((i % 32) * 2) & 3];
        }
    } else if (n == 10) {
        beam_search<140, 10> solver;
        auto [turn, ans] = solver.solve();
        for (int i = 0; i < turn; ++i) {
            s += dir_op[ans[i / 32] >> ((i % 32) * 2) & 3];
        }
    }
    cout << s << endl;

    ofstream fout("../log/time.txt", ios::app);
    fout << n << ' ' << (double)clock() / CLOCKS_PER_SEC << endl;
    fout.close();

    return 0;
}
