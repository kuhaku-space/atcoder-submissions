#include <stdio.h>

int main(void){
  int i;

  char s[4], t[4];
  scanf(" %s", s);
  scanf(" %s", t);

  int ans=0;
  for(i=0; i<3; i++){
    if(s[i]==t[i]){
      ans++;
    }
  }

  printf("%d\n", ans);

  return 0;
}
