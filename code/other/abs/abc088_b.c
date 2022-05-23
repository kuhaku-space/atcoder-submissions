#include <stdio.h>

int main(){
	int n,i,j,sa,gap=0;
	int a[101];
	
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf(" %d",&a[i]);
	}
	
	for(i=1;i<=n;i++){
		for(j=n;j>i;j--){
			if(a[j]>a[j-1]){
				sa=a[j]; a[j]=a[j-1]; a[j-1]=sa;
			}
		}
	}
	for(i=1;i<=n;i++){
		if(i%2==1){
			gap+=a[i];
		}else{
			gap-=a[i];
		}
	}
	
	printf("%d",gap);
	
	return 0;
}