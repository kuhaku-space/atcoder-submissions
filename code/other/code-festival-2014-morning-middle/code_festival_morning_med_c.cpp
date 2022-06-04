#line 1 "Contests/AtCoder_code-festival-2014-morning-middle/code_festival_morning_med_c/main.cpp"
/* #define aclmodint */
/* #define aclsegtree */
/* #include <atcoder/all> */
/* using namespace atcoder; */

#line 1 "library/me/template.cpp"
#include <bits/stdc++.h>
using namespace std;

#define REP(a, b) for (int a = 0; a < (b); ++a)
#define ALL(a) (a).begin(), (a).end()
#define END(a)    \
    {             \
        print(a); \
        return;   \
    }
#define DBG(a)              \
    {                       \
        cerr << #a << ": "; \
        dbg(a);             \
    }
using ll = long long;
using P = pair<int, int>;
using VI = vector<int>;
using VVI = vector<VI>;
using VVVI = vector<VVI>;
using VL = vector<ll>;
using VVL = vector<VL>;
using VVVL = vector<VVL>;
using VP = vector<P>;
using VVP = vector<VP>;
using VVVP = vector<VVP>;
using LP = pair<ll, ll>;
using VLP = vector<LP>;
using VVLP = vector<VLP>;
using VVVLP = vector<VVLP>;
using VD = vector<double>;
using VVD = vector<VD>;
using VVVD = vector<VVD>;
using VS = vector<string>;
using VVS = vector<VS>;
using VVVS = vector<VVS>;
using VC = vector<char>;
using VVC = vector<VC>;
using VVVC = vector<VVC>;
constexpr int INF = 1001001001;
constexpr ll LINF = 1001001001001001001ll;

#ifdef aclmodint

using MI7 = modint1000000007;
using V7 = vector<MI7>;
using VV7 = vector<V7>;
using VVV7 = vector<VV7>;
using MI3 = modint998244353;
using V3 = vector<MI3>;
using VV3 = vector<V3>;
using VVV3 = vector<VV3>;

ostream &operator<<(ostream &os, const modint &x) {
    os << x.val();
    return os;
}

ostream &operator<<(ostream &os, const MI3 &x) {
    os << x.val();
    return os;
}

ostream &operator<<(ostream &os, const MI7 &x) {
    os << x.val();
    return os;
}

istream &operator>>(istream &is, modint &x) {
    int y;
    is >> y;
    x = y;
    return is;
}

istream &operator>>(istream &is, MI3 &x) {
    int y;
    is >> y;
    x = y;
    return is;
}

istream &operator>>(istream &is, MI7 &x) {
    int y;
    is >> y;
    x = y;
    return is;
}

#endif

template <class T>
void print(const T &t) {
    cout << t << '\n';
}
template <class Head, class... Tail>
void print(const Head &head, const Tail &...tail) {
    cout << head << ' ';
    print(tail...);
}

template <class T>
void dbg(const T &t) {
    cerr << t << '\n';
}
template <class Head, class... Tail>
void dbg(const Head &head, const Tail &...tail) {
    cerr << head << ' ';
    dbg(tail...);
}

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p) {
    os << p.first << " " << p.second;
    return os;
}

template <typename T1, typename T2>
istream &operator>>(istream &is, pair<T1, T2> &p) {
    is >> p.first >> p.second;
    return is;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    for (int i = 0; i < (int)v.size(); i++) {
        os << v[i] << (i + 1 != (int)v.size() ? " " : "");
    }
    return os;
}

template <typename T>
istream &operator>>(istream &is, vector<T> &v) {
    for (T &in : v)
        is >> in;
    return is;
}

template <typename T1, typename T2>
inline bool chmax(T1 &a, T2 b) {
    return a < b && (a = b, true);
}

template <typename T1, typename T2>
inline bool chmin(T1 &a, T2 b) {
    return a > b && (a = b, true);
}

#ifdef aclsegtree
template <typename S>
struct value_size {
    S value;
    int size;
};

template <typename S>
S min_op(S l, S r) {
    return min(l, r);
};
template <typename S>
S max_op(S l, S r) {
    return max(l, r);
};
template <typename S>
S sum_op(S l, S r) {
    return l + r;
};
template <typename S>
value_size<S> sum_op_size(value_size<S> l, value_size<S> r) {
    return {l.value + r.value, l.size + r.size};
};
template <typename S>
value_size<S> min_op_size(value_size<S> l, value_size<S> r) {
    return {min(l.value, r.value), l.size + r.size};
};
template <typename S>
value_size<S> max_op_size(value_size<S> l, value_size<S> r) {
    return {max(l.value, r.value), l.size + r.size};
};

template <typename S>
S min_e() {
    return numeric_limits<S>::max();
};
template <typename S>
S max_e() {
    return numeric_limits<S>::min();
};
template <typename S>
S sum_e() {
    return 0;
}
template <typename S>
value_size<S> sum_e_size() {
    return {0, 0};
}
template <typename S>
value_size<S> min_e_size() {
    return {numeric_limits<S>::max(), 0};
}
template <typename S>
value_size<S> max_e_size() {
    return {numeric_limits<S>::min(), 0};
}

template <typename S, typename F>
S chmin_mapping(F f, S x) {
    return min(x, f);
}
template <typename S, typename F>
S chmax_mapping(F f, S x) {
    return max(x, f);
}
template <typename S, typename F>
value_size<S> add_mapping(F f, value_size<S> x) {
    return {x.value + x.size * f, x.size};
}

template <typename F>
F chmin_composition(F f, F g) {
    return min(f, g);
}
template <typename F>
F chmax_composition(F f, F g) {
    return max(f, g);
}
template <typename F>
F add_composition(F f, F g) {
    return f + g;
}

template <typename F>
F chmin_id() {
    return numeric_limits<F>::max();
}
template <typename F>
F chmax_id() {
    return numeric_limits<F>::min();
}
template <typename F>
F add_id() {
    return 0;
}

template <typename S>
using RSumQ = segtree<S, sum_op<S>, sum_e<S>>;
template <typename S>
using RMaxQ = segtree<S, max_op<S>, max_e<S>>;
template <typename S>
using RMinQ = segtree<S, min_op<S>, min_e<S>>;

template <typename S, typename F>
using RAddSumQ =
    lazy_segtree<value_size<S>, sum_op_size<S>, sum_e_size<S>, F, add_mapping<S, F>, add_composition<F>, add_id<F>>;
template <typename S, typename F>
using RAddMinQ =
    lazy_segtree<value_size<S>, min_op_size<S>, min_e_size<S>, F, add_mapping<S, F>, add_composition<F>, add_id<F>>;
template <typename S, typename F>
using RAddMaxQ =
    lazy_segtree<value_size<S>, max_op_size<S>, max_e_size<S>, F, add_mapping<S, F>, add_composition<F>, add_id<F>>;
#endif
#line 1 "library/ei1333/math/matrix/matrix.cpp"
template <class T>
struct Matrix {
    vector<vector<T>> A;

    Matrix() {}

    Matrix(size_t n, size_t m) : A(n, vector<T>(m, 0)) {}

    Matrix(size_t n) : A(n, vector<T>(n, 0)){};

    size_t size() const {
        if (A.empty())
            return 0;
        assert(A.size() == A[0].size());
        return A.size();
    }

    size_t height() const {
        return (A.size());
    }

    size_t width() const {
        return (A[0].size());
    }

    inline const vector<T> &operator[](int k) const {
        return (A.at(k));
    }

    inline vector<T> &operator[](int k) {
        return (A.at(k));
    }

    static Matrix I(size_t n) {
        Matrix mat(n);
        for (int i = 0; i < n; i++)
            mat[i][i] = 1;
        return (mat);
    }

    Matrix &operator+=(const Matrix &B) {
        size_t n = height(), m = width();
        assert(n == B.height() && m == B.width());
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                (*this)[i][j] += B[i][j];
        return (*this);
    }

    Matrix &operator-=(const Matrix &B) {
        size_t n = height(), m = width();
        assert(n == B.height() && m == B.width());
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                (*this)[i][j] -= B[i][j];
        return (*this);
    }

    Matrix &operator*=(const Matrix &B) {
        size_t n = height(), m = B.width(), p = width();
        assert(p == B.height());
        vector<vector<T>> C(n, vector<T>(m, 0));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                for (int k = 0; k < p; k++)
                    C[i][j] = (C[i][j] + (*this)[i][k] * B[k][j]);
        A.swap(C);
        return (*this);
    }

    Matrix &operator^=(long long k) {
        Matrix B = Matrix::I(height());
        while (k > 0) {
            if (k & 1)
                B *= *this;
            *this *= *this;
            k >>= 1LL;
        }
        A.swap(B.A);
        return (*this);
    }

    Matrix operator+(const Matrix &B) const {
        return (Matrix(*this) += B);
    }

    Matrix operator-(const Matrix &B) const {
        return (Matrix(*this) -= B);
    }

    Matrix operator*(const Matrix &B) const {
        return (Matrix(*this) *= B);
    }

    Matrix operator^(const long long k) const {
        return (Matrix(*this) ^= k);
    }

    friend ostream &operator<<(ostream &os, Matrix &p) {
        size_t n = p.height(), m = p.width();
        for (int i = 0; i < n; i++) {
            os << "[";
            for (int j = 0; j < m; j++) {
                os << p[i][j] << (j + 1 == m ? "]\n" : ",");
            }
        }
        return (os);
    }

    T determinant() {
        Matrix B(*this);
        assert(width() == height());
        T ret = 1;
        for (int i = 0; i < width(); i++) {
            int idx = -1;
            for (int j = i; j < width(); j++) {
                if (B[j][i] != 0)
                    idx = j;
            }
            if (idx == -1)
                return (0);
            if (i != idx) {
                ret *= -1;
                swap(B[i], B[idx]);
            }
            ret *= B[i][i];
            T vv = B[i][i];
            for (int j = 0; j < width(); j++) {
                B[i][j] /= vv;
            }
            for (int j = i + 1; j < width(); j++) {
                T a = B[j][i];
                for (int k = 0; k < width(); k++) {
                    B[j][k] -= B[i][k] * a;
                }
            }
        }
        return (ret);
    }
};
#line 8 "Contests/AtCoder_code-festival-2014-morning-middle/code_festival_morning_med_c/main.cpp"

void solve() {
    double p;
    ll n;
    cin >> p >> n;
    print((1 - powl(1 - 2 * p, n)) / 2);
}

// generated by oj-template v4.7.2 (https://github.com/online-judge-tools/template-generator)
int main() {
    // Fasterize input/output script
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(100);
    // scanf/printf user should delete this fasterize input/output script

    int t = 1;
    // cin >> t; // comment out if solving multi testcase
    for (int testCase = 1; testCase <= t; ++testCase) {
        solve();
    }
    return 0;
}
