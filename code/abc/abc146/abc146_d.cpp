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
typedef vector<ll> Vec;

const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;

struct Edge{
	ll no;
	ll to;
};

ll maxi = 0;
vector<vector<Edge> > tree;
Vec edges;

void dfs(ll node, ll color){
	for(Edge e : tree[node]){
		if(!edges[e.no]){
			color = color%maxi+1;
			edges[e.no] = color;
			dfs(e.to, color);
		}
	}
}

int main(void){
	ll n;
	cin >> n;
	edges.resize(n-1);
	tree.resize(n);
	
	rep(i, n-1){
		ll a, b;
		cin >> a >> b;
		a--; b--;
		tree[a].pb(Edge {i, b});
		tree[b].pb(Edge {i, a});
	}
	rep(i, n){
		maxi = max(maxi, (ll)tree[i].size());
	}

	dfs(0LL, 0LL);
	
	co(maxi);
	rep(i, n-1) co(edges[i]);

	return 0;
}
