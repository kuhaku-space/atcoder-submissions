#include <stdio.h>
#include <string.h>

int main(void){
  int i,j;

  int n;
  scanf("%d", &n);

  char str[50][51];
  for(i=0;i<n;i++){
    scanf(" %s", str[i]);
  }

  char search_str[2][5]={"okyo","ech"};
  char *str_pointer[2];
  for(i=0;i<n;i++){
    str_pointer[0]=strstr(str[i],search_str[0]);
    if(str_pointer[0]==NULL){
      printf("No\n");
    }else{
      str_pointer[1]=strstr(str_pointer[0],search_str[1]);
      if(str_pointer[1]==NULL){
        printf("No\n");
      }else{
        printf("Yes\n");
      }
    }
  }

  return 0;
}
