#include <stdio.h>

int main(void){
  int a,b,c;
  scanf("%d%d%d",&a,&b,&c);

  if(a>=b+c){
    printf("0\n");
  }else{
    printf("%d\n",b+c-a);
  }

  return 0;
}
