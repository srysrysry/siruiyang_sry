#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<climits>
#include<queue>
using namespace std;
inline int read(){
	int f=1,ans=0;char c;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
	return ans*f;
}
const int MAXN=40001;
struct node{
	int u,v,w,nex;
}x[MAXN<<1];
int deep[MAXN],head[MAXN],ans,vis,cnt,n,m,S,T,fa[MAXN];
queue<int> que; 
void add(int u,int v,int w){
	x[cnt].u=u,x[cnt].v=v,x[cnt].w=w,x[cnt].nex=head[u],head[u]=cnt++;
}
bool bfs(){
	memset(deep,127/3,sizeof(deep));
	int inf=deep[0];
	deep[S]=0;
	while(!que.empty()) que.pop();
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
			int slow=dfs(x[i].v,min(flow-used,x[i].w));
			used+=slow;
			x[i].w-=slow,x[i^1].w+=slow;
			if(used==flow) break;
		}
	}return used;
}
int dinic(){
	while(bfs()){
		vis=1;
		while(vis){
			vis=0;
			dfs(S,INT_MAX);
		}
	}return ans;
}
int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
void print(int xx){
	for(int i=head[xx];i!=-1;i=x[i].nex){
		if(x[i].v>n&&x[i].v<=2*n&&x[i].w==0){
			printf("%d ",x[i].v-n);
			print(x[i].v-n);
			break;
		}
	}return;
}
int main(){
	memset(head,-1,sizeof(head));
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(u,v+n,1),add(v+n,u,0); 
	}
	S=0,T=2*n+1;
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=n;i++) add(S,i,1),add(i,S,0);
	for(int i=1;i<=n;i++) add(i+n,T,1),add(T,i+n,0);
	int Ans=dinic();
	for(int i=0;i<cnt;i++) 
	     if(x[i].u>=1&&x[i].u<=n&&x[i].v>n&&x[i].v<=2*n&&x[i].w==0) fa[x[i].v-n]=find(fa[x[i].u]);
	for(int i=1;i<=n;i++)
	     if(i==find(i)){
	     	printf("%d ",i);
	     	print(i);
	     	printf("\n");
		 }
	printf("%d\n",n-Ans);
}
