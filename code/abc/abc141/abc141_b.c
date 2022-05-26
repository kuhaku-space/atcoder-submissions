#include <stdio.h>
#include <string.h>

#define S_MAX 101

int main(void){
  int i;

  char s[S_MAX];
  scanf("%s", s);

  for(i=0; i<strlen(s); i++){
    if(i%2 == 0){
      if(s[i] == 'L'){
        printf("No\n");
        return 0;
      }
    }else{
      if(s[i] == 'R'){
        printf("No\n");
        return 0;
      }
    }
  }

  printf("Yes\n");

  return 0;
}
