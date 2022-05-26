/*
confirm 0LL and 1LL
confirm cornercases such as 0
confirm times of cin < 10^6
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using P = pair<ll, ll>;
using Vec = vector<ll>;
using VecP = vector<P>;
using VecB = vector<bool>;
using VecC = vector<char>;
using VecVec = vector<Vec>;
#define REP(i, m, n) for(ll (i) = (m); (i) < (n); ++(i))
#define REPN(i, m, n) for(ll (i) = (m); (i) <= (n); ++(i))
#define REPR(i, m, n) for(ll (i) = (m)-1; (i) >= (n); --(i))
#define REPNR(i, m, n) for(ll (i) = (m); (i) >= (n); --(i))
#define rep(i, n) REP(i, 0, n)
#define repn(i, n) REPN(i, 1, n)
#define repr(i, n) REPR(i, n, 0)
#define repnr(i, n) REPNR(i, n, 1)
#define all(s) (s).begin(), (s).end()
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define fs first
#define sc second
template <typename T>
bool chmax(T &a, const T& b){if(a < b){a = b; return true;} return false;}
template <typename T>
bool chmin(T &a, const T& b){if(a > b){a = b; return true;} return false;}
template <typename T>
void co(const T n){cout << n << endl;}
template <typename T>
void cosp(const T n){cout << n << ' ';}
void coVec(const Vec &v){for(ll i : v) co(i);}
void sonic(){ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);}
void setp(ll n){cout << fixed << setprecision(n);}
const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;

int main(void){
	ll n, x;
	cin >> n >> x;
	if(n == 1){
		puts("Yes");
		co(1);
	}else if(n == 2){
		if(x == 2){
			puts("Yes");
			coVec({1, 2, 3});
		}else{
			puts("No");
		}
	}else{
		if(x == 1 || x == n*2-1) puts("No");
		else{
			puts("Yes");
			unordered_set<ll> ust;
			Vec ans(2*n-1);
			ans[n-2] = 1, ans[n-1] = x, ans[n] = n*2-1;
			ust.insert({1, x, n*2-1});
			if(x != 2){
				ans[n+1] = 2;
				ust.insert(2);
			}else{
				ans[n-3] = n*2-2;
				ust.insert(n*2-2);
			}
			ll cnt = 1;
			rep(i, n*2-1){
				while(true){
					if(ust.find(cnt) == ust.end()) break;
					cnt++;
				}
				if(!ans[i]) ans[i] = cnt++;
			}
			coVec(ans);
		}
	}

	return 0;
}
