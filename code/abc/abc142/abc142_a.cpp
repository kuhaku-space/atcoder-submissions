#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int (i) = 0; (i) < (n); (i)++)
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef long long ll;

int main(void){
	int n;
	cin >> n;

	int m = (n+1)/2;
	cout << fixed;
	cout << setprecision(7) << (double)m/n << endl;

	return 0;
}
