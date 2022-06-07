#line 1 "a.cpp"
#define PROBLEM ""
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/template/template.hpp"
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
const double PI = acos(-1.0);
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/algorithm/compress.hpp"

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
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/data_structure/bit_vector.hpp"

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
            if (this->sum[m] < k)
                sl = m;
            else
                sr = m;
        }
        k -= this->sum[sl];
        unsigned int bl = 0, br = 32;
        while (br - bl > 1) {
            unsigned int m = (bl + br) >> 2;
            if (__builtin_popcount(this->bit[sl] & ((1U << m) - 1)) < k)
                bl = m;
            else
                br = m;
        }
        return (sl << 5) + bl;
    }

  private:
    unsigned int length, blocks;
    std::vector<unsigned int> bit, sum;
};
#line 3 "/home/kuhaku/atcoder/github/atcoder-lib/lib/data_structure/wavelet_matrix.hpp"

template <class T, int MAXLOG = 20>
struct wavelet_matrix {
    wavelet_matrix() = default;

    wavelet_matrix(std::vector<T> v) : length(v.size()) {
        std::vector<T> l(length), r(length);
        for (int level = MAXLOG - 1; level >= 0; level--) {
            this->matrix[level] = bit_vector(this->length + 1);
            int left = 0, right = 0;
            for (int i = 0; i < this->length; i++) {
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
            for (int i = 0; i < right; i++) { v[left + i] = r[i]; }
        }
    }

    T access(int k) const {
        T res = 0;
        for (int level = MAXLOG - 1; level >= 0; level--) {
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
        for (int level = MAXLOG - 1; level >= 0; level--) {
            tie(l, r) = this->succ((x >> level) & 1, l, r, level);
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
        for (int level = MAXLOG - 1; level >= 0; level--) {
            int cnt = this->matrix[level].rank(false, r) - this->matrix[level].rank(false, l);
            bool f = cnt <= k;
            if (f) {
                res |= T(1) << level;
                k -= cnt;
            }
            tie(l, r) = succ(f, l, r, level);
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
        for (int level = MAXLOG - 1; level >= 0; level--) {
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
    bit_vector matrix[MAXLOG];
    int mid[MAXLOG];

    std::pair<int, int> succ(bool f, int l, int r, int level) const {
        return std::make_pair(matrix[level].rank(f, l) + mid[level] * f,
                              matrix[level].rank(f, r) + mid[level] * f);
    }
};
#line 4 "/home/kuhaku/atcoder/github/atcoder-lib/lib/data_structure/compressed_wavelet_matrix.hpp"

template <class T, int MAXLOG = 20>
struct compressed_wavelet_matrix {
    wavelet_matrix<int, MAXLOG> mat;
    Compress<T> cps;

    compressed_wavelet_matrix(const vector<T> &v) : cps(v) {
        int n = v.size();
        std::vector<int> t(n);
        for (int i = 0; i < n; ++i) t[i] = this->cps.get(v[i]);
        this->mat = wavelet_matrix<int, MAXLOG>(t);
    }

    T access(int k) const { return this->cps[this->mat.access(k)]; }
    T operator[](int k) const { return this->access(k); }

    int rank(int r, T x) const {
        auto pos = this->cps.get(x);
        if (pos == this->cps.size() || this->cps[pos] != x) return 0;
        return this->mat.rank(r, pos);
    }

    T kth_smallest(int l, int r, int k) const { return this->cps[this->mat.kth_smallest(l, r, k)]; }

    T kth_largest(int l, int r, int k) const { return this->cps[this->mat.kth_largest(l, r, k)]; }

    int range_freq(int l, int r, T upper) const {
        return this->mat.range_freq(l, r, this->cps.get(upper));
    }

    int range_freq(int l, int r, T lower, T upper) const {
        return this->mat.range_freq(l, r, this->cps.get(lower), this->cps.get(upper));
    }

    T prev_value(int l, int r, T upper) const {
        auto res = this->mat.prev_value(l, r, this->cps.get(upper));
        return res == -1 ? T(-1) : this->cps[res];
    }

    T next_value(int l, int r, T lower) const {
        auto res = this->mat.next_value(l, r, this->cps.get(lower));
        return res == -1 ? T(-1) : this->cps[res];
    }
};
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/template/atcoder.hpp"
#pragma GCC target("avx")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#line 6 "/home/kuhaku/atcoder/github/atcoder-lib/lib/template/atcoder.hpp"
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
void Yes(bool is_correct) { std::cout<<(is_correct?"Yes":"No")<<std::endl; }
void YES(bool is_correct) { std::cout<<(is_correct?"YES":"NO")<<std::endl; }
#line 4 "a.cpp"

int main(void) {
    sonic();
    int q;
    cin >> q;

    vector<tuple<int, ll, int>> query(q);
    for (auto &[a, b, c] : query) {
        cin >> a >> b;
        if (a != 1)
            cin >> c;
    }

    vector<ll> v;
    for (auto [a, b, c] : query) {
        if (a == 1)
            v.emplace_back(b);
    }

    compressed_wavelet_matrix<ll, 20> wm(v);

    int count = 0;
    for (auto [a, b, k] : query) {
        if (a == 1)
            ++count;
        else if (a == 2) {
            int x = 0;
            b++;
            while (x < k) {
                b = wm.prev_value(0, count, b);
                if (b == -1) {
                    co(-1);
                    break;
                }
                x += wm.rank(count, b);
                if (x >= k)
                    co(b);
            }
        } else {
            int x = 0;
            b--;
            while (x < k) {
                b = wm.next_value(0, count, b + 1);
                if (b == -1) {
                    co(-1);
                    break;
                }
                x += wm.rank(count, b);
                ce(b, x);
                if (x >= k)
                    co(b);
            }
        }
    }

    return 0;
}
