#include <bits/stdc++.h>
using namespace std;
using ll = long long ;
using P = pair<ll, ll>;
using Vec = vector<ll>;
using VecP = vector<P>;
using VecB = vector<bool>;
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
	ll a, b, c, d, e, f;
	cin >> a >> b >> c >> d >> e >> f;

	vector<bool> water(31, false);
	water[0] = true;
	repn(i, f/100){
		if(i >= a && water[i-a]) water[i] = true;
		else if (i >= b && water[i-b]) water[i] = true;
	}

	vector<bool> suger(f+1);
	suger[0] = true;
	repn(i, f){
		if(i >= c && suger[i-c]) suger[i] = true;
		else if(i >= d && suger[i-d]) suger[i] = true;
	}

	ll ansW = 0, ansS = 0;
	double ansP = 0;
	repn(i, f/100){
		if(water[i]){
			ll s = i*e;
			repr(j, s){
				if(suger[j] && i*100+j <= f){
					if((double)j/(i*100+j) >= ansP){
						ansW = i, ansS = j, ansP = (double)j/(i*100+j);
					}
					break;
				}
			}
		}
	}

	cosp(ansW*100+ansS); co(ansS);

	return 0;
}
