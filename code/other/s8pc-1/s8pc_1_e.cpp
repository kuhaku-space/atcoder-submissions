#line 1 "a.cpp"
#include <bits/stdc++.h>
using namespace std;
using Graph = vector<vector<int>>;
#define INF (long long)1e+10
#define rep(i, x) for (int i = 0; i < (x); i++)

int main() {
    long long n, q;
    cin >> n >> q;
    vector<long long> a(n, 0);
    vector<long long> c(q + 2, 1);
    rep (i, n) cin >> a[i];
    rep (i, q) cin >> c[i + 1];
    long long k = 1000000007;
    vector<long long> b(n, 0);

    rep (i, n - 1) {
        long long x = a[i];
        long long y = a[i + 1];
        long long x2 = 1;
        while (y > 0) {
            if (y % 2 == 1) {
                x2 *= x;
                x2 %= k;
            }
            y /= 2;
            x *= x;
            x %= k;
        }
        b[i + 1] = x2;
    }
    vector<long long> b2(n + 1, 0);  // i番目までの距離

    rep (i, n - 1) {
        b2[i + 2] = b2[i + 1] + b[i + 1];
        b2[i + 2] %= k;
    }
    long long ans = 0;
    long long now = 0;

    rep (i, q + 1) {
        if (c[i] < c[i + 1])
            ans += b2[c[i + 1]] - b2[c[i]];
        else
            ans += b2[c[i]] - b2[c[i + 1]];
        ans += k;
        ans %= k;
    }
    cout << ans << endl;
}
