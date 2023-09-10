#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <numeric>
#include <queue>
#include <stack>
#include <string>
#include <vector>

template <class T, class U>
bool chmax(T& a, const U b) {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
bool chmin(T& a, const U b) {
    return (T)b < a ? a = (T)b, true : false;
}

constexpr int T = 100, H = 20, W = 20;

template <class T>
using land_array = std::array<std::array<T, W>, H>;

struct Pos {
    int x, y;

    constexpr Pos() : x(), y() {}
    constexpr Pos(int line) : x(line / W), y(line % W) {}
    constexpr Pos(int _x, int _y) : x(_x), y(_y) {}

    constexpr Pos& operator+=(const Pos& rhs) {
        x += rhs.x, y += rhs.y;
        return *this;
    }
    constexpr Pos& operator-=(const Pos& rhs) {
        x -= rhs.x, y -= rhs.y;
        return *this;
    }

    constexpr Pos operator+(const Pos& rhs) const { return Pos(*this) += rhs; }
    constexpr Pos operator-(const Pos& rhs) const { return Pos(*this) -= rhs; }

    constexpr bool operator==(const Pos& rhs) const { return x == rhs.x && y == rhs.y; }
    constexpr bool operator!=(const Pos& rhs) const { return !(*this == rhs); }

    constexpr bool in_field() const { return 0 <= x && x < H && 0 <= y && y < W; }

    int line() const { return x * W + y; }

    constexpr int norm1(const Pos& p) const {
        int dx = std::abs(x - p.x), dy = std::abs(y - p.y);
        return dx + dy;
    }

    constexpr int norm2(const Pos& p) const {
        int dx = std::abs(x - p.x), dy = std::abs(y - p.y);
        return dx * dx + dy * dy;
    }

    constexpr std::pair<int, int> pair() const { return std::make_pair(x, y); }
};

constexpr std::array<Pos, 4> adjacent_dir = {{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}};

struct Graph {
    Pos entrance;
    land_array<std::array<int, 4>> connected = {};
    land_array<int> distance_from_entrance;
    std::array<Pos, H * W> ordered_blocks;

    constexpr const std::array<std::array<int, 4>, W>& operator[](int i) { return connected[i]; }

    constexpr bool is_connected(int x, int y, int dir) const { return connected[x][y][dir]; }
    constexpr bool is_connected(const Pos& pos, int dir) const {
        return is_connected(pos.x, pos.y, dir);
    }

    constexpr int get_distance_from_entrance(int x, int y) const {
        return distance_from_entrance[x][y];
    }
    constexpr int get_distance_from_entrance(const Pos& pos) const {
        return get_distance_from_entrance(pos.x, pos.y);
    }

    void input() {
        int t, h, w, i;
        std::cin >> t >> h >> w >> i;
        entrance = Pos(i, 0);
        for (int x = 0; x < H - 1; ++x) {
            std::string s;
            std::cin >> s;
            for (int y = 0; y < W; ++y) {
                if (s[y] == '0') connected[x][y][0] = 1, connected[x + 1][y][1] = 1;
            }
        }
        for (int x = 0; x < H; ++x) {
            std::string s;
            std::cin >> s;
            for (int y = 0; y < W - 1; ++y) {
                if (s[y] == '0') connected[x][y][2] = 1, connected[x][y + 1][3] = 1;
            }
        }
        init();
    }

  private:
    void init() {
        calculate_distance_from_entrance();
        sort_blocks_by_distance_from_entrance();
    }

    /// @brief 出入り口からの距離を求める
    /// @return land_array<int>
    void calculate_distance_from_entrance() {
        for (int i = 0; i < H; ++i) distance_from_entrance[i].fill(-1);
        std::queue<Pos> que;
        distance_from_entrance[entrance.x][entrance.y] = 0;
        que.emplace(entrance);
        while (!que.empty()) {
            auto cur = que.front();
            que.pop();
            for (int k = 0; k < 4; ++k) {
                if (auto nxt = cur + adjacent_dir[k];
                    connected[cur.x][cur.y][k] && distance_from_entrance[nxt.x][nxt.y] == -1) {
                    distance_from_entrance[nxt.x][nxt.y] = distance_from_entrance[cur.x][cur.y] + 1;
                    que.emplace(nxt);
                }
            }
        }
    }

    /// @brief 出入り口からの距離が遠い順に区画を並べる
    /// @return std::array<Pos, H * W>
    void sort_blocks_by_distance_from_entrance() {
        for (int x = 0; x < H; ++x) {
            for (int y = 0; y < W; ++y) ordered_blocks[x * W + y] = Pos{x, y};
        }
        std::sort(ordered_blocks.begin(), ordered_blocks.end(), [this](auto l, auto r) {
            return distance_from_entrance[l.x][l.y] > distance_from_entrance[r.x][r.y];
        });
    }
} graph;

struct Crop {
    int id, s, d;

    constexpr bool operator<(const Crop& rhs) const { return score() > rhs.score(); }

    constexpr int score() const { return d - s + 1; }
};

struct Operation {
    int k, x, y, s;

    constexpr Operation(Pos _pos, int _k, int _s) : k(_k), x(_pos.x), y(_pos.y), s(_s) {}
    constexpr Operation(int _k, int _x, int _y, int _s) : k(_k), x(_x), y(_y), s(_s) {}

    friend std::ostream& operator<<(std::ostream& os, const Operation& rhs) {
        return os << rhs.k << ' ' << rhs.x << ' ' << rhs.y << ' ' << rhs.s;
    }
};

struct RestBlock {
    Pos pos;
    int s, d;

    constexpr RestBlock() : pos(), s(), d() {}
    constexpr RestBlock(Pos _pos, int _s = 1, int _d = 100) : pos(_pos), s(_s), d(_d) {}
    constexpr RestBlock(int _x, int _y, int _s = 1, int _d = 100) : pos(_x, _y), s(_s), d(_d) {}

    constexpr int rest() const { return d - s; }

    constexpr bool operator<(const RestBlock& rhs) const { return rest() < rhs.rest(); }

    constexpr bool can_cultivate(const Crop& crop) const { return s <= crop.s && crop.d <= d; }

    constexpr Operation create_operation(const Crop& crop) const {
        return Operation(crop.id, pos.x, pos.y, crop.s);
    }

    constexpr bool exists_left_rest_block(int crop_s) const { return s < crop_s; }
    constexpr bool exists_left_rest_block(const Crop& crop) const { return s < crop.s; }
    constexpr bool exists_right_rest_block(int crop_d) const { return crop_d < d; }
    constexpr bool exists_right_rest_block(const Crop& crop) const { return crop.d < d; }

    constexpr RestBlock get_left_rest_block(int crop_s) const {
        return RestBlock(pos, s, crop_s - 1);
    }
    constexpr RestBlock get_left_rest_block(const Crop& crop) const {
        return RestBlock(pos, s, crop.s - 1);
    }
    constexpr RestBlock get_right_rest_block(int crop_d) const {
        return RestBlock(pos, crop_d + 1, d);
    }
    constexpr RestBlock get_right_rest_block(const Crop& crop) const {
        return RestBlock(pos, crop.d + 1, d);
    }
};

struct Blocks {
    enum struct BlockType { NONE, PATHWAY, CULTIVATION };

    land_array<BlockType> blocks_type;

    constexpr Blocks() : blocks_type{} {}

    constexpr bool is_pathway(int x, int y) const {
        return blocks_type[x][y] == BlockType::PATHWAY;
    }
    constexpr bool is_pathway(const Pos& pos) const { return is_pathway(pos.x, pos.y); }
    constexpr bool is_cultivation(int x, int y) const {
        return blocks_type[x][y] == BlockType::CULTIVATION;
    }
    constexpr bool is_cultivation(const Pos& pos) const { return is_cultivation(pos.x, pos.y); }
    constexpr bool is_decided(int x, int y) const { return blocks_type[x][y] != BlockType::NONE; }
    constexpr bool is_decided(const Pos& pos) const { return is_decided(pos.x, pos.y); }

    constexpr void set_pathway(const Pos& pos) { blocks_type[pos.x][pos.y] = BlockType::PATHWAY; }
    constexpr void set_cultivation(const Pos& pos) {
        blocks_type[pos.x][pos.y] = BlockType::CULTIVATION;
    }

    std::vector<Pos> get_pathway_blocks() const {
        std::vector<Pos> pathway_blocks;
        for (int x = 0; x < H; ++x) {
            for (int y = 0; y < W; ++y) {
                if (is_pathway(x, y)) pathway_blocks.emplace_back(x, y);
            }
        }
        return pathway_blocks;
    }

    std::vector<Pos> get_cultivation_blocks() const {
        std::vector<Pos> cultivation_blocks;
        for (int x = 0; x < H; ++x) {
            for (int y = 0; y < W; ++y) {
                if (is_cultivation(x, y)) cultivation_blocks.emplace_back(x, y);
            }
        }
        return cultivation_blocks;
    }

    land_array<int> calculate_distance_from_entrance_in_pathway() const {
        land_array<int> dists;
        for (int x = 0; x < H; ++x) dists[x].fill(-1);
        std::queue<Pos> que;
        dists[graph.entrance.x][graph.entrance.y] = 0;
        que.emplace(graph.entrance);
        while (!que.empty()) {
            auto pos = que.front();
            que.pop();
            for (int k = 0; k < 4; ++k) {
                if (auto adj_pos = pos + adjacent_dir[k]; graph.is_connected(pos, k) &&
                                                          is_pathway(adj_pos) &&
                                                          dists[adj_pos.x][adj_pos.y] == -1) {
                    dists[adj_pos.x][adj_pos.y] = dists[pos.x][pos.y] + 1;
                    que.emplace(adj_pos);
                }
            }
        }
        return dists;
    }

    std::vector<Pos> create_sorted_pathway_blocks() const {
        std::vector<Pos> pathway_blocks = get_pathway_blocks();
        auto dists = calculate_distance_from_entrance_in_pathway();
        std::sort(pathway_blocks.begin(), pathway_blocks.end(),
                  [&dists](const Pos& l, const Pos& r) {
                      return dists[l.x][l.y] > dists[r.x][r.y];
                  });
        return pathway_blocks;
    }

    std::vector<Pos> create_ordered_pathway_blocks() const {
        std::vector<Pos> ordered_pathway_blocks;
        ordered_pathway_blocks.emplace_back(graph.entrance);
        while (true) {
            land_array<int> dists;
            for (int x = 0; x < H; ++x) dists[x].fill(-1);
            std::queue<Pos> que;
            for (auto pos : ordered_pathway_blocks) {
                dists[pos.x][pos.y] = 0;
                que.emplace(pos);
            }
            while (!que.empty()) {
                auto pos = que.front();
                que.pop();
                for (int k = 0; k < 4; ++k) {
                    if (auto adj_pos = pos + adjacent_dir[k]; graph.is_connected(pos, k) &&
                                                              is_pathway(adj_pos) &&
                                                              dists[adj_pos.x][adj_pos.y] == -1) {
                        dists[adj_pos.x][adj_pos.y] = dists[pos.x][pos.y] + 1;
                        que.emplace(adj_pos);
                    }
                }
            }

            Pos max_dists_pos;
            int max_dist = 0;
            for (int x = 0; x < H; ++x) {
                for (int y = 0; y < W; ++y) {
                    if (chmax(max_dist, dists[x][y])) max_dists_pos = Pos(x, y);
                }
            }
            if (max_dist) {
                for (int d = max_dist - 1; d >= 0; --d) {
                    ordered_pathway_blocks.emplace_back(max_dists_pos);
                    for (int k = 0; k < 4; ++k) {
                        if (auto adj_pos = max_dists_pos + adjacent_dir[k];
                            graph.is_connected(max_dists_pos, k) &&
                            dists[adj_pos.x][adj_pos.y] == d) {
                            max_dists_pos = adj_pos;
                            break;
                        }
                    }
                }
                std::reverse(ordered_pathway_blocks.end() - max_dist, ordered_pathway_blocks.end());
            } else break;
        }

        std::reverse(ordered_pathway_blocks.begin(), ordered_pathway_blocks.end());
        return ordered_pathway_blocks;
    }
};

struct PathwaySolver {
    struct DSU {
        land_array<Pos> data;

        constexpr DSU() {
            for (int x = 0; x < H; ++x) {
                for (int y = 0; y < W; ++y) data[x][y] = Pos{x, y};
            }
        }

        constexpr Pos root(Pos pos) {
            return pos == data[pos.x][pos.y] ? pos : data[pos.x][pos.y] = root(data[pos.x][pos.y]);
        }

        constexpr bool is_root(Pos pos) const { return pos == data[pos.x][pos.y]; }

        constexpr void unite(Pos l, Pos r) {
            l = root(l), r = root(r);
            if (graph.get_distance_from_entrance(l) < graph.get_distance_from_entrance(r))
                std::swap(l, r);
            data[l.x][l.y] = r;
        }

        template <class F>
        constexpr void unite_with_adjacent_blocks(const Pos& pos, const F& can_unite) {
            for (int k = 0; k < 4; ++k) {
                if (!graph[pos.x][pos.y][k]) continue;
                auto adj_pos = pos + adjacent_dir[k];
                if (can_unite(adj_pos)) unite(pos, adj_pos);
            }
        };
    };

    Blocks blocks;
    land_array<int> adjacent_count;
    DSU dsu;

    constexpr PathwaySolver() : blocks{}, adjacent_count{}, dsu() {
        blocks.set_pathway(graph.entrance);
        for (int x = 0; x < H; ++x) {
            for (int y = 0; y < W; ++y) {
                adjacent_count[x][y] = std::accumulate(graph[x][y].begin(), graph[x][y].end(), 0);
            }
        }
    }

    Blocks decide_all_block_type() {
        for (Pos pos : graph.ordered_blocks) {
            if (blocks.is_decided(pos)) continue;
            std::stack<Pos> st;
            set_cultivation(pos);
            push_block_to_stack(pos, st);
            while (!st.empty()) {
                auto pos = st.top();
                st.pop();
                for (int k = 0; k < 4; ++k) {
                    if (!graph[pos.x][pos.y][k]) continue;
                    auto adj_pos = pos + adjacent_dir[k];
                    if (!blocks.is_decided(adj_pos)) {
                        set_pathway(adj_pos);
                        dsu.unite_with_adjacent_blocks(adj_pos, [this](const Pos& pos) {
                            return blocks.is_pathway(pos);
                        });
                        push_block_to_stack(adj_pos, st);
                    }
                }
            }
        }
        return blocks;
    }

    Blocks decide_efficient_block_type() {
        for (Pos pos : graph.ordered_blocks) {
            if (blocks.is_decided(pos)) continue;
            std::stack<Pos> st;
            set_cultivation(pos);
            push_block_to_stack(pos, st);

            int max_dir = 0;
            int max_move = 0;
            for (int k = 0; k < 4; ++k) {
                auto cur_pos = pos;
                for (int i = 0; i < std::max(H, W); ++i) {
                    if (auto adj_pos = cur_pos + adjacent_dir[k];
                        graph.is_connected(cur_pos, k) && !blocks.is_decided(adj_pos) &&
                        (!graph.is_connected(adj_pos, (k + 2) % 4) ||
                         !graph.is_connected(adj_pos, 3 - k))) {
                        cur_pos = adj_pos;
                    } else {
                        if (chmax(max_move, i)) max_dir = k;
                        break;
                    }
                }
            }

            while (true) {
                while (!st.empty()) {
                    auto pos = st.top();
                    st.pop();
                    for (int k = 0; k < 4; ++k) {
                        if (!graph.is_connected(pos, k)) continue;
                        auto adj_pos = pos + adjacent_dir[k];
                        if (!blocks.is_decided(adj_pos)) {
                            set_pathway(adj_pos);
                            dsu.unite_with_adjacent_blocks(adj_pos, [this](const Pos& pos) {
                                return blocks.is_pathway(pos);
                            });
                            push_block_to_stack(adj_pos, st);
                        }
                    }
                }

                if (auto adj_pos = pos + adjacent_dir[max_dir];
                    graph.is_connected(pos, max_dir) && !blocks.is_decided(adj_pos) &&
                    (!graph.is_connected(adj_pos, (max_dir + 2) % 4) ||
                     !graph.is_connected(adj_pos, 3 - max_dir))) {
                    pos = adj_pos;
                    set_cultivation(pos);
                    push_block_to_stack(pos, st);
                } else {
                    break;
                }
            }
        }
        return blocks;
    }

  private:
    bool is_adjacent_to_pathway(const Pos& pos) const {
        for (int k = 0; k < 4; ++k) {
            if (!graph[pos.x][pos.y][k]) continue;
            auto adj_pos = pos + adjacent_dir[k];
            if (blocks.is_pathway(adj_pos)) return true;
        }
        return false;
    };

    void update_adjacent_count(const Pos& pos) {
        for (int k = 0; k < 4; ++k) {
            if (!graph[pos.x][pos.y][k]) continue;
            auto adj_pos = pos + adjacent_dir[k];
            --adjacent_count[adj_pos.x][adj_pos.y];
        }
    }

    void set_pathway(const Pos& pos) {
        blocks.set_pathway(pos);
        update_adjacent_count(pos);
    }
    void set_cultivation(const Pos& pos) {
        blocks.set_cultivation(pos);
        update_adjacent_count(pos);
    }

    bool can_decide_adjacent_pathway(const Pos& pos) const {
        return adjacent_count[pos.x][pos.y] == 1 &&
               ((blocks.is_pathway(pos) && dsu.is_root(pos)) ||
                (blocks.is_cultivation(pos) && !is_adjacent_to_pathway(pos)));
    }

    void push_block_to_stack(const Pos& pos, std::stack<Pos>& st) const {
        if (can_decide_adjacent_pathway(pos)) st.emplace(pos);
        for (int k = 0; k < 4; ++k) {
            if (!graph[pos.x][pos.y][k]) continue;
            auto adj_pos = pos + adjacent_dir[k];
            if (can_decide_adjacent_pathway(adj_pos)) st.emplace(adj_pos);
        }
    }
};

enum struct SolverType {
    MixedSolver,
    MixedSolver2,
    MixedSolver3,
    TightBordersSolver,
    MaxTightBordersSolver,
    EfficientPathwaySolver
};

struct Solver {
    const std::vector<Crop> crops;

    Solver(const std::vector<Crop>& _crops) : crops(_crops) {}

    std::vector<Crop> get_rest_crops(const std::vector<bool>& used_crops) const {
        std::vector<Crop> rest_crops;
        for (auto& crop : crops) {
            if (!used_crops[crop.id]) rest_crops.emplace_back(crop);
        }
        return rest_crops;
    }

    std::vector<int> create_optimal_period_borders(int max_size = H * W) const {
        std::array<std::array<int, T + 1>, T + 1> crops_count = {};
        for (auto& crop : crops) crops_count[crop.s][crop.d]++;

        std::array<int, T + 1> score_dp = {}, prev_time = {};
        for (int lim = 1; lim <= T; ++lim) {
            int score = 0;
            std::vector<int> v;
            for (int x = lim - 2; x >= 1; --x) {
                int len = v.size();
                for (int y = x + 2; y <= lim; ++y) {
                    score += (y - x + 1) * crops_count[x][y];
                    for (int i = 0; i < crops_count[x][y]; ++i) v.emplace_back(y - x + 1);
                }
                std::reverse(v.begin() + len, v.end());
                std::inplace_merge(v.begin(), v.begin() + len, v.end(), [](auto l, auto r) {
                    return l > r;
                });
                if ((int)v.size() > max_size) {
                    for (int i = max_size; i < (int)v.size(); ++i) score -= v[i];
                    v.erase(v.begin() + max_size, v.end());
                }
                if (chmax(score_dp[lim], score_dp[x - 1] + score)) prev_time[lim] = x - 1;
            }
        }

        std::vector<int> borders;
        borders.emplace_back(T);
        while (borders.back()) borders.emplace_back(prev_time[borders.back()]);
        std::reverse(borders.begin(), borders.end());
        return borders;
    }

    std::vector<int> create_tight_period_borders(int max_size = H * W) const {
        std::array<std::array<int, T + 1>, T + 1> crops_count = {};
        for (auto& crop : crops) crops_count[crop.s][crop.d]++;

        std::array<int, T + 1> sum_count = {}, prev_time = {};
        for (int y = 1; y <= T; ++y) {
            int sum = 0;
            for (int x = y - 2; x >= 1; --x) {
                sum_count[x] += crops_count[x][y];
                sum += sum_count[x];
                if (sum >= max_size) {
                    prev_time[y] = x - 1;
                    break;
                }
            }
        }

        std::vector<int> borders;
        borders.emplace_back(T);
        while (borders.back()) borders.emplace_back(prev_time[borders.back()]);
        std::reverse(borders.begin(), borders.end());
        return borders;
    }

    std::vector<int> create_max_tight_period_borders(int max_size = H * W) const {
        std::array<std::array<int, T + 1>, T + 1> crops_count = {};
        for (auto& crop : crops) crops_count[crop.s][crop.d]++;

        std::array<int, T + 1> border_count = {}, score_dp = {}, prev_time = {};
        for (int lim = 1; lim <= T; ++lim) {
            int score = 0;
            std::vector<int> v;
            for (int x = lim - 2; x >= 1; --x) {
                int len = v.size();
                for (int y = x + 2; y <= lim; ++y) {
                    score += (y - x + 1) * crops_count[x][y];
                    for (int i = 0; i < crops_count[x][y]; ++i) v.emplace_back(y - x + 1);
                }
                std::reverse(v.begin() + len, v.end());
                std::inplace_merge(v.begin(), v.begin() + len, v.end(), [](auto l, auto r) {
                    return l > r;
                });
                if ((int)v.size() > max_size) {
                    for (int i = max_size; i < (int)v.size(); ++i) score -= v[i];
                    v.erase(v.begin() + max_size, v.end());
                }
                if (border_count[lim] == 0 && (int)v.size() == max_size)
                    border_count[lim] = border_count[x - 1] + 1;
                if (border_count[lim] == border_count[x - 1] + 1 &&
                    chmax(score_dp[lim], score_dp[x - 1] + score))
                    prev_time[lim] = x - 1;
            }
        }

        std::vector<int> borders;
        borders.emplace_back(T);
        while (borders.back()) borders.emplace_back(prev_time[borders.back()]);
        std::reverse(borders.begin(), borders.end());
        return borders;
    }

    template <SolverType SolverT>
    std::vector<Operation> solve();

    int calculate_score(const std::vector<Operation>& operations) {
        int score = 0;
        for (auto& operation : operations) score += crops[operation.k - 1].score();
        return score * 25;
    }
};

template <>
std::vector<Operation> Solver::solve<SolverType::MixedSolver>() {
    auto blocks = PathwaySolver().decide_all_block_type();
    auto pathway_blocks = blocks.create_sorted_pathway_blocks();
    auto borders = create_optimal_period_borders(pathway_blocks.size());
    std::vector<Operation> operations;
    land_array<std::bitset<T + 1>> can_harvest;
    std::vector<bool> used_crops(crops.size() + 1);
    for (int t = 0; t < (int)borders.size() - 1; ++t) {
        std::vector<Crop> short_crops;
        for (const Crop& crop : crops) {
            if (borders[t] + 1 <= crop.s && crop.d <= borders[t + 1])
                short_crops.emplace_back(crop);
        }
        if (short_crops.size() > pathway_blocks.size()) {
            std::nth_element(short_crops.begin(), short_crops.begin() + H * W, short_crops.end(),
                             [](const Crop& l, const Crop& r) {
                                 if (l.score() == r.score()) return l.s < r.s;
                                 return l.score() > r.score();
                             });
            short_crops.erase(short_crops.begin() + pathway_blocks.size(), short_crops.end());
        }
        std::sort(short_crops.begin(), short_crops.end(), [](auto l, auto r) {
            return l.d > r.d;
        });
        for (int i = 0; i < (int)std::min(pathway_blocks.size(), short_crops.size()); ++i) {
            operations.emplace_back(pathway_blocks[i], short_crops[i].id, borders[t] + 1);
            used_crops[short_crops[i].id] = true;
            for (int k = 0; k < 4; ++k) {
                if (graph.is_connected(pathway_blocks[i], k)) {
                    auto adj_pos = pathway_blocks[i] + adjacent_dir[k];
                    for (int j = crops[short_crops[i].id - 1].d; j <= borders[t + 1]; ++j) {
                        can_harvest[adj_pos.x][adj_pos.y].set(j);
                    }
                }
            }
        }
    }

    std::vector<Pos> cultivation_blocks = blocks.get_cultivation_blocks();
    std::vector<Crop> rest_crops = get_rest_crops(used_crops);
    std::sort(rest_crops.begin(), rest_crops.end());
    std::vector<RestBlock> rest_blocks;
    for (auto& pos : cultivation_blocks) rest_blocks.emplace_back(pos);
    auto comp = [](const RestBlock& l, const RestBlock& r) {
        if (l < r || r < l) return l < r;
        return graph.get_distance_from_entrance(l.pos) > graph.get_distance_from_entrance(r.pos);
    };
    for (auto& crop : rest_crops) {
        for (auto it = rest_blocks.begin(); it != rest_blocks.end(); ++it) {
            if (it->can_cultivate(crop) && can_harvest[it->pos.x][it->pos.y][crop.d]) {
                RestBlock rest_block(*it);
                rest_blocks.erase(it);
                int s =
                    std::max(rest_block.s,
                             *(std::lower_bound(borders.begin(), borders.end(), crop.s) - 1) + 1);
                operations.emplace_back(rest_block.pos, crop.id, s);
                if (rest_block.exists_left_rest_block(s))
                    rest_blocks.emplace_back(rest_block.get_left_rest_block(s));
                if (rest_block.exists_right_rest_block(crop))
                    rest_blocks.emplace_back(rest_block.get_right_rest_block(crop));
                std::sort(rest_blocks.begin(), rest_blocks.end(), comp);
                break;
            }
        }
    }

    return operations;
}

template <>
std::vector<Operation> Solver::solve<SolverType::MixedSolver2>() {
    auto blocks = PathwaySolver().decide_all_block_type();
    auto pathway_blocks = blocks.create_sorted_pathway_blocks();
    auto borders = create_optimal_period_borders(pathway_blocks.size());
    std::vector<Operation> operations;
    std::array<std::vector<Pos>, T + 1> can_harvest;
    std::vector<bool> used_crops(crops.size() + 1);
    for (int t = 0; t < (int)borders.size() - 1; ++t) {
        std::vector<Crop> short_crops;
        for (const Crop& crop : crops) {
            if (borders[t] + 1 <= crop.s && crop.d <= borders[t + 1])
                short_crops.emplace_back(crop);
        }
        if (short_crops.size() > pathway_blocks.size()) {
            std::nth_element(short_crops.begin(), short_crops.begin() + H * W, short_crops.end(),
                             [](const Crop& l, const Crop& r) {
                                 if (l.score() == r.score()) return l.s < r.s;
                                 return l.score() > r.score();
                             });
            short_crops.erase(short_crops.begin() + pathway_blocks.size(), short_crops.end());
        }
        std::sort(short_crops.begin(), short_crops.end(), [](auto l, auto r) {
            return l.d > r.d;
        });
        land_array<int> min_blocks;
        for (int i = 0; i < H; ++i) min_blocks[i].fill(T + 1);
        for (int i = 0; i < (int)std::min(pathway_blocks.size(), short_crops.size()); ++i) {
            operations.emplace_back(pathway_blocks[i], short_crops[i].id, borders[t] + 1);
            used_crops[short_crops[i].id] = true;
            for (int k = 0; k < 4; ++k) {
                if (graph.is_connected(pathway_blocks[i], k)) {
                    auto adj_pos = pathway_blocks[i] + adjacent_dir[k];
                    chmin(min_blocks[adj_pos.x][adj_pos.y], crops[short_crops[i].id - 1].d);
                }
            }
        }
        for (int x = 0; x < H; ++x) {
            for (int y = 0; y < W; ++y) {
                if (min_blocks[x][y] != T + 1) can_harvest[min_blocks[x][y]].emplace_back(x, y);
            }
        }
    }

    std::vector<Pos> cultivation_blocks = blocks.get_cultivation_blocks();
    std::vector<Crop> rest_crops = get_rest_crops(used_crops);
    std::sort(rest_crops.begin(), rest_crops.end());
    land_array<std::vector<RestBlock>> rest_blocks;
    for (auto& pos : cultivation_blocks) rest_blocks[pos.x][pos.y].emplace_back(pos);
    for (auto& crop : rest_crops) {
        int min_d = *(std::lower_bound(borders.begin(), borders.end(), crop.d) - 1) + 1;
        bool is_decided = false;
        for (int d = crop.d; d >= min_d; --d) {
            for (auto& pos : can_harvest[d]) {
                for (auto it = rest_blocks[pos.x][pos.y].begin();
                     it != rest_blocks[pos.x][pos.y].end(); ++it) {
                    if (it->can_cultivate(crop)) {
                        RestBlock rest_block(*it);
                        rest_blocks[pos.x][pos.y].erase(it);
                        int s = std::max(
                            rest_block.s,
                            *(std::lower_bound(borders.begin(), borders.end(), crop.s) - 1) + 1);
                        operations.emplace_back(rest_block.pos, crop.id, s);
                        if (rest_block.exists_left_rest_block(s))
                            rest_blocks[pos.x][pos.y].emplace_back(
                                rest_block.get_left_rest_block(s));
                        if (rest_block.exists_right_rest_block(crop))
                            rest_blocks[pos.x][pos.y].emplace_back(
                                rest_block.get_right_rest_block(crop));
                        is_decided = true;
                        break;
                    }
                }
                if (is_decided) break;
            }
            if (is_decided) break;
        }
    }

    return operations;
}

template <>
std::vector<Operation> Solver::solve<SolverType::MixedSolver3>() {
    auto blocks = PathwaySolver().decide_all_block_type();
    std::vector<Pos> pathway_blocks = blocks.create_ordered_pathway_blocks();
    auto borders = create_optimal_period_borders(pathway_blocks.size());
    std::vector<Operation> operations;
    std::array<std::vector<Pos>, T + 1> can_harvest;
    std::vector<bool> used_crops(crops.size() + 1);
    for (int t = 0; t < (int)borders.size() - 1; ++t) {
        std::vector<Crop> short_crops;
        for (const Crop& crop : crops) {
            if (borders[t] + 1 <= crop.s && crop.d <= borders[t + 1])
                short_crops.emplace_back(crop);
        }
        if (short_crops.size() > pathway_blocks.size()) {
            std::nth_element(short_crops.begin(), short_crops.begin() + H * W, short_crops.end(),
                             [](const Crop& l, const Crop& r) {
                                 if (l.score() == r.score()) return l.s < r.s;
                                 return l.score() > r.score();
                             });
            short_crops.erase(short_crops.begin() + pathway_blocks.size(), short_crops.end());
        }
        std::sort(short_crops.begin(), short_crops.end(), [](auto l, auto r) {
            return l.d > r.d;
        });
        land_array<int> min_blocks;
        for (int i = 0; i < H; ++i) min_blocks[i].fill(T + 1);
        for (int i = 0; i < (int)std::min(pathway_blocks.size(), short_crops.size()); ++i) {
            operations.emplace_back(pathway_blocks[i], short_crops[i].id, borders[t] + 1);
            used_crops[short_crops[i].id] = true;
            for (int k = 0; k < 4; ++k) {
                if (graph.is_connected(pathway_blocks[i], k)) {
                    auto adj_pos = pathway_blocks[i] + adjacent_dir[k];
                    chmin(min_blocks[adj_pos.x][adj_pos.y], crops[short_crops[i].id - 1].d);
                }
            }
        }
        for (int x = 0; x < H; ++x) {
            for (int y = 0; y < W; ++y) {
                if (min_blocks[x][y] != T + 1) can_harvest[min_blocks[x][y]].emplace_back(x, y);
            }
        }
    }

    std::vector<Pos> cultivation_blocks = blocks.get_cultivation_blocks();
    std::vector<Crop> rest_crops = get_rest_crops(used_crops);
    std::sort(rest_crops.begin(), rest_crops.end());
    land_array<std::vector<RestBlock>> rest_blocks;
    for (auto& pos : cultivation_blocks) rest_blocks[pos.x][pos.y].emplace_back(pos);
    for (auto& crop : rest_crops) {
        int min_d = *(std::lower_bound(borders.begin(), borders.end(), crop.d) - 1) + 1;
        bool is_decided = false;
        for (int d = crop.d; d >= min_d; --d) {
            for (auto& pos : can_harvest[d]) {
                for (auto it = rest_blocks[pos.x][pos.y].begin();
                     it != rest_blocks[pos.x][pos.y].end(); ++it) {
                    if (it->can_cultivate(crop)) {
                        RestBlock rest_block(*it);
                        rest_blocks[pos.x][pos.y].erase(it);
                        int s = std::max(
                            rest_block.s,
                            *(std::lower_bound(borders.begin(), borders.end(), crop.s) - 1) + 1);
                        operations.emplace_back(rest_block.pos, crop.id, s);
                        if (rest_block.exists_left_rest_block(s))
                            rest_blocks[pos.x][pos.y].emplace_back(
                                rest_block.get_left_rest_block(s));
                        if (rest_block.exists_right_rest_block(crop))
                            rest_blocks[pos.x][pos.y].emplace_back(
                                rest_block.get_right_rest_block(crop));
                        is_decided = true;
                        break;
                    }
                }
                if (is_decided) break;
            }
            if (is_decided) break;
        }
    }

    return operations;
}

template <>
std::vector<Operation> Solver::solve<SolverType::TightBordersSolver>() {
    auto blocks = PathwaySolver().decide_all_block_type();
    std::vector<Pos> pathway_blocks = blocks.create_ordered_pathway_blocks();
    auto borders = create_tight_period_borders(pathway_blocks.size());
    std::vector<Operation> operations;
    std::array<std::vector<Pos>, T + 1> can_harvest;
    std::vector<bool> used_crops(crops.size() + 1);
    for (int t = 0; t < (int)borders.size() - 1; ++t) {
        std::vector<Crop> short_crops;
        for (const Crop& crop : crops) {
            if (borders[t] + 1 <= crop.s && crop.d <= borders[t + 1])
                short_crops.emplace_back(crop);
        }
        if (short_crops.size() > pathway_blocks.size()) {
            std::nth_element(short_crops.begin(), short_crops.begin() + H * W, short_crops.end(),
                             [](const Crop& l, const Crop& r) {
                                 if (l.score() == r.score()) return l.s < r.s;
                                 return l.score() > r.score();
                             });
            short_crops.erase(short_crops.begin() + pathway_blocks.size(), short_crops.end());
        }
        std::sort(short_crops.begin(), short_crops.end(), [](auto l, auto r) {
            return l.d > r.d;
        });
        land_array<int> min_blocks;
        for (int i = 0; i < H; ++i) min_blocks[i].fill(T + 1);
        for (int i = 0; i < (int)std::min(pathway_blocks.size(), short_crops.size()); ++i) {
            operations.emplace_back(pathway_blocks[i], short_crops[i].id, borders[t] + 1);
            used_crops[short_crops[i].id] = true;
            for (int k = 0; k < 4; ++k) {
                if (graph.is_connected(pathway_blocks[i], k)) {
                    auto adj_pos = pathway_blocks[i] + adjacent_dir[k];
                    chmin(min_blocks[adj_pos.x][adj_pos.y], crops[short_crops[i].id - 1].d);
                }
            }
        }
        for (int x = 0; x < H; ++x) {
            for (int y = 0; y < W; ++y) {
                if (min_blocks[x][y] != T + 1) can_harvest[min_blocks[x][y]].emplace_back(x, y);
            }
        }
    }

    std::vector<Pos> cultivation_blocks = blocks.get_cultivation_blocks();
    std::vector<Crop> rest_crops = get_rest_crops(used_crops);
    std::sort(rest_crops.begin(), rest_crops.end());
    land_array<std::vector<RestBlock>> rest_blocks;
    for (auto& pos : cultivation_blocks) rest_blocks[pos.x][pos.y].emplace_back(pos);
    for (auto& crop : rest_crops) {
        int min_d = *(std::lower_bound(borders.begin(), borders.end(), crop.d) - 1) + 1;
        bool is_decided = false;
        for (int d = crop.d; d >= min_d; --d) {
            for (auto& pos : can_harvest[d]) {
                for (auto it = rest_blocks[pos.x][pos.y].begin();
                     it != rest_blocks[pos.x][pos.y].end(); ++it) {
                    if (it->can_cultivate(crop)) {
                        RestBlock rest_block(*it);
                        rest_blocks[pos.x][pos.y].erase(it);
                        int s = std::max(
                            rest_block.s,
                            *(std::lower_bound(borders.begin(), borders.end(), crop.s) - 1) + 1);
                        operations.emplace_back(rest_block.pos, crop.id, s);
                        if (rest_block.exists_left_rest_block(s))
                            rest_blocks[pos.x][pos.y].emplace_back(
                                rest_block.get_left_rest_block(s));
                        if (rest_block.exists_right_rest_block(crop))
                            rest_blocks[pos.x][pos.y].emplace_back(
                                rest_block.get_right_rest_block(crop));
                        is_decided = true;
                        break;
                    }
                }
                if (is_decided) break;
            }
            if (is_decided) break;
        }
    }

    return operations;
}

template <>
std::vector<Operation> Solver::solve<SolverType::MaxTightBordersSolver>() {
    auto blocks = PathwaySolver().decide_all_block_type();
    std::vector<Pos> pathway_blocks = blocks.create_ordered_pathway_blocks();
    auto borders = create_max_tight_period_borders(pathway_blocks.size());
    std::vector<Operation> operations;
    std::array<std::vector<Pos>, T + 1> can_harvest;
    std::vector<bool> used_crops(crops.size() + 1);
    for (int t = 0; t < (int)borders.size() - 1; ++t) {
        std::vector<Crop> short_crops;
        for (const Crop& crop : crops) {
            if (borders[t] + 1 <= crop.s && crop.d <= borders[t + 1])
                short_crops.emplace_back(crop);
        }
        if (short_crops.size() > pathway_blocks.size()) {
            std::nth_element(short_crops.begin(), short_crops.begin() + H * W, short_crops.end(),
                             [](const Crop& l, const Crop& r) {
                                 if (l.score() == r.score()) return l.s < r.s;
                                 return l.score() > r.score();
                             });
            short_crops.erase(short_crops.begin() + pathway_blocks.size(), short_crops.end());
        }
        std::sort(short_crops.begin(), short_crops.end(), [](auto l, auto r) {
            return l.d > r.d;
        });
        land_array<int> min_blocks;
        for (int i = 0; i < H; ++i) min_blocks[i].fill(T + 1);
        for (int i = 0; i < (int)std::min(pathway_blocks.size(), short_crops.size()); ++i) {
            operations.emplace_back(pathway_blocks[i], short_crops[i].id, borders[t] + 1);
            used_crops[short_crops[i].id] = true;
            for (int k = 0; k < 4; ++k) {
                if (graph.is_connected(pathway_blocks[i], k)) {
                    auto adj_pos = pathway_blocks[i] + adjacent_dir[k];
                    chmin(min_blocks[adj_pos.x][adj_pos.y], crops[short_crops[i].id - 1].d);
                }
            }
        }
        for (int x = 0; x < H; ++x) {
            for (int y = 0; y < W; ++y) {
                if (min_blocks[x][y] != T + 1) can_harvest[min_blocks[x][y]].emplace_back(x, y);
            }
        }
    }

    std::vector<Pos> cultivation_blocks = blocks.get_cultivation_blocks();
    std::vector<Crop> rest_crops = get_rest_crops(used_crops);
    std::sort(rest_crops.begin(), rest_crops.end());
    land_array<std::vector<RestBlock>> rest_blocks;
    for (auto& pos : cultivation_blocks) rest_blocks[pos.x][pos.y].emplace_back(pos);
    for (auto& crop : rest_crops) {
        int min_d = *(std::lower_bound(borders.begin(), borders.end(), crop.d) - 1) + 1;
        bool is_decided = false;
        for (int d = crop.d; d >= min_d; --d) {
            for (auto& pos : can_harvest[d]) {
                for (auto it = rest_blocks[pos.x][pos.y].begin();
                     it != rest_blocks[pos.x][pos.y].end(); ++it) {
                    if (it->can_cultivate(crop)) {
                        RestBlock rest_block(*it);
                        rest_blocks[pos.x][pos.y].erase(it);
                        int s = std::max(
                            rest_block.s,
                            *(std::lower_bound(borders.begin(), borders.end(), crop.s) - 1) + 1);
                        operations.emplace_back(rest_block.pos, crop.id, s);
                        if (rest_block.exists_left_rest_block(s))
                            rest_blocks[pos.x][pos.y].emplace_back(
                                rest_block.get_left_rest_block(s));
                        if (rest_block.exists_right_rest_block(crop))
                            rest_blocks[pos.x][pos.y].emplace_back(
                                rest_block.get_right_rest_block(crop));
                        is_decided = true;
                        break;
                    }
                }
                if (is_decided) break;
            }
            if (is_decided) break;
        }
    }

    return operations;
}

template <>
std::vector<Operation> Solver::solve<SolverType::EfficientPathwaySolver>() {
    auto blocks = PathwaySolver().decide_efficient_block_type();
    std::vector<Pos> pathway_blocks = blocks.create_ordered_pathway_blocks();
    auto borders = create_max_tight_period_borders(pathway_blocks.size());
    std::vector<Operation> operations;
    std::array<std::vector<Pos>, T + 1> can_harvest;
    std::vector<bool> used_crops(crops.size() + 1);
    for (int t = 0; t < (int)borders.size() - 1; ++t) {
        std::vector<Crop> short_crops;
        for (const Crop& crop : crops) {
            if (borders[t] + 1 <= crop.s && crop.d <= borders[t + 1])
                short_crops.emplace_back(crop);
        }
        if (short_crops.size() > pathway_blocks.size()) {
            std::nth_element(short_crops.begin(), short_crops.begin() + H * W, short_crops.end(),
                             [](const Crop& l, const Crop& r) {
                                 if (l.score() == r.score()) return l.s < r.s;
                                 return l.score() > r.score();
                             });
            short_crops.erase(short_crops.begin() + pathway_blocks.size(), short_crops.end());
        }
        std::sort(short_crops.begin(), short_crops.end(), [](auto l, auto r) {
            return l.d > r.d;
        });
        land_array<int> min_blocks;
        for (int i = 0; i < H; ++i) min_blocks[i].fill(T + 1);
        for (int i = 0; i < (int)std::min(pathway_blocks.size(), short_crops.size()); ++i) {
            operations.emplace_back(pathway_blocks[i], short_crops[i].id, borders[t] + 1);
            used_crops[short_crops[i].id] = true;
            for (int k = 0; k < 4; ++k) {
                if (graph.is_connected(pathway_blocks[i], k)) {
                    auto adj_pos = pathway_blocks[i] + adjacent_dir[k];
                    chmin(min_blocks[adj_pos.x][adj_pos.y], crops[short_crops[i].id - 1].d);
                }
            }
        }
        for (int x = 0; x < H; ++x) {
            for (int y = 0; y < W; ++y) {
                if (blocks.is_cultivation(x, y) && min_blocks[x][y] != T + 1)
                    can_harvest[min_blocks[x][y]].emplace_back(x, y);
            }
        }
    }

    std::vector<Pos> cultivation_blocks = blocks.get_cultivation_blocks();
    std::vector<Crop> rest_crops = get_rest_crops(used_crops);
    std::sort(rest_crops.begin(), rest_crops.end());
    land_array<std::vector<RestBlock>> rest_blocks;
    for (auto& pos : cultivation_blocks) rest_blocks[pos.x][pos.y].emplace_back(pos);
    for (auto& crop : rest_crops) {
        int min_d = *(std::lower_bound(borders.begin(), borders.end(), crop.d) - 1) + 1;
        bool is_decided = false;
        for (int d = crop.d; d >= min_d; --d) {
            for (auto& pos : can_harvest[d]) {
                for (auto it = rest_blocks[pos.x][pos.y].begin();
                     it != rest_blocks[pos.x][pos.y].end(); ++it) {
                    if (it->can_cultivate(crop)) {
                        RestBlock rest_block(*it);
                        rest_blocks[pos.x][pos.y].erase(it);
                        int s = std::max(
                            rest_block.s,
                            *(std::lower_bound(borders.begin(), borders.end(), crop.s) - 1) + 1);
                        operations.emplace_back(rest_block.pos, crop.id, s);
                        if (rest_block.exists_left_rest_block(s))
                            rest_blocks[pos.x][pos.y].emplace_back(
                                rest_block.get_left_rest_block(s));
                        if (rest_block.exists_right_rest_block(crop))
                            rest_blocks[pos.x][pos.y].emplace_back(
                                rest_block.get_right_rest_block(crop));
                        is_decided = true;
                        break;
                    }
                }
                if (is_decided) break;
            }
            if (is_decided) break;
        }
    }

    return operations;
}

int main(void) {
    graph.input();
    int K;
    std::cin >> K;
    std::vector<Crop> crops(K);
    for (int i = 0; i < K; ++i) {
        int s, d;
        std::cin >> s >> d;
        crops[i] = Crop{i + 1, s, d};
    }
    Solver solver(crops);
    auto max_operations = solver.solve<SolverType::MixedSolver>();
    int max_score = solver.calculate_score(max_operations);
    int max_solver = 0;
    {
        auto operations = solver.solve<SolverType::MixedSolver2>();
        if (chmax(max_score, solver.calculate_score(operations)))
            max_operations = operations, max_solver = 1;
    }
    {
        auto operations = solver.solve<SolverType::MixedSolver3>();
        if (chmax(max_score, solver.calculate_score(operations)))
            max_operations = operations, max_solver = 2;
    }
    {
        auto operations = solver.solve<SolverType::TightBordersSolver>();
        if (chmax(max_score, solver.calculate_score(operations)))
            max_operations = operations, max_solver = 3;
    }
    {
        auto operations = solver.solve<SolverType::MaxTightBordersSolver>();
        if (chmax(max_score, solver.calculate_score(operations)))
            max_operations = operations, max_solver = 4;
    }
    {
        auto operations = solver.solve<SolverType::EfficientPathwaySolver>();
        if (chmax(max_score, solver.calculate_score(operations)))
            max_operations = operations, max_solver = 5;
    }
    std::cerr << "Solver = " << max_solver << std::endl;
    std::cerr << "Time = " << (double)clock() / CLOCKS_PER_SEC << std::endl;
    std::cout << max_operations.size() << std::endl;
    for (auto operation : max_operations) {
        std::cout << operation << std::endl;
    }

    return 0;
}
