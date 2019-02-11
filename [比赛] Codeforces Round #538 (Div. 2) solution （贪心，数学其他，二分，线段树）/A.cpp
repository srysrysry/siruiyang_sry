#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
inline int read(){
	int f=1,ans=0;char c;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
	return ans*f;
}
int x,y,z,a,b,c,ans;
int main(){
	x=read(),y=read(),z=read(),a=read(),b=read(),c=read();
	ans=a+b+c;
	if(a<x){printf("NO");return 0;}
	ans-=x;
	a-=x;
	if(a+b<y){printf("NO");return 0;}
	ans-=y;
	if(ans<z){printf("NO");return 0;}
	else{printf("YES");return 0;}
}
