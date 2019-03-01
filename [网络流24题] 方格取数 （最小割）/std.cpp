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
const int N=31;
const int MAXN=100001;
struct node{
    int u,v,w,nex;
}x[MAXN<<1];
int sum,S,T,head[MAXN],cnt,deep[MAXN],ans,vis,n,m,a[N][N],M[N][N],INF=INT_MAX;
int bx[4]={0,0,1,-1};
int by[4]={1,-1,0,0};
queue<int> que;
void add(int u,int v,int w){
    x[cnt].u=u,x[cnt].v=v,x[cnt].w=w,x[cnt].nex=head[u],head[u]=cnt++;
}
void gao(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(j==1) M[i][j]=1-M[i-1][j];
            else M[i][j]=1-M[i][j-1];
        }
    }return;
}
int Q(int x,int y){return (x-1)*m+y;}
bool bfs(){
    memset(deep,127/3,sizeof(deep));
    int inf=deep[0];
    deep[S]=1;que.push(S);
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
            int slow=dfs(x[i].v,min(flow-used,x[i].w));
            used+=slow;
            x[i].w-=slow,x[i^1].w+=slow;
            if(slow==flow) break;
        }
    } if(!used) deep[u]=-1;
    return used;
}
int dinic(){
    ans=0;
    while(bfs()){
        vis=1;
        while(vis){
            dfs(S,INF);
            vis=0;
        }
    }
    return ans;
}
void build(){
    S=0,T=n*m+1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(M[i][j]&1){
                add(S,Q(i,j),a[i][j]);
                add(Q(i,j),S,0);
            }else{
                add(Q(i,j),T,a[i][j]);
                add(T,Q(i,j),0); 
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(!M[i][j]) continue;
            for(int k=0;k<4;k++){
                int dx=i+bx[k],dy=j+by[k];
                if(dx>=1&&dx<=n&&dy>=1&&dy<=m){
                    add(Q(i,j),Q(dx,dy),INF);
                    add(Q(dx,dy),Q(i,j),0);
                }
            }
        }
    }
}
int main(){
    memset(head,-1,sizeof(head));
    n=read(),m=read();
    gao();
    for(int i=1;i<=n;i++)
         for(int j=1;j<=m;j++) a[i][j]=read(),sum+=a[i][j];
    build();
    printf("%d\n",sum-dinic());
}
