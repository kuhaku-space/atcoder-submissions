#include <stdio.h>
#include <stdlib.h>

int main(void){
  long i,j;

  long n;
  scanf("%ld",&n);

  long current;
  int current_state;
  scanf("%ld",&current);

  long next;
  for(i=1;i<n;i++){
    scanf("%ld",&next);
    if(current<next){
      current=next;
      current_state=0;
    }else if(current==next){
    }else if(current==next+1&&current_state==0){
      current=next;
      current_state=1;
    }else{
      printf("No\n");
      exit(0);
    }
  }

  printf("Yes\n");

  return 0;
}
