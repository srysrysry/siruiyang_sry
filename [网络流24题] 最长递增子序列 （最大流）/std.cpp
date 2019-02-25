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
queue<int> que;
const int MAXN=25001;
struct node{
	int u,v,w,nex;
}x[MAXN<<1];
int f[MAXN],deep[MAXN],S,T,cnt,head[MAXN],n,a[MAXN];
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
int Ans1,Ans2,Ans3,vis,ans;
int dfs(int u,int flow){
	if(u==T){vis=1;ans+=flow;return flow;}
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
	ans=0;
	while(bfs()){
		vis=1;
		while(vis){
			vis=0;
			dfs(S,INT_MAX);
		}
	}return ans;
}
int main(){
//	freopen("3.in","r",stdin);
	memset(head,-1,sizeof(head));
	n=read();
	if(n==1){
		for(int i=1;i<=3;i++) printf("1\n");
		return 0;
	}
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++)
	     for(int j=0;j<i;j++) if(a[j]<=a[i]) f[i]=max(f[i],f[j]+1);
	for(int i=1;i<=n;i++) Ans1=max(Ans1,f[i]);
	printf("%d\n",Ans1);
	S=0,T=2*n+1;
	for(int i=1;i<=n;i++) add(i,i+n,1),add(i+n,i,0);
	for(int i=1;i<=n;i++) if(f[i]==1) add(S,i,1),add(i,S,0);
	for(int i=1;i<=n;i++)
	    for(int j=1;j<i;j++) if(f[i]==f[j]+1&&a[j]<=a[i]) add(j+n,i,1),add(i,j+n,0);
	for(int i=1;i<=n;i++) if(f[i]==Ans1) add(i+n,T,1),add(T,i+n,0);
	Ans2=dinic();
	printf("%d\n",Ans2);
	add(S,1,INT_MAX),add(1,1+n,INT_MAX);
	if(f[n]==Ans1) add(n,2*n,INT_MAX),add(2*n,T,INT_MAX);
	Ans3=dinic()+Ans2;
	printf("%d\n",Ans3);
}/*
4
3 6 2 5
*/
