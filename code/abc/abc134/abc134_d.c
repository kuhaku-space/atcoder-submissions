#include <stdio.h>

int main(void) {
  long i,j,num=0;

  long n;
  scanf("%ld",&n);

  int a[n+1];
  for(i=1;i<=n;i++){
    scanf("%d",&a[i]);
  }

  int ans[n+1];

  for(i=0;i<=n;i++){
    ans[i]=0;
  }

  for(i=n;i>=1;i--){
    for(j=2;i*j<=n;j++){
      if(ans[i*j]==1){
        ans[i]=(ans[i]+1)%2;
      }
    }
    if(ans[i]==a[i]){
      ans[i]=0;
    }else{
      ans[i]=1;
      num++;
    }
  }


  printf("%ld\n",num);
  for(i=1;i<=n;i++){
    if(ans[i]==1){
      printf("%ld ",i);
    }
  }
  printf("\n");

  return 0;
}
