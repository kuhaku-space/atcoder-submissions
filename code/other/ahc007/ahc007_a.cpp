/**
 * @file main.cpp
 * @author kuhaku-space (kuhakuspace2000@gmail.com)
 * @brief AHC007 solution
 * @version 1.0
 * @date 2021-12-12
 * @details [問題](https://atcoder.jp/contests/ahc007/tasks/ahc007_a)
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef LOCAL
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#endif

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iostream>
#include <numeric>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;
#define FOR(i, m, n) for (int i = (m); i < (n); ++i)
#define rep(i, n) FOR (i, 0, n)

constexpr int N = 400;
constexpr int M = 1995;
array<int, N> x, y;
array<int, M> u, v;
array<int, M> d, l;
array<int, M> dmax, dmin;

int dist(int a, int b) {
    return round(sqrt(pow(x[a] - x[b], 2) + pow(y[a] - y[b], 2)));
}

// clang-format off

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

struct union_find {
    array<int, N> data;

    union_find() : data() {
        data.fill(-1);
    }

    int root(int x) { return this->data[x] < 0 ? x : this->data[x] = this->root(data[x]); }
    int get_root(int x) { return this->root(x); }

    bool is_root(int x) { return this->data[x] < 0; }

    bool unite(int x, int y) {
        x = this->root(x), y = this->root(y);
        if (x == y) return false;
        if (this->data[x] > this->data[y]) swap(x, y);
        this->data[x] += this->data[y];
        this->data[y] = x;
        return true;
    }

    int size(int x) { return -(this->data[this->root(x)]); }
    int get_size(int x) { return this->size(x); }

    bool same(int x, int y) { return this->root(x) == this->root(y); }
    bool is_same(int x, int y) { return this->same(x, y); }
};
// clang-format on

Xorshift rnd;

constexpr int TRY_TIME = 100;
array<array<int, M>, TRY_TIME> drand;

void set_drand() {
    rep (i, TRY_TIME) {
        rep (j, M) {
            drand[i][j] = dmin[j] + rnd() % (dmax[j] - dmin[j] + 1);
        }
    }
}

int main(void) {
    rep (i, N) cin >> x[i] >> y[i];
    rep (i, M) cin >> u[i] >> v[i];

    rep (i, M) {
        d[i] = dist(u[i], v[i]);
        dmax[i] = d[i] * 2.87, dmin[i] = d[i] * 1.13;
    }
    set_drand();

    array<int, M> cnt = {};
    rep (loop, TRY_TIME) {
        vector<pair<int, int>> ps;
        rep (i, M) {
            ps.emplace_back(drand[loop][i], i);
        }
        sort(ps.begin(), ps.end());
        union_find uf;
        for (auto p : ps) {
            if (uf.unite(u[p.second], v[p.second]))
                ++cnt[p.second];
        }
    }

    int score = 0;
    union_find uf;
    vector<int> idx;
    for (int i = M - 1; i >= 0; --i) {
        if (cnt[i] >= 1)
            idx.emplace_back(i);
    }
    rep (m, M) {
        cin >> l[m];
        if (idx.empty() || idx.back() != m) {
            cout << 0 << endl;
            continue;
        }
        idx.pop_back();
        int eval = 0;
        rep (loop, 25) {
            if (cnt[m] == TRY_TIME)
                break;

            vector<pair<int, int>> ps;
            for (auto i : idx) {
                ps.emplace_back(drand[loop][i], i);
            }
            sort(ps.begin(), ps.end());
            int score_a = score + l[m], score_b = score;
            union_find ufa = uf, ufb = uf;
            ufa.unite(u[m], v[m]);
            for (auto p : ps) {
                if (ufa.unite(u[p.second], v[p.second]))
                    score_a += p.first;
                if (ufb.unite(u[p.second], v[p.second]))
                    score_b += p.first;

                if (loop && ufa.size(u[m]) == ufb.size(u[m]))
                    break;
            }

            if (loop == 0 && ufb.size(0) != N) {
                eval = 1;
                break;
            }
            eval += score_b - score_a;
        }
        if (eval >= 0) {
            cout << 1 << endl;
            uf.unite(u[m], v[m]);
            idx.erase(remove_if(idx.begin(), idx.end(),
                                [&uf](int i) {
                                    return uf.same(u[i], v[i]);
                                }),
                      idx.end());
            score += l[m];
        } else {
            cout << 0 << endl;
        }
    }
    cerr << score << endl;

    return 0;
}
