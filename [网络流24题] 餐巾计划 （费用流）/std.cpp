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
const int NM=5001;
const int MAXN=100001;
struct node{
	int u,v,w,dis,nex;
}x[MAXN<<2];
queue<int> que;
int head[NM],cnt,cost,dis[NM],INF=INT_MAX,S,T,vis[NM];
void add(int u,int v,int dis,int w){
//	printf("u:%d v:%d cost:%d w:%d\n",u,v,dis,w);
	x[cnt].u=u,x[cnt].v=v,x[cnt].w=w,x[cnt].dis=dis,x[cnt].nex=head[u],head[u]=cnt++;swap(u,v);
	x[cnt].u=u,x[cnt].v=v,x[cnt].w=0,x[cnt].dis=-dis,x[cnt].nex=head[u],head[u]=cnt++;
}
bool spfa(){
	memset(vis,0,sizeof(vis));
	memset(dis,127/3,sizeof(dis));int inf=dis[0];dis[S]=0;
	que.push(S);vis[S]=1;
	while(!que.empty()){
		int xx=que.front();que.pop();vis[xx]=0;
		for(int i=head[xx];i!=-1;i=x[i].nex){
			if(x[i].w&&dis[x[i].v]>dis[xx]+x[i].dis){
				dis[x[i].v]=dis[xx]+x[i].dis;
				if(!vis[x[i].v]){
					vis[x[i].v]=1;
					que.push(x[i].v);
				}
			}
		}
	}return dis[T]!=inf;
}
int dfs(int u,int flow){
	if(u==T) return flow;
	int used=0;vis[u]=1;
	for(int i=head[u];i!=-1;i=x[i].nex){
		if(x[i].w&&dis[x[i].v]==dis[u]+x[i].dis&&!vis[x[i].v]){
			int slow=dfs(x[i].v,min(flow-used,x[i].w));used+=slow;
			x[i].w-=slow,x[i^1].w+=slow;
			cost+=x[i].dis*slow;
			if(used==flow) break;
		}
	}if(!used) dis[u]=-1;
	vis[u]=0;
	return used;
}
int dinic(){
	int ans=0;
	while(spfa()) {
		memset(vis,0,sizeof(vis));
		ans+=dfs(S,INF);
	}
	return ans;
}
int N,r[MAXN],p,m,f,s,n;
signed main(){
//	freopen("7.in","r",stdin);
	memset(head,-1,sizeof(head));
	N=read();S=0,T=2*N+1;
	p=read(),m=read(),f=read(),n=read(),s=read();
	for(int i=1;i<=N;i++) r[i]=read();
	for(int i=1;i<=N;i++){
		/*每个点的供给 */
		add(S,i,p,INF);
		/*给予答案*/
		add(i,T,0,r[i]);
		/*给与垃圾*/
		add(S,i+N,0,r[i]);
		/*快洗*/
		if(i+m<=N)add(i+N,i+m,f,INF);
		/*慢洗*/
		if(i+n<=N)add(i+N,i+n,s,INF);
		/*给下个垃圾桶*/
		if(i+1<=N)add(i+N,i+N+1,0,INF); 
	}
	int Ans=dinic();
//	printf("%d\n",Ans);
	printf("%lld\n",cost);
}
