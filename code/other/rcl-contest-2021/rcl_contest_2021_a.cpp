#ifndef LOCAL
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#endif

#include <sys/time.h>

#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;
using ll = int64_t;
#define FOR(i, m, n) for (int i = (m); i < (n); ++i)
#define rep(i, n) FOR(i, 0, n)
template <class T, class U>
bool chmax(T &a, const U &b) {
    return a < b ? a = b, true : false;
}
template <class T, class U>
bool chmin(T &a, const U &b) {
    return b < a ? a = b, true : false;
}
constexpr int INF = 1000000003;
constexpr ll LINF = 1000000000000000003;

constexpr int N = 300;
constexpr int M = 1000;
constexpr int K = 100000000;
array<int, N> A;

int main(void) {
    int tmp;
    cin >> tmp >> tmp >> tmp;
    rep(i, N) cin >> A[i];

    vector<int> idx(N);
    // iota(idx.begin(), idx.end(), 0);
    vector<pair<int, int>> ans;
    rep(_, M) {
        vector<int> a, b;
        rep(i, N) {
            if (A[i] < K - A[i])
                a.emplace_back(i);
            else
                b.emplace_back(i);
        }
        // cerr << _ << ' ' << a.size() << ' ' << b.size() << endl;
        sort(a.begin(), a.end(), [&](int x, int y) {
            return A[x] > A[y];
        });
        sort(b.begin(), b.end(), [&](int x, int y) {
            return A[x] < A[y];
        });

        int cnt = 0;
        rep(i, N) {
            if (A[i] > K - A[i])
                cnt += (K - A[i] - 1) / A[a[0]] + 1;
        }

        if (M - _ <= cnt + 1) {
            // cerr << M - _ << ' ' << cnt << ' ' << b.size() << endl;
            if (b.size() == 0)
                continue;
            int x = b[0];
            int m = INF;
            int y = a[0];
            for (auto i : a) {
                if (A[x] + A[i] >= K && chmin(m, A[x] + A[i] - K))
                    y = i;
            }
            ans.emplace_back(x, y);
            A[x] += A[y];
            A[x] %= K;
        } else {
            int x = a[0];
            int y = b[0];
            if (A[x] <= (K - A[y]) * 1.001) {
                swap(x, y);
            }
            ans.emplace_back(x, y);
            A[x] += A[y];
            A[x] %= K;
        }
    }

    for (auto p : ans) {
        cout << p.first << ' ' << p.second << endl;
    }
    // rep(i, N) cerr << A[i] << ' ';
    // cerr << endl;

    return 0;
}