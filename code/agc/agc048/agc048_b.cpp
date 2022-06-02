#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ld = long double;
using P = pair<ll, ll>;
using Pld = pair<ld, ld>;
using Vec = vector<ll>;
using VecP = vector<P>;
using VecB = vector<bool>;
using VecC = vector<char>;
using VecD = vector<ld>;
using VecS = vector<string>;
template <class T>
using Vec2 = vector<vector<T>>;
#define REP(i, m, n) for(ll i = (m); i < (n); ++i)
#define REPN(i, m, n) for(ll i = (m); i <= (n); ++i)
#define REPR(i, m, n) for(ll i = (m)-1; i >= (n); --i)
#define REPNR(i, m, n) for(ll i = (m); i >= (n); --i)
#define rep(i, n) REP(i, 0, n)
#define repn(i, n) REPN(i, 1, n)
#define repr(i, n) REPR(i, n, 0)
#define repnr(i, n) REPNR(i, n, 1)
#define all(s) (s).begin(), (s).end()
#define pb push_back
#define fs first
#define sc second
template <class T1, class T2>
bool chmax(T1 &a, const T2 b){if(a < b){a = b; return true;} return false;}
template <class T1, class T2>
bool chmin(T1 &a, const T2 b){if(a > b){a = b; return true;} return false;}
ll pow2(const int n){return (1LL << n);}
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    for (const T &i : v) os << i << ' ';
    return os;
}
void co() { cout << '\n'; }
template <class Head, class... Tail>
void co(Head&& head, Tail&&... tail) {
    cout << head << ' ';
    co(forward<Tail>(tail)...);
}
void ce() { cerr << '\n'; }
template <class Head, class... Tail>
void ce(Head&& head, Tail&&... tail) {
    cerr << head << ' ';
    ce(forward<Tail>(tail)...);
}
void sonic(){ios::sync_with_stdio(false); cin.tie(0);}
void setp(const int n){cout << fixed << setprecision(n);}
constexpr int INF = 1000000001;
constexpr ll LINF = 1000000000000000001;
constexpr ll MOD = 1000000007;
constexpr ll MOD_N = 998244353;
constexpr ld EPS = 1e-11;
const double PI = acos(-1);

namespace kuhaku {

template <class T>
struct priority_queue {
    vector<T> data;
    int64_t _size;

    priority_queue() {
        data.assign(1 << 20, -LINF);
        _size = 0;
    }

    void push(T x) {
        int64_t it = ++_size;
        data[it] = x;
        while (it > 1 && data[it] > data[it / 2]) {
            swap(data[it], data[it / 2]);
            it >>= 1;
        }
    }

    T top() {
        return data[1];
    }

    void pop() {
        data[1] = data[_size];
        data[_size--] = -LINF;
        int64_t it = 1;
        while (data[it] < data[it * 2] || data[it] < data[it * 2 + 1]) {
            it <<= 1;
            if (data[it] < data[it + 1]) ++it;
            swap(data[it], data[it / 2]);
        }
    }

    const int64_t size() {
        return _size;
    }

    int64_t empty() {
        return _size == 0;
    }
};

}

int main(void) {
    ll n;
    cin >> n;
    Vec a(n), b(n);
    rep(i, n) cin >> a[i];
    rep(i, n) cin >> b[i];

    ll sum = accumulate(all(b), 0LL);
    rep(i, n) a[i] -= b[i];

    kuhaku::priority_queue<ll> pq1, pq2;
    rep(i, n) {
        if (i & 1) pq2.push(a[i]);
        else
            pq1.push(a[i]);
    }

    while(!pq1.empty()) {
        if (pq1.top() + pq2.top() < 0) break;
        sum += pq1.top() + pq2.top();
        pq1.pop();
        pq2.pop();
    }
    co(sum);

    return 0;
}