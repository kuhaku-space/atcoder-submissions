#ifndef LOCAL
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#endif

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

constexpr int N = 40;
int E[N][N];

inline bool in_board(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N;
}

inline int dist(int a, int b, int c, int d) {
    return abs(a - c) + abs(b - d);
}

struct State {
    int score;
    array<array<int, N>, N> P;
    array<array<bool, N>, N> B, C;

    State() : score() {
        rep(i, N) rep(j, N) {
            P[i][j] = 0;
            B[i][j] = false;
            C[i][j] = false;
        }
    }

    bool operator<(const State &rhs) const {
        return eval() < rhs.eval();
    }
    bool operator>(const State &rhs) const {
        return rhs < *this;
    }

    int eval() const {
        return score;
    }

    int next_eval(int x, int y, int k) const {
        return score + E[x][y] * k;
    }

    void update_score(int x, int y, int k) {
        score += E[x][y] * k;
    }

    bool can_place(int x, int y, int k) {
        if (!k)
            return true;
        if (B[x][y])
            return false;
        for (int a = -k; a <= k; ++a) {
            int l = k - abs(a);
            for (int b = -l; b <= l; ++b) {
                if (in_board(x + a, y + b)) {
                    if (C[x + a][y + b])
                        return false;
                }
            }
        }
        return true;
    }

    void place(int x, int y, int k) {
        if (k) {
            P[x][y] = k;
            C[x][y] = true;
            for (int a = -k; a <= k; ++a) {
                int l = k - abs(a);
                for (int b = -l; b <= l; ++b) {
                    if (in_board(x + a, y + b)) {
                        B[x + a][y + b] = true;
                    }
                }
            }
            update_score(x, y, k);
        }
    }

    auto answer() const {
        return P;
    }

    void print_debug() {
        rep(i, N) {
            rep(j, N) cerr << B[i][j] << ' ';
            cerr << endl;
        }
    }
};

template <int BEAM_SIZE>
struct beam_search {
    auto solve() {
        vector<tuple<int, int, int>> v;
        rep(i, N) rep(j, N) v.emplace_back(E[i][j], i, j);
        sort(v.begin(), v.end());
        reverse(v.begin(), v.end());
        array<State, BEAM_SIZE> cur, nxt;
        cur[0] = State();
        int cur_size = 1, nxt_size = 0;
        for (int t = 0; t < N * N; ++t) {
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> eval_que;
            nxt_size = 0;
            for (int i = 0; i < cur_size; ++i) {
                auto [e, x, y] = v[t];
                for (int k = 0; k <= 6; ++k) {
                    if (!cur[i].can_place(x, y, k))
                        break;
                    // cerr << x << ' ' << y << ' ' << k << endl;
                    int eval = cur[i].next_eval(x, y, k);
                    if (nxt_size < BEAM_SIZE) {
                        nxt[nxt_size] = cur[i];
                        nxt[nxt_size].place(x, y, k);
                        eval_que.push({eval, nxt_size++});
                    } else if (eval > eval_que.top().first) {
                        int idx = eval_que.top().second;
                        eval_que.pop();
                        nxt[idx] = cur[i];
                        nxt[idx].place(x, y, k);
                        eval_que.push({eval, idx});
                    }
                }
            }
            swap(cur, nxt);
            cur_size = nxt_size;
        }

        int idx = 0, max_eval = cur[0].eval();
        for (int i = 1; i < cur_size; ++i) {
            if (chmax(max_eval, cur[i].eval()))
                idx = i;
        }
        cerr << max_eval << endl;
        return cur[idx].answer();
    }
};

int main(void) {
    int tmp;
    cin >> tmp;
    rep(i, N) rep(j, N) cin >> E[i][j];

    beam_search<600> solver;
    auto ans = solver.solve();
    rep(i, N) {
        rep(j, N) cout << ans[i][j] << ' ';
        cout << endl;
    }
}