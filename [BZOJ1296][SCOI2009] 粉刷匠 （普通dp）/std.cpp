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
const int MAXN=55;
const int Maxn=2501;
int f[MAXN][MAXN][Maxn][3],t,n,m,a[MAXN][MAXN];
char str[MAXN];
int main(){
    n=read(),m=read(),t=read();
    for(int i=1;i<=n;i++){
        scanf("%s",str+1);
        for(int j=1;j<=m;j++)a[i][j]=str[j]-'0';
    }f[0][m][0][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int k=1;k<=t;k++){
                if(j==1){
                    f[i][j][k][1]=max(f[i-1][m][k-1][0],f[i-1][m][k-1][1])+1;
                    f[i][j][k][0]=max(f[i-1][m][k-1][0],f[i-1][m][k-1][1]);
                }else{
                    if(a[i][j]==a[i][j-1]){
                        f[i][j][k][1]=f[i][j-1][k][1]+1;
                        f[i][j][k][0]=f[i][j-1][k][0];
                    }else{
                        f[i][j][k][1]=max(f[i][j-1][k][0],f[i][j-1][k-1][1])+1;
                        f[i][j][k][0]=max(f[i][j-1][k][1],f[i][j-1][k-1][0]);
                    }
                }
            }
        }
    }printf("%d\n",max(f[n][m][t][0],f[n][m][t][1]));
}
