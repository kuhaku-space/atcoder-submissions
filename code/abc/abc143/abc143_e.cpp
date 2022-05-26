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
typedef pair<ll, ll> P;
typedef pair<P, ll> PP;

const ll INF = 1e18;
const ll MOD = 1e9+7;
//const ll MOD 998244353;
const ll MAX_N = 305;

ll d[MAX_N][MAX_N] = {};
ll dd[MAX_N][MAX_N] = {};

int main(void){
	int n, m, l;
	scanf("%d%d%d", &n, &m, &l);

	rep(i, n) rep(j, n) d[i][j] = INF;
	rep(i, n) d[i][i] = 0;

	rep(i, m){
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		a--; b--;
		d[a][b] = c;
		d[b][a] = c;
	}

	rep(k, n) rep(i, n) rep(j, n) d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
	rep(i, n) rep(j, n){
		if(d[i][j] <= l) dd[i][j] = 1;
		else dd[i][j] = INF;
	}
	rep(i, n) dd[i][i] = 0;
	rep(k, n) rep(i, n) rep(j, n) dd[i][j] = min(dd[i][j], dd[i][k]+dd[k][j]);

	int q;
	cin >> q;
	rep(i, q){
		int s, t;
		scanf("%d%d", &s, &t);
		s--; t--;
		if(dd[s][t] != INF) printf("%d\n", dd[s][t]-1);
		else printf("-1\n");
	}

	return 0;
}
