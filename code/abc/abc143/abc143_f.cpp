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
template <typename T> bool chmax(T &a, const T& b){if(a < b){a = b; return true;} return false;}
template <typename T> bool chmin(T &a, const T& b){if(a > b){a = b; return true;} return false;}
const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;

int main(void){
	ll n;
	cin >> n;
	unordered_map<ll, ll> ump;
	rep(i, n){
		ll a;
		cin >> a;
		ump[a]++;
	}

	Vec cs1(n+1), cs2(n+1);
	for(P i : ump){
		cs1[i.sc]++;
	}

	repn(i, n){
		cs2[i] = i*cs1[i];
		cs1[i] += cs1[i-1];
		cs2[i] += cs2[i-1];
	}

	repn(i, n){
		ll l = 0, r = n+1;
		while(r-l > 1){
			ll mid = (l+r)/2;
			ll sum = cs2[mid]+mid*(ump.size()-cs1[mid]);
			if(sum/mid >= i) l = mid;
			else r = mid;
		}
		co(l);
	}

	return 0;
}
