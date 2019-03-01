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
int deep[MAXN],inf,S,T,cnt,head[MAXN],INF=INT_MAX;
void add(int u,int v,int w){
	x[cnt].u=u,x[cnt].v=v,x[cnt].w=w,x[cnt].nex=head[u],head[u]=cnt++;
}
bool bfs(){
	memset(deep,127/3,sizeof(deep));
	inf=deep[0];deep[S]=1;que.push(S);
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
int C[MAXN],sum;
queue<int> que1,que2;
int main(){
//	freopen("shut1.in","r",stdin);
	memset(head,-1,sizeof(head));
	n=read(),m=read();
	S=0,T=n+m+1;
	for(int i=1;i<=n;i++){
		int cost=read();
		sum+=cost;
		add(S,i,cost),add(i,S,0);
		char tools[10000];
        memset(tools,0,sizeof tools);
        cin.getline(tools,10000);
        int ulen=0,tool;
        while (sscanf(tools+ulen,"%d",&tool)==1){
		    add(i,tool+n,INF),add(tool+n,i,0);     
            if (tool==0) ulen++;
            else {
               while (tool) {
                    tool/=10;
                    ulen++;
                }
            }
            ulen++;
        }
	}
	for(int i=1;i<=m;i++){C[i]=read();add(i+n,T,C[i]),add(T,i+n,C[i]);}
	int Ans1=sum-dinic();
	bfs();
	for(int i=1;i<=n;i++)
		if(deep[i]!=inf) que1.push(i);
	for(int i=n+1;i<T;i++)
	    if(deep[i]!=inf) que2.push(i-n); 
	bool flag1=0;int siz=que1.size();
	for(int i=0;i<siz;i++){
		if(flag1==1) printf(" ");
		printf("%d",que1.front());que1.pop();
		flag1=1;
	}printf("\n");
	bool flag2=0;siz=que2.size();
	for(int i=0;i<siz;i++){
		if(flag2==1) printf(" ");
		printf("%d",que2.front());que2.pop();
		flag2=1;
	}printf("\n%d",Ans1);
}
