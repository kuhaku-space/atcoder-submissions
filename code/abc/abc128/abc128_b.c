#include <stdio.h>
#include <string.h>

int main(void){
	int i,j,k,sign=0;
	int n;
	
	scanf("%d",&n);
	
	char s[n+1][11];
	int p[n+1],rank[n+1],min=0;
	
	for(i=0;i<=n;i++){
		for(j=1;j<=10;j++){
			s[i][0]='\n';
		}
	}
	for(i=0;i<=n;i++){
		rank[i]=0;
	}
	for(i=0;i<=9;i++){
		s[0][i]='z';
	}
	p[0]=0;
	
	for(i=1;i<=n;i++){
		scanf(" %s %d",s[i],&p[i]);
	}
	
	for(k=1;k<=n;k++){
			min=0;
		for(i=1;i<=n;i++){
			if(rank[i]!=0){
			}else{
				for(j=1;j<=10;j++){
					if(strcmp(s[i],s[min])==0){
						if(p[i]>p[min]){
							min=i;
						}
						break;
					}else if(strcmp(s[i],s[min])<0){
						min=i;
						break;
					}else if(strcmp(s[i],s[min])>0){
						break;
					}
				}
			}
		}
		rank[min]=1;
		printf("%d",min);
		if(k!=n){
			printf("\n");
		}
	}
	
	return 0;
}