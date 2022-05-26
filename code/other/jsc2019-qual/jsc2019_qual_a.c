#include <stdio.h>

int main(void){
  int i,j,ans=0;

  int m,d;
  scanf("%d%d",&m,&d);

  for(i=4;i<=m;i++){
    for(j=2;j<=9;j++){
      if(i%j==0&&i/j>=2&&i/j<=9){
        if(j*10+i/j<=d){
          ans++;
        }
      }
    }
  }

  printf("%d\n",ans);

  return 0;
}
