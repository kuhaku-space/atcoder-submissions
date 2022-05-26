#include <stdio.h>

int main(void){
  int i;

  int n;
  scanf("%d",&n);

  int ans=1,sign=0;
  long a[n];
  for(i=0;i<n;i++){
    scanf("%ld",&a[i]);
  }



  for(i=1;i<n;i++){
    if(a[i]>a[i-1]){
      if(sign==-1){
        ans++;
        sign=1;
      }else if(sign==0){
        sign=1;
      }
    }else if(a[i]<a[i-1]){
      if(sign==1){
        ans++;
        sign=-1;
      }else if(sign==0){
        sign=-1;
      }
    }
  }

  if(sign==0){
    printf("0\n");
  }else{
    printf("%d\n",ans+1);
  }

  return 0;
}
