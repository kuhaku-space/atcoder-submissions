#include <bits/stdc++.h>
using namespace std;

#define FOR(i, m, n) for(int (i) = (m); (i) < (n); (i)++)
#define rep(i, n) FOR(i, 0, n)
#define co(n) cout << (n) << endl
#define cosp(n) cout << (n) << ' '
#define all(s) (s).begin(), (s).end()
#define pb push_back
#define mp make_pair
#define fs first
#define sc second
typedef long long ll;
typedef pair<int, int> P;

const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;

int main(void){
	int a, b;
	cin >> a >> b;
	if(a < 10 && b < 10){
		co(a*b);
	}else{
		co(-1);
	}

	return 0;
}
