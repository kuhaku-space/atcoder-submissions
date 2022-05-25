#include <stdio.h>
#include <string.h>

#define MAX 100001

int main(void){
  int i,j;

  char str[MAX];
  scanf(" %s",str);

  long ans[MAX];
  for(i=0;i<MAX;i++){
    ans[MAX]=0;
  }

  long r_num=0,l_num=0,repeat_place;
  for(i=0;i<strlen(str);i++){
    if(str[i]=='R'){
      if(l_num==0){
        r_num++;
      }else{
        if(l_num%2==0){
          ans[repeat_place]+=l_num/2;
          ans[repeat_place+1]+=l_num/2;
        }else{
          ans[repeat_place]+=l_num/2;
          ans[repeat_place+1]+=l_num/2+1;
        }
        l_num=0;
        r_num++;
      }
    }else{
      if(r_num==0){
        l_num++;
      }else{
        repeat_place=i-1;
        if(r_num%2==0){
          ans[repeat_place]+=r_num/2;
          ans[repeat_place+1]+=r_num/2;
        }else{
          ans[repeat_place]+=r_num/2+1;
          ans[repeat_place+1]+=r_num/2;
        }
        r_num=0;
        l_num++;
      }
    }
  }

  if(l_num%2==0){
    ans[repeat_place]+=l_num/2;
    ans[repeat_place+1]+=l_num/2;
  }else{
    ans[repeat_place]+=l_num/2;
    ans[repeat_place+1]+=l_num/2+1;
  }

  for(i=0;i<strlen(str);i++){
    printf("%ld ",ans[i]);
  }
  printf("\n");

  return 0;
}
