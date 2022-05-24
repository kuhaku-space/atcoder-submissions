#include <stdio.h>

int main(void){
  int i;

  int n,w;
  scanf("%d%d",&n,&w);

  for(i=n;i>=0;i--){
    if(w*i+n-i<w*n){
      printf("%d\n",i);
      break;
    }
  }

  return 0;
}
