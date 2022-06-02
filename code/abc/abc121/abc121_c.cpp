#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using P = pair<ll, ll>;
using Vec = vector<ll>;
template <typename T>
using Vec1 = vector<T>;
template <typename T>
using Vec2 = vector<Vec1<T> >;
#define all(s) (s).begin(), (s).end()
#define pb push_back
#define fs first
#define sc second
template <typename T>
bool chmax(T &a, const T b){if(a < b){a = b; return true;} return false;}
template <typename T>
bool chmin(T &a, const T b){if(a > b){a = b; return true;} return false;}
template <typename T>
ll pow2(const T n){return (1LL << n);}
void sonic(){ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);}
void setp(const ll n){cout << fixed << setprecision(n);}
const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const ld PI = acos(-1);
const ld EPS = 1e-11;

int main(void){
	ll n, m;
	cin >> n >> m;
	Vec1<P> p(n);
	for(ll i = 0; i < n; ++i) cin >> p[i].fs >> p[i].sc;

	sort(all(p));

	ll c = 0, ans = 0, i = 0;
	while(c < m){
		if(c+p[i].sc < m){
			ans += p[i].fs*p[i].sc;
			c += p[i].sc;
		}else{
			ans += p[i].fs*(m-c);
			c += m-c;
		}
		i++;
	}
	cout << ans << endl;

	return 0;
}
