#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int main(void){
	int i,j;
	
	int s;
	
	scanf("%d",&s);
	
	int a,b,c,d;
	
	a=s%10;
	s/=10;
	b=s%10;
	s/=10;
	c=s%10;
	s/=10;
	d=s;
	
	if(a==b||b==c||c==d){
		printf("Bad\n");
	}else{
		printf("Good\n");
	}
	
	return 0;
}