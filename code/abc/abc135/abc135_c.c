#include <stdio.h>

int main(void){
  int i;
  long long sum=0;

  int n;
  scanf("%d",&n);

  long a[n];
  for(i=0;i<n+1;i++){
    scanf("%ld",&a[i]);
  }

  long b;
  for(i=0;i<n;i++){
    scanf("%ld",&b);

    if(b>a[i]){
      if(b>=a[i]+a[i+1]){
        sum+=a[i]+a[i+1];
        a[i+1]=0;
      }else{
        sum+=b;
        a[i+1]-=b-a[i];
      }
    }else{
      sum+=b;
    }
  }

  printf("%lld\n",sum);

  return 0;
}
