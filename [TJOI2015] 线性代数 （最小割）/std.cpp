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
const int MAXN=501; 
queue<int> que;
int n; 
int b[MAXN][MAXN],INF=INT_MAX,c[MAXN<<8],deep[MAXN<<12],S,T;
struct node{
    int u,v,w,nex;
}x[MAXN<<12];
int head[MAXN<<12],cnt,vis,ans;
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
}int sum;
int Q(int x,int y){return (x-1)*n+y+n;}
int main(){
//	freopen("algebra9.in","r",stdin);
//	freopen("12.out","w",stdout);
    memset(head,-1,sizeof(head));
    n=read();T=n*n+n+1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) b[i][j]=read(),sum+=b[i][j];
    for(int i=1;i<=n;i++) c[i]=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            add(S,Q(i,j),b[i][j]),add(Q(i,j),S,0);
            add(Q(i,j),i,INF),add(i,Q(i,j),0);
            add(Q(i,j),j,INF),add(j,Q(i,j),0);;		
        }
    }
    for(int i=1;i<=n;i++) add(i,T,c[i]),add(T,i,0);
    printf("%d\n",sum-dinic());
}

