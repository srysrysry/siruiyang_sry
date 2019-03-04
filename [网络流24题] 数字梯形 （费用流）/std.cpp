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
queue<int> que;
const int MAXN=6001;
const int N=101;
struct node{
	int u,v,w,cost,nex;
}x[MAXN<<1];
int vis[MAXN],head[MAXN],INF=INT_MAX,S,T,cnt,dis[MAXN],cost;
void add(int u,int v,int cost,int w){
//	printf("u:%d v:%d cost:%d w:%d\n",u,v,cost,w);
	x[cnt].u=u,x[cnt].v=v,x[cnt].cost=cost,x[cnt].w=w,x[cnt].nex=head[u],head[u]=cnt++;swap(u,v);
	x[cnt].u=u,x[cnt].v=v,x[cnt].cost=-cost,x[cnt].w=0,x[cnt].nex=head[u],head[u]=cnt++;
}
bool spfa(){
	memset(vis,0,sizeof(vis));memset(dis,-127/3,sizeof(dis));
	int inf=dis[0];dis[S]=0;vis[S]=1;que.push(S);
	while(!que.empty()){
		int xx=que.front();que.pop();
		for(int i=head[xx];i!=-1;i=x[i].nex){
			if(x[i].w&&dis[x[i].v]<dis[xx]+x[i].cost){
				dis[x[i].v]=dis[xx]+x[i].cost;
				if(!vis[x[i].v]){
					vis[x[i].v]=1;
					que.push(x[i].v);
				}
			}
		}vis[xx]=0;
	}return dis[T]!=inf;
}
int dfs(int u,int flow){
	if(u==T) return flow;
	int used=0;vis[u]=1;
	for(int i=head[u];i!=-1;i=x[i].nex){
		if(dis[x[i].v]==dis[u]+x[i].cost&&x[i].w&&!vis[x[i].v]){
			int slow=dfs(x[i].v,min(flow-used,x[i].w));used+=slow;
			x[i].w-=slow,x[i^1].w+=slow;cost+=slow*x[i].cost;
			if(used==flow) break;
		}
	}vis[u]=0;
	if(!used) dis[u]=-1;
	return used;
}
int dinic(){
	int ans=0;
	while(spfa()){
		memset(vis,0,sizeof(vis));
		ans+=dfs(S,INF);
	}return ans;
}int m,n,H[N][N],Cnt,val[N][N];
int main(){
	memset(head,-1,sizeof(head));
	m=read(),n=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m+i-1;j++) H[i][j]=++H[0][0];
	Cnt=H[0][0];S=0,T=Cnt*2+1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m+i-1;j++){
			int x=read();val[i][j]=x;
			if(i==1) add(S,H[i][j],0,1);
			if(i==n) add(H[i][j]+Cnt,T,0,1);
			add(H[i][j],H[i][j]+Cnt,x,1);
			if(i+1<=n)add(H[i][j]+Cnt,H[i+1][j],0,1);
			if(i+1<=n)add(H[i][j]+Cnt,H[i+1][j+1],0,1);
		}
	}
    dinic();
    int Ans1=cost;
	printf("%d\n",Ans1);cost=0;
	memset(head,-1,sizeof(head)),cnt=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m+i-1;j++){
			int x=val[i][j];
			if(i==1) add(S,H[i][j],0,1);
			if(i==n) add(H[i][j]+Cnt,T,0,INF);
			add(H[i][j],H[i][j]+Cnt,x,INF);
			if(i+1<=n)add(H[i][j]+Cnt,H[i+1][j],0,1);
			if(i+1<=n)add(H[i][j]+Cnt,H[i+1][j+1],0,1);
		}
	}
	dinic();
	int Ans2=cost;
	printf("%d\n",Ans2); 
	cost=0;
	memset(head,-1,sizeof(head)),cnt=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m+i-1;j++){
			int x=val[i][j];
			if(i==1) add(S,H[i][j],0,1);
			if(i==n) add(H[i][j]+Cnt,T,0,INF);
			add(H[i][j],H[i][j]+Cnt,x,INF);
			if(i+1<=n)add(H[i][j]+Cnt,H[i+1][j],0,INF);
			if(i+1<=n)add(H[i][j]+Cnt,H[i+1][j+1],0,INF);
		}
	}dinic();
	int Ans3=cost;
	printf("%d\n",Ans3);
}/*
1 2
1
2 3
*/
