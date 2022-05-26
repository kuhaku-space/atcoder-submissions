#include <stdio.h>

int main(void){
  int i,wrong=0;

  int n;
  scanf("%d\n",&n);

  int p;
  for(i=1;i<=n;i++){
    scanf("%d",&p);
    if(p!=i){
      wrong++;
    }
  }

  if(wrong==0||wrong==2){
    printf("YES\n");
  }else{
    printf("NO\n");
  }

  return 0;
}
