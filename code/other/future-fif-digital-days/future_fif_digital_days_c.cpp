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

constexpr int N = 50;
constexpr int K = 100;
constexpr int B = 10;

constexpr bool in_board(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y < N;
}

struct Pos {
    int x, y;

    constexpr Pos() : x(), y() {}
    constexpr Pos(int _x, int _y) : x(_x), y(_y) {}

    constexpr Pos &operator+=(const Pos &rhs) noexcept {
        x += rhs.x, y += rhs.y;
        return *this;
    }
    constexpr Pos &operator-=(const Pos &rhs) noexcept {
        x -= rhs.x, y -= rhs.y;
        return *this;
    }

    constexpr Pos operator+(const Pos &rhs) const noexcept {
        return Pos(*this) += rhs;
    }
    constexpr Pos operator-(const Pos &rhs) const noexcept {
        return Pos(*this) -= rhs;
    }

    constexpr bool in_board() const {
        return 0 <= x && x < N && 0 <= y && y < N;
    }

    constexpr int dist(const Pos &rhs) const {
        return abs(x - rhs.x) + abs(y - rhs.y);
    }

    friend istream &operator>>(istream &is, Pos &rhs) {
        is >> rhs.x >> rhs.y;
        return is;
    }
};

struct Polyomino {
    int h, w, cost;
    vector<string> shape;
    vector<Pos> edges[4];  // (x=0,x=h-1,y=0,y=w-1)

    void build() {
        rep(i, 4) edges[i] = vector<Pos>();
        rep(y, w) {
            if (shape[0][y] == '#')
                edges[0].emplace_back(0, y);
            if (shape[h - 1][y] == '#')
                edges[1].emplace_back(h - 1, y);
        }
        rep(x, h) {
            if (shape[x][0] == '#')
                edges[2].emplace_back(x, 0);
            if (shape[x][w - 1] == '#')
                edges[3].emplace_back(x, w - 1);
        }
    }

    bool exists_block(int x, int y) const {
        return shape[x][y] == '#';
    }

    friend istream &operator>>(istream &is, Polyomino &rhs) {
        is >> rhs.h >> rhs.w >> rhs.cost;
        rhs.shape.resize(rhs.h);
        rep(i, rhs.h) cin >> rhs.shape[i];
        rhs.build();
        return is;
    }
};

struct Operation {
    int b, x, y;

    constexpr Operation() : b(), x(), y() {}
    constexpr Operation(int _b, int _x, int _y) : b(_b), x(_x), y(_y) {}

    friend ostream &operator<<(ostream &os, const Operation &rhs) {
        os << rhs.b + 1 << ' ' << rhs.x << ' ' << rhs.y;
        return os;
    }
};

array<Pos, K> marks;
array<Polyomino, B> polyominos;
array<Pos, 4> adjacent_pos = {Pos{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
bitset<K> mark_is_linked;
array<int, K> dist;
array<Pos, K> nearest_block;
array<bitset<N>, N> block_exists;
vector<Operation> operations;

constexpr bool exists_block(Pos pos) {
    return pos.in_board() && block_exists[pos.x][pos.y];
}

bool is_place_polyomino(const Polyomino &polyomino, Pos polyomino_pos) {
    rep(i, polyomino.h) {
        rep(j, polyomino.w) {
            Pos pos = polyomino_pos + Pos{i, j};
            if (!pos.in_board())
                return false;
            if (polyomino.exists_block(i, j) && exists_block(pos)) {
                return false;
            }
        }
    }
    return true;
}

Pos get_nearest_block(Pos mark_pos, const Polyomino &polyomino, Pos polyomino_pos) {
    int min_dist = INF;
    Pos res;
    rep(i, polyomino.h) {
        rep(j, polyomino.w) {
            if (polyomino.exists_block(i, j)) {
                Pos pos = polyomino_pos + Pos{i, j};
                if (chmin(min_dist, mark_pos.dist(pos)))
                    res = pos;
            }
        }
    }
    return res;
}

void update(Operation op) {
    operations.emplace_back(op);
    auto polyomino = polyominos[op.b];
    rep(i, polyomino.h) {
        rep(j, polyomino.w) {
            if (polyomino.exists_block(i, j)) {
                auto pos = Pos{op.x + i, op.y + j};
                assert(pos.in_board());
                block_exists[pos.x][pos.y] = true;
                rep(k, K) {
                    if (chmin(dist[k], marks[k].dist(pos))) {
                        nearest_block[k] = pos;
                        if (dist[k] == 0)
                            mark_is_linked[k] = true;
                    }
                }
            }
        }
    }
}

int main(void) {
    int t;
    cin >> t >> t >> t;
    rep(i, K) cin >> marks[i];
    rep(i, B) cin >> polyominos[i];

    rep(i, K) dist[i] = INF;

    Operation op{0, marks[0].x, marks[0].y};
    update(op);
    // int cnt = 0;
    while (!mark_is_linked.all()) {
        int idx = -1;
        int max_dist = 0;
        rep(i, K) {
            if (mark_is_linked[i])
                continue;
            if (chmax(max_dist, dist[i]))
                idx = i;
        }

        int min_dist = INF;
        Operation op;
        for (int i = B - 1; i >= 0; --i) {
            rep(k, 4) {
                Pos next_pos = nearest_block[idx] + adjacent_pos[k];
                if (!next_pos.in_board())
                    continue;
                for (auto standard_pos : polyominos[i].edges[k]) {
                    Pos polyomino_pos = next_pos - standard_pos;
                    if (is_place_polyomino(polyominos[i], polyomino_pos)) {
                        Pos pos = get_nearest_block(marks[idx], polyominos[i], polyomino_pos);
                        if (chmin(min_dist, marks[idx].dist(pos))) {
                            op = Operation{i, polyomino_pos.x, polyomino_pos.y};
                        }
                    }
                }
            }
            if (min_dist != INF)
                break;
        }
        // cerr << op << '\n';
        // break;

        update(op);
        // ++cnt;
    }

    cout << operations.size() << '\n';
    for (auto operation : operations) cout << operation << '\n';

    return 0;
}
