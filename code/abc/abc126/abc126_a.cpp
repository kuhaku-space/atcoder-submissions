#include <iostream>
#include <string>
using namespace std;
int main(void){
  int n,m;
  cin>>n>>m;
  string s;
  cin>>s;
  s[m-1]-='A'-'a';
  cout<<s<<endl;
  return 0;
}