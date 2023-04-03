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
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U &b) {
    return (T)b < a ? a = (T)b, true : false;
}
constexpr int64_t INF = 1000000000000000003;
constexpr int Inf = 1000000003;
constexpr int MOD = 1000000007;
constexpr int MOD_N = 998244353;
constexpr double EPS = 1e-7;
constexpr double PI = M_PI;
#line 2 "/home/kuhaku/home/github/algo/lib/algorithm/rollback_mo.hpp"

/**
 * @brief rollback_mo's algorithm
 * @see https://ei1333.hateblo.jp/entry/2017/09/11/211011
 * @see https://snuke.hatenablog.com/entry/2016/07/01/000000
 *
 * @tparam F
 * @tparam G
 */
struct rollback_mo {
    rollback_mo(int n) : _left(), _right(), _order(), _size(n) {}

    void input(int q, int bias = 1, int closed = 0) {
        for (int i = 0; i < q; ++i) {
            int l, r;
            cin >> l >> r;
            this->add(l - bias, r - bias + closed);
        }
    }

    void add(int l, int r) {
        this->_left.emplace_back(l);
        this->_right.emplace_back(r);
    }
    void emplace(int l, int r) { return this->add(l, r); }
    void insert(int l, int r) { return this->add(l, r); }

    template <class F, class G, class H, class I, class J>
    void build(F rem, G save, H load, I addl, J addr) {
        int q = this->_left.size();
        int width = std::max(1, int(this->_size / sqrt(q)));
        this->_order.resize(q);
        std::iota(this->_order.begin(), this->_order.end(), 0);
        std::sort(this->_order.begin(), this->_order.end(), [&](int a, int b) -> bool {
            if (this->_left[a] / width != this->_left[b] / width)
                return this->_left[a] < this->_left[b];
            return this->_right[a] < this->_right[b];
        });

        auto reset = save();
        for (auto idx : this->_order) {
            if (this->_right[idx] - this->_left[idx] < width) {
                for (int i = this->_left[idx]; i < this->_right[idx]; i++) addr(i);
                rem(idx);
                load(reset);
            }
        }

        int right = 0, last_block = -1;
        for (auto idx : this->_order) {
            if (this->_right[idx] - this->_left[idx] < width) continue;
            int block = this->_left[idx] / width;
            if (block != last_block) {
                load(reset);
                last_block = block;
                right = (block + 1) * width;
            }
            while (right < this->_right[idx]) addr(right++);
            auto snapshot = save();
            for (int j = (block + 1) * width - 1; j >= this->_left[idx]; --j) addl(j);
            rem(idx);
            load(snapshot);
        }
    }

  private:
    std::vector<int> _left, _right, _order;
    int _size;
};
#line 2 "/home/kuhaku/home/github/algo/lib/data_structure/undo_deque.hpp"

template <class T>
struct undo_deque {
    T front() const { return this->data.front(); }
    T back() const { return this->data.back(); }
    bool empty() const { return this->data.empty(); }
    int size() const { return this->data.size(); }

    void emplace_front(T x) {
        this->history.emplace(0, x);
        this->data.emplace_front(x);
    }

    void emplace_back(T x) {
        this->history.emplace(1, x);
        this->data.emplace_back(x);
    }

    void pop_front() {
        this->history.emplace(2, this->data.front());
        this->data.pop_front();
    }

    void pop_back() {
        this->history.emplace(3, this->data.back());
        this->data.pop_back();
    }

    void undo() {
        auto [x, y] = this->history.top();
        this->history.pop();
        if (x == 0) this->data.pop_front();
        else if (x == 1) this->data.pop_back();
        else if (x == 2) this->data.emplace_front(y);
        else this->data.emplace_back(y);
    }

    int snapshot() const { return this->history.size(); }
    void rollback(int x = 0) {
        if (x == 0) {
            data.clear();
            history = std::stack<std::pair<int, T>>();
        }
        while (x < (int)this->history.size()) this->undo();
    }

  private:
    std::deque<T> data;
    std::stack<std::pair<int, T>> history;
};
#line 3 "/home/kuhaku/home/github/algo/lib/template/macro.hpp"
#define FOR(i, m, n) for (int i = (m); i < int(n); ++i)
#define FORR(i, m, n) for (int i = (m)-1; i >= int(n); --i)
#define FORL(i, m, n) for (int64_t i = (m); i < int64_t(n); ++i)
#define rep(i, n) FOR (i, 0, n)
#define repn(i, n) FOR (i, 1, n + 1)
#define repr(i, n) FORR (i, n, 0)
#define repnr(i, n) FORR (i, n + 1, 1)
#define all(s) (s).begin(), (s).end()
#line 3 "/home/kuhaku/home/github/algo/lib/template/sonic.hpp"
struct Sonic {
    Sonic() {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
    }

    constexpr void operator()() const {}
} sonic;
#line 5 "/home/kuhaku/home/github/algo/lib/template/atcoder.hpp"
using ll = int64_t;
using ld = long double;
template <class T, class U>
std::istream &operator>>(std::istream &is, std::pair<T, U> &p) {
    return is >> p.first >> p.second;
}
template <class T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) {
    for (T &i : v) is >> i;
    return is;
}
template <class T, class U>
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &p) {
    return os << '(' << p.first << ',' << p.second << ')';
}
template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    for (auto it = v.begin(); it != v.end(); ++it) {
        os << (it == v.begin() ? "" : " ") << *it;
    }
    return os;
}
template <class Head, class... Tail>
void co(Head &&head, Tail &&...tail) {
    if constexpr (sizeof...(tail) == 0) std::cout << head << '\n';
    else std::cout << head << ' ', co(std::forward<Tail>(tail)...);
}
template <class Head, class... Tail>
void ce(Head &&head, Tail &&...tail) {
    if constexpr (sizeof...(tail) == 0) std::cerr << head << '\n';
    else std::cerr << head << ' ', ce(std::forward<Tail>(tail)...);
}
template <typename T, typename... Args>
auto make_vector(T x, int arg, Args... args) {
    if constexpr (sizeof...(args) == 0) return std::vector<T>(arg, x);
    else return std::vector(arg, make_vector<T>(x, args...));
}
void setp(int n) {
    std::cout << std::fixed << std::setprecision(n);
}
void Yes(bool is_correct = true) {
    std::cout << (is_correct ? "Yes" : "No") << '\n';
}
void No(bool is_not_correct = true) {
    Yes(!is_not_correct);
}
void YES(bool is_correct = true) {
    std::cout << (is_correct ? "YES" : "NO") << '\n';
}
void NO(bool is_not_correct = true) {
    YES(!is_not_correct);
}
void Takahashi(bool is_correct = true) {
    std::cout << (is_correct ? "Takahashi" : "Aoki") << '\n';
}
void Aoki(bool is_not_correct = true) {
    Takahashi(!is_not_correct);
}
#line 5 "a.cpp"

int main(void) {
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;

    int q;
    cin >> q;
    rollback_mo mo(n);
    mo.input(q, 1, 1);

    undo_deque<int> st;
    vector<int> ans(q);
    auto rem = [&](int x) {
        ans[x] = st.size();
    };
    auto save = [&]() -> int {
        return st.snapshot();
    };
    auto load = [&](int x) {
        st.rollback(x);
    };
    auto addl = [&](int x) {
        while (!st.empty() && a[x] >= st.front()) st.pop_front();
        st.emplace_front(a[x]);
    };
    auto addr = [&](int x) {
        if (st.empty() || a[x] > st.back())
            st.emplace_back(a[x]);
    };

    mo.build(rem, save, load, addl, addr);
    for (auto x : ans) co(x);

    return 0;
}
