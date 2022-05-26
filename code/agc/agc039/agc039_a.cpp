#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int (i) = 0; (i) < (n); (i)++)
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef long long ll;

int main(void){
	string s;
	getline(cin, s);
	ll k;
	cin >> k;

	int flg = 1;
	REP(i, s.length()){
		if(!i) continue;
		if(s[i] != s[i-1]){
			flg = 0;
			break;
		}
	}
	if(flg){
		cout << s.length()*k/2 << endl;;
		return 0;
	}

	ll same = 1, same1 = 1;
	ll ans = 0;
	if(s[0] != s[s.length()-1]){
		REP(i, s.length()){
			if(!i) continue;
			if(s[i] == s[i-1]){
				same++;
			}else{
				ans += same/2;
				same = 1;
			}
		}
		ans += same/2;

		cout << ans*k << endl;
	}else{
		REP(i, s.length()){
			if(!i) continue;
			if(s[i] == s[i-1]){
				same++;
			}else{
				if(i != same){
					ans += same/2*k;
				}
				same = 1;
			}
		}
		ans += same/2;
		same++;
		REP(i, s.length()){
			if(!i) continue;
			if(s[i] == s[i-1]){
				same1++;
				same++;
			}else{
				ans += same/2*(k-1);
				ans += same1/2;
				break;
			}
		}

		cout << ans << endl;
	}

	return 0;
}
