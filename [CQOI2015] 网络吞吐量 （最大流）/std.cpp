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
priority_queue<pair<int,int> > Que;
queue<int> que;
int n,m,vis[MAXN],dis[MAXN],deep[MAXN],head[MAXN],ans,cnt,S,T,inf;
struct node{
    int u,v,w,nex;
}x[MAXN<<1],k[MAXN<<1];
int A[MAXN],Vis;
void add(int u,int v,int w){
    x[cnt].u=u,x[cnt].v=v,x[cnt].w=w,x[cnt].nex=head[u],head[u]=cnt++;
}
void dijkstra(){
    memset(dis,127,sizeof(dis));
    dis[1]=0;
    Que.push(make_pair(0,1));
    while(!Que.empty()){
        int xx=Que.top().second;Que.pop();
        if(vis[xx]) continue;
        vis[xx]=1;
        for(int i=head[xx];i!=-1;i=x[i].nex){
            if(dis[x[i].v]>dis[xx]+x[i].w){
                dis[x[i].v]=dis[xx]+x[i].w;
                Que.push(make_pair(-dis[x[i].v],x[i].v));
            }
        }
    }return;
}
bool bfs(){
    memset(deep,127,sizeof(deep));
    inf=deep[0];deep[S]=1;
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
    if(u==T){Vis=1;ans+=flow;return flow;}
    int used=0;
    for(int i=head[u];i!=-1;i=x[i].nex){
        if(deep[x[i].v]==deep[u]+1&&x[i].w){
            int slow=dfs(x[i].v,min(flow-used,x[i].w));
            used+=slow;
//          exit(0);
            x[i].w-=slow,x[i^1].w+=slow;
            if(flow==used) break; 
        }
    }
    if(!used) deep[u]=-1; 
    return used;
}int tot;
int dinic(){
    ans=0;
    while(bfs()){
        Vis=1;
        while(Vis){
            Vis=0;
            dfs(S,LLONG_MAX);
        }
    }return ans;
}
signed main(){
//  freopen("network3.in","r",stdin);
//  freopen("4.out","w",stdout);
    memset(head,-1,sizeof(head));
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u=read(),v=read(),w=read();
        add(u,v,w),add(v,u,w);
    }
    dijkstra();
    for(int i=1;i<=n;i++) A[i]=read();
    for(int i=0;i<cnt;i++) k[i]=x[i];
    memset(head,-1,sizeof(head));
    int Cnt=cnt;cnt=0;
    A[1]=A[n]=LLONG_MAX; S=0,T=2*n+1;
//  for(int i=1;i<=n;i++) printf("%d\n",A[i]);
    for(int i=0;i<Cnt;i++)
        if(dis[k[i].u]+k[i].w==dis[k[i].v]) add(k[i].u+n,k[i].v,LLONG_MAX),add(k[i].v,k[i].u+n,0);
//  printf("S:%d T:%d\n",S,T);
    for(int i=1;i<=n;i++) add(i,i+n,A[i]),add(i+n,i,0);
    add(S,1,LLONG_MAX),add(1,S,0);
    add(2*n,T,LLONG_MAX),add(T,2*n,0);
//  exit(0);
    printf("%lld\n",dinic());
}
