#include <stdio.h>
#include <string.h>

int main(void){
  int i,j;

  long long n;
  char x[60];
  scanf("%lld",&n);
  scanf(" %s",x);

  for(i=2;i<=10;i++){
    if(n%i==x[strlen(x)-1]-'0'){
      if(strlen(x)==1){
        printf("%d\n",i);
        break;
      }else if(n/i%i==x[strlen(x)-2]-'0'){
        if(strlen(x)==2){
          printf("%d\n",i);
          break;
        }else if(n/i/i%i==x[strlen(x)-3]-'0'){
          printf("%d\n",i);
          break;
        }
      }
    }
  }

  return 0;
}
