#include <stdio.h>

int main(void){
  int i,j;

  int m,n,k;
  scanf("%d%d%d",&m,&n,&k);

  int line[m+1],x;
  for(i=0;i<=m;i++){
    line[i]=0;
  }
  for(i=0;i<n;i++){
    scanf("%d",&x);
    line[x]++;
  }

  int sum,max=0;
  for(i=1;i<=m;i++){
    sum=line[i];
    for(j=1;j<=k;j++){
      if((i-j>=1&&line[i-j]!=0)||(i+j<=m&&line[i+j]!=0)){
        sum++;
      }
    }
    if(sum>max){
      max=sum;
    }
  }

  printf("%d\n",max);

  return 0;
}
