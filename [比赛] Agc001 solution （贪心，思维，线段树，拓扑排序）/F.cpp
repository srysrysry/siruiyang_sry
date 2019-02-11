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
const int N=500001;
int n,a[N],minn[N<<2],k;
struct node{
    int u,v,nex;
}x[N<<1];
int head[N];
struct segment_tree{
    void insert(int k,int l,int r,int x,int y,int val){
        if(l==r){minn[k]=val;return;}
        int mid=l+r>>1;
        if(x<=mid) insert(k<<1,l,mid,x,y,val);
        if(mid<y) insert(k<<1|1,mid+1,r,x,y,val);
        minn[k]=min(minn[k<<1],minn[k<<1|1]);
        return; 
    }
    int query(int k,int l,int r,int x,int y){
//		printf("x:%d y:%d\n",x,y);
        if(x>y) return INT_MAX;
        if(x<=l&&r<=y) return minn[k];
        int res=INT_MAX,mid=l+r>>1;
        if(x<=mid) res=min(res,query(k<<1,l,mid,x,y));
        if(mid<y) res=min(res,query(k<<1|1,mid+1,r,x,y));
        return res;
    }
}seg;
int cnt,du[N];
void add(int u,int v){
//	printf("u:%d v:%d\n",u,v);
    x[cnt].u=u,x[cnt].v=v,x[cnt].nex=head[u],head[u]=cnt++;
    du[v]++;
    return;
}
priority_queue<int> que;
int id[N];
int main(){
    memset(head,-1,sizeof(head));
    int inf=INT_MAX;
    memset(minn,127/3,sizeof(minn));
    n=read(),k=read();
    for(int i=1;i<=n;i++) a[read()]=i;
    for(int i=n;i>=1;i--){
        int pos=seg.query(1,1,n,a[i]+1,min(n,a[i]+k-1));
        if(pos>=1&&pos<=n) add(a[i],a[pos]);
        pos=seg.query(1,1,n,max(1,a[i]-k+1),a[i]-1);
        if(pos>=1&&pos<=n) add(a[i],a[pos]);
        seg.insert(1,1,n,a[i],a[i],i);
    }
    for(int i=1;i<=n;i++) if(!du[i]) que.push(-i);
    while(!que.empty()){
        int xx=-que.top();que.pop();
        id[xx]=++id[0];
        for(int i=head[xx];i!=-1;i=x[i].nex){
            du[x[i].v]--;
            if(!du[x[i].v]) que.push(-x[i].v);
        } 
    }
    for(int i=1;i<=n;i++) printf("%d\n",id[i]);
}

