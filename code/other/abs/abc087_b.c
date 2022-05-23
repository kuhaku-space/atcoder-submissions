#include <stdio.h>

int main(){
	int a,b,c,i,j,k,n=0,x;
	
	scanf("%d",&a);
	scanf("%d",&b);
	scanf("%d",&c);
	scanf("%d",&x);
	
	for(i=0;i<=a;i++){
		for(j=0;j<=b;j++){
			for(k=0;k<=c;k++){
				if(500*i+100*j+50*k==x){
					n++;
				}
			}
		}
	}
	
	printf("%d\n",n);
	
	return 0;
}