#include <stdio.h>
#include <stdlib.h>

int asc(const void *a, const void *b){
  if(*(long *)a > *(long *)b){
    return 1;
  }else if(*(long *)a == *(long *)b){
    asc(a+1, b+1);
  }else{
    return -1;
  }
}

int main(void){
	int i, j, k;

	int n;
	scanf("%d", &n);

	long pos[50][2] = {};
	for(i = 0; i < n; i++){
		scanf("%ld%ld", &pos[i][0], &pos[i][1]);
	}

	qsort(pos, n, sizeof(long)*2, asc);

	long dif[2500][2] = {};
	for(i = 0; i < n-1; i++){
		for(j = i+1; j < n; j++){
			for(k = 0; ; k++){
				if(dif[k][0] == 0 && dif[k][1] == 0){
					dif[k][0] = pos[j][0]-pos[i][0];
					dif[k][1] = pos[j][1]-pos[i][1];
					break;
				}
			}
		}
	}

	int ans = 0, cnt = 0;
	for(i = 0; ; i++){
		if(dif[i][0] == 0 && dif[i][1] == 0) break;
		cnt = 0;
		for(j = i+1; ;j++){
			if(dif[j][0] == 0 && dif[j][1] == 0) break;
			if(dif[j][0] == dif[i][0] && dif[j][1] == dif[i][1]) cnt++;
		}
		if(cnt > ans) ans = cnt;
	}

	if(n == 1) printf("1\n");
	else printf("%d\n",n-ans-1);

	return 0;
}
