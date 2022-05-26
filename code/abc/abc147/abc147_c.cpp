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
template <typename T> bool chmix(T &a, const T& b){if(a > b){a = b; return true;} return false;}
const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;

int main(void){
	ll n;
	cin >> n;

	Vec a(n);
	vector<VecP> t(n);
	rep(i, n){
		cin >> a[i];
		t[i].resize(a[i]);
		rep(j, a[i]){
			cin >> t[i][j].fs >> t[i][j].sc;
			t[i][j].fs--;
		}
	}

	ll ans = 0;
	rep(bit, (1 << n)){
		bitset<15> bits(bit);

		bool flg = true;
		rep(i, n){
			if(bits[i]){
				for(P j : t[i]){
					if(j.sc != bits[j.fs]){
							flg = false;
							break;
					}
				}
			}
			if(!flg) break;
		}
		if(flg) chmax(ans, (ll)bits.count());
	}
	co(ans);

	return 0;
}
