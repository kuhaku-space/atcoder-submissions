#include <stdio.h>
#include <stdlib.h>

#define N_MAX 100000

int desc(const void *a, const void *b){
  if(*(int *)a > *(int *)b){
    return -1;
  }else if(*(int *)a == *(int *)b){
    return 0;
  }else{
    return 1;
  }
}

int main(void){
  int i, j;

  int n;
  scanf("%d", &n);

  int a[N_MAX] = {}, plus = 0, minus = 0;
  long sum = 0;
  for(i = 0; i < n; i++){
    scanf("%d", &a[i]);
    if(a[i] > 0){
      plus++;
      sum += a[i];
    }else if(a[i] < 0){
      minus++;
      sum -= a[i];
    }
  }

  qsort(a, n, sizeof(int), desc);

  if(plus == 0) sum += a[0]*2;
  else if(minus == 0) sum -= a[n-1]*2;
  printf("%ld\n", sum);

  if(plus == 0){
    for(i = 1; i < n ;i++){
      printf("%d %d\n", a[0], a[i]);
      a[0] -= a[i];
    }
    return 0;
  }else if(minus == 0){
    for(i = 1; i < n-1; i++){
      printf("%d %d\n", a[n-1], a[i]);
      a[n-1] -= a[i];
    }
    printf("%d %d\n", a[0], a[n-1]);
    return 0;
  }

  for(i = 0; i < plus-1; i++){
    printf("%d %d\n", a[n-1], a[i]);
    a[n-1] -= a[i];
  }
  for(i = plus; i< n; i++){
    printf("%d %d\n", a[plus-1], a[i]);
    a[plus-1] -= a[i];
  }

  return 0;
}
