#include <bits/stdc++.h>

template <class T, class U>
constexpr bool chmax(T &a, const U &b) {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
constexpr bool chmin(T &a, const U &b) {
    return (T)b < a ? a = (T)b, true : false;
}

using namespace std;

namespace lib {

struct Timer {
    std::chrono::system_clock::time_point start;

    Timer() : start(std::chrono::system_clock::now()) {}

    int64_t operator()() const { return this->get_time(); }

    int64_t get_time() const {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count();
    }

    void reset() { this->start = std::chrono::system_clock::now(); }
};

template <class T>
struct Trace {
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

};  // namespace lib
using namespace lib;

static constexpr int ERROR_BIAS = 10000;
constexpr int N = 20;
constexpr int H = 1000;
int K, T, D;

struct Color {
    double c, m, y;

    constexpr Color() : c(), m(), y() {}

    double length() const { return sqrt(c * c + m * m + y * y); }
    double length2() const { return c * c + m * m + y * y; }

    double score(const Color &target) const { return (*this - target).length(); }

    constexpr Color &operator+=(const Color &rhs) {
        c += rhs.c, m += rhs.m, y += rhs.y;
        return *this;
    }
    constexpr Color &operator-=(const Color &rhs) {
        c -= rhs.c, m -= rhs.m, y -= rhs.y;
        return *this;
    }
    constexpr Color &operator*=(double rhs) {
        c *= rhs, m *= rhs, y *= rhs;
        return *this;
    }
    constexpr Color &operator/=(double rhs) {
        c /= rhs, m /= rhs, y /= rhs;
        return *this;
    }

    friend constexpr Color operator+(const Color &lhs, const Color &rhs) { return Color(lhs) += rhs; }
    friend constexpr Color operator-(const Color &lhs, const Color &rhs) { return Color(lhs) -= rhs; }
    friend constexpr Color operator*(const Color &lhs, double rhs) { return Color(lhs) *= rhs; }
    friend constexpr Color operator*(double lhs, const Color &rhs) { return Color(rhs) *= lhs; }
    friend constexpr Color operator/(const Color &lhs, double rhs) { return Color(lhs) /= rhs; }
    friend std::istream &operator>>(std::istream &is, Color &rhs) { return is >> rhs.c >> rhs.m >> rhs.y; }
};

struct Parameter {
    vector<Color> own_color;
    array<Color, H> target_color;

    friend std::istream &operator>>(std::istream &is, Parameter &rhs) {
        int tmp;
        is >> tmp >> K >> tmp >> T >> D;
        rhs.own_color.resize(K);
        for (auto &c : rhs.own_color) is >> c;
        for (auto &c : rhs.target_color) is >> c;
        return is;
    }
};

struct Point2D {
    int x, y;

    constexpr bool in_field() const { return 0 <= x && x < N && 0 <= y && y < N; }

    constexpr Point2D &operator+=(const Point2D &rhs) {
        x += rhs.x, y += rhs.y;
        return *this;
    }
    constexpr Point2D &operator-=(const Point2D &rhs) {
        x -= rhs.x, y -= rhs.y;
        return *this;
    }
    constexpr bool operator==(const Point2D &rhs) const { return x == rhs.x && y == rhs.y; }
    constexpr bool operator!=(const Point2D &rhs) const { return x != rhs.x || y != rhs.y; }

    friend constexpr Point2D operator+(const Point2D &lhs, const Point2D &rhs) { return Point2D(lhs) += rhs; }
    friend constexpr Point2D operator-(const Point2D &lhs, const Point2D &rhs) { return Point2D(lhs) -= rhs; }

    friend std::ostream &operator<<(std::ostream &os, const Point2D &rhs) { return os << rhs.x << ' ' << rhs.y; }
};

array<Point2D, 4> directions = {Point2D{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

struct Board {
    array<array<unsigned, N>, N> board;

    Board() : board{} {}

    constexpr void fill() {
        for (int i = 0; i < N; ++i) board[i].fill(15);
    }
    constexpr void clear() {
        for (int i = 0; i < N; ++i) board[i].fill(0);
    }

    void add_divider(Point2D l, Point2D r) {
        for (int loop = 0; loop < 2; ++loop) {
            auto d = r - l;
            for (int k = 0; k < 4; ++k) {
                if (d == directions[k]) {
                    board[l.x][l.y] |= 1 << k;
                }
            }
            swap(l, r);
        }
    }

    void delete_divider(Point2D l, Point2D r) {
        for (int loop = 0; loop < 2; ++loop) {
            auto d = r - l;
            for (int k = 0; k < 4; ++k) {
                if (d == directions[k]) {
                    board[l.x][l.y] &= ~(1 << k);
                }
            }
            swap(l, r);
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Board &rhs) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N - 1; ++j) {
                os << (rhs.board[i][j] & 1) << ' ';
            }
            os << '\n';
        }
        for (int i = 0; i < N - 1; ++i) {
            for (int j = 0; j < N; ++j) {
                cout << (rhs.board[i][j] >> 2 & 1) << ' ';
            }
            cout << '\n';
        }
        return os;
    }
};

struct Operation {
    int type, paint;
    Point2D p, q;

    Operation(int _t, Point2D _p) : type(_t), p(_p) {}
    Operation(int _t, Point2D _p, int _k) : type(_t), p(_p), paint(_k) {}
    Operation(int _t, Point2D _p, Point2D _q) : type(_t), p(_p), q(_q) {}

    friend std::ostream &operator<<(std::ostream &os, const Operation &rhs) {
        if (rhs.type == 1) {
            os << rhs.type << ' ' << rhs.p << ' ' << rhs.paint;
        } else if (rhs.type == 2 || rhs.type == 3) {
            os << rhs.type << ' ' << rhs.p;
        } else if (rhs.type == 4) {
            os << rhs.type << ' ' << rhs.p << ' ' << rhs.q;
        }
        return os;
    }
};

struct Generator {
    double score;
    vector<Operation> operations;

    Generator() : score(numeric_limits<double>::max()) {}
    Generator(double d, vector<Operation> v) : score(d), operations(v) {}

    int size() const { return operations.size(); }

    constexpr bool operator<(const Generator &rhs) const { return score < rhs.score; }

    friend std::ostream &operator<<(std::ostream &os, const Generator &rhs) {
        for (auto &op : rhs.operations) os << op << '\n';
        return os;
    }
};

struct Solution {
    double score;
    Board board;
    vector<Operation> operations;

    Solution(Board b) : score(), board(b), operations() {}

    void add_generator(const Generator &gen) {
        score += gen.score;
        operations.insert(operations.end(), gen.operations.begin(), gen.operations.end());
    }

    friend std::ostream &operator<<(std::ostream &os, const Solution &rhs) {
        os << rhs.board;
        for (auto &op : rhs.operations) os << op << '\n';
        return os;
    }
};

struct ColorInfo {
    Color color;
    int amount;
};

struct ColorDetailedInfo {
    Color color;
    double amount, product;
};

struct PalletInfo {
    Color color;
    int amount, paint_flag, rest, position;
};

struct Solver {
    static constexpr int BORDER = 15;
    Board board;
    vector<Point2D> ordered_pallet_point;
    vector<Color> own_color;
    array<Color, H> target_color;
    vector<ColorInfo> colors;
    array<int, H> best_color;
    vector<PalletInfo> pallets;
    int rest_size;

    Solver(const Parameter &param) : own_color(param.own_color), target_color(param.target_color) {}

    void setup() {
        rest_size = 400;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) ordered_pallet_point.emplace_back(i, j);
        }
        for (int i = 0; i < N / 2; ++i)
            reverse(ordered_pallet_point.begin() + N * (2 * i + 1), ordered_pallet_point.begin() + N * (2 * i + 2));

        board.fill();
        for (int i = 0; i < N * N - 1; ++i) board.delete_divider(ordered_pallet_point[i], ordered_pallet_point[i + 1]);
    }

    Solution solve() {
        setup();
        array<Generator, H> answer;
        answer = solve_best();
        Solution sol(board);
        for (auto &gen : answer) sol.add_generator(gen);
        cerr << sol.score << endl;
        return sol;
    }

  private:
    double calculate_optimized_score(int x, int y, int h) const {
        auto dc = own_color[y] - own_color[x];
        auto dt = target_color[h] - own_color[x];
        double sum = (dc.c * dt.c + dc.m * dt.m + dc.y * dt.y) / dc.length2();
        sum = clamp(sum, 0., 1.);
        return (own_color[x] * (1 - sum) + own_color[y] * sum).score(target_color[h]);
    }

    void generate_mixed_color() {
        if (K > BORDER) return;
        int max_type = 1;
        if (K <= 5) {
            for (int i = 0; i < K; ++i) max_type *= 3;
        } else {
            max_type = 1 << K;
        }
        colors.resize(max_type);
        if (K <= 5) {
            for (int bit = 1; bit < max_type; ++bit) {
                int mask = bit;
                for (int i = 0; i < K; ++i) {
                    int t = mask % 3;
                    colors[bit].color += own_color[i] * t;
                    colors[bit].amount += t;
                    mask /= 3;
                }
            }
        } else {
            for (int i = 0; i < K; ++i) colors[1 << i] = {own_color[i], 1};
            for (int bit = 1; bit < max_type; ++bit) {
                if (colors[bit].amount == 1) continue;
                for (int i = 0; i < K; ++i) {
                    if (bit >> i & 1) {
                        colors[bit] = {colors[bit ^ (1 << i)].color + own_color[i], colors[bit ^ (1 << i)].amount + 1};
                        break;
                    }
                }
            }
        }
        for (int bit = 1; bit < max_type; ++bit) colors[bit].color /= colors[bit].amount;
    }

    void generate_min_color() {
        best_color.fill(-1);
        if (K > BORDER) return;
        int type_size = colors.size();
        vector<vector<int>> min_colors(type_size);
        vector<double> min_scores(H, numeric_limits<double>::max());
        for (int h = 0; h < H; ++h) {
            for (int i = 0; i < K; ++i) {
                for (int j = 0; j < K; ++j) {
                    if (i == j) continue;
                    chmin(min_scores[h], calculate_optimized_score(i, j, h));
                }
            }
            int min_color = -1;
            for (int k = 1; k < type_size; ++k) {
                if (chmin(min_scores[h], colors[k].color.score(target_color[h]))) min_color = k;
            }
            if (min_color != -1) min_colors[min_color].emplace_back(h);
        }
        for (int k = 1; k < type_size; ++k) {
            if (colors[k].amount == 1 || min_colors[k].size() < colors[k].amount) continue;
            pallets.emplace_back(colors[k].color, colors[k].amount, k, 0, 0);
            sort(min_colors[k].begin(), min_colors[k].end(), [&](int x, int y) {
                return min_scores[x] < min_scores[y];
            });
        }
        sort(pallets.begin(), pallets.end(), [&](auto l, auto r) {
            return l.amount > r.amount;
        });
        for (int j = 0; j < (int)pallets.size(); ++j) {
            rest_size -= pallets[j].amount;
            pallets[j].position = rest_size;
            board.add_divider(ordered_pallet_point[rest_size - 1], ordered_pallet_point[rest_size]);
            for (int i = 0; i < min_colors[pallets[j].paint_flag].size() / pallets[j].amount * pallets[j].amount; ++i) {
                best_color[min_colors[pallets[j].paint_flag][i]] = j;
            }
            if (rest_size < 100) break;
        }
    }

    vector<Operation> create_mixed_color(int pallet_index) {
        auto &pallet = pallets[pallet_index];
        int flag = pallet.paint_flag;
        vector<Operation> operations =
            create_mixed_color_operation(pallet.paint_flag, ordered_pallet_point[pallet.position]);
        pallet.rest = pallet.amount;
        return operations;
    }

    vector<Operation> create_mixed_color_operation(int paint_flag, Point2D point) {
        vector<Operation> operations;
        for (int k = 0; k < K; ++k) {
            if (K <= 5) {
                int t = paint_flag % 3;
                for (int _ = 0; _ < t; ++_) operations.emplace_back(1, point, k);
                paint_flag /= 3;
            } else {
                if (paint_flag >> k & 1) operations.emplace_back(1, point, k);
            }
        }
        return operations;
    }

    array<Generator, H> solve_best() {
        array<Generator, H> generators;
        vector<vector<Generator>> candidates_of_generator(H, vector<Generator>(60));
        generate_mixed_color();
        generate_min_color();
        int type_size = colors.size();
        for (int h = 0; h < H; ++h) {
            if (best_color[h] != -1) {
                auto &pallet = pallets[best_color[h]];
                vector<Operation> operations;
                if (pallet.rest == 0) {
                    operations = create_mixed_color(best_color[h]);
                }
                --pallet.rest;
                operations.emplace_back(2, ordered_pallet_point[pallet.position]);
                candidates_of_generator[h][operations.size()] =
                    Generator{pallet.color.score(target_color[h]), operations};
                continue;
            }
            if (K <= BORDER) {
                int max_amount = 0;
                for (int i = 1; i < type_size; ++i) chmax(max_amount, colors[i].amount);
                vector<double> min_score(max_amount + 1, numeric_limits<double>::max());
                vector<int> min_bit(max_amount + 1, -1);
                for (int i = 1; i < type_size; ++i) {
                    int c = colors[i].amount;
                    if (chmin(min_score[c], colors[i].color.score(target_color[h]) + (double)D * (c - 1) / 10000))
                        min_bit[c] = i;
                }
                for (int c = 0; c < max_amount + 1; ++c) {
                    if (min_bit[c] == -1) continue;
                    vector<Operation> operations = create_mixed_color_operation(min_bit[c], {0, 0});
                    operations.emplace_back(2, Point2D{0, 0});
                    for (int i = 0; i < c - 1; ++i) {
                        operations.emplace_back(3, Point2D{0, 0});
                    }
                    chmin(candidates_of_generator[h][operations.size()], Generator{min_score[c], operations});
                }
            } else {
                for (int i = 0; i < K; ++i) {
                    {  // single color
                        vector<Operation> operations;
                        operations.emplace_back(1, Point2D{0, 0}, i);
                        operations.emplace_back(2, Point2D{0, 0});
                        chmin(candidates_of_generator[h][operations.size()],
                              Generator{own_color[i].score(target_color[h]), operations});
                    }
                    for (int j = i + 1; j < K; ++j) {
                        vector<Operation> operations;
                        operations.emplace_back(1, Point2D{0, 0}, i);
                        operations.emplace_back(1, Point2D{0, 0}, j);
                        operations.emplace_back(2, Point2D{0, 0});
                        operations.emplace_back(3, Point2D{0, 0});
                        auto mixed_color = (own_color[i] + own_color[j]) / 2;
                        chmin(candidates_of_generator[h][operations.size()],
                              Generator{mixed_color.score(target_color[h]) + (double)D / 10000, operations});
                    }
                }
            }

            {
                double min_distance = numeric_limits<double>::max();
                int min_color = -1;
                vector<pair<int, int>> data;
                for (int k = 0; k < K; ++k) {
                    if (chmin(min_distance, own_color[k].score(target_color[h]))) min_color = k;
                }
                ColorDetailedInfo mixed_color{own_color[min_color], 1., 1.};
                data.emplace_back(min_color, rest_size);
                for (int d = 1; d < 10; ++d) {
                    min_distance = numeric_limits<double>::max();
                    min_color = -1;
                    int min_t = -1;
                    for (int k = 0; k < K; ++k) {
                        auto dc = (mixed_color.color + own_color[k] * mixed_color.product) /
                                      (mixed_color.amount + mixed_color.product) -
                                  mixed_color.color / mixed_color.amount;
                        if (dc.length2() < 1e-20) {
                            if (chmin(min_distance, ((mixed_color.color + own_color[k] * mixed_color.product) /
                                                     (mixed_color.amount + mixed_color.product))
                                                        .score(target_color[h])))
                                min_color = k, min_t = rest_size;
                            continue;
                        }
                        auto dt = target_color[h] - mixed_color.color / mixed_color.amount;
                        double sum = (dc.c * dt.c + dc.m * dt.m + dc.y * dt.y) / dc.length2();
                        sum = clamp(sum, 0., 1.);
                        int t = round(rest_size * sum);
                        if (chmin(min_distance,
                                  ((mixed_color.color + own_color[k] * mixed_color.product * t / rest_size) /
                                   (mixed_color.amount + mixed_color.product * t / rest_size))
                                      .score(target_color[h])))
                            min_color = k, min_t = t;
                    }
                    if (min_t == 0 || mixed_color.product == 0) break;
                    mixed_color.product *= (double)min_t / rest_size;
                    mixed_color.color += own_color[min_color] * mixed_color.product;
                    mixed_color.amount += mixed_color.product;
                    vector<Operation> operations;
                    data.emplace_back(min_color, min_t);
                    ColorDetailedInfo gen_color{};
                    for (auto [color, t] : data | views::reverse) {
                        operations.emplace_back(1, Point2D{0, 0}, color);
                        gen_color.color += own_color[color];
                        gen_color.amount += 1;
                        if (t < rest_size) {
                            operations.emplace_back(4, ordered_pallet_point[rest_size - t - 1],
                                                    ordered_pallet_point[rest_size - t]);
                            for (int _ = 0; _ < (int)ceil(gen_color.amount * (rest_size - t) / rest_size); ++_)
                                operations.emplace_back(3, Point2D{0, 0});
                            operations.emplace_back(4, ordered_pallet_point[rest_size - t - 1],
                                                    ordered_pallet_point[rest_size - t]);
                            gen_color.amount *= (double)t / rest_size;
                        }
                    }
                    operations.emplace_back(2, Point2D{0, 0});
                    for (int _ = 0; _ < (int)ceil(gen_color.amount - 1); ++_) operations.emplace_back(3, Point2D{0, 0});
                    chmin(candidates_of_generator[h][operations.size()],
                          Generator{min_distance + (double)D * d / ERROR_BIAS, operations});
                }
            }

            for (int i = 0; i < K; ++i) {
                for (int j = 0; j < K; ++j) {
                    if (i == j) continue;
                    auto dc = own_color[j] - own_color[i];
                    auto dt = target_color[h] - own_color[i];
                    double sum = (dc.c * dt.c + dc.m * dt.m + dc.y * dt.y) / dc.length2();
                    if (0 < sum && sum <= 0.5) {
                    } else {
                        continue;
                    }
                    int t = round(rest_size * sum / (1 - sum));
                    if (t <= 0 || t >= rest_size) continue;
                    vector<Operation> operations;
                    operations.emplace_back(1, Point2D{0, 0}, j);
                    operations.emplace_back(4, ordered_pallet_point[t - 1], ordered_pallet_point[t]);
                    operations.emplace_back(1, Point2D{0, 0}, i);
                    operations.emplace_back(2, Point2D{0, 0});
                    operations.emplace_back(4, ordered_pallet_point[t - 1], ordered_pallet_point[t]);
                    operations.emplace_back(3, Point2D{0, 0});
                    chmin(candidates_of_generator[h][operations.size()],
                          Generator{((own_color[j] * t / rest_size + own_color[i]) * rest_size / (rest_size + t))
                                            .score(target_color[h]) +
                                        (double)D / 10000,
                                    operations});
                }
            }
        }

        int total_turn = 0;
        priority_queue<tuple<double, int, int, int>, vector<tuple<double, int, int, int>>, greater<>> p_que;
        array<int, H> selected_generators;
        for (int h = 0; h < H; ++h) {
            int min_idx = min_element(candidates_of_generator[h].begin(), candidates_of_generator[h].end()) -
                          candidates_of_generator[h].begin();
            selected_generators[h] = min_idx;
            total_turn += min_idx;
            int alternative_idx =
                min_element(candidates_of_generator[h].begin(), candidates_of_generator[h].begin() + min_idx) -
                candidates_of_generator[h].begin();
            if (alternative_idx >= 2) {
                p_que.emplace(
                    candidates_of_generator[h][alternative_idx].score - candidates_of_generator[h][min_idx].score,
                    min_idx, alternative_idx, h);
            }
        }
        while (total_turn > T) {
            auto [diff_score, min_idx, alternative_idx, h] = p_que.top();
            p_que.pop();
            total_turn -= min_idx - alternative_idx;
            selected_generators[h] = alternative_idx;
            int second_idx =
                min_element(candidates_of_generator[h].begin(), candidates_of_generator[h].begin() + alternative_idx) -
                candidates_of_generator[h].begin();
            if (second_idx >= 2) {
                p_que.emplace(
                    candidates_of_generator[h][second_idx].score - candidates_of_generator[h][alternative_idx].score,
                    alternative_idx, second_idx, h);
            }
        }
        for (int h = 0; h < H; ++h) {
            generators[h] = candidates_of_generator[h][selected_generators[h]];
        }
        cerr << total_turn << '\n';
        return generators;
    }
};

template <int NUMBER_OF_GROUPS>
struct KMeansSolver {
    vector<Color> own_color;
    array<Color, H> target_color;
    Board board;
    vector<Point2D> ordered_pallet_point;

    KMeansSolver(const Parameter &param) : own_color(param.own_color), target_color(param.target_color) {}

    void setup() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) ordered_pallet_point.emplace_back(i, j);
        }
        for (int i = 0; i < N / 2; ++i) {
            reverse(ordered_pallet_point.begin() + N * (2 * i + 1), ordered_pallet_point.begin() + N * (2 * i + 2));
        }
        board.fill();
        for (int i = 0; i < N * N - 1; ++i) board.delete_divider(ordered_pallet_point[i], ordered_pallet_point[i + 1]);
    }

    Solution solve() {
        setup();
        vector<Color> center_of_group(NUMBER_OF_GROUPS);
        set<int> st;
        mt19937 mt;
        for (int i = 0; i < NUMBER_OF_GROUPS; ++i) {
            int x = mt() % H;
            while (st.count(x)) x = mt() % H;
            center_of_group[i] = target_color[x];
            st.emplace(x);
        }
        array<int, H> group_number;
        vector<int> group_count(NUMBER_OF_GROUPS);
        for (int loop = 0; loop < 100; ++loop) {
            for (int h = 0; h < H; ++h) {
                double min_distance = numeric_limits<double>::max();
                for (int i = 0; i < NUMBER_OF_GROUPS; ++i) {
                    if (chmin(min_distance, target_color[h].score(center_of_group[i]))) group_number[h] = i;
                }
            }
            for (int i = 0; i < NUMBER_OF_GROUPS; ++i) center_of_group[i] = Color();
            group_count.assign(NUMBER_OF_GROUPS, 0);
            for (int h = 0; h < H; ++h) {
                center_of_group[group_number[h]] += target_color[h];
                ++group_count[group_number[h]];
            }
            for (int i = 0; i < NUMBER_OF_GROUPS; ++i) {
                // TODO
                assert(group_count[i]);
                center_of_group[i] /= group_count[i];
            }
        }

        for (int _ = 0; _ < 50; ++_) {
            vector<Color> next_center(NUMBER_OF_GROUPS);
            vector<double> inv_sum(NUMBER_OF_GROUPS);
            vector<bool> flag(NUMBER_OF_GROUPS);
            for (int h = 0; h < H; ++h) {
                double score = center_of_group[group_number[h]].score(target_color[h]);
                if (score < 1e-9) {
                    flag[group_number[h]] = true;
                    continue;
                }
                next_center[group_number[h]] += target_color[h] / score;
                inv_sum[group_number[h]] += 1. / score;
            }
            for (int i = 0; i < NUMBER_OF_GROUPS; ++i) {
                if (!flag[i]) center_of_group[i] = next_center[i] / inv_sum[i];
            }
        }

        vector<vector<int>> group_member(NUMBER_OF_GROUPS);
        for (int h = 0; h < H; ++h) group_member[group_number[h]].emplace_back(h);

        vector<array<pair<double, int>, 401>> content_of_mixed_color(NUMBER_OF_GROUPS);
        for (int i = 0; i < NUMBER_OF_GROUPS; ++i) {
            ColorInfo mixed_color{};
            for (int j = 1; j <= 400; ++j) {
                ++mixed_color.amount;
                double min_distance = numeric_limits<double>::max();
                int min_color = -1;
                for (int k = 0; k < K; ++k) {
                    if (chmin(min_distance,
                              center_of_group[i].score((mixed_color.color + own_color[k]) / mixed_color.amount)))
                        min_color = k;
                }
                mixed_color.color += own_color[min_color];
                double sum_distance = 0;
                for (auto h : group_member[i]) sum_distance += (mixed_color.color / j).score(target_color[h]);
                content_of_mixed_color[i][j] = {sum_distance + (double)D *
                                                                   ((group_count[i] - 1) / mixed_color.amount + 1) *
                                                                   mixed_color.amount / ERROR_BIAS,
                                                min_color};
            }
        }

        Trace<int> trace;
        array<pair<double, int>, 401> dp;
        for (int i = 0; i < NUMBER_OF_GROUPS; ++i) {
            if (i == 0) {
                for (int j = 1; j <= 400; ++j) {
                    dp[j] = {content_of_mixed_color[i][j].first, trace.push(j, -1)};
                }
                continue;
            }
            array<pair<double, int>, 401> ndp;
            for (int j = 1; j <= 400; ++j) ndp[j] = {numeric_limits<double>::max(), -1};
            for (int j = 1; j <= 400; ++j) {
                for (int k = 1; (j + k) <= 400; ++k) {
                    if (chmin(ndp[j + k].first, dp[j].first + content_of_mixed_color[i][k].first)) {
                        ndp[j + k].second = trace.push(k, dp[j].second);
                    }
                }
            }
            dp = ndp;
        }

        double min_score = numeric_limits<double>::max();
        int min_idx = -1;
        for (int i = 1; i <= 400; ++i) {
            if (chmin(min_score, dp[i].first)) min_idx = i;
        }

        auto v = trace.chain(dp[min_idx].second);
        assert(v.size() == NUMBER_OF_GROUPS);
        vector<PalletInfo> pallets(NUMBER_OF_GROUPS);
        int position = 0;
        for (int i = 0; i < NUMBER_OF_GROUPS; ++i) {
            pallets[i] = {Color(), v[i], 0, 0, position};
            for (int j = 1; j <= v[i]; ++j) pallets[i].color += own_color[content_of_mixed_color[i][j].second];
            pallets[i].color /= v[i];
            position += v[i];
            if (position < 400) board.add_divider(ordered_pallet_point[position - 1], ordered_pallet_point[position]);
        }
        vector<Generator> generators;
        for (int h = 0; h < H; ++h) {
            int group_index = group_number[h];
            auto &pallet = pallets[group_index];
            vector<Operation> operations;
            double score = pallets[group_index].color.score(target_color[h]);
            if (pallet.rest == 0) {
                for (int i = 1; i <= pallet.amount; ++i) {
                    operations.emplace_back(1, ordered_pallet_point[pallet.position],
                                            content_of_mixed_color[group_index][i].second);
                }
                pallet.rest = pallet.amount;
                score += (double)D * v[group_index] / ERROR_BIAS;
            }
            --pallet.rest;
            operations.emplace_back(2, ordered_pallet_point[pallets[group_index].position]);
            generators.emplace_back(score, operations);
        }
        Solution sol(board);
        for (auto &gen : generators) sol.add_generator(gen);
        sol.score -= (double)D * H / ERROR_BIAS;
        cerr << "KMeansSolver(" << NUMBER_OF_GROUPS << ") Score = " << sol.score << endl;
        return sol;
    }
};

struct IncrementallySolver {
    vector<Color> own_color;
    array<Color, H> target_color;
    vector<Point2D> ordered_pallet_point;
    Board board;

    IncrementallySolver(const Parameter &param) : own_color(param.own_color), target_color(param.target_color) {}

    void setup() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) ordered_pallet_point.emplace_back(i, j);
        }
        for (int i = 0; i < N / 2; ++i) {
            reverse(ordered_pallet_point.begin() + N * (2 * i + 1), ordered_pallet_point.begin() + N * (2 * i + 2));
        }
        board.fill();
        for (int i = 0; i < N * N - 1; ++i) board.delete_divider(ordered_pallet_point[i], ordered_pallet_point[i + 1]);
    }

    Solution solve() {
        setup();
        array<ColorDetailedInfo, H> mixed_color;
        priority_queue<pair<double, int>> p_que;
        vector<tuple<int, int, int>> history;
        double current_score = 0;
        for (int h = 0; h < H; ++h) {
            double min_distance = numeric_limits<double>::max();
            int min_color = -1;
            for (int k = 0; k < K; ++k) {
                if (chmin(min_distance, own_color[k].score(target_color[h]))) min_color = k;
            }
            mixed_color[h] = ColorDetailedInfo{own_color[min_color], 1., 1.};
            p_que.emplace(min_distance, h);
            history.emplace_back(h, min_color, 400);
            current_score += min_distance;
        }

        int operation_size = H * 2;
        double best_score = current_score;
        int best_history = history.size();
        while (operation_size + 5 <= T && !p_que.empty()) {
            auto [min_distance, h] = p_que.top();
            p_que.pop();
            current_score -= min_distance;
            min_distance = numeric_limits<double>::max();
            int min_color = -1, min_t = -1;
            for (int k = 0; k < K; ++k) {
                auto dc = (mixed_color[h].color + own_color[k] * mixed_color[h].product) /
                              (mixed_color[h].amount + mixed_color[h].product) -
                          mixed_color[h].color / mixed_color[h].amount;
                if (dc.length2() < 1e-20) {
                    if (chmin(min_distance, ((mixed_color[h].color + own_color[k] * mixed_color[h].product) /
                                             (mixed_color[h].amount + mixed_color[h].product))
                                                .score(target_color[h])))
                        min_color = k, min_t = 400;
                    continue;
                }
                auto dt = target_color[h] - mixed_color[h].color / mixed_color[h].amount;
                double sum = (dc.c * dt.c + dc.m * dt.m + dc.y * dt.y) / dc.length2();
                sum = clamp(sum, 0., 1.);
                int t = round(400. * sum);
                assert(0 <= t && t <= 400);
                if (chmin(min_distance, ((mixed_color[h].color + own_color[k] * mixed_color[h].product * t / 400) /
                                         (mixed_color[h].amount + mixed_color[h].product * t / 400))
                                            .score(target_color[h])))
                    min_color = k, min_t = t;
            }
            assert(min_color != -1);
            if (min_t == 0 || mixed_color[h].product == 0) {
                current_score += min_distance;
                continue;
            }
            mixed_color[h].product *= min_t / 400.;
            mixed_color[h].color += own_color[min_color] * mixed_color[h].product;
            mixed_color[h].amount += mixed_color[h].product;
            if (mixed_color[h].amount + mixed_color[h].product < 400) p_que.emplace(min_distance, h);
            history.emplace_back(h, min_color, min_t);
            current_score += min_distance + (double)D / ERROR_BIAS;
            if (chmin(best_score, current_score)) best_history = history.size();
            if (min_t == 400)
                operation_size += 2;
            else
                operation_size += 5;
        }

        array<vector<pair<int, int>>, H> content_of_mixed_color = {};
        for (int i = 0; i < best_history; ++i) {
            auto [x, y, t] = history[i];
            content_of_mixed_color[x].emplace_back(y, t);
        }
        for (int h = 0; h < H; ++h) reverse(content_of_mixed_color[h].begin(), content_of_mixed_color[h].end());

        Solution sol(board);
        for (int h = 0; h < H; ++h) {
            ColorDetailedInfo color{};
            for (auto [x, t] : content_of_mixed_color[h]) {
                sol.operations.emplace_back(1, Point2D{0, 0}, x);
                color.color += own_color[x];
                color.amount += 1;
                if (t < 400) {
                    int r = ceil(color.amount * (400 - t) / 400);
                    color.amount *= (double)t / 400;
                    sol.operations.emplace_back(4, ordered_pallet_point[400 - t - 1], ordered_pallet_point[400 - t]);
                    for (int _ = 0; _ < r; ++_) sol.operations.emplace_back(3, Point2D{0, 0});
                    sol.operations.emplace_back(4, ordered_pallet_point[400 - t - 1], ordered_pallet_point[400 - t]);
                }
            }
            sol.operations.emplace_back(2, Point2D{0, 0});
            for (int _ = 0; _ < ceil(color.amount - 1); ++_) sol.operations.emplace_back(3, Point2D{0, 0});
        }
        sol.score = best_score;
        cerr << sol.score << endl;
        return sol;
    }
};

constexpr int NUMBER_OF_GROUPS[] = {18, 20, 23, 26, 29, 32, 35, 38, 41, 44, 47, 50, 53, 56, 59, 62, 65};

template <int INDEX>
Solution brute_force_parameter_search(const Parameter &param) {
    auto solution = brute_force_parameter_search<INDEX - 1>(param);
    KMeansSolver<NUMBER_OF_GROUPS[INDEX]> solver(param);
    auto sol = solver.solve();
    if (sol.score < solution.score) solution = sol;
    return solution;
}

template <>
Solution brute_force_parameter_search<-1>(const Parameter &param) {
    Solution sol(Board{});
    sol.score = numeric_limits<double>::max();
    return sol;
}

int main(void) {
    Timer timer;
    Parameter param;
    cin >> param;
    Solver solver(param);
    auto solution = solver.solve();
    cerr << "Lap 1 = " << timer.get_time() << endl;
    auto solution2 = brute_force_parameter_search<size(NUMBER_OF_GROUPS) - 1>(param);
    if (solution2.score < solution.score) solution = solution2;
    cerr << "Lap 2 = " << timer.get_time() << endl;
    IncrementallySolver solver3(param);
    auto solution3 = solver3.solve();
    cerr << "Lap 3 = " << timer.get_time() << endl;
    if (solution3.score < solution.score) solution = solution3;
    cout << solution;
}
