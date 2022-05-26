#include <stdio.h>

int main(void){
  int i;

  int a, b;
  scanf("%d%d", &a, &b);

  int soket=1;
  for(i=0;; i++){
    if(soket>=b) break;
    soket+=a-1;
  }

  printf("%d\n", i);

  return 0;
}
