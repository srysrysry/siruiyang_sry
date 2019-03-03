#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
inline int read(){
	int f=1,ans=0;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
	return f*ans;
}
const int MAXN=1001;
int n,f[MAXN][MAXN],cur,B,Max;
int main(){
	n=read(),B=read(),Max=read();
	f[0][B]=1;
	for(int i=1;i<=n;i++){
		cur^=1;
		int x=read();
		for(int j=Max;j>=x;j--) f[cur][j]=f[cur^1][j-x];
		for(int j=Max-x;j>=0;j--) f[cur][j]=max(f[cur][j],f[cur^1][j+x]);
	}
	for(int i=Max;i>=0;i--){
		if(f[cur][i]){printf("%d\n",i);return 0;}
	}printf("-1");return 0;
}

