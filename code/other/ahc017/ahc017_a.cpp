#include <bits/stdc++.h>
using namespace std;
template <class T, class U>
bool chmax(T &a, const U b) {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U b) {
    return (T)b < a ? a = (T)b, true : false;
}

struct edge {
    int id, u, v, w;

    constexpr edge(int _id, int _u, int _v, int _w) : id(_id), u(_u), v(_v), w(_w) {}
};

struct S {
    int v, w;

    constexpr S(int _v, int _w) : v(_v), w(_w) {}
    constexpr bool operator<(const S &rhs) const {
        return this->w > rhs.w;
    }
};

struct union_find {
    union_find() : data() {}
    union_find(int _n) : data(_n, -1) {}

    int root(int x) {
        return this->data[x] < 0 ? x : this->data[x] = this->root(this->data[x]);
    }
    bool same(int x, int y) {
        return this->root(x) == this->root(y);
    }
    int size(int x) {
        return -(this->data[this->root(x)]);
    }
    bool unite(int x, int y) {
        x = this->root(x), y = this->root(y);
        if (x == y)
            return false;
        if (this->data[x] > this->data[y])
            swap(x, y);
        this->data[x] += this->data[y];
        this->data[y] = x;
        return true;
    }

  private:
    std::vector<int> data;
};

int N, M, D, K;

vector<tuple<int, int, int>> get_triangles(const vector<pair<int, int>> &edges) {
    map<pair<int, int>, int> mp;
    for (int m = 0; m < M; ++m) {
        auto [u, v] = edges[m];
        mp[{u, v}] = m;
        mp[{v, u}] = m;
    }

    vector<tuple<int, int, int>> triangles;
    for (int i = 0; i < M; ++i) {
        auto [u1, v1] = edges[i];
        for (int j = i + 1; j < M; ++j) {
            auto [u2, v2] = edges[j];
            for (int loop = 0; loop < 4; ++loop) {
                if (u1 == u2) {
                    if (mp.count({v1, v2})) {
                        int k = mp[{v1, v2}];
                        if (j < k)
                            triangles.emplace_back(i, j, k);
                    }
                    if (mp.count({v2, v1})) {
                        int k = mp[{v2, v1}];
                        if (j < k)
                            triangles.emplace_back(i, j, k);
                    }
                }
                if (loop & 1)
                    swap(u1, v1);
                else
                    swap(u2, v2);
            }
        }
    }
    return triangles;
}

vector<vector<int>> get_dists(const vector<vector<edge>> &graph) {
    vector<vector<int>> dists(N);
    for (int s = 0; s < N; ++s) {
        vector<int> dist(N, 1000000000);
        priority_queue<S> p_que;
        dist[s] = 0;
        p_que.emplace(s, 0);
        while (!p_que.empty()) {
            auto [x, d] = p_que.top();
            p_que.pop();
            for (auto [id, u, v, w] : graph[x]) {
                if (chmin(dist[v], d + w)) {
                    p_que.emplace(v, dist[v]);
                }
            }
        }
        dists[s] = dist;
    }
    return dists;
}

int get_score(const vector<vector<edge>> &graph, const vector<int> &color) {
    vector<vector<int>> dists = get_dists(graph);

    long long sum = 0;
    for (int i = 0; i < D; ++i) {
        for (int s = 0; s < N; ++s) {
            vector<int> dist(N, 1000000000);
            priority_queue<S> p_que;
            dist[s] = 0;
            p_que.emplace(s, 0);
            while (!p_que.empty()) {
                auto [x, d] = p_que.top();
                p_que.pop();
                for (auto [id, u, v, w] : graph[x]) {
                    if (color[id] == i)
                        continue;
                    if (chmin(dist[v], d + w)) {
                        p_que.emplace(v, dist[v]);
                    }
                }
            }
            for (int t = 0; t < N; ++t) {
                sum += dist[t] - dists[s][t];
            }
        }
    }
    return sum / N / (N - 1) / D;
}

int main(void) {
    cin >> N >> M >> D >> K;
    vector<pair<int, int>> edges;
    vector<vector<edge>> graph(N);
    for (int m = 0; m < M; ++m) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        edges.emplace_back(u, v);
        graph[u].emplace_back(m, u, v, w);
        graph[v].emplace_back(m, v, u, w);
    }

    auto dists = get_dists(graph);
    vector<vector<int>> edge_dists(M);
    for (int i = 0; i < M; ++i) {
        auto [u1, v1] = edges[i];
        vector<int> dist(M, 1000000000);
        for (int j = 0; j < M; ++j) {
            auto [u2, v2] = edges[j];
            chmin(dist[j], dists[u1][u2]);
            chmin(dist[j], dists[u1][v2]);
            chmin(dist[j], dists[v1][u2]);
            chmin(dist[j], dists[v1][v2]);
        }
        edge_dists[i] = dist;
    }

    mt19937 rnd;
    vector<int> color(M);
    {
        vector<int> v(M);
        iota(v.begin(), v.end(), 0);
        shuffle(v.begin(), v.end(), rnd);
        int L = M / D;
        for (int m = 0; m < M; ++m) {
            if (m < L * D)
                color[v[m]] = m / L;
            else
                color[v[m]] = m - L * D;
        }
    }

    vector<int> color_num(D);
    for (int m = 0; m < M; ++m) {
        ++color_num[color[m]];
    }
    while ((double)clock() / CLOCKS_PER_SEC < 5.0) {
        int r = rnd() % M;
        --color_num[color[r]];
        vector<double> color_weight(D);
        vector<union_find> uf(D, union_find(M));
        for (int m = 0; m < M; ++m) {
            if (m == r)
                continue;
            color_weight[color[m]] += 1.0 / (edge_dists[r][m] + 1);
            auto [u, v] = edges[m];
            for (int d = 0; d < D; ++d) {
                if (d == color[m])
                    continue;
                uf[d].unite(u, v);
            }
        }

        double min_weight = 1000000000;
        int c = color[r];
        auto [u, v] = edges[r];
        for (int d = 0; d < D; ++d) {
            if (color_num[d] < K && uf[d].same(u, v) && chmin(min_weight, color_weight[d]))
                c = d;
        }
        color[r] = c;
        ++color_num[c];
    }

    for (int m = 0; m < M; ++m) {
        assert(0 <= color[m] && color[m] < D);
        cout << color[m] + 1;
        if (m == M - 1)
            cout << endl;
        else
            cout << ' ';
    }

#ifndef ONLINE_JUDGE
    cerr << get_score(graph, color) << endl;
#endif

    return 0;
}
