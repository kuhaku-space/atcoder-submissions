#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define swap(type,x,y) do{type t=x; x=y; y=t;}while(0)

void sort(long a[][2],long left,long right, long num){
	long pl=left;
	long pr=right;
	long x=a[(pl+pr)/2][num];
	
	do{
		while(a[pl][num]<x) pl++;
		while(a[pr][num]>x) pr--;
		if(pl<=pr){
			swap(long,a[pl][0],a[pr][0]);
			swap(long,a[pl][1],a[pr][1]);
			pl++;
			pr--;
		}
	}while(pl<=pr);
	if(left<pr) sort(a,left,pr,num);
	if(pl<right) sort(a,pl,right,num);
}

int main(void){
	long i,j,time=0,ans=0;
	
	long n;
	scanf("%ld",&n);
	
	long t[n+1][2];
	
	for(i=1;i<=n;i++){
		scanf("%ld%ld",&t[i][0],&t[i][1]);
	}
	
	sort(t,1,n,1);
	
	for(i=1;i<=n;i++){
		time+=t[i][0];
		if(time>t[i][1]){
			ans=1;
			break;
		}
	}
	
	if(ans==0){
		printf("Yes\n");
	}else{
		printf("No\n");
	}
	
	return 0;
}