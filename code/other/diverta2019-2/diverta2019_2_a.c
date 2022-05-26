#include <stdio.h>

int main(void){
	int n,k;
	
	scanf("%d%d",&n,&k);
	
	if(k==1){
		printf("0\n");
	}else{
		printf("%d\n",n-k);
	}
	
	return 0;
}