#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int (i) = 0; (i) < (n); (i)++)
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef long long ll;

int main(void){
	int n, k;
	cin >> n >> k;

	if(k > (n-1)*(n-2)/2){
		cout << -1 << endl;
		return 0;
	}

	int num = (n-1)*(n-2)/2-k+n-1;
	cout << num << endl;

	for(int i = 1; i < n; i++){
		cout << "1 " << i+1 << endl;
	}

	num -= n-1;
	for(int i = 1; i < n-1; i++){
		for(int j = i+1; j < n; j++){
			if(!num) break;
			cout << i+1 << ' ' << j+1 << endl;
			num--;
		}
		if(!num) break;
	}

	return 0;
}
