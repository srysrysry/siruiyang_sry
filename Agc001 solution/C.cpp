#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<climits>
using namespace std;
inline int read(){
    int f=1,ans=0;char c;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return ans*f;
}
const int N=2001;
int deep[N],n,k,head[N],cnt;
struct node{
    int u,v,nex;
}x[N<<1];
void add(int u,int v){
    x[cnt].u=u,x[cnt].v=v,x[cnt].nex=head[u],head[u]=cnt++;
}
int ans,minn;
void dfs(int f,int fath){
    deep[f]=deep[fath]+1;
    if(deep[f]>(k/2)) ans++;
    for(int i=head[f];i!=-1;i=x[i].nex){
        if(x[i].v==fath) continue;
        dfs(x[i].v,f);
    }return;
}
int main(){
    memset(head,-1,sizeof(head));
    n=read(),k=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        add(u,v),add(v,u);
    }
    if(k&1){
        ans=0,minn=INT_MAX;
        for(int u=1;u<=n;u++){
            for(int i=head[u];i!=-1;i=x[i].nex){
                ans=0;
                int v=x[i].v;
                deep[v]=-1;
                dfs(u,v);
                deep[u]=-1;
                dfs(v,u);
                minn=min(minn,ans);
            }
        }
    }else{
        ans=0,minn=INT_MAX;
        for(int u=1;u<=n;u++){
            ans=0;
            deep[0]=-1;
            dfs(u,0);
            minn=min(minn,ans);
        }
    }printf("%d\n",minn);
}

