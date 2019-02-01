#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define int long long
using namespace std;
inline int read(){
    int f=1,ans=0;char c;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return ans*f;
}
const int N=200011;
int cnt,d1[N],d2[N],d3[N],head[N],n,siz[N];
/*d1到叶子节点最长路径*/
/*d2为除掉一个子树的最长路径*/
/*d3为下界*/
struct node{
    int u,v,nex;
}x[N<<1];
void add(int u,int v){
    x[cnt].u=u,x[cnt].v=v,x[cnt].nex=head[u],head[u]=cnt++;
}
int son[N],sum;
char str[N];
void dfs1(int f,int fath){
    if(str[f]=='1') siz[f]=1,d3[f]=0,sum++;
    for(int i=head[f];i!=-1;i=x[i].nex){
        if(x[i].v==fath) continue;
        dfs1(x[i].v,f);
        if(d1[x[i].v]+1>=d1[f]) son[f]=x[i].v,d2[f]=d1[f],d1[f]=d1[x[i].v]+1;
        else if(d1[x[i].v]+1>=d2[f]) d2[f]=d1[x[i].v]+1;
        if(siz[x[i].v]) d3[f]=min(d3[f],d1[x[i].v]+1);
        siz[f]+=siz[x[i].v];
    }return; 
}
void dfs2(int f,int fath,int v){
    int nowv;
    for(int i=head[f];i!=-1;i=x[i].nex){
        if(x[i].v==fath) continue;
        if(son[f]==x[i].v) nowv=max(v,d2[f])+1;
        else nowv=max(v,d1[f])+1;
        if(nowv>=d1[x[i].v]) d2[x[i].v]=d1[x[i].v],d1[x[i].v]=nowv;
        else if(nowv>d2[x[i].v]) d2[x[i].v]=nowv;
        if(sum-siz[x[i].v]) d3[x[i].v]=min(d3[x[i].v],nowv);
        dfs2(x[i].v,f,nowv);
    }
}int ans;
signed main(){
    memset(head,-1,sizeof(head));
    n=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        add(u,v),add(v,u);
    }
    scanf("%s",str+1);
    memset(d3,127,sizeof(d3));
    dfs1(1,0); 
    dfs2(1,0,0);
    for(int i=1;i<=n;i++){
        if(str[i]=='1') ans+=max(min(d1[i],d2[i]+2),0LL);
        else ans+=max(min(d1[i],d2[i]+2)-d3[i],0LL);
    }printf("%lld\n",ans+1);
}

