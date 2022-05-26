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
typedef pair<double, ll> Pdl;
typedef vector<ll> Vec;

const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;
const ll MAX_L = 40075017;

struct Node{
	ll x;
	ll v;
	ll d;
};

bool asc(const Node &a, const Node &b){
	return a.x < b.x;
}

int main(void){
	ll n, l;
	cin >> n >> l;
	vector<vector<Pdl> > tree(n+2);
	Vec dist(n+2);
	vector<Node> node(n+1);
	node[0].x = 0;
	cin >> node[0].v >> node[0].d;
	repn(i, n) cin >> node[i].x >> node[i].v >> node[i].d;
	sort(all(node), asc);

	dist[0] = 0;
	repn(i, n) dist[i] = node[i].x;
	dist[n+1] = l;

	rep(i, n+1){
		FORN(j, i+1, n+1){
			if(dist[j]-dist[i] <= node[i].d) tree[i].pb(mp((double)(dist[j]-dist[i])/node[i].v, j));
			else break;
		}
	}

	vector<double> ans(n+2, INF);
	priority_queue<Pdl, vector<Pdl>, greater<Pdl> > que;
	que.push(mp(0.0, 0));
	while(!que.empty()){
		Pdl out = que.top(); que.pop();
		if(out.fs >= ans[out.sc]) continue;
		ans[out.sc] = out.fs;
		for(Pdl i : tree[out.sc]){
			que.push(mp(out.fs+i.fs, i.sc));
		}
	}

	setp(20);
	if(ans[n+1] == INF) puts("impossible");
	else co(ans[n+1]);

	return 0;
}
