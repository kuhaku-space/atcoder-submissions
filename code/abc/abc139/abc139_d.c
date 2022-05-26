#include <stdio.h>

int main(void){
  long i;

  long n;
  scanf("%ld", &n);

  long long ans;
  for(i=0; i<n; i++){
    ans+=i;
  }

  printf("%lld\n", ans);

  return 0;
}
