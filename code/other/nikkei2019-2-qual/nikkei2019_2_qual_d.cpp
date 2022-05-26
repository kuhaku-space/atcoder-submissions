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
typedef pair<ll, ll> P;

struct Edge{
	int to;
	int cost;
};

const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;
const int MAX_N = 1e5;
vector<vector<Edge> > tree;
ll dist[MAX_N] = {};

int main(void){
	int n, m;
	cin >> n >> m;
	tree.resize(n);
	fill_n(dist, n, LINF);
	repn(i, n-1){
		Edge e = {i-1, 0};
		tree[i].pb(e);
	}

	rep(i, m){
		int l, r, c;
		cin >> l >> r >> c;
		l--; r--;
		Edge e = {r, c};
		tree[l].pb(e);
	}

	priority_queue<P, vector<P>, greater<P> > q;
	q.push(mp(0, 0));
	while(!q.empty()){
		P p = q.top(); q.pop();
		if(p.fs >= dist[p.sc]) continue;
		dist[p.sc] = p.fs;
		rep(i, tree[p.sc].size()){
			Edge e = tree[p.sc][i];
			q.push(mp(p.fs+e.cost, e.to));
		}
	}

	if(dist[n-1] == LINF) co(-1);
	else co(dist[n-1]);

	return 0;
}
