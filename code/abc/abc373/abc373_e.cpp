#ifdef ATCODER
#pragma GCC target("sse4.2,avx512f,avx512dq,avx512ifma,avx512cd,avx512bw,avx512vl,bmi2")
#endif
#pragma GCC optimize("Ofast,fast-math,unroll-all-loops")
#include <bits/stdc++.h>
#ifndef ATCODER
#pragma GCC target("sse4.2,avx2,bmi2")
#endif
#include <bits/stdc++.h>

using namespace std;
#define SZ(x) (int)(x).size()
#define REP(i, n) for (int i = 0; i < (n); i++)
#define FOR(i, a, b) for (auto i = (a); i < (b); i++)
#define For(i, a, b, c) for (auto i = (a); i != (b); i += (c))
#define REPR(i, n) for (auto i = (n) - 1; i >= 0; i--)
#define ALL(s) (s).begin(), (s).end()
#define so(V) sort(ALL(V))
#define rev(V) reverse(ALL(V))
#define uni(v) v.erase(unique(ALL(v)), (v).end())
#define eb emplace_back

typedef unsigned long long ull;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<bool> vb;
typedef vector<vi> vvi;
typedef vector<vll> vvll;
typedef pair<int, int> PI;
typedef pair<ll, ll> PL;
const double EPS = 1e-6;
const int MOD = 1e9 + 7;
const int INF = (1 << 30);
const ll LINF = 1e18;
const double math_PI = acos(-1);

template <typename T>
vector<T> make_v(size_t a) {
    return vector<T>(a);
}

template <typename T, typename... Ts>
auto make_v(size_t a, Ts... ts) {
    return vector<decltype(make_v<T>(ts...))>(a, make_v<T>(ts...));
}

template <typename T, typename V>
typename enable_if<is_class<T>::value == 0>::type fill_v(T &t, const V &v) {
    t = v;
}

template <typename T, typename V>
typename enable_if<is_class<T>::value != 0>::type fill_v(T &t, const V &v) {
    for (auto &e : t) fill_v(e, v);
}

template <class T>
bool chmax(T &a, const T &b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

template <class T>
bool chmin(T &a, const T &b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

template <typename S, typename T>
istream &operator>>(istream &is, pair<S, T> &p) {
    cin >> p.first >> p.second;
    return is;
}

template <typename T>
istream &operator>>(istream &is, vector<T> &vec) {
    for (T &x : vec) is >> x;
    return is;
}

template <typename T>
string join(vector<T> &vec, string splitter) {
    stringstream ss;
    REP(i, SZ(vec)) {
        if (i != 0)
            ss << splitter;
        ss << vec[i];
    }
    return ss.str();
}

template <typename T>
ostream &operator<<(ostream &os, vector<T> &vec) {
    os << join(vec, " ");
    return os;
}

#ifdef LOCAL
#include "cpp-dump/cpp-dump.hpp"
CPP_DUMP_DEFINE_EXPORT_OBJECT_GENERIC(dump())
#define dump(...) cpp_dump(__VA_ARGS__)
namespace cp = cpp_dump;
#else
#define dump(...)
#define preprocess(...)
#define CPP_DUMP_SET_OPTION(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT(...)
#define CPP_DUMP_DEFINE_EXPORT_ENUM(...)
#define CPP_DUMP_DEFINE_DANGEROUS_EXPORT_OBJECT(...)
#endif
template <typename T, int MAX_LOG = 32>
struct BinaryTrie {
    struct Node {
        array<int, 2> next;  // 次の頂点番号
        int common;          // この頂点を通る文字列の数
        T lazy;
        Node() : next{-1, -1}, common(), lazy() {}
    };

    vector<Node> nodes;
    BinaryTrie() {
        nodes.push_back(Node());
    }

    void apply_xor(T val) {
        nodes[0].lazy ^= val;
    }

  private:
    void push(int cur, int b) {
        if ((nodes[cur].lazy >> (T)b) & (T)1) {
            swap(nodes[cur].next[0], nodes[cur].next[1]);
        }
        REP(i, 2) {
            if (nodes[cur].next[i] != -1) {
                nodes[nodes[cur].next[i]].lazy ^= nodes[cur].lazy;
            }
        }
        nodes[cur].lazy = 0;
    }

  public:
    void add(T val, int cur = 0, int b = MAX_LOG - 1) {
        nodes[cur].common++;
        if (b < 0) {
            return;
        }
        push(cur, b);
        int nxt = (val >> (T)b) & (T)1;
        if (nodes[cur].next[nxt] == -1) {
            nodes[cur].next[nxt] = SZ(nodes);
            nodes.push_back(Node());
        }
        add(val, nodes[cur].next[nxt], b - 1);
    }
    void erase(T val, int cur = 0, int b = MAX_LOG - 1) {
        assert(cur != -1);
        nodes[cur].common--;
        if (b < 0) {
            return;
        }
        push(cur, b);
        int nxt = (val >> (T)b) & (T)1;
        erase(val, nodes[cur].next[nxt], b - 1);
    }
    T min_element(T bxor = 0, int cur = 0, int b = MAX_LOG - 1) {
        if (b < 0)
            return 0;
        push(cur, b);
        int nxt = (bxor >> (T)b) & (T)1;
        int ind = nodes[cur].next[nxt];
        if (ind == -1 || nodes[ind].common == 0) {
            nxt = nxt ^ 1;
        }
        return min_element(bxor, nodes[cur].next[nxt], b - 1) | ((T)nxt << (T)b);
    }
    T max_element(T bxor = 0) {
        return min_element(~bxor);
    }
    int lower_bound_rank(T val, int cur = 0, int b = MAX_LOG - 1) {
        if (cur == -1 || b < 0)
            return 0;
        push(cur, b);
        int nxt = (val >> (T)b) & (T)1;
        int ret = lower_bound_rank(val, nodes[cur].next[nxt], b - 1);
        if (nxt == 1 && nodes[cur].next[0] != -1) {
            ret += nodes[nodes[cur].next[0]].common;
        }
        return ret;
    }

    int upper_bound_rank(T val) {
        return lower_bound_rank(val + 1);
    }

    T kth_smallest(int k, int cur = 0, int b = MAX_LOG - 1) {
        if (b < 0)
            return 0;
        push(cur, b);
        int lower_ind = nodes[cur].next[0];
        int lower_cnt = 0;
        if (lower_ind != -1) {
            lower_cnt = nodes[lower_ind].common;
        }
        if (k < lower_cnt) {
            return kth_smallest(k, nodes[cur].next[0], b - 1);
        } else {
            return kth_smallest(k - lower_cnt, nodes[cur].next[1], b - 1) | ((T)1 << (T)b);
        }
    }
    T kth_largest(int k) {
        return kth_smallest(size() - 1 - k);
    }

    T operator[](int k) {
        return kth_smallest(k);
    }

    int count(T val) {
        int cur = 0;
        REPR(b, MAX_LOG) {
            push(cur, b);
            cur = nodes[cur].next[(val >> (T)b) & (T)1];
            if (cur == -1)
                return 0;
        }
        return nodes[cur].common;
    }
    size_t size() const {
        return nodes[0].common;
    }
    bool empty() const {
        return nodes[0].common == 0;
    }
};
struct BitVector {
  private:
    vector<int> vec;
    int len;

  public:
    BitVector() {}
    BitVector(const vector<int> &v) {
        len = SZ(v);
        vec.resize(len + 1, 0);
        REP(i, len) {
            vec[i + 1] += vec[i];
            vec[i + 1] += v[i];
        }
    }
    int get(const unsigned int i) {
        return vec[i + 1] - vec[i];
    }

    unsigned int rank1(const unsigned int i) const {
        return vec[i];
    }
    unsigned int rank1(const unsigned int i, const unsigned int j) const {
        return rank1(j) - rank1(i);
    }
    unsigned int rank0(const unsigned int i) const {
        return i - rank1(i);
    }
    unsigned int rank0(const unsigned int i, const unsigned int j) const {
        return rank0(j) - rank0(i);
    }

    unsigned int rank(const unsigned int b, const unsigned int i) const {
        if (b == 0)
            return rank0(i);
        else
            return rank1(i);
    }

    unsigned int select(const unsigned int b, const unsigned int k) const {
        if (rank(b, len) >= k)
            return -1;
        int ok = 0;
        int ng = len;
        while (abs(ng - ok) > 1) {
            int mid = (ng + ok) / 2;
            if (rank(b, mid) <= k)
                ok = mid;
            else
                ng = mid;
        }
        return ok;
    }
};
template <typename T>
struct WaveletMatrix {
  private:
    vector<BitVector> B;    // ビットベクトル
    vector<vector<T>> acc;  // 各行での累積和
    vi start_one;           // ソート結果の1の開始地点
    map<T, int> start_num;  // 最終結果の各数字の開始地点
    int len, bit_len;
    T base = 0;

  public:
    WaveletMatrix(vector<T> vec, bool use_acc = true) {
        for (auto e : vec) chmax(base, -e);
        for (auto &&e : vec) e += base;
        ll max_el = vec.empty() ? 1 : *max_element(ALL(vec)) + 1;
        bit_len = (max_el == 1) ? 1 : (64 - __builtin_clzll(max_el - 1));
        len = SZ(vec);
        if (use_acc)
            acc = vector(bit_len, vector<T>(len + 1));
        start_one = vi(bit_len);
        vector<T> v(vec);
        REP(b, bit_len) {
            vector<T> cur;
            vi bi(len);
            REP(i, len) {
                ll bit = (v[i] >> T(bit_len - b - 1)) & 1;
                if (bit == 0) {
                    cur.push_back(v[i]);
                    bi[i] = 0;
                }
            }
            start_one[b] = SZ(cur);
            REP(i, len) {
                ll bit = (v[i] >> T(bit_len - b - 1)) & 1;
                if (bit == 1) {
                    cur.push_back(v[i]);
                    bi[i] = 1;
                }
            }
            B.push_back(BitVector(bi));
            if (use_acc) {
                REP(i, len) {
                    if (B[b].get(i) == 0)
                        acc[b][i + 1] = v[i];
                    acc[b][i + 1] += acc[b][i];
                }
            }
            v = cur;
        }

        REPR(i, len) {
            start_num[v[i]] = i;
        }
    }

    T access(int i) {
        assert(i < len);

        T ret = 0;
        REP(j, bit_len) {
            int b = B[j].get(i);
            ret <<= 1;
            ret |= b;
            i = B[j].rank(b, i);
            if (b == 1) {
                i += start_one[j];
            }
        }
        return ret - base;
    }

    int rank(T c, int k) {
        c += base;
        assert(k <= len);
        assert(k >= 0);
        if (start_num.find(c) == start_num.end())
            return 0;
        REP(i, bit_len) {
            ll bit = (c >> T(bit_len - i - 1)) & 1;
            k = B[i].rank(bit, k);
            if (bit == 1) {
                k += start_one[i];
            }
        }
        return k - start_num[c];
    }

    T kthMin(int left, int right, int k) {
        assert(right - left > k);
        assert(left < right);
        ll res = 0;
        REP(i, bit_len) {
            ll left_rank = B[i].rank(0, left);
            ll right_rank = B[i].rank(0, right);
            ll zero_in_range = right_rank - left_rank;
            ll bit = (k < zero_in_range) ? 0 : 1;
            if (bit == 1) {
                k -= zero_in_range;
                left += start_one[i] - left_rank;
                right += start_one[i] - right_rank;
            } else {
                left = left_rank;
                right = right_rank;
            }
            res <<= 1;
            res |= bit;
        }
        return res - base;
    }

    T kthMax(int left, int right, int k) {
        assert(right - left > k);
        assert(left < right);
        int len = right - left;
        int nk = len - k - 1;
        return kthMin(left, right, nk);
    }

    T kMinSum(int left, int right, int k) {
        int original_k = k;
        assert(right - left >= k);
        if (k == 0)
            return 0;
        assert(left < right);
        ll kth = 0;
        ll ret = 0;
        REP(i, bit_len) {
            ll left_rank = B[i].rank(0, left);
            ll right_rank = B[i].rank(0, right);
            ll zero_in_range = right_rank - left_rank;
            ll bit = (k < zero_in_range) ? 0 : 1;
            if (bit == 1) {
                ret += acc[i][right] - acc[i][left];
                k -= zero_in_range;
                left += start_one[i] - left_rank;
                right += start_one[i] - right_rank;
            } else {
                left = left_rank;
                right = right_rank;
            }
            kth <<= 1;
            kth |= bit;
        }
        ret += kth * k;
        return ret - base * original_k;
    }
    T kMaxSum(int left, int right, int k) {
        assert(right - left >= k);
        if (k == 0)
            return 0;
        assert(left < right);
        return kMinSum(left, right, right - left) - kMinSum(left, right, right - left - k);
    }
    int lessCount(int left, int right, T upper) {
        upper += base;
        assert(left <= right);
        ll ret = 0;
        if (left == right) {
            return 0;
        }
        if (upper >= T(T(1) << T(bit_len))) {
            return right - left;
        }
        REP(i, bit_len) {
            ll left_rank = B[i].rank(0, left);
            ll right_rank = B[i].rank(0, right);
            ll zero_in_range = right_rank - left_rank;
            ll bit = (upper >> T(bit_len - i - 1)) & 1;
            if (bit == 1) {
                ret += zero_in_range;
                left += start_one[i] - left_rank;
                right += start_one[i] - right_rank;
            } else {
                left = left_rank;
                right = right_rank;
            }
        }
        return ret;
    }
    int lessEqualCount(int left, int right, T upper) {
        assert(left <= right);
        return lessCount(left, right, upper) + rangeFreq(left, right, upper);
    }
    int greaterCount(int left, int right, T lower) {
        assert(left <= right);
        return right - left - lessEqualCount(left, right, lower);
    }
    int greaterEqualCount(int left, int right, T lower) {
        assert(left <= right);
        return right - left - lessCount(left, right, lower);
    }
    T greaterEqualKthMin(int left, int right, T lower, int k) {
        assert(left < right);
        int cnt = lessCount(left, right, lower);
        return kthMin(left, right, k + cnt);
    }
    T greaterKthMin(int left, int right, T lower, int k) {
        assert(left < right);
        int cnt = lessEqualCount(left, right, lower);
        return kthMin(left, right, k + cnt);
    }
    T lessKthMax(int left, int right, T upper, int k) {
        assert(left < right);
        int cnt = lessCount(left, right, upper);
        return kthMin(left, right, cnt - k - 1);
    }
    T lessEqualKthMax(int left, int right, T upper, int k) {
        assert(left < right);
        int cnt = lessEqualCount(left, right, upper);
        return kthMin(left, right, cnt - k - 1);
    }
    T lessKMaxSum(int left, int right, T upper, int k) {
        assert(left < right);
        int cnt = greaterEqualCount(left, right, upper);
        return kMaxSum(left, right, cnt + k) - kMaxSum(left, right, cnt);
    }
    T lessEqualKMaxSum(int left, int right, T upper, int k) {
        assert(left < right);
        int cnt = greaterCount(left, right, upper);
        return kMaxSum(left, right, cnt + k) - kMaxSum(left, right, cnt);
    }
    T greaterKMinSum(int left, int right, T lower, int k) {
        assert(left < right);
        int cnt = lessEqualCount(left, right, lower);
        return kMinSum(left, right, cnt + k) - kMinSum(left, right, cnt);
    }
    T greaterEqualKMinSum(int left, int right, T lower, int k) {
        assert(left < right);
        int cnt = lessCount(left, right, lower);
        return kMinSum(left, right, cnt + k) - kMinSum(left, right, cnt);
    }
    int valueRangeCount(int left, int right, T lower, T upper) {
        assert(left <= right);
        return lessCount(left, right, upper) - lessCount(left, right, lower);
    }
    T valueRangeSum(int left, int right, T lower, T upper) {
        assert(left <= right);
        int less = lessCount(left, right, lower);
        int greater = greaterEqualCount(left, right, upper);
        return kMaxSum(left, right, right - left) - kMaxSum(left, right, greater) -
               kMinSum(left, right, less);
    }
    int rangeFreq(int l, int r, T v) {
        assert(0 <= l && l <= r && r <= len);
        return rank(v, r) - rank(v, l);
    }
};

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int N, M;
    ll K;
    cin >> N >> M >> K;
    vll A(N);
    cin >> A;
    if (N == M) {
        vi ans(N);
        cout << ans << endl;
        return 0;
    }
    ll rest = K;
    BinaryTrie<ll, 42> trie;
    REP(i, N) {
        rest -= A[i];
        trie.add(A[i]);
    }
    WaveletMatrix<ll> wm(A);
    ll mth = wm.kthMax(0, N, M - 1);
    vll S(N);
    REP(i, N) {
        S[i] = wm.kMaxSum(0, N, i + 1);
    }
    ll sub = wm.kthMax(0, N, M);
    map<ll, ll> mm;
    vll ans(N);
    REP(i, N) {
        if (mm.contains(A[i])) {
            ans[i] = mm[A[i]];
            continue;
        }
        ll ok = rest + 100;
        ll ng = -1;
        auto isOk = [&](ll X) -> bool {
            ll border = A[i] + X;
            if (border < mth)
                return false;
            int rank = N - trie.upper_bound_rank(border);
            if (rank > M)
                return false;
            ll sum = S[M - 1];
            if (rank > 0) {
                sum -= S[rank - 1];
            }
            if (A[i] >= mth) {
                sum -= A[i];
                sum += sub;
            }
            dump(i, X, sum);
            ll R = rest - X;
            return R < (border + 1) * (M - rank) - sum;
        };
        while (ok - ng > 1) {
            ll mid = (ok + ng) / 2;
            if (isOk(mid))
                ok = mid;
            else
                ng = mid;
        }
        ans[i] = ok;
        if (ok > rest)
            ans[i] = -1;
        mm[A[i]] = ans[i];
    }
    cout << ans << endl;
    return 0;
}
