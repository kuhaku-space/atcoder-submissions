#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

long long fgcm(long long a,long long b){
	long long ab;
	
	while(b!=0){
		a=a%b;
		ab=a; a=b; b=ab;
	}
	
	return a;
}

int main(void){
	long long na,nb,ans,gcm,lcm;
	
	long long a,b;
	
	long long c,d;
	
	scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
	
	if(c>=d){
		gcm=fgcm(c,d);
	}else{
		gcm=fgcm(d,c);
	}
	
	a--;
	
	lcm=c*d/gcm;
	
	nb=b-(b/c)-(b/d)+(b/lcm);
	na=a-(a/c)-(a/d)+(a/lcm);
	
	printf("%lld\n",nb-na);
	
	return 0;
}