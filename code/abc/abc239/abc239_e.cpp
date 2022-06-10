#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/home/github/algo/lib/template/template.hpp"
#pragma GCC target("sse4.2,avx2,bmi2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
template <class T, class U>
bool chmax(T &a, const U &b) {
    return a < b ? a = b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U &b) {
    return b < a ? a = b, true : false;
}
constexpr int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
constexpr double PI = M_PI;
#line 2 "/home/kuhaku/home/github/algo/lib/algorithm/compress.hpp"

/**
 * @brief 座標圧縮
 *
 * @tparam T 要素の型
 */
template <class T>
struct Compress {
    Compress() {}
    Compress(const vector<T>& _data) : data(_data) { this->build(); }

    const T& operator[](int i) const { return this->data[i]; }
    T& operator[](int i) { return this->data[i]; }

    void add(T x) { this->data.emplace_back(x); }

    void build() {
        std::sort(this->data.begin(), this->data.end());
        this->data.erase(std::unique(this->data.begin(), this->data.end()), this->data.end());
    }
    void build(const vector<T>& _data) {
        this->data = _data;
        std::sort(this->data.begin(), this->data.end());
        this->data.erase(std::unique(this->data.begin(), this->data.end()), this->data.end());
    }

    bool exist(T x) const {
        auto it = std::lower_bound(this->data.begin(), this->data.end(), x);
        return it != this->data.end() && *it == x;
    }

    int get(T x) const {
        auto it = std::lower_bound(this->data.begin(), this->data.end(), x);
        return it - this->data.begin();
    }

    int size() const { return this->data.size(); }

  private:
    std::vector<T> data;
};
#line 2 "/home/kuhaku/home/github/algo/lib/data_structure/bit_vector.hpp"

/**
 * @brief 完備辞書
 *
 * @details
 * [参考](https://ei1333.github.io/library/structure/wavelet/succinct-indexable-dictionary.cpp)
 */
struct bit_vector {
    bit_vector() = default;
    bit_vector(unsigned int _length)
        : length(_length),
          blocks((_length + 31) >> 5),
          bit((_length + 31) >> 5),
          sum((_length + 31) >> 5) {}

    void set(unsigned int k) { this->bit[k >> 5] |= 1U << (k & 31); }

    void build() {
        this->sum[0] = 0U;
        for (unsigned int i = 1; i < this->blocks; ++i) {
            this->sum[i] = this->sum[i - 1] + __builtin_popcount(bit[i - 1]);
        }
    }

    bool operator[](unsigned int k) const { return this->bit[k >> 5] >> (k & 31) & 1; }

    unsigned int rank(unsigned int k) const {
        return this->sum[k >> 5] + __builtin_popcount(this->bit[k >> 5] & ((1U << (k & 31)) - 1));
    }
    unsigned int rank(bool val, unsigned int k) const {
        return val ? this->rank(k) : k - this->rank(k);
    }

    unsigned int select(unsigned int k) const {
        unsigned int sl = 0, sr = this->blocks + 1;
        while (sr - sl > 1) {
            unsigned int m = (sl + sr) >> 2;
            if (this->sum[m] < k) sl = m;
            else sr = m;
        }
        k -= this->sum[sl];
        unsigned int bl = 0, br = 32;
        while (br - bl > 1) {
            unsigned int m = (bl + br) >> 2;
            if (__builtin_popcount(this->bit[sl] & ((1U << m) - 1)) < k) bl = m;
            else br = m;
        }
        return (sl << 5) + bl;
    }

  private:
    unsigned int length, blocks;
    std::vector<unsigned int> bit, sum;
};
#line 3 "/home/kuhaku/home/github/algo/lib/matrix/wavelet_matrix.hpp"

/**
 * @brief ウェーブレット行列
 * @details [参考](https://ei1333.github.io/library/structure/wavelet/wavelet-matrix.cpp.html)
 *
 * @tparam T
 * @tparam L
 */
template <class T, int L = 20>
struct wavelet_matrix {
    wavelet_matrix() = default;
    wavelet_matrix(std::vector<T> v) : length(v.size()) {
        std::vector<T> l(length), r(length);
        for (int level = L - 1; level >= 0; --level) {
            this->matrix[level] = bit_vector(this->length + 1);
            int left = 0, right = 0;
            for (int i = 0; i < this->length; ++i) {
                if (v[i] >> level & 1) {
                    this->matrix[level].set(i);
                    r[right++] = v[i];
                } else {
                    l[left++] = v[i];
                }
            }
            this->mid[level] = left;
            this->matrix[level].build();
            v.swap(l);
            for (int i = 0; i < right; ++i) { v[left + i] = r[i]; }
        }
    }

    T access(int k) const {
        T res = 0;
        for (int level = L - 1; level >= 0; --level) {
            bool f = this->matrix[level][k];
            if (f) res |= T(1) << level;
            k = this->matrix[level].rank(f, k) + this->mid[level] * f;
        }
        return res;
    }
    T operator[](int k) const { return this->access(k); }

    /**
     * @brief count i s.t. (0 <= i < r) && v[i] == x
     *
     * @param x
     * @param r
     * @return int
     */
    int rank(int r, T x) const {
        int l = 0;
        for (int level = L - 1; level >= 0; --level) {
            std::tie(l, r) = this->succ((x >> level) & 1, l, r, level);
        }
        return r - l;
    }

    /**
     * @brief count i s.t. (l <= i < r) && v[i] == x
     *
     * @param l
     * @param r
     * @param x
     * @return int
     */
    int rank(int l, int r, T x) const { return this->rank(r, x) - this->rank(l, x); }

    /**
     * @brief k-th smallest number in v[l ... r-1]
     *
     * @param l
     * @param r
     * @param k
     * @return T
     */
    T kth_smallest(int l, int r, int k) const {
        assert(0 <= k && k < r - l);
        T res = 0;
        for (int level = L - 1; level >= 0; --level) {
            int cnt = this->matrix[level].rank(false, r) - this->matrix[level].rank(false, l);
            bool f = cnt <= k;
            if (f) {
                res |= T(1) << level;
                k -= cnt;
            }
            std::tie(l, r) = succ(f, l, r, level);
        }
        return res;
    }

    /**
     * @brief k-th largest number in v[l ... r-1]
     *
     * @param l
     * @param r
     * @param k
     * @return T
     */
    T kth_largest(int l, int r, int k) const { return this->kth_smallest(l, r, r - l - k - 1); }

    /**
     * @brief count i s.t. (l <= i < r) && (v[i] < upper)
     *
     * @param l
     * @param r
     * @param upper
     * @return int
     */
    int range_freq(int l, int r, T upper) const {
        int res = 0;
        for (int level = L - 1; level >= 0; --level) {
            bool f = ((upper >> level) & 1);
            if (f) res += this->matrix[level].rank(false, r) - this->matrix[level].rank(false, l);
            tie(l, r) = this->succ(f, l, r, level);
        }
        return res;
    }

    /**
     * @brief count i s.t. (l <= i < r) && (lower <= v[i] < upper)
     *
     * @param l
     * @param r
     * @param lower
     * @param upper
     * @return int
     */
    int range_freq(int l, int r, T lower, T upper) const {
        return this->range_freq(l, r, upper) - this->range_freq(l, r, lower);
    }

    /**
     * @brief max v[i] s.t. (l <= i < r) && (v[i] < upper)
     *
     * @param l
     * @param r
     * @param upper
     * @return T
     */
    T prev_value(int l, int r, T upper) const {
        int cnt = this->range_freq(l, r, upper);
        return cnt == 0 ? T(-1) : this->kth_smallest(l, r, cnt - 1);
    }

    /**
     * @brief min v[i] s.t. (l <= i < r) && (lower <= v[i])
     *
     * @param l
     * @param r
     * @param lower
     * @return T
     */
    T next_value(int l, int r, T lower) const {
        int cnt = this->range_freq(l, r, lower);
        return cnt == r - l ? T(-1) : this->kth_smallest(l, r, cnt);
    }

  private:
    int length;
    bit_vector matrix[L];
    int mid[L];

    std::pair<int, int> succ(bool f, int l, int r, int level) const {
        return {this->matrix[level].rank(f, l) + this->mid[level] * f,
                this->matrix[level].rank(f, r) + this->mid[level] * f};
    }
};
#line 4 "/home/kuhaku/home/github/algo/lib/matrix/compressed_wavelet_matrix.hpp"

/**
 * @brief ウェーブレット行列
 * @details [参考](https://ei1333.github.io/library/structure/wavelet/wavelet-matrix.cpp.html)
 *
 * @tparam T
 * @tparam MAXLOG
 */
template <class T, int MAXLOG = 20>
struct compressed_wavelet_matrix {
    compressed_wavelet_matrix() = default;
    compressed_wavelet_matrix(const vector<T> &v) : cps(v) {
        int n = v.size();
        std::vector<int> t(n);
        for (int i = 0; i < n; ++i) t[i] = this->cps.get(v[i]);
        this->mat = wavelet_matrix<int, MAXLOG>(t);
    }

    T access(int k) const { return this->cps[this->mat.access(k)]; }
    T operator[](int k) const { return this->access(k); }

    /**
     * @brief count i s.t. (0 <= i < r) && v[i] == x
     *
     * @param x
     * @param r
     * @return int
     */
    int rank(int r, T x) const {
        auto pos = this->cps.get(x);
        if (pos == this->cps.size() || this->cps[pos] != x) return 0;
        return this->mat.rank(r, pos);
    }

    /**
     * @brief count i s.t. (l <= i < r) && v[i] == x
     *
     * @param l
     * @param r
     * @param x
     * @return int
     */
    int rank(int l, int r, T x) const { return this->rank(r, x) - this->rank(l, x); }

    /**
     * @brief k-th smallest number in v[l ... r-1]
     *
     * @param l
     * @param r
     * @param k
     * @return T
     */
    T kth_smallest(int l, int r, int k) const { return this->cps[this->mat.kth_smallest(l, r, k)]; }

    /**
     * @brief k-th largest number in v[l ... r-1]
     *
     * @param l
     * @param r
     * @param k
     * @return T
     */
    T kth_largest(int l, int r, int k) const { return this->cps[this->mat.kth_largest(l, r, k)]; }

    /**
     * @brief count i s.t. (l <= i < r) && (v[i] < upper)
     *
     * @param l
     * @param r
     * @param upper
     * @return int
     */
    int range_freq(int l, int r, T upper) const {
        return this->mat.range_freq(l, r, this->cps.get(upper));
    }

    /**
     * @brief count i s.t. (l <= i < r) && (lower <= v[i] < upper)
     *
     * @param l
     * @param r
     * @param lower
     * @param upper
     * @return int
     */
    int range_freq(int l, int r, T lower, T upper) const {
        return this->mat.range_freq(l, r, this->cps.get(lower), this->cps.get(upper));
    }

    /**
     * @brief max v[i] s.t. (l <= i < r) && (v[i] < upper)
     *
     * @param l
     * @param r
     * @param upper
     * @return T
     */
    T prev_value(int l, int r, T upper) const {
        auto res = this->mat.prev_value(l, r, this->cps.get(upper));
        return res == -1 ? T(-1) : this->cps[res];
    }

    /**
     * @brief min v[i] s.t. (l <= i < r) && (lower <= v[i])
     *
     * @param l
     * @param r
     * @param lower
     * @return T
     */
    T next_value(int l, int r, T lower) const {
        auto res = this->mat.next_value(l, r, this->cps.get(lower));
        return res == -1 ? T(-1) : this->cps[res];
    }

  private:
    wavelet_matrix<int, MAXLOG> mat;
    Compress<T> cps;
};
#line 3 "/home/kuhaku/home/github/algo/lib/template/atcoder.hpp"
using ll = int64_t;
using ld = long double;
#define FOR(i, m, n) for(int i = (m); i < int(n); ++i)
#define FORR(i, m, n) for(int i = (m)-1; i >= int(n); --i)
#define FORL(i, m, n) for(int64_t i = (m); i < int64_t(n); ++i)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FOR(i, 1, n+1)
#define repr(i, n) FORR(i, n, 0)
#define repnr(i, n) FORR(i, n+1, 1)
#define all(s) (s).begin(), (s).end()
template<class T, class U>
std::istream &operator>>(std::istream &is, std::pair<T, U> &p) { is >> p.first >> p.second; return is; }
template <class T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) { for (T &i : v) is>>i; return is; }
template <class T, class U>
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &p) {
    return os<<'('<<p.first<< ','<<p.second<<')';
}
template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    for (auto it=v.begin(); it!=v.end(); ++it) { os<<(it==v.begin()?"":" ")<<*it; } return os;
}
template <class Head, class... Tail>
void co(Head&& head, Tail&&... tail) {
    if constexpr(sizeof...(tail)==0) std::cout<<head<<'\n'; else std::cout<<head<<' ',co(forward<Tail>(tail)...);
}
template <class Head, class... Tail>
void ce(Head&& head, Tail&&... tail) {
    if constexpr(sizeof...(tail)==0) std::cerr<<head<<'\n'; else std::cerr<<head<<' ',ce(forward<Tail>(tail)...);
}
template<typename T, typename... Args>
auto make_vector(T x, int arg, Args ...args) {
    if constexpr(sizeof...(args)==0) return std::vector<T>(arg,x); else return std::vector(arg,make_vector<T>(x,args...));
}
void sonic() { std::ios::sync_with_stdio(false); std::cin.tie(nullptr); }
void setp(const int n) { std::cout<<std::fixed<<std::setprecision(n); }
void Yes(bool is_correct=true) { std::cout<<(is_correct?"Yes":"No")<<std::endl; }
void No(bool is_not_correct=true) { Yes(!is_not_correct); }
void YES(bool is_correct=true) { std::cout<<(is_correct?"YES":"NO")<<std::endl; }
void NO(bool is_not_correct=true) { YES(!is_not_correct); }
void Takahashi(bool is_correct=true) { std::cout<<(is_correct?"Takahashi":"Aoki")<<std::endl; }
void Aoki(bool is_not_correct=true) { Takahashi(!is_not_correct); }
#line 3 "/home/kuhaku/home/github/algo/lib/graph/graph.hpp"

/**
 * @brief 重み付きグラフ
 *
 * @tparam T 辺の重みの型
 */
template <class T>
struct Graph {
  private:
    struct _edge {
        constexpr _edge() : _from(), _to(), _weight() {}
        constexpr _edge(int from, int to, T weight) : _from(from), _to(to), _weight(weight) {}
        bool operator<(const _edge &rhs) const { return this->weight() < rhs.weight(); }
        bool operator>(const _edge &rhs) const { return rhs < *this; }

        constexpr int from() const { return this->_from; }
        constexpr int to() const { return this->_to; }
        constexpr T weight() const { return this->_weight; }

      private:
        int _from, _to;
        T _weight;
    };

  public:
    using edge_type = typename Graph<T>::_edge;

    Graph(int v) : _size(v), edges(v) {}

    const auto &operator[](int i) const { return this->edges[i]; }
    auto &operator[](int i) { return this->edges[i]; }
    const auto begin() const { return this->edges.begin(); }
    auto begin() { return this->edges.begin(); }
    const auto end() const { return this->edges.end(); }
    auto end() { return this->edges.end(); }
    constexpr int size() const { return this->_size; }

    void add_edge(const edge_type &e) { this->edges[e.from()].emplace_back(e); }
    void add_edge(int from, int to, T weight = T(1)) {
        this->edges[from].emplace_back(from, to, weight);
    }
    void add_edges(int from, int to, T weight = T(1)) {
        this->edges[from].emplace_back(from, to, weight);
        this->edges[to].emplace_back(to, from, weight);
    }

    void input_edge(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            T weight;
            cin >> from >> to >> weight;
            this->add_edge(from - base, to - base, weight);
        }
    }
    void input_edges(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            T weight;
            cin >> from >> to >> weight;
            this->add_edges(from - base, to - base, weight);
        }
    }

  private:
    int _size;
    std::vector<std::vector<edge_type>> edges;
};

template <>
struct Graph<void> {
  private:
    struct _edge {
        constexpr _edge() : _from(), _to() {}
        constexpr _edge(int from, int to) : _from(from), _to(to) {}

        constexpr int from() const { return this->_from; }
        constexpr int to() const { return this->_to; }
        constexpr int weight() const { return 1; }
        bool operator<(const _edge &rhs) const { return false; }
        bool operator>(const _edge &rhs) const { return rhs < *this; }

      private:
        int _from, _to;
    };

  public:
    using edge_type = typename Graph<void>::_edge;

    Graph(int v) : _size(v), edges(v) {}

    const auto &operator[](int i) const { return this->edges[i]; }
    auto &operator[](int i) { return this->edges[i]; }
    const auto begin() const { return this->edges.begin(); }
    auto begin() { return this->edges.begin(); }
    const auto end() const { return this->edges.end(); }
    auto end() { return this->edges.end(); }
    constexpr int size() const { return this->_size; }

    void add_edge(const edge_type &e) { this->edges[e.from()].emplace_back(e); }
    void add_edge(int from, int to) { this->edges[from].emplace_back(from, to); }
    void add_edges(int from, int to) {
        this->edges[from].emplace_back(from, to);
        this->edges[to].emplace_back(to, from);
    }

    void input_edge(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            cin >> from >> to;
            this->add_edge(from - base, to - base);
        }
    }
    void input_edges(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            cin >> from >> to;
            this->add_edges(from - base, to - base);
        }
    }

  private:
    int _size;
    std::vector<std::vector<edge_type>> edges;
};
#line 3 "/home/kuhaku/home/github/algo/lib/tree/eular_tour.hpp"

/**
 * @brief オイラーツアー
 * @details [参考](https://github.com/beet-aizu/library/blob/master/tree/eulertourforvertex.cpp)
 *
 * @tparam T 辺の重みの型
 */
template <class T>
struct eular_tour {
    eular_tour(const Graph<T> &_g, int r = 0) : g(_g), ls(_g.size()), rs(_g.size()), pos() {
        this->build(r);
    }

    std::pair<int, int> operator[](int i) const { return {this->ls[i], this->rs[i]}; }

    int size() const { return this->pos; }

    int get_l(int i) const { return this->ls[i]; }
    int get_r(int i) const { return this->rs[i]; }

    template <class F>
    void query(int v, const F &f) const {
        f(this->ls[v], this->rs[v]);
    }

  private:
    const Graph<T> &g;
    std::vector<int> ls, rs;
    int pos;

    void build(int r = 0) {
        this->pos = 0;
        this->dfs(r, -1);
    }

    void dfs(int v, int p) {
        this->ls[v] = this->pos++;
        for (auto &e : this->g[v]) {
            if (e.to() != p) this->dfs(e.to(), v);
        }
        this->rs[v] = this->pos;
    }
};
#line 5 "a.cpp"

int main(void) {
    sonic();
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    cin >> a;
    Graph<void> g(n);
    g.input_edges(n - 1);
    eular_tour et(g);

    vector<int> x(n);
    rep(i, n) {
        x[et.get_l(i)] = a[i];
    }
    compressed_wavelet_matrix wm(x);

    rep(i, q) {
        int v, k;
        cin >> v >> k;
        auto f = [&](int l, int r) {
            co(wm.kth_largest(l, r, k - 1));
        };
        et.query(v - 1, f);
    }

    return 0;
}
