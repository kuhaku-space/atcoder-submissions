#include <stdio.h>

int main(){
	int n,y,a,b,c,i,k,x,z,sign=0;
	
	scanf("%d %d",&n,&y);
	
	a=y/1000;
	k=a/5;
	
	for(i=0;i<=k;i++){
		if(n>=a+i%2+i/2&&n<=a+i){
			sign=1;
			break;
		}
		a-=5;
	}
	
	if(sign==1){
		x=(y/1000-a)/5;
		z=n-a;
		printf("%d %d %d\n",x-z,2*z-x,a);
	}else{
		printf("-1 -1 -1\n");
	}
	
	return 0;
}