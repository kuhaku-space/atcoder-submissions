#ifndef LOCAL
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#endif

#include <sys/time.h>

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;
using ll = int64_t;
#define FOR(i, m, n) for (int i = (m); i < (n); ++i)
#define rep(i, n) FOR(i, 0, n)
template <class T, class U>
bool chmax(T &a, const U &b) {
    return a < b ? a = b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U &b) {
    return b < a ? a = b, true : false;
}
constexpr int INF = 1000000003;
constexpr ll LINF = 1000000000000000003;

constexpr int N = 16;
constexpr int M = 5000;
constexpr int T = 1000;
constexpr int MAX_HARVESTER = 49;

struct Pos {
    int X, Y;

    constexpr Pos() : X(), Y() {}
    constexpr Pos(int x, int y) : X(x), Y(y) {}

    constexpr bool operator==(const Pos &rhs) const {
        return this->X == rhs.X && this->Y == rhs.Y;
    }
    constexpr bool operator!=(const Pos &rhs) const {
        return !(*this == rhs);
    }

    constexpr Pos operator+(const Pos rhs) const noexcept {
        return Pos(*this) += rhs;
    }
    constexpr Pos operator-(const Pos rhs) const {
        return Pos(*this) -= rhs;
    }
    constexpr Pos &operator+=(const Pos rhs) {
        this->X += rhs.X, this->Y += rhs.Y;
        return *this;
    }
    constexpr Pos &operator-=(const Pos rhs) {
        this->X -= rhs.X, this->Y -= rhs.Y;
        return *this;
    }

    friend istream &operator>>(istream &is, Pos &rhs) {
        int x, y;
        cin >> x >> y;
        rhs = Pos(x, y);
        return (is);
    }
    friend ostream &operator<<(ostream &os, const Pos &rhs) {
        return os << rhs.X << ' ' << rhs.Y;
    }

    constexpr int to_line() const {
        return this->X << 4 | this->Y;
    }

    constexpr bool in_board() const {
        return 0 <= this->X && this->X < N && 0 <= this->Y && this->Y < N;
    }

    constexpr int dist(const Pos &pos) const {
        return abs(this->X - pos.X) + abs(this->Y - pos.Y);
    }
};
array<Pos, 4> dv = {Pos{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

struct Query {
    Pos P;
    int S, E, V;

    Query() {}
    constexpr Query(Pos p, int s, int e, int v) : P(p), S(s), E(e), V(v) {}
    constexpr Query(int r, int c, int s, int e, int v) : P(r, c), S(s), E(e), V(v) {}

    friend istream &operator>>(istream &is, Query &rhs) {
        Pos p;
        int s, e, v;
        is >> p >> s >> e >> v;
        rhs = Query(p, s, e, v);
        return (is);
    }

    constexpr bool in_turn(int t) const {
        return S <= t && t <= E;
    }

    constexpr Pos get_pos() const {
        return P;
    }

    constexpr int get_value() const {
        return V;
    }
};
array<Query, M> querys;

struct Command {
    int cmd, idx, swap_idx;
    bool is_activate;
    Pos F, T;

    constexpr Command() : cmd(-1), idx(), swap_idx(), is_activate(true) {}
    constexpr Command(Pos f) : cmd(0), idx(), swap_idx(), is_activate(true), F(f) {}
    constexpr Command(int x, Pos f, Pos t) : cmd(1), idx(x), swap_idx(), is_activate(true), F(f), T(t) {}
    constexpr Command(int x, int y, Pos f, Pos t, bool flg = true)
        : cmd(2), idx(x), swap_idx(y), is_activate(flg), F(f), T(t) {}

    friend ostream &operator<<(ostream &os, const Command &rhs) {
        if (rhs.cmd == -1 || rhs.cmd == 2)
            return os << -1;
        else if (rhs.cmd == 0)
            return os << rhs.F;
        else if (rhs.cmd == 1)
            return os << rhs.F << ' ' << rhs.T;
        else
            return os;
    }

    void buy(Pos f) {
        cmd = 0;
        F = f;
    }

    void move(int x, Pos f, Pos t) {
        cmd = 1, idx = x;
        F = f, T = t;
    }

    constexpr bool is_pass() const {
        return this->cmd == -1;
    }
    constexpr bool is_buy() const {
        return this->cmd == 0;
    }
    constexpr bool is_move() const {
        return this->cmd == 1;
    }
    constexpr bool is_swap() const {
        return this->cmd == 2;
    }

    constexpr int get_cmd() const {
        return cmd;
    }
    constexpr int get_idx(int x = 0) const {
        return x == 0 ? idx : swap_idx;
    }
    constexpr Pos get_pos(int x = 0) const {
        return x == 0 ? F : T;
    }

    constexpr Command inverse() const {
        return Command(this->get_idx(), this->get_pos(1), this->get_pos(0));
    }
};

array<Pos, MAX_HARVESTER> default_harvester_pos;

void make_default_harvester_pos() {
    array<int, 6> arr = {13, 11, 11, 6, 6, 4};
    Pos cur_pos(0, 2);
    int idx = 0, cnt = 0;
    for (int i = 1; i < MAX_HARVESTER; ++i) {
        default_harvester_pos[i] = cur_pos;
        if (cnt == arr[idx]) {
            ++idx;
            cnt = 0;
        }
        cur_pos += dv[idx % 4];
        ++cnt;
    }
    // reverse(default_harvester_pos.begin(), default_harvester_pos.end());
}

void make_reversed_default_harvester_pos() {
    array<int, 6> arr = {11, 11, 11, 6, 6, 4};
    Pos cur_pos(2, 2);
    int idx = 0, cnt = 0;
    for (int i = 0; i < MAX_HARVESTER; ++i) {
        default_harvester_pos[i] = cur_pos;
        if (cnt == arr[idx]) {
            ++idx;
            cnt = 0;
        }
        cur_pos += dv[idx % 4];
        ++cnt;
    }
    reverse(default_harvester_pos.begin(), default_harvester_pos.end());
}

struct State {
    int score;
    int harvester_count;
    array<Pos, MAX_HARVESTER> harvester_pos;
    array<array<int, N>, N> harvester_idx;
    array<bool, M> vagetable_harvested;

    constexpr State() : score(1), harvester_count(), harvester_idx(), vagetable_harvested() {
        harvester_pos.fill(Pos());
        for (auto &v : harvester_idx)
            v.fill(-1);
        vagetable_harvested.fill(false);
    }

    constexpr bool exists_harvester(Pos pos) const {
        return ~(this->harvester_idx[pos.X][pos.Y]);
    }
    constexpr bool is_exist_next(const Pos &pos) const {
        for (int m = 1; m < this->get_harvester_count(); ++m) {
            if (pos.dist(this->get_harvester_pos(m)) == 1)
                return true;
        }
        return false;
    }

    constexpr Pos get_harvester_pos(int idx) const {
        assert(idx < this->get_harvester_count());
        return this->harvester_pos[idx];
    }
    constexpr int get_harvester_idx(Pos pos) const {
        return this->harvester_idx[pos.X][pos.Y];
    }
    constexpr int get_harvester_count() const {
        return this->harvester_count;
    }

    constexpr void set_harvester(int idx, Pos pos) {
        assert(!(this->exists_harvester(pos)));
        this->harvester_pos[idx] = pos;
        this->harvester_idx[pos.X][pos.Y] = idx;
    }
    constexpr void reset_harvester(int idx) {
        auto pos = this->get_harvester_pos(idx);
        this->harvester_idx[pos.X][pos.Y] = -1;
    }
    constexpr void swap_harvester(int idx, int swap_idx) {
        assert(idx < this->get_harvester_count() && swap_idx < this->get_harvester_count());
        if (idx == swap_idx)
            return;
        auto pos = this->harvester_pos[idx];
        auto swap_pos = this->harvester_pos[swap_idx];
        this->reset_harvester(idx);
        this->reset_harvester(swap_idx);
        this->set_harvester(idx, swap_pos);
        this->set_harvester(swap_idx, pos);
    }

    constexpr void execute(const Command &command) {
        if (command.is_buy()) {
            assert(!(this->exists_harvester(command.get_pos())));
            int idx = this->get_harvester_count();
            this->score -= this->calc_new_harvester_cost();
            this->set_harvester(idx, command.get_pos());
            ++(this->harvester_count);
        } else if (command.is_move()) {
            assert(command.get_pos() == this->get_harvester_pos(command.get_idx()));
            assert(this->exists_harvester(command.get_pos()));
            assert(!(this->exists_harvester(command.get_pos(1))));
            this->reset_harvester(command.get_idx());
            this->set_harvester(command.get_idx(), command.get_pos(1));
            assert(command.get_pos(1) == this->get_harvester_pos(command.get_idx()));
        } else if (command.is_swap()) {
            this->swap_harvester(command.get_idx(), command.get_idx(1));
        }
    }

    constexpr int calc_new_harvester_cost() const {
        int next_harvester_count = this->harvester_count + 1;
        return next_harvester_count * next_harvester_count * next_harvester_count;
    }
    constexpr bool can_buy_new_harvester() const {
        return this->score >= calc_new_harvester_cost();
    }

    vector<Command> solve(int turn) const {
        vector<Command> commands;
        static vector<int> move_idx = {0, 1, 2};
        if (this->harvester_count == 0) {
            Pos next_pos;
            int max_score = 0;
            for (int m = 0; m < M; ++m) {
                if (!this->vagetable_harvested[m] && querys[m].in_turn(turn)) {
                    if (chmax(max_score, querys[m].get_value())) {
                        next_pos = querys[m].get_pos();
                    }
                }
            }
            commands.emplace_back(Command(next_pos));
        } else if (this->get_harvester_count() < MAX_HARVESTER && this->can_buy_new_harvester() &&
                   !this->exists_harvester(default_harvester_pos[this->get_harvester_count()])) {
            commands.emplace_back(Command(default_harvester_pos[this->get_harvester_count()]));
        } else if (this->get_harvester_count() < 5) {
            Pos next_pos;
            int max_score = 0;
            for (int m = 0; m < M; ++m) {
                if (!this->vagetable_harvested[m] && querys[m].in_turn(turn) &&
                    !this->exists_harvester(querys[m].get_pos())) {
                    if (chmax(max_score,
                              querys[m].get_value() *
                                  (this->is_exist_next(querys[m].get_pos()) ? this->get_harvester_count() : 1))) {
                        next_pos = querys[m].get_pos();
                    }
                }
            }
            commands.emplace_back(Command(0, this->get_harvester_pos(0), next_pos));
        } else {
            int query_idx = -1;
            int opp_idx = -1;
            int max_score = 0;
            for (int m = 0; m < M; ++m) {
                if (this->vagetable_harvested[m] || this->exists_harvester(querys[m].get_pos()))
                    continue;
                int dist = 100;
                int idx = -1;
                for (int i = 3; i < this->get_harvester_count(); ++i) {
                    int d = this->get_harvester_pos(i).dist(querys[m].get_pos());
                    if (chmin(dist, d))
                        idx = i;
                }
                assert(dist);

                if (querys[m].in_turn(turn) && chmax(max_score, querys[m].get_value())) {
                    query_idx = m;
                    opp_idx = -1;
                }
                if (dist <= 3 && querys[m].in_turn(turn + dist - 1)) {
                    if (chmax(max_score, querys[m].get_value() * this->get_harvester_count() / dist)) {
                        query_idx = m;
                        opp_idx = idx;
                    }
                }
            }

            if (!~query_idx)
                return vector<Command>(1);

            auto opp_pos = querys[query_idx].get_pos();
            if (opp_idx == -1) {
                int idx = move_idx[0];
                commands.emplace_back(Command(idx, this->get_harvester_pos(idx), opp_pos));
            } else {
                auto state_copy = *this;
                Pos cur_pos = this->get_harvester_pos(opp_idx);
                int dist = opp_pos.dist(cur_pos);
                int duplicate_cnt = 0;
                for (int i = 0; i < dist; ++i) {
                    for (auto p : dv) {
                        if ((cur_pos + p).in_board() && opp_pos.dist(cur_pos + p) == dist - i - 1) {
                            cur_pos += p;
                            int idx = move_idx[i];
                            if (this->exists_harvester(cur_pos)) {
                                int swap_idx = this->get_harvester_idx(cur_pos);
                                bool flag = !querys[query_idx].in_turn(turn + dist - 2 - duplicate_cnt);
                                auto command = Command(idx, swap_idx, state_copy.get_harvester_pos(idx),
                                                       state_copy.get_harvester_pos(swap_idx), flag);
                                state_copy.execute(command);
                                commands.emplace_back(command);
                                if (flag) {
                                    ++duplicate_cnt;
                                }
                            } else {
                                auto command = Command(idx, state_copy.get_harvester_pos(idx), cur_pos);
                                state_copy.execute(command);
                                commands.emplace_back(command);
                            }
                            break;
                        }
                    }
                }
                reverse(move_idx.begin(), move_idx.begin() + dist);
            }
        }
        return commands;
    }

    constexpr void harvest_vagetables(int turn) {
        for (int m = 0; m < M; ++m) {
            if (!this->vagetable_harvested[m] && querys[m].in_turn(turn)) {
                if (this->exists_harvester(querys[m].get_pos())) {
                    bitset<MAX_HARVESTER> connection;
                    auto dfs = [&](auto self, Pos p) -> void {
                        for (int i = 0; i < this->get_harvester_count(); ++i) {
                            if (this->get_harvester_pos(i) == p && !connection[i]) {
                                connection[i] = true;
                                for (auto &d : dv)
                                    self(self, p + d);
                            }
                        }
                    };
                    dfs(dfs, querys[m].get_pos());
                    this->score += querys[m].get_value() * connection.count();
                    this->vagetable_harvested[m] = true;
                }
            }
        }
    }

    constexpr int get_score() const {
        return this->score;
    }
};

int main(void) {
    int tmp;
    cin >> tmp >> tmp >> tmp;
    for (auto &q : querys)
        cin >> q;

    make_default_harvester_pos();

    queue<Command> command_queue;
    State state;
    for (int t = 0; t < T; ++t) {
        // cerr << t << endl;
        if (command_queue.empty()) {
            auto commands = state.solve(t);
            for (auto command : commands)
                command_queue.emplace(command);
        }
        while (!command_queue.front().is_activate) {
            state.execute(command_queue.front());
            command_queue.pop();
        }
        auto command = command_queue.front();
        command_queue.pop();
        cout << command << endl;
        state.execute(command);
        state.harvest_vagetables(t);
    }
    cerr << state.get_score() << endl;

    return 0;
}
