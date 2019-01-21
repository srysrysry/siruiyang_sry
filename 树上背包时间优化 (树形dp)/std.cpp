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
const int N=103;
int head[N],f[N][N],size[N],val[N],n,m,cnt;
struct node{
    int u,v,w,nex;
}x[N<<1];
void add(int u,int v){
    x[cnt].u=u,x[cnt].v=v,x[cnt].nex=head[u],head[u]=cnt++;
}
void dfs(int u,int fath){
    f[u][1]=val[u];
    size[u]=1;
    for(int i=head[u];i!=-1;i=x[i].nex){
    	if(x[i].v==fath) continue;
        dfs(x[i].v,u);
        for(int w1=min(m+1,size[u]+size[x[i].v]);w1>=1;w1--)
            for(int w2=max(0,w1-size[u]);w2<w1&&w2<=size[x[i].v];w2++) f[u][w1]=max(f[u][w1],f[u][w1-w2]+f[x[i].v][w2]);
        size[u]+=size[x[i].v];
    }
    return;
}
int main(){
    memset(f,-127/3,sizeof(f));
    memset(head,-1,sizeof(head));
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        int u=read(),v=i,W=read();
        val[i]=W;add(u,v);
    }
    dfs(0,-1);
    printf("%d\n",f[0][m+1]);
}
