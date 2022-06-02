#include <iostream>
#include <string>
using namespace std;
int main(void){
  int x;
  cin>>x;
  int a=x/100,b=x%100;
  bool f=false,g=false;
  for(int i=1;i<=12;++i){
    f|=a==i;
    g|=b==i;
  }
  if(f&g) puts("AMBIGUOUS");
  else if(f&!g) puts("MMYY");
  else if(!f&g) puts("YYMM");
  else puts("NA");
  return 0;
}