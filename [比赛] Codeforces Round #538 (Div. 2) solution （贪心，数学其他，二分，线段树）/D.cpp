
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
const int MAXN=5001;
int f[MAXN][MAXN],n,col[MAXN];
int main(){
	n=read();
	for(int i=1;i<=n;i++) col[i]=read();
	memset(f,127/3,sizeof(f));
	for(int i=1;i<=n;i++) f[i][i]=0;
	for(int len=2;len<=n;len++){
		for(int i=1;i+len-1<=n;i++){
			int j=i+len-1;
			if(col[i]==col[j]) f[i][j]=min(f[i][j],f[i+1][j-1]+1);
			if(col[i]==col[i+1]) f[i][j]=min(f[i][j],f[i+1][j]);
			else f[i][j]=min(f[i][j],f[i+1][j]+1);
			if(col[j]==col[j-1]) f[i][j]=min(f[i][j],f[i][j-1]);
			else f[i][j]=min(f[i][j],f[i][j-1]+1);
		}
    }printf("%d\n",f[1][n]);
}
