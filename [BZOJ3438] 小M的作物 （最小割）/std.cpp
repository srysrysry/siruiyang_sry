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
int n,sum,k;
int main(){
//	freopen("18.in","r",stdin);
    memset(head,-1,sizeof(head));
    n=read();T=3001;
    for(int i=1;i<=n;i++){
        int x=read();sum+=x;
        add(S,i,x);
    }
    for(int i=1;i<=n;i++){
        int x=read();sum+=x;
        add(i,T,x);
    }
    k=read();
    for(int i=1;i<=k;i++){
        int cnt=read();
        int c1=read(),c2=read();sum+=c1,sum+=c2;
        
        add(S,n+i,c1),add(n+k+i,T,c2);
        for(int j=1;j<=cnt;j++){
            int x=read();
            add(n+i,x,INF),add(x,n+k+i,INF);
        }
    }
    printf("%d\n",sum-dinic());
}

