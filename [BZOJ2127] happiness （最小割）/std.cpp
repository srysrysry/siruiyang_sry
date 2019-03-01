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
const int MAXN=1000001;
struct node{
    int u,v,w,nex;
}x[MAXN<<1];
queue<int> que;
int head[MAXN],cnt,INF=INT_MAX,S,T,deep[MAXN],ans,vis;
void add(int u,int v,int w){
    x[cnt].u=u,x[cnt].v=v,x[cnt].w=w,x[cnt].nex=head[u],head[u]=cnt++;
    swap(u,v),w=0;
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
int sum,n,m;
int Q(int x,int y){return (x-1)*m+y;}
int main(){
    memset(head,-1,sizeof(head));
    n=read(),m=read();S=0,T=n*m*5+1;
    int siz=n*m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int x=read();
            sum+=x;
            add(S,Q(i,j),x);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int x=read();
            sum+=x;
            add(Q(i,j),T,x);
        }
    }
    for(int i=1;i<n;i++){
        for(int j=1;j<=m;j++){
            int x=read();
            sum+=x;
            add(Q(i,j)+1*siz,Q(i,j),INF);
            add(Q(i,j)+1*siz,Q(i+1,j),INF);
            add(S,Q(i,j)+1*siz,x);
        }
    }
    for(int i=1;i<n;i++){
        for(int j=1;j<=m;j++){
            int x=read();
            sum+=x; 
            add(Q(i,j),Q(i,j)+2*siz,INF);
            add(Q(i+1,j),Q(i,j)+2*siz,INF);
            add(Q(i,j)+2*siz,T,x);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<m;j++){
            int x=read();
            sum+=x;
            add(Q(i,j)+3*siz,Q(i,j),INF);
            add(Q(i,j)+3*siz,Q(i,j+1),INF);
            add(S,Q(i,j)+3*siz,x);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<m;j++){
            int x=read();
            sum+=x;
            add(Q(i,j),Q(i,j)+4*siz,INF);
            add(Q(i,j+1),Q(i,j)+4*siz,INF);
            add(Q(i,j)+4*siz,T,x);
        }
    }
    printf("%d\n",sum-dinic());
}

