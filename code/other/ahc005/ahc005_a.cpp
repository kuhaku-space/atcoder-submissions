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
#include <random>
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

int N, M, K, SX, SY, ST;
int MAX_SCORE = 0;
vector<string> board;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
string op = "DURL";
vector<tuple<int, int, int, int>> edges;
vector<pair<int, int>> vertexs;
vector<int> indexs;
vector<vector<pair<int, string>>> dp;

inline bool in_board(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N && board[x][y] != '#';
}

bool in_edge(int x, int y, int e) {
    auto [sx, sy, gx, gy] = edges[e];
    return x >= sx && x <= gx && y >= sy && y <= gy;
}

inline int to_line(int x, int y) {
    return x * N + y;
}

inline int to_line(pair<int, int> p) {
    return p.first * N + p.second;
}

inline pair<int, int> to_face(int p) {
    return {p / N, p % N};
}

vector<pair<int, string>> dijkstra(int st) {
    struct _edge {
        int to;
        int dist;
        string s;
        bool operator<(const _edge &rhs) const {
            return dist < rhs.dist;
        }
        bool operator>(const _edge &rhs) const {
            return rhs < *this;
        }
    };
    vector<pair<int, string>> dist(M, {INF, string()});
    priority_queue<_edge, vector<_edge>, greater<_edge>> p_que;
    dist[st] = pair<int, string>();
    p_que.push(_edge{st, 0, string()});
    while (!p_que.empty()) {
        auto [l, d, s] = p_que.top();
        int x = l / N, y = l % N;
        p_que.pop();
        if (dist[l].first < d)
            continue;
        rep(i, 4) {
            int nx = x + dx[i], ny = y + dy[i];
            if (!in_board(nx, ny))
                continue;
            int nl = to_line(nx, ny);
            if (chmin(dist[nl].first, d + board[nx][ny] - '0')) {
                dist[nl].second = s + op[i];
                p_que.push(_edge{nl, dist[nl].first, dist[nl].second});
            }
        }
    }
    vector<pair<int, string>> res;
    for (auto i : indexs) {
        res.emplace_back(dist[to_line(vertexs[i])]);
    }
    return res;
}

void build() {
    vertexs.emplace_back(SX, SY);
    rep(i, N) {
        rep(j, N) {
            if (!in_board(i, j))
                continue;
            ++MAX_SCORE;
            if (!((in_board(i + dx[0], j + dy[0]) || in_board(i + dx[1], j + dy[1])) &&
                  (in_board(i + dx[2], j + dy[2]) || in_board(i + dx[3], j + dy[3]))))
                continue;
            vertexs.emplace_back(i, j);
        }
    }

    rep(i, N) {
        rep(j, N) {
            if (in_board(i, j) && in_board(i, j + 1)) {
                int t = j;
                while (in_board(i, j))
                    ++j;
                edges.emplace_back(i, t, i, j - 1);
            }
        }
    }

    rep(j, N) {
        rep(i, N) {
            if (in_board(i, j) && in_board(i + 1, j)) {
                int t = i;
                while (in_board(i, j))
                    ++i;
                edges.emplace_back(t, j, i - 1, j);
            }
        }
    }
}

vector<int> solve() {
    vector<int> res(vertexs.size());
    vector<int> idxs(vertexs.size() + 1);
    iota(idxs.begin(), idxs.end(), 0);
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());
    rep(_, 5000) {
        vector<int> v;
        std::shuffle(idxs.begin() + 1, idxs.end(), engine);

        const int m = edges.size();
        vector<bool> used(m);
        for (auto idx : idxs) {
            auto p = vertexs[idx];
            bool f = false;
            rep(i, m) {
                if (in_edge(p.first, p.second, i) && !used[i]) {
                    f = true;
                    used[i] = true;
                }
            }

            if (f) {
                v.emplace_back(idx);
            }
        }

        if (v.size() < res.size())
            swap(res, v);
    }
    return res;
}

struct State {
    int pos;
    int cost;
    string ops;
    vector<bool> is_visit;

    State() : pos(0), cost(), ops(), is_visit(K) {
        is_visit[0] = true;
    }

    bool operator<(const State &rhs) const {
        return eval() < rhs.eval();
    }
    bool operator>(const State &rhs) const {
        return rhs < *this;
    }

    int eval() const {
        return -cost;
    }

    void update_score() {}

    void _place(int to) {
        is_visit[to] = true;
        auto p = dp[pos][to_line(vertexs[indexs[to]])];
        pos = to;
        cost += p.first;
        ops += p.second;
    }

    auto place(int to) const {
        // cerr << "! " << to << " " << c << endl;
        auto res(*this);
        res._place(to);
        return res;
    }

    auto answer() const {
        return ops;
    }
};

template <int BEAM_SIZE>
struct beam_search {
    auto solve() {
        array<State, BEAM_SIZE> cur, nxt;
        cur[0] = State();
        int cur_size = 1, nxt_size = 0;
        rep(t, K) {
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> eval_que;
            // cerr << cur[0].pos / N << "," << cur[0].pos % N << " " << cur[0].score << endl;
            nxt_size = 0;
            for (int i = 0; i < cur_size; ++i) {
                if (t == K - 1) {
                    cur[i].is_visit[0] = false;
                }
                rep(k, K) {
                    if (cur[i].is_visit[k])
                        continue;
                    auto &&s = cur[i].place(k);
                    int eval = s.eval();
                    if (nxt_size < BEAM_SIZE) {
                        nxt[nxt_size] = s;
                        eval_que.push({eval, nxt_size++});
                    } else if (eval > eval_que.top().first) {
                        int idx = eval_que.top().second;
                        eval_que.pop();
                        nxt[idx] = s;
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

        cerr << max_eval << " " << endl;
        return cur[idx].answer();
    }
};

constexpr double T0 = 1000, T1 = 10, TL = 2.95;

struct Xorshift {
    unsigned int x, y, z, w;

    Xorshift() {
        x = 123456789, y = 362436069, z = 521288629, w = 88675123;
    }

    unsigned int operator()() {
        unsigned int t = (x ^ (x << 11));
        x = y, y = z, z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }

    double rand_d() {
        return (double)(*this)() / (1LL << 32);
    }
};
Xorshift xor128;

struct two_opt {
    two_opt() {}

    double temperature(double t) {
        t /= TL;
        return pow(T0, 1.0 - t) * pow(T1, t);
    }

    int calc_score(const vector<int> &v) {
        int score = 0;
        int n = v.size();
        rep(i, n - 1) {
            score += dp[v[i]][v[i + 1]].first;
        }
        return score;
    }

    bool is_update(int diff_score, double temp) {
        if (diff_score <= 0)
            return true;
        return exp((double)-diff_score / temp) >= xor128.rand_d();
    }

    vector<int> solve(vector<int> v) {
        int score = calc_score(v);
        int n = v.size();

        while ((double)clock() / CLOCKS_PER_SEC < TL) {
            double t = (double)clock() / CLOCKS_PER_SEC;
            double temp = temperature(t);
            int x = xor128() % (n - 1);
            int y = xor128() % (n - 1);
            if (x == y)
                continue;
            if (x > y)
                swap(x, y);

            int diff = dp[v[x]][v[y + 1]].first + dp[v[y]][v[x + 1]].first - dp[v[x]][v[x + 1]].first -
                       dp[v[y]][v[y + 1]].first;
            if (is_update(diff, temp)) {
                score += diff;
                reverse(v.begin() + x + 1, v.begin() + y + 1);
            }
        }

        return v;
    }
};

string make_answer(vector<int> v) {
    string res;
    int n = v.size();
    rep(i, n - 1) {
        res += dp[v[i]][v[i + 1]].second;
    }
    return res;
}

int main(void) {
    cin >> N >> SX >> SY;
    M = N * N;
    ST = to_line(SX, SY);
    board.resize(N);
    for (auto &s : board)
        cin >> s;

    build();
    indexs = solve();
    K = indexs.size();
    dp.resize(K);
    rep(i, K) dp[i] = dijkstra(to_line(vertexs[indexs[i]]));
    cerr << vertexs.size() << " " << indexs.size() << endl;

    two_opt solver;
    vector<int> v(K);
    iota(v.begin(), v.end(), 0);
    v.emplace_back(0);
    auto ans = solver.solve(v);
    for (auto i : ans)
        cerr << i << " ";
    cout << make_answer(ans) << endl;

    return 0;
}
