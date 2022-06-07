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
#line 2 "/home/kuhaku/atcoder/github/atcoder-lib/lib/math/prime_number.hpp"

/**
 * @brief 素数ライブラリ
 * 
 */
struct prime_number {
    static constexpr int sz = 1 << 22;
    bitset<sz> is_not_prime;
    vector<int> data;

    prime_number() { init(); }

    void init() {
        is_not_prime[0] = is_not_prime[1] = true;
        for (int i = 2; i < sz; ++i) {
            if (!is_not_prime[i]) {
                data.emplace_back(i);
                if ((int64_t)i * i >= sz) continue;
                if (i == 2) {
                    for (int j = i * i; j < sz; j += i) is_not_prime[j] = true;
                } else {
                    for (int j = i * i; j < sz; j += i << 1) is_not_prime[j] = true;
                }
            }
        }
    }

    constexpr bool is_prime(int64_t n) const {
        assert(n >= 0);
        if (n < sz) return !is_not_prime[n];
        for (auto i : data) {
            if ((int64_t)i * i > n) break;
            if (n % i == 0) return false;
        }
        return true;
    }

    vector<int> prime_numbers(int x) const {
        vector<int> res;
        for (auto i : data) {
            if (i > x) break;
            res.emplace_back(i);
        }
        return res;
    }

    /**
     * @brief 素因数分解
     *
     * @tparam T
     * @param x
     * @return vector<pair<T, int>>
     */
    template <class T>
    vector<pair<T, int>> prime_factorization(T x) const {
        if (x == 1) return vector<pair<T, int>>(1, {1, 1});
        vector<pair<T, int>> res;
        for (auto i : data) {
            int cnt = 0;
            for (; x % i == 0; x /= i) ++cnt;
            if (cnt) res.emplace_back(i, cnt);
            if ((int64_t)i * i > x) break;
        }
        if (x != 1) res.emplace_back(x, 1);
        return res;
    }

    /**
     * @brief 約数列挙
     *
     * @tparam T
     * @param x
     * @return vector<T>
     */
    template <class T>
    vector<T> divisors(T x) const {
        if (x == 1) return vector<T>(1, 1);
        auto v = this->prime_factorization(x);
        vector<T> res;
        res.emplace_back(1);
        for (auto p : v) {
            int n = res.size();
            res.resize(n * (p.second + 1));
            for (int i = 0; i < n * p.second; ++i) { res[n + i] = res[i] * p.first; }
            for (int i = 1; i <= p.second; ++i) {
                inplace_merge(res.begin(), res.begin() + n * i, res.begin() + n * (i + 1));
            }
        }
        return res;
    }

    // 因数分解列挙
    template <class T>
    vector<vector<T>> factorization(T x) const {
        vector<vector<T>> res;
        auto f = [&](auto self, vector<T> v, T a) -> void {
            if (a == 1) res.emplace_back(v);
            for (auto i : divisors(a)) {
                if (i == 1 || (!v.empty() && v.back() > i)) continue;
                v.emplace_back(i);
                self(self, v, a / i);
                v.pop_back();
            }
        };
        f(f, vector<T>(), x);
        return res;
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

prime_number pn;

int main(void) {
    sonic();
    int a, b, c, d;
    cin >> a >> b >> c >> d;

    FOR(i, a, b + 1) {
        bool flag = false;
        FOR(j, c, d + 1) {
            flag |= pn.is_prime(i + j);
        }
        if (!flag) {
            co("Takahashi");
            return 0;
        }
    }

    co("Aoki");
    return 0;
}
