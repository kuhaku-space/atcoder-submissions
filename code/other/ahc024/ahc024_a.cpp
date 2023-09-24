#ifndef LOCAL
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#endif

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>
#include <numeric>
#include <queue>
#include <random>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

using ll = std::int64_t;
#define FOR(i, m, n) for (int i = (m); i < (n); ++i)
#define rep(i, n) FOR (i, 0, n)
template <class T, class U>
constexpr bool chmax(T &a, const U &b) noexcept {
    return a < b ? a = b, true : false;
}
template <class T, class U>
constexpr bool chmin(T &a, const U &b) noexcept {
    return b < a ? a = b, true : false;
}
constexpr int Inf = 1000000003;
constexpr std::int64_t INF = 1000000000000000003;

constexpr int N = 50;
constexpr int M = 100;

struct UnionFind {
    array<int, N * N + 1> data;

    UnionFind() : data{} {
        data.fill(-1);
    }

    int is_root(int x) const {
        return data[x] < 0;
    }

    int root(int x) {
        return is_root(x) ? x : data[x] = root(data[x]);
    }

    int size(int x) {
        return -data[root(x)];
    }

    void unite(int x, int y) {
        x = root(x), y = root(y);
        if (x == y) return;
        if (data[x] > data[y]) swap(x, y);
        data[x] += data[y];
        data[y] = x;
    }
};

array<int, 4> dx = {1, -1, 0, 0}, dy = {0, 0, 1, -1};

struct Field {
    array<array<int, N>, N> color;
    array<bitset<M + 1>, M + 1> adjacent;
    array<int, M + 1> color_size;

    Field() : color{}, adjacent{}, color_size{} {}

    static bool in_field(int x, int y) {
        return 0 <= x && x < N && 0 <= y && y < N;
    }

    static bool is_edge(int x, int y) {
        return x == 0 || x == N - 1 || y == 0 || y == N - 1;
    }

    static int to_line(int x, int y) {
        return x * N + y;
    }

    const array<int, N> &operator[](int i) const {
        return color[i];
    }

    void build() {
        adjacent = array<bitset<M + 1>, M + 1>{};
        color_size = array<int, M + 1>{};
        adjacent[0][0] = true;
        for (int x = 0; x < N; ++x) {
            for (int y = 0; y < N; ++y) {
                color_size[color[x][y]]++;
                if (is_edge(x, y)) {
                    adjacent[0][color[x][y]] = true;
                    adjacent[color[x][y]][0] = true;
                }
                for (int k = 0; k < 4; ++k) {
                    int ax = x + dx[k], ay = y + dy[k];
                    if (!in_field(ax, ay)) continue;
                    adjacent[color[x][y]][color[ax][ay]] = true;
                    adjacent[color[ax][ay]][color[x][y]] = true;
                }
            }
        }
    }

    bool is_clear(int fx, int fy) {
        int c = color[fx][fy];
        if (c == 0 || color_size[c] == 1) return false;
        color[fx][fy] = 0;
        color_size[0]++;
        color_size[c]--;
        array<bitset<M + 1>, M + 1> local_adjacent{};
        UnionFind uf;
        for (int x = 0; x < N; ++x) {
            for (int y = 0; y < N; ++y) {
                if (is_edge(x, y)) {
                    local_adjacent[0][color[x][y]] = true;
                    local_adjacent[color[x][y]][0] = true;
                    if (color[x][y] == 0) uf.unite(to_line(x, y), N * N);
                }
                for (int k = 0; k < 4; ++k) {
                    int ax = x + dx[k], ay = y + dy[k];
                    if (!in_field(ax, ay)) continue;
                    if (color[x][y] == c && color[ax][ay] == c)
                        uf.unite(to_line(x, y), to_line(ax, ay));
                    if (color[x][y] == 0 && color[ax][ay] == 0)
                        uf.unite(to_line(x, y), to_line(ax, ay));
                    local_adjacent[color[x][y]][color[ax][ay]] = true;
                    local_adjacent[color[ax][ay]][color[x][y]] = true;
                }
            }
        }
        for (int x = 0; x < N; ++x) {
            for (int y = 0; y < N; ++y) {
                if (color[x][y] == c && uf.size(to_line(x, y)) != color_size[c]) {
                    color[fx][fy] = c;
                    color_size[0]--;
                    color_size[c]++;
                    return false;
                }
            }
        }

        color[fx][fy] = c;
        color_size[0]--;
        color_size[c]++;
        return adjacent == local_adjacent && uf.size(N * N) == color_size[0] + 2;
    }

    void clear(int x, int y) {
        int c = color[x][y];
        color[x][y] = 0;
        color_size[0]++;
        color_size[c]--;
    }

    bool is_change(int x, int y) {
        if (is_edge(x, y)) return false;
        int c = color[x][y];
        vector<int> dc;
        for (int k = 0; k < 4; ++k) {
            dc.emplace_back(color[x + dx[k]][y + dy[k]]);
        }
        unordered_map<int, int> mp;
        for (auto cc : dc) {
            ++mp[cc];
        }
        if (mp.size() != 2) return false;
        return mp.contains(c) && mp[c] == 1;
    }

    void change(int x, int y) {
        int c = color[x][y];
        vector<int> dc;
        for (int k = 0; k < 4; ++k) {
            dc.emplace_back(color[x + dx[k]][y + dy[k]]);
        }
        int nc = -1;
        for (auto cc : dc) {
            if (cc != c) nc = cc;
        }

        color[x][y] = nc;
        color_size[c]--;
        color_size[nc]++;
    }

    void input() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> color[i][j];
            }
        }
    }

    void output() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cout << color[i][j] << (j == N - 1 ? '\n' : ' ');
            }
        }
        cout << flush;
    }
};

struct Solver {
    Field field;

    Solver(const Field &_field) : field(_field) {}

    Field solve() {
        while ((double)clock() / CLOCKS_PER_SEC < 1.6) {
            for (int x = 0; x < N; ++x) {
                for (int y = 0; y < N; ++y) {
                    if (field.is_change(x, y)) field.change(x, y);
                }
            }
            field.build();
            for (int x = 0; x < N; ++x) {
                for (int y = 0; y < N; ++y) {
                    if (field.is_clear(x, y)) field.clear(x, y);
                }
            }
        }
        return field;
    }
};

int main(void) {
    int n, m;
    cin >> n >> m;
    Field field;
    field.input();
    field.build();
    Solver solver(field);
    auto answer = solver.solve();
    answer.output();

    return 0;
}
