#ifdef ATCODER
#pragma GCC target("sse4.2,avx512f,avx512dq,avx512ifma,avx512cd,avx512bw,avx512vl,bmi2")
#endif
#pragma GCC optimize("Ofast,fast-math,unroll-all-loops")
#include <bits/stdc++.h>
#ifndef ATCODER
#pragma GCC target("sse4.2,avx2,bmi2")
#endif
#define rep(i, n) for (int i = 0; i < int(n); ++i)
#define repn(i, n) for (int i = 1; i <= int(n); ++i)

template <class T, class U>
constexpr bool chmax(T &a, const U &b) {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
constexpr bool chmin(T &a, const U &b) {
    return (T)b < a ? a = (T)b, true : false;
}

using namespace std;
using ll = std::int64_t;

// clang-format off
struct union_find {
    union_find() = default;
    explicit union_find(int _n) : _rank(_n), data(_n, -1) {}

    const int &operator[](std::size_t x) const { return data[x]; }
    int &operator[](std::size_t x) { return data[x]; }

    int root(int x) { return data[x] < 0 ? x : data[x] = root(data[x]); }
    int get_root(int x) { return root(x); }

    bool is_root(int x) const { return data[x] < 0; }

    bool same(int x, int y) { return root(x) == root(y); }
    bool is_same(int x, int y) { return same(x, y); }

    int rank() { return _rank; }

    int size(int x) { return -(data[root(x)]); }
    int get_size(int x) { return size(x); }

    std::vector<int> leaders() {
        std::vector<int> res;
        for (int i = 0; i < (int)data.size(); ++i) {
            if (is_root(i)) res.emplace_back(i);
        }
        return res;
    }

    bool unite(int x, int y) {
        x = root(x), y = root(y);
        if (x == y) return false;
        --_rank;
        if (data[x] > data[y]) std::swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return true;
    }

    template <class F>
    bool unite(int x, int y, F f) {
        x = root(x), y = root(y);
        if (x != y) {
            if (data[x] > data[y]) std::swap(x, y);
            data[x] += data[y];
            data[y] = x;
        }
        f(x, y);
        return x != y;
    }

  private:
    int _rank;
    std::vector<int> data;
};
// clang-format on

struct point {
    ll x, y;
};

bool valid(point p, point q) {
    return p.x <= q.x && p.y <= q.y;
}

ll dist(point p, point q) {
    return abs(p.x - q.x) + abs(p.y - q.y);
}

vector<tuple<int, int, int, int>> separate(int a, int b, int c, int d, int e) {
    return vector<tuple<int, int, int, int>>{{a, b, c, e}, {a, b, e, d}};
}

vector<tuple<int, int, int, int>> generate(int a, int b, int c, int d) {
    if (a == c && b == d)
        return vector<tuple<int, int, int, int>>();
    if (a == c)
        return vector<tuple<int, int, int, int>>{{0, c, b, d}};
    if (b == d)
        return vector<tuple<int, int, int, int>>{{1, d, a, c}};
    if (c <= d)
        return vector<tuple<int, int, int, int>>{{1, b, a, c}, {0, c, b, d}};
    else
        return vector<tuple<int, int, int, int>>{{0, a, b, d}, {1, d, a, c}};
}

void solve() {
    int n;
    cin >> n;
    vector<point> ps(n + 1);
    repn (i, n) cin >> ps[i].x >> ps[i].y;

    sort(ps.begin(), ps.end(), [](point p, point q) {
        if (min(p.x, p.y) == min(q.x, q.y))
            return p.x + p.y < q.x + q.y;
        return min(p.x, p.y) < min(q.x, q.y);
    });

    vector<tuple<int, int, int, int>> edges;
    repn (i, n) {
        auto [x, y] = ps[i];
        if (x == 0 || y == 0) {
            if (x == 0)
                edges.emplace_back(0, 0, 0, y);
            else
                edges.emplace_back(1, 0, 0, x);
            continue;
        }
        int min_idx = -1;
        ll md = 1e18;
        vector<tuple<int, int, int, int>> emp;
        rep (idx, edges.size()) {
            if (get<0>(edges[idx]) == 0) {
                auto [t, dx, sy, gy] = edges[idx];
                if (x < dx || y < sy)
                    continue;
                if (y < gy) {
                    if (chmin(md, x - dx)) {
                        min_idx = idx;
                        emp = separate(t, dx, sy, gy, y);
                        emp.emplace_back(!t, y, dx, x);
                    }
                } else {
                    if (chmin(md, x - dx + y - gy)) {
                        min_idx = -1;
                        emp = generate(dx, gy, x, y);
                    }
                }
            } else {
                auto [t, dy, sx, gx] = edges[idx];
                if (y < dy || x < sx)
                    continue;
                if (x < gx) {
                    if (chmin(md, y - dy)) {
                        min_idx = idx;
                        emp = separate(t, dy, sx, gx, x);
                        emp.emplace_back(!t, x, dy, y);
                    }
                } else {
                    if (chmin(md, x - gx + y - dy)) {
                        min_idx = -1;
                        emp = generate(gx, dy, x, y);
                    }
                }
            }
        }

        if (min_idx != -1) {
            swap(edges.back(), edges[min_idx]);
            edges.pop_back();
        }
        for (auto e : emp) edges.emplace_back(e);
    }

    while ((double)clock() / CLOCKS_PER_SEC < 1.98 && edges.size() < 5 * n - 2) {
        int r = rand() % edges.size();
        if (get<1>(edges[r]) == 0 && get<2>(edges[r]) == 0)
            continue;
        swap(edges[r], edges.back());
        auto [t, x, _, y] = edges.back();
        edges.pop_back();
        if (t)
            swap(x, y);

        int min_idx = -1;
        ll md = 1e18;
        vector<tuple<int, int, int, int>> emp;
        rep (idx, edges.size()) {
            if (get<0>(edges[idx]) == 0) {
                auto [t, dx, sy, gy] = edges[idx];
                if (x < dx || y < sy || (x == dx && y == sy))
                    continue;
                if (y < gy) {
                    if (chmin(md, x - dx)) {
                        min_idx = idx;
                        emp = separate(t, dx, sy, gy, y);
                        emp.emplace_back(!t, y, dx, x);
                    }
                } else {
                    if (chmin(md, x - dx + y - gy)) {
                        min_idx = -1;
                        emp = generate(dx, gy, x, y);
                    }
                }
            } else {
                auto [t, dy, sx, gx] = edges[idx];
                if (y < dy || x < sx || (y == dy && x == sx))
                    continue;
                if (x < gx) {
                    if (chmin(md, y - dy)) {
                        min_idx = idx;
                        emp = separate(t, dy, sx, gx, x);
                        emp.emplace_back(!t, x, dy, y);
                    }
                } else {
                    if (chmin(md, x - gx + y - dy)) {
                        min_idx = -1;
                        emp = generate(gx, dy, x, y);
                    }
                }
            }
        }

        if (min_idx != -1) {
            swap(edges.back(), edges[min_idx]);
            edges.pop_back();
        }
        for (auto e : emp) edges.emplace_back(e);
    }

    map<pair<int, int>, int> mp;
    mp[{0, 0}] = 0;
    for (auto [t, a, b, c] : edges) {
        if (t == 0) {
            if (!mp.count({a, b}))
                mp[{a, b}] = mp.size();
            if (!mp.count({a, c}))
                mp[{a, c}] = mp.size();
        } else {
            if (!mp.count({b, a}))
                mp[{b, a}] = mp.size();
            if (!mp.count({c, a}))
                mp[{c, a}] = mp.size();
        }
    }

    vector<point> points(mp.size());
    for (auto [p, idx] : mp) {
        points[idx] = {p.first, p.second};
    }

    vector graph(mp.size(), vector<int>());
    for (auto [t, a, b, c] : edges) {
        if (b == c)
            continue;
        if (t == 0) {
            graph[mp[{a, b}]].emplace_back(mp[{a, c}]);
        } else {
            graph[mp[{b, a}]].emplace_back(mp[{c, a}]);
        }
    }

    stack<int> st;
    st.emplace(0);
    vector<tuple<int, int, int, int>> ans;
    while (!st.empty()) {
        int x = st.top();
        st.pop();
        for (auto y : graph[x]) {
            ans.emplace_back(points[x].x, points[x].y, points[y].x, points[y].y);
            st.emplace(y);
        }
    }

    cout << ans.size() << '\n';
    for (auto [x, y, z, w] : ans) cout << x << ' ' << y << ' ' << z << ' ' << w << '\n';
}

int main(void) {
    solve();
    return 0;
}
