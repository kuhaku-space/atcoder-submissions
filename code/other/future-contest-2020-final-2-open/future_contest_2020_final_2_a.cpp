#include <bits/stdc++.h>
using namespace std;
using ll = long long ;
using P = pair<ll, ll>;
using Vec = vector<ll>;
using VecP = vector<P>;
#define REP(i, m, n) for(ll (i) = (m); (i) < (n); ++(i))
#define REPN(i, m, n) for(ll (i) = (m); (i) <= (n); ++(i))
#define REPR(i, m, n) for(ll (i) = (m); (i) >= (n); --(i))
#define rep(i, n) REP(i, 0, n)
#define repn(i, n) REPN(i, 1, n)
#define repr(i, n) REPR(i, n, 0)
#define repnr(i, n) REPR(i, n, 1)
#define co(n) cout << (n) << endl
#define cosp(n) cout << (n) << ' '
#define setp(n) cout << fixed << setprecision(n);
#define all(s) (s).begin(), (s).end()
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define fs first
#define sc second

const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;
const ll MAX_K = 100;

struct Ver{
	ll x;
	ll y;
	ll c;
};

struct Query{
	ll id;
	ll k;
	Vec p;
};

const ll N = 1000;
const ll S = 1000;
vector<Ver> v(N+1);
vector<Query> q(S);
double dist[N+1][N+1] = {};
vector<Vec> isEdge(N+1);
vector<Vec> tree(N+1);
vector<bool> isUsed(N+1, false);
vector<Query> ans(S);
ll root = 0;
ll M = 0;

bool desc(const ll &a, const ll &b){
	return isEdge[a].size() > isEdge[b].size();
}

bool descQueryOfK(const Query &a, const Query &b){
	if(a.k == b.k) return a.id < b.id;
	else return a.k > b.k;
}

bool ascQueryOfId(const Query &a, const Query &b){
	return a.id < b.id;
}

void input(){
	ll n, s;
	cin >> n >> s;
	repn(i, N) cin >> v[i].x >> v[i].y >> v[i].c;
	rep(i, S){
		q[i].id = i;
		ans[i].id = i;
		cin >> q[i].k;
		ans[i].k = q[i].k;
		q[i].p.resize(q[i].k);
		ans[i].p.resize(q[i].k);
		REP(j, 1, q[i].k) cin >> q[i].p[j];
	}
}

void preprocessing(){
	repn(i, N) repn(j, N) dist[i][j] = sqrt(pow(v[i].x-v[j].x, 2)+pow(v[i].y-v[j].y, 2));
	repn(i, N){
		repn(j, N){
			if(i == j) continue;
			if(dist[i][j] < v[i].c+v[j].c) isEdge[i].pb(j);
		}
	}
	repn(i, N) sort(all(isEdge[i]), desc);

	ll edgeMax = 0;
	repn(i, N){
		if(isEdge[i].size() > edgeMax){
			root = i;
			edgeMax = isEdge[i].size();
		}
	}
}

void query(ll s){
	sort(all(q), descQueryOfK);
	sort(all(ans), descQueryOfK);
	rep(i, q[s].k){
		if(!i){
			ans[s].p[i] = root;
			continue;
		}
		ll par = ans[s].p[q[s].p[i]-1];
		for(ll j : isEdge[par]){
			if(find(all(ans[s].p), j) == ans[s].p.end()){
				if(find(all(tree[par]), j) != tree[par].end()){
					ans[s].p[i] = j;
					break;
				}else if(!isUsed[j]){
					ans[s].p[i] = j;
					tree[par].pb(j);
					tree[j].pb(par);
					M++;
					isUsed[j] = true;
					break;
				}
			}
		}
	}
	
	rep(i, q[s].k){
		if(ans[s].p[i]) continue;
		repn(n, N){
			if(find(all(ans[s].p), n) == ans[s].p.end()){
				ans[s].p[i] = n;
				break;
			}
		}
	}
	
	sort(all(q), ascQueryOfId);
	sort(all(ans), ascQueryOfId);
}

void debug(){
	puts("**************************");
	repn(i, N){
		cout << i << ":" << isEdge[i].size() << ' ';
		if(!(i%20)) cout << endl;
	}
	puts("**************************");

	repn(i, N){
		cosp(i); cosp(':');
		for(ll j : isEdge[i]) cosp(j);
		cout << endl;
	}

}

void output(){
	co(M);
	repn(i, N){
		for(ll j : tree[i]){
			if(i < j){
				cosp(i); co(j);
			}
		}
	}

	rep(i, S){
		rep(j, ans[i].k) cosp(ans[i].p[j]);
		cout << endl;
	}
}

int main(void){
	input();
	preprocessing();
	//debug();
	rep(i, S) query(i);
	output();

	return 0;
}
