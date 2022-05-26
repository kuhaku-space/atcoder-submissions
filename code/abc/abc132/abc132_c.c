#include <stdio.h>
#include <stdlib.h>

#define swap(type,x,y) do{type t=x; x=y; y=t;}while(0)

void sort(int a[],int left,int right){
	int pl=left;
	int pr=right;
	int x=a[(pl+pr)/2];

	do{
		while(a[pl]<x) pl++;
		while(a[pr]>x) pr--;
		if(pl<=pr){
			swap(int,a[pl],a[pr]);
			pl++;
			pr--;
		}
	}while(pl<=pr);
	if(left<pr) sort(a,left,pr);
	if(pl<right) sort(a,pl,right);
}

int main(void){
	int i,j;

  int n;

  scanf("%d",&n);

  int d[n+1];

  for(i=1;i<=n;i++){
    scanf("%d",&d[i]);
  }

  sort(d,1,n);

  printf("%d\n",d[n/2+1]-d[n/2]);

	return 0;
}
