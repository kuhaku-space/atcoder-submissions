#include <bits/stdc++.h>
using namespace std;

#define FOR(i, m, n) for(int (i) = (m); (i) < (n); (i)++)
#define FORN(i, m, n) for(int (i) = (m); (i) <= (n); (i)++)
#define FORR(i, m, n) for(int (i) = (m); (i) >= (n); (i)--)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FORN(i, 1, n)
#define repr(i, n) FORR(i, n, 0)
#define repnr(i, n) FORR(i, n, 1)
#define co(n) cout << (n) << endl
#define cosp(n) cout << (n) << ' '
#define setp(n) cout << fixed << setprecision(n);
#define all(s) (s).begin(), (s).end()
#define pb push_back
#define mp make_pair
#define fs first
#define sc second
typedef long long ll;
typedef pair<int, int> P;

const ll INF = 1e9+1;
const ll LINF = 1e18+1;
//const ll MOD = 1e9+7;
const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;
const int MAX_N = 1e5;

void solve(){
	int n;
	cin >> n;
	vector<list<int> > tree(n);

	rep(i, n-1){
		int a, b;
		cin >> a >> b;
		a--; b--;
		tree[a].pb(b);
		tree[b].pb(a);
	}

	vector<int> c(n);
	rep(i, n) cin >> c[i];
	sort(all(c));
	ll ans = 0;
	rep(i, n-1) ans += c[i];
	co(ans);

	vector<int> cost(n);
	queue<int> q;
	rep(i, n) if(tree[i].size() == 1) q.push(i);
	int cnt = 0;
	while(!q.empty()){
		int a = q.front(); q.pop();
		cost[a] = c[cnt++];
		if(!tree[a].empty()){
			int b = tree[a].front();
			tree[a].remove(b);
			tree[b].remove(a);
			if(tree[b].size() == 1) q.push(b);
		}
	}

	rep(i, n) cosp(cost[i]);
	cout << endl;
}

int main(void){
	solve();

	return 0;
}
