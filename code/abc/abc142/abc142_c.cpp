#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int (i) = 0; (i) < (n); (i)++)
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef long long ll;

int main(void){
	int n;
	cin >> n;

	vector< pair<int, int> > a(n);

	REP(i, n){
		cin >> a[i].first;
		a[i].second = i+1;
	}

	sort(a.begin(), a.end());

	REP(i, n){
		cout << a[i].second << ' ';
	}
	cout << endl;

	return 0;
}
