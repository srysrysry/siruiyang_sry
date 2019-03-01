#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<climits>
#include<queue>
#define int long long
using namespace std;
inline int read(){
    int f=1,ans=0;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return f*ans;
}
const int MAXN=1000001;
struct node{
    int u,v,w,nex;
}x[MAXN<<1];
queue<int> que;
int deep[MAXN],head[MAXN],INF=LLONG_MAX,S,T,vis,ans,cnt,val[MAXN];
void add(int u,int v,int w){
    x[cnt].u=u,x[cnt].v=v,x[cnt].w=w,x[cnt].nex=head[u],head[u]=cnt++;
}
bool bfs(){
    memset(deep,127/3,sizeof(deep));
    int inf=deep[0];deep[S]=1;
    que.push(S);
    while(!que.empty()){
        int xx=que.front();que.pop();
        for(int i=head[xx];i!=-1;i=x[i].nex){
            if(deep[x[i].v]>deep[xx]+1&&x[i].w){
                deep[x[i].v]=deep[xx]+1;
                que.push(x[i].v);
            }
        }
    }return deep[T]!=inf;
}
int dfs(int u,int flow){
    if(u==T){ans+=flow;vis=1;return flow;}
    int used=0;
    for(int i=head[u];i!=-1;i=x[i].nex){
        if(deep[x[i].v]==deep[u]+1&&x[i].w){
            int slow=dfs(x[i].v,min(flow-used,x[i].w));used+=slow;
            x[i].w-=slow,x[i^1].w+=slow;
            if(flow==used) break;
        }
    }if(!used) deep[u]=-1;
    return used;
}
int dinic(){
    ans=0;
    while(bfs()){
        vis=1;
        while(vis){
            vis=0;
            dfs(S,INF);
        }
    }return ans;
}
int n,m,sum;
signed main(){
//	freopen("make.in","r",stdin);
    memset(head,-1,sizeof(head));
    n=read(),m=read();
    S=0,T=n+m+1;
    for(int i=1;i<=n;i++){
        val[i]=read(),add(i,T,val[i]),add(T,i,0);
    }
    for(int i=1;i<=m;i++){
        int u=read(),v=read(),cost=read();
        sum+=cost;
        add(i+n,u,INF),add(u,i+n,0);
        add(i+n,v,INF),add(v,i+n,0);;
        add(S,i+n,cost),add(i+n,S,0);
    }
    printf("%lld\n",sum-dinic());
    return 0;
}
