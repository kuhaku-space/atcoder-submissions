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
ll n, k;

ll permutation(ll n, ll k){
	ll res = 1;
	rep(i, k){
		res *= n-i;
		res %= MOD;
	}
	return res;
}

void dfs(ll node, ll p, ll &ans){
	if(!node) ans *= permutation(k-1, tree[node].size());
	else ans *= permutation(k-2, tree[node].size()-1);
	ans %= MOD;
	for(ll i : tree[node]) if(i != p) dfs(i, node, ans);
}

int main(void){
	cin >> n >> k;
	tree.resize(n);
	rep(i, n-1){
		ll a, b;
		cin >> a >> b;
		a--, b--;
		tree[a].pb(b);
		tree[b].pb(a);
	}

	ll ans = k;
	dfs(0, 0, ans);
	co(ans);

	return 0;
}
