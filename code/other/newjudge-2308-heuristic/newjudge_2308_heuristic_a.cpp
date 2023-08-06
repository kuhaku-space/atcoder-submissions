#ifndef LOCAL
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#endif

#include <array>
#include <chrono>
#include <cmath>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;
using ll = int64_t;
#define FOR(i, m, n) for (int i = (m); i < (n); ++i)
#define rep(i, n) FOR (i, 0, n)
template <class T, class U>
bool chmax(T &a, const U &b) {
    return a < b ? a = b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U &b) {
    return b < a ? a = b, true : false;
}

constexpr int D = 365;
array<int, 26> C;
array<int, 26> prev_day;
int SUM = 0;

int main(void) {
    fill(prev_day.begin(), prev_day.end(), -1);
    int d;
    cin >> d;
    rep (i, 26) cin >> C[i];
    rep (i, 26) SUM += C[i];
    rep (cur_day, D) {
        int idx = 0, max_score = 0;
        rep (i, 26) {
            int S;
            cin >> S;
            if (chmax(max_score, S + 13L * C[i] * (cur_day - prev_day[i])))
                idx = i;
        }
        cout << idx + 1 << endl;
        prev_day[idx] = cur_day;
    }

    return 0;
}
