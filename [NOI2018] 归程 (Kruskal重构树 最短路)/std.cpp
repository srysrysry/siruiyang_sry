#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;
inline int read(){
	int f=1,ans=0;char c;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
	return ans*f;
}
const int N=1200001;
const int M=1400001;
struct node{
	int u,v,len,h;
}k[M];
int cnt,head[N];
struct Edge{
	int u,v,w,nex;
}x[M<<1];
void add(int u,int v,int w){
	x[cnt].u=u,x[cnt].v=v,x[cnt].w=w,x[cnt].nex=head[u],head[u]=cnt++;
}
int n,m,T,dis[N],vis[N],f[N];
priority_queue<pair<int,int> > que;
void dijkstra(){
	memset(dis,127/3,sizeof(dis));
	dis[1]=0;
	que.push(make_pair(0,1));
	while(!que.empty()){
		int xx=que.top().second;que.pop();
		if(vis[xx]) continue;
		vis[xx]=1;
		for(int i=head[xx];i!=-1;i=x[i].nex){
			if(dis[x[i].v]>dis[xx]+x[i].w){
				dis[x[i].v]=dis[xx]+x[i].w;
				que.push(make_pair(-dis[x[i].v],x[i].v));
			}
		}
	}return;
}
bool cmp(node x1,node x2){return x1.h>x2.h;}
int find(int x){
	if(f[x]==x) return x;
	return f[x]=find(f[x]);
}
int F[N][23],Minn[N],val[N],deep[N];
void dfs(int u,int fath){
	deep[u]=deep[fath]+1;vis[u]=1;
	for(int i=1;(1<<i)<=deep[fath];i++) F[u][i]=F[F[u][i-1]][i-1];
	 for(int i=head[u];i!=-1;i=x[i].nex) {
	 	dfs(x[i].v,u);
	 	Minn[u]=min(Minn[u],Minn[x[i].v]);
	 }
}
int query(int u,int h){
	for(int i=22;i>=0;i--){
		if(F[u][i]&&val[F[u][i]]>h) u=F[u][i];
	}
	return Minn[u];
} 
int main(){
//	freopen("return.in","r",stdin);
//	freopen("return.out","w",stdout);
	T=read();
	while(T--){
		memset(Minn,127/3,sizeof(Minn)),memset(val,127/3,sizeof(val)),memset(F,0,sizeof(F));
		memset(head,-1,sizeof(head)),memset(vis,0,sizeof(vis)),cnt=0;
		n=read(),m=read();
		for(int i=1;i<=m;i++){
		    int u=read(),v=read(),len=read(),h=read();
		    k[i].u=u,k[i].v=v,k[i].len=len,k[i].h=h;
		    add(u,v,len),add(v,u,len);
		}
		dijkstra();
		sort(k+1,k+m+1,cmp);
		memset(head,-1,sizeof(head)),cnt=0;
		int Num=n;
		for(int i=1;i<=2*n-1;i++) f[i]=i;
		for(int i=1;i<=m;i++){
			int t1=find(k[i].u),t2=find(k[i].v);
			if(t1==t2) continue;
			if(t1<=n) Minn[t1]=dis[t1];
			if(t2<=n) Minn[t2]=dis[t2];
			++Num;
			f[t1]=Num,f[t2]=Num;
			val[Num]=k[i].h;
			F[t1][0]=F[t2][0]=Num;
			add(Num,t1,0),add(Num,t2,0);
		}
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=Num;i++) if(!vis[find(i)]) dfs(find(i),0);
		int lastans=0;
		int Q=read(),K=read(),S=read();
		for(int i=1;i<=Q;i++){
			int u=read(),h=read();
			u=(u+K*lastans-1)%n+1,h=(h+K*lastans)%(S+1);
			printf("%d\n",lastans=query(u,h));
		}
	}
}
