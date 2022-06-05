/**
 * @file main.cpp
 * @author kuhaku-space
 * @brief
 * @version 0.1
 * @date 2021-11-14
 *
 * @copyright Copyright (c) 2021
 *
 */

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
#include <chrono>
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
constexpr int Inf = 1000000003;
constexpr ll INF = 1000000000000000003;
constexpr double PI = M_PI;

constexpr int N = 1000;

struct Position {
    int x, y;

    constexpr Position() : x(), y() {}
    constexpr Position(int _x, int _y) : x(_x), y(_y) {}

    friend ostream &operator<<(ostream &os, const Position &rhs) {
        return os << rhs.x + 400 << ' ' << rhs.y + 400;
    }
};

struct Xorshift {
    unsigned int x, y, z, w;

    constexpr Xorshift() : x(123456789), y(362436069), z(521288629), w(88675123) {}

    using result_type = unsigned int;
    constexpr result_type min() const {
        return numeric_limits<result_type>::min();
    }
    constexpr result_type max() const {
        return numeric_limits<result_type>::max();
    }
    result_type operator()() {
        result_type t = (x ^ (x << 11));
        x = y, y = z, z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }

    double rand_d() {
        return (double)this->operator()() / this->max();
    }
};

constexpr double T0 = 1e5, T1 = 1e2, TL = 1900;

Xorshift xor128;

// 焼きなまし法
struct annealing {
    chrono::system_clock::time_point st;

    annealing() : st(chrono::system_clock::now()){};

    double temperature() {
        auto en = chrono::system_clock::now();
        auto t = chrono::duration_cast<std::chrono::milliseconds>(en - st).count();
        t /= TL;
        return pow(T0, 1.0 - t) * pow(T1, t);
    }

    bool is_update(double diff_score, double temp) {
        if (diff_score >= 0)
            return true;
        return exp((double)diff_score / temp) >= xor128.rand_d();
    }
};

array<array<Position, 2>, N> task_pos;
array<array<double, 2>, N> task_angle;

int dist(const Position &a, const Position &b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

double dist2(const Position &a, const Position &b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void input() {
    for (int i = 0; i < N; ++i) {
        rep(j, 2) {
            cin >> task_pos[i][j].x >> task_pos[i][j].y;
            task_pos[i][j].x -= 400;
            task_pos[i][j].y -= 400;
        }
    }
}

void build() {
    rep(i, N) {
        rep(j, 2) task_angle[i][j] = atan2(task_pos[i][j].x, task_pos[i][j].y);
    }
}

constexpr bool ng(const array<array<int, 2>, N> &v, int a) {
    return v[a][0] > v[a][1];
}

constexpr int get_idx(int x) {
    return x >= 0 ? x : ~x;
}

constexpr int get_type(int x) {
    return 1 - (x >= 0);
}

constexpr Position get_pos(int x) {
    return task_pos[get_idx(x)][get_type(x)];
}

constexpr double get_angle(int x) {
    return task_angle[get_idx(x)][get_type(x)];
}

void output(const vector<int> &ans, const vector<Position> &pos) {
    cout << ans.size();
    for (auto i : ans) cout << ' ' << i + 1;
    cout << '\n';
    cout << pos.size();
    for (auto i : pos) cout << ' ' << i;
    cout << endl;

    if (ans.size() == 50) {
    } else {
        cerr << 0 << endl;
    }
}

double calc_score(double x) {
    return 100000000.0 / (1000 + x);
}

void NA(const vector<int> &ans) {
    auto st = chrono::system_clock::now();

    vector<int> ang;
    for (auto i : ans) {
        ang.emplace_back(i);
        ang.emplace_back(~i);
    }

    sort(ang.begin(), ang.end(), [&](auto a, auto b) {
        return get_angle(a) < get_angle(b);
    });

    vector<Position> pos;
    pos.emplace_back(0, 0);
    for (auto i : ang) {
        pos.emplace_back(get_pos(i));
    }
    pos.emplace_back(0, 0);

    array<array<int, 2>, N> task_order;
    rep(i, (int)ang.size()) {
        task_order[get_idx(ang[i])][get_type(ang[i])] = i;
    }

    vector<int> dists;
    rep(i, (int)pos.size() - 1) {
        dists.emplace_back(dist(pos[i], pos[i + 1]));
    }
    double dist_sum = accumulate(dists.begin(), dists.end(), 0.0);

    auto en = chrono::system_clock::now();
    Xorshift xor128;
    annealing an;
    while (chrono::duration_cast<std::chrono::milliseconds>(en - st).count() < 1900) {
        auto temp = an.temperature();
        rep(_, 100) {
            int x = int(xor128() % (100));
            int y = x + 1 + int(xor128() % 5);
            if (y >= 100)
                continue;
            auto xidx = get_idx(ang[x]);
            auto yidx = get_idx(ang[y]);
            auto xtype = get_type(ang[x]);
            auto ytype = get_type(ang[y]);
            swap(ang[x], ang[y]);
            swap(pos[x + 1], pos[y + 1]);
            swap(task_order[xidx][xtype], task_order[yidx][ytype]);
            if (ng(task_order, xidx) || ng(task_order, yidx)) {
                swap(ang[x], ang[y]);
                swap(pos[x + 1], pos[y + 1]);
                swap(task_order[xidx][xtype], task_order[yidx][ytype]);
                continue;
            }

            double prev_sum = 0;
            prev_sum += dists[x] + dists[x + 1];
            prev_sum += dists[y] + dists[y + 1];
            double next_sum = 0;
            next_sum += dist(pos[x], pos[x + 1]) + dist(pos[x + 1], pos[x + 2]);
            next_sum += dist(pos[y], pos[y + 1]) + dist(pos[y + 1], pos[y + 2]);
            if (an.is_update(next_sum - prev_sum, temp)) {
                dist_sum += next_sum - prev_sum;
                dists[x] = dist(pos[x], pos[x + 1]);
                dists[x + 1] = dist(pos[x + 1], pos[x + 2]);
                dists[y] = dist(pos[y], pos[y + 1]);
                dists[y + 1] = dist(pos[y + 1], pos[y + 2]);
            } else {
                swap(ang[x], ang[y]);
                swap(pos[x + 1], pos[y + 1]);
                swap(task_order[xidx][xtype], task_order[yidx][ytype]);
            }
        }

        en = chrono::system_clock::now();
    }

    assert(pos[0].x == 0 && pos[0].y == 0);
    rep(i, (int)ang.size()) {
        assert(pos[i + 1].x == task_pos[get_idx(ang[i])][get_type(ang[i])].x &&
               pos[i + 1].y == task_pos[get_idx(ang[i])][get_type(ang[i])].y);
    }
    assert(pos[101].x == 0 && pos[101].y == 0);
    for (auto i : ans) {
        if (ng(task_order, i))
            cerr << i << ' ' << task_order[i][0] << ' ' << task_order[i][1] << '\n';
        assert(!ng(task_order, i));
    }
    cerr << int(round(100000000.0 / (1000 + accumulate(dists.begin(), dists.end(), 0)))) << endl;
    output(ans, pos);
}

void solve() {
    auto office_pos = Position(0, 0);
    vector<pair<double, int>> idx;
    rep(i, N) {
        if (task_angle[i][0] >= task_angle[i][1])
            continue;
        // if (abs(start_angle[i]) >= 1.5 || abs(finish_angle[i]) >= 1.5)
        //     continue;
        // double x = 1 - abs(start_angle[i]) / PI;
        // double y = 1 - abs(finish_angle[i]) / PI;
        // idx.emplace_back(pow((240 + 120 * x) - dist2(office_pos, start[i]), 2) +
        //                      pow((240 + 120 * y) - dist2(office_pos, finish[i]), 2),
        //                  i);
        idx.emplace_back(pow((340) - dist2(office_pos, task_pos[i][0]), 2) +
                             pow((340) - dist2(office_pos, task_pos[i][1]), 2),
                         i);
    }
    sort(idx.begin(), idx.end());

    vector<int> ans;
    rep(i, 50) ans.emplace_back(idx[i].second);
    NA(ans);
}

int main(void) {
    input();
    build();
    solve();

    return 0;
}
