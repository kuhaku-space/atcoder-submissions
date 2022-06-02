#include<bits/stdc++.h>
using namespace std;
#define arep(i,x,n) for(int i=int(x);i<(int)(n);i++)
#define rep(i,n) for(long long i = 0;i < n;++i)
#define pi 3.141592653589793
#define eps 0.001
#define INF 1e9+7  
using ll = long long;
using P = pair<int, int>;
using lP = pair<ll, ll>;
using fP = pair<long double, long double>;
ll const mod = 998244353;
const ll MAX = 300000;

class UnionFind {
public:
    vector <ll> par; // 各元の親を表す配列
    vector <ll> siz; // 素集合のサイズを表す配列(1 で初期化)

    // Constructor
    UnionFind(ll sz_) : par(sz_+1), siz(sz_+1, 1LL) {
        for (ll i = 0; i < sz_+1; ++i) par[i] = i; // 初期では親は自分自身
    }
    void init(ll sz_) {
        par.resize(sz_);
        siz.assign(sz_, 1LL);  // resize だとなぜか初期化されなかった
        for (ll i = 0; i < sz_; ++i) par[i] = i; // 初期では親は自分自身
    }

    // Member Function
    // Find
    ll root(ll x) { // 根の検索
        while (par[x] != x) {
            x = par[x] = par[par[x]]; // x の親の親を x の親とする
        }
        return x;
    }

    // Union(Unite, Merge)
    bool merge(ll x, ll y) {
        x = root(x);
        y = root(y);
        if (x == y) return false;
        // merge technique（データ構造をマージするテク．小を大にくっつける）
        //if (siz[x] < siz[y]) swap(x, y);
        siz[x] += siz[y];
        par[y] = x;
        return true;
    }

    bool issame(ll x, ll y) { // 連結判定
        return root(x) == root(y);
    }

    ll size(ll x) { // 素集合のサイズ
        return siz[root(x)];
    }
};


bool cmp(pair<long double, P>a, pair<long double, P> b) {
    return a.first > b.first;
}


int main() {
    int n, m;
    cin >> n >> m;
    vector<P>ab(m);
    vector<int>c(m), t(m);
    UnionFind uf(n);
    rep(i, m) {
        cin >> ab[i].first >> ab[i].second;
        cin >> c[i] >> t[i];
    }
    auto check = [&](long double k) {
        vector<pair<long double, P>>d(m);
        rep(i, m) {
            d[i].first =(long double) t[i] * k - c[i];
            d[i].second = ab[i];
        }
        sort(d.begin(), d.end(), cmp);
        
        uf.init(n+1);
        long double sum = 0;
        rep(i, m) {
            
            ll a = d[i].second.first;
            ll b = d[i].second.second;
            if (uf.merge(a, b)||d[i].first>=0) {
                sum += d[i].first;
            }
        }
        return sum >= 0;
    };
    double l = 0, r = 1000000;
    rep(i, 100) {
        long double now = (l + r) / 2;
        if (check(now))r = now;
        else l = now;
    }

    printf("%.4f\n", r);
    return 0;
}
