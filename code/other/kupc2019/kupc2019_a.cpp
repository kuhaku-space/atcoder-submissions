#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int (i) = 0; (i) < (n); (i)++)
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define mp make_pair
#define INF 2000000000
#define MOD 1000000007

typedef long long ll;
typedef pair<int, int> P;

int main(void){
	int n, x;
	cin >> n >> x;

	int a[n], max = 0;
	REP(i, n){
		cin >> a[i];
		max = MAX(max, a[i]);
	}

	int ans = 0;
	REP(i, n){
		if(a[i]+x >= max) ans++;
	}

	cout << ans << endl;

	return 0;
}
