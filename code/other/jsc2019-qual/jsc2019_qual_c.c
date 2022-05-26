#include <stdio.h>

#define MOD 1000000007

int main(void){
  int i,j;
  long ans=1;

  int n;
  scanf("%d",&n);

  char str[2*n+1];
  scanf(" %s",str);

  int arr[2*n];
  for(i=0;i<2*n;i++){
    if(str[i]=='W'){
      arr[i]=0;
    }else{
      arr[i]=1;
    }
  }

  int line=0;
  for(i=0;i<2*n;i++){
    if(line==0&&arr[i]==0){
      printf("0\n");
      return 0;
    }else if((line+arr[i])%2==0){
      ans=(ans*line)%MOD;
      line--;
    }else{
      line++;
    }
  }

  if(line!=0){
    printf("0\n");
  }else{
    for(i=2;i<=n;i++){
      ans=(ans*i)%MOD;
    }
    printf("%ld\n",ans);
  }

  return 0;
}
