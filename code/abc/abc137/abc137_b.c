#include <stdio.h>

int main(void){
  int i;

  int k,x;
  scanf("%d%d",&k,&x);

  for(i=x-k+1;i<x+k;i++){
    printf("%d ",i);
  }
  printf("\n");

  return 0;
}
