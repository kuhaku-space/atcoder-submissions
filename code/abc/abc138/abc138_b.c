#include <stdio.h>

int main(void){
  int i;

  int n;
  scanf("%d",&n);

  int a[n];
  for(i=0;i<n;i++){
    scanf("%d",&a[i]);
  }

  double sum=0.0;
  for(i=0;i<n;i++){
    sum+=(1/(double)a[i]);
  }

  printf("%lf\n",1/sum);

  return 0;
}
