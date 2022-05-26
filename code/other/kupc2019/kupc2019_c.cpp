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
	ll m, k;
	cin >> m >> k;

	ll ans = 0;
	ll sum = 0;
	while(sum < m){
		ans++;
		sum = (2*sum+1)*k+sum;
	}

	cout << ans << endl;

	return 0;
}
