#include <stdio.h>

int main(void){
  long i,j;

  long n;
  scanf("%ld",&n);

  long a;
  if(n%3){
    for(i = 0; i < n; i++){
      scanf("%ld", &a);
      if(a){
        printf("No\n");
        return 0;
      }
    }
    printf("Yes\n");
    return 0;
  }

  long index_no[3]={-1,-1,-1},index[3]={0,0,0};
  for(i=0;i<n;i++){
    scanf("%ld",&a);
    if(index_no[0]==-1){
      index_no[0]=a;
      index[0]++;
    }else if(a==index_no[0]){
      index[0]++;
    }else if(index_no[1]==-1){
      index_no[1]=a;
      index[1]++;
    }else if(a==index_no[1]){
      index[1]++;
    }else if(index_no[2]==-1){
      index_no[2]=a;
      index[2]++;
    }else if(a==index_no[2]){
      index[2]++;
    }else{
      printf("No\n");
      return 0;
    }
  }

  if(((index_no[0]==0&&index[0]*2==index[1])||(index_no[1]==0&&index[1]*2==index[0]))&&index_no[2]==-1){
    printf("Yes\n");
  }else if(index_no[0]==0&&index[0]==n){
    printf("Yes\n");
  }else if(index[0]!=index[1]||index[1]!=index[2]){
    printf("No\n");
  }else if(index_no[0]!=(index_no[1]^index_no[2])){
    printf("No\n");
  }else{
    printf("Yes\n");
  }

  return 0;
}
