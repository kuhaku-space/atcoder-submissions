#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int (i) = 0; (i) < (n); (i)++)
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef long long ll;

int main(void){
	int n, k;
	cin >> n >> k;

	int sum = 0;
	vector<int> a(n);
	REP(i, n){
		cin >> a[i];
		sum += a[i];
	}

	priority_queue<int> que;
	for(int i = 1; i*i <= sum; i++){
		if(!(sum%i)){
			que.push(i);
			if(i != sum/i) que.push(sum/i);
		}
	}

	int ans = 0, mod;
	vector<int> r(n);
	while(1){
		if(!que.empty()){
			mod = que.top();
			que.pop();
		}else break;
		REP(i, n){
			r[i] = a[i]%mod;
		}
		sort(r.begin(), r.end());
		REP(i, n){
			if(!i) continue;
			r[i] += r[i-1];
		}
		REP(i, n){
			//cout << r[i] << "<=" << k << ' ' << (n-1-i)*mod-(r[n-1]-r[i]) << "<=" << k << endl;
			if(r[i] <= k && r[i] == (n-1-i)*mod-(r[n-1]-r[i])){
				ans = mod;
				break;
			}
		}
		if(ans) break;
	}

	cout << ans << endl;

	return 0;
}
