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
#line 3 "a.cpp"

int main(void) {
    sonic();
    int n;
    cin >> n;
    n <<= 1;
    vector<int> a(n), b(n);
    cin >> a >> b;
    rep(i, n) {
        --a[i];
        b[i] = n - b[i];
    }
    vector<int> ans(n);

    rep(xyz, 10) {
        rep(_, 2) {
            int mini = Inf;
            priority_queue<int, vector<int>, greater<>> p, q, r;
            repr(i, n) {
                if (chmin(mini, a[i])) {
                    int x = a[i];
                    if (_ == 1) {
                        x = n - 1 - x;
                    }
                    if (ans[x] == 1) {
                        q.emplace(a[i]);
                    } else if (ans[x] == -1) {
                        r.emplace(a[i]);
                    } else if (q.size() == r.size() && p.empty()) {
                        r.emplace(a[i]);
                    } else {
                        p.emplace(a[i]);
                    }
                } else {
                    if (i & 1) {
                        co(-1);
                        return 0;
                    }
                    if (!q.empty() && q.top() < a[i]) {
                        co(-1);
                        return 0;
                    }
                    q.emplace(a[i]);
                    while (!p.empty() && p.top() < a[i]) {
                        r.emplace(p.top());
                        p.pop();
                    }

                    if (p.size() + q.size() == r.size()) {
                        while (!p.empty()) {
                            q.emplace(p.top());
                            p.pop();
                        }
                    }
                    if (p.size() + r.size() == q.size()) {
                        while (!p.empty()) {
                            r.emplace(p.top());
                            p.pop();
                        }
                    }
                }
            }
            if (_ == 0) {
                while (!q.empty()) {
                    ans[q.top()] = 1;
                    q.pop();
                }
                while (!r.empty()) {
                    ans[r.top()] = -1;
                    r.pop();
                }
            } else {
                while (!q.empty()) {
                    ans[n - 1 - q.top()] = 1;
                    q.pop();
                }
                while (!r.empty()) {
                    ans[n - 1 - r.top()] = -1;
                    r.pop();
                }
            }
            int s = 0;
            vector<int> v;
            rep(i, n) {
                int x = a[i];
                if (_ == 1)
                    x = n - 1 - x;
                if (s == 0) {
                    if (ans[x] == -1) {
                        co(-1);
                        return 0;
                    }
                    ans[x] = 1;
                    for (auto y : v) ans[y] = 1;
                    v.clear();
                }
                if (ans[x] == -1)
                    --s;
                else if (ans[x] == 1)
                    ++s;
                else {
                    ++s;
                    v.emplace_back(x);
                }
            }

            swap(a, b);
        }
    }

    string s;
    rep(i, n) {
        if (ans[i] == 1)
            s += '(';
        else if (ans[i] == -1)
            s += ')';
        else
            s += ')';
    }
    co(s);

    return 0;
}
