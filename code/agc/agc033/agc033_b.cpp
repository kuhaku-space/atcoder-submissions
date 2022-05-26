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
const ll MAX_H = 2e5;
const ll MAX_W = 2e5;

int main(void){
	ll h, w, n;
	cin >> h >> w >> n;
	P p;
	cin >> p.fs >> p.sc;
	string s, t;
	cin >> s >> t;
    ll u = 0, d = h+1;
	repr(i, n-1){
		if(t[i] == 'U') d = min(h+1, d+1);
		else if(t[i] == 'D') u = max(0LL, u-1);
		if(s[i] == 'U') u++;
		else if(s[i] == 'D') d--;
        if(u == h || d == 1){
            puts("NO");
            return 0;
        }
	}
    if(u >= p.fs || d <= p.fs){
        puts("NO");
        return 0;
    }

    ll l = 0, r = w+1;
	repr(i, n-1){
		if(t[i] == 'L') r = min(w+1, r+1);
		else if(t[i] == 'R') l = max(0LL, l-1);
		if(s[i] == 'L') l++;
		else if(s[i] == 'R') r--;
        if(l == w || r == 1){
            puts("NO");
            return 0;
        }
	}
	if(l >= p.sc || r <= p.sc){
		puts("NO");
		return 0;
	}

	puts("YES");
	return 0;
}
