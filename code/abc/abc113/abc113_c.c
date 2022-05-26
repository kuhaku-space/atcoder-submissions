#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define swap(type,x,y) do{type t=x; x=y; y=t;}while(0)

void quick(int a[][4],int left,int right,int num){
	int i;
	int pl=left;
	int pr=right;
	int x=a[(pl+pr)/2][num];
	
	do{
		while(a[pl][num]<x) pl++;
		while(a[pr][num]>x) pr--;
		if(pl<=pr){
			for(i=0;i<=3;i++){
				swap(int,a[pl][i],a[pr][i]);
			}
			pl++;
			pr--;
		}
	}while(pl<=pr);
	if(left<pr) quick(a,left,pr,num);
	if(pl<right) quick(a,pl,right,num);
}

int main(void){
	int i,j;
	
	int n,m;
	scanf("%d%d",&n,&m);
	
	int b[n+1];
	for(i=1;i<=n;i++){
		b[i]=1;
	}
	
	int a[m+1][4];
	for(i=1;i<=m;i++){
		scanf("%d%d",&a[i][1],&a[i][2]);
		a[i][0]=i;
	}

	quick(a,1,m,2);
	
	for(i=1;i<=m;i++){
		a[i][3]=b[a[i][1]];
		b[a[i][1]]++;
	}
	
	quick(a,1,m,0);
	
	for(i=1;i<=m;i++){
		printf("%06d%06d\n",a[i][1],a[i][3]);
	}
	
	return 0;
}