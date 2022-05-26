#include <stdio.h>

int main(void){
  int i;

  int n;
  scanf("%d", &n);

  int sum=0, ans=0;
  long h[n];
  for(i=0; i<n; i++){
    scanf("%ld", &h[i]);
    if(i>=1){
      if(h[i] <= h[i-1]){
        sum++;
      }else{
        if(sum > ans){
          ans=sum;
        }
        sum=0;
      }
      if(i == n-1 && sum > ans){
        ans=sum;
      }
    }
  }

  printf("%d\n", ans);

  return 0;
}
