#include <stdio.h>

int main(void){
  int i;

  int a, b, t;
  scanf("%d%d%d", &a, &b, &t);

  int dif=b-a;
  while(1){
    b+=dif;
    if(b>=t){
      printf("%d\n", b);
      break;
    }
  }

  return 0;
}
