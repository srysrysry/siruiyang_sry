#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<queue>
#include<climits>
using namespace std;
inline int read(){
	int f=1,ans=0;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
	return f*ans;
}
queue<int> que;
const int MAXN=500001;
struct node{
	int u,v,w,nex;
}x[MAXN<<1];
int vis,deep[MAXN],f[MAXN],ans,head[MAXN],cnt,N,S,T;
void init(){memset(head,-1,sizeof(head));cnt=0;}
void add(int u,int v,int w){
	x[cnt].u=u,x[cnt].v=v,x[cnt].w=w,x[cnt].nex=head[u],head[u]=cnt++;
}
bool bfs(){
	memset(deep,127/3,sizeof(deep));
	int inf=deep[0];
	deep[S]=1;
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
int find(int x){
	if(f[x]==x) return x;
	return f[x]=find(f[x]);
}
int tot;
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
	}
	return used;
}
int dinic(){
	ans=0;
	while(bfs()){
		vis=1;
		while(vis){
			vis=0;
			dfs(S,INT_MAX);
		}
	}return ans;
}
int n,maxn;
int Query(int lim){
	init();
	N=lim;S=0,T=N*2+1;
	for(int i=1;i<=lim;i++)
	    for(int j=i+1;j<=lim;j++) if(sqrt(i+j)==(int)sqrt(i+j))add(i,j+N,1),add(j+N,i,0);
	for(int i=1;i<=N;i++) add(S,i,1),add(i,S,0);
	for(int i=1;i<=N;i++) add(i+N,T,1),add(T,i+N,0);
	int Ans=dinic();
	return N-Ans;
} 
void print(int u){
	for(int i=head[u];i!=-1;i=x[i].nex){
		int u=x[i].u,v=x[i].v-maxn;
        if(u>=1&&u<=maxn&&v>=1&&v<=maxn&&!x[i].w){
        	printf("%d ",v);
        	print(v);
        	return;
		}
	}
}
int main(){
	n=read();
	int l=1,r=2000;maxn=0;
	while(l<=r){
		int mid=l+r>>1;
		if(Query(mid)<=n) maxn=max(maxn,mid),l=mid+1;
		else r=mid-1; 
	}
	printf("%d\n",maxn);
	Query(maxn);
	for(int i=1;i<=maxn;i++) f[i]=i;
	for(int i=0;i<cnt;i++){
		int u=x[i].u,v=x[i].v-maxn;
		if(u>=1&&u<=maxn&&v>=1&&v<=maxn&&!x[i].w) f[v]=find(u);
	}
	for(int i=1;i<=maxn;i++)
	    if(find(i)==i){printf("%d ",i);print(i);printf("\n");} 
}
