#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int main(void){
	int i,j,sum=0,sl;
	
	int n,l;
	
	scanf("%d%d",&n,&l);
	
	sl=l;
	
	for(i=1;i<=n;i++){
		sum+=l;
		l++;
	}
	
	if(sl>=0){
		sum-=sl;
	}else if(sl+n-1>=0){
	}else{
		sum-=sl+n-1;
	}
	
	printf("%d\n",sum);
	
	return 0;
}