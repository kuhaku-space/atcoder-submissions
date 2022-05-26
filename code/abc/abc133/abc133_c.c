#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define Mod 2019

int main(void){
  long i,j,x,min=Mod,mini=Mod;
  long l,r;

  scanf("%ld%ld",&l,&r);

  if(r-l>=Mod){
    printf("0\n");
  }else{
    for(i=l;i<r;i++){
      x=(i*i)%Mod;
      for(j=1;i+j<=r;j++){
        x=(x+i)%Mod;
        if(x<mini){
          mini=x;
        }
      }
      if(mini<min){
        min=mini;
      }
    }
    printf("%ld\n",min);
  }


	return 0;
}
