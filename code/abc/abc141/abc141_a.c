#include <stdio.h>

int main(void){
  char c;
  scanf("%c", &c);

  if(c == 'S'){
    printf("Cloudy\n");
  }else if(c == 'C'){
    printf("Rainy\n");
  }else{
    printf("Sunny\n");
  }

  return 0;
}
