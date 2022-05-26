#include <bits/stdc++.h>
using namespace std;
using ll = long long ;
using P = pair<ll, ll>;
using Vec = vector<ll>;
using VecP = vector<P>;
#define FOR(i, m, n) for(ll (i) = (m); (i) < (n); (i)++)
#define FORN(i, m, n) for(ll (i) = (m); (i) <= (n); (i)++)
#define FORR(i, m, n) for(ll (i) = (m); (i) >= (n); (i)--)
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

const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;

vector<VecP> tree;
Vec dist;

void dijkstra(ll node){
	priority_queue<P, vector<P>, greater<P> > que;
	que.push(mp(0, node));
	while(!que.empty()){
		P o = que.top(); que.pop();
		if(o.fs >= dist[o.sc]) continue;
		dist[o.sc] = o.fs;
		for(P i : tree[o.sc]) que.push(mp(o.fs+i.fs, i.sc));
	}
}

int main(void){
	ll n;
	cin >> n;
	tree.resize(n);
	dist.resize(n);
	fill(all(dist), LINF);
	rep(i, n-1){
		ll a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		tree[a].pb(mp(c, b));
		tree[b].pb(mp(c, a));
	}

	ll q, k;
	cin >> q >> k;
	k--;
	dijkstra(k);

	rep(i, q){
		ll x, y;
		cin >> x >> y;
		x--, y--;
		co(dist[x]+dist[y]);
	}

	return 0;
}
