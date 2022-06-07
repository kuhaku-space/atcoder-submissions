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
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/data_structure/radix_heap.hpp"

template <class Key, class Value>
struct radix_heap {
  private:
    struct _node {
        using pointer = _node*;
        Key key;
        Value value;
        int index;

        constexpr _node(Key _key, Value _value) : key(_key), value(_value), index() {}
        constexpr _node(Key _key, Value _value, int _index)
            : key(_key), value(_value), index(_index) {}

        constexpr bool operator<(const _node& rhs) const { return this->value < rhs.value; }

        constexpr auto get_pair() const { return make_pair(key, value); }
    };

  public:
    using node_pointer = typename _node::pointer;

    radix_heap() : v{}, _last(), _size() {}

    constexpr int size() const { return this->_size; }
    constexpr bool empty() const { return this->_size == 0; }

    auto push(Key key, Value value) {
        assert(value >= this->_last);
        ++this->_size;
        auto node = new _node(key, value, this->find_bucket(value ^ this->_last));
        this->v[node->index].emplace(node);
        return node;
    }
    auto emplace(Key key, Value value) { return this->push(key, value); }

    auto top() {
        if (this->v[0].empty()) this->relocate();
        return (*this->v[0].begin())->get_pair();
    }

    void pop() {
        assert(this->_size);
        if (this->v[0].empty()) this->relocate();
        this->v[0].erase(this->v[0].begin());
        --this->_size;
    }

    void update(node_pointer node, Value value) {
        if (value < node->value)
            node->value = value;
        else
            return;
        this->v[node->index].erase(node);
        node->index = this->find_bucket(value ^ this->_last);
        this->v[this->find_bucket(value ^ this->_last)].emplace(node);
    }

  private:
    std::unordered_set<node_pointer> v[std::numeric_limits<Value>::digits + 1];
    Value _last;
    int _size;

    int find_bucket(Value value) const {
        return value == 0 ? 0 : std::numeric_limits<Value>::digits - this->clz(value);
    }

    template <class U>
    int clz(U x) const {
        static_assert(std::is_integral_v<U>);
        if constexpr (std::is_signed_v<U>)
            return this->clz_unsigned(std::make_unsigned_t<U>(x)) - 1;
        else
            return this->clz_unsigned(x);
    }

    template <class U>
    int clz_unsigned(U x) const {
        static_assert(std::is_integral_v<U> && std::is_unsigned_v<U>);
        if constexpr (std::is_same_v<U, unsigned int>)
            return __builtin_clz(x);
        else if constexpr (std::is_same_v<U, unsigned long>)
            return __builtin_clzl(x);
        else if constexpr (std::is_same_v<U, unsigned long long>)
            return __builtin_clzll(x);
        else
            return -1;
    }

    void relocate() {
        int index = 1;
        while (v[index].empty()) ++index;
        auto new_last = (*std::min_element(this->v[index].begin(), this->v[index].end(),
                                           [](const auto& a, const auto& b) {
                                               return a->value < b->value;
                                           }))
                            ->value;
        for (auto node : this->v[index]) {
            node->index = this->find_bucket(node->value ^ new_last);
            this->v[this->find_bucket(node->value ^ new_last)].emplace(node);
        }
        this->_last = new_last;
        this->v[index].clear();
    }
};

template <class T>
struct radix_heap<void, T> {
    radix_heap() : v{}, _last(), _size() {}

    constexpr int size() const { return this->_size; }
    constexpr bool empty() const { return this->_size == 0; }

    void push(T x) {
        assert(x >= this->_last);
        ++this->_size;
        this->v[this->find_bucket(x ^ this->_last)].emplace_back(x);
    }
    void emplace(T x) { this->push(x); }

    T top() {
        if (this->v[0].empty()) this->relocate();
        return this->_last;
    }

    void pop() {
        assert(this->_size);
        if (this->v[0].empty()) this->relocate();
        this->v[0].pop_back();
        --this->_size;
    }

  private:
    std::vector<T> v[std::numeric_limits<T>::digits + 1];
    T _last;
    int _size;

    int find_bucket(T x) const {
        return x == 0 ? 0 : std::numeric_limits<T>::digits - this->clz(x);
    }

    template <class U>
    int clz(U x) const {
        static_assert(std::is_integral_v<U>);
        if constexpr (std::is_signed_v<U>)
            return this->clz_unsigned(std::make_unsigned_t<U>(x)) - 1;
        else
            return this->clz_unsigned(x);
    }

    template <class U>
    int clz_unsigned(U x) const {
        static_assert(std::is_integral_v<U> && std::is_unsigned_v<U>);
        if constexpr (std::is_same_v<U, unsigned int>)
            return __builtin_clz(x);
        else if constexpr (std::is_same_v<U, unsigned long>)
            return __builtin_clzl(x);
        else if constexpr (std::is_same_v<U, unsigned long long>)
            return __builtin_clzll(x);
        else
            return -1;
    }

    void relocate() {
        int index = 1;
        while (v[index].empty()) ++index;
        auto new_last = *min_element(this->v[index].begin(), this->v[index].end());
        for (auto x : this->v[index]) { this->v[this->find_bucket(x ^ new_last)].emplace_back(x); }
        this->_last = new_last;
        this->v[index].clear();
    }
};

template <class T>
struct radix_heap_dijkstra {
    vector<T> v[33];
    T last;
    unsigned int sz;
    bool is_top;

    radix_heap_dijkstra() : last(), sz(), is_top() {}

    int bsr(unsigned int x) {
        if (x == 0) return -1;
        return 31 - __builtin_clz(x);
    }

    bool empty() const { return sz == 0; }
    auto size() const { return sz; }

    void push(T x) {
        assert(x.dist >= last.dist);
        ++sz;
        v[bsr(x.dist ^ last.dist) + 1].emplace_back(x);
    }

    auto top() {
        if (!is_top) pop();
        is_top = true;
        return last;
    }

    void pop() {
        if (is_top) {
            is_top = false;
            return;
        }
        assert(sz);
        if (!v[0].size()) {
            int index = 1;
            while (!v[index].size()) ++index;
            auto new_last = *min_element(v[index].begin(), v[index].end());
            for (auto x : v[index]) { v[bsr(x.dist ^ new_last.dist) + 1].emplace_back(x); }
            v[index].clear();
        }
        --sz;
        last = v[0].back();
        v[0].pop_back();
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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    cin >> a;

    radix_heap<void, int> pq;
    sort(a.begin(), a.begin() + k);
    rep(i, n) {
        if (i < k)
            pq.emplace(a[i]);
        else if (pq.top() <= a[i]) {
            pq.emplace(a[i]);
            pq.pop();
        }

        if (i >= k - 1)
            co(pq.top());
    }

    return 0;
}
