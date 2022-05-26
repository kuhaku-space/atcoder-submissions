#include <bits/stdc++.h>
using namespace std;
using ll = long long ;
using P = pair<ll, ll>;
using Vec = vector<ll>;
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

vector<Vec> tree;
Vec dist;

void print_vec(const Vec &vec){
	for(ll i : vec) cosp(i);
	cout << endl;
}

void print_tree(const vector<Vec> &tree){
	for(Vec vec : tree) print_vec(vec);
}

void dijkstra(ll node){
	priority_queue<P, vector<P>, greater<P> > que;
	que.push(mp(0, node));
	while(!que.empty()){
		P o = que.top(); que.pop();
		if(o.fs >= dist[o.sc]) continue;
		dist[o.sc] = o.fs;
		for(ll i : tree[o.sc]) que.push(mp(o.fs+1, i));
	}
}

int main(void){
	ll n, m;
	cin >> n >> m;
	tree.resize(n*3);
	dist.resize(n*3);
	fill(all(dist), LINF);
	rep(i, m){
		ll a, b;
		cin >> a >> b;
		a--, b--;
		tree[a*3].pb(b*3+1);
		tree[a*3+1].pb(b*3+2);
		tree[a*3+2].pb(b*3);
	}
	ll s, t;
	cin >> s >> t;
	s--, t--;
	dijkstra(s*3);
	if(dist[t*3] == LINF || dist[t*3]%3) co(-1);
	else co(dist[t*3]/3);

	return 0;
}
