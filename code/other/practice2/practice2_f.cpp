#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using ll = int64_t;
using ld = long double;
#define FOR(i, m, n) for (int i = (m); i < int(n); ++i)
#define FORR(i, m, n) for (int i = (m)-1; i >= int(n); --i)
#define FORL(i, m, n) for (int64_t i = (m); i < int64_t(n); ++i)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FOR(i, 1, n + 1)
#define repr(i, n) FORR(i, n, 0)
#define repnr(i, n) FORR(i, n + 1, 1)
#define all(s) (s).begin(), (s).end()
template <class T, class U>
bool chmax(T &a, const U &b) {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U &b) {
    return (T)b < a ? a = (T)b, true : false;
}
template <class T, class U>
std::istream &operator>>(std::istream &is, std::pair<T, U> &p) {
    is >> p.first >> p.second;
    return is;
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
    if constexpr (sizeof...(tail) == 0)
        std::cout << head << '\n';
    else
        std::cout << head << ' ', co(forward<Tail>(tail)...);
}
void sonic() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

using Mint = modint998244353;

int main(void) {
    sonic();
    int n, m;
    cin >> n >> m;
    vector<Mint> a(n), b(m);
    rep(i, n) {
        ll t;
        cin >> t;
        a[i] = t;
    }
    rep(i, m) {
        ll t;
        cin >> t;
        b[i] = t;
    }

    auto ans = convolution(a, b);
    for (auto i : ans) cout << i.val() << ' ';
    cout << endl;

    return 0;
}