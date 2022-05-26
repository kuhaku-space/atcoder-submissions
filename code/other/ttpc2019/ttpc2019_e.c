#include <stdio.h>
#include <stdlib.h>

int main(void){
  int i, j, k;

  int n;
  scanf("%d", &n);

  if(n%2==0){
    printf("No\n");
    return 0;
  }else{
    printf("Yes\n");
  }

  long arr[n][n];
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      arr[i][j]=i*n+j+1;
    }
  }

  long arr_line[n];
  long arr_line_copy[n];
  for(i=0;i<n;i++){
    arr_line[i]=arr[i][i];
    arr_line_copy[i]=arr[i][i];
  }
  for(i=0;i<n;i++){
    arr_line[i]=arr_line_copy[(i*2)%n];
  }

  for(i=0;i<n;i++){
    arr[i][i]=arr_line[i];
  }

  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      printf("%ld ", arr[i][j]);
    }
    printf("\n");
  }

  return 0;
}
