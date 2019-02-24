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
struct node{
    int u,v,w,nex;
}x[MAXN<<1];
int cnt,head[MAXN];
void add(int u,int v,int w){
    x[cnt].u=u,x[cnt].v=v,x[cnt].w=w,x[cnt].nex=head[u],head[u]=cnt++;
}
queue<int> que;
vector<int> Que[MAXN];
int k,n,ans,deep[MAXN],a[MAXN],M[MAXN],sum,Cnt,S,T;
bool bfs(){
    memset(deep,127/3,sizeof(deep));
    int inf=deep[0];
    deep[S]=1;
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
int vis;
int dfs(int u,int flow){
	if(flow==0) return 0;
    if(u==T){
        vis=1;
        ans+=flow;return flow;
    }
    int used=0;
    for(int i=head[u];i!=-1;i=x[i].nex){
        if(deep[x[i].v]==deep[u]+1&&x[i].w){
            int slow=dfs(x[i].v,min(flow-used,x[i].w));
            if(slow>0){
                used+=slow;
                x[i].w-=slow,x[i^1].w+=slow;
                if(slow==flow) break;
            }
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
int Q[MAXN];
int main(){
//	freopen("3.in","r",stdin);
    memset(head,-1,sizeof(head));
    k=read(),n=read();
    for(int i=1;i<=k;i++) a[i]=read(),sum+=a[i];
    Cnt=n;
    S=++Cnt,T=++Cnt;
    for(int i=1;i<=k;i++){
        M[i]=++Cnt;Q[Cnt]=i;
        add(S,M[i],a[i]);add(M[i],S,0);
    }
    for(int i=1;i<=n;i++){
        int Num=read();
        for(int j=1;j<=Num;j++){
            int f=read();
            add(M[f],i,1),add(i,M[f],0);
        }
    }
    for(int i=1;i<=n;i++) add(i,T,1),add(T,i,0);
    int Ans=dinic();
    if(Ans!=sum){printf("No Solution!");return 0;}
    for(int i=0;i<cnt;i++){
//		printf("%d %d\n",Q[x[i].u],x[i].u);
        if(Q[x[i].u]>=1&&Q[x[i].u]<=k&&x[i].w==0&&x[i].u>=1&&x[i].v<=n){
//			printf("%d\n",x[i].u);
            Que[Q[x[i].u]].push_back(x[i].v);
        }
    }
//	return 0;
    for(int i=1;i<=k;i++){
        int siz=Que[i].size();
        printf("%d: ",i);
        for(int j=0;j<siz;j++) printf("%d ",Que[i][j]);
        printf("\n");
    }
}
