#include <stdio.h>
#include <stdlib.h>

int asc(const void *a,const void *b){
  return *(int *)a-*(int *)b;
}

int main(void){
  int i;

  int n;
  scanf("%d",&n);

  int v[n];
  for(i=0;i<n;i++){
    scanf("%d",&v[i]);
  }

  qsort(v,n,sizeof(int),asc);

  double ans=v[0];

  for(i=1;i<n;i++){
    ans=(ans+v[i])/2;
  }

  printf("%lf\n",ans);

  return 0;
}
