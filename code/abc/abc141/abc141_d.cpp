#include <cstdio>
#include <queue>
using namespace std;

#define N_MAX 100001

int desc(const void *a, const void *b){
  if(*(long *)a > *(long *)b){
    return -1;
  }else if(*(long *)a == *(long *)b){
    return 0;
  }else{
    return 1;
  }
}

int main(void){
  int i, j;

  int n, m;
  scanf("%d%d", &n, &m);

  priority_queue<long> q;

  long a;
  for(i = 0; i < n; i++){
    scanf("%ld", &a);
    q.push(a);
  }

  for(i = 0; i < m; i++){
    a = q.top();
    q.pop();
    a /= 2;
    q.push(a);
  }

  long ans=0;
  for(i = 0; i < n; i++){
    a = q.top();
    q.pop();
    ans += a;
  }

  printf("%ld\n", ans);

  return 0;
}
