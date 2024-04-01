#include <algorithm>
#include <array>
#include <bit>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <numeric>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

namespace lib {
// clang-format off

constexpr int inf = 1000000000;

template <class T, class U>
constexpr bool chmax(T &a, const U &b) {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
constexpr bool chmin(T &a, const U &b) {
    return (T)b < a ? a = (T)b, true : false;
}

struct Position {
    int x, y;

    constexpr Position() : x(), y() {}
    constexpr Position(int _x, int _y) : x(_x), y(_y) {}

    constexpr Position &operator+=(const Position &rhs) {
        this->x += rhs.x, this->y += rhs.y;
        return *this;
    }
    constexpr Position &operator-=(const Position &rhs) {
        this->x -= rhs.x, this->y -= rhs.y;
        return *this;
    }

    constexpr Position operator+(const Position &rhs) const { return Position(*this) += rhs; }
    constexpr Position operator-(const Position &rhs) const { return Position(*this) -= rhs; }

    constexpr bool operator==(const Position &rhs) const{ return x == rhs.x && y == rhs.y; }
    constexpr bool operator<(const Position &rhs) const{ return x == rhs.x ? y < rhs.y : x < rhs.x; }

    friend std::ostream &operator<<(std::ostream &os, const Position &rhs) {
        return os << rhs.x << ' ' << rhs.y;
    }

    int dist(const Position &rhs) const { return abs(x - rhs.x) + abs(y - rhs.y); }
};

template <class T>
struct Trace {
    int size() const { return log.size(); }

    int push(T operation, int prev_idx) {
        log.emplace_back(operation, prev_idx);
        return log.size() - 1;
    }

    std::pair<T, int> get(int idx) const { return log[idx]; }

    std::vector<T> chain(int idx, int root = -1) const {
        std::vector<T> res;
        while (idx != root) {
            res.emplace_back(log[idx].first);
            idx = log[idx].second;
        }
        std::reverse(res.begin(), res.end());
        return res;
    }

  private:
    std::vector<std::pair<T, int>> log;
};

struct Xorshift {
    using state_type = std::array<std::uint32_t, 4>;
    using result_type = std::uint32_t;
    constexpr Xorshift() : state{123456789, 362436069, 521288629, 88675123} {}

    static constexpr result_type min() { return std::numeric_limits<result_type>::min(); }
    static constexpr result_type max() { return std::numeric_limits<result_type>::max(); }
    result_type operator()() {
        std::uint32_t t = (state[0] ^ (state[0] << 11));
        state[0] = state[1], state[1] = state[2], state[2] = state[3];
        return state[3] = (state[3] ^ (state[3] >> 19)) ^ (t ^ (t >> 8));
    }
    bool operator==(const Xorshift &rhs) noexcept { return (state == rhs.state); }
    bool operator!=(const Xorshift &rhs) noexcept { return (state != rhs.state); }

    constexpr state_type serialize() const noexcept { return state; }
    constexpr void deserialize(const state_type &data) noexcept { state = data; }
    constexpr void deserialize(state_type &&data) noexcept { state = std::move(data); }

  private:
    state_type state;
};
Xorshift xorshift;

// clang-format on
}  // namespace lib
using namespace lib;

constexpr int W = 1000;
int D, N;

struct Reservation {
    vector<int> areas;

    Reservation() : areas(N) {}
};

struct Rectangle {
    Position tl_vertex, br_vertex;

    Rectangle() {}
    Rectangle(Position tl, Position br) : tl_vertex(tl), br_vertex(br) {}
    Rectangle(int tlx, int tly, int brx, int bry) : tl_vertex(tlx, tly), br_vertex(brx, bry) {}

    int area() const {
        return (br_vertex.x - tl_vertex.x) * (br_vertex.y - tl_vertex.y);
    }

    int height() const {
        return (br_vertex.x - tl_vertex.x);
    }

    int width() const {
        return (br_vertex.y - tl_vertex.y);
    }

    bool is_landscape() const {
        return height() < width();
    }

    friend std::ostream &operator<<(std::ostream &os, const Rectangle &rhs) {
        return os << rhs.tl_vertex.x << ' ' << rhs.tl_vertex.y << ' ' << rhs.br_vertex.x << ' '
                  << rhs.br_vertex.y;
    }
};

namespace internal {

pair<vector<tuple<int, int, int>>, vector<tuple<int, int, int>>> calc_partitions(
    const vector<Rectangle> &rectangles) {
    vector<tuple<int, int, int>> vx, vy;
    for (const Rectangle &rectangle : rectangles) {
        auto [tlx, tly] = rectangle.tl_vertex;
        auto [brx, bry] = rectangle.br_vertex;
        if (tlx != 0) vx.emplace_back(tlx, tly, bry);
        if (brx != W) vx.emplace_back(brx, tly, bry);
        if (tly != 0) vy.emplace_back(tly, tlx, brx);
        if (bry != W) vy.emplace_back(bry, tlx, brx);
    }
    sort(vx.begin(), vx.end());
    sort(vy.begin(), vy.end());
    vector<tuple<int, int, int>> ax, ay;
    for (int loop = 0; loop < 2; ++loop) {
        for (auto [x2, l2, r2] : vx) {
            if (ax.empty()) {
                ax.emplace_back(x2, l2, r2);
            } else {
                auto &[x1, l1, r1] = ax.back();
                if (x1 != x2) ax.emplace_back(x2, l2, r2);
                else if (r1 < l2) ax.emplace_back(x2, l2, r2);
                else if (r1 < r2) r1 = r2;
            }
        }
        swap(vx, vy);
        swap(ax, ay);
    }
    return {ax, ay};
}

int64_t calc_score(const vector<vector<Rectangle>> &answer,
                   const vector<Reservation> &reservations) {
    vector<tuple<int, int, int>> partition_x, partition_y;
    int64_t res = 0;
    for (int d = 0; d < D; ++d) {
        for (int i = 0; i < N; ++i) {
            res += max(0, reservations[d].areas[i] - answer[d][i].area()) * 100;
        }
        auto [vx, vy] = calc_partitions(answer[d]);
        auto px = vx, py = vy;
        if (d != 0) {
            for (int loop = 0; loop < 2; ++loop) {
                int idx1 = 0, idx2 = 0;
                while (idx1 < (int)partition_x.size() || idx2 < (int)vx.size()) {
                    if (idx1 == (int)partition_x.size()) {
                        auto [x, l, r] = vx[idx2];
                        res += r - l, ++idx2;
                    } else if (idx2 == (int)vx.size()) {
                        auto [x, l, r] = partition_x[idx1];
                        res += r - l, ++idx1;
                    } else {
                        auto &[x1, l1, r1] = partition_x[idx1];
                        auto &[x2, l2, r2] = vx[idx2];
                        if (x1 < x2) res += r1 - l1, ++idx1;
                        else if (x2 < x1) res += r2 - l2, ++idx2;
                        else if (r1 <= l2) res += r1 - l1, ++idx1;
                        else if (r2 <= l1) res += r2 - l2, ++idx2;
                        else if (l1 < l2) res += l2 - l1, l2 = l1;
                        else if (l2 < l1) res += l1 - l2, l1 = l2;
                        else if (r1 < r2) l2 = r1, ++idx1;
                        else if (r2 < r1) l1 = r2, ++idx2;
                        else ++idx1, ++idx2;
                    }
                }
                swap(partition_x, partition_y);
                swap(vx, vy);
            }
        }
        partition_x = px, partition_y = py;
    }
    return res + 1;
}

}  // namespace internal

struct Solver {
    const vector<Reservation> &reservations;

    Solver(const vector<Reservation> &reservations) : reservations(reservations) {}

    int64_t calc_score(const vector<Rectangle> &rectangles) {
        vector<Position> vx, vy;
        for (const Rectangle &rectangle : rectangles) {
            auto [tlx, tly] = rectangle.tl_vertex;
            auto [brx, bry] = rectangle.br_vertex;
            if (tlx != 0) {
                for (int y = tly; y < bry; ++y) vx.emplace_back(tlx, y);
            }
            if (brx != W) {
                for (int y = tly; y < bry; ++y) vx.emplace_back(brx, y);
            }
            if (tly != 0) {
                for (int x = tlx; x < brx; ++x) vy.emplace_back(x, tly);
            }
            if (bry != W) {
                for (int x = tlx; x < brx; ++x) vy.emplace_back(x, bry);
            }
        }
        sort(vx.begin(), vx.end());
        sort(vy.begin(), vy.end());
        vx.erase(unique(vx.begin(), vx.end()), vx.end());
        vy.erase(unique(vy.begin(), vy.end()), vy.end());
        return vx.size() + vy.size();
    }

    pair<vector<tuple<int, int, int>>, vector<tuple<int, int, int>>> calc_partitions(
        const vector<Rectangle> &rectangles) {
        vector<tuple<int, int, int>> vx, vy;
        for (const Rectangle &rectangle : rectangles) {
            auto [tlx, tly] = rectangle.tl_vertex;
            auto [brx, bry] = rectangle.br_vertex;
            if (tlx != 0) vx.emplace_back(tlx, tly, bry);
            if (brx != W) vx.emplace_back(brx, tly, bry);
            if (tly != 0) vy.emplace_back(tly, tlx, brx);
            if (bry != W) vy.emplace_back(bry, tlx, brx);
        }
        sort(vx.begin(), vx.end());
        sort(vy.begin(), vy.end());
        vector<tuple<int, int, int>> ax, ay;
        for (int loop = 0; loop < 2; ++loop) {
            for (auto [x2, l2, r2] : vx) {
                if (ax.empty()) {
                    ax.emplace_back(x2, l2, r2);
                } else {
                    auto &[x1, l1, r1] = ax.back();
                    if (x1 != x2) ax.emplace_back(x2, l2, r2);
                    else if (r1 < l2) ax.emplace_back(x2, l2, r2);
                    else if (r1 < r2) r1 = r2;
                }
            }
            swap(vx, vy);
            swap(ax, ay);
        }
        return {ax, ay};
    }

    int64_t calc_score(const vector<vector<Rectangle>> &answer) {
        vector<tuple<int, int, int>> partition_x, partition_y;
        int64_t res = 0;
        for (int d = 0; d < D; ++d) {
            for (int i = 0; i < N; ++i) {
                res += max(0, reservations[d].areas[i] - answer[d][i].area()) * 100;
            }
            auto [vx, vy] = calc_partitions(answer[d]);
            auto px = vx, py = vy;
            if (d != 0) {
                for (int loop = 0; loop < 2; ++loop) {
                    int idx1 = 0, idx2 = 0;
                    while (idx1 < (int)partition_x.size() || idx2 < (int)vx.size()) {
                        if (idx1 == (int)partition_x.size()) {
                            auto [x, l, r] = vx[idx2];
                            res += r - l, ++idx2;
                        } else if (idx2 == (int)vx.size()) {
                            auto [x, l, r] = partition_x[idx1];
                            res += r - l, ++idx1;
                        } else {
                            auto &[x1, l1, r1] = partition_x[idx1];
                            auto &[x2, l2, r2] = vx[idx2];
                            if (x1 < x2) res += r1 - l1, ++idx1;
                            else if (x2 < x1) res += r2 - l2, ++idx2;
                            else if (r1 <= l2) res += r1 - l1, ++idx1;
                            else if (r2 <= l1) res += r2 - l2, ++idx2;
                            else if (l1 < l2) res += l2 - l1, l2 = l1;
                            else if (l2 < l1) res += l1 - l2, l1 = l2;
                            else if (r1 < r2) l2 = r1, ++idx1;
                            else if (r2 < r1) l1 = r2, ++idx2;
                            else ++idx1, ++idx2;
                        }
                    }
                    swap(partition_x, partition_y);
                    swap(vx, vy);
                }
            }
            partition_x = px, partition_y = py;
        }
        return res + 1;
    }

    bool solve_zero_cost(vector<vector<Rectangle>> &answer) {
        vector<int> v(N);
        for (int d = 0; d < D; ++d) {
            for (int i = 0; i < N; ++i) chmax(v[i], reservations[d].areas[i]);
        }
        if (accumulate(v.begin(), v.end(), 0) > W * W) return false;

        vector<Rectangle> rectangles(N);
        vector<int> candidate(N);
        iota(candidate.begin(), candidate.end(), 0);
        Position limit(W, W);
        for (int i = 0; i < N; ++i) {
            int min_r = W * W;
            int min_idx = -1;
            int min_dir = -1;
            for (int idx : candidate) {
                int x = (v[idx] - 1) / limit.y + 1;
                int y = (v[idx] - 1) / limit.x + 1;
                if (x <= limit.x && chmin(min_r, x * limit.y - v[idx])) min_idx = idx, min_dir = 0;
                if (y <= limit.y && chmin(min_r, y * limit.x - v[idx])) min_idx = idx, min_dir = 1;
            }
            if (min_idx == -1) break;
            if (i == N - 1) {
                rectangles[min_idx] = Rectangle{Position(0, 0), limit};
                candidate.pop_back();
                break;
            }
            int x = (v[min_idx] + limit.y - 1) / limit.y;
            int y = (v[min_idx] + limit.x - 1) / limit.x;
            if (min_dir == 0) {
                rectangles[min_idx] = Rectangle{Position(limit.x - x, 0), limit};
                limit.x -= x;
            } else {
                rectangles[min_idx] = Rectangle{Position(0, limit.y - y), limit};
                limit.y -= y;
            }
            int idx = find(candidate.begin(), candidate.end(), min_idx) - candidate.begin();
            swap(candidate[idx], candidate.back());
            candidate.pop_back();
        }

        if (!candidate.empty()) return false;
        for (int d = 0; d < D; ++d) answer[d] = rectangles;
        return true;
    }

    template <int C, std::enable_if_t<(2 <= C)> * = nullptr>
    void solve_column(vector<vector<Rectangle>> &answer, int &score) {
        vector<vector<Rectangle>> tmp(D, vector<Rectangle>(N));
        if (solve_column_ordinarily_detail<C>(tmp)) {
            if (chmin(score, calc_score(tmp))) answer = tmp;
        }
        if (solve_column_inexpensively_detail<C>(tmp)) {
            if (chmin(score, calc_score(tmp))) answer = tmp;
        }
        int tmp_score = inf;
        if constexpr (C - 1 >= 2) {
            solve_column<C - 1>(tmp, tmp_score);
            if (chmin(score, tmp_score)) answer = tmp;
        }
    }

    template <int C>
    bool solve_column_ordinarily_detail(vector<vector<Rectangle>> &answer) {
        if (N < C) return false;
        int max_area = 0;
        for (int d = 0; d < D; ++d) {
            chmax(max_area, reservations[d].areas.back());
        }
        for (int d = 0; d < D; ++d) {
            vector<int> w;
            w.emplace_back(0);
            if ((max_area - 1) / W + 1 > W / C) w.emplace_back((max_area - 1) / W + 1);
            else w.emplace_back(W / C);

            int r = W - w.back();
            for (int i = 1; i < C; ++i) w.emplace_back(w[1] + r * i / (C - 1));

            vector<int> column(N, -1);
            array<int, C> column_sum = {};
            array<int, C> column_size = {};
            for (int i = N - 1; i >= 0; --i) {
                for (int c = 0; c < C; ++c) {
                    int x = (reservations[d].areas[i] - 1) / (w[c + 1] - w[c]) + 1;
                    if (column_sum[c] + x <= W) {
                        column[i] = c;
                        column_sum[c] += x;
                        ++column_size[c];
                        break;
                    }
                }
            }
            if (find(column.begin(), column.end(), -1) != column.end()) return false;
            for (int c = C - 1; c >= 0; --c) {
                if (column_size[c] != 0) continue;
                for (int i = 0; i < N; ++i) {
                    if (column_size[column[i]] <= 1) continue;
                    --column_size[column[i]];
                    ++column_size[c];
                    column[i] = c;
                    break;
                }
            }
            column_sum.fill(0);
            for (int i = 0; i < N; ++i) {
                for (int c = 0; c < C; ++c) {
                    if (column[i] == c) {
                        int x = (reservations[d].areas[i] - 1) / (w[c + 1] - w[c]) + 1;
                        answer[d][i] = Rectangle(Position(column_sum[c], w[c]),
                                                 Position(column_sum[c] + x, w[c + 1]));
                        column_sum[c] += x;
                    }
                }
            }
            array<bool, C> last;
            last.fill(true);
            for (int i = N - 1; i >= 0; --i) {
                for (int c = 0; c < C; ++c) {
                    if (column[i] == c && last[c]) {
                        answer[d][i].br_vertex.x = W;
                        last[c] = false;
                    }
                }
            }
        }
        return true;
    }

    template <int C>
    bool solve_column_inexpensively_detail(vector<vector<Rectangle>> &answer) {
        if (N < C) return false;
        int max_area = 0;
        for (int d = 0; d < D; ++d) chmax(max_area, reservations[d].areas.back());

        for (int d = 0; d < D; ++d) {
            vector<int> w;
            w.emplace_back(0);
            if ((max_area - 1) / W + 1 > W / C) w.emplace_back((max_area - 1) / W + 1);
            else w.emplace_back(W / C);
            int r = W - w.back();
            for (int i = 1; i < C; ++i) w.emplace_back(w[1] + r * i / (C - 1));

            array<Rectangle, C> rest;
            for (int i = 0; i < C; ++i) rest[i] = Rectangle(0, w[i], W, w[i + 1]);

            vector<int> column(N, -1);
            array<int, C> column_size = {};
            for (int i = N - 1; i >= 0; --i) {
                int s = reservations[d].areas[i];
                for (int c = 0; c < C; ++c) {
                    if (rest[c].area() < s) continue;
                    if (rest[c].is_landscape()) {
                        int h = rest[c].height();
                        int w = (s - 1) / h + 1;
                        rest[c].br_vertex.y -= w;
                    } else {
                        int w = rest[c].width();
                        int h = (s - 1) / w + 1;
                        rest[c].br_vertex.x -= h;
                    }
                    column[i] = c;
                    ++column_size[c];
                    break;
                }
            }
            if (find(column.begin(), column.end(), -1) != column.end()) return false;
            for (int c = C - 1; c >= 0; --c) {
                if (column_size[c] != 0) continue;
                for (int i = 0; i < N; ++i) {
                    assert(column_size[column[i]] > 0);
                    if (column_size[column[i]] == 1) continue;
                    if (rest[c].area() < reservations[d].areas[i]) continue;
                    --column_size[column[i]];
                    ++column_size[c];
                    column[i] = c;
                    break;
                }
            }

            for (int i = 0; i < C; ++i) rest[i] = Rectangle(0, w[i], W, w[i + 1]);
            array<int, C> last;
            last.fill(-1);
            for (int i = N - 1; i >= 0; --i) {
                int c = column[i];
                int s = reservations[d].areas[i];
                auto &[tlx, tly] = rest[c].tl_vertex;
                auto &[brx, bry] = rest[c].br_vertex;
                if (rest[c].is_landscape()) {
                    int h = rest[c].height();
                    int w = (s - 1) / h + 1;
                    answer[d][i] = Rectangle(tlx, bry - w, brx, bry);
                    bry -= w;
                } else {
                    int w = rest[c].width();
                    int h = (s - 1) / w + 1;
                    answer[d][i] = Rectangle(brx - h, tly, brx, bry);
                    brx -= h;
                }
                last[c] = i;
            }

            for (int c = 0; c < C; ++c) {
                if (last[c] != -1) {
                    int i = last[c];
                    answer[d][i].tl_vertex = rest[c].tl_vertex;
                }
            }
        }
        return true;
    }

    vector<bool> create_border_build1() {
        vector<pair<int, int>> v;
        for (int d = 0; d < D; ++d) {
            for (int i = 0; i < N; ++i) {
                v.emplace_back(d, i);
            }
        }
        sort(v.begin(), v.end(), [&](auto l, auto r) {
            return reservations[l.first].areas[l.second] > reservations[r.first].areas[r.second];
        });

        vector<bool> res(D * N, false);
        vector<int> border(1, 0);
        vector<vector<Rectangle>> rest(D);
        for (int x = 0; x < D * N; ++x) {
            auto [d, id] = v[x];
            while (rest[d].size() < border.size() - 1) {
                int l = rest[d].size();
                rest[d].emplace_back(0, border[l], W, border[l + 1]);
            }
            int s = reservations[d].areas[id];
            bool f = false;
            for (int i = 0; i < (int)rest[d].size(); ++i) {
                if (rest[d][i].area() < s) continue;
                auto &[brx, bry] = rest[d][i].br_vertex;
                if (rest[d][i].is_landscape()) {
                    int h = rest[d][i].height();
                    int w = (s - 1) / h + 1;
                    bry -= w;
                } else {
                    int w = rest[d][i].width();
                    int h = (s - 1) / w + 1;
                    brx -= h;
                }
                f = true;
                break;
            }
            if (f) continue;
            int w = (reservations[d].areas[id] - 1) / W + 1;
            if (w == 0 || border.back() + w > W) return res;
            int h = (reservations[d].areas[id] - 1) / w + 1;
            rest[d].emplace_back(Rectangle(0, border.back(), W - h, border.back() + w));
            border.emplace_back(border.back() + w);
            res[x] = true;
        }
        return res;
    }

    void solve_build(vector<vector<Rectangle>> &answer, int &score) {
        vector<vector<Rectangle>> tmp(D, vector<Rectangle>(N));
        auto is_border = create_border_build1();
        if (solve_build_detail(tmp, -1)) {
            if (chmin(score, calc_score(tmp))) answer = tmp;
        }
        for (int i = 0; i < D * N; ++i) {
            if (!is_border[i]) continue;
            if (solve_build_detail(tmp, i)) {
                if (chmin(score, calc_score(tmp))) answer = tmp;
            }
        }
    }

    bool solve_build_detail(vector<vector<Rectangle>> &answer, int b) {
        vector<pair<int, int>> v;
        for (int d = 0; d < D; ++d) {
            for (int i = 0; i < N; ++i) v.emplace_back(d, i);
        }
        sort(v.begin(), v.end(), [&](auto l, auto r) {
            return reservations[l.first].areas[l.second] > reservations[r.first].areas[r.second];
        });
        int T = (b == -1 ? 0 : reservations[v[b].first].areas[v[b].second]);

        vector<int> border(1, 0);
        vector<vector<Rectangle>> rest(D);
        vector<vector<int>> column(D, vector<int>(N, -1)), column_size(D);
        for (auto [d, id] : v) {
            while (rest[d].size() < border.size() - 1) {
                int l = rest[d].size();
                rest[d].emplace_back(Rectangle(0, border[l], W, border[l + 1]));
            }
            if (column_size[d].size() < border.size() - 1) column_size[d].resize(border.size() - 1);
            bool f = false;
            int s = reservations[d].areas[id];
            for (int i = 0; i < (int)rest[d].size(); ++i) {
                if (rest[d][i].area() < s) continue;
                auto &[brx, bry] = rest[d][i].br_vertex;
                if (rest[d][i].is_landscape()) {
                    int h = rest[d][i].height();
                    int w = (s - 1) / h + 1;
                    bry -= w;
                } else {
                    int w = rest[d][i].width();
                    int h = (s - 1) / w + 1;
                    brx -= h;
                }
                column[d][id] = i;
                ++column_size[d][i];
                f = true;
                break;
            }
            if (f) continue;
            int w = (s - 1) / W + 1;
            if (!border.empty() && s <= T) w = W - border.back();
            if (w == 0 || border.back() + w > W) return false;
            int h = (s - 1) / w + 1;
            rest[d].emplace_back(Rectangle(0, border.back(), W - h, border.back() + w));
            border.emplace_back(border.back() + w);
            column[d][id] = column_size[d].size();
            column_size[d].emplace_back(1);
        }

        if (border.back() != W) border.emplace_back(W);
        vector<int> width;
        for (int i = 0; i < (int)border.size() - 1; ++i)
            width.emplace_back(border[i + 1] - border[i]);

        vector<int> column_ord(width.size());
        iota(column_ord.begin(), column_ord.end(), 0);
        sort(column_ord.begin(), column_ord.end(),
             [&](int l, int r) { return width[l] < width[r]; });
        vector<int> reservation_ord(N);
        iota(reservation_ord.begin(), reservation_ord.end(), 0);
        for (int d = 0; d < D; ++d) {
            if (column_size[d].size() < width.size()) column_size[d].resize(width.size());
            sort(reservation_ord.begin(), reservation_ord.end(), [&](int l, int r) {
                if (width[column[d][l]] == width[column[d][r]])
                    return reservations[d].areas[l] > reservations[d].areas[r];
                return width[column[d][l]] > width[column[d][r]];
            });
            for (int i : reservation_ord) {
                assert(column_size[d][column[d][i]] > 0);
                if (column_size[d][column[d][i]] == 1) continue;
                for (int id : column_ord) {
                    if (column_size[d][id] == 0 && reservations[d].areas[i] <= width[id] * W) {
                        --column_size[d][column[d][i]];
                        column[d][i] = id;
                        ++column_size[d][id];
                        break;
                    }
                }
            }
        }

        vector<vector<int>> last(D, vector<int>(width.size(), -1));
        vector<Rectangle> rectangles;
        for (int i = 0; i < (int)border.size() - 1; ++i)
            rectangles.emplace_back(0, border[i], W, border[i + 1]);

        rest = vector<vector<Rectangle>>(D, vector<Rectangle>(rectangles));
        for (auto [d, id] : v) {
            int s = reservations[d].areas[id];
            int i = column[d][id];
            auto &[tlx, tly] = rest[d][i].tl_vertex;
            auto &[brx, bry] = rest[d][i].br_vertex;
            if (rest[d][i].is_landscape()) {
                int h = rest[d][i].height();
                int w = (s - 1) / h + 1;
                answer[d][id] = Rectangle(tlx, bry - w, brx, bry);
                bry -= w;
            } else {
                int w = rest[d][i].width();
                int h = (s - 1) / w + 1;
                answer[d][id] = Rectangle(brx - h, tly, brx, bry);
                brx -= h;
            }
            last[d][i] = id;
        }

        for (int d = 0; d < D; ++d) {
            for (int i = 0; i < (int)last[d].size(); ++i) {
                if (last[d][i] != -1) {
                    answer[d][last[d][i]].tl_vertex = rest[d][i].tl_vertex;
                }
            }
        }

        return true;
    }

    vector<bool> create_border_build_tightly() {
        vector<pair<int, int>> v;
        for (int d = 0; d < D; ++d) {
            for (int i = 0; i < N; ++i) {
                v.emplace_back(d, i);
            }
        }
        sort(v.begin(), v.end(), [&](auto l, auto r) {
            return reservations[l.first].areas[l.second] > reservations[r.first].areas[r.second];
        });

        vector<bool> res(D * N, false);
        vector<int> border(1, 0);
        vector<vector<Rectangle>> rest(D);
        for (int x = 0; x < D * N; ++x) {
            auto [d, id] = v[x];
            while (rest[d].size() < border.size() - 1) {
                int l = rest[d].size();
                rest[d].emplace_back(0, border[l], W, border[l + 1]);
            }
            int s = reservations[d].areas[id];
            bool f = false;
            vector<int> rest_ord(rest[d].size());
            iota(rest_ord.begin(), rest_ord.end(), 0);
            sort(rest_ord.begin(), rest_ord.end(),
                 [&](int l, int r) { return rest[d][l].area() < rest[d][r].area(); });
            for (int i : rest_ord) {
                if (rest[d][i].area() < s) continue;
                auto &[brx, bry] = rest[d][i].br_vertex;
                if (rest[d][i].is_landscape()) {
                    int h = rest[d][i].height();
                    int w = (s - 1) / h + 1;
                    bry -= w;
                } else {
                    int w = rest[d][i].width();
                    int h = (s - 1) / w + 1;
                    brx -= h;
                }
                f = true;
                break;
            }
            if (f) continue;
            int w = (reservations[d].areas[id] - 1) / W + 1;
            if (w == 0 || border.back() + w > W) return res;
            int h = (reservations[d].areas[id] - 1) / w + 1;
            rest[d].emplace_back(Rectangle(0, border.back(), W - h, border.back() + w));
            border.emplace_back(border.back() + w);
            res[x] = true;
        }
        return res;
    }

    void solve_build_tightly(vector<vector<Rectangle>> &answer, int &score) {
        vector<vector<Rectangle>> tmp(D, vector<Rectangle>(N));
        auto is_border = create_border_build_tightly();
        if (solve_build_tightly_detail(tmp, -1)) {
            if (chmin(score, calc_score(tmp))) answer = tmp;
        }
        for (int i = 0; i < D * N; ++i) {
            if (!is_border[i]) continue;
            if (solve_build_tightly_detail(tmp, i)) {
                if (chmin(score, calc_score(tmp))) answer = tmp;
            }
        }
    }

    bool solve_build_tightly_detail(vector<vector<Rectangle>> &answer, int b) {
        vector<pair<int, int>> v;
        for (int d = 0; d < D; ++d) {
            for (int i = 0; i < N; ++i) v.emplace_back(d, i);
        }
        sort(v.begin(), v.end(), [&](auto l, auto r) {
            return reservations[l.first].areas[l.second] > reservations[r.first].areas[r.second];
        });
        int T = (b == -1 ? 0 : reservations[v[b].first].areas[v[b].second]);

        Rectangle rest_all(0, 0, W, W);
        vector<Rectangle> rectangles;
        vector<vector<Rectangle>> rest(D);
        vector<vector<int>> column(D, vector<int>(N, -1)), column_size(D);
        for (auto [d, id] : v) {
            while (rest[d].size() < rectangles.size())
                rest[d].emplace_back(rectangles[rest[d].size()]);
            if (column_size[d].size() < rectangles.size()) column_size[d].resize(rectangles.size());
            bool f = false;
            int s = reservations[d].areas[id];
            vector<int> rest_ord(rest[d].size());
            iota(rest_ord.begin(), rest_ord.end(), 0);
            sort(rest_ord.begin(), rest_ord.end(),
                 [&](int l, int r) { return rest[d][l].area() < rest[d][r].area(); });
            for (int i : rest_ord) {
                if (rest[d][i].area() < s) continue;
                auto &[brx, bry] = rest[d][i].br_vertex;
                if (rest[d][i].is_landscape()) {
                    int h = rest[d][i].height();
                    int w = (s - 1) / h + 1;
                    bry -= w;
                } else {
                    int w = rest[d][i].width();
                    int h = (s - 1) / w + 1;
                    brx -= h;
                }
                column[d][id] = i;
                ++column_size[d][i];
                f = true;
                break;
            }
            if (f) continue;
            if (rest_all.width() == 0 || s > rest_all.area()) return false;
            int w = (s - 1) / rest_all.height() + 1;
            if (s <= T) w = rest_all.width();
            int h = (s - 1) / w + 1;
            auto [tlx, tly] = rest_all.tl_vertex;
            auto &[brx, bry] = rest_all.br_vertex;
            rest[d].emplace_back(tlx, bry - w, brx - h, bry);
            rectangles.emplace_back(tlx, bry - w, brx, bry);
            bry -= w;
            column[d][id] = column_size[d].size();
            column_size[d].emplace_back(1);
        }

        if (rest_all.area() != 0) rectangles.emplace_back(rest_all);

        vector<int> column_ord(rectangles.size());
        iota(column_ord.begin(), column_ord.end(), 0);
        sort(column_ord.begin(), column_ord.end(),
             [&](int l, int r) { return rectangles[l].width() < rectangles[r].width(); });
        vector<int> reservation_ord(N);
        iota(reservation_ord.begin(), reservation_ord.end(), 0);
        for (int d = 0; d < D; ++d) {
            if (column_size[d].size() < rectangles.size()) column_size[d].resize(rectangles.size());
            sort(reservation_ord.begin(), reservation_ord.end(), [&](int l, int r) {
                if (rectangles[column[d][l]].width() == rectangles[column[d][r]].width())
                    return reservations[d].areas[l] > reservations[d].areas[r];
                return rectangles[column[d][l]].width() > rectangles[column[d][r]].width();
            });
            for (int i : reservation_ord) {
                assert(column_size[d][column[d][i]] > 0);
                if (column_size[d][column[d][i]] == 1) continue;
                for (int id : column_ord) {
                    if (column_size[d][id] == 0 &&
                        reservations[d].areas[i] <= rectangles[id].area()) {
                        --column_size[d][column[d][i]];
                        column[d][i] = id;
                        ++column_size[d][id];
                        break;
                    }
                }
            }
        }

        vector<vector<int>> last(D, vector<int>(rectangles.size(), -1));
        rest = vector<vector<Rectangle>>(D, vector<Rectangle>(rectangles));
        for (auto [d, id] : v) {
            int s = reservations[d].areas[id];
            int i = column[d][id];
            auto &[tlx, tly] = rest[d][i].tl_vertex;
            auto &[brx, bry] = rest[d][i].br_vertex;
            if (rest[d][i].is_landscape()) {
                int h = rest[d][i].height();
                int w = (s - 1) / h + 1;
                answer[d][id] = Rectangle(tlx, bry - w, brx, bry);
                bry -= w;
            } else {
                int w = rest[d][i].width();
                int h = (s - 1) / w + 1;
                answer[d][id] = Rectangle(brx - h, tly, brx, bry);
                brx -= h;
            }
            last[d][i] = id;
        }

        for (int d = 0; d < D; ++d) {
            for (int i = 0; i < (int)last[d].size(); ++i) {
                if (last[d][i] != -1) answer[d][last[d][i]].tl_vertex = rest[d][i].tl_vertex;
            }
        }

        return true;
    }

    vector<bool> create_border_build_tightly2(int smallest) {
        vector<pair<int, int>> v;
        for (int d = 0; d < D; ++d) {
            for (int i = smallest; i < N; ++i) {
                v.emplace_back(d, i);
            }
        }
        sort(v.begin(), v.end(), [&](auto l, auto r) {
            return reservations[l.first].areas[l.second] > reservations[r.first].areas[r.second];
        });

        vector<bool> res(D * (N - smallest), false);
        vector<int> border(1, 0);
        vector<vector<Rectangle>> rest(D);
        for (int x = 0; x < D * (N - smallest); ++x) {
            auto [d, id] = v[x];
            while (rest[d].size() < border.size() - 1) {
                int l = rest[d].size();
                rest[d].emplace_back(0, border[l], W, border[l + 1]);
            }
            int s = reservations[d].areas[id];
            bool f = false;
            vector<int> rest_ord(rest[d].size());
            iota(rest_ord.begin(), rest_ord.end(), 0);
            sort(rest_ord.begin(), rest_ord.end(),
                 [&](int l, int r) { return rest[d][l].area() < rest[d][r].area(); });
            for (int i : rest_ord) {
                if (rest[d][i].area() < s) continue;
                auto &[brx, bry] = rest[d][i].br_vertex;
                if (rest[d][i].is_landscape()) {
                    int h = rest[d][i].height();
                    int w = (s - 1) / h + 1;
                    bry -= w;
                } else {
                    int w = rest[d][i].width();
                    int h = (s - 1) / w + 1;
                    brx -= h;
                }
                f = true;
                break;
            }
            if (f) continue;
            int w = (reservations[d].areas[id] - 1) / W + 1;
            if (w == 0 || border.back() + w > W) return res;
            int h = (reservations[d].areas[id] - 1) / w + 1;
            rest[d].emplace_back(Rectangle(0, border.back(), W - h, border.back() + w));
            border.emplace_back(border.back() + w);
            res[x] = true;
        }
        return res;
    }

    int decide_small_rectangle(vector<vector<Rectangle>> &answer, int smallest) {
        if (smallest == 0) return W;
        vector<int> v(smallest);
        for (int d = 0; d < D; ++d) {
            for (int i = 0; i < smallest; ++i) {
                chmax(v[i], reservations[d].areas[i]);
            }
        }

        int w = search_width(v);
        if (w > W) return -1;
        vector<Rectangle> rectangles(N);
        int limit = W;
        for (int i = 0; i < smallest; ++i) {
            int h = (v[i] - 1) / w + 1;
            rectangles[i] = Rectangle(limit - h, W - w, limit, W);
            limit -= h;
        }
        rectangles[smallest - 1].tl_vertex.x = 0;
        for (int d = 0; d < D; ++d) {
            answer[d] = rectangles;
        }
        return W - w;
    }

    void solve_build_tightly2(vector<vector<Rectangle>> &answer, int &score) {
        vector<vector<Rectangle>> tmp(D, vector<Rectangle>(N));
        for (int smallest = 1; smallest < N; ++smallest) {
            int limit_y = decide_small_rectangle(tmp, smallest);
            if (limit_y == -1) break;
            if (solve_build_tightly2_detail(tmp, -1, smallest, limit_y)) {
                if (chmin(score, calc_score(tmp))) answer = tmp;
            }
            auto is_border = create_border_build_tightly2(smallest);
            for (int i = 0; i < D * (N - smallest); ++i) {
                if (!is_border[i]) continue;
                if (solve_build_tightly2_detail(tmp, i, smallest, limit_y)) {
                    if (chmin(score, calc_score(tmp))) answer = tmp;
                }
            }
        }
    }

    bool solve_build_tightly2_detail(vector<vector<Rectangle>> &answer, int b, int smallest,
                                     int limit_y) {
        vector<pair<int, int>> v;
        for (int d = 0; d < D; ++d) {
            for (int i = smallest; i < N; ++i) v.emplace_back(d, i);
        }
        sort(v.begin(), v.end(), [&](auto l, auto r) {
            return reservations[l.first].areas[l.second] > reservations[r.first].areas[r.second];
        });
        int T = (b == -1 ? 0 : reservations[v[b].first].areas[v[b].second]);

        Rectangle rest_all(0, 0, W, limit_y);
        vector<Rectangle> rectangles;
        vector<vector<Rectangle>> rest(D);
        vector<vector<int>> column(D, vector<int>(N, -1)), column_size(D);
        for (auto [d, id] : v) {
            while (rest[d].size() < rectangles.size())
                rest[d].emplace_back(rectangles[rest[d].size()]);
            if (column_size[d].size() < rectangles.size()) column_size[d].resize(rectangles.size());
            bool f = false;
            int s = reservations[d].areas[id];
            vector<int> rest_ord(rest[d].size());
            iota(rest_ord.begin(), rest_ord.end(), 0);
            sort(rest_ord.begin(), rest_ord.end(),
                 [&](int l, int r) { return rest[d][l].area() < rest[d][r].area(); });
            for (int i : rest_ord) {
                if (rest[d][i].area() < s) continue;
                auto &[brx, bry] = rest[d][i].br_vertex;
                if (rest[d][i].is_landscape()) {
                    int h = rest[d][i].height();
                    int w = (s - 1) / h + 1;
                    bry -= w;
                } else {
                    int w = rest[d][i].width();
                    int h = (s - 1) / w + 1;
                    brx -= h;
                }
                column[d][id] = i;
                ++column_size[d][i];
                f = true;
                break;
            }
            if (f) continue;
            if (s > rest_all.area()) return false;
            int w = (s - 1) / rest_all.height() + 1;
            if (s <= T) w = rest_all.width();
            int h = (s - 1) / w + 1;
            auto [tlx, tly] = rest_all.tl_vertex;
            auto &[brx, bry] = rest_all.br_vertex;
            rest[d].emplace_back(tlx, bry - w, brx - h, bry);
            rectangles.emplace_back(tlx, bry - w, brx, bry);
            bry -= w;
            column[d][id] = column_size[d].size();
            column_size[d].emplace_back(1);
        }

        if (rest_all.area() != 0) rectangles.emplace_back(rest_all);

        vector<int> column_ord(rectangles.size());
        iota(column_ord.begin(), column_ord.end(), 0);
        sort(column_ord.begin(), column_ord.end(),
             [&](int l, int r) { return rectangles[l].width() < rectangles[r].width(); });
        vector<int> reservation_ord(N - smallest);
        iota(reservation_ord.begin(), reservation_ord.end(), smallest);
        for (int d = 0; d < D; ++d) {
            if (column_size[d].size() < rectangles.size()) column_size[d].resize(rectangles.size());
            sort(reservation_ord.begin(), reservation_ord.end(), [&](int l, int r) {
                if (rectangles[column[d][l]].width() == rectangles[column[d][r]].width())
                    return reservations[d].areas[l] > reservations[d].areas[r];
                return rectangles[column[d][l]].width() > rectangles[column[d][r]].width();
            });
            for (int i : reservation_ord) {
                assert(column_size[d][column[d][i]] > 0);
                if (column_size[d][column[d][i]] == 1) continue;
                for (int id : column_ord) {
                    if (column_size[d][id] == 0 &&
                        reservations[d].areas[i] <= rectangles[id].area()) {
                        --column_size[d][column[d][i]];
                        column[d][i] = id;
                        ++column_size[d][id];
                        break;
                    }
                }
            }
        }

        vector<vector<int>> last(D, vector<int>(rectangles.size(), -1));
        rest = vector<vector<Rectangle>>(D, vector<Rectangle>(rectangles));
        for (auto [d, id] : v) {
            int s = reservations[d].areas[id];
            int i = column[d][id];
            auto &[tlx, tly] = rest[d][i].tl_vertex;
            auto &[brx, bry] = rest[d][i].br_vertex;
            if (rest[d][i].is_landscape()) {
                int h = rest[d][i].height();
                int w = (s - 1) / h + 1;
                answer[d][id] = Rectangle(tlx, bry - w, brx, bry);
                bry -= w;
            } else {
                int w = rest[d][i].width();
                int h = (s - 1) / w + 1;
                answer[d][id] = Rectangle(brx - h, tly, brx, bry);
                brx -= h;
            }
            last[d][i] = id;
        }

        for (int d = 0; d < D; ++d) {
            for (int i = 0; i < (int)last[d].size(); ++i) {
                if (last[d][i] != -1) answer[d][last[d][i]].tl_vertex = rest[d][i].tl_vertex;
            }
        }

        return true;
    }

    vector<bool> create_border_build2() {
        vector<pair<int, int>> v;
        for (int d = 0; d < D; ++d) {
            for (int i = 0; i < N; ++i) {
                v.emplace_back(d, i);
            }
        }
        sort(v.begin(), v.end(), [&](auto l, auto r) {
            return reservations[l.first].areas[l.second] > reservations[r.first].areas[r.second];
        });

        vector<bool> res(D * N, false);
        vector<Rectangle> rectangles;
        Position limit(W, W);
        vector<vector<Rectangle>> rest(D);
        for (int x = 0; x < D * N; ++x) {
            auto [d, id] = v[x];
            while (rest[d].size() < rectangles.size()) {
                rest[d].emplace_back(rectangles[rest[d].size()]);
            }
            int s = reservations[d].areas[id];
            bool f = false;
            for (int i = 0; i < (int)rest[d].size(); ++i) {
                auto &[brx, bry] = rest[d][i].br_vertex;
                if (rest[d][i].area() < s) continue;
                if (rest[d][i].is_landscape()) {
                    int h = rest[d][i].height();
                    int w = (s - 1) / h + 1;
                    if (w > rest[d][i].width()) continue;
                    bry -= w;
                } else {
                    int w = rest[d][i].width();
                    int h = (s - 1) / w + 1;
                    if (h > rest[d][i].height()) continue;
                    brx -= h;
                }
                f = true;
                break;
            }
            if (f) continue;
            if (limit.x == 0 || limit.y == 0) return res;
            if (limit.x < limit.y) {
                int h = limit.x;
                int w = (s - 1) / h + 1;
                h = (s - 1) / w + 1;
                if (w > limit.y) return res;
                rectangles.emplace_back(0, limit.y - w, limit.x, limit.y);
                rest[d].emplace_back(0, limit.y - w, limit.x - h, limit.y);
                limit.y -= w;
            } else {
                int w = limit.y;
                int h = (s - 1) / w + 1;
                w = (s - 1) / h + 1;
                if (h > limit.x) return res;
                rectangles.emplace_back(limit.x - h, 0, limit.x, limit.y);
                rest[d].emplace_back(limit.x - h, 0, limit.x, limit.y - w);
                limit.x -= h;
            }
            res[x] = true;
        }
        return res;
    }

    void solve_build2(vector<vector<Rectangle>> &answer, int &score) {
        vector<vector<Rectangle>> tmp(D, vector<Rectangle>(N));
        auto is_border = create_border_build2();
        if (solve_build2_detail(tmp, -1)) {
            if (chmin(score, calc_score(tmp))) answer = tmp;
        }
        for (int i = 0; i < D * N; ++i) {
            if (!is_border[i]) continue;
            if (solve_build2_detail(tmp, i)) {
                if (chmin(score, calc_score(tmp))) answer = tmp;
            }
        }
    }

    bool solve_build2_detail(vector<vector<Rectangle>> &answer, int b) {
        vector<pair<int, int>> v;
        for (int d = 0; d < D; ++d) {
            for (int i = 0; i < N; ++i) {
                v.emplace_back(d, i);
            }
        }
        sort(v.begin(), v.end(), [&](auto l, auto r) {
            return reservations[l.first].areas[l.second] > reservations[r.first].areas[r.second];
        });
        int T = (b == -1 ? -1 : reservations[v[b].first].areas[v[b].second]);

        vector<Rectangle> rectangles;
        Position limit(W, W);
        vector<vector<Rectangle>> rest(D);
        vector<vector<int>> group(D, vector<int>(N, -1)), group_size(D);
        for (auto [d, id] : v) {
            while (rest[d].size() < rectangles.size()) {
                rest[d].emplace_back(rectangles[rest[d].size()]);
            }
            if (group_size[d].size() < rectangles.size())
                group_size[d].resize(rectangles.size(), 0);
            int s = reservations[d].areas[id];
            bool f = false;
            for (int i = 0; i < (int)rest[d].size(); ++i) {
                auto &[tlx, tly] = rest[d][i].tl_vertex;
                auto &[brx, bry] = rest[d][i].br_vertex;
                if (rest[d][i].area() < s) continue;
                if (rest[d][i].is_landscape()) {
                    int h = rest[d][i].height();
                    int w = (s - 1) / h + 1;
                    if (w > rest[d][i].width()) continue;
                    answer[d][id] = Rectangle(tlx, bry - w, brx, bry);
                    group[d][id] = i;
                    ++group_size[d][i];
                    bry -= w;
                } else {
                    int w = rest[d][i].width();
                    int h = (s - 1) / w + 1;
                    if (h > rest[d][i].height()) continue;
                    answer[d][id] = Rectangle(brx - h, tly, brx, bry);
                    group[d][id] = i;
                    ++group_size[d][i];
                    brx -= h;
                }
                f = true;
                break;
            }
            if (f) continue;
            if (limit.x == 0 || limit.y == 0) return false;
            int hr = (s % limit.x == 0 ? 0 : limit.x - s % limit.x);
            int wr = (s % limit.y == 0 ? 0 : limit.y - s % limit.y);
            if (hr < wr) {
                int h = limit.x;
                int w = (s - 1) / h + 1;
                h = (s - 1) / w + 1;
                if (w > limit.y) return false;
                if (s <= T) {
                    rectangles.emplace_back(0, 0, limit.x, limit.y);
                    answer[d][id] = Rectangle(0, limit.y - w, limit.x, limit.y);
                    rest[d].emplace_back(0, 0, limit.x, limit.y - w);
                    group[d][id] = group_size[d].size();
                    group_size[d].emplace_back(1);
                    limit = Position(0, 0);
                } else {
                    rectangles.emplace_back(0, limit.y - w, limit.x, limit.y);
                    answer[d][id] = Rectangle(limit.x - h, limit.y - w, limit.x, limit.y);
                    rest[d].emplace_back(0, limit.y - w, limit.x - h, limit.y);
                    group[d][id] = group_size[d].size();
                    group_size[d].emplace_back(1);
                    limit.y -= w;
                }
            } else {
                int w = limit.y;
                int h = (s - 1) / w + 1;
                w = (s - 1) / h + 1;
                if (h > limit.x) return false;
                if (s <= T) {
                    rectangles.emplace_back(0, 0, limit.x, limit.y);
                    answer[d][id] = Rectangle(limit.x - h, 0, limit.x, limit.y);
                    rest[d].emplace_back(0, 0, limit.x - h, limit.y);
                    group[d][id] = group_size[d].size();
                    group_size[d].emplace_back(1);
                    limit = Position(0, 0);
                } else {
                    rectangles.emplace_back(limit.x - h, 0, limit.x, limit.y);
                    answer[d][id] = Rectangle(limit.x - h, limit.y - w, limit.x, limit.y);
                    rest[d].emplace_back(limit.x - h, 0, limit.x, limit.y - w);
                    group[d][id] = group_size[d].size();
                    group_size[d].emplace_back(1);
                    limit.x -= h;
                }
            }
        }

        if (limit.x != 0 && limit.y != 0) rectangles.emplace_back(Position(0, 0), limit);

        vector<int> group_ord(rectangles.size());
        iota(group_ord.begin(), group_ord.end(), 0);
        sort(group_ord.begin(), group_ord.end(),
             [&](int l, int r) { return rectangles[l].area() < rectangles[r].area(); });
        vector<int> reservation_ord(N);
        iota(reservation_ord.begin(), reservation_ord.end(), 0);
        for (int d = 0; d < D; ++d) {
            if (group_size[d].size() < rectangles.size())
                group_size[d].resize(rectangles.size(), 0);
            sort(reservation_ord.begin(), reservation_ord.end(), [&](int l, int r) {
                if (rectangles[group[d][l]].area() == rectangles[group[d][r]].area())
                    return reservations[d].areas[l] > reservations[d].areas[r];
                return rectangles[group[d][l]].area() > rectangles[group[d][r]].area();
            });
            for (int i : reservation_ord) {
                assert(group_size[d][group[d][i]] > 0);
                if (group_size[d][group[d][i]] == 1) continue;
                for (int id : group_ord) {
                    if (group_size[d][id] == 0 &&
                        reservations[d].areas[i] <= rectangles[id].area()) {
                        --group_size[d][group[d][i]];
                        group[d][i] = id;
                        ++group_size[d][id];
                        break;
                    }
                }
            }
        }

        vector<vector<int>> last(D, vector<int>(rectangles.size(), -1));
        rest = vector<vector<Rectangle>>(D, vector<Rectangle>(rectangles));
        for (auto [d, id] : v) {
            int s = reservations[d].areas[id];
            int i = group[d][id];
            if (rest[d][i].area() < s) return false;
            auto &[tlx, tly] = rest[d][i].tl_vertex;
            auto &[brx, bry] = rest[d][i].br_vertex;
            if (rest[d][i].is_landscape()) {
                int h = rest[d][i].height();
                int w = (s - 1) / h + 1;
                answer[d][id] = Rectangle(tlx, bry - w, brx, bry);
                bry -= w;
            } else {
                int w = rest[d][i].width();
                int h = (s - 1) / w + 1;
                answer[d][id] = Rectangle(brx - h, tly, brx, bry);
                brx -= h;
            }
            last[d][i] = id;
        }

        for (int d = 0; d < D; ++d) {
            for (int i = 0; i < (int)last[d].size(); ++i) {
                if (last[d][i] != -1) {
                    int id = last[d][i];
                    answer[d][id].tl_vertex = rest[d][i].tl_vertex;
                }
            }
        }

        return true;
    }

    bool solve_half(vector<vector<Rectangle>> &answer) {
        vector dp(D, vector(W, inf));
        vector data(D, vector(W, -1l));
        vector pr(D, vector(W, -1));
        int prev_border = -1, prev_cost = 0;
        vector<int> ord(N);
        for (int d = 0; d < D; ++d) {
            int min_border = -1, min_cost = inf;
            iota(ord.begin(), ord.end(), 0);
            for (int loop = 0; loop < 100; ++loop) {
                int64_t bit = 0;
                for (int border = 1; border < N; ++border) {
                    vector<int> u, v;
                    for (int i = 0; i < N; ++i) {
                        if (i < border) {
                            bit |= 1l << ord[i];
                            u.emplace_back(reservations[d].areas[ord[i]]);
                        } else {
                            v.emplace_back(reservations[d].areas[ord[i]]);
                        }
                    }
                    int l = search_width(u);
                    int r = search_width(v);
                    if (l + r <= W) {
                        if (d == 0) {
                            for (int i = l; i <= W - r; ++i) {
                                int c = i * (border - 1) + (W - i) * (N - border - 1);
                                if (chmin(dp[d][i], c)) {
                                    data[d][i] = bit;
                                }
                                if (chmin(min_cost, c)) {
                                    min_border = i;
                                }
                            }
                        } else {
                            for (int i = l; i <= W - r; ++i) {
                                int c = i * (border - 1) + (W - i) * (N - border - 1);
                                if (d < D - 1) c *= 2;
                                if (chmin(dp[d][i], dp[d - 1][i] + c)) {
                                    data[d][i] = bit;
                                    pr[d][i] = i;
                                }
                                if (chmin(dp[d][i], prev_cost + W * 2 + c)) {
                                    data[d][i] = bit;
                                    pr[d][i] = prev_border;
                                }
                                if (chmin(min_cost, dp[d][i])) {
                                    min_border = i;
                                }
                            }
                        }
                    }
                }
                shuffle(ord.begin(), ord.end(), xorshift);
            }
            if (min_border == -1) return false;
            prev_border = min_border, prev_cost = min_cost;
        }

        for (int d = D - 1; d >= 0; --d) {
            int64_t bit = data[d][prev_border];
            int wl = 0, wr = 0;
            for (int i = 0; i < N; ++i) {
                if (bit >> i & 1) {
                    int w = (reservations[d].areas[i] - 1) / prev_border + 1;
                    answer[d][i] = Rectangle(0, wl, prev_border, wl + w);
                    wl += w;
                } else {
                    int w = (reservations[d].areas[i] - 1) / (W - prev_border) + 1;
                    answer[d][i] = Rectangle(prev_border, wr, W, wr + w);
                    wr += w;
                }
            }
            for (int i = 0; i < N; ++i) {
                if (answer[d][i].tl_vertex.x == 0 && answer[d][i].br_vertex.y == wl)
                    answer[d][i].br_vertex.y = W;
                if (answer[d][i].br_vertex.x == W && answer[d][i].br_vertex.y == wr)
                    answer[d][i].br_vertex.y = W;
            }
            prev_border = pr[d][prev_border];
        }
        return true;
    }

    bool solve_edge(const Reservation &reservation, vector<Rectangle> &rectangles) {
        vector<int> candidate(N);
        iota(candidate.begin(), candidate.end(), 0);
        Position limit(W, W);
        for (int i = 0; i < N; ++i) {
            int min_r = W * W;
            int min_idx = -1;
            int min_dir = -1;
            for (int idx : candidate) {
                int x = (reservation.areas[idx] + limit.y - 1) / limit.y;
                int y = (reservation.areas[idx] + limit.x - 1) / limit.x;
                if (x <= limit.x && chmin(min_r, x * limit.y - reservation.areas[idx])) {
                    min_idx = idx;
                    min_dir = 0;
                }
                if (y <= limit.y && chmin(min_r, y * limit.x - reservation.areas[idx])) {
                    min_idx = idx;
                    min_dir = 1;
                }
            }
            if (min_idx == -1) break;
            if (i == N - 1) {
                rectangles[min_idx] = Rectangle{Position(0, 0), limit};
                candidate.pop_back();
                break;
            }
            int x = (reservation.areas[min_idx] + limit.y - 1) / limit.y;
            int y = (reservation.areas[min_idx] + limit.x - 1) / limit.x;
            if (min_dir == 0) {
                rectangles[min_idx] = Rectangle{Position(limit.x - x, 0), limit};
                limit.x -= x;
            } else {
                rectangles[min_idx] = Rectangle{Position(0, limit.y - y), limit};
                limit.y -= y;
            }
            int idx = find(candidate.begin(), candidate.end(), min_idx) - candidate.begin();
            swap(candidate[idx], candidate.back());
            candidate.pop_back();
        }

        return candidate.empty();
    }

    bool solve_linear(const Reservation &reservation, vector<Rectangle> &rectangles) {
        vector<int> v(N);
        for (int i = 0; i < N; ++i) {
            v[i] = max(1, reservation.areas[i] / W);
        }
        int s = accumulate(v.begin(), v.end(), 0);
        if (s > W) {
            for (int i = N - 1; i >= 0; --i) {
                s -= v[i] - 1;
                v[i] = 1;
                if (s <= W) {
                    v[i] += W - s;
                    break;
                }
            }
        } else {
            vector<int> r(N);
            for (int i = 0; i < N; ++i) {
                r[i] = reservation.areas[i] % W;
            }
            vector<int> ord(N);
            iota(ord.begin(), ord.end(), 0);
            sort(ord.begin(), ord.end(), [&r](int x, int y) { return r[x] > r[y]; });
            for (int i = 0; i < min(N, W - s); ++i) {
                ++v[ord[i]];
            }
        }
        int sum = 0;
        for (int i = 0; i < N; ++i) {
            rectangles[i] = Rectangle(Position(sum, 0), Position(sum + v[i], W));
        }
        return true;
    }

    int search_width(const vector<int> areas) const {
        int l = 0, r = W + 1;
        while (r - l > 1) {
            int m = (l + r) / 2;
            int s = 0;
            for (int x : areas) s += (x - 1) / m + 1;
            if (s <= W) r = m;
            else l = m;
        }
        return r;
    }

    bool solve_dp(const Reservation &reservation, vector<Rectangle> &rectangles) {
        if (N > 16) return false;
        vector<int> dp(1 << N);
        vector<int> p(1 << N, -1);
        for (int bit = 1; bit < 1 << N; ++bit) {
            vector<int> v;
            for (int i = 0; i < N; ++i) {
                if (bit >> i & 1) v.emplace_back(reservation.areas[i]);
            }
            dp[bit] = search_width(v);
        }

        for (int bit = 1; bit < 1 << N; ++bit) {
            for (int x = bit; x; x = (x - 1) & bit) {
                if (chmin(dp[bit], dp[x] + dp[x ^ bit])) {
                    p[bit] = x;
                }
            }
        }

        if (dp.back() > W) return false;

        int s = 0;
        auto dfs = [&](auto self, int x) -> void {
            if (p[x] != -1) {
                self(self, p[x]);
                self(self, x ^ p[x]);
                return;
            }
            vector<int> v;
            for (int i = 0; i < N; ++i) {
                if (x >> i & 1) {
                    v.emplace_back(i);
                }
            }
            int t = 0;
            for (int i : v) {
                int w = (reservation.areas[i] - 1) / dp[x] + 1;
                rectangles[i] = Rectangle(s, t, s + dp[x], t + w);
                t += w;
            }
            rectangles[v.back()].br_vertex.y = W;
            s += dp[x];
        };
        dfs(dfs, (1 << N) - 1);
        for (int i = 0; i < N; ++i) {
            if (rectangles[i].br_vertex.x == s) {
                rectangles[i].br_vertex.x = W;
            }
        }
        return true;
    }

    bool solve_half(const Reservation &reservation, vector<Rectangle> &rectangles) {
        int min_border = -1, min_width = -1, min_cost = inf;
        for (int border = 1; border < N; ++border) {
            vector<int> u, v;
            for (int i = 0; i < N; ++i) {
                if (i < border) u.emplace_back(reservation.areas[i]);
                else v.emplace_back(reservation.areas[i]);
            }
            int l = search_width(u);
            int r = search_width(v);
            if (l + r <= W) {
                for (int i = l; i <= W - r; ++i) {
                    if (chmin(min_cost, i * (border - 1) + (W - i) * (N - border - 1))) {
                        min_border = border;
                        min_width = i;
                    }
                }
            }
        }

        if (min_border == -1) return false;
        int wl = 0, wr = 0;
        for (int i = 0; i < N; ++i) {
            if (i < min_border - 1) {
                int w = (reservation.areas[i] - 1) / min_width + 1;
                rectangles[i] = Rectangle(0, wl, min_width, wl + w);
                wl += w;
            } else if (i == min_border - 1) {
                rectangles[i] = Rectangle(0, wl, min_width, W);
            } else if (i < N - 1) {
                int w = (reservation.areas[i] - 1) / (W - min_width) + 1;
                rectangles[i] = Rectangle(min_width, wr, W, wr + w);
                wr += w;
            } else {
                rectangles[i] = Rectangle(min_width, wr, W, W);
            }
        }
        return true;
    }

    vector<vector<Rectangle>> solve() {
        vector<vector<Rectangle>> answer(D, vector<Rectangle>(N));
        int score = inf;
        solve_column<11>(answer, score);
        solve_build(answer, score);
        solve_build_tightly(answer, score);
        solve_build_tightly2(answer, score);
        solve_build2(answer, score);
        auto tmp = answer;
        if (solve_zero_cost(tmp)) {
            if (chmin(score, calc_score(tmp))) answer = tmp;
        }
        if (solve_half(tmp)) {
            if (chmin(score, calc_score(tmp))) answer = tmp;
        }

        if (score != inf) return answer;

        for (int d = 0; d < D; ++d) {
            vector<Rectangle> rectangles(N);
            if (solve_dp(reservations[d], rectangles)) {
            } else if (solve_half(reservations[d], rectangles)) {
            } else if (solve_edge(reservations[d], rectangles)) {
            } else {
                solve_linear(reservations[d], rectangles);
            }
            answer[d] = rectangles;
        }
        return answer;
    }
};

struct State {
    static vector<Reservation> reservations;
    int score, width_sum;
    vector<vector<uint64_t>> group;
    vector<vector<int>> width;
    vector<int> max_width, max_width_day;
    State()
        : score(), width_sum(), group(D, vector<uint64_t>(N)), width(D, vector<int>(N)),
          max_width(N), max_width_day(N, -1) {
        for (int d = 0; d < D; ++d) {
            for (int i = 0; i < N; ++i) {
                group[d][i] = 1l << i;
                width[d][i] = (reservations[d].areas[i] - 1) / W + 1;
            }
        }
        for (int i = 0; i < N; ++i) update_max_width(i);
        update_width_sum();
    }

    constexpr bool operator<(const State &rhs) const {
        return score < rhs.score;
    }

    void update_width_sum() {
        width_sum = accumulate(max_width.begin(), max_width.end(), 0);
    }

    void update_max_width(int i) {
        max_width[i] = 0;
        for (int d = 0; d < D; ++d) update_max_width(d, i);
    }

    void update_max_width(int d, int i) {
        if (chmax(max_width[i], width[d][i])) max_width_day[i] = d;
    }

    void update_score() {
        score = 0;
        for (int d = 0; d < D; ++d) {
            for (int i = 0; i < N; ++i) {
                if (width[d][i] == 0) continue;
                int p = popcount(group[d][i]);
                score += max_width[i] * (p - 1);
                if (1 <= d && d < D - 1) score += max_width[i] * (p - 1);
            }
        }
    }

    int calc_width(int d, uint64_t bit) const {
        int l = 0, r = W + 1;
        while (r - l > 1) {
            int m = (l + r) / 2;
            int s = 0;
            for (int i = 0; i < N; ++i) {
                if (bit >> i & 1) s += (reservations[d].areas[i] - 1) / m + 1;
            }
            if (s <= W) r = m;
            else l = m;
        }
        return r;
    }

    void merge_detail(int d, int l, int r) {
        group[d][l] |= group[d][r];
        for (int i = r; i < N - 1; ++i) {
            group[d][i] = group[d][i + 1];
            width[d][i] = width[d][i + 1];
            if (max_width_day[i] == d) update_max_width(i);
            if (width[d][i] == 0) break;
        }
        group[d][N - 1] = 0;
        width[d][N - 1] = 0;
        width[d][l] = calc_width(d, group[d][l]);
        for (; l >= 1; --l) {
            if (width[d][l - 1] >= width[d][l]) break;
            swap(group[d][l - 1], group[d][l]);
            swap(width[d][l - 1], width[d][l]);
            update_max_width(d, l);
        }
        chmax(max_width[l], width[d][l]);
        update_width_sum();
        update_score();
    }

    State merge(int d, int l, int r) {
        State res(*this);
        res.merge_detail(d, l, r);
        return res;
    }

    void format() {
        int last_idx = N;
        for (int d = 0; d < D; ++d) {
            for (int i = 0; i < N; ++i) {
                if (width[d][i] == 0) chmin(last_idx, i);
            }
        }
        --last_idx;
        for (int d = 0; d < D; ++d) {
            for (int i = last_idx + 1; i < N; ++i) {
                group[d][last_idx] |= group[d][i];
                group[d][i] = 0;
                width[d][i] = 0;
            }
        }
        for (int d = 0; d < D; ++d) width[d][last_idx] = calc_width(d, group[d][last_idx]);
        update_max_width(last_idx);
        update_score();
    }
};

template <int BEAM_WIDTH>
struct chokudai_search {
    vector<array<State, BEAM_WIDTH>> states;
    vector<set<pair<int, int>>> state_eval;
    vector<stack<int>> unused_index;

    chokudai_search() {}

    bool exists_unused_index(int i) {
        return !unused_index[i].empty();
    }

    int pop_unused_index(int i) {
        int x = unused_index[i].top();
        unused_index[i].pop();
        return x;
    }

    int exists_state(int i) {
        return !state_eval[i].empty();
    }

    int pop_best_state(int i) {
        auto [x, y] = *state_eval[i].begin();
        state_eval[i].erase(state_eval[i].begin());
        unused_index[i].emplace(y);
        return y;
    }

    vector<vector<Rectangle>> solve(const vector<Reservation> &reservations) {
        int min_score = inf;
        State ans;
        State init = State();
        int len = init.width_sum - W;
        if (len <= 0) return vector<vector<Rectangle>>(D, vector<Rectangle>(N));
        states.resize(len);
        state_eval.resize(len);
        unused_index.resize(len);
        for (int i = 0; i < len; ++i) {
            for (int j = 0; j < BEAM_WIDTH; ++j) unused_index[i].emplace(j);
        }
        int p = pop_unused_index(len - 1);
        states[len - 1][p] = init;
        state_eval[len - 1].emplace(init.score, p);
        while ((double)clock() / CLOCKS_PER_SEC < 2.9) {
            for (int x = len - 1; x >= 0; --x) {
                if (!exists_state(x)) continue;
                int y = pop_best_state(x);
                State state = states[x][y];
                for (int r = N - 1; r >= 0; --r) {
                    int d = state.max_width_day[r];
                    if (d == -1) continue;
                    for (int l = r - 1; l >= 0; --l) {
                        State new_state = state.merge(d, l, r);
                        if (new_state.width_sum <= W) {
                            new_state.format();
                            if (chmin(min_score, new_state.score)) ans = new_state;
                        } else if (new_state.width_sum - W < len) {
                            int idx = new_state.width_sum - W - 1;
                            if (exists_unused_index(idx)) {
                                int p = pop_unused_index(idx);
                                states[idx][p] = new_state;
                                state_eval[idx].emplace(new_state.score, p);
                            } else {
                                auto [score, p] = *state_eval[idx].rbegin();
                                if (new_state.score < score) {
                                    state_eval[idx].erase(prev(state_eval[idx].end()));
                                    states[idx][p] = new_state;
                                    state_eval[idx].emplace(new_state.score, p);
                                }
                            }
                        }
                        if ((double)clock() / CLOCKS_PER_SEC >= 2.9) break;
                    }
                    if ((double)clock() / CLOCKS_PER_SEC >= 2.9) break;
                }
                if ((double)clock() / CLOCKS_PER_SEC >= 2.9) break;
            }
        }

        if (min_score == inf) return vector<vector<Rectangle>>(D, vector<Rectangle>(N));
        vector<vector<Rectangle>> answer(D, vector<Rectangle>(N));
        int sw = 0;
        for (int x = 0; x < N; ++x) {
            int w = ans.max_width[x];
            if (w == 0) break;
            for (int d = 0; d < D; ++d) {
                int s = 0;
                int last = -1;
                for (int i = 0; i < N; ++i) {
                    if (ans.group[d][x] >> i & 1) {
                        int h = (reservations[d].areas[i] - 1) / w + 1;
                        answer[d][i] = Rectangle(s, sw, s + h, sw + w);
                        s += h;
                        last = i;
                    }
                }
                if (last != -1) {
                    answer[d][last].br_vertex.x = W;
                }
            }
            sw += w;
        }

        for (int d = 0; d < D; ++d) reverse(answer[d].begin(), answer[d].end());
        return answer;
    }
};

vector<Reservation> State::reservations = vector<Reservation>();

int main(void) {
    int tmp;
    cin >> tmp >> D >> N;
    vector<Reservation> reservations(D);
    for (int i = 0; i < D; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> reservations[i].areas[j];
        }
    }

    int64_t min_score = inf;
    vector<vector<Rectangle>> answer, tmp_ans;

    Solver solver(reservations);
    answer = solver.solve();
    min_score = internal::calc_score(answer, reservations);

    for (int d = 0; d < D; ++d) reverse(reservations[d].areas.begin(), reservations[d].areas.end());
    State::reservations = reservations;
    chokudai_search<20> solver2;
    tmp_ans = solver2.solve(reservations);
    for (int d = 0; d < D; ++d) reverse(reservations[d].areas.begin(), reservations[d].areas.end());
    if (chmin(min_score, internal::calc_score(tmp_ans, reservations))) answer = tmp_ans;

    for (int d = 0; d < D; ++d) {
        for (int i = 0; i < N; ++i) {
            cout << answer[d][i] << endl;
        }
    }

    return 0;
}
