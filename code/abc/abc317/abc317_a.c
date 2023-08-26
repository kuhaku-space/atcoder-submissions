#include<stdio.h>

int main(void){
  int n,h,x;
  scanf("%d%d%d",&n,&h,&x);
  for(int i = 0; i < n; ++i){
    int p;
    scanf("%d",&p);
    if (h + p >= x){
      printf("%d\n",i + 1);
      return 0;
    }
  }
}