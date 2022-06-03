#include <bits/stdc++.h>
using namespace std;

int main(void){
  long long a,b,c,d;
  cin>>a>>b>>c>>d;
  if (b >= c * d) {
    cout << -1 <<endl;
    return 0;
  }
  
  cout << (a - 1) / (d * c - b) + 1 << endl;
  return 0;
}