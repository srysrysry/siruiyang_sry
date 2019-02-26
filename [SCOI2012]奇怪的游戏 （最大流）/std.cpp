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
const int N=401;
const int MAXN=32001;
queue<int> que;
struct node{
    int u,v,w,nex;
}x[MAXN];
int TT,cnt,n,m,a[N][N],INF=LLONG_MAX>>20,ans,Vis,inf,deep[MAXN],head[MAXN],M[N][N],S,T;
int Maxn,n1,n2,v1,v2;
void init(){cnt=0;memset(head,-1,sizeof(head));ans=0;}
void add(int u,int v,int w){
    x[cnt].u=u,x[cnt].v=v,x[cnt].w=w,x[cnt].nex=head[u],head[u]=cnt++;
}
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
    if(u==T){
        vis=1;
        ans+=flow;return flow;
    }
    int used=0;
    for(int i=head[u];i!=-1;i=x[i].nex){
        if(deep[x[i].v]==deep[u]+1&&x[i].w){
            int slow=dfs(x[i].v,min(flow-used,x[i].w));
            if(slow){
                used+=slow;
                x[i].w-=slow,x[i^1].w+=slow;
                if(slow==flow) break;
            }
        }
    }
    if(!used) deep[u]=-1;
    return used;
}
int dinic(){
    while(bfs()){
        vis=1;
        while(vis){
            vis=0;
            dfs(S,INF);
        }
    }return ans;
}
void gao(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(j>1) M[i][j]=1-M[i][j-1];
            else M[i][j]=1-M[i-1][j];
        }
    }
}
int Num;
inline int Q(int x,int y){return (x-1)*m+y;}
bool check(int lim){
    int sum=0,sum1=0;
    init();
    S=0,T=n*m+1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(M[i][j]&1){
                add(S,Q(i,j),lim-a[i][j]);
                add(Q(i,j),S,0);
                sum+=lim-a[i][j];
                if(j-1>=1)add(Q(i,j),Q(i,j-1),INF),add(Q(i,j-1),Q(i,j),0);
                if(j+1<=m)add(Q(i,j),Q(i,j+1),INF),add(Q(i,j+1),Q(i,j),0);
                if(i-1>=1)add(Q(i,j),Q(i-1,j),INF),add(Q(i-1,j),Q(i,j),0);
                if(i+1<=n)add(Q(i,j),Q(i+1,j),INF),add(Q(i+1,j),Q(i,j),0);
            }else{
                add(Q(i,j),T,lim-a[i][j]);
                add(T,Q(i,j),0);
                sum1+=lim-a[i][j];
            }
        }
    }
//  printf("%lld %lld\n",sum,sum1);
    if(sum!=sum1) return 0;
    int Ans=dinic();
    return Ans==sum;
}
signed main(){
//  freopen("8.in","r",stdin);
    TT=read();
    while(TT--){
        M[0][0]=0;
        Maxn=0,n1=0,n2=0,v1=0,v2=0;
        init();
        n=read(),m=read();
        gao();
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++){
                a[i][j]=read(),Maxn=max(Maxn,a[i][j]);
                if(M[i][j]&1) n1++,v1+=a[i][j];
                else n2++,v2+=a[i][j];
            }
        Num=n*m;
//      return 0;
        if(n1==n2){
            if((n*m)%2==0){
                int l=Maxn,r=INF>>1,minn=INF>>1;
                while(l<=r){
                    int mid=l+r>>1;
                    int opt=check((long long)mid);
                    if(!opt) l=mid+1;
                    else r=mid-1,minn=min(minn,mid);
                }
                if(minn==INF>>1){printf("-1\n");continue;}
                else {printf("%lld\n",(minn*n*m-(v1+v2))/2);continue;}
            }else{printf("-1\n");continue;}
        }else{
//          printf("%d %d %d %d\n",v2,v1,n2,n1);
            double x=(v2-v1)/(n2-n1);
            if(x<Maxn||(int)x!=x){printf("-1\n");continue;}
            if(check((int)x)){printf("%lld\n",((int)x*n*m-(v1+v2))/2);continue;}
            else{printf("-1\n");continue;}
        }
    }
}/*
1
2 2
2 2 
1 2 
*/
