#include <stdio.h>

int main(){
	int i,j=0;
	char k[15];
	
	scanf("%s",k);
	
	for(i=0;i<=14;i++){
		if(k[i]=='x'){
			j++;
		}
	}
	
	if(j>=8){
		printf("NO\n");
	}else{
		printf("YES\n");
	}
	
	return 0;
}