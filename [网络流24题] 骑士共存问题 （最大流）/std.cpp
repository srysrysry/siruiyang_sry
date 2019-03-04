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
const int MAXN=400001;
const int N=201;
struct node{
	int u,v,w,nex;
}x[MAXN<<2];
int M[N][N];
int head[MAXN],cnt;
void add(int u,int v,int w){
	x[cnt].u=u,x[cnt].v=v,x[cnt].w=w,x[cnt].nex=head[u],head[u]=cnt++;swap(u,v);
	x[cnt].u=u,x[cnt].v=v,x[cnt].w=0,x[cnt].nex=head[u],head[u]=cnt++;
}
queue<int> que;
int dis[MAXN],S,T;
bool bfs(){
	memset(dis,127/3,sizeof(dis));int inf=dis[0];
	dis[S]=1;que.push(S);
	while(!que.empty()){
		int xx=que.front();que.pop();
		for(int i=head[xx];i!=-1;i=x[i].nex){
			if(dis[x[i].v]>dis[xx]+1&&x[i].w){
				dis[x[i].v]=dis[xx]+1;
				que.push(x[i].v);
			}
		}
	} return dis[T]!=inf;
}
int dfs(int u,int flow){
	if(u==T) return flow;
	int used=0;
	for(int i=head[u];i!=-1;i=x[i].nex){
		if(dis[x[i].v]==dis[u]+1&&x[i].w){
			int slow=dfs(x[i].v,min(flow-used,x[i].w));used+=slow;
			x[i].w-=slow,x[i^1].w+=slow;
			if(used==flow) break;
		}
	}if(!used) dis[u]=-1;
	return used;
}
int n,m,L[N][N];
int dinic(){
	int ans=0;
	while(bfs()) ans+=dfs(S,INT_MAX);
	return ans;
}
void gao(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(j==1) M[i][j]=1-M[i-1][j];
			else M[i][j]=1-M[i][j-1];
		}
	}return;
}
int Q(int x,int y){return (x-1)*n+y;}
int bx[8]={-1,-1,1,1,2,2,-2,-2};
int by[8]={-2,2,-2,2,1,-1,1,-1}; 
int main(){
//	freopen("8.in","r",stdin);
	n=read(),m=read();T=N*N+1; 
	memset(head,-1,sizeof(head));
	gao();
	for(int i=1;i<=m;i++){int x=read(),y=read();L[x][y]=1;}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(M[i][j]&&!L[i][j]){
				for(int k=0;k<8;k++){
					int dx=i+bx[k],dy=j+by[k];
					if(dx>=1&&dx<=n&&dy>=1&&dy<=n){
						if(!L[dx][dy]){ 
							add(Q(i,j),Q(dx,dy),1);
						}
					}
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(M[i][j]==1) add(S,Q(i,j),1);
			else add(Q(i,j),T,1);
		}
	}printf("%d\n",n*n-m-dinic());
	return 0;
}
