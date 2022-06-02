#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
const int MOD = 1e10;
const int INF = 1e9;
using Graph = vector<vector<int>>;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int pow_int(int x, int k) {
    // cerr << x << " " << k << endl;
    int res = 1;
    while (k) {
        if (k & 1) res *= x;
        k >>= 1;
        x *= x;
    }
    return res;
}

signed main(){
  int L;
  cin >> L;
  L--;

  vector<int> bunshi(201);
  for( int i = L-10; i <= L; i++ ){
    int a = i;
    for( int j = 2; j <= i; j++ ){
      while( a%j == 0 ){
        a /= j;
        bunshi[j]++;
      }
    }
  }

  vector<int> bunbo(12);
  for( int i = 2; i <= 11; i++ ){
    int a = i;
    for( int j = 2; j <= i; j++ ){
      while( a%j == 0 ){
        a /= j;
        bunbo[j]++;
      }
    }
  }

  int ue = 1;
  int shita = 1;
  for( int i = 0; i <= L; i++ ){
    if( i <= 11 ){
      if( bunshi[i] - bunbo[i] > 0 ) ue *= pow_int(i, bunshi[i]-bunbo[i]);
      else if( bunshi[i]-bunbo[i] < 0 ) shita *= pow_int(i, bunbo[i]-bunshi[i]);
    }else{
      if( bunshi[i] > 0 ) ue *= pow_int(i, bunshi[i]);
    }
//   cerr << ue << endl;
  }
  cout << ue/shita << endl;
}
