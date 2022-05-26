#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int (i) = 0; (i) < (n); (i)++)

int main(void){
	int n, k;
	cin >> n >> k;

	vector<int> p(n);
	REP(i, n){
		cin >> p[i];
	}

	if(n == k){
		cout << 1 << endl;
		return 0;
	}

	int ans = n-k+1;
	int cnt = 0, sum = 0;
	REP(i, n-1){
		if(p[i] < p[i+1]) cnt++;
		else cnt = 0;
		if(cnt == k-1) sum++;
	}
	if(sum > 1) ans -= sum-1;

	set<int> st;
	REP(i, n){
		st.insert(p[i]);
		if(i >= k){
			if(p[i] == *st.rbegin() && p[i-k] == *st.begin()) ans--;
			st.erase(p[i-k]);
		}
	}

	cout << ans << endl;

	return 0;
}
