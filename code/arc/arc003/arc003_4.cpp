#include <assert.h>
#include <math.h>

#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;
#define REP(i, m, n) for (int i = (int)(m); i < (int)(n); ++i)
#define rep(i, n) REP(i, 0, n)
using ll = long long;
constexpr int inf = 1e9 + 7;
constexpr ll longinf = 1LL << 60;
constexpr ll mod = 1e9 + 7;

inline unsigned xor128() {
    static unsigned x = 123456789;
    static unsigned y = 362436069;
    static unsigned z = 521288629;
    static unsigned w = 88675123;
    unsigned t;
    t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> ng(n, vector<int>(n));
    rep(i, m) {
        int x, y;
        cin >> x >> y;
        ng[x][y] = ng[y][x] = 1;
    }
    vector<pair<int, int>> es;
    rep(i, n) rep(j, i) {
        es.emplace_back(i, j);
    }
    int sz = es.size();
    int T = 245000;
    int cnt = 0;
    int a[n + 1];
    rep(_, T) {
        rep(i, n) a[i] = i;
        rep(__, k) {
            int i = xor128() % sz;
            swap(a[es[i].first], a[es[i].second]);
        }
        bool ok = true;
        a[n] = a[0];
        for (int i = 0; i < n && ok; ++i)
            ok &= !ng[a[i]][a[i + 1]];
        cnt += ok;
    }
    cout << 1.0 * cnt / T << endl;
    return 0;
}
