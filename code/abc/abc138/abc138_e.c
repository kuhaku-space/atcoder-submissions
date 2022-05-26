#include <stdio.h>
#include <string.h>

#define S_MAX 100001
#define T_MAX 100001

int b_search(int arr[], int num, int left, int right){
  if(left == right) return arr[left];
  int mid = (left+right)/2;
  if(arr[mid] > num) return b_search(arr, num, left, mid);
  else return b_search(arr, num, mid+1, right);
}

int main(void){
  int i, j, k;

  char s[S_MAX], t[T_MAX];
  scanf(" %s", s);
  scanf(" %s", t);

  int s_len = strlen(s);

  int alp[26][S_MAX] = {}, alp_num[26] = {}, c_num;
  for(i = 0; i < s_len; i++){
    c_num = s[i]-'a';
    alp[c_num][alp_num[c_num]] = i+1;
    alp_num[c_num]++;
  }

  for(i = 0; i < 26; i++){
    if(alp[i][0] == 0) continue;
    alp[i][alp_num[i]] = alp[i][0]+s_len;
  }

  long ans = 0;
  int prev_pos = 0, next_pos = 0;
  for(i = 0; i < strlen(t); i++){
    c_num = t[i]-'a';
    if(alp[c_num][0] == 0){
      printf("-1\n");
      return 0;
    }
    next_pos = b_search(alp[c_num], prev_pos, 0, alp_num[c_num]);
    ans += next_pos - prev_pos;
    prev_pos = next_pos%s_len;
  }

  printf("%ld\n", ans);

  return 0;
}
