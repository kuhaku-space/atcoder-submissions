#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int (i) = 0; (i) < (n); (i)++)

typedef long long ll;

int main(void){
  int n, m;
  cin >> n >> m;

  vector<pair<int, int>> work(n);

  int a, b;
  REP(i, n){
    cin >> a >> b;
    work[i] = make_pair(a, b);
  }

  sort(work.begin(), work.end());

  priority_queue<int> queue;

  int start = 0;
  ll ans = 0;
  for(int i = 1; i <= m; i++){
    for(int j = start; j < n; j++){
      if(work[j].first <= i){
        queue.push(work[j].second);
      }else{
        start = j;
        break;
      }
      if(j == n-1) start = n;
    }

    if(!queue.empty()){
      ans += queue.top();
      queue.pop();
    }
  }

  cout << ans << endl;

  return 0;
}
