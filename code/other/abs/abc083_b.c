#include <stdio.h>

int main(){
	int a,b,n,i,j,w,x,y,z,sum=0;
	
	scanf("%d %d %d",&n,&a,&b);
	
	for(w=0;w<=9;w++){
		for(x=0;x<=9;x++){
			for(y=0;y<=9;y++){
				for(z=0;z<=9;z++){
					if(1000*w+100*x+10*y+z<=n&&w+x+y+z>=a&&w+x+y+z<=b){
						sum+=1000*w+100*x+10*y+z;
					}
				}
			}
		}
	}
	
	if(a==1&&n==10000){
		sum+=10000;
	}
	
	printf("%d\n",sum);
	
	return 0;
}