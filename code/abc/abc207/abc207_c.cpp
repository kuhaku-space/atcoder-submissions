#include <bits/stdc++.h>
using namespace std;

int main(void){
  int n;
  cin>>n;
  vector<double> l(n),r(n);
  for (int i = 0; i < n; ++i){
    int t;
    cin>>t>>l[i]>>r[i];
    if (t == 2 || t == 4) {
      r[i] -= 0.1;
    }
    if (t >= 3) {
      l[i] += 0.1;
    }
  }
  
  int ans=0;
  for (int i = 0; i < n; ++i){
    for (int j = i+1;j<n;++j){
      if(l[i]<=l[j]&&l[j]<=r[i]||l[j]<=l[i]&&l[i]<=r[j])++ans;
    }
  }
  
  cout <<ans<<endl;
  return 0;
}