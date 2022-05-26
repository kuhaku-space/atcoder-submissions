#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(void){
	int i;
	
	int n,t,a;
	scanf("%d%d%d",&n,&t,&a);
	
	int h[n+1];
	for(i=1;i<=n;i++){
		scanf("%d",&h[i]);
	}
	
	int num=1;
	float abs=fabs(t-a-0.006*h[1]);
	for(i=1;i<=n;i++){
		if(abs>fabs(t-a-0.006*h[i])){
			abs=fabs(t-a-0.006*h[i]);
			num=i;
		}
	}
	
	printf("%d\n",num);
	
	return 0;
}