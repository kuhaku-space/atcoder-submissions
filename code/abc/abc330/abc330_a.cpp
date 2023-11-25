#include <iostream>
#include <vector>
using namespace std;

int main(){
  int n,l;
  cin>>n>>l;
  vector<int> a(n);
  for (auto&x:a)cin>>x;
  int ans=0;
  for(auto x:a)ans+=x>=l;
  cout<<ans<<endl;
}