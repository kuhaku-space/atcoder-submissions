#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin>>N;
  long sum=0;
  vector<int> vec(N);
  for(int i=0;i<N;i++){
    cin>>vec.at(i);
    sum+=vec.at(i);
  }
  long X;
  cin>>X;
  long R=0;
  R=X%sum;
  int i=0;
  while(true){
    if(R<vec.at(i)){
      break;
    }
    R-=vec.at(i);
    i+=1;
  }
  cout<<(X/sum)*N+i+1<<endl;
}