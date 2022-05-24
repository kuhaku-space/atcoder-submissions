#include <stdio.h>

#define Max 1000000001

int main(void){
  long i,j,min=Max,min_id=0;

  long n;
  scanf("%ld",&n);

  long a,color[n+1];

  for(i=0;i<=n;i++){
    color[i]=-1;
  }

  for(i=0;i<n;i++){
    scanf("%ld",&a);

    if(a<=min){
      min=a;
      color[min_id++]=a;
    }else{
      for(j=0;j<=n;j++){
        if(a>color[j]){
          color[j]=a;
          if(j==min_id-1){
            min=a;
          }
          break;
        }
      }
    }
  }

  printf("%ld\n",min_id);

  return 0;
}
