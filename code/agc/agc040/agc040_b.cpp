#include <bits/stdc++.h>
using namespace std;

#define FOR(i, m, n) for(int (i) = (m); (i) < (n); (i)++)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FOR(i, 1, n+1)
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

const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;
const int MAX_N = 1e5;

ll N;
ll data[MAX_N*4];

bool asc(const P &a, const P &b){
	if(a.fs == b.fs) return a.sc > b.sc;
	else return a.fs < b.fs;
}

void init(){
  rep(i, MAX_N*4) data[i] = LINF;
}

void update(int i, int x){
  i += N-1;
  data[i] = x;
  while(i > 0){
    i = (i-1)/2;
    data[i] = min(data[i*2+1], data[i*2+2]);
  }
}

ll rmq(ll a, ll b, ll k, ll l, ll r){
  if(r <= a || b <= l) return LINF;
  if(a <= l && r <= b) return data[k];
  else{
    ll vl = rmq(a, b, k*2+1, l, (l+r)/2);
    ll vr = rmq(a, b, k*2+2, (l+r)/2, r);
    return min(vl, vr);
  }
}

int main(void){
	int n;
	cin >> n;

	N = 1;
	while(N < n) N <<= 1;
	init();

	vector<P> r(n);
	rep(i, n) cin >> r[i].fs >> r[i].sc;

	sort(all(r));

	rep(i, n) update(i, r[i].sc);

	ll ans = 0;
	repn(i, n-1){
		ans = max(ans, max(0LL, rmq(0, i, 0, 0, N)-r[i-1].fs+1)+max(0LL, rmq(i, n, 0, 0, N)-r[n-1].fs+1));
	}

	rep(i, n){
		ans = max(ans, r[i].sc-r[i].fs+1+max(0LL, rmq(0, n, 0, 0, N)-r[n-1].fs+1));
	}

	co(ans);

	return 0;
}
