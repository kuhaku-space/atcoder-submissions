#include <stdio.h>

int main(void){
	int i,j,ans=0;

  int n;

  scanf("%d",&n);

  int p[n+1];

  for(i=1;i<=n;i++){
    scanf("%d",&p[i]);
  }

  for(i=1;i<n-1;i++){
    if(p[i]<p[i+1]&&p[i+1]<p[i+2]){
      ans++;
    }else if(p[i]>p[i+1]&&p[i+1]>p[i+2]){
      ans++;
    }
  }

  printf("%d\n",ans);

	return 0;
}
