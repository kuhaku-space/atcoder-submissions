#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(ll (i) = 0; (i) < (n); (i)++)
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef long long ll;

ll gcm(ll a, ll b){
	if(!b) return a;
	else return gcm(b, a%b);
}

int main(void){
	ll a, b;
	cin >> a >> b;

	ll n = gcm(a, b), ans = 1;
	//cout << n << endl;
	for(ll i = 2; i*i <= n; i++){
		if(!(n%i)){
			ans++;
			while(!(n%i)) n /= i;
		}
	}
	if(n != 1) ans++;

	cout << ans << endl;

	return 0;
}
