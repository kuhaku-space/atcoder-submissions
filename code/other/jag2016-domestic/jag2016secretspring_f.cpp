#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Vec = vector<ll>;
#define REP(i, m, n) for(ll i = (m); i < (n); ++i)
#define rep(i, n) REP(i, 0, n)
template <class T1, class T2>
bool chmax(T1 &a, const T2 b){if(a < b){a = b; return true;} return false;}
template <class T1, class T2>
bool chmin(T1 &a, const T2 b){if(a > b){a = b; return true;} return false;}
constexpr ll LINF = 1e18L+1;
constexpr ll MOD = 1e9+7;

ll h, w, n;
ll sum[2005][2005] = {};
ll a[2005][2005] = {};

ll area(ll u, ll d, ll l, ll r){
    return sum[d][r] - sum[d][l] - sum[u][r] + sum[u][l];
}

ll f(ll u, ll d, ll l, ll r, ll p){
    if (p == 1) return area(u, d, l, r);

    ll res = 0;
    for (int i = u + 1; i < d; ++i){
        for (int j = 1; j <= p - 1; ++j)
            chmax(res, min(f(u, i, l, r, j), f(i, d, l, r, p - j)));
    }
    for(int i = l + 1; i < r; ++i){
        for (int j = 1; j <= p - 1; ++j)
            chmax(res, min(f(u, d, l, i, j), f(u, d, i, r, p - j)));
    }
    return res;
}

ll g(ll d, ll r){
    ll res = 0;
    for(int x = 1; x <= h; ++x){
        for (int y = 1; y <= w; ++y){
            if (x > d && y > r) break;
            ll t = sum[d][r];
            chmin(t, area(0, x, r, w));
            chmin(t, area(d, h, 0, y));
            if (t < res) continue;
            if(x < d && y < r){
                ll tmp = max(area(x, h, r, w), area(d, h, y, w));
                chmin(t, tmp);
            }else{
                chmin(t, area(x, h, y, w));
            }
            chmax(res, t);
            if (res == sum[d][r]) return res;
        }
    }
    return res;
}

int main(void) {
    cin >> h >> w >> n;
    rep(i, h) rep(j, w) cin >> a[i][j];
    rep(i, h) rep(j, w) sum[i + 1][j + 1] = sum[i + 1][j] + a[i][j];
    rep(i, h) rep(j, w) sum[i + 1][j + 1] += sum[i][j + 1];

    ll ans = 0;
    chmax(ans, f(0, h, 0, w, n));
    if(n == 4){
        for (int i = 1; i < h; ++i){
            for (int j = 1; j < w; ++j){
                chmax(ans, g(i, j));
            }
        }
    }
    cout << ans << endl;

    return 0;
}
