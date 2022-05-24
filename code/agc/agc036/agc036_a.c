#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Max 1000000000

int main(void){
  long i,j;
  long rest1,rest2=1;

  long long s;
  scanf("%lld",&s);

  if(s==1000000000000000000){
    printf("0 0 0 %ld %ld 0\n",Max,Max);
    return 0;
  }

  long root_s1=sqrt(s)+1;
  long root_s2=root_s1;

  if((root_s1-1)*(root_s2-1)>s){
    root_s1--;
    root_s2--;
  }else if(root_s1*(root_s2-1)>s){
    root_s2--;
  }

  rest1=root_s1*root_s2-s;

  if(rest1>Max){
    for(i=2;i<rest1;i++){
      while(0){
        if(rest1%i==0){
          rest1/=i;
          rest2*=i;
        }else{
          break;
        }
      }
      if(rest1<Max){
        break;
      }
    }
  }

  printf("0 0 %ld %ld %ld %ld\n",root_s1,rest1,rest2,root_s2);

  return 0;
}
