#include <stdio.h>

int main(){
	int i,k=0,sign=0;
	char s[100001];
	
	scanf("%s",s);
	
	for(i=0;i<=100000;i++){
		if(s[i]=='d'&&s[i+1]=='r'&&s[i+2]=='e'&&s[i+3]=='a'&&s[i+4]=='m'){
			if(s[i+5]=='e'&&s[i+6]=='r'){
				if(s[i+7]=='a'){
					i+=4;
				}else{
					i+=6;
				}
			}else{
				i+=4;
			}
		}else if(s[i]=='e'&&s[i+1]=='r'&&s[i+2]=='a'&&s[i+3]=='s'&&s[i+4]=='e'){
			if(s[i+5]=='r'){
				i+=5;
			}else{
				i+=4;
			}
		}else if(s[i]=='\0'){
			break;
		}else{
			k=1;
			break;
		}
	}
	
	if(k==0){
		printf("YES\n");
	}else{
		printf("NO\n");
	}
	
	return 0;
}