#include <stdio.h>

int main(void){
  int i;

  int n, k;
  scanf("%d%d", &n, &k);

  char s[n+1];
  scanf(" %s", s);

  int dif=1;
  for(i=1; i<n; i++){
    if(s[i] != s[i-1]) dif++;
  }

  if(dif - 2*k <= 1){
    printf("%d\n", n-1);
  }else{
    printf("%d\n", n-dif+2*k);
  }

  return 0;
}
