#include <stdio.h>

int main(){
	int i,j,k=0,n;
	int a[201];
	
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf(" %d",&a[i]);
	}
	
	for(j=0;;j++){
		
		for(i=1;i<=n;i++){
			if(a[i]%2==1){
				k++;
				break;
			}
		}
		if(k==1){
			break;
		}else{
			for(i=1;i<=n;i++){
				a[i]/=2;
			}
		}
	}
	
	printf("%d\n",j);
	
	return 0;
}