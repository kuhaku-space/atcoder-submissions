// Problem : https://atcoder.jp/contests/ahc001/tasks/ahc001_a
#ifdef ONLINE_JUDGE
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#endif

#include <sys/time.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
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

struct Xorshift {
    unsigned int x, y, z, w;

    Xorshift() {
        x = 123456789, y = 362436069, z = 521288629, w = 88675123;
    }

    unsigned int operator()() {
        unsigned int t = (x ^ (x << 11));
        x = y;
        y = z;
        z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }

    double rand_d() {
        return (double)(*this)() / (1LL << 32);
    }
};
Xorshift xor128;

constexpr int SZ = 10000;
constexpr double T0 = 3e5, T1 = 1e2, TL = 4.975;
constexpr int LOOP = 20, SIZE1 = 2047, SIZE2 = 1023;
int N;

struct Item {
    int x, y, r;

    friend istream &operator>>(istream &is, Item &rhs) {
        is >> rhs.x >> rhs.y >> rhs.r;
        return (is);
    }
};

struct Command {
    int a, b, c, d;

    Command &operator+=(const Command &rhs) {
        a += rhs.a, b += rhs.b, c += rhs.c, d += rhs.d;
        return *this;
    }
    Command &operator-=(const Command &rhs) {
        a -= rhs.a, b -= rhs.b, c -= rhs.c, d -= rhs.d;
        return *this;
    }
    Command operator+(const Command &rhs) const {
        return Command(*this) += rhs;
    }
    Command operator-(const Command &rhs) const {
        return Command(*this) -= rhs;
    }

    void set(const Item &item) {
        a = item.x, b = item.y, c = item.x + 1, d = item.y + 1;
    }

    bool is_contain(const Item &item) const {
        return a <= item.x && item.x < c && b <= item.y && item.y < d;
    }

    inline int get_s() const {
        return max(0, (c - a) * (d - b));
    }

    double eval(const Item &item) const {
        if (!is_contain(item))
            return 0;
        int s = get_s();
        double t = min(1.0, (double)s / item.r);
        t = 1 - (1 - t) * (1 - t);
        return t * 1e9 / N;
    }

    bool in_board() const {
        return 0 <= a && a < c && c <= SZ && 0 <= b && b < d && d <= SZ;
        // return 0 <= a && c <= SZ && 0 <= b && d <= SZ;
    }

    bool is_overlap(const Command &cmd) const {
        int xl = max(a, cmd.a), xr = min(c, cmd.c);
        int yl = max(b, cmd.b), yr = min(d, cmd.d);
        return xl < xr && yl < yr;
    }

    friend ostream &operator<<(ostream &os, const Command &rhs) {
        return os << rhs.a << " " << rhs.b << " " << rhs.c << " " << rhs.d;
    }
};

Command &operator*=(Command &lhs, const int rhs) {
    lhs.a *= rhs, lhs.b *= rhs, lhs.c *= rhs, lhs.d *= rhs;
    return lhs;
}
Command operator*(const Command &lhs, const int rhs) {
    Command res(lhs);
    res.a *= rhs, res.b *= rhs, res.c *= rhs, res.d *= rhs;
    return res;
}

vector<Item> items;

vector<Command> dir = {
    {-1, 0, 0, 0}, {0, -1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

void input() {
    cin >> N;
    items.resize(N);
    for (auto &item : items) cin >> item;
}

void format_command(Command &cmd, Item &item) {
    int max_x = 0, max_y = 0;
    double max_score = 0;
    int dx = cmd.c - cmd.a, dy = cmd.d - cmd.b;
    for (int x = 1; x <= dx; ++x) {
        int l = item.r / x;
        int r = l + 1;
        l = clamp(l, 1, dy);
        r = clamp(r, 1, dy);
        if (chmax(max_score, (double)min(item.r, x * l) / max(item.r, x * l))) {
            max_x = x, max_y = l;
        }
        if (chmax(max_score, (double)min(item.r, x * r) / max(item.r, x * r))) {
            max_x = x, max_y = r;
        }
    }

    chmax(cmd.a, item.x - max_x + 1);
    chmax(cmd.b, item.y - max_y + 1);
    cmd.c = cmd.a + max_x;
    cmd.d = cmd.b + max_y;
}

double eval(const vector<Command> &cmds) {
    double res = 0;
    rep(i, N) res += cmds[i].eval(items[i]);
    return res;
}

void extend_area(vector<Command> &cmds) {
    vector<int> id(N << 2);
    iota(id.begin(), id.end(), 0);
    int sz = N << 2;
    while (sz) {
        int t = xor128() % sz;
        int idx = id[t] >> 2;
        int didx = id[t] & 3;

        Command &cmd = cmds[idx];
        cmd += dir[didx];
        bool flg = cmd.in_board();
        rep(i, N) {
            if (!flg)
                break;
            if (i == idx)
                continue;
            flg &= !cmd.is_overlap(cmds[i]);
        }
        if (!flg) {
            cmd -= dir[didx];
            swap(id[t], id[--sz]);
        }
    }
}

void solve(vector<Command> &cmds) {
    vector<int> id(N);
    iota(id.begin(), id.end(), 0);
    int sz = N;
    while (sz) {
        int r = xor128() % sz;
        int idx = id[r];
        auto &item = items[idx];
        auto &cmd = cmds[idx];
        if (cmd.get_s() >= item.r) {
            swap(id[r], id[--sz]);
            continue;
        }

        vector<int> dir_id(4);
        iota(dir_id.begin(), dir_id.end(), 0);
        while (dir_id.size()) {
            int k = xor128() % dir_id.size();
            int didx = dir_id[k];
            cmd += dir[didx];
            bool flg = cmd.in_board();
            rep(i, N) {
                if (!flg)
                    break;
                if (i == idx)
                    continue;
                flg &= !cmd.is_overlap(cmds[i]);
            }
            if (flg)
                break;

            cmd -= dir[didx];
            dir_id.erase(dir_id.begin() + k);
        }

        if (dir_id.empty())
            swap(id[r], id[--sz]);
    }

    extend_area(cmds);
}

struct annealing {
    vector<int> id;

    annealing() {
        id = vector<int>(4);
        iota(id.begin(), id.end(), 0);
    }

    double temperature(double t) {
        rep(i, 4) swap(id[i], id[xor128() & 3]);
        return T0 + (T1 - T0) * t / TL;
        // t /= TL;
        // return pow(T0, 1.0 - t) * pow(T1, t);
    }

    bool is_update(double diff_score, double temp) {
        if (diff_score > 0)
            return true;
        return exp(diff_score / temp) >= xor128.rand_d();
    }

    double resolve_contain(Command &cmd, const Item &item, const Command &lim) {
        Command res;
        res.set(item);
        double max_eval = res.eval(item);
        for (auto i : id) {
            auto tmp = cmd;
            switch (i) {
                case 0:
                    chmax(tmp.a, lim.a);
                    break;
                case 1:
                    chmax(tmp.b, lim.b);
                    break;
                case 2:
                    chmin(tmp.c, lim.c);
                    break;
                case 3:
                    chmin(tmp.d, lim.d);
                    break;
            }

            double eval = tmp.eval(item);
            if (chmax(max_eval, eval))
                res = tmp;
        }
        cmd = res;
        return max_eval;
    }

    double resolve_overlap(Command &cmd, const Item &item,
                           const Command &command) {
        Command res;
        res.set(item);
        double max_eval = res.eval(item);
        for (auto i : id) {
            auto tmp = cmd;
            switch (i) {
                case 0:
                    chmax(tmp.a, command.c);
                    break;
                case 1:
                    chmax(tmp.b, command.d);
                    break;
                case 2:
                    chmin(tmp.c, command.a);
                    break;
                case 3:
                    chmin(tmp.d, command.b);
                    break;
            }

            double eval = tmp.eval(item);
            if (chmax(max_eval, eval))
                res = tmp;
        }
        cmd = res;
        return max_eval;
    }

    void solve(vector<Command> &commands) {
        int debug_cnt = 0;
        auto ans = commands;
        double max_eval = eval(ans);
        double now_eval = max_eval;
        int cnt = 0;
        while ((double)clock() / CLOCKS_PER_SEC < TL) {
            ++debug_cnt;
            double t = (double)clock() / CLOCKS_PER_SEC;
            double temp = temperature(t);
            rep(_, LOOP) {
                auto cmds = commands;
                int idx = xor128() % N;
                int didx = xor128() & 3;
                auto &item = items[idx];
                auto &cmd = cmds[idx];
                double cur_eval = 0, next_eval = 0;
                cur_eval += cmd.eval(item);
                int k = xor128() & (t <= 2.5 ? SIZE1 : SIZE2);
                cmd += dir[didx] * k;
                if (!cmd.in_board())
                    continue;

                Command lim{0, 0, SZ, SZ};
                rep(i, N) {
                    if (i == idx)
                        continue;
                    if (cmd.is_contain(items[i])) {
                        auto [x, y, r] = items[i];
                        chmax(lim.a, x + 1);
                        chmax(lim.b, y + 1);
                        chmin(lim.c, x);
                        chmin(lim.d, y);
                    }
                }
                next_eval += resolve_contain(cmd, item, lim);
                vector<int> overlap_id;
                rep(i, N) {
                    if (i == idx)
                        continue;
                    if (cmd.is_overlap(cmds[i]))
                        overlap_id.emplace_back(i);
                }
                for (auto i : overlap_id) {
                    cur_eval += cmds[i].eval(items[i]);
                    next_eval += resolve_overlap(cmds[i], items[i], cmd);
                }
                if (is_update(next_eval - cur_eval, temp)) {
                    commands[idx] = cmds[idx];
                    for (auto i : overlap_id) commands[i] = cmds[i];
                    now_eval += next_eval - cur_eval;
                }
                if (chmax(max_eval, now_eval)) {
                    ans = commands;
                    cnt = 0;
                } else
                    cnt = 0;
                if (cnt >= 100000) {
                    commands = ans;
                    now_eval = max_eval;
                }
            }
        }
        commands = ans;
        cerr << debug_cnt << " " << (int)max_eval << " " << (int)eval(ans) << endl;
    }
};

int main(void) {
    input();
    vector<Command> ans(N);
    rep(i, N) ans[i].set(items[i]);
    solve(ans);
    annealing solver;
    solver.solve(ans);
    rep(i, N) format_command(ans[i], items[i]);
    for (auto &cmd : ans) cout << cmd << endl;
    return 0;
}
