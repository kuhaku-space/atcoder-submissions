#include<stdio.h>

int main(void){
  int n;
  scanf("%d",&n);
  int a[n];
  int m=100000;
  for (int i=0;i<n;++i){
    scanf("%d",&a[i]);
    if (a[i]<m){
      m=a[i];
    }
  }
  for(int x=m;;++x){
    int c=0;
    for(int i=0;i<n;++i){
      c+=a[i]==x;
    }
    if(c==0){
      printf("%d\n",x);
      return 0;
    }
  }
}