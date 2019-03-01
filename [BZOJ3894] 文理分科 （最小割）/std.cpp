#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<climits>
#include<queue>
using namespace std;
inline int read(){
    int f=1,ans=0;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return f*ans;
}
const int MAXN=900001;
queue<int> que;
struct node{
    int u,v,w,nex;
}x[MAXN<<3];
int head[MAXN],cnt,vis,ans,deep[MAXN],S,T,INF=INT_MAX;
int dx[5]={1,-1,0,0,0};
int dy[5]={0,0,1,-1,0};
void add(int u,int v,int w){
//	printf("u:%d v:%d w:%d\n",u,v,w);
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
int Q(int x,int y){return (x-1)*m+y;}
int main(){
//	freopen("15.in","r",stdin);
    memset(head,-1,sizeof(head));
    n=read(),m=read();S=0,T=n*m*3+1; 
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int x=read();sum+=x;
            add(S,Q(i,j),x),add(Q(i,j),S,0);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int x=read();sum+=x;
            add(Q(i,j),T,x),add(T,Q(i,j),0); 
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int x=read();sum+=x;
            add(S,Q(i,j)+n*m,x),add(Q(i,j)+n*m,S,0);
            for(int k=0;k<5;k++){
                int bx=dx[k]+i,by=dy[k]+j;
                if(bx>=1&&bx<=n&&by>=1&&by<=m){
                    add(Q(i,j)+n*m,Q(bx,by),INF);
                    add(Q(bx,by),Q(i,j)+n*m,0);
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int x=read();sum+=x;
            add(Q(i,j)+2*n*m,T,x),add(T,2*n*m+Q(i,j),0);
            for(int k=0;k<5;k++){
                int bx=dx[k]+i,by=dy[k]+j;
                if(bx>=1&&bx<=n&&by>=1&&by<=m){
                    add(Q(bx,by),Q(i,j)+2*n*m,INF);
                    add(Q(i,j)+2*n*m,Q(bx,by),0);
                }
            }
        }
    }printf("%d\n",sum-dinic());
}

