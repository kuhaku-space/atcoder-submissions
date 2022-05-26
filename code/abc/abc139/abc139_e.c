#include <stdio.h>

#define MAX_N 1000

int main(void){
  int i, j, k;

  int n;
  scanf("%d", &n);

  int player_opponent[MAX_N+1][MAX_N-1]={};
  for(i=1; i<=n; i++){
    for(j=0; j<n-1; j++){
      scanf("%d", &player_opponent[i][j]);
    }
  }

  int game_num[MAX_N+1]={};
  int game_finish[MAX_N+1]={};
  int next_player[MAX_N+1]={};
  for(i=1; i<=n; i++){
    next_player[i]=player_opponent[i][0];
  }

  int flag=0, finish_player=0;
  for(i=1;;i++){
    flag=0;
    for(j=1; j<=n; j++) game_finish[j]=0;
    for(j=1; j<=n; j++){
      k=next_player[j];
      if(k==0) continue;
      if(game_finish[j] == 0 && game_finish[k] == 0 && next_player[k] == j){
        //printf("%d %dvs%d\n", i, j, k);
        game_num[j]++; game_num[k]++;
        next_player[j]=player_opponent[j][game_num[j]];
        next_player[k]=player_opponent[k][game_num[k]];
        game_finish[j]=1; game_finish[k]=1;
        if(game_num[j] == n-1) finish_player++;
        if(game_num[k] == n-1) finish_player++;
        flag=1;
      }
    }

    if(flag==0){
      printf("-1\n");
      return 0;
    }else if(finish_player == n){
      break;
    }
  }

  printf("%d\n", i);

  return 0;
}
