#include <stdio.h>

int main(void){
  int i;

  int n;
  scanf("%d", &n);

  int b[n-1];
  for(i=0; i<n-1; i++){
    scanf("%d", &b[i]);
  }

  long sum=b[n-2];
  for(i=n-2; i>0; i--){
    if(b[i] < b[i-1]){
      sum += b[i];
    }else{
      sum += b[i-1];
    }
  }
  sum += b[0];

  printf("%ld\n", sum);

  return 0;
}
