#include <stdio.h>

int main(void){
  int i;

  int n, p;
  scanf("%d%d", &n, &p);

  int a[n];
  for(i = 0; i < n; i++){
    scanf("%d", &a[i]);
  }

  for(i = 0; i < n; i++){
    if(p >= a[i]){
      p -= a[i];
    }else{
      printf("%d\n", i);
      return 0;
    }
  }

  printf("%d\n", n);

  return 0;
}
