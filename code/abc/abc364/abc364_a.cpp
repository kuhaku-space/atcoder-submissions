#include<iostream>
#include<string>

using namespace std;

int main(void){
  int n;
  cin>>n;
  bool f=false;
  while(n--){
    string s;
    cin>>s;
    if(s=="sweet"){
      if(f&&n){
        cout<<"No\n";
        return 0;
      }else{
        f=true;
      }
    }else{
      f=false;
    }
  }
  cout<<"Yes\n";
}