#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int (i) = 0; (i) < (n); (i)++)
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef long long ll;

int main(void){
	int n;
	cin >> n;

	string arr;

	vector< vector<int> > a(n, vector<int>(n));
	REP(i, n){
		cin >> arr;
		REP(j, n){
			a[i][j] = arr[j]-'0';
		}
	}

	vector< vector<int> > b(n, vector<int>(n));
	REP(i, n){
		cin >> arr;
		REP(j, n){
			b[i][j] = arr[j]-'0';
		}
	}

	vector< vector<int> > c(n, vector<int>(n, 1));

	REP(i, n){
		REP(j, n){
			if(!b[i][j]){
				REP(k, n){
					if(a[i][k]) c[k][j] = 0;
				}
			}
		}
	}

	REP(i, n){
		REP(j, n){
			if(b[i][j]){
				bool flg = true;
				REP(k, n){
					if(a[i][k] && c[k][j]){
						flg = false;
						break;
					}
				}
				if(flg){
					cout << -1 << endl;
					return 0;
				}
			}
		}
	}

	REP(i, n){
		REP(j, n){
			cout << c[i][j];
		}
		cout << endl;
	}

	return 0;
}
