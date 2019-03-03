#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<climits>
using namespace std;
inline int read(){
    int f=1,ans=0;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return f*ans;
}
queue<int> que;
const int MAXN=60001;
struct node{
    int u,v,w,nex;
}x[MAXN<<1];
int n,m,S,T,ans,vis,head[MAXN],cnt,deep[MAXN];
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
    if(u==T){vis=1;ans+=flow;return flow;}
    int used=0;
    for(int i=head[u];i!=-1;i=x[i].nex){
        if(deep[x[i].v]==deep[u]+1&&x[i].w){
            int slow=dfs(x[i].v,min(flow-used,x[i].w));used+=slow;
            x[i].w-=slow,x[i^1].w+=slow;
            if(slow==flow) break;
        }
    }if(!used) deep[u]=-1;
    return used;
}
int dfn[MAXN],scc[MAXN],low[MAXN],sta[MAXN],tot,num,Scc;
int dinic(){
    ans=0;
    while(bfs()){
        vis=1;
        while(vis){
            vis=0;
            dfs(S,INT_MAX);
        } 
    }return ans;
}
void tarjan(int u,int fath){
    low[u]=dfn[u]=++num,sta[++tot]=u;
    for(int i=head[u];i!=-1;i=x[i].nex){
        if(!x[i].w) continue;
        if(!dfn[x[i].v]){
            tarjan(x[i].v,u);
            low[u]=min(low[u],low[x[i].v]);
        }else if(!scc[x[i].v]) low[u]=min(low[u],low[x[i].v]);
    }
    if(dfn[u]==low[u]){
        scc[u]=++Scc;
        while(sta[tot]!=u){
            scc[sta[tot]]=scc[u];
            tot--;
        }tot--;
    }return;
}
int main(){
//	freopen("2.in","r",stdin);
    memset(head,-1,sizeof(head));
    n=read(),m=read(),S=read(),T=read();
    for(int i=1;i<=m;i++){
        int u=read(),v=read(),w=read();
        add(u,v,w),add(v,u,0);
    }
    dinic();
    for(int i=1;i<=n;i++) 
        if(!dfn[i]) tarjan(i,0);
//	for(int i=0;i<cnt;i++) printf("u:%d v:%d w:%d\n",x[i].u,x[i].v,x[i].w);
//	for(int i=1;i<=n;i++) printf("low(%d):%d\n",i,low[i]);
    for(int i=0;i<cnt;i+=2){
        if(x[i].w){printf("0 0\n");continue;}
        if(scc[x[i].u]!=scc[x[i].v]) printf("1 ");
        else printf("0 ");
        if(scc[S]==scc[x[i].u]&&scc[T]==scc[x[i].v]) printf("1\n");
        else printf("0\n"); 
    } 
}

