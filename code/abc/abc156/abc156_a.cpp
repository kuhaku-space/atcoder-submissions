#include<stdio.h>

int main(void){
 int k, r;
 scanf("%d%d", &k, &r);
 
 if(k >= 10){
  printf("%d\n", r);
 }else{
  printf("%d\n", r+100*(10-k));
 }
 
 return 0;
}
