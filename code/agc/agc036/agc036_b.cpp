#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int (i) = 0; (i) < (n); (i)++)
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef long long ll;

int main(void){
	ll n, k;
	cin >> n >> k;

	vector< vector<int> > v(200001);
	vector<int> a(n);

	REP(i, n){
		cin >> a[i];
		v[a[i]].push_back(i);
	}

	ll pos = 0, cnt = 1;
	vector<int> ans;
	while(1){
		//cout << pos << ' ' << cnt << endl;
		int num = a[pos];
		bool flg = true;
		REP(i, v[num].size()){
			if(v[num][i] > pos){
				pos = v[num][i]+1;
				flg = false;
				break;
			}
		}
		if(flg){
			if(cnt < k){
				pos = v[num][0]+1;
				cnt++;
			}else{
				ans.push_back(a[pos]);
				pos++;
			}
		}

		if(pos == n) cnt *= k/cnt;
		if(pos == n && cnt == k) break;
		if(pos == n){
			pos = 0;
			cnt++;
		}
	}

	REP(i, ans.size()){
		cout << ans[i] << ' ';
	}
	cout << endl;

	return 0;
}
