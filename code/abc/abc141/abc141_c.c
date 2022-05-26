#include <stdio.h>

#define N_MAX 100001

int main(void){
  int i, j;

  int n, q;
  long k;
  scanf("%d%ld%d", &n, &k, &q);

  int ans[N_MAX]={};

  int a;
  for(i=0; i<q; i++){
    scanf("%d", &a);
    ans[a]++;
  }

  for(i=1; i<=n; i++){
    if(q-ans[i] < k){
      printf("Yes\n");
    }else{
      printf("No\n");
    }
  }

  return 0;
}
