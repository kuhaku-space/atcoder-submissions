/*
confirm 0LL and 1LL
confirm cornercases such as 0
confirm times of cin < 10^6
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using P = pair<ll, ll>;
using Pld = pair<ld, ld>;
using Vec = vector<ll>;
using VecP = vector<P>;
using VecB = vector<bool>;
using VecC = vector<char>;
using VecD = vector<ld>;
using VecS = vector<string>;
using Graph = vector<VecP>;
template <typename T>
using Vec1 = vector<T>;
template <typename T>
using Vec2 = vector<Vec1<T> >;
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
#define fs first
#define sc second
template <typename T>
bool chmax(T &a, const T b){if(a < b){a = b; return true;} return false;}
template <typename T>
bool chmin(T &a, const T b){if(a > b){a = b; return true;} return false;}
template <typename T>
ll pow2(const T n){return (1LL << n);}
template <typename T>
void cosp(const T n){cout << n << ' ';}
template <typename T>
void co(const T n){cout << n << '\n';}
template <typename T1, typename T2>
void co(pair<T1, T2> p){cout << p.fs << ' ' << p.sc << '\n';}
template <typename T>
void co(const Vec1<T> &v){for(T i : v) cosp(i); cout << '\n';}
template <typename T>
void co(initializer_list<T> v){for(T i : v) cosp(i); cout << '\n';}
template <typename T>
void ce(const T n){cerr << n << endl;}
void sonic(){ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);}
void setp(const ll n){cout << fixed << setprecision(n);}
const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const ld PI = acos(-1);
const ld EPS = 1e-11;

void print(Vec v){
	for(ll i : v){
		if(i) cout << 'S';
		else cout << 'W';
	}
	cout << endl;
}

bool check(ll t, Vec v, string s){
	ll n = v.size();
	ll f = t+1, b = t-1;
	f += n; f %= n;
	b += n; b %= n;

	if(v[t] == 1){
		if(s[t] == 'o' && v[f] == v[b]) return true;
		if(s[t] == 'x' && v[f] != v[b]) return true;
	}else{
		if(s[t] == 'o' && v[f] != v[b]) return true;
		if(s[t] == 'x' && v[f] == v[b]) return true;
	}
	return false;
}

int main(void){
	ll n;
	cin >> n;
	string s;
	cin >> s;

	//hitsuji:1,okami:0
	Vec a(n);
	rep(i, 4){
		ll x = i%2, y = i/2;
		a[0] = x, a[1] = y;
		REP(j, 2, n){
			if(a[j-1] == 1){
				if(s[j-1] == 'o') a[j] = a[j-2];
				else a[j] = !a[j-2];
			}else{
				if(s[j-1] == 'x') a[j] = a[j-2];
				else a[j] = !a[j-2];
			}
		}

		if(check(0, a, s) && check(n-1, a, s)){
			print(a);
			return 0;
		}
	}

	co(-1);
	return 0;
}
