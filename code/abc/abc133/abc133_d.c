#include <stdio.h>

#define N_MAX 100000

int main(void){
	int i, j;

	int n;
	scanf("%ld", &n);

	int a[N_MAX], ans[N_MAX];
	long sum = 0, sum0 = 0;
	for(i = 0; i < n; i++){
		scanf("%ld", &a[i]);
		sum += a[i];
		if(i%2 == 0) sum0 += a[i];
	}

	ans[0] = 2*sum0-sum;

	for(i = 1; i < n; i++){
		ans[i] = 2*a[i-1]-ans[i-1];
	}

	for(i=0;i<n;i++){
		printf("%ld ", ans[i]);
	}
	printf("\n");

	return 0;
}
