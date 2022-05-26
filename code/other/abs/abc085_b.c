#include <stdio.h>

int main(){
	int n,i,j,k,ans=0;
	int d[101];
	
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		k=0;
		scanf("%d",&d[i]);
		for(j=1;j<i;j++){
			if(d[i]==d[j]){
				k=1;
			}
		}
		if(k==0){
			ans++;
		}
	}
	
	printf("%d\n",ans);
	
	return 0;
}