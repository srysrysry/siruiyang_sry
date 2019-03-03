#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<climits>
#include<vector> 
using namespace std;
inline int read(){
    int f=1,ans=0;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return f*ans;
}
const int MAXN=500001;
const int N=1001;
queue<int> que;
vector<int> ve[N];
struct node{
    int u,v,w,nex;
}x[MAXN<<2]; 
int head[MAXN],cnt,sum;
void add(int u,int v,int w){
//	printf("u:%d v:%d w:%d\n",u,v,w);
    x[cnt].u=u,x[cnt].v=v,x[cnt].w=w,x[cnt].nex=head[u],head[u]=cnt++;
}
int S,T,INF=INT_MAX,n,m,ans,val[MAXN],deep[MAXN],vis,in[MAXN],Vis[MAXN];
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
            if(used==flow) break;
        }
    } if(!used) deep[u]=-1;
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
int Q(int x,int y){return (x-1)*m+y;}
void topsort(){
    for(int i=1;i<=n*m;i++){
        if(!in[i]) que.push(i);
    }
    while(!que.empty()){
        int xx=que.front();que.pop();Vis[xx]=1;
        for(int i=head[xx];i!=-1;i=x[i].nex){
            in[x[i].v]--;
            if(!in[x[i].v]) que.push(x[i].v);
        }
    }return;
}
int main(){
//	freopen("1.in","r",stdin);
    memset(head,-1,sizeof(head));
    n=read(),m=read();S=0,T=n*m+1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            val[Q(i,j)]=read();
            int cnt=read();
            for(int k=0;k<cnt;k++){
                int x1=read()+1,y1=read()+1;
                in[Q(x1,y1)]++;
                add(Q(i,j),Q(x1,y1),0);
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<m;j++) add(Q(i,j+1),Q(i,j),0),in[Q(i,j)]++;
    }
//	for(int i=1;i<=n*m;i++) printf("in(%d):%d\n",i,in[i]);
    topsort();
    for(int i=0;i<cnt;i++)
        ve[x[i].u].push_back(x[i].v);
    memset(head,-1,sizeof(head)),cnt=0;
//	for(int i=1;i<=n*m;i++) printf("vis(%d):%d\n",i,Vis[i]);
//	return 0;
    for(int i=1;i<=n*m;i++){
        if(!Vis[i]) continue;
        int siz=ve[i].size();
        for(int j=0;j<siz;j++){
            int u=ve[i][j],v=i;
            if(!Vis[u]) continue;
            add(u,v,INF),add(v,u,0);
        }
        if(val[i]>0){
            add(S,i,val[i]),add(i,S,0);
            sum+=val[i];
        }
        if(val[i]<0) add(i,T,-val[i]),add(T,i,0); 
    }
    printf("%d\n",sum-dinic());
}

