#include <stdio.h>

#define H_MAX 1000
#define W_MAX 1000

int main(void){
  int i, j;

  int h, w;
  scanf("%d%d", &h, &w);

  char c;
  int board[H_MAX][W_MAX] = {}, black_num = 0;
  for(i = 0; i < h; i++){
    for(j = 0; j < w; j++){
      scanf(" %c", &c);
      if(c == '.') board[i][j] = -1;
      else black_num++;
    }
  }

  if(black_num == 1){
    int max_h, max_w;
    for(i = 0; i < h; i++){
      for(j = 0; j < w; j++){
        if(board[i][j] == 0){
          if(i > h-i-1) max_h = i;
          else max_h = h-i-1;
          if(j > w-j-1) max_w = j;
          else max_w = w-j-1;
          printf("%d\n", max_h+max_w);
          return 0;
        }
      }
    }
  }

  int cnt = 0, flag;
  while(1){
    flag = 0;
    for(i = 0; i < h; i++){
      for(j = 0; j < w; j++){
        if(board[i][j] == cnt){
          if(i != 0 && board[i-1][j] == -1){
            board[i-1][j] = cnt+1;
            flag = 1;
          }
          if(i != h-1 && board[i+1][j] == -1){
            board[i+1][j] = cnt+1;
            flag = 1;
          }
          if(j != 0 && board[i][j-1] == -1){
            board[i][j-1] = cnt+1;
            flag = 1;
          }
          if(j != w-1 && board[i][j+1] == -1){
            board[i][j+1] = cnt+1;
            flag = 1;
          }
        }
      }
    }
    if(flag == 0) break;
    cnt++;
  }

  printf("%d\n", cnt);

  return 0;
}
