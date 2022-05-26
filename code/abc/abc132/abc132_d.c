#include <stdio.h>
#include <stdlib.h>

#define Mod 1000000007

int main(void){
	long long i,j,a=1,b=1;

  long long n,k;

  scanf("%lld%lld",&n,&k);

  long long c[2001][2001];
  for(i=0;i<=2000;i++){
    c[i][0]=1;
    c[i][i]=1;
  }

  for(i=2;i<=2000;i++){
    for(j=1;j<i;j++){
      c[i][j]=(c[i-1][j-1]+c[i-1][j])%Mod;
    }
  }

  for(i=1;i<=k;i++){
    if(i<=n-k+1){
      a=c[n-k+1][i];
      b=c[k-1][i-1];
      printf("%lld\n",(a*b)%Mod);
    }else{
      printf("0\n");
    }
  }

	return 0;
}
