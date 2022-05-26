#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int (i) = 0; (i) < (n); (i)++)
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef long long ll;

int main(void){
	int n, k;
	cin >> n >> k;

	int h, ans;
	REP(i, n){
		cin >> h;
		if(h >= k) ans++;
	}

	cout << ans << endl;

	return 0;
}
