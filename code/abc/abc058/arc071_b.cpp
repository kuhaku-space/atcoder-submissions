#include <stdio.h>
#define MOD 1000000007

int main(void){
	long i, n, m;
	scanf("%ld %ld", &n, &m);
	long x, y;
	long sumx = 0;
	for(i = 0; i < n; i++){
		scanf("%ld", &x);
		sumx += x*(i*2-(n-1));
	}
	sumx %= MOD;
	long sumy = 0;
	for(i = 0; i < m; i++){
		scanf("%ld", &y);
		sumy += y*(i*2-(m-1));
	}
	sumy %= MOD;
	printf("%ld\n", sumx*sumy%MOD);

	return 0;
}
