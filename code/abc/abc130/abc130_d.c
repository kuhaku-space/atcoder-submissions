#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int main(void){
	long i,j,sum=0,sign=1;
	long long ans=0;
	
	long n,k;
	scanf("%ld%ld",&n,&k);
	
	long a[n+1];
	for(i=1;i<=n;i++){
		scanf("%ld",&a[i]);
	}
	
	for(i=1;i<=n;i++){
		for(j=sign;j<=n;j++){
			sum+=a[j];
			if(sum>=k){
				ans+=n-j+1;
				sign=j;
				sum-=a[i];
				break;
			}else{
				sign=j;
			}
		}
		sum-=a[sign];
	}
	
	printf("%lld\n",ans);
	
	return 0;
}