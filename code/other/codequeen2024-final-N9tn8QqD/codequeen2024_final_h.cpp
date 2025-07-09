#include<bits/stdc++.h>
using namespace std;
using pl=pair<long long,long long>;
bool comp(const pl &l, const pl &r){
  return (l.first-l.second) > (r.first-r.second);
}
int main(){
  long long n,k,t;
  cin >> n >> k >> t;
  vector<pl> a(n);
  for(long long i=0;i<n;i++){
    cin >> a[i].first >> a[i].second;
  }
  sort(a.begin(),a.end(),comp);
  long long l=1,r=n;
  while(l<=r){
    long long x=(l+r)/2;
    vector<long long> pre(n+1,4e18);
    vector<long long> suf(n+1,4e18);
    long long ps=min(x,k);
    long long ss=max(x-k,0ll);
    {
      long long sum=0;
      priority_queue<long long> pq;
      for(long long i=0;i<n;i++){
        sum+=a[i].second;
        pq.push(a[i].second);
        if(pq.size()>ps){
          long long od=pq.top(); pq.pop();
          sum-=od;
        }
        if(pq.size()==ps){pre[i]=sum;}
      }
    }
    
    {
      long long sum=0;
      priority_queue<long long> pq;
      if(ss==0){suf[n]=0;}
      for(long long i=n-1;i>=0;i--){
        sum+=a[i].first;
        pq.push(a[i].first);
        if(pq.size()>ss){
          long long od=pq.top(); pq.pop();
          sum-=od;
        }
        if(pq.size()==ss){suf[i]=sum;}
      }
    }
    long long tim=8e18;
    for(long long i=0;i<n;i++){
      tim=min(tim,pre[i]+suf[i+1]);
    }
    if(tim<=t){l=x+1;}
    else{r=x-1;}
  }
  cout << r << "\n";
  return 0;
}