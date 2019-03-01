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
const int MAXN=200001;
int n,m;
queue<int> que;
struct node{
	int u,v,w,nex;
}x[MAXN<<1];
int deep[MAXN],S,T,a[MAXN],cnt,M[MAXN],head[MAXN],INF=INT_MAX;
void add(int u,int v,int w){
	x[cnt].u=u,x[cnt].v=v,x[cnt].w=w,x[cnt].nex=head[u],head[u]=cnt++;
}
bool bfs(){
	memset(deep,127/3,sizeof(deep));
	int inf=deep[0];deep[S]=1;que.push(S);
	while(!que.empty()){
		int xx=que.front();que.pop();
		for(int i=head[xx];i!=-1;i=x[i].nex){
			if(deep[x[i].v]>deep[xx]+1&&x[i].w){
				deep[x[i].v]=deep[xx]+1;
				que.push(x[i].v); 
			}
		}
	}return deep[T]!=inf;
}int ans,vis;
int dfs(int u,int flow){
	if(u==T){ans+=flow;vis=1;return flow;}
	int used=0;
	for(int i=head[u];i!=-1;i=x[i].nex){
		if(deep[x[i].v]==deep[u]+1&&x[i].w){
			int slow=dfs(x[i].v,min(flow-used,x[i].w));used+=slow; 
			x[i].w-=slow,x[i^1].w+=slow;
			if(used==flow) break;
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
int main(){
//	freopen("9.in","r",stdin);
	S=0;
	memset(head,-1,sizeof(head));
	n=read(),m=read();
	T=m+1;
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=m;i++){
		int Cnt=read();
		for(int j=1;j<=Cnt;j++){
			int x=read();
			if(!M[x]) add(S,i,a[x]),add(i,S,0);
			else add(M[x],i,INF),add(i,M[x],0);
			M[x]=i;
		}
		int num=read();
	    add(i,T,num),add(T,i,0);
	}
	printf("%d\n",dinic());
	return 0;
}
