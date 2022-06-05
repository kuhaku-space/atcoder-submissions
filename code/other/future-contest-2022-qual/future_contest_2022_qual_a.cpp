/**
 * @file a.cpp
 * @author kuhaku-space
 * @brief
 * @version 0.1
 * @date 2021-11-03
 * @ref https://atcoder.jp/contests/future-contest-2022-qual/tasks/future_contest_2022_qual_a "問題"
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
#include <bitset>
#include <cassert>
#include <cmath>
#include <deque>
#include <fstream>
#include <iostream>
#include <numeric>
#include <set>
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

constexpr int N = 1000, M = 20;
int K, R;
array<vector<int>, N> task_skill;
array<vector<int>, N> G, H;

array<vector<int>, M> member_skill, member_min_skill;
array<vector<pair<int, int>>, M> task_arr;
array<double, N> expected_time;

void input() {
    int tmp;
    cin >> tmp >> tmp >> K >> R;
    for (int i = 0; i < N; ++i) {
        task_skill[i].resize(K);
        for (int j = 0; j < K; ++j) cin >> task_skill[i][j];
        G[i].clear();
    }
    int u, v;
    for (int i = 0; i < R; ++i) {
        cin >> u >> v;
        G[v - 1].emplace_back(u - 1);
        H[u - 1].emplace_back(v - 1);
    }
}

void init_expected_time() {
    array<int, N> skill_sum;
    for (int i = 0; i < N; ++i) {
        skill_sum[i] = accumulate(task_skill[i].begin(), task_skill[i].end(), 0);
        expected_time[i] = skill_sum[i];
    }
    for (int i = N - 1; i >= 0; --i) {
        for (auto idx : G[i]) {
            chmax(expected_time[idx], expected_time[i] + skill_sum[idx]);
        }
    }
}

void init_member_skill() {
    for (int i = 0; i < M; ++i) {
        member_skill[i].assign(K, 0);
        member_min_skill[i].assign(K, 0);
        task_arr[i].clear();
    }
}

int calc_time(int member_idx, int task_idx) {
    int sum_diff = 0;
    for (int i = 0; i < K; ++i) {
        sum_diff += max(0, task_skill[task_idx][i] - member_skill[member_idx][i]);
    }
    return sum_diff;
}

int calc_min_time(int task_idx) {
    int min_time = Inf;
    for (int i = 0; i < M; ++i) {
        chmin(min_time, calc_time(i, task_idx));
    }
    return min_time;
}

int calc_min_time(int task_idx, int my_idx) {
    int min_time = Inf;
    for (int i = 0; i < M; ++i) {
        if (i == my_idx)
            continue;
        chmin(min_time, calc_time(i, task_idx));
    }
    return min_time;
}

double calc_mean_time(int task_idx) {
    double sum_time = 0;
    for (int i = 0; i < M; ++i) {
        sum_time += calc_time(i, task_idx);
    }
    return sum_time / M;
}

void update_expected_time() {
    array<double, N> mean_time;
    for (int i = 0; i < N; ++i) {
        mean_time[i] = calc_mean_time(i);
        expected_time[i] = mean_time[i];
    }
    for (int i = N - 1; i >= 0; --i) {
        for (auto idx : G[i]) {
            chmax(expected_time[idx], expected_time[i] + mean_time[idx]);
        }
    }
}

bool is_active_task(int task_idx, bitset<N> &finished_task) {
    for (auto idx : G[task_idx]) {
        if (!finished_task[idx])
            return false;
    }
    return true;
}

double calc_score(int member_idx, int task_idx) {
    return expected_time[task_idx] -
           0.9 * pow(double(calc_time(member_idx, task_idx) - calc_min_time(task_idx)), 2.1);
}

int get_max_task(int member_idx, set<int> &free_task) {
    double max_score = -Inf;
    int max_idx = -1;
    for (auto task_idx : free_task) {
        if (chmax(max_score, calc_score(member_idx, task_idx)))
            max_idx = task_idx;
    }
    return max_idx;
}

void sort_member_arr(array<int, M> &member_arr) {
    sort(member_arr.begin(), member_arr.end(), [&](auto a, auto b) {
        return accumulate(member_skill[a].begin(), member_skill[a].end(), 0) >
               accumulate(member_skill[b].begin(), member_skill[b].end(), 0);
    });
}

void predict_skill(int member_idx) {
    while (true) {
        double max_score = 0;
        int max_idx = -1;
        for (int i = 0; i < K; ++i) {
            int ok = 0, ng = 0;
            for (auto [task_idx, score_diff] : task_arr[member_idx]) {
                int score_sum = 0;
                for (int j = 0; j < K; ++j) {
                    score_sum += max(0, task_skill[task_idx][j] - member_skill[member_idx][j]);
                }
                if (task_skill[task_idx][i] > member_skill[member_idx][i]) {
                    if (score_sum > score_diff)
                        ++ok;
                    else
                        ++ng;
                }
            }
            if (chmax(max_score, (double)(ok) / (ok + ng) * 50 + ok)) {
                max_idx = i;
            }
        }
        if (max_idx == -1)
            break;
        ++member_skill[member_idx][max_idx];
    }
}

void update_skill(int member_idx, int task_idx, int skill_diff) {
    task_arr[member_idx].emplace_back(task_idx, skill_diff);
    for (int i = 0; i < K; ++i) {
        chmax(member_min_skill[member_idx][i], task_skill[task_idx][i] - skill_diff - 1);
        member_skill[member_idx][i] = member_min_skill[member_idx][i];
    }
    predict_skill(member_idx);
}

void print_debug(const int member_idx) {
    cout << "#s " << member_idx + 1;
    for (int i = 0; i < K; ++i) {
        cout << ' ' << member_skill[member_idx][i];
    }
    cout << endl;
}

void print(const vector<pair<int, int>> &commands, int turn,
           array<pair<int, int>, M> &member_task) {
    cout << commands.size();
    for (auto [a, b] : commands) {
        member_task[a] = {b, turn};
        cout << ' ' << a + 1 << ' ' << b + 1;
    }
    cout << endl;
}

void print_score(int turn, int task_count) {
    ofstream ofs("score.txt", ios_base::app);
    if (turn == 2000) {
        ofs << task_count << endl;
    } else {
        ofs << 2000 + N - turn << endl;
    }
}

void solve() {
    init_expected_time();
    init_member_skill();
    bitset<N> finished_task;
    array<pair<int, int>, M> member_task;
    member_task.fill({-1, -1});
    set<int> free_task;
    for (int i = 0; i < N; ++i) {
        if (G[i].empty())
            free_task.emplace(i);
    }
    array<int, M> member_arr;
    iota(member_arr.begin(), member_arr.end(), 0);
    for (int turn = 1; true; ++turn) {
        vector<pair<int, int>> commands;
        for (auto member_idx : member_arr) {
            if (member_task[member_idx].first != -1)
                continue;
            int task_idx = get_max_task(member_idx, free_task);
            if (task_idx != -1) {
                commands.emplace_back(member_idx, task_idx);
                free_task.erase(task_idx);
            }
        }

        print(commands, turn, member_task);

        int n;
        cin >> n;
        if (n == -1) {
            print_score(turn, finished_task.count());
            return;
        }
        for (int _ = 0; _ < n; ++_) {
            int member_idx;
            cin >> member_idx;
            --member_idx;
            auto [task_idx, begin_turn] = member_task[member_idx];
            finished_task[task_idx] = true;
            member_task[member_idx] = {-1, -1};
            for (auto idx : H[task_idx]) {
                if (is_active_task(idx, finished_task))
                    free_task.emplace(idx);
            }
            update_skill(member_idx, task_idx, turn - begin_turn);
            print_debug(member_idx);
        }

        sort_member_arr(member_arr);
        update_expected_time();
    }
}

int main(void) {
    input();
    solve();
    return 0;
}
