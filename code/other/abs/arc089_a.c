#include <stdio.h>
#include <stdlib.h>

int main(){
	int n,i,dx,dy,dt,sign=0;
	
	scanf("%d",&n);
	
	int t[n+1],x[n+1],y[n+1];
	t[0]=0,x[0]=0,y[0]=0;
	
	for(i=1;i<=n;i++){
		scanf("%d %d %d",&t[i],&x[i],&y[i]);
	}
	
	for(i=1;i<=n;i++){
		dx=x[i]-x[i-1]; dy=y[i]-y[i-1]; dt=t[i]-t[i-1];
		if((abs(dx)+abs(dy))<=abs(dt)&&(dx+dy-dt)%2==0){
		}else{
			sign=1;
			break;
		}
	}
	
	if(sign==0){
		printf("Yes\n");
	}else{
		printf("No\n");
	}
	
	return 0;
}