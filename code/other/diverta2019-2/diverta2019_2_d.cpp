#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(ll (i) = 0; (i) < (n); (i)++)
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef long long ll;

int main(void){
	int n;
	cin >> n;

	vector<int> g(2), s(2), b(2);
	REP(i, 2){
		cin >> g[i] >> s[i] >> b[i];
	}

	int dif_g = g[1]-g[0], dif_s = s[1]-s[0], dif_b = b[1]-b[0];

	vector<ll> dp(n+1, n);
	REP(i, n){
		if(dp[i] > n || !i){
			if(i+g[0] <= n && dif_g > 0) dp[i+g[0]] = MAX(dp[i+g[0]], dp[i]+dif_g);
			if(i+s[0] <= n && dif_s > 0) dp[i+s[0]] = MAX(dp[i+s[0]], dp[i]+dif_s);
			if(i+b[0] <= n && dif_b > 0) dp[i+b[0]] = MAX(dp[i+b[0]], dp[i]+dif_b);
		}
	}

	ll max = n;
	REP(i, n+1){
		if(dp[i] > max){
			max = dp[i];
		}
	}

	dp.resize(max+1);
	dp.assign(max+1, max);
	//REP(i, max+1) cout << dp[i] << ' '; cout << endl;
	REP(i, max){
		if(dp[i] > max || !i){
			if(i+g[1] <= max && dif_g < 0) dp[i+g[1]] = MAX(dp[i+g[1]], dp[i]-dif_g);
			if(i+s[1] <= max && dif_s < 0) dp[i+s[1]] = MAX(dp[i+s[1]], dp[i]-dif_s);
			if(i+b[1] <= max && dif_b < 0) dp[i+b[1]] = MAX(dp[i+b[1]], dp[i]-dif_b);
		}
	}

	ll ans = max;
	REP(i, max+1){
		if(dp[i] > ans){
			ans = dp[i];
		}
	}

	cout << ans << endl;

	return 0;
}
