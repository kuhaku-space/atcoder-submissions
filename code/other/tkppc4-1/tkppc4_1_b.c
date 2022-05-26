#include <stdio.h>

int main(void){
  long i,max=0,max_id;

  long n,k;
  scanf("%ld%ld",&n,&k);

  long a;
  for(i=0;i<n;i++){
    scanf("%ld",&a);
    if(a<k&&a>max){
      max=a;
      max_id=i+1;
    }
  }

  if(max!=0){
    printf("%ld\n",max_id);
  }else{
    printf("-1\n");
  }

  return 0;
}
