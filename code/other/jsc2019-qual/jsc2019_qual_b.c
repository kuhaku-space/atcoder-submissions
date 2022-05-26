#include <stdio.h>

#define MAX 2000
#define MOD 1000000007

int main(void){
  long i,j;
  long ans=0;

  long n,k;
  scanf("%ld%ld",&n,&k);

  long a[MAX]={};
  for(i=0;i<n;i++){
    scanf("%ld",&a[i]);
    for(j=0;j<i;j++){
      if(a[j]>a[i]){
        ans=(ans+k*(k+1)/2)%MOD;
      }else if(a[j]<a[i]){
        ans=(ans+k*(k-1)/2)%MOD;
      }
    }
  }

  printf("%ld\n",ans);

  return 0;
}
