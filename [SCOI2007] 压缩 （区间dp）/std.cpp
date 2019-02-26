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
const int MAXN=61;
int f[MAXN][MAXN][3],len;
char str[MAXN];
bool access(int l,int r){
    if((r-l+1)%2!=0) return 0;
    int len=(r-l+1)/2;
    for(int i=1;i<=len;i++)
         if(str[l+i-1]!=str[((l+r+1)>>1)+i-1]) return 0;
    return 1;
}
int main(){
    memset(f,127/3,sizeof(f));
    scanf("%s",str+1);
    len=strlen(str+1);
    for(int i=1;i<=len;i++) f[i][i][1]=2,f[i][i][0]=2;
    for(int l=1;l<len;l++)
         for(int i=1;i+l<=len;i++){
            int j=i+l;
            for(int k=i;k<j;k++) f[i][j][0]=min(f[i][j][0],min(f[i][k][0],f[i][k][1])+min(f[k+1][j][1],f[k+1][j][0]));
            for(int k=i;k<j;k++) f[i][j][1]=min(f[i][j][1],f[i][k][1]+(j-k));
            if(access(i,j)) f[i][j][1]=min(f[i][j][1],f[i][(i+j)>>1][1]+1);
            //printf("f(%d,%d,0):%d f(%d,%d,1):%d\n",i,j,f[i][j][0],i,j,f[i][j][1]);
         }
    int ans=min(f[1][len][1]-1,f[1][len][0]-1);
    printf("%d\n",ans);
    return 0;
}
