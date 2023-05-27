#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <iostream>
#include <limits>
#include <numeric>
#include <random>
#include <vector>

#define FOR(i, m, n) for (int i = (m); i < int(n); ++i)
#define rep(i, n) FOR (i, 0, n)

using namespace std;
template <class T, class U>
bool chmax(T &a, const U b) {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U b) {
    return (T)b < a ? a = (T)b, true : false;
}

struct Xorshift {
    using state_type = std::array<std::uint32_t, 4>;
    using result_type = std::uint32_t;
    constexpr Xorshift() : state{123456789, 362436069, 521288629, 88675123} {}

    constexpr result_type min() { return std::numeric_limits<result_type>::min(); }
    constexpr result_type max() { return std::numeric_limits<result_type>::max(); }
    result_type operator()() {
        std::uint32_t t = (state[0] ^ (state[0] << 11));
        state[0] = state[1], state[1] = state[2], state[2] = state[3];
        return state[3] = (state[3] ^ (state[3] >> 19)) ^ (t ^ (t >> 8));
    }
    bool operator==(const Xorshift &rhs) noexcept { return (this->state == rhs.state); }
    bool operator!=(const Xorshift &rhs) noexcept { return (this->state != rhs.state); }

    constexpr state_type serialize() const noexcept { return this->state; }
    constexpr void deserialize(const state_type state) noexcept { this->state = state; }

    /**
     * @brief a以上b以下の整数を生成
     *
     * @param a
     * @param b
     * @return int [a, b]
     */
    int rand_range(int a, int b) { return a + this->operator()() % (b - a + 1); }

    /**
     * @brief 0.0以上1.0未満の浮動小数点数を生成
     *
     * @return double [0.0, 1.0)
     */
    double random() { return (double)this->operator()() / this->max(); }

  private:
    state_type state;
};

Xorshift rnd;

struct Pos {
    int x, y, z;

    constexpr Pos &operator+=(const Pos &rhs) noexcept {
        this->x += rhs.x, this->y += rhs.y, this->z += rhs.z;
        return *this;
    }
    constexpr Pos &operator-=(const Pos &rhs) noexcept {
        this->x -= rhs.x, this->y -= rhs.y, this->z -= rhs.z;
        return *this;
    }

    constexpr Pos operator+(const Pos &rhs) const noexcept { return Pos(*this) += rhs; }
    constexpr Pos operator-(const Pos &rhs) const noexcept { return Pos(*this) -= rhs; }
    constexpr bool operator==(const Pos &rhs) const noexcept {
        return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z;
    }
    constexpr bool operator!=(const Pos &rhs) const noexcept { return !(*this == rhs); }
    constexpr const int &operator[](int i) const {
        switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
        }
        // assert(false);
    }
    constexpr int &operator[](int i) {
        switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
        }
        // assert(false);
    }

    friend ostream &operator<<(ostream &os, const Pos &rhs) {
        return os << '(' << rhs.x << ',' << rhs.y << ',' << rhs.z << ')';
    }
};

struct Matrix {
    int degree;
    array<array<int, 3>, 3> mat;

    constexpr Matrix() : degree(), mat{} {}

    constexpr Matrix(int k) : degree(2), mat{} {
        // assert(0 <= k && k < 24);
        int x = k >> 3;
        int y = (x + 1) % 3;
        if (k >> 2 & 1) swap(x, y);
        mat[0][x] = (k >> 1 & 1 ? 1 : -1);
        mat[1][y] = (k & 1 ? 1 : -1);
        predict();
    }

    constexpr Pos operator*(const Pos &rhs) const {
        Pos res{};
        rep (i, 3) {
            rep (j, 3) { res[i] += mat[i][j] * rhs[j]; }
        }
        return res;
    }

    constexpr Matrix transpose() const {
        Matrix res;
        rep (i, 3) {
            rep (j, 3) { res.mat[i][j] = mat[j][i]; }
        }
        return res;
    }

    Matrix set(Pos p, Pos q) {
        Matrix res = *this;
        int x = -1, y = -1;
        rep (i, 3) {
            if (p[i] != 0) x = i;
            if (q[i] != 0) y = i;
        }
        // assert(x != -1);
        // assert(y != -1);
        //  rep (i, 3) assert(mat[i][x] == 0);
        //  rep (i, 3) assert(mat[y][i] == 0);
        res.mat[y][x] = 1 * p[x] * q[y];
        if (++res.degree == 2) res.predict();
        return res;
    }

    void predict() {
        pair<int, int> p, q;
        int val = 1;
        rep (x, 3) {
            rep (y, 3) {
                if (mat[x][y] != 0) {
                    val *= mat[x][y];
                    p = {x, y};
                    swap(p, q);
                }
            }
        }
        if ((q.first + 3 - p.first) % 3 == 1) swap(p, q);
        if ((q.second + 3 - p.second) % 3 == 1) val *= -1;
        int x = 3 - p.first - q.first, y = 3 - p.second - q.second;
        mat[x][y] = val;
    }
};

struct SilhouettePos {
    int z, xy;

    constexpr SilhouettePos &operator+=(const SilhouettePos &rhs) noexcept {
        this->z += rhs.z, this->xy += rhs.xy;
        return *this;
    }
    constexpr SilhouettePos &operator-=(const SilhouettePos &rhs) noexcept {
        this->z -= rhs.z, this->xy -= rhs.xy;
        return *this;
    }

    constexpr SilhouettePos operator+(const SilhouettePos &rhs) const noexcept {
        return SilhouettePos(*this) += rhs;
    }
    constexpr SilhouettePos operator-(const SilhouettePos &rhs) const noexcept {
        return SilhouettePos(*this) -= rhs;
    }
    constexpr bool operator==(const SilhouettePos &rhs) const noexcept {
        return this->z == rhs.z && this->xy == rhs.xy;
    }
    constexpr bool operator!=(const SilhouettePos &rhs) const noexcept { return !(*this == rhs); }
};

array<Pos, 6> adjacent_pos = {Pos{1, 0, 0}, {-1, 0, 0}, {0, 1, 0},
                              {0, -1, 0},   {0, 0, 1},  {0, 0, -1}};

array<SilhouettePos, 4> adjacent_silhouette_pos = {SilhouettePos{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

struct Silhouette {
    int silhouette_num;
    vector<bool> x, y;

    Silhouette(int D) : silhouette_num(), x(D * D), y(D * D) {}
    Silhouette(const vector<bool> &x, const vector<bool> &y) : silhouette_num(), x(x), y(y) {
        for (auto e : x) silhouette_num += e;
        for (auto e : y) silhouette_num += e;
    }

    void set_x(int k) {
        // assert(0 <= k && k < (int)x.size());
        if (x[k] == false) {
            ++silhouette_num;
            x[k] = true;
        }
    }

    void set_y(int k) {
        // assert(0 <= k && k < (int)y.size());
        if (y[k] == false) {
            ++silhouette_num;
            y[k] = true;
        }
    }

    template <size_t N>
    bool is_qualified(const bitset<N> &bits, int num) const {
        vector<bool> a(x.size()), b(y.size());
        rep (i, 5) {
            rep (j, 5) {
                rep (k, 5) {
                    a[k * 5 + j] = a[k * 5 + j] | bits[i * 25 + j * 5 + k + 125 * (1 - num)];
                    b[k * 5 + i] = b[k * 5 + i] | bits[i * 25 + j * 5 + k + 125 * (1 - num)];
                }
            }
        }

        return a == x && b == y;
    }
};

struct Object {
    int D;
    vector<int> body;
    Silhouette shadow;
    const Silhouette silhouette;

    Object(int D, const Silhouette &silhouette)
        : D(D), body(D * D * D), shadow(D), silhouette(silhouette) {}

    constexpr bool is_completed() const {
        return shadow.silhouette_num == silhouette.silhouette_num;
    }

    int to_line(int x, int y) const { return x * D + y; }
    int to_line(SilhouettePos p) const { return to_line(p.z, p.xy); }
    int to_line(int x, int y, int z) const { return x * D * D + y * D + z; }
    int to_line(Pos p) const { return to_line(p.x, p.y, p.z); }

    bool in_field(int x) const { return 0 <= x && x < D; }
    bool in_field(SilhouettePos p) const { return in_field(p.z) && in_field(p.xy); }
    bool in_field(int x, int y, int z) const { return in_field(x) && in_field(y) && in_field(z); }
    bool in_field(Pos p) const { return in_field(p.x, p.y, p.z); }

    bool can_put_block(Pos p) const {
        return in_field(p) && body[to_line(p)] == 0 && silhouette.x[to_line(p.z, p.y)] &&
               silhouette.y[to_line(p.z, p.x)];
    }

    vector<Pos> get_adjacent_cube(Pos p) const {
        // assert(in_field(p));
        vector<Pos> res;
        for (auto e : adjacent_pos) {
            if (in_field(p + e)) res.emplace_back(p + e);
        }
        return res;
    }

    vector<SilhouettePos> get_adjacent_silhouette_pos(SilhouettePos p) const {
        // assert(in_field(p));
        vector<SilhouettePos> res;
        for (auto e : adjacent_silhouette_pos) {
            if (in_field(p + e)) res.emplace_back(p + e);
        }
        return res;
    }

    int get_simple_score(Pos p) const {
        return !shadow.x[to_line(p.z, p.y)] + !shadow.y[to_line(p.z, p.x)];
    }

    int get_root_score(Pos pos) const {
        if (D <= 7) return get_simple_score(pos);
        SilhouettePos silhouette_x{pos.z, pos.y}, silhouette_y{pos.z, pos.x};
        int score = 0;
        if (!shadow.x[to_line(silhouette_x)]) {
            ++score;
            bool flag = false;
            for (auto e : get_adjacent_cube(pos)) { flag |= can_put_block(e); }
            if (flag) {
                for (auto e : get_adjacent_silhouette_pos(silhouette_x)) {
                    score += !silhouette.x[to_line(e)] | shadow.x[to_line(e)];
                }
            }
        }
        if (!shadow.y[to_line(silhouette_y)]) {
            ++score;
            bool flag = false;
            for (auto e : get_adjacent_cube(pos)) { flag |= can_put_block(e); }
            if (flag) {
                for (auto e : get_adjacent_silhouette_pos(silhouette_y)) {
                    score += !silhouette.y[to_line(e)] | shadow.y[to_line(e)];
                }
            }
        }
        return score;
    }

    int get_adjacent_score(Pos pos) const {
        if (D <= 7) return get_simple_score(pos);
        SilhouettePos silhouette_x{pos.z, pos.y}, silhouette_y{pos.z, pos.x};
        int score = 0;
        if (!shadow.x[to_line(silhouette_x)]) {
            ++score;
            for (auto e : get_adjacent_silhouette_pos(silhouette_x)) {
                score += !silhouette.x[to_line(e)] | shadow.x[to_line(e)];
            }
        }
        if (!shadow.y[to_line(silhouette_y)]) {
            ++score;
            for (auto e : get_adjacent_silhouette_pos(silhouette_y)) {
                score += !silhouette.y[to_line(e)] | shadow.y[to_line(e)];
            }
        }
        return score;
    }

    Pos pick_cube() const {
        int max_score = -1;
        vector<Pos> max_pos{Pos{-1, -1, -1}};
        rep (x, D) {
            rep (y, D) {
                rep (z, D) {
                    Pos p{x, y, z};
                    if (!can_put_block(p)) continue;
                    int score = get_root_score(p);
                    if (chmax(max_score, score)) max_pos = vector<Pos>{p};
                    else if (max_score == score) max_pos.emplace_back(p);
                }
            }
        }

        // assert(!max_pos.empty());
        int r = rnd() % max_pos.size();
        return max_pos[r];
    }

    Pos select_adjacent_cube(Pos current_pos) const {
        int max_score = -1;
        vector<Pos> max_pos{Pos{-1, -1, -1}};
        for (auto p : get_adjacent_cube(current_pos)) {
            if (!can_put_block(p)) continue;
            int score = get_adjacent_score(p);
            if (chmax(max_score, score)) max_pos = vector<Pos>{p};
            else if (max_score == score) max_pos.emplace_back(p);
        }

        // assert(!max_pos.empty());
        int r = rnd() % max_pos.size();
        return max_pos[r];
    }

    void put_block(const Pos &p, int block_num) {
        // assert(in_field(p));
        // assert(body[to_line(p)] == 0);
        body[to_line(p)] = block_num;
        shadow.set_x(to_line(p.z, p.y));
        shadow.set_y(to_line(p.z, p.x));
    }
};

struct Result {
    int block_num;
    vector<int> body1, body2;

    Result() {}
    Result(int block_num, const vector<int> &body1, const vector<int> &body2)
        : block_num(block_num), body1(body1), body2(body2) {}
};

struct Field {
    const int D;
    int block_num;
    Object object1, object2;

    Field(int D, const Silhouette &silhouette1, const Silhouette &silhouette2)
        : D(D), block_num(), object1(D, silhouette1), object2(D, silhouette2) {}

    constexpr bool is_completed() const { return object1.is_completed() && object2.is_completed(); }

    int to_line(int x, int y) const { return x * D + y; }
    int to_line(SilhouettePos p) const { return to_line(p.z, p.xy); }
    int to_line(int x, int y, int z) const { return x * D * D + y * D + z; }
    int to_line(Pos p) const { return to_line(p.x, p.y, p.z); }
    Pos to_pos(int x) const { return Pos{x / D / D, x / D % D, x % D}; }

    bool in_field(int x) const { return 0 <= x && x < D; }
    bool in_field(SilhouettePos p) const { return in_field(p.z) && in_field(p.xy); }
    bool in_field(int x, int y, int z) const { return in_field(x) && in_field(y) && in_field(z); }
    bool in_field(Pos p) const { return in_field(p.x, p.y, p.z); }

    bool can_put_block_first(Pos p) const { return object1.can_put_block(p); }
    bool can_put_block_second(Pos p) const { return object2.can_put_block(p); }

    vector<Pos> get_adjacent_cube(Pos p) const {
        // assert(in_field(p));
        vector<Pos> res;
        for (auto e : adjacent_pos) {
            if (in_field(p + e)) res.emplace_back(p + e);
        }
        return res;
    }

    vector<SilhouettePos> get_adjacent_silhouette_pos(SilhouettePos p) const {
        // assert(in_field(p));
        vector<SilhouettePos> res;
        for (auto e : adjacent_silhouette_pos) {
            if (in_field(p + e)) res.emplace_back(p + e);
        }
        return res;
    }

    Pos pick_cube_first() const { return object1.pick_cube(); }
    Pos pick_cube_second() const { return object2.pick_cube(); }

    Pos select_adjacent_cube_first(Pos p) const { return object1.select_adjacent_cube(p); }
    Pos select_adjacent_cube_second(Pos p) const { return object2.select_adjacent_cube(p); }

    void select_k_block(int k) {
        vector<Pos> u, v;
        Matrix mat;
        {
            auto p = pick_cube_first();
            auto q = pick_cube_second();
            u.emplace_back(p);
            v.emplace_back(q);
            put_block(p, q, true);
            if (p == Pos{-1, -1, -1} || q == Pos{-1, -1, -1}) return;
        }
        rep (_, k) {
            int max_score = -1;
            vector<pair<Pos, Pos>> max_pos;
            vector<Matrix> max_matrix;
            rep (i, u.size()) {
                auto p = u[i], q = v[i];
                for (auto e : get_adjacent_cube(p)) {
                    if (!can_put_block_first(e)) continue;
                    int score1 = object1.get_adjacent_score(e);
                    auto d = e - p;
                    if (mat * d == Pos{0, 0, 0}) {
                        for (auto f : get_adjacent_cube(q)) {
                            if (!can_put_block_second(f)) continue;
                            if (mat.transpose() * (f - q) != Pos{0, 0, 0}) continue;
                            int score2 = object2.get_adjacent_score(f);
                            if (chmax(max_score, score1 + score2)) {
                                max_pos = vector<pair<Pos, Pos>>{{e, f}};
                                max_matrix = vector<Matrix>{mat.set(e - p, f - q)};
                            } else if (max_score == score1 + score2) {
                                max_pos.emplace_back(e, f);
                                max_matrix.emplace_back(mat.set(e - p, f - q));
                            }
                        }
                    } else {
                        auto f = q + mat * d;
                        if (!can_put_block_second(f)) continue;
                        int score2 = object2.get_adjacent_score(f);
                        if (chmax(max_score, score1 + score2)) {
                            max_pos = vector<pair<Pos, Pos>>{{e, f}};
                            max_matrix = vector<Matrix>{mat};
                        } else if (max_score == score1 + score2) {
                            max_pos.emplace_back(e, f);
                            max_matrix.emplace_back(mat);
                        }
                    }
                }
            }
            if (max_score == -1) break;
            // assert(!max_pos.empty() && max_pos.size() == max_matrix.size());
            int r = rnd() % max_pos.size();
            u.emplace_back(max_pos[r].first);
            v.emplace_back(max_pos[r].second);
            put_block(max_pos[r].first, max_pos[r].second, false);
            mat = max_matrix[r];
        }
    }

    template <int MAX_SCORE>
    void select_block() {
        vector<Pos> u, v;
        Matrix mat;
        {
            auto p = pick_cube_first();
            auto q = pick_cube_second();
            u.emplace_back(p);
            v.emplace_back(q);
            put_block(p, q, true);
            if (p == Pos{-1, -1, -1} || q == Pos{-1, -1, -1}) return;
        }
        while (true) {
            int max_score = MAX_SCORE;
            vector<pair<Pos, Pos>> max_pos;
            vector<Matrix> max_matrix;
            rep (i, u.size()) {
                auto p = u[i], q = v[i];
                for (auto e : get_adjacent_cube(p)) {
                    if (!can_put_block_first(e)) continue;
                    int score1 = object1.get_adjacent_score(e);
                    auto d = e - p;
                    if (mat * d == Pos{0, 0, 0}) {
                        for (auto f : get_adjacent_cube(q)) {
                            if (!can_put_block_second(f)) continue;
                            if (mat.transpose() * (f - q) != Pos{0, 0, 0}) continue;
                            int score2 = object2.get_adjacent_score(f);
                            if (chmax(max_score, score1 + score2)) {
                                max_pos = vector<pair<Pos, Pos>>{{e, f}};
                                max_matrix = vector<Matrix>{mat.set(e - p, f - q)};
                            } else if (max_score == score1 + score2) {
                                max_pos.emplace_back(e, f);
                                max_matrix.emplace_back(mat.set(e - p, f - q));
                            }
                        }
                    } else {
                        auto f = q + mat * d;
                        if (!can_put_block_second(f)) continue;
                        int score2 = object2.get_adjacent_score(f);
                        if (chmax(max_score, score1 + score2)) {
                            max_pos = vector<pair<Pos, Pos>>{{e, f}};
                            max_matrix = vector<Matrix>{mat};
                        } else if (max_score == score1 + score2) {
                            max_pos.emplace_back(e, f);
                            max_matrix.emplace_back(mat);
                        }
                    }
                }
            }
            if (max_score == MAX_SCORE) break;
            // assert(!max_pos.empty() && max_pos.size() == max_matrix.size());
            int r = rnd() % max_pos.size();
            u.emplace_back(max_pos[r].first);
            v.emplace_back(max_pos[r].second);
            put_block(max_pos[r].first, max_pos[r].second, false);
            mat = max_matrix[r];
        }
    }

    void put_block(const Pos &p, const Pos &q, bool is_increment = true) {
        if (is_increment) ++block_num;
        if (p != Pos{-1, -1, -1}) object1.put_block(p, block_num);
        if (q != Pos{-1, -1, -1}) object2.put_block(q, block_num);
    }

    void put_block(const vector<Pos> &block1, const vector<Pos> &block2, bool is_increment = true) {
        if (is_increment) ++block_num;
        for (auto p : block1) {
            if (p == Pos{-1, -1, -1}) continue;
            object1.put_block(p, block_num);
        }
        for (auto p : block2) {
            if (p == Pos{-1, -1, -1}) continue;
            object2.put_block(p, block_num);
        }
    }

    Result get_max_block() {
        vector<Pos> max_u, max_v;
        vector<Pos> u, v;
        unordered_map<bitset<250>, double> mp;
        mp[bitset<250>()] = 0;
        rep (k, 24) {
            Matrix mat(k);
            rep (i, D * D * D) {
                rep (j, D * D * D) {
                    {
                        Pos p{i % D, i / D % D, i / D / D};
                        if (!can_put_block_first(p)) continue;
                        Pos q{j % D, j / D % D, j / D / D};
                        if (!can_put_block_second(q)) continue;
                        u.clear();
                        u.emplace_back(p);
                        v.clear();
                        v.emplace_back(q);
                    }
                    put_block(u[0], v[0], true);
                    while (true) {
                        int max_score = -1;
                        Pos max_p{-1, -1, -1}, max_q{-1, -1, -1};
                        rep (i, u.size()) {
                            auto p = u[i], q = v[i];
                            for (auto e : get_adjacent_cube(p)) {
                                if (!can_put_block_first(e)) continue;
                                auto d = e - p;
                                auto f = q + mat * d;
                                if (!can_put_block_second(f)) continue;
                                if (chmax(max_score, object1.get_simple_score(e) +
                                                         object2.get_simple_score(f))) {
                                    max_p = e, max_q = f;
                                }
                            }
                        }

                        if (max_score == -1) break;
                        u.emplace_back(max_p);
                        v.emplace_back(max_q);
                        put_block(max_p, max_q, false);
                    }

                    if (u.size() > max_u.size()) {
                        max_u = u;
                        max_v = v;
                    }
                    fill(object1.body.begin(), object1.body.end(), 0);
                    fill(object2.body.begin(), object2.body.end(), 0);
                    fill(object1.shadow.x.begin(), object1.shadow.x.end(), false);
                    fill(object1.shadow.y.begin(), object1.shadow.y.end(), false);
                    fill(object2.shadow.x.begin(), object2.shadow.x.end(), false);
                    fill(object2.shadow.y.begin(), object2.shadow.y.end(), false);

                    if (u.size() < 7) continue;

                    bitset<250> bit;
                    for (auto p : u) bit.set(to_line(p));
                    bit <<= 125;
                    for (auto q : v) bit.set(to_line(q));
                    for (auto &&[x, y] : mp) {
                        if ((bit & x).count() == 0) {
                            if (mp.find(bit | x) == mp.end()) mp[bit | x] = y + 1 / u.size();
                            else chmin(mp[bit | x], y + 1 / u.size());
                        }
                    }
                }
            }
        }

        int m = 0;
        bool flag = false;
        bitset<250> ans;
        for (auto &&[x, y] : mp) {
            flag |= object1.silhouette.is_qualified(x, 0) && object2.silhouette.is_qualified(x, 1);
            if (chmax(m, x.count())) ans = x;
        }
        cerr << flag << m << endl;

        vector<Pos> a, b;
        rep (i, 125) {
            if (ans[i + 125]) a.emplace_back(to_pos(i));
            if (ans[i]) b.emplace_back(to_pos(i));
        }
        Field res(D, object1.silhouette, object2.silhouette);
        res.put_block(a, b);
        return Result(res.block_num, res.object1.body, res.object2.body);

        // Field res(D, object1.silhouette, object2.silhouette);
        // cerr << max_u.size() << endl;
        // res.put_block(max_u, max_v);
        // return Result(res.block_num, res.object1.body, res.object2.body);
    }
};

template <int MAX_SCORE = -1>
struct Solver {
    int D, k;
    Field field;

    Solver(int D, const Silhouette &silhouette1, const Silhouette &silhouette2, int k = 0)
        : D(D), k(k), field(D, silhouette1, silhouette2) {}

    Result get_max_block() { return field.get_max_block(); }

    Result solve() {
        while (!field.is_completed()) {
            if (k == 0) field.select_block<MAX_SCORE>();
            else field.select_k_block(k);
            // field.put_block(u, v);
        }

        return Result(field.block_num, field.object1.body, field.object2.body);
    }
};

Silhouette read_silhouette(int D) {
    Silhouette silhouette(D);
    rep (i, D) {
        string s;
        std::cin >> s;
        rep (j, D) {
            if (s[j] == '1') silhouette.set_y(i * D + j);
        }
    }
    rep (i, D) {
        string s;
        std::cin >> s;
        rep (j, D) {
            if (s[j] == '1') silhouette.set_x(i * D + j);
        }
    }
    return silhouette;
}

int get_max_cube(int D, const Silhouette &silhouette) {
    int sum = 0;
    rep (x, D) {
        rep (y, D) {
            rep (z, D) { sum += silhouette.x[z * D + y] & silhouette.y[z * D + x]; }
        }
    }
    return sum;
}

long calc_score(const Result &result) {
    int block_num = result.block_num;
    auto &blocks1 = result.body1;
    auto &blocks2 = result.body2;
    vector<int> cnt1(block_num + 1), cnt2(block_num + 1);
    for (auto x : blocks1) ++cnt1[x];
    for (auto x : blocks2) ++cnt2[x];
    double sum = 0;
    rep (i, block_num) {
        int x = cnt1[i + 1], y = cnt2[i + 1], z = max(x, y);
        if (x != 0 && y != 0) {
            // assert(x == y);
            sum += 1. / x;
        } else {
            // assert(z != 0);
            sum += z;
        }
    }
    return (long)round(sum * 1000000000);
}

void write_answer(const Result &result) {
    int block_num = result.block_num;
    auto &blocks1 = result.body1;
    auto &blocks2 = result.body2;
    std::cout << block_num << std::endl;
    for (auto it = blocks1.begin(); it != blocks1.end(); ++it) {
        std::cout << (it == blocks1.begin() ? "" : " ") << *it;
    }
    std::cout << std::endl;
    for (auto it = blocks2.begin(); it != blocks2.end(); ++it) {
        std::cout << (it == blocks2.begin() ? "" : " ") << *it;
    }
    std::cout << std::endl;
}

int main(void) {
    int D;
    std::cin >> D;
    auto silhouette1 = read_silhouette(D);
    auto silhouette2 = read_silhouette(D);

    long score = numeric_limits<long>::max();
    Result answer;
    int max_size = min(get_max_cube(D, silhouette1), get_max_cube(D, silhouette2));
    int k = 2;
    int x = -1, y = -1;
    while ((double)clock() / CLOCKS_PER_SEC < 5.8) {
        {
            Solver<-1> solver(D, silhouette1, silhouette2);
            auto &&result = solver.solve();
            if (chmin(score, calc_score(result))) {
                answer = result;
                x = -1, y = 0;
            }
        }
        {
            Solver<0> solver(D, silhouette1, silhouette2);
            auto &&result = solver.solve();
            if (chmin(score, calc_score(result))) {
                answer = result;
                x = 0, y = 0;
            }
        }
        {
            int z = k % (max_size - 1) + 2;
            Solver<-1> solver(D, silhouette1, silhouette2, z);
            auto &&result = solver.solve();
            if (chmin(score, calc_score(result))) {
                answer = result;
                x = -1, y = z;
            }
        }
        {
            int z = k % (max_size - 1) + 2;
            Solver<0> solver(D, silhouette1, silhouette2, z);
            auto &&result = solver.solve();
            if (chmin(score, calc_score(result))) {
                answer = result;
                x = 0, y = z;
            }
        }
        ++k;
    }

    write_answer(answer);
    std::cerr << x << ' ' << y << ' ' << k << endl;
    std::cerr << "Score = " << calc_score(answer) << std::endl;

    return 0;
}
