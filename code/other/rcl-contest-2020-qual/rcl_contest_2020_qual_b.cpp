// Problem :
// https://atcoder.jp/contests/rcl-contest-2020-qual/tasks/rcl_contest_2020_qual_b

#include <sys/time.h>

#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
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

constexpr int N = 50;
constexpr int M = 500;
const string dir = "UDLR";
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int board[N][N];

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
};
Xorshift xor128;

struct Command {
    char x, y, d;

    Command() : d(-1) {
    }
    Command(char _x, char _y, char _d) : x(_x), y(_y), d(_d) {
    }

    void print() {
        if (d != -1)
            cout << (int)x << ' ' << (int)y << ' ' << dir[d] << endl;
        else
            cout << -1 << endl;
    }
};

struct State {
    array<array<char, N>, N> color;
    array<array<bool, N>, N> visitable;
    array<Command, M> commands;

    State() {
        init();
    }

    void init() {
        rep(i, N) rep(j, N) color[i][j] = -1;
        rep(i, N) rep(j, N) visitable[i][j] = false;
        update(0, 0, 0);
        update(0, N - 1, 1);
        update(N - 1, 0, 2);
        update(N - 1, N - 1, 3);
    }

    inline bool in_board(int x, int y) {
        return x >= 0 && x < N && y >= 0 && y < N;
    }

    int score() {
        int res = 0;
        rep(i, N) rep(j, N) if (color[i][j] == board[i][j]) res++;
        return res;
    }

    int eval(int c, Command cmd) {
        int res = 0;
        int x = cmd.x, y = cmd.y;
        rep(i, 5) {
            x += dx[cmd.d];
            y += dy[cmd.d];
            if (!in_board(x, y))
                break;
            if (board[x][y] == c) {
                if (color[x][y] == -1)
                    res += 12;
                else if (board[x][y] != color[x][y])
                    res += 10;
            } else if (board[x][y] == color[x][y])
                res -= 30;
        }

        return res;
    }

    int countRest(int c) {
        int res = 0;
        rep(i, N) rep(j, N) if (!visitable[i][j] && board[i][j] == c) res++;
        return res;
    }

    void fill(int x, int y, int c) {
        if (board[x][y] != c || visitable[x][y])
            return;
        visitable[x][y] = true;
        rep(i, 4) {
            x += dx[i];
            y += dy[i];
            if (!in_board(x, y))
                break;
            fill(x, y, c);
        }
    }

    void update(int x, int y, int c) {
        color[x][y] = c;
        fill(x, y, c);
    }

    Command findNewArea(int c) {
        Command res, tmp;
        int x, y, d, gx, gy;
        int min = INF;
        rep(i, N) rep(j, N) {
            if (board[i][j] != c || visitable[i][j])
                continue;
            rep(k, N) rep(l, N) {
                if (color[k][l] == c) {
                    int dist = ((abs(k - i) + abs(l - j)) << 2) + xor128() % 10;
                    if (chmin(min, dist)) {
                        x = k, y = l;
                        gx = i, gy = j;
                    }
                }
            }
        }

        if (min != INF) {
            if (x > gx)
                d = 0;
            else if (y > gy)
                d = 2;
            else if (x < gx)
                d = 1;
            else
                d = 3;
            res = Command(x, y, d);
        }
        return res;
    }

    Command drowArea(int c) {
        Command res, tmp;
        int score = -INF;
        rep(i, N) rep(j, N) {
            if (color[i][j] != c)
                continue;
            rep(k, 4) {
                tmp = Command(i, j, k);
                if (chmax(score, eval(c, tmp)))
                    res = Command(i, j, k);
            }
        }

        return res;
    }

    void paint(int c, Command cmd) {
        if (cmd.d == -1)
            return;
        int x = cmd.x, y = cmd.y;
        rep(i, 5) {
            x += dx[cmd.d];
            y += dy[cmd.d];
            if (!in_board(x, y))
                break;
            update(x, y, c);
        }
    }

    Command solve(int c, int t) {
        Command res;
        if (countRest(c) >= 40 && t < 100)
            res = (findNewArea(c));
        if (res.d == -1)
            res = (drowArea(c));
        paint(c, res);
        return res;
    }

    void solve() {
        rep(i, M) {
            commands[i] = solve(i % 4, i);
        }
    }

    array<Command, M> answer() {
        return commands;
    }

    void print() {
        rep(i, N) {
            rep(j, N) cout << color[i][j] << ' ';
            cout << endl;
        }
        cout << endl;
    }
};

array<Command, M> solve() {
    clock_t st, en;
    st = clock();
    en = clock();
    array<Command, M> res;
    int max = 0;
    while ((double)(en - st) / CLOCKS_PER_SEC < 1.8) {
        State state;
        state.solve();
        if (chmax(max, state.score()))
            res = state.answer();
        en = clock();
    }
    cerr << max << endl;
    return res;
}

int main(void) {
    int tmp;
    cin >> tmp >> tmp;

    rep(i, N) rep(j, N) cin >> board[i][j];
    auto ans = solve();
    for (auto i : ans) i.print();

    return 0;
}
